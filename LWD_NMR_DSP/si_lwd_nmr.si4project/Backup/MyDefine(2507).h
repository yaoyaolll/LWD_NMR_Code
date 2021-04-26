//Address macro definations
#define TABLE_START			0x8000    //������0x8000+78
#define WORK_MODE_ADDR		0x8001
#define FREQ_STR_ADDR		0x8002
#define FREQ_SEL_WORDS_ADDR	0x800A
#define WIDTH_STR_ADDR		0x800C
#define STEP_FREQ_ADDR		0x8015
#define SIGNAL_ACQ_PERIOD_NUM_ADDR		0x8016
#define SIGNAL_ACQ_FREQ_TIMES_ADDR		0x8017
#define NOISE_ACQ_TIME_ADDR	0x8018
#define NOISE_ACQ_FREQ_ADDR	0x8019
#define MAT_PARA_STR_ADDR	0x801C
#define SCALE_TE_ADDR		0x801F

#define DDS_FREQ_ADDR		0x8062 //gai

#define SCANTABLE_START			0x120000		//ɨƵ�ϴ����ݱ��׵�ַ
#define SCALETABLE_START		0x120000		//�̶����ݱ��׵�ַ
#define HOLETABLE_START			0x120000		//��϶�����ݱ��׵�ַ
#define PLUSETABLE_START		0x120000		//�����źŲ��βɼ������׵�ַ
#define DECPMGTABLE_START		0x120000		//DeCpmg���׵�ַ

// mode for LWD NMR
#define PPM_TABLE_START         0x120000
#define PPDIF_TABLE_START		0x120000
#define PPT1_TABLE_START        0x120000
#define PPOFTW_TABLE_START      0x120000
#define PPShort_TABLE_START     0x120000

#define MINITABLE_START		0x008100		//the start address of mini scan data store zone

//Parameter macro definations
#define USER_DISABLE		0x0002
#define USER_ENABLE			0x0001
#define SET					0x0001
#define CLEAR				0x0000

#define POSITIVE			0x0001
#define NEGATIVE			0x0000

#define TABLE_TOTAL_NUM     83
#define BAND_NUM			9

/*
#define RELAY_CTR_1			0x000D
#define RELAY_CTR_2			0x000E
#define RELAY_CTR_3			0x0005
#define RELAY_CTR_4			0x0001
#define RELAY_CTR_5			0x0002
#define RELAY_CTR_6			0x0000
*/

#define RELAY_CTR_1 0x0029
#define RELAY_CTR_2 0x0025
#define RELAY_CTR_3 0x0009
#define RELAY_CTR_4 0x0030
#define RELAY_CTR_5 0x0018
#define RELAY_CTR_6 0x0008
#define RELAY_CTR_7 0x0002
#define RELAY_CTR_8 0x0000


#define SHIFT				10           //��ʽת��
#define NOISE_STRIP			8           //������ȥ����

#define SHAKE_NUM			4			//�������
#define IN_BRI_WIDTH		100			//��������
#define OUT_BRI_WIDTH		200			//��������
#define SHORT_DUMP_TIME		100			//��й��ʱ��
#define LONG_DUMP_TIME		2000		//��й��ʱ��
#define WAIT_DUMP_TIME		280			//��й�ż��ʱ��

#define PLUSE_STRIP  		10           //������ȥ����

#define SOFT_DUMP_TIME		8000
#define TE_ADD				1
#define T_N					10   //90���180��֮����ٵ�������
#define FPGA_COUNT			100      //fpga��Ӧ1us����ֵ��10ns��λ
#define HV_ON				0x0001
#define HV_OFF				0x0002

#define	P_PLUSE_T1			120
#define	P_PLUSE_T2			603		
#define	P_PLUSE_T3			120
#define	P_PLUSE_T4			201

#define	SD_SACQ_T1			120	
#define	SD_SACQ_T2			613	

