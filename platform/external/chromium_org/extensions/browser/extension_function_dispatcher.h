// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_EXTENSION_FUNCTION_DISPATCHER_H_
#define EXTENSIONS_BROWSER_EXTENSION_FUNCTION_DISPATCHER_H_

#include <map>
#include <string>
#include <vector>

#include "base/memory/weak_ptr.h"
#include "extensions/browser/extension_function.h"
#include "ipc/ipc_sender.h"

struct ExtensionHostMsg_Request_Params;

namespace content {
class BrowserContext;
class RenderFrameHost;
class RenderViewHost;
class WebContents;
}

namespace extensions {

class Extension;
class ExtensionAPI;
class ExtensionMessageFilter;
class InfoMap;
class ProcessMap;
class WindowController;

typedef ExtensionFunction* (*ExtensionFunctionFactory)();

class ExtensionFunctionDispatcher
    : public base::SupportsWeakPtr<ExtensionFunctionDispatcher> {
 public:
  class Delegate {
   public:
    
    
    virtual WindowController* GetExtensionWindowController() const;

    
    
    
    
    virtual content::WebContents* GetAssociatedWebContents() const;

    
    
    
    virtual content::WebContents* GetVisibleWebContents() const;

   protected:
    virtual ~Delegate() {}
  };

  
  static void GetAllFunctionNames(std::vector<std::string>* names);

  
  
  static bool OverrideFunction(const std::string& name,
                               ExtensionFunctionFactory factory);

  
  
  static void DispatchOnIOThread(
      InfoMap* extension_info_map,
      void* profile_id,
      int render_process_id,
      base::WeakPtr<ExtensionMessageFilter> ipc_sender,
      int routing_id,
      const ExtensionHostMsg_Request_Params& params);

  
  
  
  
  ExtensionFunctionDispatcher(content::BrowserContext* browser_context,
                              Delegate* delegate);

  ~ExtensionFunctionDispatcher();

  Delegate* delegate() { return delegate_; }

  
  
  
  
  void Dispatch(const ExtensionHostMsg_Request_Params& params,
                content::RenderViewHost* render_view_host);

  
  
  void OnExtensionFunctionCompleted(const Extension* extension);

  
  content::BrowserContext* browser_context() { return browser_context_; }

 private:
  
  
  
  
  
  class UIThreadResponseCallbackWrapper;

  
  
  
  
  static bool CheckPermissions(
      ExtensionFunction* function,
      const ExtensionHostMsg_Request_Params& params,
      const ExtensionFunction::ResponseCallback& callback);

  
  
  
  static ExtensionFunction* CreateExtensionFunction(
      const ExtensionHostMsg_Request_Params& params,
      const Extension* extension,
      int requesting_process_id,
      const ProcessMap& process_map,
      ExtensionAPI* api,
      void* profile_id,
      const ExtensionFunction::ResponseCallback& callback);

  
  
  static void SendAccessDenied(
      const ExtensionFunction::ResponseCallback& callback);

  void DispatchWithCallbackInternal(
      const ExtensionHostMsg_Request_Params& params,
      content::RenderViewHost* render_view_host,
      content::RenderFrameHost* render_frame_host,
      const ExtensionFunction::ResponseCallback& callback);

  content::BrowserContext* browser_context_;

  Delegate* delegate_;

  
  
  
  typedef std::map<content::RenderViewHost*, UIThreadResponseCallbackWrapper*>
      UIThreadResponseCallbackWrapperMap;
  UIThreadResponseCallbackWrapperMap ui_thread_response_callback_wrappers_;
};

}  

#endif  
