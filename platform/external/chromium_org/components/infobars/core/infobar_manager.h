// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_INFOBARS_CORE_INFOBAR_MANAGER_H_
#define COMPONENTS_INFOBARS_CORE_INFOBAR_MANAGER_H_

#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "components/infobars/core/infobar_delegate.h"

namespace content {
class WebContents;
}

namespace infobars {

class InfoBar;

class InfoBarManager {
 public:
  
  class Observer {
   public:
    virtual void OnInfoBarAdded(InfoBar* infobar);
    virtual void OnInfoBarRemoved(InfoBar* infobar, bool animate);
    virtual void OnInfoBarReplaced(InfoBar* old_infobar,
                                   InfoBar* new_infobar);
    virtual void OnManagerShuttingDown(InfoBarManager* manager);
  };

  InfoBarManager();
  virtual ~InfoBarManager();

  
  
  
  void ShutDown();

  
  
  
  
  
  
  
  
  InfoBar* AddInfoBar(scoped_ptr<InfoBar> infobar);

  
  
  
  
  
  
  void RemoveInfoBar(InfoBar* infobar);

  
  void RemoveAllInfoBars(bool animate);

  
  
  
  
  
  
  
  
  
  InfoBar* ReplaceInfoBar(InfoBar* old_infobar,
                          scoped_ptr<InfoBar> new_infobar);

  
  size_t infobar_count() const { return infobars_.size(); }

  
  
  
  
  InfoBar* infobar_at(size_t index) { return infobars_[index]; }

  
  void OnNavigation(const InfoBarDelegate::NavigationDetails& details);

  void AddObserver(Observer* obs);
  void RemoveObserver(Observer* obs);

  
  virtual int GetActiveEntryID() = 0;

 protected:
  
  
  
  virtual void NotifyInfoBarAdded(InfoBar* infobar);
  virtual void NotifyInfoBarRemoved(InfoBar* infobar, bool animate);

 private:
  
  
  
  
  
  typedef std::vector<InfoBar*> InfoBars;

  void RemoveInfoBarInternal(InfoBar* infobar, bool animate);

  InfoBars infobars_;
  bool infobars_enabled_;

  ObserverList<Observer, true> observer_list_;

  DISALLOW_COPY_AND_ASSIGN(InfoBarManager);
};

}  

#endif  
