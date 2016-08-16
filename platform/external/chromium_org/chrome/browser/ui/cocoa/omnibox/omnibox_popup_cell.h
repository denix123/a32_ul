// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_OMNIBOX_OMNIBOX_POPUP_CELL_H_
#define CHROME_BROWSER_UI_COCOA_OMNIBOX_OMNIBOX_POPUP_CELL_H_

#import <Cocoa/Cocoa.h>

#include "base/mac/scoped_nsobject.h"
#include "components/omnibox/autocomplete_match.h"

class OmniboxPopupViewMac;

@interface OmniboxPopupCell : NSButtonCell {
 @private
  
  OmniboxPopupViewMac* parent_;

  
  AutocompleteMatch match_;

  
  base::scoped_nsobject<NSAttributedString> separator_;
  base::scoped_nsobject<NSAttributedString> description_;

  
  
  
  
  base::scoped_nsobject<NSAttributedString> prefix_;

  
  CGFloat maxMatchContentsWidth_;

  
  CGFloat contentsOffset_;
}

- (void)setMatch:(const AutocompleteMatch&)match;

- (void)setMaxMatchContentsWidth:(CGFloat)maxMatchContentsWidth;

- (void)setContentsOffset:(CGFloat)contentsOffset;

- (CGFloat)getMatchContentsWidth;

+ (CGFloat)computeContentsOffset:(const AutocompleteMatch&)match;

@end

#endif  
