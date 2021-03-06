/* Copyright (C) 2007-2008 The Android Open Source Project
**
** This software is licensed under the terms of the GNU General Public
** License version 2, as published by the Free Software Foundation, and
** may be copied, distributed, and modified under those terms.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
*/
#ifndef _ANDROID_UTILS_TIMEZONE_H
#define _ANDROID_UTILS_TIMEZONE_H

#include "android/utils/compiler.h"

ANDROID_BEGIN_HEADER

extern int  timezone_set( const char*  tzname );

extern char*  bufprint_zoneinfo_timezone( char*  buffer, char*  end );

ANDROID_END_HEADER

#endif 
