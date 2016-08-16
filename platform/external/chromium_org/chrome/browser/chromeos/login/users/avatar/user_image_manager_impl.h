// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_USERS_AVATAR_USER_IMAGE_MANAGER_IMPL_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_USERS_AVATAR_USER_IMAGE_MANAGER_IMPL_H_

#include <map>
#include <set>
#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "base/values.h"
#include "chrome/browser/chromeos/login/users/avatar/user_image_loader.h"
#include "chrome/browser/chromeos/login/users/avatar/user_image_manager.h"
#include "chrome/browser/profiles/profile_downloader_delegate.h"
#include "components/user_manager/user.h"
#include "ui/gfx/image/image_skia.h"

class ProfileDownloader;

namespace base {
class FilePath;
class SequencedTaskRunner;
}

namespace user_manager {
class UserImage;
class UserManager;
}

namespace chromeos {

class UserImageSyncObserver;

class UserImageManagerImpl
    : public UserImageManager,
      public ProfileDownloaderDelegate {
 public:
  
  UserImageManagerImpl(const std::string& user_id,
                       user_manager::UserManager* user_manager);
  virtual ~UserImageManagerImpl();

  virtual void LoadUserImage() OVERRIDE;
  virtual void UserLoggedIn(bool user_is_new, bool user_is_local) OVERRIDE;
  virtual void SaveUserDefaultImageIndex(int default_image_index) OVERRIDE;
  virtual void SaveUserImage(
      const user_manager::UserImage& user_image) OVERRIDE;
  virtual void SaveUserImageFromFile(const base::FilePath& path) OVERRIDE;
  virtual void SaveUserImageFromProfileImage() OVERRIDE;
  virtual void DeleteUserImage() OVERRIDE;
  virtual void DownloadProfileImage(const std::string& reason) OVERRIDE;
  virtual const gfx::ImageSkia& DownloadedProfileImage() const OVERRIDE;
  virtual UserImageSyncObserver* GetSyncObserver() const OVERRIDE;
  virtual void Shutdown() OVERRIDE;

  virtual void OnExternalDataSet(const std::string& policy) OVERRIDE;
  virtual void OnExternalDataCleared(const std::string& policy) OVERRIDE;
  virtual void OnExternalDataFetched(const std::string& policy,
                                     scoped_ptr<std::string> data) OVERRIDE;

  static void IgnoreProfileDataDownloadDelayForTesting();

 private:
  friend class UserImageManagerTest;

  
  
  
  
  
  
  
  
  
  
  
  class Job;

  
  virtual bool NeedsProfilePicture() const OVERRIDE;
  virtual int GetDesiredImageSideLength() const OVERRIDE;
  virtual Profile* GetBrowserProfile() OVERRIDE;
  virtual std::string GetCachedPictureURL() const OVERRIDE;
  virtual void OnProfileDownloadSuccess(ProfileDownloader* downloader) OVERRIDE;
  virtual void OnProfileDownloadFailure(
      ProfileDownloader* downloader,
      ProfileDownloaderDelegate::FailureReason reason) OVERRIDE;

  
  
  bool IsUserImageManaged() const;

  
  
  void SetInitialUserImage();

  
  
  
  void TryToInitDownloadedProfileImage();

  
  
  
  
  
  bool NeedProfileImage() const;

  
  
  
  
  void DownloadProfileData(const std::string& reason);

  
  
  
  void DeleteUserImageAndLocalStateEntry(const char* prefs_dict_root);

  
  
  
  void OnJobChangedUserImage();

  
  
  
  void OnJobDone();

  
  
  void UpdateLocalStateAfterMigration();

  
  
  void TryToCreateImageSyncObserver();

  
  const user_manager::User* GetUser() const;

  
  user_manager::User* GetUserAndModify() const;

  
  bool IsUserLoggedInAndRegular() const;

  
  user_manager::UserManager* user_manager_;

  
  scoped_refptr<UserImageLoader> image_loader_;

  
  scoped_refptr<UserImageLoader> unsafe_image_loader_;

  
  
  
  bool downloading_profile_image_;

  
  
  
  std::string profile_image_download_reason_;

  
  
  base::TimeTicks profile_image_load_start_time_;

  
  
  scoped_ptr<ProfileDownloader> profile_downloader_;

  
  
  gfx::ImageSkia downloaded_profile_image_;

  
  
  std::string downloaded_profile_image_data_url_;

  
  
  GURL profile_image_url_;

  
  
  
  bool profile_image_requested_;

  
  
  base::OneShotTimer<UserImageManagerImpl> profile_download_one_shot_timer_;

  
  
  base::RepeatingTimer<UserImageManagerImpl> profile_download_periodic_timer_;

  
  scoped_ptr<UserImageSyncObserver> user_image_sync_observer_;

  
  
  scoped_refptr<base::SequencedTaskRunner> background_task_runner_;

  
  scoped_ptr<Job> job_;

  bool has_managed_image_;
  bool user_needs_migration_;

  base::WeakPtrFactory<UserImageManagerImpl> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(UserImageManagerImpl);
};

}  

#endif  
