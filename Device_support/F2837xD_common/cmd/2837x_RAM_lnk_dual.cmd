/* Default linker map for Soprano validation. Works for both CPUs with CLAs. */

/* Required definitions for the CLA scratchpad */
CLA_SCRATCHPAD_SIZE = 0x80;
--undef_sym=__cla_scratchpad_end
--undef_sym=__cla_scratchpad_start


MEMORY
{
PAGE 0 : /* Program memory. This is a legacy description since the C28 has a unified memory model. */

	/* Used for boot to SARAM */
	BEGIN           : origin = 0x000000, length = 0x000002
   RAMM0           	: origin = 0x000122, length = 0x0002DE

	/* Locally shared memory -- can be used by the local CPU and its CLA */
	RAMLS0          : origin = 0x008000, length = 0x000800
	RAMLS1          : origin = 0x008800, length = 0x000800
	RAMLS2          : origin = 0x009000, length = 0x000800

	/* C program space for RAM-based validation testing */
	RAMLS5          : origin = 0x00A800, length = 0x000800
	RAMD0           : origin = 0x00B000, length = 0x000800
	RAMD1           : origin = 0x00B800, length = 0x000800

	/* Boot ROM reset vector */
	RESET           : origin = 0x3FFFC0, length = 0x000002

PAGE 1 : /* Data memory. This is a legacy description since the C28 has a unified memory model. */

	/* Stack */
	BOOT_RSVD       : origin = 0x000002, length = 0x000120     /* Part of M0, BOOT rom will use this for stack */
	RAMM1           : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */

	/* Locally shared memory -- can be used by the local CPU and its CLA */
	RAMLS3          : origin = 0x009800, length = 0x000800
	RAMLS4          : origin = 0x00A000, length = 0x000800

	/* Globally shared memory -- can be used by both CPUs and their CLAs */
	RAMGS0          : origin = 0x00C000, length = 0x001000
	RAMGS1          : origin = 0x00D000, length = 0x001000
	RAMGS2          : origin = 0x00E000, length = 0x001000
	RAMGS3          : origin = 0x00F000, length = 0x001000
	RAMGS4          : origin = 0x010000, length = 0x001000
	RAMGS5          : origin = 0x011000, length = 0x001000
	RAMGS6          : origin = 0x012000, length = 0x001000
	RAMGS7          : origin = 0x013000, length = 0x001000
	RAMGS8          : origin = 0x014000, length = 0x001000
	RAMGS9          : origin = 0x015000, length = 0x001000
	RAMGS10         : origin = 0x016000, length = 0x001000
	RAMGS11         : origin = 0x017000, length = 0x001000
	RAMGS12         : origin = 0x018000, length = 0x001000
	RAMGS13         : origin = 0x019000, length = 0x001000
	RAMGS14         : origin = 0x01A000, length = 0x001000
	RAMGS15         : origin = 0x01B000, length = 0x001000
    CPU1TOCPU2RAM   : origin = 0x03F800, length = 0x000400
	/* Local CLA<->CPU message RAMs */
	CLATOCPU_MSGRAM : origin = 0x001480, length = 0x000080
	CPUTOCLA_MSGRAM : origin = 0x001500, length = 0x000080
}

SECTIONS
{
	/* Program sections */
	codestart        : > BEGIN,                     PAGE = 0
	ramfuncs         : > RAMM0,                     PAGE = 0
	.cinit           : > RAMM0,                     PAGE = 0
	.pinit           : > RAMM0,                     PAGE = 0
	.switch          : > RAMM0,                     PAGE = 0
	.text            : >>RAMLS5 | RAMD0 | RAMD1,    PAGE = 0
	.reset           : > RESET,                     PAGE = 0, TYPE = DSECT /* not used */

 	/* CLA program and data sections */
	Cla1Prog         : > RAMLS0 | RAMLS1 | RAMLS2,  PAGE = 0
	ClaData          : > RAMLS3 | RAMLS4,           PAGE = 1
	ClaToCpuMsgRAM   : > CLATOCPU_MSGRAM,           PAGE = 1
	CpuToClaMsgRAM   : > CPUTOCLA_MSGRAM,           PAGE = 1
	.bss_cla         : > RAMLS4,                    PAGE = 1

	/* CLA stack section, AKA the scratchpad */
    CLAscratch       : { *.obj(CLAscratch)
                         . += CLA_SCRATCHPAD_SIZE;
                         *.obj(CLAscratch_end) }
                        > RAMLS3 | RAMLS4,          PAGE = 1


	/* Data sections */
	.stack           : > RAMM1,                     PAGE = 1
	.ebss            : > RAMLS4,                    PAGE = 1
	.econst          : > RAMLS4,                    PAGE = 1
	.esysmem         : > RAMLS4,                    PAGE = 1
	Filter_RegsFile  : > RAMGS0,                    PAGE = 1
}

/*
* ===========================================================================
* End of file.
* ===========================================================================
*/
