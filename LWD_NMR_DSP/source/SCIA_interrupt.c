/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"   // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(SciaTx_Ready, "secureRamFuncs");
#pragma CODE_SECTION(SciaRx_Ready, "secureRamFuncs");
#pragma CODE_SECTION(SCIRXINTA_ISR, "secureRamFuncs");
#pragma CODE_SECTION(CpuTimer0ISR, "secureRamFuncs");
#pragma CODE_SECTION(parse_sci_rec_buf, "secureRamFuncs");
#define REC_BUF_LEN 100

// 485每次接收一个字节，拼接成一个字
union Bytes2U16
{
    Uint16 data[REC_BUF_LEN];
    unsigned char bytes[2 * REC_BUF_LEN];       // 实际上也是存的16位
};


// 定义长度为100的接收缓冲区
typedef struct
{
    union Bytes2U16 buf;    // 缓冲区
    int idx;                // 已接收字节数目，0<=idx<=2*REC_BUF_LEN
    int time_out;           // 超时标志，0未超时，1超时
    int start_rec;          // 是否开始接收本帧数据，0已接收数据头，1未接收数据头
    int frame_length;       // 接收的本帧数据的字节长度
}RecBuffer_t;
RecBuffer_t rec_buffer;
#pragma DATA_SECTION(rec_buffer, "MyVariablesZone");


// initialize sci rec_buf
void clear_sci_rec_buf()
{
    rec_buffer.idx = 0;
    rec_buffer.time_out = 0;
    rec_buffer.start_rec = 1;
    rec_buffer.frame_length = -1;
}


// 1ms定时器中断
interrupt void CpuTimer0ISR(void) 
{
    CpuTimer0Regs.TCR.bit.TSS = 1;      //停止定时器
    CpuTimer0Regs.TCR.bit.TRB = 1;      //定时器重装，将定时器周期寄存器的值装入定时器计数器寄存器

    rec_buffer.time_out = 1;

//    CpuTimer0Regs.TCR.bit.TIF = 1;    // 清除定时器中断标志位
    PieCtrlRegs.PIEACK.bit.ACK1 = 1;    // 响应同组其他中断
    EINT;                               // 开全局中断
}


// 重置sci接收错误寄存器
void reset_sci(){
    if (SciaRegs.SCIRXST.bit.RXERROR == 1)    // 进入错误中断，SW RESET
    {
        SciaRegs.SCICTL1.bit.SWRESET = 0;
        SciaRegs.SCICTL1.bit.SWRESET = 1;
    }
}


// RS485中断处理函数
interrupt void SCIRXINTA_ISR(void) // SCI-A接收中断函数
{
    // 超时处理
    CpuTimer0Regs.TCR.bit.TRB = 1; //定时器重装，将定时器周期寄存器的值装入定时器计数器寄存器
    CpuTimer0Regs.TCR.bit.TSS = 0; //重启定时器

    if (rec_buffer.time_out)
    {
        // 放弃上次数据
        rec_buffer.start_rec = 1;
        rec_buffer.time_out = 0;
    }

    // 接收数据
    Uint16 sci_data;
    sci_data = SciaRegs.SCIRXBUF.bit.RXDT;          // 从寄存器获取数据

    // test code
//    data_rec_ary[idx++] = sci_data;
//    if (idx>=500)
//        idx = 0;

    if (rec_buffer.start_rec)  
    {
        // 判断帧头字节是否符合要求，防止后续奇偶错位
        if (sci_data == 0x99 || sci_data == 0x13 || sci_data == 0x14)       // 头部校验合格
        {
            rec_buffer.idx = 0;
            rec_buffer.frame_length = -1;
            rec_buffer.start_rec = 0;   // 已接收数据头
        }
        else                                                                // 头部校验不合格
        {
            goto clear_int;
        }
    }

    rec_buffer.buf.bytes[rec_buffer.idx++] = sci_data;          // 数据存入缓冲区    
    
    if (rec_buffer.idx == 4)                                    // 是否接收到帧长度
    {
        rec_buffer.frame_length = ((rec_buffer.buf.bytes[2]<<8 | rec_buffer.buf.bytes[3]) + 1) << 1;   // 整个帧的字节的长度
        if (rec_buffer.frame_length > 2 * REC_BUF_LEN || rec_buffer.frame_length <= 0)                      // 防止溢出
            rec_buffer.start_rec = 1;
    }

    // 接收完成，解析数据
    if (rec_buffer.frame_length == rec_buffer.idx)
    {
        CpuTimer0Regs.TCR.bit.TSS = 1;                  //停止定时器
        
        // parse rec_buf
        parse_sci_rec_buf();

        rec_buffer.start_rec = 1;                       // 接收下一帧数据
        rec_buffer.time_out = 0;
    }

clear_int:
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    EINT;
    //      SciaRegs.SCICTL1.bit.SLEEP = 1;         //更改完成，结束 485 总线上 地址
    return;
}


