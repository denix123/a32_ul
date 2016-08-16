// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_WEB_APPLICATIONS_WEB_APP_WIN_H_
#define CHROME_BROWSER_WEB_APPLICATIONS_WEB_APP_WIN_H_

#include "base/files/file_path.h"
#include "chrome/browser/web_applications/web_app.h"

class Profile;

namespace content {
class WebContents;
}

namespace extensions {
class Extension;
}

namespace gfx {
class ImageFamily;
}

namespace web_app {

base::FilePath CreateShortcutInWebAppDir(const base::FilePath& web_app_path,
                                         const ShortcutInfo& shortcut_info);

void UpdateRelaunchDetailsForApp(Profile* profile,
                                 const extensions::Extension* extension,
                                 HWND hwnd);

namespace internals {

bool CheckAndSaveIcon(const base::FilePath& icon_file,
                      const gfx::ImageFamily& image);

base::FilePath GetIconFilePath(const base::FilePath& web_app_path,
                               const base::string16& title);

}  

}  

#endif  
