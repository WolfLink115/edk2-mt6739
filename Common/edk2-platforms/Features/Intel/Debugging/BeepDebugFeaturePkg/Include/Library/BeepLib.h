/** @file
  Provides services to send progress/error codes to Beep device.

  Copyright (c) 2011 - 2020, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef __BEEP_LIB_H__
#define __BEEP_LIB_H__

/**
  Sends a 32-bit value to Beep device.

  Sends the 32-bit value specified by Value to Beep device, and returns Value.
  Some implementations of this library function may perform I/O operations
  directly to Beep device.  Other implementations may send Value to
  ReportStatusCode (), and the status code reporting mechanism will eventually
  display the 32-bit value on the status reporting device.

  Beep () must actively prevent recursion.  If Beep () is called while
  processing another Post Code Library function, then
  Beep () must return Value immediately.

  @param  Value  Beep count.
**/
VOID
EFIAPI
Beep (
  IN UINT32  Value
  );

#endif
