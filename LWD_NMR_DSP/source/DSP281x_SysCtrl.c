//###########################################################################
//
// FILE:   DSP281x_SysCtrl.c
//
// TITLE:  DSP281x Device System Control Initialization & Support Functions.
//
// DESCRIPTION:
//
//         Example initialization of system resources.
//
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================
//  1.00| 11 Sep 2003 | L.H. | Changes since previous version (v.58 Alpha)
//      |             |      | Additional comments added to explain the PLL
//      |             |      |    initialization.
//      |             |      | Changed the PLL initialization to take into
//      |             |      |    account bit definitions for the PLLCR register
//      |             |      | Removed DFT initialization - no longer needed 
//      |             |      |    as of Rev C F2810/12 silicon
//      |             |      | Split some operations into their own function
//      |             |      |    for better modularity
//      |             |      | Added pipeline flush after the Flash Init
//###########################################################################


#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File

// Functions that will be run from RAM need to be assigned to 
// a different section.  This section will then be mapped to a load and 
// run address using the linker cmd file.

#pragma CODE_SECTION(InitFlash, "secureRamFuncs");

//---------------------------------------------------------------------------
// InitSysCtrl: 
//---------------------------------------------------------------------------
// This function initializes the System Control registers to a known state.
// - Disables the watchdog
// - Set the PLLCR for proper SYSCLKOUT frequency 
// - Set the pre-scaler for the high and low frequency peripheral clocks
// - Enable the clocks to the peripherals

void InitSysCtrl(void)
{
  
// On F2812/F2810 TMX samples prior to rev C this initialization was 
// required.  For Rev C and after this is no longer required
/*
   EALLOW;
   DevEmuRegs.M0RAMDFT = 0x0300;
   DevEmuRegs.M1RAMDFT = 0x0300;
   DevEmuRegs.L0RAMDFT = 0x0300;
   DevEmuRegs.L1RAMDFT = 0x0300;
   DevEmuRegs.H0RAMDFT = 0x0300;
   EDIS;
*/  
   // Disable the watchdog        
	DisableDog();
   
   // Initialize the PLLCR to 0xA
	InitPll(2);   // OSCCLKIN*val/2=30MHz
	DisableDog();
   // Initialize the peripheral clocks
	InitPeripheralClocks();
   
   XintfRegs.XINTCNF2.bit.XTIMCLK = 0x0;  //XTIMCLK和SYSCLKOUT相同
   XintfRegs.XINTCNF2.bit.CLKMODE = 0x0;  //XCLKOUT和XTIMCLK相同
   XintfRegs.XINTCNF2.bit.CLKOFF = 0;

   //配置区域0的时序寄存器   
   XintfRegs.XTIMING0.bit.USEREADY = 0x0;   //不采样XREADY信号
   
   XintfRegs.XTIMING0.bit.XRDLEAD = 1;    //读前导时间最小
   XintfRegs.XTIMING0.bit.XRDACTIVE = 0;  //读有效时间最小
   XintfRegs.XTIMING0.bit.XRDTRAIL = 1;   //读结束时间
   
   XintfRegs.XTIMING0.bit.XWRLEAD = 1;    //写前导时间最小
   XintfRegs.XTIMING0.bit.XWRACTIVE = 3;  //写有效时间最小
   XintfRegs.XTIMING0.bit.XWRTRAIL = 3;   //写结束时间 
 
   XintfRegs.XTIMING0.bit.X2TIMING = 0;	  //前导，有效，结束基本时间和XTIMCLK比例为1：1

   //配置区域1的时序寄存器   
   XintfRegs.XTIMING1.bit.USEREADY = 0x0;   //不采样XREADY信号
   
   XintfRegs.XTIMING1.bit.XRDLEAD = 1;    //读前导时间最小
   XintfRegs.XTIMING1.bit.XRDACTIVE = 0;  //读有效时间最小
   XintfRegs.XTIMING1.bit.XRDTRAIL = 1;   //读结束时间
   
   XintfRegs.XTIMING1.bit.XWRLEAD = 1;    //写前导时间最小
   XintfRegs.XTIMING1.bit.XWRACTIVE = 3;  //写有效时间最小
   XintfRegs.XTIMING1.bit.XWRTRAIL = 3;   //写结束时间 
 
   XintfRegs.XTIMING1.bit.X2TIMING = 0;	  //前导，有效，结束基本时间和XTIMCLK比例为1：1   
   
   //配置区域2的时序寄存器   
   XintfRegs.XTIMING2.bit.USEREADY = 0x0;   //不采样XREADY信号
   
   XintfRegs.XTIMING2.bit.XRDLEAD = 1;    //读前导时间最小
   XintfRegs.XTIMING2.bit.XRDACTIVE = 0;  //读有效时间最小
   XintfRegs.XTIMING2.bit.XRDTRAIL = 1;   //读结束时间
   
   XintfRegs.XTIMING2.bit.XWRLEAD = 1;    //写前导时间最小
   XintfRegs.XTIMING2.bit.XWRACTIVE = 3;  //写有效时间最小
   XintfRegs.XTIMING2.bit.XWRTRAIL = 3;   //写结束时间 
 
   XintfRegs.XTIMING2.bit.X2TIMING = 0;	  //前导，有效，结束基本时间和XTIMCLK比例为1：1
    // Zone 6------------------------------------
    // When using ready, ACTIVE must be 1 or greater
    // Lead must always be 1 or greater
    // Zone write timing
    XintfRegs.XTIMING6.bit.XWRLEAD = 1;
    XintfRegs.XTIMING6.bit.XWRACTIVE = 0;
    XintfRegs.XTIMING6.bit.XWRTRAIL = 1;
    // Zone read timing
    XintfRegs.XTIMING6.bit.XRDLEAD = 1;
    XintfRegs.XTIMING6.bit.XRDACTIVE = 0;
    XintfRegs.XTIMING6.bit.XRDTRAIL = 1;
    
    // double all Zone read/write lead/active/trail timing 
    XintfRegs.XTIMING6.bit.X2TIMING = 0;

    // Zone will not sample XREADY signal 
    XintfRegs.XTIMING6.bit.USEREADY = 0;


    // Zone 7------------------------------------
    // When using ready, ACTIVE must be 1 or greater
    // Lead must always be 1 or greater
    // Zone write timing
    XintfRegs.XTIMING7.bit.XWRLEAD = 1;
    XintfRegs.XTIMING7.bit.XWRACTIVE = 0;
    XintfRegs.XTIMING7.bit.XWRTRAIL = 1;
    // Zone read timing
    XintfRegs.XTIMING7.bit.XRDLEAD = 1;
    XintfRegs.XTIMING7.bit.XRDACTIVE = 0;
    XintfRegs.XTIMING7.bit.XRDTRAIL = 1;
    
    // double all Zone read/write lead/active/trail timing 
    XintfRegs.XTIMING7.bit.X2TIMING = 0;

    // Zone will not sample XREADY signal 
    XintfRegs.XTIMING7.bit.USEREADY = 0;
    

}


