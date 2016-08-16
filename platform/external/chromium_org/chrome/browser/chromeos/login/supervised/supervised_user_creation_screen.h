// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_SUPERVISED_SUPERVISED_USER_CREATION_SCREEN_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_SUPERVISED_SUPERVISED_USER_CREATION_SCREEN_H_

#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "chrome/browser/chromeos/camera_presence_notifier.h"
#include "chrome/browser/chromeos/login/screens/wizard_screen.h"
#include "chrome/browser/chromeos/login/supervised/supervised_user_creation_controller.h"
#include "chrome/browser/image_decoder.h"
#include "chrome/browser/supervised_user/supervised_user_sync_service.h"
#include "chrome/browser/ui/webui/chromeos/login/supervised_user_creation_screen_handler.h"
#include "chromeos/network/portal_detector/network_portal_detector.h"
#include "ui/gfx/image/image_skia.h"

class Profile;

namespace chromeos {

class NetworkState;
class ScreenManager;

class SupervisedUserCreationScreen
    : public WizardScreen,
      public SupervisedUserCreationScreenHandler::Delegate,
      public SupervisedUserCreationController::StatusConsumer,
      public SupervisedUserSyncServiceObserver,
      public ImageDecoder::Delegate,
      public NetworkPortalDetector::Observer,
      public CameraPresenceNotifier::Observer {
 public:
  SupervisedUserCreationScreen(
      ScreenObserver* observer,
      SupervisedUserCreationScreenHandler* actor);
  virtual ~SupervisedUserCreationScreen();

  static SupervisedUserCreationScreen* Get(ScreenManager* manager);

  
  
  
  
  void ShowManagerInconsistentStateErrorScreen();

  
  
  void OnManagerLoginFailure();

  
  
  void OnManagerFullyAuthenticated(Profile* manager_profile);

  
  
  
  void OnManagerCryptohomeAuthenticated();

  
  
  void ShowInitialScreen();

  
  virtual void OnCameraPresenceCheckDone(bool is_camera_present) OVERRIDE;

  
  virtual void OnSupervisedUserAcknowledged(
      const std::string& supervised_user_id) OVERRIDE {}
  virtual void OnSupervisedUsersSyncingStopped() OVERRIDE {}
  virtual void OnSupervisedUsersChanged() OVERRIDE;

  
  virtual void PrepareToShow() OVERRIDE;
  virtual void Show() OVERRIDE;
  virtual void Hide() OVERRIDE;
  virtual std::string GetName() const OVERRIDE;

  
  virtual void OnActorDestroyed(SupervisedUserCreationScreenHandler* actor)
      OVERRIDE;
  virtual void CreateSupervisedUser(
      const base::string16& display_name,
      const std::string& supervised_user_password) OVERRIDE;
  virtual void ImportSupervisedUser(const std::string& user_id) OVERRIDE;
  virtual void ImportSupervisedUserWithPassword(
      const std::string& user_id,
      const std::string& password) OVERRIDE;
  virtual void AuthenticateManager(
      const std::string& manager_id,
      const std::string& manager_password) OVERRIDE;
  virtual void AbortFlow() OVERRIDE;
  virtual void FinishFlow() OVERRIDE;
  virtual bool FindUserByDisplayName(const base::string16& display_name,
                                     std::string *out_id) const OVERRIDE;
  virtual void OnPageSelected(const std::string& page) OVERRIDE;

  
  virtual void OnCreationError(SupervisedUserCreationController::ErrorCode code)
      OVERRIDE;
  virtual void OnCreationTimeout() OVERRIDE;
  virtual void OnCreationSuccess() OVERRIDE;
  virtual void OnLongCreationWarning() OVERRIDE;

  
  virtual void OnPortalDetectionCompleted(
          const NetworkState* network,
          const NetworkPortalDetector::CaptivePortalState& state) OVERRIDE;

  
  

  
  virtual void OnPhotoTaken(const std::string& raw_data) OVERRIDE;
  virtual void OnImageSelected(const std::string& image_url,
                               const std::string& image_type) OVERRIDE;
  virtual void OnImageAccepted() OVERRIDE;
  
  virtual void OnImageDecoded(const ImageDecoder* decoder,
                              const SkBitmap& decoded_image) OVERRIDE;
  virtual void OnDecodeImageFailed(const ImageDecoder* decoder) OVERRIDE;

 private:
  void ApplyPicture();
  void OnGetSupervisedUsers(const base::DictionaryValue* users);

  SupervisedUserCreationScreenHandler* actor_;

  scoped_ptr<SupervisedUserCreationController> controller_;
  scoped_ptr<base::DictionaryValue> existing_users_;

  bool on_error_screen_;
  bool manager_signin_in_progress_;
  std::string last_page_;

  SupervisedUserSyncService* sync_service_;

  gfx::ImageSkia user_photo_;
  scoped_refptr<ImageDecoder> image_decoder_;
  bool apply_photo_after_decoding_;
  int selected_image_;

  base::WeakPtrFactory<SupervisedUserCreationScreen> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(SupervisedUserCreationScreen);
};

}  

#endif  

