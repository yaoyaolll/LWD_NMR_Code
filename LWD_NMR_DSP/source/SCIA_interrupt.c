/*----------------------------ͷ�ļ�---------------------------------------------*/
#include "DSP281x_Device.h"   // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#pragma CODE_SECTION(SciaTx_Ready, "secureRamFuncs");
#pragma CODE_SECTION(SciaRx_Ready, "secureRamFuncs");
#pragma CODE_SECTION(SCIRXINTA_ISR, "secureRamFuncs");
#pragma CODE_SECTION(CpuTimer0ISR, "secureRamFuncs");
#pragma CODE_SECTION(parse_sci_rec_buf, "secureRamFuncs");
#define REC_BUF_LEN 100

// 485ÿ�ν���һ���ֽڣ�ƴ�ӳ�һ����
union Bytes2U16
{
    Uint16 data[REC_BUF_LEN];
    unsigned char bytes[2 * REC_BUF_LEN];       // ʵ����Ҳ�Ǵ��16λ
};


// ���峤��Ϊ100�Ľ��ջ�����
typedef struct
{
    union Bytes2U16 buf;    // ������
    int idx;                // �ѽ����ֽ���Ŀ��0<=idx<=2*REC_BUF_LEN
    int time_out;           // ��ʱ��־��0δ��ʱ��1��ʱ
    int start_rec;          // �Ƿ�ʼ���ձ�֡���ݣ�0�ѽ�������ͷ��1δ��������ͷ
    int frame_length;       // ���յı�֡���ݵ��ֽڳ���
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


// 1ms��ʱ���ж�
interrupt void CpuTimer0ISR(void) 
{
    CpuTimer0Regs.TCR.bit.TSS = 1;      //ֹͣ��ʱ��
    CpuTimer0Regs.TCR.bit.TRB = 1;      //��ʱ����װ������ʱ�����ڼĴ�����ֵװ�붨ʱ���������Ĵ���

    rec_buffer.time_out = 1;

//    CpuTimer0Regs.TCR.bit.TIF = 1;    // �����ʱ���жϱ�־λ
    PieCtrlRegs.PIEACK.bit.ACK1 = 1;    // ��Ӧͬ�������ж�
    EINT;                               // ��ȫ���ж�
}


// ����sci���մ���Ĵ���
void reset_sci(){
    if (SciaRegs.SCIRXST.bit.RXERROR == 1)    // ��������жϣ�SW RESET
    {
        SciaRegs.SCICTL1.bit.SWRESET = 0;
        SciaRegs.SCICTL1.bit.SWRESET = 1;
    }
}


// RS485�жϴ�����
interrupt void SCIRXINTA_ISR(void) // SCI-A�����жϺ���
{
    // ��ʱ����
    CpuTimer0Regs.TCR.bit.TRB = 1; //��ʱ����װ������ʱ�����ڼĴ�����ֵװ�붨ʱ���������Ĵ���
    CpuTimer0Regs.TCR.bit.TSS = 0; //������ʱ��

    if (rec_buffer.time_out)
    {
        // �����ϴ�����
        rec_buffer.start_rec = 1;
        rec_buffer.time_out = 0;
    }

    // ��������
    Uint16 sci_data;
    sci_data = SciaRegs.SCIRXBUF.bit.RXDT;          // �ӼĴ�����ȡ����

    // test code
//    data_rec_ary[idx++] = sci_data;
//    if (idx>=500)
//        idx = 0;

    if (rec_buffer.start_rec)  
    {
        // �ж�֡ͷ�ֽ��Ƿ����Ҫ�󣬷�ֹ������ż��λ
        if (sci_data == 0x99 || sci_data == 0x13 || sci_data == 0x14)       // ͷ��У��ϸ�
        {
            rec_buffer.idx = 0;
            rec_buffer.frame_length = -1;
            rec_buffer.start_rec = 0;   // �ѽ�������ͷ
        }
        else                                                                // ͷ��У�鲻�ϸ�
        {
            goto clear_int;
        }
    }

    rec_buffer.buf.bytes[rec_buffer.idx++] = sci_data;          // ���ݴ��뻺����    
    
    if (rec_buffer.idx == 4)                                    // �Ƿ���յ�֡����
    {
        rec_buffer.frame_length = ((rec_buffer.buf.bytes[2]<<8 | rec_buffer.buf.bytes[3]) + 1) << 1;   // ����֡���ֽڵĳ���
        if (rec_buffer.frame_length > 2 * REC_BUF_LEN || rec_buffer.frame_length <= 0)                      // ��ֹ���
            rec_buffer.start_rec = 1;
    }

    // ������ɣ���������
    if (rec_buffer.frame_length == rec_buffer.idx)
    {
        CpuTimer0Regs.TCR.bit.TSS = 1;                  //ֹͣ��ʱ��
        
        // parse rec_buf
        parse_sci_rec_buf();

        rec_buffer.start_rec = 1;                       // ������һ֡����
        rec_buffer.time_out = 0;
    }

clear_int:
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    EINT;
    //      SciaRegs.SCICTL1.bit.SLEEP = 1;         //������ɣ����� 485 ������ ��ַ
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
    if (rec_buffer.buf.data[FRAME_HEAD_INDEX] == DATA_DOWN_TABLE_F)    // ���ز���������
    {
        down_table_cmd();
        // reply
        ReplyLastCheckFrame(REPLY_DOWN_TABLE_F, check_sum); // ����У���
        return;
    }
    else if (rec_buffer.buf.data[FRAME_HEAD_INDEX] == DATA_UP_TABLE_F)  // �ϴ�����������
    {
        up_table_cmd();
        return;
    }
    else if (rec_buffer.buf.data[FRAME_HEAD_INDEX] == DATA_Parameter_F) // ��Ҫ�����·�ָ��
    {
        parameter_cmd();
        // reply
        ReplyLastCheckFrame(REPLY_Parameter_F, check_sum);
        return;
    }
    else if (rec_buffer.buf.data[FRAME_HEAD_INDEX] == DATA_K1K2_EN_F)   // ���ܶ̽ڿ���ָ��
    {
        K1K2_ctl_cmd();
        // reply
        ReplyNoVarFrame(DATA_K1K2_EN_F);
        return;
    }
    else if (rec_buffer.buf.data[FRAME_HEAD_INDEX] >= DATA_INQUIRE_F && rec_buffer.buf.data[BOARD_ADDR_INDEX] <= DATA_PAPS_F)   // ������
    {
        single_order_cmd();
        return;
    }
}

// ���ر������ַ
void down_table_cmd(void)
{
    // ���ݱ�Ĳ�ͬ���н���
    int len = rec_buffer.buf.data[FRAME_LEN_INDEX];
    if (len == CAL_TABLE_LEN + 3){               // �̶�ģʽ������
        SaveTablePt = ADDR_CAL_TABLE_START;
        *(Uint16 *)TABLE_START = rec_buffer.buf.data[3];    // �洢��ID
    }             
    else if (len == WELL_TABLE_LEN + 3){        // �⾮ģʽ������
        SaveTablePt = ADDR_WELL_TABLE_START;
        *(Uint16 *)TABLE_START = rec_buffer.buf.data[3];    // �洢��ID
    }
    else if (len == TUNING_TABLE_LEN + 3)       // �̶Ȳ�����
        SaveTablePt = ADDR_TUNING_TABLE_START;
    else if (len == CONFIG_TABLE_LEN + 3)       // �������ò�����
        SaveTablePt = ADDR_CONFIG_TABLE_START;
    
    *SaveTablePt++ = len;
    int i= 0;
    for (i=0; i<len-3;++i) {
        *SaveTablePt++ = rec_buffer.buf.data[i+3];  // idx=3��Ϊ����ʼ��
    }
    
    // ���ݿ̶�ģʽ������Ͳ⾮ģʽ���������þ��幤��ģʽ
    if (*(Uint16 *)TABLE_START == 0x0002)
        *(Uint16 *)0x8001 = *(Uint16 *)0x8007;
    else if (*(Uint16 *)TABLE_START == 0x0003)
        *(Uint16 *)0x8001 = *(Uint16 *)0x801D;
}


// �ϴ�������ָ�����
void up_table_cmd()
{
    SendTableID = rec_buffer.buf.data[3];
    SendTableFlag = SET;    // �ڿ���״̬���ϴ���
}


// ��uint16ת��Ϊfloat��
// ��Ҫע�������λ�������������ݿ�ͨ���˺������������¼�������λ�����͵���������������
// С����ǰ
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

// ��Ҫ�����·�ָ�����
void parameter_cmd()
{
    // �������ذ巢�����¶ȼ��㷢��Ƶ�ʺͼ̵�����
    float PTa0;
    float PTa1;
    float PTa2;
    float temperature = rec_buffer.buf.data[3] / 10.0;

    // PTa�ӿ̶Ȳ������е���
    PTa0 = type_transform(TuningTableEntry->PTa0[0], TuningTableEntry->PTa0[1]);
    PTa1 = type_transform(TuningTableEntry->PTa1[0], TuningTableEntry->PTa1[1]);
    PTa2 = type_transform(TuningTableEntry->PTa2[0], TuningTableEntry->PTa2[1]);

    // PAPS���Ӵ���
    PAPSEntry.STKLEV = rec_buffer.buf.data[4];

    // ����Ƶ��
    TransmitFre_f = (PTa0 + PTa1*temperature + PTa2*temperature*temperature) * 10.0;    // 0.1kHz

    // Ƶ���޷�
    if (TransmitFre_f < 3000)   // 0.1kHz
        TransmitFre = 3000;
    else if (TransmitFre_f > 6000)
        TransmitFre = 6000;
    else
        TransmitFre = (Uint16)(TransmitFre_f + 0.5);    // ��������

//    // ����̵�����
//    float rca0;
//    float rca1;
//    float rca2;
//    float frequency = TransmitFre / 10.0;
//
//    rca0 = type_transform(TuningTableEntry->rca0[0], TuningTableEntry->rca0[1]);
//    rca1 = type_transform(TuningTableEntry->rca1[0], TuningTableEntry->rca1[1]);
//    rca2 = type_transform(TuningTableEntry->rca2[0], TuningTableEntry->rca2[1]);
//
//    // ��������Ϲ�ʽ�����ݿ̶Ȳ������·�����������
//    RelayCtrlCode_f = rca0 + rca1*frequency + rca2*frequency*frequency;
//
//    // Ŀǰֻʹ����8���̵�������Ҫʱ������
//    // �޷���0~255
//    if (RelayCtrlCode_f < 0)
//        RelayCtrlCode =  0;
//    else if (RelayCtrlCode_f > 255)
//        RelayCtrlCode =  255;
//    else
//        RelayCtrlCode =  (Uint16)(RelayCtrlCode_f + 0.5);  // ǿ������ת��
    RelayCtrlCode = CalRelayFromFre(TransmitFre);

    // PAPS���Ӵ���
    PAPSEntry.STKLEV = rec_buffer.buf.data[4];
}

// ���ܶ̽ڿ���ָ�����
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
    // K2Ϊ���ֽڣ�K1Ϊ���ֽ�
    // ʵ�������ȱպ�K1���ٱպ�K2����20s���Ͽ�K1K2
    if (K1K2_ctl_ord == 0x0001)            // ��K1���պ�K2
    {
        K1_DIS = USER_ENABLE;       // K1�Ͽ�������ͣ�
        K2_EN  = USER_ENABLE;       // K2�պϣ�����ߣ�
        HVState = HV_ON;           // ������ѹ����
//        HVState = HV_OFF;
    }
    else if (K1K2_ctl_ord == 0x0100)
    {
        K1_EN = USER_ENABLE;    // K1�պϣ�����ߣ�
        K2_DIS = USER_ENABLE;   // K2�Ͽ�������ͣ�
        HVState = HV_OFF;
    }
    else if (K1K2_ctl_ord == 0x0101)       // K1 K2����
    {
        K1_DIS = USER_ENABLE;       // K1�Ͽ�������ͣ�
        K2_DIS = USER_ENABLE;       // K2�Ͽ�������ͣ�
        HVState = HV_OFF;           // ������ѹδ����
    }
    else if (K1K2_ctl_ord == 0)            // K1 K2���պ�
    {
        K1_EN = USER_DISABLE;      // K1�պϣ�����ߣ�
        K2_EN = USER_DISABLE;      // K2�պϣ�����ߣ�
        HVState = HV_OFF;            // ������ѹδ����
//        HVState = HV_ON;
    }
}


