// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include "ipc/ipc_message_macros.h"

#define IPC_MESSAGE_START NaClHostMsgStart

IPC_SYNC_MESSAGE_CONTROL1_0(NaClRendererMsg_ReportExitStatus,
                            int )
