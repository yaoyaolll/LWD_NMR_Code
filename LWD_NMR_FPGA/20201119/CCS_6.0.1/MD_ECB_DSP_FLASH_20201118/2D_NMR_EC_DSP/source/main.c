/*----------------------------头文件---------------------------------------------*/
#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include "MyHeaderFiles.h"

void main()
{	
	DINT;
	InitAll();   //初始化
   
	while(1)
	{
		if(SendTableFlag==SET)
		{
			CheckReadTable();
			SendTable();
			SendTableFlag = CLEAR;
		}     
		if(ScanModeFlag==SET)
		{
			CheckReadTable();
			ScanModeTop();         
			ScanModeFlag	=CLEAR;
		}      
		else if((ScaleModeFlag||HoleModeFlag)==SET)
		{
			CheckReadTable();
			ScaleHoleModeTop();     //刻度主函数 
			ScaleModeFlag	= CLEAR;
			HoleModeFlag	= CLEAR;
		}   
		else if(PulseAcqFlag==SET)
		{
			CheckReadTable();
			PulseTop();       //波形检测主函数
			PulseAcqFlag	= CLEAR;
		} 
     
		else if(PP6ModeFlag==SET)
		{
			CheckReadTable();
			PP6ModeTop();       //6频pp主函数
			PP6ModeFlag	= CLEAR;
		} 	
		else if(Oil3ModeFlag==SET)
		{
			CheckReadTable();
			Oil3ModeTop();       //pp_oil主函数
			Oil3ModeFlag	= CLEAR;
		}   
		else if(Gas6ModeFlag==SET)
		{
			CheckReadTable();
			Gas6ModeTop();       //pp_gas主函数
			Gas6ModeFlag	= CLEAR;      
		} 
		else if(SingleModeFlag==SET)
		{
			//if(DENum==DEMn) 
			//{
			//	DENum	= 0;
			//}
			CheckReadTable();
			DeCpmgTop();  
			SingleModeFlag	= CLEAR; 
		}
		else if (ST2DFlag==SET)
		{
			CheckReadTable();
			ST2DModeTop();
			ST2DFlag	= CLEAR;
		}
		else if (DT2DFlag==SET)
		{
			CheckReadTable();
			DT2DModeTop();
			DT2DFlag	= CLEAR;		
		}
		else if (MT2DFlag==SET)
		{
			CheckReadTable();
			MT2DModeTop();
			MT2DFlag	= CLEAR;		
		}
		else if (ST1T2Flag==SET)
		{
			CheckReadTable();
			ST1T2ModeTop();
			ST1T2Flag	= CLEAR;		
		}
		else if (ST12DFlag==SET)
		{
			CheckReadTable();
			ST1T2DModeTop();
			ST12DFlag	= CLEAR;		
		}
		else if (PPLOIL6FFlag==SET)
		{
			CheckReadTable();
			PPLOIL6FModeTop();
			PPLOIL6FFlag	= CLEAR;
		}
		else if(flag_pp3==SET)
		{
			CheckReadTable();
			freq3PP_top();
			flag_pp3	= CLEAR;
		}
		else if(FBW2FFlag==SET)
		{
			CheckReadTable();
			FBW2FModeTop();
			FBW2FFlag	= CLEAR;
		}
		else if(PPHOIL6FFlag==SET)
		{
			CheckReadTable();
			PPHOIL6FModeTop();
			PPHOIL6FFlag	= CLEAR;
		}
		else if(Gas6_2ModeFlag==SET)
		{
			CheckReadTable();
			Gas6_2ModeTop();       //pp_gas主函数
			Gas6_2ModeFlag	= CLEAR;
		}
		else if(PPHOIL6F_2Flag==SET)
		{
			CheckReadTable();
			PPHOIL6F_2ModeTop();
			PPHOIL6F_2Flag	= CLEAR;
		}
		else if(P3D6FFlag==SET)
		{
			CheckReadTable();
			P3D6FModeTop();
			P3D6FFlag	= CLEAR;
		}
		else if(HRT1T22FFlag==SET)
		{
			CheckReadTable();
			HRT1T22FModeTop();
			HRT1T22FFlag	= CLEAR;
		}
		else if (DFT1T2DFlag==SET)
		{
			CheckReadTable();
			DFT1T2DModeTop();
			DFT1T2DFlag	= CLEAR;
		}
	}
}
/*-----------------------------------------------------------------------------------------*/
/*---------------------------------END-----------------------------------------------------*/ 
/*-----------------------------------------------------------------------------------------*/  
