// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SEARCH_HOTWORD_CLIENT_H_
#define CHROME_BROWSER_SEARCH_HOTWORD_CLIENT_H_

class HotwordClient {
 public:
  virtual ~HotwordClient() {}

  
  virtual void OnHotwordStateChanged(bool started) {}

  
  virtual void OnHotwordRecognized() = 0;
};

#endif  
