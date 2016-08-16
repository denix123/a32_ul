// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_USER_MANAGER_USER_IMAGE_DEFAULT_USER_IMAGES_H_
#define COMPONENTS_USER_MANAGER_USER_IMAGE_DEFAULT_USER_IMAGES_H_

#include <cstddef>  
#include <string>

#include "base/strings/string16.h"
#include "components/user_manager/user_manager_export.h"

namespace gfx {
class ImageSkia;
}

namespace user_manager {

USER_MANAGER_EXPORT std::string GetDefaultImageUrl(int index);

USER_MANAGER_EXPORT bool IsDefaultImageUrl(const std::string& url,
                                           int* image_id);

USER_MANAGER_EXPORT const gfx::ImageSkia& GetDefaultImage(int index);

USER_MANAGER_EXPORT base::string16 GetDefaultImageDescription(int index);

USER_MANAGER_EXPORT extern const int kDefaultImageResourceIDs[];

USER_MANAGER_EXPORT extern const int kDefaultImageAuthorIDs[];

USER_MANAGER_EXPORT extern const int kDefaultImageWebsiteIDs[];

USER_MANAGER_EXPORT extern const int kDefaultImagesCount;

USER_MANAGER_EXPORT extern const int kFirstDefaultImageIndex;


USER_MANAGER_EXPORT extern const int kHistogramImageFromFile;

USER_MANAGER_EXPORT extern const int kHistogramImageFromCamera;

USER_MANAGER_EXPORT extern const int kHistogramImageOld;

USER_MANAGER_EXPORT extern const int kHistogramImageFromProfile;

USER_MANAGER_EXPORT extern const int kHistogramVideoFromCamera;

USER_MANAGER_EXPORT extern const int kHistogramVideoFromFile;

USER_MANAGER_EXPORT extern const int kHistogramImagesCount;

USER_MANAGER_EXPORT int GetDefaultImageHistogramValue(int index);

}  

#endif  
