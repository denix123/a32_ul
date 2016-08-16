// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#import <Cocoa/Cocoa.h>

#include "base/mac/scoped_nsobject.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/translate/chrome_translate_client.h"
#import "chrome/browser/ui/cocoa/base_bubble_controller.h"
#include "components/translate/core/common/translate_errors.h"

@class BrowserWindowController;

class LanguageComboboxModel;
class TranslateBubbleModel;
class TranslateDenialComboboxModel;

namespace content {
class WebContents;
}

@interface TranslateBubbleController : BaseBubbleController {
 @private
  content::WebContents* webContents_;
  scoped_ptr<TranslateBubbleModel> model_;

  
  
  base::scoped_nsobject<NSDictionary> views_;

  
  NSButton* advancedDoneButton_;

  
  NSButton* advancedCancelButton_;

  
  
  NSButton* alwaysTranslateCheckbox_;

  
  
  scoped_ptr<TranslateDenialComboboxModel> translateDenialComboboxModel_;

  
  scoped_ptr<LanguageComboboxModel> sourceLanguageComboboxModel_;

  
  scoped_ptr<LanguageComboboxModel> targetLanguageComboboxModel_;

  
  BOOL translateExecuted_;
}

@property(readonly, nonatomic) const content::WebContents* webContents;
@property(readonly, nonatomic) const TranslateBubbleModel* model;

- (id)initWithParentWindow:(BrowserWindowController*)controller
                     model:(scoped_ptr<TranslateBubbleModel>)model
               webContents:(content::WebContents*)webContents;
- (void)switchView:(TranslateBubbleModel::ViewState)viewState;
- (void)switchToErrorView:(translate::TranslateErrors::Type)errorType;

@end