#define SCALE_REPAIR1		813    //scale״̬�������ȶ�����λ�Ȳ�����ʱ�����ֵ��10ns��λ��
#define SCALE_REPAIR2		920    //scale״̬�������ȶ�����λ�Ȳ�����ʱ�����ֵ��10ns��λ��
#define SWITCH_REPAIR		200    //ADG1404�ȶ�ʱ�����ֵ��10ns��λ��
#define PP3_REPAIR1			3
#define PPoil_REPAIR1		4
#define PPoil_REPAIR2		2
#define PPoil_REPAIR3		9
#define PPgas_REPAIR1		5
#define PPgas_REPAIR2		10
#define PPgas_REPAIR3		9
#define PP6_REPAIR1			3		//��ʱ����Ҫ������ʵ�����
#define PP6_REPAIR2			9

#define T2D_REPAIR1			11		//this parameters should be adjusted
#define T2D_REPAIR2			4		//this parameters should be adjusted
#define T1T2_REPAIR1		10		//this parameters should be adjusted
#define T1T2_REPAIR2		4		//this parameters should be adjusted
#define T12D_REPAIR1		10		//this parameters should be adjusted
#define T12D_REPAIR2		4		//this parameters should be adjusted

#define MINI_TEST			53		//the time of mini scan is 7.6ms
#define FPGA_BC				5

#define OIL3_TE_1AB			21
#define OIL3_TE_2AB			6
#define OIL3_TE_3A			15 
#define OIL3_NE_1AB			238
#define OIL3_NE_2AB			833
#define OIL3_NE_3A			333

#define GAS6_TE_123456A		6
#define GAS6_TE_1234B		6
#define GAS6_NE_1234AB56A	700

#define Gas6_2_NE_1234AB56A 700
#define Gas6_2_TE_123456A 	6
#define Gas6_2_TE_1234B 	6

#define PPHOIL6F_TE_1B 100
#define PPHOIL6F_TE_2B 50
#define PPHOIL6F_TE_3B 70
#define PPHOIL6F_TE_4B 8
#define PPHOIL6F_TE_5B 36
#define PPHOIL6F_TE_6B 12

#define PPHOIL6FNe1B 	8
#define PPHOIL6FNe2B 	16
#define PPHOIL6FNe3B 	11
#define PPHOIL6FNe4B 	220
#define PPHOIL6FNe5B 	33
#define PPHOIL6FNe6B 	100

#define PPHOIL6F_2_TE_1B 100
#define PPHOIL6F_2_TE_2B 50
#define PPHOIL6F_2_TE_3B 70
#define PPHOIL6F_2_TE_4B 8
#define PPHOIL6F_2_TE_5B 36
#define PPHOIL6F_2_TE_6B 15

#define PPHOIL6F_2Ne1B 	8
#define PPHOIL6F_2Ne2B 	16
#define PPHOIL6F_2Ne3B 	11
#define PPHOIL6F_2Ne4B 	250
#define PPHOIL6F_2Ne5B 	33
#define PPHOIL6F_2Ne6B 	100

#define DFT1T2D_NREPT_A8B8 		2
#define DFT1T2D_NREPT_A9B9 		2
#define DFT1T2D_NREPT_A10B10 	2


//Interface with FPGA macro definations
//�ⲿ��ַ����2��0x080000---0x100000��
#define  DSP_NS_CTRL_EN		*(Uint16 *) 0x80004       //����or�źſ���ѡ��ѡ����������ͨ����
#define  DSP_NS_CTRL_DIS	*(Uint16 *) 0x80005      //ѡ���ź�����ͨ��           

#define  SCAN_RST_EN		*(Uint16 *) 0x80008       //ɨƵ��λ�������ظ���Ч��
#define  SCAN_RST_DIS		*(Uint16 *) 0x80009   
#define  SCAN_START_EN		*(Uint16 *) 0x8000A       //ɨƵ����
#define  SCAN_START_DIS		*(Uint16 *) 0x8000B 

#define  NOISE_RST_EN		*(Uint16 *) 0x8000C       //������λ�������ظ���Ч��
#define  NOISE_RST_DIS		*(Uint16 *) 0x8000D
#define  NOISE_START_EN		*(Uint16 *) 0x8000E       //���������������ظ���Ч��
#define  NOISE_START_DIS	*(Uint16 *) 0x8000F

