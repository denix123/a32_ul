// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef MOJO_PUBLIC_C_SYSTEM_FUNCTIONS_H_
#define MOJO_PUBLIC_C_SYSTEM_FUNCTIONS_H_


#include "mojo/public/c/system/system_export.h"
#include "mojo/public/c/system/types.h"

#ifdef __cplusplus
extern "C" {
#endif


MOJO_SYSTEM_EXPORT MojoTimeTicks MojoGetTimeTicksNow(void);

MOJO_SYSTEM_EXPORT MojoResult MojoClose(MojoHandle handle);

MOJO_SYSTEM_EXPORT MojoResult MojoWait(MojoHandle handle,
                                       MojoHandleSignals signals,
                                       MojoDeadline deadline);

MOJO_SYSTEM_EXPORT MojoResult MojoWaitMany(const MojoHandle* handles,
                                           const MojoHandleSignals* signals,
                                           uint32_t num_handles,
                                           MojoDeadline deadline);

#ifdef __cplusplus
}  
#endif

#endif  
