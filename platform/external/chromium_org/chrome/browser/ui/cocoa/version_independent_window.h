// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_VERSION_INDEPENDENT_WINDOW_H_
#define CHROME_BROWSER_UI_COCOA_VERSION_INDEPENDENT_WINDOW_H_

#import "chrome/browser/ui/cocoa/chrome_event_processing_window.h"

#include "base/mac/scoped_nsobject.h"

@interface NSWindow (VersionIndependentWindow)

- (NSView*)cr_windowView;

@end

@interface VersionIndependentWindow : ChromeEventProcessingWindow {
 @private
  
  
  
  base::scoped_nsobject<NSView> chromeWindowView_;
}

- (instancetype)initWithContentRect:(NSRect)contentRect
                          styleMask:(NSUInteger)windowStyle
                            backing:(NSBackingStoreType)bufferingType
                              defer:(BOOL)deferCreation;

@end

#endif  
