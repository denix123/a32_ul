// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_IOS_NSSTRING_CR_STRING_DRAWING_H_
#define UI_IOS_NSSTRING_CR_STRING_DRAWING_H_

#import <UIKit/UIKit.h>

@interface NSString (CrStringDrawing)

- (CGSize)cr_pixelAlignedSizeWithFont:(UIFont*)font;

- (CGSize)cr_sizeWithFont:(UIFont*)font;

@end

#endif  