// �����������
void single_order_cmd()
{
    int single_ord_ary_idx = rec_buffer.buf.data[0] & 0x000F;

    // ���յ��������ص������ӳٵ���ʱ����
    if (single_ord_ary_idx <= 0xA)  // ��ֹԽ��
    {
        (*(singleOrderFunc[single_ord_ary_idx]))(); // �����������
    }
}


// ׼����������ʱΪ1������Ϊ0
unsigned int SciaTx_Ready(void)
{
    if (SciaRegs.SCICTL2.bit.TXRDY == 1)
        return (1);
    else
        return (0);
}

//׼����������ʱΪ1������Ϊ0
unsigned int SciaRx_Ready(void)
{
    if (SciaRegs.SCIRXST.bit.RXRDY == 1)
        return (1);
    else
        return (0);
}

// �˺�����Ҫ��GPIOF11���ʹ��
void SciaSendOneWord(Uint16 data)
{
    while (SciaTx_Ready() == 0)
    {
    }
    SciaRegs.SCITXBUF = data >> 8; // ���͸�8λ
    while (SciaTx_Ready() == 0)
    {
    }
    SciaRegs.SCITXBUF = data; // ���͵�8λ
}

// �̶�/�⾮ģʽ���ݻظ�֡
void ReplyModeDataFrame(Uint32 startAddr, Uint32 dataLen)
{
    SendTempPt = (Uint16 *)(startAddr);
    GpioDataRegs.GPFDAT.bit.GPIOF11 = 1; // SCIA����Ϊ����״̬
    for (SendCnt = 0; SendCnt < dataLen; SendCnt++)
    {
        SciaSendOneWord(*SendTempPt);
        SendTempPt++;
    }
    // �˴�Ҫ��һ����ʱ�������һ�����ݷ�����ȥ
    Delay(RS485_DELAY);
    GpioDataRegs.GPFDAT.bit.GPIOF11 = 0;
}

