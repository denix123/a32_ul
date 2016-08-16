// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROME_ELF_INIT_WIN_H_
#define CHROME_BROWSER_CHROME_ELF_INIT_WIN_H_

extern const char kBrowserBlacklistTrialName[];
extern const char kBrowserBlacklistTrialDisabledGroupName[];

void InitializeChromeElf();

void AddFinchBlacklistToRegistry();

void BrowserBlacklistBeaconSetup();

#endif  
