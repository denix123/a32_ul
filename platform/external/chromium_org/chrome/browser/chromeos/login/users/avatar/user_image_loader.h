// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_USERS_AVATAR_USER_IMAGE_LOADER_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_USERS_AVATAR_USER_IMAGE_LOADER_H_

#include <map>
#include <string>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "chrome/browser/image_decoder.h"

class SkBitmap;

namespace base {
class SequencedTaskRunner;
}

namespace user_manager {
class UserImage;
}

namespace chromeos {

class UserImageLoader : public base::RefCountedThreadSafe<UserImageLoader>,
                        public ImageDecoder::Delegate {
 public:
  
  typedef base::Callback<void(const user_manager::UserImage& user_image)>
      LoadedCallback;

  
  UserImageLoader(
      ImageDecoder::ImageCodec image_codec,
      scoped_refptr<base::SequencedTaskRunner> background_task_runner);

  
  
  
  
  
  
  void Start(const std::string& filepath,
             int pixels_per_side,
             const LoadedCallback& loaded_cb);
  void Start(scoped_ptr<std::string> data,
             int pixels_per_side,
             const LoadedCallback& loaded_cb);

 private:
  friend class base::RefCountedThreadSafe<UserImageLoader>;

  
  struct ImageInfo {
    ImageInfo(const std::string& file_path,
              int pixels_per_side,
              const LoadedCallback& loaded_cb);
    ~ImageInfo();

    const std::string file_path;
    const int pixels_per_side;
    const LoadedCallback loaded_cb;
  };

  typedef std::map<const ImageDecoder*, ImageInfo> ImageInfoMap;

  virtual ~UserImageLoader();

  
  
  void ReadAndDecodeImage(const ImageInfo& image_info);

  
  
  void DecodeImage(const scoped_ptr<std::string> data,
                   const ImageInfo& image_info);

  
  
  virtual void OnImageDecoded(const ImageDecoder* decoder,
                              const SkBitmap& decoded_image) OVERRIDE;
  virtual void OnDecodeImageFailed(const ImageDecoder* decoder) OVERRIDE;

  
  
  scoped_refptr<base::SequencedTaskRunner> foreground_task_runner_;

  
  
  scoped_refptr<base::SequencedTaskRunner> background_task_runner_;

  
  const ImageDecoder::ImageCodec image_codec_;

  
  
  ImageInfoMap image_info_map_;

  DISALLOW_COPY_AND_ASSIGN(UserImageLoader);
};

}  

#endif  
