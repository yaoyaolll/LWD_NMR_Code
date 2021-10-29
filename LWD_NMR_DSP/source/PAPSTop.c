/*
 * @Descripttion: ʵ��PAPS�Դ�����ۼ�ƽ�����ܣ��˹���ֻ�ڲ⾮ģʽ������
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

// ����ƽ���㷨
int PAPSDataGenerate(PAPSEntry_t* PAPSEntryPt)
{
    // ���FIFO��䳤���Ƿ�Ϊ����Ҫ��
    Uint16 FIFO_len = PAPSEntryPt->PAPSFIFO_end - PAPSEntryPt->PAPSFIFO_start;
    if (FIFO_len != PAPSEntryPt->STKLEV)
        return 0;

    Uint16 FIFO_element_size = 2 * (PAPSEntryPt->echo_1A_num + PAPSEntryPt->echo_1C_num);
    Uint16* PAPS_data_storge_pt = (Uint16*)(PAPS_STORAGE_DATA_ADDR);      // PAPS���ݴ洢��ַ
    int i = 0;
    for (i=0;i<FIFO_element_size;++i)
    {
        int j, k;
        float sum = 0.0f;
        for (j=PAPSEntryPt->PAPSFIFO_start, k=1; j<PAPSEntryPt->PAPSFIFO_end; ++j, ++k) 
        {
            int index = j & PAPS_FIFO_MASK;
            Uint32 PAPS_index_addr = PAPS_FIFO_ADDR + index*FIFO_element_size + i;  // ���ݵ�ĵ�ַ
            Uint16 PAPS_data = *((Uint16 *)PAPS_index_addr);
            // ����ƽ���㷨
            if (k==1 || k == PAPSEntryPt->STKLEV)    // �׻���β
                sum += PAPS_data;
            else if (k&1 == 0)      // even
                sum -= (2*PAPS_data);
            else
                sum += (2*PAPS_data);
        }
        *PAPS_data_storge_pt++ = (Uint16)(sum / (2*(PAPSEntryPt->STKLEV - 1)));
    }

    // ��дPAPS�����ϴ�֡
    
    return 1;
}

// ��ÿ��ģʽ��ĩβ��ýṹ�壬���ô˺�����1A��1C�ز���������FIFO
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
        
    // ��FIFO����ЧԪ�ظ���ά���ڵ��Ӵ���
    Uint16 FIFO_element_size = 2 * (PAPSEntryPt->echo_1A_num + PAPSEntryPt->echo_1C_num);
    // ����ַ
    Uint16* fifo_base_pt = (Uint16*)(PAPS_FIFO_ADDR + FIFO_element_size*(PAPSEntryPt->PAPSFIFO_end & PAPS_FIFO_MASK));
    if (PAPSEntryPt->PAPSFIFO_end - PAPSEntryPt->PAPSFIFO_start >= PAPSEntryPt->STKLEV && PAPSEntryPt->STKLEV != 0)
    {
        PAPSEntryPt->PAPSFIFO_start++;
    }
    PAPSEntryPt->PAPSFIFO_end++;

    // ���ز���������FIFO
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

        if (PAPSEntryPt->current_well_mode == 0x0003)       // PPDIF������1C
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

// PAPS�������������ذ����¼�����Ҫ����ƽ������ʱ����
void PAPSTop(void)
{
    Uint16* PAPS_data_frame_pt = (Uint16*)(PAPSTABLE_START);
    *(PAPS_data_frame_pt + 0) = REPLY_PAPS_F;		// ֡ͷ
    *(PAPS_data_frame_pt + 2) = EVENT_BOARD_ID;		// �ӻ���ʶ
    *(PAPS_data_frame_pt + 3) = PAPSEntry.current_well_mode;	// ����ģʽ
    *(PAPS_data_frame_pt + 5) = PAPSEntry.STKLEV;			// ����ƽ������
    *(PAPS_data_frame_pt + 6) = PAPSEntry.echo_1A_num;		// 1A�ز�����
    *(PAPS_data_frame_pt + 7) = PAPSEntry.echo_1C_num;		// 1C�ز�����

    // �ز����ݻ���ƽ������
    if (PAPSEntry.current_well_mode <= 6 && PAPSDataGenerate(&PAPSEntry))
    {
        *(PAPS_data_frame_pt + 1) = 2*(PAPSEntry.echo_1A_num + PAPSEntry.echo_1C_num) + 8;	// ֡����
        *(PAPS_data_frame_pt + 4) = 1;		// ������Чλ
        modeDataSendLen = *(PAPS_data_frame_pt + 1) + 1;
    }
    else
    {
        *(PAPS_data_frame_pt + 1) = 7;		// ֡����
        *(PAPS_data_frame_pt + 4) = 0;		// ������Чλ
        modeDataSendLen = 8;
    }

    // CheckSum
    Uint16 check_sum = 0;
    int i;
    for (i=0;i<*(Uint16*)(PAPSTABLE_START + 1);++i)          // PAPSTABLE_START + 1�洢�ŷ�������
    {
        check_sum += *PAPS_data_frame_pt++;
    }
    *PAPS_data_frame_pt = check_sum;
}
