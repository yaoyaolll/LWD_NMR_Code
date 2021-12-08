/*
 * @Descripttion: 实现PAPS对处理和累加平均功能，此功能只在测井模式下有用
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-09-22 11:45:59
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-09-23 14:54:12
 */
#include "DSP281x_Device.h"	  // DSP281x Headerfile Include File
#include "DSP281x_Examples.h" // DSP281x Examples Include File
#include "MyHeaderFiles.h"

#ifdef DEBUG
#pragma CODE_SECTION(PAPSDataGenerate, "secureRamFuncs");
#pragma CODE_SECTION(StorgePAPSToFIFO, "secureRamFuncs");
#pragma CODE_SECTION(PAPSTop, "secureRamFuncs");
#endif

// 滑动平均算法
int PAPSDataGenerate(PAPSEntry_t* PAPSEntryPt)
{
    // 检查FIFO填充长度是否为符合要求
    Uint16 FIFO_len = PAPSEntryPt->PAPSFIFO_end - PAPSEntryPt->PAPSFIFO_start;
    if (FIFO_len != PAPSEntryPt->STKLEV)
        return 0;

    Uint16 FIFO_element_size = 2 * (PAPSEntryPt->echo_1A_num + PAPSEntryPt->echo_1C_num);
    Uint16* PAPS_data_storge_pt = (Uint16*)(PAPS_STORAGE_DATA_ADDR);      // PAPS数据存储地址
    int i = 0;
    for (i=0;i<FIFO_element_size;++i)
    {
        int j, k;
        float sum = 0.0f;
        for (j=PAPSEntryPt->PAPSFIFO_start, k=1; j<PAPSEntryPt->PAPSFIFO_end; ++j, ++k) 
        {
            int index = j & PAPS_FIFO_MASK;
            Uint32 PAPS_index_addr = PAPS_FIFO_ADDR + index*FIFO_element_size + i;  // 数据点的地址
            int PAPS_data = *((int *)PAPS_index_addr);
            // 滑动平均算法
            if (k==1 || k == PAPSEntryPt->STKLEV)    // 首或者尾
                sum += PAPS_data;
            else if (k&1 == 0)      // even
                sum -= (2*PAPS_data);
            else
                sum += (2*PAPS_data);
        }
        *PAPS_data_storge_pt++ = (Uint16)(sum / (2*(PAPSEntryPt->STKLEV - 1)));
    }

    // 填写PAPS数据上传帧
    
    return 1;
}

// 在每个模式的末尾填好结构体，调用此函数将1A、1C回波数据填入FIFO
void StorgePAPSToFIFO(PAPSEntry_t* PAPSEntryPt) 
{
    if (PAPSEntryPt->current_well_mode != PAPSEntryPt->last_well_mode)
    {
        PAPSEntryPt->PAPSFIFO_start = 0;
        PAPSEntryPt->PAPSFIFO_end = 0;
    }

    PAPSEntryPt->last_well_mode = PAPSEntryPt->current_well_mode;

    if (!PAPSEntryPt->PAPSFIFO_start && !PAPSEntryPt->PAPSFIFO_end && PhaseFlag == NEGATIVE)
    {
        return;
    }
        
    // 将FIFO内有效元素个数维持在叠加次数
    Uint16 FIFO_element_size = 2 * (PAPSEntryPt->echo_1A_num + PAPSEntryPt->echo_1C_num);
    // 基地址
    Uint16* fifo_base_pt = (Uint16*)(PAPS_FIFO_ADDR + FIFO_element_size*(PAPSEntryPt->PAPSFIFO_end & PAPS_FIFO_MASK));
    if (PAPSEntryPt->PAPSFIFO_end - PAPSEntryPt->PAPSFIFO_start >= PAPSEntryPt->STKLEV && PAPSEntryPt->STKLEV != 0)
    {
        PAPSEntryPt->PAPSFIFO_start++;
    }
    PAPSEntryPt->PAPSFIFO_end++;

    // 将回波数据移入FIFO
    // 1A
    int i;
    for (i=0;i<PAPSEntryPt->echo_1A_num*2;++i)
    {
        *fifo_base_pt++ = *((Uint16*)(PAPSEntryPt->echo_1A_addr + i));
    }
    // 1C, need average operation
    for (i=0;i<PAPSEntryPt->echo_1C_num*2;++i)
    {
        float sum = 0.0f;
        int j;
        int average_num;
        for (j=0;j<PAPSEntryPt->echo_1C_nrept;++j)
        {
            Uint32 echo_data_addr = PAPSEntryPt->echo_1C_addr1 + PAPSEntryPt->echo_1C_num*j;
            sum += *((Uint16*)echo_data_addr);
        }
        average_num = PAPSEntryPt->echo_1C_nrept;

        if (PAPSEntryPt->current_well_mode == 0x0003)       // PPDIF，两段1C
        {
            for (j=0;j<PAPSEntryPt->echo_1C_nrept;++j)
            {
                Uint32 echo_data_addr = PAPSEntryPt->echo_1C_addr2 + PAPSEntryPt->echo_1C_num*j;
                sum += *((Uint16*)echo_data_addr);
            }
            average_num = PAPSEntryPt->echo_1C_nrept*2;
        }

        *fifo_base_pt++ = (Uint16)(sum / average_num);
    }

    return;
}

// PAPS处理函数，当主控板向事件板索要滑动平均数据时调用
void PAPSTop(void)
{
    Uint16* PAPS_data_frame_pt = (Uint16*)(PAPSTABLE_START);
    *(PAPS_data_frame_pt + 0) = REPLY_PAPS_F;		// 帧头
    *(PAPS_data_frame_pt + 2) = EVENT_BOARD_ID;		// 从机标识
    *(PAPS_data_frame_pt + 3) = PAPSEntry.current_well_mode;	// 工作模式
    *(PAPS_data_frame_pt + 5) = PAPSEntry.STKLEV;			// 滑动平均次数
    *(PAPS_data_frame_pt + 6) = PAPSEntry.echo_1A_num;		// 1A回波点数
    *(PAPS_data_frame_pt + 7) = PAPSEntry.echo_1C_num;		// 1C回波点数

    // 回波数据滑动平均计算
    if (PAPSEntry.current_well_mode <= 6 && PAPSDataGenerate(&PAPSEntry))
    {
        *(PAPS_data_frame_pt + 1) = 2*(PAPSEntry.echo_1A_num + PAPSEntry.echo_1C_num) + 8;	// 帧长度
        *(PAPS_data_frame_pt + 4) = 1;		// 数据有效位
//        modeDataSendLen = *(PAPS_data_frame_pt + 1) + 1;  直接从地址取发送长度
    }
    else
    {
        *(PAPS_data_frame_pt + 1) = 7;		// 帧长度
        *(PAPS_data_frame_pt + 4) = 0;		// 数据有效位
//        modeDataSendLen = 8;
    }

    // CheckSum
    Uint16 check_sum = 0;
    int i;
    for (i=0;i<*(Uint16*)(PAPSTABLE_START + 1);++i)          // PAPSTABLE_START + 1存储着发送字数
    {
        check_sum += *PAPS_data_frame_pt++;
    }
    *PAPS_data_frame_pt = check_sum;
}
