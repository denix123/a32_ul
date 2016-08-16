// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_DEVTOOLS_AGENT_HOST_H_
#define CONTENT_PUBLIC_BROWSER_DEVTOOLS_AGENT_HOST_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "content/common/content_export.h"
#include "content/public/browser/devtools_agent_host_client.h"
#include "url/gurl.h"

namespace content {

class DevToolsExternalAgentProxyDelegate;
class WebContents;

class CONTENT_EXPORT DevToolsAgentHost
    : public base::RefCounted<DevToolsAgentHost> {
 public:
  enum Type {
    
    TYPE_WEB_CONTENTS,

    
    TYPE_SHARED_WORKER,

    
    TYPE_SERVICE_WORKER,

    
    TYPE_EXTERNAL,
  };

  
  static scoped_refptr<DevToolsAgentHost> GetForId(const std::string& id);

  
  
  static scoped_refptr<DevToolsAgentHost> GetOrCreateFor(
      WebContents* web_contents);

  
  
  static bool HasFor(WebContents* web_contents);

  
  
  static scoped_refptr<DevToolsAgentHost> GetForWorker(int worker_process_id,
                                                       int worker_route_id);

  
  
  
  static scoped_refptr<DevToolsAgentHost> Create(
      DevToolsExternalAgentProxyDelegate* delegate);

  static bool IsDebuggerAttached(WebContents* web_contents);

  typedef std::vector<scoped_refptr<DevToolsAgentHost> > List;

  
  static List GetOrCreateAll();

  
  virtual void AttachClient(DevToolsAgentHostClient* client) = 0;

  
  virtual void DetachClient() = 0;

  
  virtual bool IsAttached() = 0;

  
  virtual void DispatchProtocolMessage(const std::string& message) = 0;

  
  virtual void InspectElement(int x, int y) = 0;

  
  virtual std::string GetId() = 0;

  
  virtual WebContents* GetWebContents() = 0;

  
  
  virtual void DisconnectWebContents() = 0;

  
  virtual void ConnectWebContents(WebContents* web_contents) = 0;

  
  virtual bool IsWorker() const = 0;

  
  virtual Type GetType() = 0;

  
  virtual std::string GetTitle() = 0;

  
  virtual GURL GetURL() = 0;

  
  virtual bool Activate() = 0;

  
  virtual bool Close() = 0;

  
  static void DetachAllClients();

  typedef base::Callback<void(DevToolsAgentHost*, bool attached)>
      AgentStateCallback;

  static void AddAgentStateCallback(const AgentStateCallback& callback);
  static void RemoveAgentStateCallback(const AgentStateCallback& callback);

 protected:
  friend class base::RefCounted<DevToolsAgentHost>;
  virtual ~DevToolsAgentHost() {}
};

}  

#endif  
