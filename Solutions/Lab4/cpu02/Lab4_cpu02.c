// FILE:   Lab4_cpu02.c

#include "F28x_Project.h"

// function prototypes
interrupt void ipc2_isr(void);

// variables
#define RESULTS_BUFFER_SIZE 256
Uint16 AdcaResults[RESULTS_BUFFER_SIZE];
Uint16 resultsIndex;
extern int QuadratureTable[40];
Uint16 sineData = 0;


void main(void)
{

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initialize GPIO:
// InitGpio();  // Skipped for this example

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
	DINT;

// Initialize PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the F2837xD_PieCtrl.c file.
	InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
	IER = 0x0000;
	IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in F2837xD_DefaultIsr.c.
// This function is found in F2837xD_PieVect.c.
	InitPieVectTable();

	// Map ISR functions
	EALLOW;
	PieVectTable.IPC2_INT = &ipc2_isr;		// IPC2 interrupt
	EDIS;

	//Initialize results buffer
    for(resultsIndex = 0; resultsIndex < RESULTS_BUFFER_SIZE; resultsIndex++)
    {
    	AdcaResults[resultsIndex] = 0;
    }
    resultsIndex = 0;

    IpcRegs.IPCCLR.bit.IPC1 = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

	//enable PIE interrupts
    PieCtrlRegs.PIEIER1.bit.INTx14 = 1;		// enable IPC2 ISR
    PieCtrlRegs.PIEIFR1.bit.INTx14 = 1;		// force first transfer

	//Enable global Interrupts and higher priority real-time debug events:
	IER |= M_INT1; 						// Enable group 1 interrupts
	EINT;       						// Enable Global interrupt INTM
	ERTM;   							// Enable Global real-time interrupt DBGM

		while(1)
	{
		;
	}
}


interrupt void ipc2_isr(void)
{
	// read back ADC-A0 results and store in circular buffer
	AdcaResults[resultsIndex++] = (Uint16) IpcRegs.IPCRECVDATA;
	if(RESULTS_BUFFER_SIZE <= resultsIndex)
	{
		resultsIndex = 0;
	}

	// write next data point from sine table
	sineData = (QuadratureTable[resultsIndex % 0x20] ^ 0x8000) >> 5;
	IpcRegs.IPCSENDADDR = (Uint16) sineData;
	IpcRegs.IPCSET.bit.IPC0 = 1;				// set IPC0 bit for CPU1

	// Return from interrupt
	IpcRegs.IPCACK.bit.IPC1 = 1;				// clear IPC1 bit
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

// end of file