#define  DDS_CONFDATA		*(Uint16 *) 0x80015         //ddsƵ����
#define  DDS_DATALOAD_EN	*(Uint16 *) 0x80016    //ddsƵ����װ�أ������ظ���Ч��
#define  DDS_DATALOAD_DIS	*(Uint16 *) 0x80017   
#define  DDS_DATACHOICE_EN	*(Uint16 *) 0x80018   //ddsƵ���ָߵ�λ����λ��
#define  DDS_DATACHOICE_DIS	*(Uint16 *) 0x80019   //��λ

#define  CAL_DIVDATA		*(Uint16 *) 0x8001A          //cal��Ƶ�֣�����Ƶ����ת��
#define  CAL_DATALOAD_EN	*(Uint16 *) 0x8001B     //cal��Ƶ��װ�أ������ظ���Ч��
#define  CAL_DATALOAD_DIS	*(Uint16 *) 0x8001C

#define  NRAM_RST_EN		*(Uint16 *) 0x8001D         //noise_ram����λ�������ظ���Ч��
#define  NRAM_RST_DIS		*(Uint16 *) 0x8001E 
#define  NRAM_RD_EN			*(Uint16 *) 0x8001F          //noise_ram��ʹ�ܣ�����Ч��
#define  NRAM_RD_DIS		*(Uint16 *) 0x80020
/*
#define  NRAM_RST_EN  *(Uint16 *) 0x2000         //noise_ram����λ�������ظ���Ч��
#define  NRAM_RST_DIS *(Uint16 *) 0x2001
#define  NRAM_RD_EN  *(Uint16 *) 0x2009          //noise_ram��ʹ�ܣ�����Ч��
#define  NRAM_RD_DIS *(Uint16 *) 0x2008 
*/

#define  NRAM_LOAD_EN		*(Uint16 *) 0x80021        //noise��ؼĴ���װ�أ������ظ���Ч��
#define  NRAM_LOAD_DIS		*(Uint16 *) 0x80022 
#define  NRAM_ACQNUM		*(Uint16 *) 0x80023         //noise�ɼ����ݸ���
#define  NRAM_DIVNUM		*(Uint16 *) 0x80024          //noise�ɼ�ʱ�ӷ�Ƶ����10λ���ݣ����ո�5λ�͵�5λ��Ƶ��

#define  SIGNAL_ACQNUM		*(Uint16 *) 0x80025        //�źŲɼ�����
#define  SIGNAL_PERIODNUM	*(Uint16 *) 0x80026     //�ź����ڲ�����
//#define  SIGNAL_PERIODNUM *(Uint16 *) 0x2011     //�ź����ڲ�����
#define  SIGNAL_LOAD_EN		*(Uint16 *) 0x80027       //signal��ؼĴ���װ�أ������ظ���Ч��
#define  SIGNAL_LOAD_DIS	*(Uint16 *) 0x80028

#define  DATACHOICE			*(Uint16 *) 0x80029                //�ӷ������16λͨ��ѡ�� 
//#define  DATACHOICE *(Uint16 *) 0x2010  

#define  STATE1MS_RST_EN	*(Uint16 *) 0x80031         //1ms״̬����λ
#define  STATE1MS_RST_DIS	*(Uint16 *) 0x80032         
#define  STATE1MS_START_DIS	*(Uint16 *) 0x80033         //1ms״̬������������ź����ѡ��
#define  STATE1MS_START_EN	*(Uint16 *) 0x80034
#define  STATE1MS_LOAD_DIS	*(Uint16 *) 0x80035         //1ms״̬��LOAD�ź�����
#define  STATE1MS_LOAD_EN	*(Uint16 *) 0x80036          //1ms״̬��LOAD�ź���Ч
#define  STATE1MS_CHOICE	*(Uint16 *) 0x80037         //1ms״̬������ѡ��
#define  STATE1MS_DATA		*(Uint16 *) 0x80038        //1ms״̬������

