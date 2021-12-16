/*
//###########################################################################
//
// FILE:    F2812_EzDSP_RAM_lnk.cmd
//
// TITLE:   Linker Command File For F2812 eZdsp examples that run out of RAM
//          This linker file assumes the user is booting up in Jump to H0 mode

//
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================
//  1.00| 11 Sep 2003 | L.H. | Changes since previous version (v.58 Alpha)
//      |             |      | Added BEGIN section to the start of H0
//      |             |      | Removed .bss, .const and .sysmem
//      |             |      |    These are for a small memory model.  All examples
//      |             |      |    use the large model.
//      |             |      | Added .esysmem section
//      |             |      | Changed ramfuncs section to load and run from RAM
//      |             |      |    (previously this was type DSECT)
//      |             |      | Moved peripheral register files to DSP28_Headers_BIOS.cmd
//      |             |      |    and DSP28_Headers_nonBIOS.cmd
//      |             |      | Added CSM_RSVD memory section in FLASHA - this region
//      |             |      |    should be programmed with all 0x0000 when using the CSM
// -----|-------------|------|-----------------------------------------------
//###########################################################################
*/

/* ======================================================
// For Code Composer Studio V2.2 and later
// ---------------------------------------
// In addition to this memory linker command file, 
// add the header linker command file directly to the project. 
// The header linker command file is required to link the
// peripheral structures to the proper locations within 
// the memory map.
//
// The header linker files are found in <base>\DSP281x_Headers\cmd
//   
// For BIOS applications add:      DSP281x_Headers_nonBIOS.cmd
// For nonBIOS applications add:   DSP281x_Headers_nonBIOS.cmd    
========================================================= */

/* ======================================================
// For Code Composer Studio prior to V2.2
// --------------------------------------
// 1) Use one of the following -l statements to include the 
// header linker command file in the project. The header linker
// file is required to link the peripheral structures to the proper 
// locations within the memory map                                    */

/* Uncomment this line to include file only for non-BIOS applications */
/* -l DSP281x_Headers_nonBIOS.cmd */

/* Uncomment this line to include file only for BIOS applications */
/* -l DSP281x_Headers_BIOS.cmd */