#define FRAME_HEAD_INDEX 0 
#define FRAME_LEN_INDEX  1
#define BOARD_ADDR_INDEX 2
void parse_sci_rec_buf()
{
    // copy data from buffer to ram
    int i = 0;
    for (i=0;i<rec_buffer.idx;++i)
        rec_buffer.buf.data[i] = rec_buffer.buf.bytes[2*i]<<8 | rec_buffer.buf.bytes[2*i+1];

    // first validate address
    if (rec_buffer.buf.data[BOARD_ADDR_INDEX] != EVENT_BOARD_ID)
        return;

    // second validate checksum
    Uint16 check_sum = 0;
    for (i=0; i<rec_buffer.buf.data[FRAME_LEN_INDEX]; ++i)
    {
        check_sum += rec_buffer.buf.data[i];
    }
    if (check_sum != rec_buffer.buf.data[i])
        return;

    // third analyze the data according to the frame header
    if (rec_buffer.buf.data[FRAME_HEAD_INDEX] == DATA_DOWN_TABLE_F)    // 下载参数表命令
    {
        down_table_cmd();
        // reply
        ReplyLastCheckFrame(REPLY_DOWN_TABLE_F, check_sum); // 返回校验和
        return;
    }
    else if (rec_buffer.buf.data[FRAME_HEAD_INDEX] == DATA_UP_TABLE_F)  // 上传参数表命令
    {
        up_table_cmd();
        return;
    }
    else if (rec_buffer.buf.data[FRAME_HEAD_INDEX] == DATA_Parameter_F) // 重要参数下发指令
    {
        parameter_cmd();
        // reply
        ReplyLastCheckFrame(REPLY_Parameter_F, check_sum);
        return;
    }
    else if (rec_buffer.buf.data[FRAME_HEAD_INDEX] == DATA_K1K2_EN_F)   // 储能短节控制指令
    {
        K1K2_ctl_cmd();
        // reply
        ReplyNoVarFrame(DATA_K1K2_EN_F);
        return;
    }
    else if (rec_buffer.buf.data[FRAME_HEAD_INDEX] >= DATA_INQUIRE_F && rec_buffer.buf.data[BOARD_ADDR_INDEX] <= DATA_PAPS_F)   // 单命令
    {
        single_order_cmd();
        return;
    }
}

// 下载表并存入地址
void down_table_cmd(void)
{
    // 根据表的不同进行解析
    int len = rec_buffer.buf.data[FRAME_LEN_INDEX];
    if (len == CAL_TABLE_LEN + 3){               // 刻度模式参数表
        SaveTablePt = ADDR_CAL_TABLE_START;
        *(Uint16 *)TABLE_START = rec_buffer.buf.data[3];    // 存储表ID
    }             
    else if (len == WELL_TABLE_LEN + 3){        // 测井模式参数表
        SaveTablePt = ADDR_WELL_TABLE_START;
        *(Uint16 *)TABLE_START = rec_buffer.buf.data[3];    // 存储表ID
    }
    else if (len == TUNING_TABLE_LEN + 3)       // 刻度参数表
        SaveTablePt = ADDR_TUNING_TABLE_START;
    else if (len == CONFIG_TABLE_LEN + 3)       // 仪器配置参数表
        SaveTablePt = ADDR_CONFIG_TABLE_START;
    
    *SaveTablePt++ = len;
    int i= 0;
    for (i=0; i<len-3;++i) {
        *SaveTablePt++ = rec_buffer.buf.data[i+3];  // idx=3处为表起始处
    }
    
    // 根据刻度模式参数表和测井模式参数表设置具体工作模式
    if (*(Uint16 *)TABLE_START == 0x0002)
        *(Uint16 *)0x8001 = *(Uint16 *)0x8007;
    else if (*(Uint16 *)TABLE_START == 0x0003)
        *(Uint16 *)0x8001 = *(Uint16 *)0x801D;
}


