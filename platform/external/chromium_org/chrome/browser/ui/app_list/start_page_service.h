// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_APP_LIST_START_PAGE_SERVICE_H_
#define CHROME_BROWSER_UI_APP_LIST_START_PAGE_SERVICE_H_

#include <vector>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/strings/string16.h"
#include "components/keyed_service/core/keyed_service.h"
#include "content/public/browser/web_contents.h"
#include "ui/app_list/speech_ui_model_observer.h"

namespace extensions {
class Extension;
}

class Profile;

namespace app_list {

class RecommendedApps;
class StartPageObserver;

class StartPageService : public KeyedService {
 public:
  typedef std::vector<scoped_refptr<const extensions::Extension> >
      ExtensionList;
  
  static StartPageService* Get(Profile* profile);

  void AddObserver(StartPageObserver* observer);
  void RemoveObserver(StartPageObserver* observer);

  void AppListShown();
  void AppListHidden();
  void ToggleSpeechRecognition();

  
  bool HotwordEnabled();

  
  
  content::WebContents* GetStartPageContents();
  content::WebContents* GetSpeechRecognitionContents();

  RecommendedApps* recommended_apps() { return recommended_apps_.get(); }
  Profile* profile() { return profile_; }
  SpeechRecognitionState state() { return state_; }
  void OnSpeechResult(const base::string16& query, bool is_final);
  void OnSpeechSoundLevelChanged(int16 level);
  void OnSpeechRecognitionStateChanged(SpeechRecognitionState new_state);

 private:
  friend class StartPageServiceFactory;

  
  
  
  class ProfileDestroyObserver;

  
  
  class StartPageWebContentsDelegate;

  explicit StartPageService(Profile* profile);
  virtual ~StartPageService();

  void LoadContents();
  void UnloadContents();

  
  virtual void Shutdown() OVERRIDE;

  Profile* profile_;
  scoped_ptr<content::WebContents> contents_;
  scoped_ptr<StartPageWebContentsDelegate> contents_delegate_;
  scoped_ptr<ProfileDestroyObserver> profile_destroy_observer_;
  scoped_ptr<RecommendedApps> recommended_apps_;
  SpeechRecognitionState state_;
  ObserverList<StartPageObserver> observers_;
  bool speech_button_toggled_manually_;
  bool speech_result_obtained_;

  DISALLOW_COPY_AND_ASSIGN(StartPageService);
};

}  

#endif  
