// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PROFILES_PROFILE_AVATAR_ICON_UTIL_H_
#define CHROME_BROWSER_PROFILES_PROFILE_AVATAR_ICON_UTIL_H_

#include <string>

#include "third_party/skia/include/core/SkColor.h"

namespace base {
class FilePath;
}

namespace gfx {
class Image;
}

class SkBitmap;

namespace profiles {

extern const char kGAIAPictureFileName[];
extern const char kHighResAvatarFolderName[];

extern const int kAvatarIconWidth;
extern const int kAvatarIconHeight;
extern const SkColor kAvatarTutorialBackgroundColor;
extern const SkColor kAvatarTutorialContentTextColor;
extern const SkColor kAvatarBubbleAccountsBackgroundColor;

size_t GetDefaultAvatarIconCount();

int GetPlaceholderAvatarIndex();

int GetPlaceholderAvatarIconResourceID();

size_t GetGenericAvatarIconCount();

int GetDefaultAvatarIconResourceIDAtIndex(size_t index);

const char* GetDefaultAvatarIconFileNameAtIndex(size_t index);

const char* GetNoHighResAvatarFileName();

base::FilePath GetPathOfHighResAvatarAtIndex(size_t index);

std::string GetDefaultAvatarIconUrl(size_t index);

bool IsDefaultAvatarIconIndex(size_t index);

bool IsDefaultAvatarIconUrl(const std::string& icon_url, size_t *icon_index);

gfx::Image GetSizedAvatarIcon(const gfx::Image& image,
                              bool is_rectangle,
                              int width, int height);

gfx::Image GetAvatarIconForMenu(const gfx::Image& image,
                                bool is_rectangle);

gfx::Image GetAvatarIconForWebUI(const gfx::Image& image,
                                 bool is_rectangle);

gfx::Image GetAvatarIconForTitleBar(const gfx::Image& image,
                                    bool is_rectangle,
                                    int dst_width,
                                    int dst_height);

SkBitmap GetAvatarIconAsSquare(const SkBitmap& source_bitmap, int scale_factor);

}  

#endif  
