// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_USERS_WALLPAPER_WALLPAPER_MANAGER_TEST_UTILS_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_USERS_WALLPAPER_WALLPAPER_MANAGER_TEST_UTILS_H_

#include <vector>

#include "ash/ash_constants.h"
#include "ui/gfx/image/image_skia.h"

namespace base {
class CommandLine;
class ScopedTempDir;
}  

namespace chromeos {
namespace wallpaper_manager_test_utils {

extern const SkColor kLargeDefaultWallpaperColor;
extern const SkColor kSmallDefaultWallpaperColor;
extern const SkColor kLargeGuestWallpaperColor;
extern const SkColor kSmallGuestWallpaperColor;

extern const SkColor kCustomWallpaperColor;

extern const int kWallpaperSize;

// Result bytes are written to |output|.
bool CreateJPEGImage(int width,
                     int height,
                     SkColor color,
                     std::vector<unsigned char>* output);

gfx::ImageSkia CreateTestImage(int width, int height, SkColor color);

bool WriteJPEGFile(const base::FilePath& path,
                   int width,
                   int height,
                   SkColor color);

bool ImageIsNearColor(gfx::ImageSkia image, SkColor expected_color);

void WaitAsyncWallpaperLoadFinished();

void CreateCmdlineWallpapers(const base::ScopedTempDir& dir,
                             scoped_ptr<base::CommandLine>* command_line);

}  
}  

#endif  