// 上传参数表指令解析
void up_table_cmd()
{
    SendTableID = rec_buffer.buf.data[3];
    SendTableFlag = SET;    // 在空闲状态下上传表
}


// 将uint16转换为float型
// 需要注意的是上位机发下来的数据可通过此函数解析，而事件板向上位机发送的则无需这样解析
// 小端在前
float type_transform(Uint16 data1, Uint16 data2){
    Float2Uint16_u xxx;
    unsigned char c_l = data1 & 0xff;
    unsigned char c_h = data1 >> 8;
    xxx.data[1] = c_l << 8 | c_h;
    c_l = data2 & 0xff;
    c_h = data2 >> 8;
    xxx.data[0] = c_l << 8 | c_h;
    return xxx.real_data;
}

// 重要参数下发指令解析
void parameter_cmd()
{
    // 根据主控板发来的温度计算发射频率和继电器码
    float PTa0;
    float PTa1;
    float PTa2;
    float temperature = rec_buffer.buf.data[3] / 10.0;

    // PTa从刻度参数表中得来
    PTa0 = type_transform(TuningTableEntry->PTa0[0], TuningTableEntry->PTa0[1]);
    PTa1 = type_transform(TuningTableEntry->PTa1[0], TuningTableEntry->PTa1[1]);
    PTa2 = type_transform(TuningTableEntry->PTa2[0], TuningTableEntry->PTa2[1]);

    // PAPS叠加次数
    PAPSEntry.STKLEV = rec_buffer.buf.data[4];

    // 计算频率
    TransmitFre_f = (PTa0 + PTa1*temperature + PTa2*temperature*temperature) * 10.0;    // 0.1kHz

    // 频率限幅
    if (TransmitFre_f < 3000)   // 0.1kHz
        TransmitFre = 3000;
    else if (TransmitFre_f > 6000)
        TransmitFre = 6000;
    else
        TransmitFre = (Uint16)(TransmitFre_f + 0.5);    // 四舍五入

//    // 计算继电器码
//    float rca0;
//    float rca1;
//    float rca2;
//    float frequency = TransmitFre / 10.0;
//
//    rca0 = type_transform(TuningTableEntry->rca0[0], TuningTableEntry->rca0[1]);
//    rca1 = type_transform(TuningTableEntry->rca1[0], TuningTableEntry->rca1[1]);
//    rca2 = type_transform(TuningTableEntry->rca2[0], TuningTableEntry->rca2[1]);
//
//    // 二次项拟合公式，根据刻度参数表下发参数来计算
//    RelayCtrlCode_f = rca0 + rca1*frequency + rca2*frequency*frequency;
//
//    // 目前只使用了8个继电器，需要时再扩增
//    // 限幅到0~255
//    if (RelayCtrlCode_f < 0)
//        RelayCtrlCode =  0;
//    else if (RelayCtrlCode_f > 255)
//        RelayCtrlCode =  255;
//    else
//        RelayCtrlCode =  (Uint16)(RelayCtrlCode_f + 0.5);  // 强制类型转换
    RelayCtrlCode = CalRelayFromFre(TransmitFre);

    // PAPS叠加次数
    PAPSEntry.STKLEV = rec_buffer.buf.data[4];
}

