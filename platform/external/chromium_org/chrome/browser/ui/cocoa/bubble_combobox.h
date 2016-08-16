// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef CHROME_BROWSER_UI_COCOA_BUBBLE_COMBOBOX_H_
#define CHROME_BROWSER_UI_COCOA_BUBBLE_COMBOBOX_H_

#import <Cocoa/Cocoa.h>

namespace ui {
class ComboboxModel;
}  

@interface BubbleCombobox : NSPopUpButton
- (id)initWithFrame:(NSRect)frame
          pullsDown:(BOOL)pullsDown
              model:(ui::ComboboxModel*)model;
@end

#endif  