//---------------------------------------------------------------------------
// Example: InitFlash: 
//---------------------------------------------------------------------------
// This function initializes the Flash Control registers

//                   CAUTION 
// This function MUST be executed out of RAM. Executing it
// out of OTP/Flash will yield unpredictable results

//void InitFlash(void)
//{
//   EALLOW;
//   //Enable Flash Pipeline mode to improve performance
//   //of code executed from Flash.
//   FlashRegs.FOPT.bit.ENPIPE = 1;
//
//   //                CAUTION
//   //Minimum waitstates required for the flash operating
//   //at a given CPU rate must be characterized by TI.
//   //Refer to the datasheet for the latest information.
//
//   //Set the Random Waitstate for the Flash
//   FlashRegs.FBANKWAIT.bit.RANDWAIT = 5;
//
//   //Set the Paged Waitstate for the Flash
//   FlashRegs.FBANKWAIT.bit.PAGEWAIT = 5;
//
//   //                CAUTION
//   //Minimum cycles required to move between power states
//   //at a given CPU rate must be characterized by TI.
//   //Refer to the datasheet for the latest information.
//
//   //For now use the default count
//   //Set number of cycles to transition from sleep to standby
//   FlashRegs.FSTDBYWAIT.bit.STDBYWAIT = 0x01FF;
//
//   //Set number of cycles to transition from standby to active
//   FlashRegs.FACTIVEWAIT.bit.ACTIVEWAIT = 0x01FF;
//   EDIS;
//
//   //Force a pipeline flush to ensure that the write to
//   //the last register configured occurs before returning.
//
//   asm(" RPT #7 || NOP");
//}
void InitFlash(void)
{
    asm(" EALLOW"); // Enable EALLOW protected register access
    FlashRegs.FPWR.bit.PWR = 3; // Pump and bank set to active mode
    FlashRegs.FSTATUS.bit.V3STAT = 1; // Clear the 3VSTAT bit
    FlashRegs.FSTDBYWAIT.bit.STDBYWAIT = 0x01FF; // Sleep to standby transition cycles
    FlashRegs.FACTIVEWAIT.bit.ACTIVEWAIT = 0x01FF; // Standby to active transition cycles
    FlashRegs.FBANKWAIT.bit.RANDWAIT = 5; // Random access waitstates
    FlashRegs.FBANKWAIT.bit.PAGEWAIT = 5; // Paged access waitstates
    FlashRegs.FOTPWAIT.bit.OTPWAIT = 5; // Random access waitstates
    FlashRegs.FOPT.bit.ENPIPE = 1; // Enable the flash pipeline
    asm(" EDIS"); // Disable EALLOW protected register access
    /*** Force a complete pipeline flush to ensure that the write to the last register
    configured occurs before returning. Safest thing is to wait 8 full cycles. ***/
    asm(" RPT #7 || NOP");
}


//---------------------------------------------------------------------------
// Example: KickDog: 
//---------------------------------------------------------------------------
// This function resets the watchdog timer.
// Enable this function for using KickDog in the application 