// 储能短节控制指令解析
void K1K2_ctl_cmd()
{
    /*
        * K1K2: high level means close
        *       low level means open
        * FPGA code:
                *-----k1------*
                'h00A0:
                        k1 <= 1;
                'h00A1:
                        k1 <= 0;

                *-----k2------*
                'h00A2:
                        k2 <= 1;
                'h00A3:
                        k2 <= 0;
    */
    Uint16 K1K2_ctl_ord = rec_buffer.buf.data[3];
    // K2为高字节，K1为低字节
    // 实际流程先闭合K1，再闭合K2，过20s，断开K1K2
    if (K1K2_ctl_ord == 0x0001)            // 打开K1，闭合K2
    {
        K1_DIS = USER_ENABLE;       // K1断开（输出低）
        K2_EN  = USER_ENABLE;       // K2闭合（输出高）
        HVState = HV_ON;           // 表明高压启用
//        HVState = HV_OFF;
    }
    else if (K1K2_ctl_ord == 0x0100)
    {
        K1_EN = USER_ENABLE;    // K1闭合（输出高）
        K2_DIS = USER_ENABLE;   // K2断开（输出低）
        HVState = HV_OFF;
    }
    else if (K1K2_ctl_ord == 0x0101)       // K1 K2均打开
    {
        K1_DIS = USER_ENABLE;       // K1断开（输出低）
        K2_DIS = USER_ENABLE;       // K2断开（输出低）
        HVState = HV_OFF;           // 表明高压未启用
    }
    else if (K1K2_ctl_ord == 0)            // K1 K2均闭合
    {
        K1_EN = USER_DISABLE;      // K1闭合（输出高）
        K2_EN = USER_DISABLE;      // K2闭合（输出高）
        HVState = HV_OFF;            // 表明高压未启用
//        HVState = HV_ON;
    }
}


// 单个命令解析
void single_order_cmd()
{
    int single_ord_ary_idx = rec_buffer.buf.data[0] & 0x000F;

    // 接收到来自主控的数据延迟到此时处理
    if (single_ord_ary_idx <= 0xA)  // 防止越界
    {
        (*(singleOrderFunc[single_ord_ary_idx]))(); // 单个命令处理函数
    }
}


// 准备发送数据时为1，否则为0
unsigned int SciaTx_Ready(void)
{
    if (SciaRegs.SCICTL2.bit.TXRDY == 1)
        return (1);
    else
        return (0);
}

//准备接收数据时为1，否则为0
unsigned int SciaRx_Ready(void)
{
    if (SciaRegs.SCIRXST.bit.RXRDY == 1)
        return (1);
    else
        return (0);
}

// 此函数需要与GPIOF11配合使用
void SciaSendOneWord(Uint16 data)
{
    while (SciaTx_Ready() == 0)
    {
    }
    SciaRegs.SCITXBUF = data >> 8; // 发送高8位
    while (SciaTx_Ready() == 0)
    {
    }
    SciaRegs.SCITXBUF = data; // 发送低8位
}

// 刻度/测井模式数据回复帧
void ReplyModeDataFrame(Uint32 startAddr, Uint32 dataLen)
{
    SendTempPt = (Uint16 *)(startAddr);
    GpioDataRegs.GPFDAT.bit.GPIOF11 = 1; // SCIA设置为发送状态
    for (SendCnt = 0; SendCnt < dataLen; SendCnt++)
    {
        SciaSendOneWord(*SendTempPt);
        SendTempPt++;
    }
    // 此处要加一定延时避免最后一个数据发不出去
    Delay(RS485_DELAY);
    GpioDataRegs.GPFDAT.bit.GPIOF11 = 0;
}

// 查询状态指令的回复帧
void ReplyStateFrame(Uint16 state)
{
    Uint16 CheckSum = 0;

    CheckSum += REPLY_STATE_F;
    CheckSum += 4;
    CheckSum += EVENT_BOARD_ID;
    CheckSum += state;

    GpioDataRegs.GPFDAT.bit.GPIOF11 = 1; // SCIA设置为发送状态
    SciaSendOneWord(REPLY_STATE_F);
    SciaSendOneWord(4);
    SciaSendOneWord(EVENT_BOARD_ID);
    SciaSendOneWord(state);
    SciaSendOneWord(CheckSum);
    // 此处要加一定延时避免最后一个数据发不出去
    Delay(RS485_DELAY);
    GpioDataRegs.GPFDAT.bit.GPIOF11 = 0; // SCIA设置为接收状态
}

// 参数表下载指令的回复帧
void ReplyLastCheckFrame(Uint16 frameHead, Uint16 lastCheckSum)
{
    Uint16 CheckSum = 0;
    CheckSum += frameHead;
    CheckSum += 4;
    CheckSum += EVENT_BOARD_ID;
    CheckSum += lastCheckSum;

    GpioDataRegs.GPFDAT.bit.GPIOF11 = 1; // SCIA设置为发送状态
    SciaSendOneWord(frameHead);
    SciaSendOneWord(4);
    SciaSendOneWord(EVENT_BOARD_ID);
    SciaSendOneWord(lastCheckSum);
    SciaSendOneWord(CheckSum);
    // 此处要加一定延时避免最后一个数据发不出去
    Delay(RS485_DELAY);
    GpioDataRegs.GPFDAT.bit.GPIOF11 = 0; // SCIA设置为接收状态
}