// ��ѯ״ָ̬��Ļظ�֡
void ReplyStateFrame(Uint16 state)
{
    Uint16 CheckSum = 0;

    CheckSum += REPLY_STATE_F;
    CheckSum += 4;
    CheckSum += EVENT_BOARD_ID;
    CheckSum += state;

    GpioDataRegs.GPFDAT.bit.GPIOF11 = 1; // SCIA����Ϊ����״̬
    SciaSendOneWord(REPLY_STATE_F);
    SciaSendOneWord(4);
    SciaSendOneWord(EVENT_BOARD_ID);
    SciaSendOneWord(state);
    SciaSendOneWord(CheckSum);
    // �˴�Ҫ��һ����ʱ�������һ�����ݷ�����ȥ
    Delay(RS485_DELAY);
    GpioDataRegs.GPFDAT.bit.GPIOF11 = 0; // SCIA����Ϊ����״̬
}

// ����������ָ��Ļظ�֡
void ReplyLastCheckFrame(Uint16 frameHead, Uint16 lastCheckSum)
{
    Uint16 CheckSum = 0;
    CheckSum += frameHead;
    CheckSum += 4;
    CheckSum += EVENT_BOARD_ID;
    CheckSum += lastCheckSum;

    GpioDataRegs.GPFDAT.bit.GPIOF11 = 1; // SCIA����Ϊ����״̬
    SciaSendOneWord(frameHead);
    SciaSendOneWord(4);
    SciaSendOneWord(EVENT_BOARD_ID);
    SciaSendOneWord(lastCheckSum);
    SciaSendOneWord(CheckSum);
    // �˴�Ҫ��һ����ʱ�������һ�����ݷ�����ȥ
    Delay(RS485_DELAY);
    GpioDataRegs.GPFDAT.bit.GPIOF11 = 0; // SCIA����Ϊ����״̬
}

