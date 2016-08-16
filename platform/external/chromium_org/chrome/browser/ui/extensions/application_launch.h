// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_EXTENSIONS_APPLICATION_LAUNCH_H_
#define CHROME_BROWSER_UI_EXTENSIONS_APPLICATION_LAUNCH_H_

#include "base/command_line.h"
#include "base/files/file_path.h"
#include "chrome/browser/ui/host_desktop.h"
#include "chrome/common/extensions/extension_constants.h"
#include "ui/base/window_open_disposition.h"
#include "ui/gfx/rect.h"
#include "url/gurl.h"

class Browser;
class Profile;

namespace base {
class CommandLine;
}

namespace content {
class WebContents;
}

namespace extensions {
class Extension;
}

struct AppLaunchParams {
  AppLaunchParams(Profile* profile,
                  const extensions::Extension* extension,
                  extensions::LaunchContainer container,
                  WindowOpenDisposition disposition);

  
  
  AppLaunchParams(Profile* profile,
                  const extensions::Extension* extension,
                  WindowOpenDisposition disposition);

  
  
  
  
  AppLaunchParams(Profile* profile,
                  const extensions::Extension* extension,
                  int event_flags,
                  chrome::HostDesktopType desktop_type);

  ~AppLaunchParams();

  
  Profile* profile;

  
  std::string extension_id;

  
  extensions::LaunchContainer container;

  
  WindowOpenDisposition disposition;

  
  chrome::HostDesktopType desktop_type;

  
  GURL override_url;

  
  
  gfx::Rect override_bounds;

  
  
  base::CommandLine command_line;

  
  
  base::FilePath current_directory;
};

void OpenApplicationWithReenablePrompt(const AppLaunchParams& params);

content::WebContents* OpenApplication(const AppLaunchParams& params);

content::WebContents* OpenAppShortcutWindow(Profile* profile,
                                            const GURL& url);

bool CanLaunchViaEvent(const extensions::Extension* extension);

GURL UrlForExtension(const extensions::Extension* extension,
                     const GURL& override_url);

#endif  
