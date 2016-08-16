// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_ACCESSIBILITY_ACCESSIBILITY_MANAGER_H_
#define CHROME_BROWSER_CHROMEOS_ACCESSIBILITY_ACCESSIBILITY_MANAGER_H_

#include <set>

#include "ash/accessibility_delegate.h"
#include "ash/session/session_state_observer.h"
#include "base/callback_forward.h"
#include "base/callback_list.h"
#include "base/memory/weak_ptr.h"
#include "base/prefs/pref_change_registrar.h"
#include "base/scoped_observer.h"
#include "base/time/time.h"
#include "chrome/browser/chromeos/accessibility/accessibility_util.h"
#include "chrome/browser/extensions/api/braille_display_private/braille_controller.h"
#include "chromeos/ime/input_method_manager.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "extensions/browser/event_router.h"
#include "extensions/browser/extension_system.h"

namespace content {
class RenderViewHost;
}
class Profile;

namespace chromeos {

enum AccessibilityNotificationType {
  ACCESSIBILITY_MANAGER_SHUTDOWN,
  ACCESSIBILITY_TOGGLE_HIGH_CONTRAST_MODE,
  ACCESSIBILITY_TOGGLE_LARGE_CURSOR,
  ACCESSIBILITY_TOGGLE_SCREEN_MAGNIFIER,
  ACCESSIBILITY_TOGGLE_SPOKEN_FEEDBACK,
  ACCESSIBILITY_TOGGLE_VIRTUAL_KEYBOARD,
  ACCESSIBILITY_BRAILLE_DISPLAY_CONNECTION_STATE_CHANGED
};

struct AccessibilityStatusEventDetails {
  AccessibilityStatusEventDetails(
      AccessibilityNotificationType notification_type,
      bool enabled,
      ash::AccessibilityNotificationVisibility notify);

  AccessibilityStatusEventDetails(
      AccessibilityNotificationType notification_type,
      bool enabled,
      ash::MagnifierType magnifier_type,
      ash::AccessibilityNotificationVisibility notify);

