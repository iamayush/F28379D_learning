// FILE:   Lab2_cpu01.c

#include "F28x_Project.h"     // Device Headerfile and Examples Include File

// function prototypes
void ConfigureADC(void);
void ConfigureEPWM(void);
void ConfigureDAC(void);
void SetupADCEpwm(void);
interrupt void adca1_isr(void);

// variables
#define RESULTS_BUFFER_SIZE 256
Uint16 AdcaResults[RESULTS_BUFFER_SIZE];
Uint16 resultsIndex;
Uint16 ToggleCount = 0;
Uint16 dacOffset;
Uint16 dacOutput;
Uint16 sineEnable = 0;
extern int QuadratureTable[40];


void main(void)
{
	// Initialize System Control: PLL, WatchDog, enable Peripheral Clocks
    InitSysCtrl();
    EALLOW;
    ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = 0;
    EDIS;

    // Initialize GPIO:
    InitGpio(); 				// configure default GPIO
    EALLOW;
    GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;	// used as input to ADC
    GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;	// drives LED LD2 on controlCARD
    EDIS;
    GpioDataRegs.GPADAT.bit.GPIO8 = 0; // force GPIO8 output LOW
    GpioDataRegs.GPADAT.bit.GPIO31 = 1;// turn off LED

    // Clear all interrupts and initialize PIE vector table:
    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();

    // Map ISR functions
    EALLOW;
    PieVectTable.ADCA1_INT = &adca1_isr; //function for ADCA interrupt 1
    EDIS;

    // Configure the ADC and power it up
    ConfigureADC();

    // Configure the ePWM
    ConfigureEPWM();

    // Configure DAC-B
    ConfigureDAC();

    // Setup the ADC for ePWM triggered conversions on channel 0
    SetupADCEpwm();

    // Initialize results buffer
    for(resultsIndex = 0; resultsIndex < RESULTS_BUFFER_SIZE; resultsIndex++)
    {
    	AdcaResults[resultsIndex] = 0;
    }
    resultsIndex = 0;

    // enable PIE interrupt
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;

    // Enable global Interrupts and higher priority real-time debug events:
    IER |= M_INT1; 			// Enable group 1 interrupts
    EINT;  					// Enable Global interrupt INTM
    ERTM;  					// Enable Global real-time interrupt DBGM

    // Sync ePWM
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

    // Start ePWM
    EPwm2Regs.TBCTL.bit.CTRMODE = 0; 			// un-freeze and enter up-count mode

    do {

      	GpioDataRegs.GPADAT.bit.GPIO31 = 0;		// Turn on LED
      	DELAY_US(1000 * 500);					// ON delay
      	GpioDataRegs.GPADAT.bit.GPIO31 = 1;   	// Turn off LED
      	DELAY_US(1000 * 500);					// OFF delay

    } while(1);
}

//Write ADC configurations and power up the ADC for both ADC A and ADC B
void ConfigureADC(void)
{
	EALLOW;
	AdcaRegs.ADCCTL2.bit.PRESCALE = 6; 			// set ADCCLK divider to /4
	AdcaRegs.ADCCTL2.bit.RESOLUTION = 0; 		// 12-bit resolution
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
	EPwm2Regs.TBCTL.bit.CTRMODE = 3;            // freeze counter
	EPwm2Regs.TBCTL.bit.HSPCLKDIV = 0;			// TBCLK pre-scaler = /1
	EPwm2Regs.TBPRD = 0x0FA0;			        // Set period to 4000 counts (50kHz)
	EPwm2Regs.CMPA.half.CMPA = 0x0800;          // Set compare A value to 2048 counts
	EPwm2Regs.ETSEL.bit.SOCAEN	= 0;	        // Disable SOC on A group
	EPwm2Regs.ETSEL.bit.SOCASEL	= 4;	        // Select SOC on up-count
    EPwm2Regs.ETSEL.bit.SOCAEN = 1; 			// enable SOCA
	EPwm2Regs.ETPS.bit.SOCAPRD = 1;		        // Generate pulse on 1st event
	EDIS;
}

void ConfigureDAC(void)
{
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

interrupt void adca1_isr(void)
{
	// Read the ADC result and store in circular buffer
	AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT0;
	if(RESULTS_BUFFER_SIZE <= resultsIndex)
	{
		resultsIndex = 0;
	}

	// Toggle GPIO8 so we can read it with the ADC
	if (ToggleCount++ >= 15)
	{
		GpioDataRegs.GPATOGGLE.bit.GPIO8 = 1;
		ToggleCount = 0;
	}

	// Write to DACB to create input to ADC-A0
	if (sineEnable != 0)
	{
		dacOutput = dacOffset + ((QuadratureTable[resultsIndex % 0x20] ^ 0x8000) >> 5);
	}
	else
	{
		dacOutput = dacOffset;
	}
	DacbRegs.DACVALS.all = dacOutput;

	// Return from interrupt
	AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; 		// Clear INT1 flag
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;		// acknowledge PIE group 1 to enable further interrupts
}

 // end of file
