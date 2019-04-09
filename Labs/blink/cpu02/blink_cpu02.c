//###########################################################################
// FILE:   blinky_cpu02.c
// TITLE:  LED Blink Example for F2837xD.
//
// Dual Core Blinky Example.  This example demonstrates how to run a
// implement a standalone application on both cores.
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

#include "f28377sCoecsl.h" // Ayush
#include "f28377sSerial.h"

#ifdef _FLASH
// These are defined by the linker (see device linker command file)
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadSize;
extern Uint16 RamfuncsRunStart;
#endif

// esp8266 wifi chip varibales
int AT_FLAG = 0;
int CW_FLAG = 0;
int LOGIN_FLAG = 0;
int MODE_FLAG = 0;
int PORT_FLAG = 0;
int ADDR_FLAG = 0;
#define NUM_CHARS	2048
char esp_receive[NUM_CHARS];
char espmsg[NUM_CHARS];
int esp_lv = 0;
int beginwrite = 0;
int arrlen = 0;
int msglen = 0;
int len = 0;
char msg[NUM_CHARS];
//char LV_BUF[100];
//int n;

void serialRXB(serial_t *s, char data);
//void clear_esp_receive(int option, int length);
//void LV_option(char data);

void clkfunc(void)  {
	//	GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
	GpioDataRegs.GPBTOGGLE.bit.GPIO63 = 1;
}




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

	// Call Flash Initialization to setup flash waitstates
	// This function must reside in RAM

	//  Note to DAN BLOCK,  this is not needed because InitSysCtrl calls this for you
#ifdef _FLASH
	InitFlash();
#endif

	// Step 3. Clear all interrupts and initialize PIE vector table:
	// Disable CPU interrupts
	DINT;

	// Disable CPU interrupts and clear all CPU interrupt flags:
	IER = 0x0000;
	IFR = 0x0000;

	// Enable global Interrupts and higher priority real-time debug events:
	EINT;  // Enable Global interrupt INTM
	ERTM;  // Enable Global realtime interrupt DBGM

	//	init_serial(&SerialB,115200,serialRXB);
	//	DELAY_US(200000);

	while(AT_FLAG == 0)
	{
		serial_send(&SerialB,"AT\r\n",strlen("AT\r\n"));
		DELAY_US(200000);
		GpioDataRegs.GPATOGGLE.bit.GPIO13 = 1;
	}

	// *******************************************************************
	// Comment out after connecting to new router
	//	while(CW_FLAG == 0)
	//	{
	//		serial_send(&SerialB,"AT+CWMODE=3\r\n",strlen("AT+CWMODE=3\r\n"));
	//		DELAY_US(200000L);
	//		GpioDataRegs.GPATOGGLE.bit.GPIO13 = 1;
	//	}
	//
	//	while(LOGIN_FLAG == 0)
	//	{
	//		serial_send(&SerialB,"AT+CWJAP=\"MECHNIGHT\",\"f33dback5\"\r\n",strlen("AT+CWJAP=\"MECHNIGHT\",\"f33dback5\"\r\n"));
	//		DELAY_US(2000000L);
	//		GpioDataRegs.GPATOGGLE.bit.GPIO13 = 1;
	//	}
	// *******************************************************************



	//	while(ADDR_FLAG == 0)
	//	{
	//		serial_send(&SerialB, "AT+CIPSTA=\"192.168.1.51\"\r\n", strlen("AT+CIPSTA=\"192.168.1.51\"\r\n"));
	//		DELAY_US(200000L);
	//		GpioDataRegs.GPATOGGLE.bit.GPIO13 = 1;
	//	}
	//
	//	while (MODE_FLAG == 0)
	//	{
	//		serial_send(&SerialB,"AT+CIPMUX=1\r\n", strlen("AT+CIPMUX=1\r\n"));
	//		DELAY_US(500000L);
	//		GpioDataRegs.GPATOGGLE.bit.GPIO13 = 1;
	//	}
	//
	//	while(PORT_FLAG == 0)
	//	{
	//		serial_send(&SerialB,"AT+CIPSERVER=1,1336\r\n", strlen("AT+CIPSERVER=1,1336\r\n"));
	//		DELAY_US(200000L);
	//		GpioDataRegs.GPATOGGLE.bit.GPIO13 = 1;
	//	}

	BIOS_start();
}

// helper function to clean esp chip data buffer
//void clear_esp_receive(int option, int length)
//{
//	int i;
//	if (option == 1)
//	{
//		arrlen = 0;
//		for (i = 0; i < length; i++)
//			esp_receive[i] = NULL;
//	}
//	if (option == 2)
//	{
//		for (i = 0; i < length; i++)
//			espmsg[i] = NULL;
//	}
//
//}

