// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_PDF_ADOBE_READER_INFO_WIN_H_
#define CHROME_BROWSER_UI_PDF_ADOBE_READER_INFO_WIN_H_

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "content/public/common/webplugininfo.h"

class Profile;

struct AdobeReaderPluginInfo {
  bool is_installed;
  bool is_enabled;    
  bool is_secure;     
  content::WebPluginInfo plugin_info;
};

typedef base::Callback<void(const AdobeReaderPluginInfo&)>
    GetAdobeReaderPluginInfoCallback;

void GetAdobeReaderPluginInfoAsync(
    Profile* profile,
    const GetAdobeReaderPluginInfoCallback& callback);

bool GetAdobeReaderPluginInfo(Profile* profile,
                              AdobeReaderPluginInfo* reader_info);

bool IsAdobeReaderDefaultPDFViewer();

bool IsAdobeReaderUpToDate();

#endif  
