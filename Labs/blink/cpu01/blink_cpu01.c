//###########################################################################
// FILE:   blinky_cpu01.c
// TITLE:  LED Blink Example for F2837xD.
//
//! \addtogroup dual_example_list
//! <h1> Blinky </h1>
//!
//! Dual Core Blinky Example.  This example demonstrates how to implement
//! and run a standalone application on both cores.
//
//###########################################################################
// $TI Release: F2837xD Support Library v100 $
// $Release Date: Mon Dec  9 12:58:09 CST 2013 $
//###########################################################################
#include <xdc/std.h>
#include <xdc/runtime/Log.h>
#include <ti/sysbios/BIOS.h>

#include <ti/sysbios/knl/Task.h>

#include <ti/sysbios/family/c28/Hwi.h>
#include "F28x_Project.h"     // Device Headerfile and Examples Include File
#include "F2837xD_Ipc_drivers.h"

#ifdef _FLASH
// These are defined by the linker (see device linker command file)
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadSize;
extern Uint16 RamfuncsRunStart;
#endif


unsigned long myindex = 0;

void main(void)
{

// Copy time critical code and Flash setup code to RAM
// This includes InitFlash(), Flash API functions and any functions that are
// assigned to ramfuncs section.
// The  RamfuncsLoadStart, RamfuncsLoadEnd, and RamfuncsRunStart
// symbols are created by the linker. Refer to the device .cmd file.
#ifdef _FLASH
   memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);
#endif

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F28M3Xx_SysCtrl.c file.
   InitSysCtrl();


   // Step 2. Initialize GPIO:
   // This example function is found in the F28M3Xx_Gpio.c file and
   // illustrates how to set the GPIO to it's default state.
   InitGpio(); // Skipped for this example
   EALLOW;
   GpioCtrlRegs.GPAGMUX2.bit.GPIO21 = 0;
   GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 0;
   GpioCtrlRegs.GPACSEL3.bit.GPIO21 = 0;
   GpioCtrlRegs.GPADIR.bit.GPIO21 = 1;


   GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;
   GPIO_SetupPinOptions(34, GPIO_OUTPUT, GPIO_PUSHPULL);
   GPIO_SetupPinMux(34, GPIO_MUX_CPU2, 0);
   //TODO Add code to allow configuration of GPADIR from CPU02 using IPC
   EDIS;
   GpioDataRegs.GPADAT.bit.GPIO31 = 1;// turn on LED
   GpioDataRegs.GPACLEAR.bit.GPIO21 = 1; // Turn off 21

   for (myindex = 0;myindex<1000000;myindex++) {}
   GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
   for (myindex = 0;myindex<1000000;myindex++) {}
   GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
   for (myindex = 0;myindex<1000000;myindex++) {}
   GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
   for (myindex = 0;myindex<1000000;myindex++) {}
   GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
   for (myindex = 0;myindex<1000000;myindex++) {}
   GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;

#ifdef _STANDALONE
#ifdef _FLASH
// Send boot command to allow the CPU2 application to begin execution
IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH);
#else
// Send boot command to allow the CPU2 application to begin execution
IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_RAM);
#endif
#endif

// Call Flash Initialization to setup flash waitstates
// This function must reside in RAM
#ifdef _FLASH
   InitFlash();
#endif


// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
    DINT;

// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the F28M3Xx_PieCtrl.c file.
//    InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
    IER = 0x0000;
    IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in F28M3Xx_DefaultIsr.c.
// This function is found in F28M3Xx_PieVect.c.
//    InitPieVectTable();

// Enable global Interrupts and higher priority real-time debug events:
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

// Step 6. IDLE loop. Just sit and loop forever (optional):
//    for(;;)
//    {
//        //
//        // Turn on LED
//        //
//    	GpioDataRegs.GPADAT.bit.GPIO31 = 0;
//        //
//        // Delay for a bit.
//        //
//    	DELAY_US(1000 * 500);
//
//        //
//        // Turn off LED
//        //
//        GpioDataRegs.GPADAT.bit.GPIO31 = 1;
//        //
//        // Delay for a bit.
//        //
//    	DELAY_US(1000 * 500);
//
//
//    }


    BIOS_start();

}

void danClkfunc(void) {

	GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
	GpioDataRegs.GPATOGGLE.bit.GPIO21 = 1;

}
