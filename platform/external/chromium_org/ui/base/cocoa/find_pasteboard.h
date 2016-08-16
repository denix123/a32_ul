// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_COCOA_FIND_PASTEBOARD_H_
#define UI_BASE_COCOA_FIND_PASTEBOARD_H_

#include "base/strings/string16.h"

#ifdef __OBJC__

#import <Cocoa/Cocoa.h>

#include "base/mac/scoped_nsobject.h"
#include "ui/base/ui_base_export.h"

UI_BASE_EXPORT extern NSString* kFindPasteboardChangedNotification;

UI_BASE_EXPORT
@interface FindPasteboard : NSObject {
 @private
  base::scoped_nsobject<NSString> findText_;
}

+ (FindPasteboard*)sharedInstance;

- (NSString*)findText;

- (void)setFindText:(NSString*)newText;
@end

@interface FindPasteboard (TestingAPI)
- (void)loadTextFromPasteboard:(NSNotification*)notification;

- (NSPasteboard*)findPboard;
@end

#endif  

UI_BASE_EXPORT base::string16 GetFindPboardText();

#endif  
