/* Copyright (c) 2012 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "ppapi/c/pp_var.h"


void InitializeMessageQueue();
int EnqueueMessage(struct PP_Var message);
struct PP_Var DequeueMessage();

#endif 
