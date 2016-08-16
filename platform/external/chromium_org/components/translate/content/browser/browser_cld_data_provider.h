// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_TRANSLATE_CONTENT_BROWSER_BROWSER_CLD_DATA_PROVIDER_H_
#define COMPONENTS_TRANSLATE_CONTENT_BROWSER_BROWSER_CLD_DATA_PROVIDER_H_

#include <string>

#include "base/files/file_path.h"
#include "ipc/ipc_listener.h"

namespace IPC {
class Message;
}

namespace content {
class WebContents;
}

namespace translate {

class BrowserCldDataProvider : public IPC::Listener {
 public:
  virtual ~BrowserCldDataProvider() {}

  
  
  
  
  
  virtual bool OnMessageReceived(const IPC::Message&) = 0;

  
  
  
  
  
  
  
  
  virtual void OnCldDataRequest() = 0;

  
  
  
  
  virtual void SendCldDataResponse() = 0;
};

BrowserCldDataProvider* CreateBrowserCldDataProviderFor(
    content::WebContents*);

void SetCldDataFilePath(const base::FilePath& path);

base::FilePath GetCldDataFilePath();

}  

#endif  
