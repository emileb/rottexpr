/*
Copyright (C) 1994-1995  Apogee Software, Ltd.
Copyright (C) 2002-2015  icculus.org, GNU/Linux port
Copyright (C) 2017-2018  Steven LeVesque

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
/**********************************************************************
   file:   DMA.H

   author: James R. Dose
   date:   February 4, 1994

   Public header file for DMA.C

   (c) Copyright 1994 James R. Dose.  All Rights Reserved.
**********************************************************************/

#ifndef __DMA_H
#define __DMA_H

enum DMA_ERRORS
   {
   DMA_Error = -1,
   DMA_Ok    = 0,
   DMA_ChannelOutOfRange,
   DMA_InvalidChannel
   };

enum DMA_Modes
   {
   DMA_SingleShotRead,
   DMA_SingleShotWrite,
   DMA_AutoInitRead,
   DMA_AutoInitWrite
   };

char *DMA_ErrorString
   (
   int ErrorNumber
   );

int DMA_VerifyChannel
   (
   int channel
   );

int DMA_SetupTransfer
   (
   int  channel,
   char *address,
   int  length,
   int  mode
   );

int DMA_EndTransfer
   (
   int channel
   );

char *DMA_GetCurrentPos
   (
   int channel
   );

int DMA_GetTransferCount
   (
   int channel
   );

#endif
