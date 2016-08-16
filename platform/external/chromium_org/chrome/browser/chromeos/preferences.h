// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_PREFERENCES_H_
#define CHROME_BROWSER_CHROMEOS_PREFERENCES_H_

#include <string>
#include <vector>

#include "ash/shell_observer.h"
#include "base/compiler_specific.h"
#include "base/prefs/pref_member.h"
#include "chrome/browser/chromeos/language_preferences.h"
#include "chrome/browser/prefs/pref_service_syncable_observer.h"
#include "chromeos/ime/input_method_manager.h"
#include "components/user_manager/user_manager.h"

class PrefRegistrySimple;
class PrefService;
class PrefServiceSyncable;

class TracingManager;

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace chromeos {

class User;

namespace input_method {
class InputMethodManager;
}

class Preferences : public PrefServiceSyncableObserver,
                    public ash::ShellObserver,
                    public user_manager::UserManager::UserSessionStateObserver {
 public:
  Preferences();
  explicit Preferences(
      input_method::InputMethodManager* input_method_manager);  
  virtual ~Preferences();

  
  static void RegisterPrefs(PrefRegistrySimple* registry);
  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

  
  
  void Init(Profile* profile, const user_manager::User* user);

  void InitUserPrefsForTesting(
      PrefServiceSyncable* prefs,
      const user_manager::User* user,
      scoped_refptr<input_method::InputMethodManager::State> ime_state);
  void SetInputMethodListForTesting();

 private:
  enum ApplyReason {
    REASON_INITIALIZATION,
    REASON_ACTIVE_USER_CHANGED,
    REASON_PREF_CHANGED
  };

  
  void InitUserPrefs(PrefServiceSyncable* prefs);

  
  void OnPreferenceChanged(const std::string& pref_name);

  
  
  
  
  
  void ApplyPreferences(ApplyReason reason,
                        const std::string& pref_name);

  
  
  void SetLanguageConfigStringListAsCSV(const char* section,
                                        const char* name,
                                        const std::string& value);

  
  void SetInputMethodList();

  
  
  
  void UpdateAutoRepeatRate();

  
  
  void ForceNaturalScrollDefault();

  
  virtual void OnIsSyncingChanged() OVERRIDE;

  
  virtual void OnTouchHudProjectionToggled(bool enabled) OVERRIDE;

  
  virtual void ActiveUserChanged(
      const user_manager::User* active_user) OVERRIDE;

  void ActivateInputMethods(const user_manager::User* active_user);

  PrefServiceSyncable* prefs_;

  input_method::InputMethodManager* input_method_manager_;
  scoped_ptr<TracingManager> tracing_manager_;

  BooleanPrefMember performance_tracing_enabled_;
  BooleanPrefMember tap_to_click_enabled_;
  BooleanPrefMember tap_dragging_enabled_;
  BooleanPrefMember three_finger_click_enabled_;
  BooleanPrefMember natural_scroll_;
  BooleanPrefMember vert_edge_scroll_enabled_;
  IntegerPrefMember speed_factor_;
  IntegerPrefMember mouse_sensitivity_;
  IntegerPrefMember touchpad_sensitivity_;
  BooleanPrefMember primary_mouse_button_right_;
  FilePathPrefMember download_default_directory_;
  BooleanPrefMember touch_hud_projection_enabled_;

  
  StringPrefMember preload_engines_;
  StringPrefMember current_input_method_;
  StringPrefMember previous_input_method_;
  StringPrefMember enabled_extension_imes_;

  BooleanPrefMember xkb_auto_repeat_enabled_;
  IntegerPrefMember xkb_auto_repeat_delay_pref_;
  IntegerPrefMember xkb_auto_repeat_interval_pref_;

  
  const user_manager::User* user_;

  
  bool user_is_primary_;

  
  scoped_refptr<input_method::InputMethodManager::State> ime_state_;

  DISALLOW_COPY_AND_ASSIGN(Preferences);
};

}  

#endif  
