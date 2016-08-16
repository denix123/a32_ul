// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_JUMPLIST_WIN_H_
#define CHROME_BROWSER_JUMPLIST_WIN_H_

#include <list>
#include <string>
#include <utility>
#include <vector>

#include "base/files/file_path.h"
#include "base/memory/weak_ptr.h"
#include "base/synchronization/lock.h"
#include "base/task/cancelable_task_tracker.h"
#include "chrome/browser/history/history_service.h"
#include "chrome/browser/jumplist_updater_win.h"
#include "chrome/browser/prefs/incognito_mode_prefs.h"
#include "chrome/browser/sessions/tab_restore_service.h"
#include "chrome/browser/sessions/tab_restore_service_observer.h"
#include "components/history/core/browser/history_types.h"
#include "content/public/browser/browser_thread.h"

namespace chrome {
struct FaviconImageResult;
}

namespace content {
class NotificationRegistrar;
}

class PageUsageData;
class PrefChangeRegistrar;
class Profile;

class JumpList : public TabRestoreServiceObserver,
                 public content::NotificationObserver,
                 public base::RefCountedThreadSafe<
                     JumpList, content::BrowserThread::DeleteOnUIThread> {
 public:
  explicit JumpList(Profile* profile);

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details);

  
  
  virtual void TabRestoreServiceChanged(TabRestoreService* service);

  
  
  virtual void TabRestoreServiceDestroyed(TabRestoreService* service);

  
  void CancelPendingUpdate();

  
  
  
  void Terminate();

  
  
  static bool Enabled();

 private:
  friend struct content::BrowserThread::DeleteOnThread<
      content::BrowserThread::UI>;
  friend class base::DeleteHelper<JumpList>;
  virtual ~JumpList();

  
  
  
  
  bool AddTab(const TabRestoreService::Tab* tab,
              ShellLinkItemList* list,
              size_t max_items);
  void AddWindow(const TabRestoreService::Window* window,
                 ShellLinkItemList* list,
                 size_t max_items);

  
  
  
  
  void StartLoadingFavicon();

  
  
  
  
  void OnFaviconDataAvailable(
      const favicon_base::FaviconImageResult& image_result);

  
  
  
  
  void OnMostVisitedURLsAvailable(
      const history::MostVisitedURLList& data);

  
  void OnIncognitoAvailabilityChanged();

  
  void PostRunUpdate();

  
  
  void RunUpdate(IncognitoModePrefs::Availability incognito_availability);

  
  
  void CreateIconFiles(const ShellLinkItemList& item_list);

  
  base::CancelableTaskTracker cancelable_task_tracker_;

  
  Profile* profile_;

  
  scoped_ptr<content::NotificationRegistrar> registrar_;
  scoped_ptr<PrefChangeRegistrar> pref_change_registrar_;

  
  std::wstring app_id_;

  
  base::FilePath icon_dir_;

  
  
  ShellLinkItemList most_visited_pages_;

  
  
  ShellLinkItemList recently_closed_pages_;

  
  
  typedef std::pair<std::string, scoped_refptr<ShellLinkItem> > URLPair;
  std::list<URLPair> icon_urls_;

  
  
  base::CancelableTaskTracker::TaskId task_id_;

  
  
  base::Lock list_lock_;

  
  base::WeakPtrFactory<JumpList> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(JumpList);
};

#endif  