// �������ϴ�ָ��Ļظ�֡
void ReplyUpTableFrame(Uint16 tableID)
{
    Uint16 *addr;
    Uint16 len = 0;
    Uint16 CheckSum = 0;
    int i = 0;
    if (tableID == 1)               // �̶Ȳ�����
        addr = ADDR_TUNING_TABLE_START;
    else if (tableID == 2)          // �̶�ģʽ������
        addr = ADDR_CAL_TABLE_START;
    else if (tableID == 3)          // �⾮ģʽ������
        addr = ADDR_WELL_TABLE_START;
    else                            // ��ֹ��
        return;

    len = *addr;

    GpioDataRegs.GPFDAT.bit.GPIOF11 = 1;    // SCIA����Ϊ����״̬
    SciaSendOneWord(REPLY_UP_TABLE_F);      // ֡ͷ
    SciaSendOneWord(len);
    SciaSendOneWord(EVENT_BOARD_ID);        // �����ӻ���ʶ
    addr++;
    CheckSum = REPLY_UP_TABLE_F;
    CheckSum += len;
    CheckSum += EVENT_BOARD_ID;
    for (i = 0; i < len - 3; ++i)           // �����������ͱ��ز�����ĩβ�洢��CheckSum
    {
        SciaSendOneWord(*addr);
        CheckSum += *addr;
        addr++;
    }

    SciaSendOneWord(CheckSum);              // ���ݰ���CheckSum
    // �˴�Ҫ��һ����ʱ�������һ�����ݷ�����ȥ
    Delay(RS485_DELAY);
    GpioDataRegs.GPFDAT.bit.GPIOF11 = 0; // SCIA����Ϊ����״̬
}

