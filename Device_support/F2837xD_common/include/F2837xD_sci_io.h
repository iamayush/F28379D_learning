//#############################################################################
//
//! \file   f2802x_common/source/sci_io.c
//###########################################################################
//
// FILE:   F2837xD_sci_io.h
//
// TITLE:  Prototypes for SCI redirection to STDIO
//
//###########################################################################
// $TI Release: F2837xD Support Library v100 $
// $Release Date: Mon Dec  9 12:58:09 CST 2013 $
//###########################################################################

#ifndef F28X7X_SCI_IO_H
#define F28X7X_SCI_IO_H

#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the functions

extern int SCI_open(const char * path, unsigned flags, int llv_fd);
extern int SCI_close(int dev_fd);
extern int SCI_read(int dev_fd, char * buf, unsigned count);
extern int SCI_write(int dev_fd, char * buf, unsigned count);
extern off_t SCI_lseek(int dev_fd, off_t offset, int origin);
extern int SCI_unlink(const char * path);
extern int SCI_rename(const char * old_name, const char * new_name);

#ifdef __cplusplus
}
#endif /* extern "C" */


#endif
// end of file
