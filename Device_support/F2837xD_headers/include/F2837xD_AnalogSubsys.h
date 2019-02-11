//###########################################################################
//
// FILE:   F2837x_AnalogSubsys.h
//
// TITLE:  F2837x Device AnalogSubsys Register Definitions.
//
// BUILD:  CUSTOMER RELEASE
//
//###########################################################################
// $TI Release: F2837xD Support Library v100 $
// $Release Date: Mon Dec  9 12:58:09 CST 2013 $
//###########################################################################

#ifndef F2837x_AnalogSubsys_H
#define F2837x_AnalogSubsys_H
#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// AnalogSubsys Individual Register Bit Definitions:

struct TSNSCTL_BITS {                                 // bit descriptions
    Uint16  ENABLE:1;                                 // 0 Temperature Sensor Enable 
    Uint16  rsvd1:15;                                 // 15:1 Reserved 
};

union TSNSCTL_REG {
    Uint16  all;  
    struct  TSNSCTL_BITS  bit;  
};

struct LOCK_BITS {                                    // bit descriptions
    Uint16  rsvd1:3;                                  // 2:0 Reserved 
    Uint16  TSNSCTL:1;                                // 3 Temperature Sensor Control Register Lock 
    Uint16  rsvd2:12;                                 // 15:5 Reserved 
    Uint16  rsvd3:16;                                 // 31:16 Reserved 
};

union LOCK_REG {
    Uint32  all;  
    struct  LOCK_BITS  bit;  
};

#if defined(CPU1)
struct ANALOG_SUBSYS_REGS {
    Uint16                   rsvd1[38];               // Reserved 
    union   TSNSCTL_REG      TSNSCTL;                 // Temperature Sensor Control Register 
    Uint16                   rsvd2[7];                // Reserved 
    union   LOCK_REG         LOCK;                    // Lock Register 
    Uint16                   rsvd3[24];               // Reserved 
};
#endif

//---------------------------------------------------------------------------
// AnalogSubsys External References & Function Declarations:
//

#if defined(CPU1)
extern volatile struct ANALOG_SUBSYS_REGS AnalogSubsysRegs;
#endif

#ifdef __cplusplus
}
#endif                                                /* extern "C" */


#endif                                                // end of F2837x_ANALOGSUBSYS_H definition
//===========================================================================
// End of file.
//===========================================================================