  AccessibilityNotificationType notification_type;
  bool enabled;
  ash::MagnifierType magnifier_type;
  ash::AccessibilityNotificationVisibility notify;
};

typedef base::Callback<void(const AccessibilityStatusEventDetails&)>
    AccessibilityStatusCallback;

typedef base::CallbackList<void(const AccessibilityStatusEventDetails&)>
    AccessibilityStatusCallbackList;

typedef AccessibilityStatusCallbackList::Subscription
    AccessibilityStatusSubscription;

class AccessibilityManager
    : public content::NotificationObserver,
      public extensions::api::braille_display_private::BrailleObserver,
      public input_method::InputMethodManager::Observer,
      public ash::SessionStateObserver {
 public:
  
  
  static void Initialize();
  
  static void Shutdown();
  
  static AccessibilityManager* Get();

  
  
  
  
  class PrefHandler {
   public:
    explicit PrefHandler(const char* pref_path);
    virtual ~PrefHandler();

    
    void HandleProfileChanged(Profile* previous_profile,
                              Profile* current_profile);

   private:
    const char* pref_path_;

    DISALLOW_COPY_AND_ASSIGN(PrefHandler);
  };

  
  bool ShouldShowAccessibilityMenu();

  
  bool ShouldEnableCursorCompositing();

  
  void EnableLargeCursor(bool enabled);
  
  bool IsLargeCursorEnabled();

  
  void EnableStickyKeys(bool enabled);

  
  bool IsIncognitoAllowed();

  
  bool IsStickyKeysEnabled();

  
  
  void EnableSpokenFeedback(bool enabled,
                            ash::AccessibilityNotificationVisibility notify);

  
  bool IsSpokenFeedbackEnabled();

  
  void ToggleSpokenFeedback(ash::AccessibilityNotificationVisibility notify);

  
  void EnableHighContrast(bool enabled);

  
  bool IsHighContrastEnabled();

  
  void EnableAutoclick(bool enabled);

  
  bool IsAutoclickEnabled();

  
  void SetAutoclickDelay(int delay_ms);

  
  int GetAutoclickDelay() const;

  
  void EnableVirtualKeyboard(bool enabled);
  
  bool IsVirtualKeyboardEnabled();

  
  
  bool IsBrailleDisplayConnected() const;

  
  virtual void ActiveUserChanged(const std::string& user_id) OVERRIDE;

  void SetProfileForTest(Profile* profile);

  static void SetBrailleControllerForTest(
      extensions::api::braille_display_private::BrailleController* controller);

  
  void EnableSystemSounds(bool system_sounds_enabled);

  
  base::TimeDelta PlayShutdownSound();

  
  void InjectChromeVox(content::RenderViewHost* render_view_host);

  
  
  scoped_ptr<AccessibilityStatusSubscription> RegisterCallback(
      const AccessibilityStatusCallback& cb);

  
  void NotifyAccessibilityStatusChanged(
      AccessibilityStatusEventDetails& details);

  
  void OnLocaleChanged();

  
  
  
  void PlayEarcon(int sound_key);

 protected:
  AccessibilityManager();
  virtual ~AccessibilityManager();

 private:
  void LoadChromeVox();
  void LoadChromeVoxToUserScreen(const base::Closure& done_cb);
  void LoadChromeVoxToLockScreen(const base::Closure& done_cb);
  void UnloadChromeVox();
  void UnloadChromeVoxFromLockScreen();
  void PostLoadChromeVox(Profile* profile);
  void PostUnloadChromeVox(Profile* profile);

  void UpdateLargeCursorFromPref();
  void UpdateStickyKeysFromPref();
  void UpdateSpokenFeedbackFromPref();
  void UpdateHighContrastFromPref();
  void UpdateAutoclickFromPref();
  void UpdateAutoclickDelayFromPref();
  void UpdateVirtualKeyboardFromPref();

  void CheckBrailleState();
  void ReceiveBrailleDisplayState(
      scoped_ptr<extensions::api::braille_display_private::DisplayState> state);
  void UpdateBrailleImeState();

  void SetProfile(Profile* profile);

  void UpdateChromeOSAccessibilityHistograms();

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  
  virtual void OnBrailleDisplayStateChanged(
      const extensions::api::braille_display_private::DisplayState&
          display_state) OVERRIDE;
  virtual void OnBrailleKeyEvent(
      const extensions::api::braille_display_private::KeyEvent& event) OVERRIDE;

  
  virtual void InputMethodChanged(input_method::InputMethodManager* manager,
                                  bool show_message) OVERRIDE;


  
  Profile* profile_;

  
  
  bool chrome_vox_loaded_on_lock_screen_;
  bool chrome_vox_loaded_on_user_screen_;

  content::NotificationRegistrar notification_registrar_;
  scoped_ptr<PrefChangeRegistrar> pref_change_registrar_;
  scoped_ptr<PrefChangeRegistrar> local_state_pref_change_registrar_;
  scoped_ptr<ash::ScopedSessionStateObserver> session_state_observer_;

  PrefHandler large_cursor_pref_handler_;
  PrefHandler spoken_feedback_pref_handler_;
  PrefHandler high_contrast_pref_handler_;
  PrefHandler autoclick_pref_handler_;
  PrefHandler autoclick_delay_pref_handler_;
  PrefHandler virtual_keyboard_pref_handler_;

  bool large_cursor_enabled_;
  bool sticky_keys_enabled_;
  bool spoken_feedback_enabled_;
  bool high_contrast_enabled_;
  bool autoclick_enabled_;
  int autoclick_delay_ms_;
  bool virtual_keyboard_enabled_;

  ash::AccessibilityNotificationVisibility spoken_feedback_notification_;

  bool should_speak_chrome_vox_announcements_on_user_screen_;

  bool system_sounds_enabled_;

  AccessibilityStatusCallbackList callback_list_;

  bool braille_display_connected_;
  ScopedObserver<extensions::api::braille_display_private::BrailleController,
                 AccessibilityManager> scoped_braille_observer_;

  bool braille_ime_current_;

  base::WeakPtrFactory<AccessibilityManager> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(AccessibilityManager);
};

}  

#endif  
