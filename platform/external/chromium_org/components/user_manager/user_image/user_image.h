// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_USER_MANAGER_USER_IMAGE_USER_IMAGE_H_
#define COMPONENTS_USER_MANAGER_USER_IMAGE_USER_IMAGE_H_

#include <string>
#include <vector>

#include "components/user_manager/user_manager_export.h"
#include "ui/gfx/image/image_skia.h"
#include "url/gurl.h"

namespace user_manager {

class USER_MANAGER_EXPORT UserImage {
 public:
  
  typedef std::vector<unsigned char> RawImage;

  
  
  
  static UserImage CreateAndEncode(const gfx::ImageSkia& image);

  
  UserImage();

  
  explicit UserImage(const gfx::ImageSkia& image);

  
  UserImage(const gfx::ImageSkia& image, const RawImage& raw_image);

  virtual ~UserImage();

  const gfx::ImageSkia& image() const { return image_; }

  
  bool has_raw_image() const { return has_raw_image_; }
  const RawImage& raw_image() const { return raw_image_; }

  
  void DiscardRawImage();

  
  void set_url(const GURL& url) { url_ = url; }
  GURL url() const { return url_; }

  
  
  bool is_safe_format() const { return is_safe_format_; }
  void MarkAsSafe();

  const std::string& file_path() const { return file_path_; }
  void set_file_path(const std::string& file_path) { file_path_ = file_path; }

 private:
  gfx::ImageSkia image_;
  bool has_raw_image_;
  RawImage raw_image_;
  GURL url_;

  
  std::string file_path_;
  bool is_safe_format_;
};

}  

#endif  
