// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_AUTOMATION_INTERNAL_AUTOMATION_ACTION_ADAPTER_H_
#define CHROME_BROWSER_EXTENSIONS_API_AUTOMATION_INTERNAL_AUTOMATION_ACTION_ADAPTER_H_

namespace extensions {

class AutomationActionAdapter {
 public:
  
  virtual void DoDefault(int32 id) = 0;

  
  virtual void Focus(int32 id) = 0;

  
  
  virtual void MakeVisible(int32 id) = 0;

  
  
  virtual void SetSelection(int32 id, int32 start, int32 end) = 0;
};

}  

#endif  