#define  RELAY_ON_CLOSE		*(Uint16 *) 0x80040          //�̵�����8λ�Ǳպϣ���8λ�Ͽ�

#define  CTRL_CHOICE		*(Uint16 *) 0x80060          //����ͨ·ѡ��Ϊ0ɨƵ��������Ϊ1�̶ȣ�

#define  SCALE_RST_EN		*(Uint16 *) 0x80061        //�̶ȸ�λ
#define  SCALE_RST_DIS		*(Uint16 *) 0x80062       
#define  SCALE_START_EN		*(Uint16 *) 0x80063      //�̶�����
#define  SCALE_START_DIS	*(Uint16 *) 0x80064       
#define  SCALE_LOAD_EN		*(Uint16 *) 0x80065       //�̶�����װ��
#define  SCALE_LOAD_DIS		*(Uint16 *) 0x80066 
#define  SCALE_DATA			*(Uint16 *) 0x8006D         //scale״̬������
#define  SCALE_CHOICE		*(Uint16 *) 0x8006E         //scale״̬������ѡ��

#define  POSI_NEGE_EN		*(Uint16 *) 0x8006B        //�����༤��ѡ��
#define  POSI_NEGE_DIS		*(Uint16 *) 0x8006C

#define  BRIDGE_LOAD_EN		*(Uint16 *) 0x80067      //����������װ��
#define  BRIDGE_LOAD_DIS	*(Uint16 *) 0x80068
#define  BRIDGE_DATA		*(Uint16 *) 0x8006F         //bridge�������  
    
#define  HALF_DATA			*(Uint16 *) 0x80070         //�뼤������

#define  DUMP_LOAD_EN		*(Uint16 *) 0x80069        //й������
#define  DUMP_LOAD_DIS		*(Uint16 *) 0x8006A 
#define  DUMP_CHOICE		*(Uint16 *) 0x80071         //dump����ѡ��
#define  DUMP_DATA			*(Uint16 *) 0x80072         //dump����   
    
#define  SCALE_DDSDIV		*(Uint16 *) 0x80073         //scaledds��Ƶ����

#define	 SD_SACQ_CHOICE		*(Uint16 *)	0x80074			
#define	 SD_SACQ_DATA		*(Uint16 *)	0x80075			
#define	 SD_SACQ_LOAD_EN	*(Uint16 *)	0x80076			
#define	 SD_SACQ_LOAD_DIS	*(Uint16 *)	0x80077

#define  PLUSE_NOISE_EN		*(Uint16 *) 0x80080        //pluse_noise����ѡ��
#define  PLUSE_NOISE_DIS	*(Uint16 *) 0x80081
   
#define  PLUSE_SCALE_EN		*(Uint16 *) 0x80082        //pluse_scale����й�ſ���ѡ��
#define  PLUSE_SCALE_DIS	*(Uint16 *) 0x80083 

#define  PLUSE_START_EN		*(Uint16 *) 0x80084        //pluse��������
#define  PLUSE_START_DIS	*(Uint16 *) 0x80085
#define  PLUSE_RST_EN		*(Uint16 *) 0x80086        //pluse������λ
#define  PLUSE_RST_DIS		*(Uint16 *) 0x80087
#define  PLUSE_LOAD_EN		*(Uint16 *) 0x80088        //pluse��������װ��
#define  PLUSE_LOAD_DIS		*(Uint16 *) 0x80089
#define  PLUSE_LCHOICE_EN	*(Uint16 *) 0x8008A        //pluse��������װ��ѡ��
#define  PLUSE_LCHOICE_DIS	*(Uint16 *) 0x8008B
#define  PLUSE_DATA			*(Uint16 *) 0x8008C        //pluse��������

#define  TIMER_DATA			*(Uint16 *) 0x80090        //��ʱ������
#define  TIMER_START		*(Uint16 *) 0x80091        //��ʱ������
#define  TIMER_STOP			*(Uint16 *) 0x80092

