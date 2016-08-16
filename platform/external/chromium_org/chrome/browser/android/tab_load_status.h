// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef DEFINE_TAB_LOAD_STATUS
#error "Please define DEFINE_TAB_LOAD_STATUS before including this file."
#endif

DEFINE_TAB_LOAD_STATUS(PAGE_LOAD_FAILED, 0)
DEFINE_TAB_LOAD_STATUS(DEFAULT_PAGE_LOAD, 1)
DEFINE_TAB_LOAD_STATUS(PARTIAL_PRERENDERED_PAGE_LOAD, 2)
DEFINE_TAB_LOAD_STATUS(FULL_PRERENDERED_PAGE_LOAD, 3)