void KickDog(void)
{
    EALLOW;
    SysCtrlRegs.WDKEY = 0x0055;
    SysCtrlRegs.WDKEY = 0x00AA;
    EDIS;
}

//---------------------------------------------------------------------------
// Example: DisableDog: 
//---------------------------------------------------------------------------
// This function disables the watchdog timer.

void DisableDog(void)
{
    EALLOW;
    SysCtrlRegs.WDCR= 0x0068;
    EDIS;
}

//---------------------------------------------------------------------------
// Example: InitPll: 
//---------------------------------------------------------------------------
// This function initializes the PLLCR register.

void InitPll(Uint16 val)
{
   volatile Uint16 iVol;   
   
   if (SysCtrlRegs.PLLCR.bit.DIV != val)
   {
   
      EALLOW;
      SysCtrlRegs.PLLCR.bit.DIV = val;
      EDIS;
   
   // Optional: Wait for PLL to lock.
   // During this time the CPU will switch to OSCCLK/2 until the PLL is 
   // stable.  Once the PLL is stable the CPU will switch to the new PLL value. 
   //
   // This switch time is 131072 CLKIN cycles as of Rev C silicon.  
   //   
   // Code is not required to sit and wait for the PLL to lock.   
   // However, if the code does anything that is timing critical, 
   // and requires the correct clock be locked, then it is best to 
   // wait until this switching has completed.  
   
   // If this function is run from waitstated memory, then the loop count can
   // be reduced as long as the minimum switch time is still met. 

   // iVol is volatile so the compiler will not optimize this loop out
   //
   // The watchdog should be disabled before this loop, or fed within 
   // the loop.   
   
      DisableDog();
   
   // Wait lock cycles.  
   // Note,  This loop is tuned to 0-waitstate RAM memory.  If this
   // function is run from wait-stated memory such as Flash or XINTF,
   // then the number of times through the loop can be reduced 
   // accordingly. 
      for(iVol= 0; iVol< ( (131072/2)/12 ); iVol++)
      {
   
      }
   }
}

//--------------------------------------------------------------------------
// Example: InitPeripheralClocks: 
//---------------------------------------------------------------------------
// This function initializes the clocks to the peripheral modules.
// First the high and low clock prescalers are set
// Second the clocks are enabled to each peripheral.
// To reduce power, leave clocks to unused peripherals disabled
// Note: If a peripherals clock is not enabled then you cannot 
// read or write to the registers for that peripheral 

void InitPeripheralClocks(void)
{
   EALLOW;
// HISPCP/LOSPCP prescale register settings, normally it will be set to default values
   SysCtrlRegs.HISPCP.all = 0x0001;
   SysCtrlRegs.LOSPCP.all = 0x0000;
   	
// Peripheral clock enables set for the selected peripherals.   
   SysCtrlRegs.PCLKCR.bit.EVAENCLK=0;
   SysCtrlRegs.PCLKCR.bit.EVBENCLK=0;
   SysCtrlRegs.PCLKCR.bit.SCIAENCLK=1;
   SysCtrlRegs.PCLKCR.bit.SCIBENCLK=0;
   SysCtrlRegs.PCLKCR.bit.MCBSPENCLK=0;
   SysCtrlRegs.PCLKCR.bit.SPIENCLK=0;
   SysCtrlRegs.PCLKCR.bit.ECANENCLK=0;
   SysCtrlRegs.PCLKCR.bit.ADCENCLK=0;
   EDIS;
}


#define STATUS_FAIL          0
#define STATUS_SUCCESS       1

Uint16 CsmUnlock()
{
    volatile Uint16 temp;

    // Load the key registers with the current password. The 0xFFFF's are dummy
	// passwords.  User should replace them with the correct password for the DSP.

    EALLOW;
    CsmRegs.KEY0 = 0xFFFF;
    CsmRegs.KEY1 = 0xFFFF;
    CsmRegs.KEY2 = 0xFFFF;
    CsmRegs.KEY3 = 0xFFFF;
    CsmRegs.KEY4 = 0xFFFF;
    CsmRegs.KEY5 = 0xFFFF;
    CsmRegs.KEY6 = 0xFFFF;
    CsmRegs.KEY7 = 0xFFFF;
    EDIS;

    // Perform a dummy read of the password locations
    // if they match the key values, the CSM will unlock

    temp = CsmPwl.PSWD0;
    temp = CsmPwl.PSWD1;
    temp = CsmPwl.PSWD2;
    temp = CsmPwl.PSWD3;
    temp = CsmPwl.PSWD4;
    temp = CsmPwl.PSWD5;
    temp = CsmPwl.PSWD6;
    temp = CsmPwl.PSWD7;

    // If the CSM unlocked, return succes, otherwise return
    // failure.
    if (CsmRegs.CSMSCR.bit.SECURE == 0) return STATUS_SUCCESS;
    else return STATUS_FAIL;

}	
//===========================================================================
// No more.
//===========================================================================
