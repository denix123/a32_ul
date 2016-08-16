// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_APP_LIST_APP_LIST_VIEW_DELEGATE_H_
#define UI_APP_LIST_APP_LIST_VIEW_DELEGATE_H_

#include <string>
#include <vector>

#include "base/callback_forward.h"
#include "base/files/file_path.h"
#include "base/strings/string16.h"
#include "base/time/time.h"
#include "ui/app_list/app_list_export.h"

namespace base {
class FilePath;
}

namespace gfx {
class ImageSkia;
class Size;
}

#if defined(TOOLKIT_VIEWS)
namespace views {
class View;
}
#endif

namespace app_list {

class AppListModel;
class AppListViewDelegateObserver;
class SearchResult;
class SpeechUIModel;

class APP_LIST_EXPORT AppListViewDelegate {
 public:
  
  struct APP_LIST_EXPORT User {
    User();
    ~User();

    
    bool active;

    
    base::string16 name;

    
    base::string16 email;

    
    base::FilePath profile_path;
  };
  typedef std::vector<User> Users;

  
  virtual ~AppListViewDelegate() {}

  
  
  virtual bool ForceNativeDesktop() const = 0;

  
  
  virtual void SetProfileByPath(const base::FilePath& profile_path) = 0;

  
  
  virtual AppListModel* GetModel() = 0;

  
  virtual SpeechUIModel* GetSpeechUI() = 0;

  
  
  virtual void GetShortcutPathForApp(
      const std::string& app_id,
      const base::Callback<void(const base::FilePath&)>& callback) = 0;

  
  
  
  virtual void StartSearch() = 0;

  
  virtual void StopSearch() = 0;

  
  virtual void OpenSearchResult(SearchResult* result,
                                bool auto_launch,
                                int event_flags) = 0;

  
  
  virtual void InvokeSearchResultAction(SearchResult* result,
                                        int action_index,
                                        int event_flags) = 0;

  
  
  virtual base::TimeDelta GetAutoLaunchTimeout() = 0;

  
  virtual void AutoLaunchCanceled() = 0;

  
  virtual void ViewInitialized() = 0;

  
  
  virtual void Dismiss() = 0;

  
  virtual void ViewClosing() = 0;

  
  virtual gfx::ImageSkia GetWindowIcon() = 0;

  
  virtual void OpenSettings() = 0;

  
  virtual void OpenHelp() = 0;

  
  virtual void OpenFeedback() = 0;

  
  virtual void ToggleSpeechRecognition() = 0;

  
  virtual void ShowForProfileByPath(const base::FilePath& profile_path) = 0;

#if defined(TOOLKIT_VIEWS)
  
  
  virtual views::View* CreateStartPageWebView(const gfx::Size& size) = 0;

  
  
  virtual std::vector<views::View*> CreateCustomPageWebViews(
      const gfx::Size& size) = 0;
#endif

  
  virtual bool IsSpeechRecognitionEnabled() = 0;

  
  virtual const Users& GetUsers() const = 0;

  
  virtual bool ShouldCenterWindow() const = 0;

  
  virtual void AddObserver(AppListViewDelegateObserver* observer) {}
  virtual void RemoveObserver(AppListViewDelegateObserver* observer) {}
};

}  

#endif  
