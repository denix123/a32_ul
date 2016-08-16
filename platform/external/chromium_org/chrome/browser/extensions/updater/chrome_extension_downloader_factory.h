// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_UPDATER_CHROME_EXTENSION_DOWNLOADER_FACTORY_H_
#define CHROME_BROWSER_EXTENSIONS_UPDATER_CHROME_EXTENSION_DOWNLOADER_FACTORY_H_

#include "base/memory/scoped_ptr.h"

class Profile;

namespace extensions {
class ExtensionDownloader;
class ExtensionDownloaderDelegate;
}

namespace net {
class URLRequestContextGetter;
}

class ChromeExtensionDownloaderFactory {
 public:
  
  
  static scoped_ptr<extensions::ExtensionDownloader> CreateForRequestContext(
      net::URLRequestContextGetter* request_context,
      extensions::ExtensionDownloaderDelegate* delegate);

  
  
  
  static scoped_ptr<extensions::ExtensionDownloader> CreateForProfile(
      Profile* profile,
      extensions::ExtensionDownloaderDelegate* delegate);
};

#endif  
