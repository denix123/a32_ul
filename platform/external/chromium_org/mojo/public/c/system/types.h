// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef MOJO_PUBLIC_C_SYSTEM_TYPES_H_
#define MOJO_PUBLIC_C_SYSTEM_TYPES_H_

#include <stdint.h>

#include "mojo/public/c/system/macros.h"



typedef int64_t MojoTimeTicks;


typedef uint32_t MojoHandle;

#ifdef __cplusplus
const MojoHandle MOJO_HANDLE_INVALID = 0;
#else
#define MOJO_HANDLE_INVALID ((MojoHandle)0)
#endif


typedef int32_t MojoResult;

#ifdef __cplusplus
const MojoResult MOJO_RESULT_OK = 0;
const MojoResult MOJO_RESULT_CANCELLED = -1;
const MojoResult MOJO_RESULT_UNKNOWN = -2;
const MojoResult MOJO_RESULT_INVALID_ARGUMENT = -3;
const MojoResult MOJO_RESULT_DEADLINE_EXCEEDED = -4;
const MojoResult MOJO_RESULT_NOT_FOUND = -5;
const MojoResult MOJO_RESULT_ALREADY_EXISTS = -6;
const MojoResult MOJO_RESULT_PERMISSION_DENIED = -7;
const MojoResult MOJO_RESULT_RESOURCE_EXHAUSTED = -8;
const MojoResult MOJO_RESULT_FAILED_PRECONDITION = -9;
const MojoResult MOJO_RESULT_ABORTED = -10;
const MojoResult MOJO_RESULT_OUT_OF_RANGE = -11;
const MojoResult MOJO_RESULT_UNIMPLEMENTED = -12;
const MojoResult MOJO_RESULT_INTERNAL = -13;
const MojoResult MOJO_RESULT_UNAVAILABLE = -14;
const MojoResult MOJO_RESULT_DATA_LOSS = -15;
const MojoResult MOJO_RESULT_BUSY = -16;
const MojoResult MOJO_RESULT_SHOULD_WAIT = -17;
#else
#define MOJO_RESULT_OK ((MojoResult)0)
#define MOJO_RESULT_CANCELLED ((MojoResult) - 1)
#define MOJO_RESULT_UNKNOWN ((MojoResult) - 2)
#define MOJO_RESULT_INVALID_ARGUMENT ((MojoResult) - 3)
#define MOJO_RESULT_DEADLINE_EXCEEDED ((MojoResult) - 4)
#define MOJO_RESULT_NOT_FOUND ((MojoResult) - 5)
#define MOJO_RESULT_ALREADY_EXISTS ((MojoResult) - 6)
#define MOJO_RESULT_PERMISSION_DENIED ((MojoResult) - 7)
#define MOJO_RESULT_RESOURCE_EXHAUSTED ((MojoResult) - 8)
#define MOJO_RESULT_FAILED_PRECONDITION ((MojoResult) - 9)
#define MOJO_RESULT_ABORTED ((MojoResult) - 10)
#define MOJO_RESULT_OUT_OF_RANGE ((MojoResult) - 11)
#define MOJO_RESULT_UNIMPLEMENTED ((MojoResult) - 12)
#define MOJO_RESULT_INTERNAL ((MojoResult) - 13)
#define MOJO_RESULT_UNAVAILABLE ((MojoResult) - 14)
#define MOJO_RESULT_DATA_LOSS ((MojoResult) - 15)
#define MOJO_RESULT_BUSY ((MojoResult) - 16)
#define MOJO_RESULT_SHOULD_WAIT ((MojoResult) - 17)
#endif


typedef uint64_t MojoDeadline;

#ifdef __cplusplus
const MojoDeadline MOJO_DEADLINE_INDEFINITE = static_cast<MojoDeadline>(-1);
#else
#define MOJO_DEADLINE_INDEFINITE ((MojoDeadline) - 1)
#endif


typedef uint32_t MojoHandleSignals;

#ifdef __cplusplus
const MojoHandleSignals MOJO_HANDLE_SIGNAL_NONE = 0;
const MojoHandleSignals MOJO_HANDLE_SIGNAL_READABLE = 1 << 0;
const MojoHandleSignals MOJO_HANDLE_SIGNAL_WRITABLE = 1 << 1;
#else
#define MOJO_HANDLE_SIGNAL_NONE ((MojoHandleSignals)0)
#define MOJO_HANDLE_SIGNAL_READABLE ((MojoHandleSignals)1 << 0)
#define MOJO_HANDLE_SIGNAL_WRITABLE ((MojoHandleSignals)1 << 1)
#endif

MOJO_COMPILE_ASSERT(MOJO_ALIGNOF(int32_t) == 4, int32_t_has_weird_alignment);
struct MOJO_ALIGNAS(4) MojoHandleSignalsState {
  MojoHandleSignals satisfied_signals;
  MojoHandleSignals satisfiable_signals;
};
MOJO_COMPILE_ASSERT(sizeof(MojoHandleSignalsState) == 8,
                    MojoHandleSignalsState_has_wrong_size);

#endif  
