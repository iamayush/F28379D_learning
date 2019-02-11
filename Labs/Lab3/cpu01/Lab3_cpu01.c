// FILE:   Lab3_cpu01.c

#include "F28x_Project.h"     		// Device Headerfile and Examples Include File

// definitions for PWM generation
#define PWM1_PERIOD	0xC350			// PWM1 frequency = 2kHz
#define PWM1_CMPR25	PWM1_PERIOD>>2	// PWM1 initial duty cycle = 25%

// function prototypes
void ConfigureADC(void);
void ConfigureEPWM(void);
void SetupADCEpwm(void);
void InitEPwm1Example(void);		// configure ePWM module 1
void InitEPwm2Example(void);		// configure ePWM module 2
void InitEPwm5Example(void);		// configure ePWM module 5
interrupt void adca1_isr(void);		// ADC interrupt service routine

// variables
Uint16 period1 = PWM1_PERIOD;		// PWM1 period = 2kHz PWM (clkdiv = /2)
Uint16 dutyCycle1 = PWM1_CMPR25;	// PWM1 duty cycle = 25%
Uint16 dutyCycle5 = PWM1_CMPR25;	// PWM5 duty cycle = 25%
Uint16 phaseOffset5 = 0;			// PWM5 phase offset = 0

// buffers for storing ADC conversion results
#define RESULTS_BUFFER_SIZE 256
Uint16 AdcaResults[RESULTS_BUFFER_SIZE];
Uint16 AdccResults[RESULTS_BUFFER_SIZE];
Uint16 resultsIndex;
Uint16 pretrig = 0;
Uint16 trigger = 0;


void main(void)
{
	// Initialize System Control: PLL, WatchDog, enable Peripheral Clocks
    InitSysCtrl();
    EALLOW;
    ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = 0;
    EDIS;

    // Initialize GPIO
    InitGpio(); 		// configure default GPIO
    InitEPwm1Gpio();	// configure EPWM1 GPIO pins
    InitEPwm5Gpio();	// configure EPWM5 GPIO pins

    EALLOW;
    GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;			// drives LED LD2 on controlCARD
    EDIS;
    GpioDataRegs.GPADAT.bit.GPIO31 = 1;			// turn off LED

    // Clear all interrupts and initialize PIE vector table:
    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();

    // Map ISR functions
    EALLOW;
    PieVectTable.ADCA1_INT = &adca1_isr; 			// function for ADCA interrupt 1
    EDIS;

    // Configure the ADC and power it up
    ConfigureADC();

    // Setup the ADC for ePWM triggered conversions on channel 0
    SetupADCEpwm();

    // Initialise ePWM modules
    InitEPwm1Example();
    InitEPwm2Example();
    InitEPwm5Example();

    // Initialize results buffers
    for(resultsIndex = 0; resultsIndex < RESULTS_BUFFER_SIZE; resultsIndex++)
    {
       	AdcaResults[resultsIndex] = 0;
     	AdccResults[resultsIndex] = 0;
    }
    resultsIndex = 0;

    // Enable global Interrupts and higher priority real-time debug events:
    IER |= M_INT1; 			// Enable group 1 interrupts
    EINT;  					// Enable Global interrupt INTM
    ERTM;  					// Enable Global realtime interrupt DBGM

    // Enable PIE interrupt
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;

    // Sync ePWM
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;

    // Start ePWM
    EPwm2Regs.ETSEL.bit.SOCAEN = 1; 			//enable SOCA
    EPwm2Regs.TBCTL.bit.CTRMODE = 0; 			//un-freeze and enter up-count mode

    do {
      	GpioDataRegs.GPADAT.bit.GPIO31 = 0;		// Turn on LED
      	DELAY_US(1000 * 500);					// ON delay
      	GpioDataRegs.GPADAT.bit.GPIO31 = 1;   	// Turn off LED
      	DELAY_US(1000 * 500);					// OFF delay

    } while(1);
}


//Write ADC configurations and power up the ADC for both ADC A and ADC C
void ConfigureADC(void)
{
	EALLOW;

	// ADC-A
	AdcaRegs.ADCCTL2.bit.PRESCALE = 6; 			// set ADCCLK divider to /4
	AdcaRegs.ADCCTL2.bit.RESOLUTION =  0; 		// 12-bit resolution
	AdcaRegs.ADCCTL2.bit.SIGNALMODE = 0; 		// single-ended channel conversions (12-bit mode only)
	AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;		// Set pulse positions to late
	AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;			// power up the ADC

	// ADC-C
	AdccRegs.ADCCTL2.bit.PRESCALE = 6; 			// set ADCCLK divider to /4
	AdccRegs.ADCCTL2.bit.RESOLUTION =  0; 		// 12-bit resolution RESOLUTION_12BIT;
	AdccRegs.ADCCTL2.bit.SIGNALMODE = 0; 		// single-ended channel conversions (12-bit mode only)
	AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1;		// Set pulse positions to late
	AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1;			// power up the ADC
	EDIS;

	DELAY_US(1000);								// delay for 1ms to allow ADC time to power up
}


