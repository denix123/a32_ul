// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_USERS_AVATAR_USER_IMAGE_MANAGER_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_USERS_AVATAR_USER_IMAGE_MANAGER_H_

#include <string>

#include "components/user_manager/user.h"

class PrefRegistrySimple;

namespace base {
class FilePath;
}

namespace gfx {
class ImageSkia;
}

namespace user_manager {
class UserImage;
}

namespace chromeos {

class UserImageSyncObserver;

class UserImageManager {
 public:
  
  static void RegisterPrefs(PrefRegistrySimple* registry);

  explicit UserImageManager(const std::string& user_id);
  virtual ~UserImageManager();

  
  virtual void LoadUserImage() = 0;

  
  virtual void UserLoggedIn(bool user_is_new, bool user_is_local) = 0;

  
  
  virtual void SaveUserDefaultImageIndex(int image_index) = 0;

  
  
  virtual void SaveUserImage(const user_manager::UserImage& user_image) = 0;

  
  
  virtual void SaveUserImageFromFile(const base::FilePath& path) = 0;

  
  
  
  
  
  virtual void SaveUserImageFromProfileImage() = 0;

  
  virtual void DeleteUserImage() = 0;

  
  
  
  
  virtual void DownloadProfileImage(const std::string& reason) = 0;

  
  
  virtual const gfx::ImageSkia& DownloadedProfileImage() const = 0;

  
  
  virtual UserImageSyncObserver* GetSyncObserver() const = 0;

  
  
  virtual void Shutdown() = 0;

  
  virtual void OnExternalDataSet(const std::string& policy) = 0;

  
  virtual void OnExternalDataCleared(const std::string& policy) = 0;

  
  
  
  
  
  virtual void OnExternalDataFetched(const std::string& policy,
                                     scoped_ptr<std::string> data) = 0;

 protected:
  const std::string& user_id() const { return user_id_; }

  
  
  const std::string user_id_;
};

}  

#endif  
