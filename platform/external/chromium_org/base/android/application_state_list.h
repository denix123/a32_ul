// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef DEFINE_APPLICATION_STATE
#error "DEFINE_APPLICATION_STATE should be defined before including this file"
#endif
DEFINE_APPLICATION_STATE(HAS_RUNNING_ACTIVITIES, 1)
DEFINE_APPLICATION_STATE(HAS_PAUSED_ACTIVITIES, 2)
DEFINE_APPLICATION_STATE(HAS_STOPPED_ACTIVITIES, 3)
DEFINE_APPLICATION_STATE(HAS_DESTROYED_ACTIVITIES, 4)