// �׹ܼ�������쳣ʱ�Ļظ�֡
void ReplyCasingErrFrame()
{
    Uint16 CheckSum = 0;
    CheckSum += REPLY_CASING_ERR_F;
    CheckSum += 3;
    CheckSum += EVENT_BOARD_ID;

    GpioDataRegs.GPFDAT.bit.GPIOF11 = 1; // SCIA����Ϊ����״̬
    SciaSendOneWord(REPLY_CASING_ERR_F);
    SciaSendOneWord(3);
    SciaSendOneWord(EVENT_BOARD_ID);
    SciaSendOneWord(CheckSum);
    // �˴�Ҫ��һ����ʱ�������һ�����ݷ�����ȥ
    Delay(RS485_DELAY);
    GpioDataRegs.GPFDAT.bit.GPIOF11 = 0;
}

// �ظ��������ݵ�֡ͷ
void ReplyNoVarFrame(Uint16 frameHead)
{
    Uint16 CheckSum = 0;
    CheckSum += frameHead;
    CheckSum += 3;
    CheckSum += EVENT_BOARD_ID;

    GpioDataRegs.GPFDAT.bit.GPIOF11 = 1; // SCIA����Ϊ����״̬
    SciaSendOneWord(frameHead);
    SciaSendOneWord(3);
    SciaSendOneWord(EVENT_BOARD_ID);
    SciaSendOneWord(CheckSum);
    // �˴�Ҫ��һ����ʱ�������һ�����ݷ�����ȥ
    Delay(RS485_DELAY);
    GpioDataRegs.GPFDAT.bit.GPIOF11 = 0;
}

// ���������Ļظ�֡�������ڴ��ܶ̽��жϺ�ϵͳ�Լ��ָ����
void ReplySingleVarFrame(Uint16 frameHead, Uint16 var)
{
    Uint16 CheckSum = 0;

    CheckSum += frameHead;
    CheckSum += 4;
    CheckSum += EVENT_BOARD_ID;
    CheckSum += var;

    GpioDataRegs.GPFDAT.bit.GPIOF11 = 1; // SCIA����Ϊ����״̬
    SciaSendOneWord(frameHead);
    SciaSendOneWord(4);
    SciaSendOneWord(EVENT_BOARD_ID);
    SciaSendOneWord(var);
    SciaSendOneWord(CheckSum);
    // �˴�Ҫ��һ����ʱ�������һ�����ݷ�����ȥ
    Delay(RS485_DELAY);
    GpioDataRegs.GPFDAT.bit.GPIOF11 = 0; // SCIA����Ϊ����״̬
}


