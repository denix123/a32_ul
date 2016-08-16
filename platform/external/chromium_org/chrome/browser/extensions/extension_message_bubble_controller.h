// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_MESSAGE_BUBBLE_CONTROLLER_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_MESSAGE_BUBBLE_CONTROLLER_H_

#include <string>
#include "chrome/browser/extensions/extension_message_bubble.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"
#include "extensions/common/extension.h"

class Browser;
class Profile;

namespace extensions {

class ExtensionPrefs;
class SuspiciousExtensionBubble;

class ExtensionMessageBubbleController {
 public:
  
  enum BubbleAction {
    ACTION_LEARN_MORE = 0,
    ACTION_EXECUTE,
    ACTION_DISMISS,
    ACTION_BOUNDARY, 
  };

  class Delegate {
   public:
    Delegate();
    virtual ~Delegate();

    virtual bool ShouldIncludeExtension(const std::string& extension_id) = 0;
    virtual void AcknowledgeExtension(
        const std::string& extension_id,
        BubbleAction action) = 0;
    virtual void PerformAction(const ExtensionIdList& list) = 0;
    virtual void OnClose() {}

    
    virtual base::string16 GetTitle() const = 0;
    
    
    
    
    
    virtual base::string16 GetMessageBody(
        bool anchored_to_browser_action) const = 0;
    virtual base::string16 GetOverflowText(
        const base::string16& overflow_count) const = 0;
    virtual base::string16 GetLearnMoreLabel() const = 0;
    virtual GURL GetLearnMoreUrl() const = 0;
    virtual base::string16 GetActionButtonLabel() const = 0;
    virtual base::string16 GetDismissButtonLabel() const = 0;

    
    virtual bool ShouldShowExtensionList() const = 0;

    
    
    virtual void RestrictToSingleExtension(const std::string& extension_id);

    
    virtual void LogExtensionCount(size_t count) = 0;
    virtual void LogAction(BubbleAction action) = 0;
  };

  ExtensionMessageBubbleController(Delegate* delegate, Profile* profile);
  virtual ~ExtensionMessageBubbleController();

  Delegate* delegate() const { return delegate_.get(); }

  
  std::vector<base::string16> GetExtensionList();

  
  const ExtensionIdList& GetExtensionIdList();

  
  virtual bool CloseOnDeactivate();

  
  virtual void Show(ExtensionMessageBubble* bubble);

  
  virtual void OnBubbleAction();
  virtual void OnBubbleDismiss();
  virtual void OnLinkClicked();

 private:
  
  void AcknowledgeExtensions();

  
  ExtensionIdList* GetOrCreateExtensionList();

  
  Profile* profile_;

  
  ExtensionIdList extension_list_;

  
  BubbleAction user_action_;

  
  scoped_ptr<Delegate> delegate_;

  
  bool initialized_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionMessageBubbleController);
};

}  

#endif  