/* 2) In your project add the path to <base>\DSP281x_headers\cmd to the
   library search path under project->build options, linker tab, 
   library search path (-i).
/*========================================================= */
-l rts2800_ml.lib
-w
-stack 400h
-heap 100
MEMORY
{
PAGE 0 :
   /* For this example, H0 is split between PAGE 0 and PAGE 1 */  
   /* BEGIN is used for the "boot to HO" bootloader mode      */
   /* RESET is loaded with the reset vector only if           */
   /* the boot is from XINTF Zone 7.  Otherwise reset vector  */
   /* is fetched from boot ROM. See .reset section below      */

     BEGIN      	: origin = 0x3F7FF6, length = 0x000002
     RAMM0_0    	: origin = 0x000040, length = 0x000380
     PRAMH0      	: origin = 0x3f8000, length = 0x002000
     RAML0_CODE_USE2: origin = 0x008200, length = 0x000390
     RAML1_RSV    	: origin = 0x009000, length = 0x001000		/* 新增 */
     RAMOUT_0     	: origin = 0x100000, length = 0x01FFFF
     FLASH_E     	: origin = 0x3D8000, length = 0x01F000
     RESET       	: origin = 0x3FFFC0, length = 0x000002     /* part of boot ROM (MP/MCn=0) or XINTF zone 7 (MP/MCn=1) */
     VECTORS     	: origin = 0x3FFFC2, length = 0x00003E     /* part of boot ROM (MP/MCn=0) or XINTF zone 7 (MP/MCn=1) */
     BOOTROM (RW)   : origin = 0x3ff000, length = 0x000fc0
           
PAGE 1 : 

   /* For this example, H0 is split between PAGE 0 and PAGE 1 */
   RAMM0_1  				: origin = 0x0003C0, length = 0x000040
   RAMM1    				: origin = 0x000400, length = 0x000400
   RAML0_CODE_USE   		: origin = 0x008000, length = 0x000100   /*存储参数表*/
   RAML0_CODE_USE1     		: origin = 0x008100, length = 0x000100	 /*存储噪声*/

   myzone   				: origin = 0x008590, length = 0x000A70
   /*RAML1_RSV    			: origin = 0x009000, length = 0x001000*/
   /*RAMOUT_1_CODE_USE 		: origin = 0x120000, length = 0x01FFFF*/
   /*RAMOUT_2_RSV 			: origin = 0x140000, length = 0x03FFFF*/
   RAMOUT_1_CODE_USE 		: origin = 0x120000, length = 0x00FFFF		/* 存储回波数据 */
   RAMOUT_2_CODE_USE 		: origin = 0x130000, length = 0x00FFFF		/* PAPS FIFO */
   RAMOUT_3_CODE_USE		: origin = 0x140000, length = 0x00FFFF		/* 存储PAPS滑动平均后的数据 */
   RAMOUT_4_CODE_RSV		: origin = 0x150000, length = 0x02FFFF

   FPGA_RSV 				: origin = 0x080000, length = 0x080000


   DEV_EMU     : origin = 0x000880, length = 0x000180     /* device emulation registers */
   PIE_VECT    : origin = 0x000D00, length = 0x000100     /* PIE Vector Table */
   FLASH_REGS  : origin = 0x000A80, length = 0x000060     /* FLASH registers */
   CSM         : origin = 0x000AE0, length = 0x000010     /* code security module registers */
   XINTF       : origin = 0x000B20, length = 0x000020     /* external interface registers */
   CPU_TIMER0  : origin = 0x000C00, length = 0x000008     /* CPU Timer0 registers (CPU Timer1 and Timer2 are reserved for BIOS)*/
   PIE_CTRL    : origin = 0x000CE0, length = 0x000020     /* PIE control registers */
   ECANA       : origin = 0x006000, length = 0x000040     /* eCAN control and status registers */ 
   ECANA_LAM   : origin = 0x006040, length = 0x000040     /* eCAN local acceptance masks */
   ECANA_MOTS  : origin = 0x006080, length = 0x000040     /* eCAN message object time stamps */
   ECANA_MOTO  : origin = 0x0060C0, length = 0x000040     /* eCAN object time-out registers */
   ECANA_MBOX  : origin = 0x006100, length = 0x000100     /* eCAN mailboxes */
   SYSTEM      : origin = 0x007010, length = 0x000020     /* System control registers */
   SPIA        : origin = 0x007040, length = 0x000010     /* SPI registers */
   SCIA        : origin = 0x007050, length = 0x000010     /* SCI-A registers */
   XINTRUPT    : origin = 0x007070, length = 0x000010     /* external interrupt registers */
   GPIOMUX     : origin = 0x0070C0, length = 0x000020     /* GPIO mux registers */
   GPIODAT     : origin = 0x0070E0, length = 0x000020     /* GPIO data registers */
   ADC         : origin = 0x007100, length = 0x000020     /* ADC registers */
   EVA         : origin = 0x007400, length = 0x000040     /* Event Manager A registers */
   EVB         : origin = 0x007500, length = 0x000040     /* Event Manager B registers */
   SCIB        : origin = 0x007750, length = 0x000010     /* SCI-B registers */
   MCBSPA      : origin = 0x007800, length = 0x000040     /* McBSP registers */
   CSM_PWL     : origin = 0x3F7FF8, length = 0x000008     /* Part of FLASHA.  CSM password locations. */     
}
 
 
SECTIONS
{
   /* Setup for "boot to H0" mode: 
      The codestart section (found in DSP28_CodeStartBranch.asm)
      re-directs execution to the start of user code.  
      Place this section at the start of H0  */


/*** User Defined Sections ***/
/*   	codestart       : > BEGIN,	PAGE = 0        /* Used by file CodeStartBranch.asm */

/* .reset is a standard section used by the compiler.  It contains the */
/* the address of the start of _c_int00 for C Code.   /*
/* When using the boot ROM this section and the CPU vector */
/* table is not needed.  Thus the default type is set here to  */
/* DSECT  */
	.reset         	: > RESET,      	PAGE = 0, TYPE = DSECT
	vectors         : > VECTORS     	PAGE = 0, TYPE = DSECT

/*** Uninitialized Sections ***/
   	.stack          : > RAMM1       	PAGE = 1
   	.ebss           : > RAMM0_1 | myzone      	PAGE = 1
   	.bss            : > RAMM0_1       	PAGE = 1
      .cio            : > RAMM0_1         PAGE = 1

/*** Initialized Sections ***/
  	.cinit			: > RAMM0_0 | PRAMH0        PAGE = 0

	.const			: > RAMM0_0,  	    PAGE = 0

	.econst			: > RAMM0_0,  	    PAGE = 0

	.pinit			: > RAMM0_0,  	    PAGE = 0

	.switch			: > RAMM0_0,  	    PAGE = 0

/*	ramfuncs	    : > PRAMH0,  	    PAGE = 0*/

	.text		    : {*(.text)} >> PRAMH0 | RAML1_RSV | RAML0_CODE_USE2 | RAMOUT_0,  	    PAGE = 0

	secureRamFuncs 	    : > RAMOUT_0,       PAGE = 0

   IQmathTables : load = BOOTROM,type = NOLOAD,PAGE = 0

   IQmath           : > RAMM0_0,  	    PAGE = 0


   MyVariablesZone: > myzone,   PAGE = 1
   PieVectTableFile : > PIE_VECT,   PAGE = 1

/*** Peripheral Frame 0 Register Structures ***/
   DevEmuRegsFile    : > DEV_EMU,     PAGE = 1
   FlashRegsFile     : > FLASH_REGS,  PAGE = 1
   CsmRegsFile       : > CSM,         PAGE = 1
   XintfRegsFile     : > XINTF,       PAGE = 1
   CpuTimer0RegsFile : > CPU_TIMER0,  PAGE = 1  
   PieCtrlRegsFile   : > PIE_CTRL,    PAGE = 1      

/*** Peripheral Frame 1 Register Structures ***/
   SysCtrlRegsFile   : > SYSTEM,      PAGE = 1
   SpiaRegsFile      : > SPIA,        PAGE = 1
   SciaRegsFile      : > SCIA,        PAGE = 1
   XIntruptRegsFile  : > XINTRUPT,    PAGE = 1
   GpioMuxRegsFile   : > GPIOMUX,     PAGE = 1
   GpioDataRegsFile  : > GPIODAT      PAGE = 1
   AdcRegsFile       : > ADC,         PAGE = 1
   EvaRegsFile       : > EVA,         PAGE = 1
   EvbRegsFile       : > EVB,         PAGE = 1
   ScibRegsFile      : > SCIB,        PAGE = 1
   McbspaRegsFile    : > MCBSPA,      PAGE = 1

/*** Peripheral Frame 2 Register Structures ***/
   ECanaRegsFile     : > ECANA,       PAGE = 1
   ECanaLAMRegsFile  : > ECANA_LAM    PAGE = 1   
   ECanaMboxesFile   : > ECANA_MBOX   PAGE = 1
   ECanaMOTSRegsFile : > ECANA_MOTS   PAGE = 1
   ECanaMOTORegsFile : > ECANA_MOTO   PAGE = 1

/*** Code Security Module Register Structures ***/
   CsmPwlFile        : > CSM_PWL,     PAGE = 1
     
}