void SetupADCEpwm()
{
	//Select the channels to convert and end of conversion flag
	EALLOW;
	AdcaRegs.ADCSOC0CTL.bit.CHSEL = 0;  		//SOC0 will convert pin A0
	AdcaRegs.ADCSOC0CTL.bit.ACQPS = 14; 		//sample window is 100 SYSCLK cycles
	AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 7; 		//trigger on ePWM2 SOCA/C
	AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0; 		//end of SOC0 will set INT1 flag
	AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;   		//enable INT1 flag
	AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; 		//make sure INT1 flag is cleared

	// also set up ADC-C3 in this example
	AdccRegs.ADCSOC0CTL.bit.CHSEL = 3;  		//SOC0 will convert pin C3
	AdccRegs.ADCSOC0CTL.bit.ACQPS = 14; 		//sample window is 100 SYSCLK cycles
	AdccRegs.ADCSOC0CTL.bit.TRIGSEL = 7; 		//trigger on ePWM2 SOCA/C
	EDIS;
}


void InitEPwm1Example()
{

   // Setup TBCLK
   EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; 	// Count up
   EPwm1Regs.TBPRD = period1;  					// Set timer period
   EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;    	// Disable phase loading
   EPwm1Regs.TBPHS.half.TBPHS = 0x0000;       	// Phase is 0
   EPwm1Regs.TBCTR = 0x0000;                  	// Clear counter
   EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV2;   	// Clock ratio to SYSCLKOUT
   EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV2;
   EPwm1Regs.TBCTL.bit.SYNCOSEL = 1;			// SYNC output on CTR = 0

   // Setup shadow register load on ZERO
   EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
   EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set Compare values
   EPwm1Regs.CMPA.half.CMPA = dutyCycle1; 		// Set compare A value

   // Set actions
   EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET;           // Set PWM1A on Zero
   EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;         // Clear PWM1A on event A, up count
}


void InitEPwm2Example()
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


void InitEPwm5Example()
{
   // Setup TBCLK
   EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; 	// Count up
   EPwm5Regs.TBPRD = PWM1_PERIOD;  				// Same period as PWM1
   EPwm5Regs.TBCTL.bit.PHSEN = TB_ENABLE;    	// Enable phase loading
   EPwm5Regs.TBPHS.half.TBPHS = phaseOffset5;   // Phase
   EPwm5Regs.TBCTR = 0x0000;                  	// Clear counter
   EPwm5Regs.TBCTL.bit.HSPCLKDIV = TB_DIV2;   	// Clock ratio to SYSCLKOUT
   EPwm5Regs.TBCTL.bit.CLKDIV = TB_DIV2;

   // Setup shadow register load on ZERO
   EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
   EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set Compare values
   EPwm5Regs.CMPA.half.CMPA = dutyCycle5; 		// Set compare A value

   // Set actions
   EPwm5Regs.AQCTLA.bit.ZRO = AQ_SET;           // Set PWM1A on Zero
   EPwm5Regs.AQCTLA.bit.CAU = AQ_CLEAR;         // Clear PWM1A on event A, up count
}


interrupt void adca1_isr(void)
{
	// Read the ADC result and store in circular buffer
	if (trigger != 0)
	{
		AdcaResults[resultsIndex] = AdcaResultRegs.ADCRESULT0;
		AdccResults[resultsIndex++] = AdccResultRegs.ADCRESULT0;
		if(RESULTS_BUFFER_SIZE <= resultsIndex)
		{
			resultsIndex = 0;
			pretrig = 0;
			trigger = 0;

			// update PWMs
			EPwm1Regs.TBPRD = period1;
			EPwm1Regs.CMPA.half.CMPA = dutyCycle1;
			EPwm5Regs.TBPRD = period1;
			EPwm5Regs.CMPA.half.CMPA = dutyCycle5;
			EPwm5Regs.TBPHS.half.TBPHS = phaseOffset5;
		}
	}

	// This code identifies a low-to-high transition on PWM1A so the results buffer always starts
	// on a rising edge.  This makes phase observations between PWM1 and PWM5 clearer.
	else if (pretrig != 0)
	{
		trigger |= GpioDataRegs.GPADAT.bit.GPIO0;
	}
	else pretrig = GpioDataRegs.GPADAT.bit.GPIO0 - 1;

	// Return from interrupt
	AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; 		// Clear INT1 flag
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;		// acknowledge PIE group 1 to enable further interrupts
}

 // end of file
