// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_DEVTOOLS_MANAGER_DELEGATE_H_
#define CONTENT_PUBLIC_BROWSER_DEVTOOLS_MANAGER_DELEGATE_H_

#include <string>
#include <vector>

#include "base/callback.h"

namespace base {
class DictionaryValue;
}

class GURL;

namespace content {

class BrowserContext;
class DevToolsAgentHost;
class DevToolsTarget;

class DevToolsManagerDelegate {
 public:
  virtual ~DevToolsManagerDelegate() {}

  
  virtual void Inspect(BrowserContext* browser_context,
                       DevToolsAgentHost* agent_host) = 0;

  virtual void DevToolsAgentStateChanged(DevToolsAgentHost* agent_host,
                                         bool attached) = 0;

  
  virtual base::DictionaryValue* HandleCommand(
      DevToolsAgentHost* agent_host,
      base::DictionaryValue* command) = 0;

  
  virtual scoped_ptr<DevToolsTarget> CreateNewTarget(const GURL& url) = 0;

  typedef std::vector<DevToolsTarget*> TargetList;
  typedef base::Callback<void(const TargetList&)> TargetCallback;

  
  
  virtual void EnumerateTargets(TargetCallback callback) = 0;

  
  
  virtual std::string GetPageThumbnailData(const GURL& url) = 0;
};

}  

#endif  
