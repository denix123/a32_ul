// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_IOS_UIKIT_UTIL_H_
#define UI_IOS_UIKIT_UTIL_H_

#import <UIKit/UIKit.h>

#include "base/compiler_specific.h"


namespace ui {

CGFloat AlignValueToUpperPixel(CGFloat value) WARN_UNUSED_RESULT;

CGSize AlignSizeToUpperPixel(CGSize size) WARN_UNUSED_RESULT;

} 

#endif  