#define  SCAN_CHOICE_EN		*(Uint16 *) 0x80093        //ɨƵ״̬������ѡ��
#define  SCAN_CHOICE_DIS	*(Uint16 *) 0x80094        
#define  SCAN_LOAD_EN		*(Uint16 *) 0x80095        //ɨƵ״̬������װ��
#define  SCAN_LOAD_DIS		*(Uint16 *) 0x80096        
#define  SCAN_DATA			*(Uint16 *) 0x80097        //ɨƵ״̬������

#define  NSTATE_CHOICE_EN	*(Uint16 *) 0x80098        //noise״̬������ѡ��
#define  NSTATE_CHOICE_DIS	*(Uint16 *) 0x80099       
#define  NSTATE_LOAD_EN		*(Uint16 *) 0x8009A        //noise״̬������װ��
#define  NSTATE_LOAD_DIS	*(Uint16 *) 0x8009B      
#define  NSTATE_DATA		*(Uint16 *) 0x8009C        //noise״̬������

#define  ACQCLK_EN			*(Uint16 *) 0x8009D        
#define  ACQCLK_DIS			*(Uint16 *) 0x8009E

#define  K1_EN				*(Uint16 *) 0x800A0        
#define  K1_DIS				*(Uint16 *) 0x800A1 
#define  K2_EN				*(Uint16 *) 0x800A2        
#define  K2_DIS				*(Uint16 *) 0x800A3

#define  PD_PLUSE_CHOICE	*(Uint16 *) 0x800A4 
#define  PD_PLUSE_DATA		*(Uint16 *) 0x800A5
#define  PD_PLUSE_LOAD_EN	*(Uint16 *) 0x800A6        
#define  PD_PLUSE_LOAD_DIS	*(Uint16 *) 0x800A7

#define  DUMP_SUSTAIN_EN	*(Uint16 *) 0x800A8
#define  DUMP_SUSTAIN_DIS	*(Uint16 *) 0x800A9
#define  DUMP_SUSTAIN_DATA  *(Uint16 *) 0x800AA

#define  INV_TURN_EN		*(Uint16 *) 0x800AB
#define  INV_TURN_DIS		*(Uint16 *) 0x800AC

#define  READ_NOISE			*(Uint16 *) 0x81000           
#define  RDDATA				*(Uint16 *) 0x82000 

#define MODE_CHOICE    		11
/*
#define  READ_NOISE *(Uint16 *) 0x2100           
#define  RDDATA *(Uint16 *) 0x2200
*/

// ���ذ��·�����֡֡ͷ���壬F means Frame
#define DATA_INQUIRE_F      0x999A  // ��ѯ״ָ̬��
#define DATA_DOWN_TABLE_F   0x1328  // ����������ָ��
#define DATA_UP_TABLE_F     0x1428  // �������ϴ�ָ��
#define DATA_OPERATION_F    0x999B  // ��������ָ��
#define DATA_CASING_F       0x999C  // �׹ܼ��ָ��
#define DATA_UP_MODE_F      0x999D  // ģʽ�����ϴ�ָ��
#define DATA_MODE_CONFIRM_F 0x999E  // ģʽ����ȷ��ָ��
#define DATA_K1K2_EN_F      0x9922  // ���ܶ̽�����ָ��
#define DATA_K1K2_DIS_F     0x9923  // ���ܶ̽ڶϿ�ָ��
#define DATA_HVState_F      0x9924  // ���ܶ̽��ж�ָ��
#define DATA_SysCheck_F     0x9901  // ϵͳ�Լ��ָ��

// �¼���ظ�֡֡ͷ���壬F means Frame
#define REPLY_STATE_F       0x9991  // ��ѯ״ָ̬��ظ�
#define REPLY_DOWN_TABLE_F  0x9992  // ����������ָ��ظ�
#define REPLY_UP_TABLE_F    0x9993  // �������ϴ�ָ��ظ�
#define REPLY_CASING_F      0x9994  // �׹ܼ������
#define REPLY_MODE_DATA_F   0x9995  // �̶�/�⾮ģʽ���ݻظ�
#define REPLY_CASING_ERR_F  0x9996  // �׹ܼ���쳣֡
