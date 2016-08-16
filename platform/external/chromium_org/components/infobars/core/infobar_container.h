// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_INFOBARS_CORE_INFOBAR_CONTAINER_H_
#define COMPONENTS_INFOBARS_CORE_INFOBAR_CONTAINER_H_

#include <vector>

#include "base/compiler_specific.h"
#include "base/time/time.h"
#include "components/infobars/core/infobar_manager.h"
#include "third_party/skia/include/core/SkColor.h"

namespace infobars {

class InfoBar;

class InfoBarContainer : public InfoBarManager::Observer {
 public:
  class Delegate {
   public:
    
    virtual SkColor GetInfoBarSeparatorColor() const = 0;

    
    
    virtual void InfoBarContainerStateChanged(bool is_animating) = 0;

    
    
    virtual bool DrawInfoBarArrows(int* x) const = 0;

   protected:
    virtual ~Delegate();
  };

  explicit InfoBarContainer(Delegate* delegate);
  virtual ~InfoBarContainer();

  
  
  
  
  void ChangeInfoBarManager(InfoBarManager* infobar_manager);

  
  
  
  int GetVerticalOverlap(int* total_height) const;

  
  
  
  
  
  
  
  
  
  void SetMaxTopArrowHeight(int height);

  
  
  
  void OnInfoBarStateChanged(bool is_animating);

  
  
  void RemoveInfoBar(InfoBar* infobar);

  const Delegate* delegate() const { return delegate_; }

 protected:
  
  
  
  void RemoveAllInfoBarsForDestruction();

  
  
  
  
  virtual void PlatformSpecificAddInfoBar(InfoBar* infobar,
                                          size_t position) = 0;
  
  
  
  virtual void PlatformSpecificReplaceInfoBar(InfoBar* old_infobar,
                                              InfoBar* new_infobar) {}
  virtual void PlatformSpecificRemoveInfoBar(InfoBar* infobar) = 0;
  virtual void PlatformSpecificInfoBarStateChanged(bool is_animating) {}

 private:
  typedef std::vector<InfoBar*> InfoBars;

  
  virtual void OnInfoBarAdded(InfoBar* infobar) OVERRIDE;
  virtual void OnInfoBarRemoved(InfoBar* infobar, bool animate) OVERRIDE;
  virtual void OnInfoBarReplaced(InfoBar* old_infobar,
                                 InfoBar* new_infobar) OVERRIDE;
  virtual void OnManagerShuttingDown(InfoBarManager* manager) OVERRIDE;

  
  
  
  
  
  enum CallbackStatus { NO_CALLBACK, WANT_CALLBACK };
  void AddInfoBar(InfoBar* infobar,
                  size_t position,
                  bool animate,
                  CallbackStatus callback_status);

  void UpdateInfoBarArrowTargetHeights();
  int ArrowTargetHeightForInfoBar(size_t infobar_index) const;

  Delegate* delegate_;
  InfoBarManager* infobar_manager_;
  InfoBars infobars_;

  
  int top_arrow_target_height_;

  DISALLOW_COPY_AND_ASSIGN(InfoBarContainer);
};

}  

#endif  
