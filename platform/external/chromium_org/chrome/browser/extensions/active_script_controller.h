// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_ACTIVE_SCRIPT_CONTROLLER_H_
#define CHROME_BROWSER_EXTENSIONS_ACTIVE_SCRIPT_CONTROLLER_H_

#include <map>
#include <set>
#include <string>
#include <vector>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/scoped_observer.h"
#include "content/public/browser/web_contents_observer.h"
#include "extensions/browser/extension_registry_observer.h"
#include "extensions/common/permissions/permissions_data.h"
#include "extensions/common/user_script.h"

namespace content {
class WebContents;
}

namespace IPC {
class Message;
}

class ExtensionAction;

namespace extensions {
class Extension;
class ExtensionRegistry;

class ActiveScriptController : public content::WebContentsObserver,
                               public ExtensionRegistryObserver {
 public:
  explicit ActiveScriptController(content::WebContents* web_contents);
  virtual ~ActiveScriptController();

  
  
  static ActiveScriptController* GetForWebContents(
      content::WebContents* web_contents);

  
  
  
  void OnActiveTabPermissionGranted(const Extension* extension);

  
  void OnAdInjectionDetected(const std::set<std::string>& ad_injectors);

  
  
  void AlwaysRunOnVisibleOrigin(const Extension* extension);

  
  
  void OnClicked(const Extension* extension);

  
  
  bool WantsToRun(const Extension* extension);

#if defined(UNIT_TEST)
  
  PermissionsData::AccessType RequiresUserConsentForScriptInjectionForTesting(
      const Extension* extension,
      UserScript::InjectionType type) {
    return RequiresUserConsentForScriptInjection(extension, type);
  }
  void RequestScriptInjectionForTesting(const Extension* extension,
                                        const base::Closure& callback) {
    return RequestScriptInjection(extension, callback);
  }
#endif  

 private:
  typedef std::vector<base::Closure> PendingRequestList;
  typedef std::map<std::string, PendingRequestList> PendingRequestMap;

  
  
  
  PermissionsData::AccessType RequiresUserConsentForScriptInjection(
      const Extension* extension,
      UserScript::InjectionType type);

  
  
  void RequestScriptInjection(const Extension* extension,
                              const base::Closure& callback);

  
  void RunPendingForExtension(const Extension* extension);

  
  void OnRequestScriptInjectionPermission(
      const std::string& extension_id,
      UserScript::InjectionType script_type,
      int64 request_id);

  
  void PermitScriptInjection(int64 request_id);

  
  void LogUMA() const;

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;
  virtual void DidNavigateMainFrame(
      const content::LoadCommittedDetails& details,
      const content::FrameNavigateParams& params) OVERRIDE;

  
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const Extension* extension,
      UnloadedExtensionInfo::Reason reason) OVERRIDE;

  
  
  
  bool enabled_;

  
  PendingRequestMap pending_requests_;

  
  
  
  
  std::set<std::string> permitted_extensions_;

  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver>
      extension_registry_observer_;

  DISALLOW_COPY_AND_ASSIGN(ActiveScriptController);
};

}  

#endif  
