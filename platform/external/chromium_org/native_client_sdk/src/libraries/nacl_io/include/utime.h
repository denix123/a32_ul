/* Copyright 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file. */

#include_next <utime.h>

#ifndef LIBRARIES_NACL_IO_INCLUDE_UTIME_H_
#define LIBRARIES_NACL_IO_INCLUDE_UTIME_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

int utime(const char* filename, const struct utimbuf* times);

__END_DECLS

#endif  
