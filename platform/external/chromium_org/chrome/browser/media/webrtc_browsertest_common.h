// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_WEBRTC_BROWSERTEST_COMMON_H_
#define CHROME_BROWSER_MEDIA_WEBRTC_BROWSERTEST_COMMON_H_

#include <string>

#include "base/files/file_path.h"
#include "base/process/process_handle.h"

namespace content {
class WebContents;
}

namespace test {


bool HasReferenceFilesInCheckout();

bool HasYuvAndY4mFile(const base::FilePath::CharType* reference_file);

base::FilePath GetReferenceFilesDir();

extern const base::FilePath::CharType kReferenceFileName360p[];
extern const base::FilePath::CharType kReferenceFileName720p[];
extern const base::FilePath::CharType kYuvFileExtension[];
extern const base::FilePath::CharType kY4mFileExtension[];

bool SleepInJavascript(content::WebContents* tab_contents, int timeout_msec);

bool PollingWaitUntil(const std::string& javascript,
                      const std::string& evaluates_to,
                      content::WebContents* tab_contents);
bool PollingWaitUntil(const std::string& javascript,
                      const std::string& evaluates_to,
                      content::WebContents* tab_contents,
                      int poll_interval_msec);

}  

#endif  
