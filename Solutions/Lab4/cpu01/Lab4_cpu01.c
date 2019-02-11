// FILE:   Lab4_cpu01.c

#include "F28x_Project.h"

// function prototypes
void ConfigureADC(void);
void ConfigureEPWM(void);
void ConfigureDAC(void);
void SetupADCEpwm(void);
interrupt void adca1_isr(void);
interrupt void ipc1_isr(void);

// variables
Uint16 dacbOutput;
Uint16 AdcaResult;


void main(void)
{

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
	InitSysCtrl();
    EALLOW;
    ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = 0;
    EDIS;


// Step 2. Initialize GPIO:
	InitGpio();  

	EALLOW;
	GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;		// used as input to ADC
	GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;		// drives LED LD2 on controlCARD
	EDIS;
	GpioDataRegs.GPADAT.bit.GPIO31 = 1;		// turn off LED
    
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

	//Map ISR functions
	EALLOW;
	PieVectTable.ADCA1_INT = &adca1_isr; 	// ADCA1 interrupt
	PieVectTable.IPC1_INT = &ipc1_isr;		// CIPC1 interrupt
	EDIS;

	//Configure the ADC and power it up
	ConfigureADC();

	//Configure the ePWM
	ConfigureEPWM();

	//Configure DAC-B
    ConfigureDAC();

	//Setup the ADC for ePWM triggered conversions on channel 0
	SetupADCEpwm();

	IpcRegs.IPCCLR.all = 0xFFFFFFFF;

	//enable PIE interrupts
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;	// ADC ISR
    PieCtrlRegs.PIEIER1.bit.INTx13 = 1;	// IPC1 ISR

	//Enable global Interrupts and higher priority real-time debug events:
	IER |= M_INT1; 						//Enable group 1 interrupts
	EINT;  								// Enable Global interrupt INTM
	ERTM;  								// Enable Global realtime interrupt DBGM

	//sync & start ePWM
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EPwm2Regs.ETSEL.bit.SOCAEN = 1; 	// enable SOCA
    EPwm2Regs.TBCTL.bit.CTRMODE = 0; 	// un-freeze, and enter up count mode
    EDIS;

    // main loop
	while(1)
	{
      	GpioDataRegs.GPADAT.bit.GPIO31 = 0;		// Turn on LED
      	DELAY_US(1000 * 500);					// ON delay
      	GpioDataRegs.GPADAT.bit.GPIO31 = 1;   	// Turn off LED
      	DELAY_US(1000 * 500);					// OFF delay
	}

}


//Write ADC configurations and power up the ADC for both ADC A and ADC B
void ConfigureADC(void)
{
	EALLOW;
	AdcaRegs.ADCCTL2.bit.PRESCALE = 6; 			// set ADCCLK divider to /4
	AdcaRegs.ADCCTL2.bit.RESOLUTION = 0;	 	// 12-bit resolution
	AdcaRegs.ADCCTL2.bit.SIGNALMODE = 0; 		// single-ended channel conversions (12-bit mode only)
	AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;		// Set pulse positions to late
	AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;			// power up the ADC
	DELAY_US(1000);								// delay for 1ms to allow ADC time to power up
	EDIS;
}


void ConfigureEPWM(void)
{
	EALLOW;
	// Assumes ePWM clock is already enabled
	EPwm2Regs.ETSEL.bit.SOCAEN	= 0;	        // Disable SOC on A group
	EPwm2Regs.ETSEL.bit.SOCASEL	= 4;	        // Select SOC on up-count
	EPwm2Regs.ETPS.bit.SOCAPRD = 1;		        // Generate pulse on 1st event
	EPwm2Regs.CMPA.half.CMPA = 0x0800;          // Set compare A value to 2048 counts
	EPwm2Regs.TBPRD = 0x0FA0;			        // Set period to 4000 counts (50kHz)
	EPwm2Regs.TBCTL.bit.CTRMODE = 3;            // freeze counter
	EPwm2Regs.TBCTL.bit.HSPCLKDIV = 0;			// TBCLK pre-scaler = /1
	EDIS;
}


void ConfigureDAC(void)
{
	// configure DACB
	EALLOW;
	DacbRegs.DACCTL.bit.DACREFSEL = 1;			// use ADC references
	DacbRegs.DACCTL.bit.MODE = 0;				// gain = x1
	DacbRegs.DACCTL.bit.LOADMODE = 0;			// load on next SYSCLK
	DacbRegs.DACVALS.all = 0x0800;				// set mid-range
	DacbRegs.DACOUTEN.bit.DACOUTEN = 1;			// enable DAC
	EDIS;
}

void SetupADCEpwm(void)
{
	EALLOW;
	AdcaRegs.ADCSOC0CTL.bit.CHSEL = 0;  		// SOC0 will convert pin A0
	AdcaRegs.ADCSOC0CTL.bit.ACQPS = 14; 		// sample window is 100 SYSCLK cycles
	AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 7; 		// trigger on ePWM2 SOCA/C
	AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0; 		// end of SOC0 will set INT1 flag
	AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;   		// enable INT1 flag
	AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; 		// make sure INT1 flag is cleared
	EDIS;
}


interrupt void ipc1_isr(void)
{
	// read IPC channel 0 and write to DACB
	dacbOutput = (Uint16) IpcRegs.IPCRECVADDR;	// read data on IPC ADDR register
	DacbRegs.DACVALS.all = dacbOutput;			// write to DACB

	// Return from interrupt
	IpcRegs.IPCACK.bit.IPC0 = 1;				// clear IPC1 bit
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}


interrupt void adca1_isr(void)
{
	// read the ADC result and write to IPC channel 1
	AdcaResult = AdcaResultRegs.ADCRESULT0;
	IpcRegs.IPCSENDDATA = (Uint32) AdcaResult;	// write the result to the IPC data register
	IpcRegs.IPCSET.bit.IPC1 = 1;				// set the IPC2 flag for CPU2

	// Return from interrupt
	AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; 		// Clear ADC INT1 flag
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

 // end of file