// 参数表上传指令的回复帧
void ReplyUpTableFrame(Uint16 tableID)
{
    Uint16 *addr;
    Uint16 len = 0;
    Uint16 CheckSum = 0;
    int i = 0;
    if (tableID == 1)               // 刻度参数表
        addr = ADDR_TUNING_TABLE_START;
    else if (tableID == 2)          // 刻度模式参数表
        addr = ADDR_CAL_TABLE_START;
    else if (tableID == 3)          // 测井模式参数表
        addr = ADDR_WELL_TABLE_START;
    else                            // 防止误发
        return;

    len = *addr;

    GpioDataRegs.GPFDAT.bit.GPIOF11 = 1;    // SCIA设置为发送状态
    SciaSendOneWord(REPLY_UP_TABLE_F);      // 帧头
    SciaSendOneWord(len);
    SciaSendOneWord(EVENT_BOARD_ID);        // 新增从机标识
    addr++;
    CheckSum = REPLY_UP_TABLE_F;
    CheckSum += len;
    CheckSum += EVENT_BOARD_ID;
    for (i = 0; i < len - 3; ++i)           // 参数表，不发送本地参数表末尾存储的CheckSum
    {
        SciaSendOneWord(*addr);
        CheckSum += *addr;
        addr++;
    }

    SciaSendOneWord(CheckSum);              // 数据包的CheckSum
    // 此处要加一定延时避免最后一个数据发不出去
    Delay(RS485_DELAY);
    GpioDataRegs.GPFDAT.bit.GPIOF11 = 0; // SCIA设置为接收状态
}

// 套管检测数据异常时的回复帧
void ReplyCasingErrFrame()
{
    Uint16 CheckSum = 0;
    CheckSum += REPLY_CASING_ERR_F;
    CheckSum += 3;
    CheckSum += EVENT_BOARD_ID;

    GpioDataRegs.GPFDAT.bit.GPIOF11 = 1; // SCIA设置为发送状态
    SciaSendOneWord(REPLY_CASING_ERR_F);
    SciaSendOneWord(3);
    SciaSendOneWord(EVENT_BOARD_ID);
    SciaSendOneWord(CheckSum);
    // 此处要加一定延时避免最后一个数据发不出去
    Delay(RS485_DELAY);
    GpioDataRegs.GPFDAT.bit.GPIOF11 = 0;
}

// 回复不带内容的帧头
void ReplyNoVarFrame(Uint16 frameHead)
{
    Uint16 CheckSum = 0;
    CheckSum += frameHead;
    CheckSum += 3;
    CheckSum += EVENT_BOARD_ID;

    GpioDataRegs.GPFDAT.bit.GPIOF11 = 1; // SCIA设置为发送状态
    SciaSendOneWord(frameHead);
    SciaSendOneWord(3);
    SciaSendOneWord(EVENT_BOARD_ID);
    SciaSendOneWord(CheckSum);
    // 此处要加一定延时避免最后一个数据发不出去
    Delay(RS485_DELAY);
    GpioDataRegs.GPFDAT.bit.GPIOF11 = 0;
}

// 单个变量的回复帧，可用于储能短节判断和系统自检测指令中
void ReplySingleVarFrame(Uint16 frameHead, Uint16 var)
{
    Uint16 CheckSum = 0;

    CheckSum += frameHead;
    CheckSum += 4;
    CheckSum += EVENT_BOARD_ID;
    CheckSum += var;

    GpioDataRegs.GPFDAT.bit.GPIOF11 = 1; // SCIA设置为发送状态
    SciaSendOneWord(frameHead);
    SciaSendOneWord(4);
    SciaSendOneWord(EVENT_BOARD_ID);
    SciaSendOneWord(var);
    SciaSendOneWord(CheckSum);
    // 此处要加一定延时避免最后一个数据发不出去
    Delay(RS485_DELAY);
    GpioDataRegs.GPFDAT.bit.GPIOF11 = 0; // SCIA设置为接收状态
}