void serialRXB(serial_t *s, char data)
{
	//	if (s == &SerialB)
	//	{
	//
	//		if (PORT_FLAG != 1) // SETUP NOT READY
	//		{
	//
	//
	//			if (beginwrite == 0 && data == 'A') // beginwrite -- flag for useful command, starting with "AT"
	//			{
	//				beginwrite = 1;
	//				arrlen = 1;
	//				esp_receive[arrlen-1] = (char) data;
	//			}
	//			else if (beginwrite == 1 && arrlen < NUM_CHARS && data != 'K') // command data transfer not finished
	//			{
	//				arrlen++;
	//
	//
	//				esp_receive[arrlen-1] = (char) data;
	//			}
	//			else if (beginwrite == 1 && arrlen < NUM_CHARS && data == 'K') // end of transferring command data
	//			{
	//				arrlen++;
	//				esp_receive[arrlen-1] = (char) data;
	//				// check command contents, based on the length of the string
	//				if (arrlen == 9){ // check initially if AT command connection works
	//					AT_FLAG = 1;
	//
	//				}
	//
	//
	//
	//
	//				// *******************************************************************
	//				// Comment out after connecting to new router
	//
	////				else if (arrlen == (strlen("AT+CWMODE=3")+7)){
	////					CW_FLAG = 1;
	////				}
	////				else if (arrlen == (3*(strlen("AT+CWJAP=\"MECHNIGHT\",\"f33dback5\""))+80)){
	////					LOGIN_FLAG = 1;
	////
	////				}
	//				// *******************************************************************
	//
	//
	//
	//
	//
	//				else if (arrlen == 18){// set up mux mode
	//					MODE_FLAG = 1;
	//
	//				}
	//				else if (arrlen == 26 || arrlen == 37){ // set up port number
	//					PORT_FLAG = 1;
	//
	//				}
	//				else if (arrlen == (strlen("AT+CIPSTA=\"192.168.1.51\"")+7)){ // set up unique IP address
	//					ADDR_FLAG = 1;
	//
	//				}
	//
	//				beginwrite = 0;
	//				clear_esp_receive(1, arrlen);
	//				//arrlen = 0;
	//			}
	//			else if (beginwrite == 1 && arrlen >= NUM_CHARS)
	//			{
	//				beginwrite = 0;
	//				//clear_esp_receive(1, NUM_CHARS);
	//				//arrlen = 0;
	//			}
	//
	//		}
	//
	//		else if (PORT_FLAG == 1)// SETUP READY
	//		{
	//			if (esp_lv == 0)
	//			{
	//				if (data == '$')
	//				{
	//					beginwrite = 0;
	//					esp_lv = 1; // set flag between esp and LV to be 1
	//
	//				}
	//
	//			}
	//			else if (esp_lv == 1 && msglen < NUM_CHARS && data != '@') // data transfer not finished
	//			{
	//				msglen++;
	//				espmsg[msglen-1] = (char) data;
	//				LV_option(data);
	//			}
	//			else if (esp_lv == 1 && msglen < NUM_CHARS && data == '@') // end of data transfer
	//			{
	//				esp_lv = 0;
	//			}
	//			else if (esp_lv == 1 && msglen >= NUM_CHARS)
	//			{
	//				msglen=1;
	//				espmsg[msglen-1] = (char) data;
	//			}
	//			if (beginwrite == 1)
	//			{
	//				LV_option(data);
	//			}
	//		}
	//
	//	}

}

//char LV_BUF[100];
//int n;
//void LV_option(char data)
//{
//	if (data == 's' && beginwrite == 0)
//	{
//		beginwrite = 1;
//		n = sprintf(LV_BUF,"%.2f%0.2f%0.2f%0.2f%.4f%.4f%.4f\r\n",
//				u,
//				vel2,
//				K[0],
//				K[1],
//				K[3],
//				tilt,
//				accelxSide);
//		// prepare esp to start transferring data to labview
//		// with the length of the data string
//		serial_printf(&SerialB,"AT+CIPSEND=0,%d\r\n", n);
//	}
//	if (data == '>') // indicates we can start esp->labview transfer
//	{
//		serial_send(&SerialB, LV_BUF, n);
//		beginwrite = 0;
//	}
//	if (data == 'p')
//		accelxSide+= 0.0005;
//	if (data == 'q')
//		accelxSide-= 0.0005;
//	if (data == 'x')
//		K[0]+=5;
//	if(data == 'v')
//		K[0]-=5;
//	if(data == 'k')
//		K[1]+=.5;
//	if(data == 'i')
//		K[1]-=.5;
//	if(data == 'j')
//		K[3]+=.0005;
//	if(data == 'n')
//		K[3]-=.0005;
//}
