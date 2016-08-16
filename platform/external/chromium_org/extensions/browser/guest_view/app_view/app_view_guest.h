// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_GUEST_VIEW_APP_VIEW_APP_VIEW_GUEST_H_
#define EXTENSIONS_BROWSER_GUEST_VIEW_APP_VIEW_APP_VIEW_GUEST_H_

#include "base/id_map.h"
#include "extensions/browser/extension_function_dispatcher.h"
#include "extensions/browser/guest_view/app_view/app_view_guest_delegate.h"
#include "extensions/browser/guest_view/guest_view.h"

namespace extensions {
class Extension;
class ExtensionHost;

class AppViewGuest : public GuestView<AppViewGuest>,
                     public ExtensionFunctionDispatcher::Delegate {
 public:
  static const char Type[];

  
  
  static bool CompletePendingRequest(
      content::BrowserContext* browser_context,
      const GURL& url,
      int guest_instance_id,
      const std::string& guest_extension_id);

  static GuestViewBase* Create(content::BrowserContext* browser_context,
                               int guest_instance_id);

  
  virtual WindowController* GetExtensionWindowController() const OVERRIDE;
  virtual content::WebContents* GetAssociatedWebContents() const OVERRIDE;

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  
  virtual bool HandleContextMenu(
      const content::ContextMenuParams& params) OVERRIDE;

  
  virtual const char* GetAPINamespace() const OVERRIDE;
  virtual int GetTaskPrefix() const OVERRIDE;
  virtual void CreateWebContents(
      const std::string& embedder_extension_id,
      int embedder_render_process_id,
      const GURL& embedder_site_url,
      const base::DictionaryValue& create_params,
      const WebContentsCreatedCallback& callback) OVERRIDE;
  virtual void DidAttachToEmbedder() OVERRIDE;
  virtual void DidInitialize() OVERRIDE;

 private:
  AppViewGuest(content::BrowserContext* browser_context, int guest_instance_id);

  virtual ~AppViewGuest();

  void OnRequest(const ExtensionHostMsg_Request_Params& params);

  void CompleteCreateWebContents(const GURL& url,
                                 const Extension* guest_extension,
                                 const WebContentsCreatedCallback& callback);

  void LaunchAppAndFireEvent(scoped_ptr<base::DictionaryValue> data,
                             const WebContentsCreatedCallback& callback,
                             ExtensionHost* extension_host);

  GURL url_;
  std::string guest_extension_id_;
  scoped_ptr<ExtensionFunctionDispatcher> extension_function_dispatcher_;
  scoped_ptr<AppViewGuestDelegate> app_view_guest_delegate_;

  
  
  base::WeakPtrFactory<AppViewGuest> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(AppViewGuest);
};

}  

#endif  