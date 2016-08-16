// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_PROCESS_MANAGER_H_
#define EXTENSIONS_BROWSER_PROCESS_MANAGER_H_

#include <map>
#include <set>
#include <string>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/time/time.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "extensions/common/view_type.h"

class GURL;

namespace content {
class BrowserContext;
class DevToolsAgentHost;
class RenderViewHost;
class RenderFrameHost;
class SiteInstance;
};

namespace extensions {

class Extension;
class ExtensionHost;
class ExtensionRegistry;
class ProcessManagerDelegate;
class ProcessManagerObserver;

class ProcessManager : public content::NotificationObserver {
 public:
  typedef std::set<extensions::ExtensionHost*> ExtensionHostSet;
  typedef ExtensionHostSet::const_iterator const_iterator;

  static ProcessManager* Create(content::BrowserContext* context);
  virtual ~ProcessManager();

  const ExtensionHostSet& background_hosts() const {
    return background_hosts_;
  }

  typedef std::set<content::RenderViewHost*> ViewSet;
  const ViewSet GetAllViews() const;

  
  void AddObserver(ProcessManagerObserver* observer);
  void RemoveObserver(ProcessManagerObserver* observer);

  
  
  
  
  virtual bool CreateBackgroundHost(const Extension* extension,
                                    const GURL& url);

  
  
  ExtensionHost* GetBackgroundHostForExtension(const std::string& extension_id);

  
  
  
  virtual content::SiteInstance* GetSiteInstanceForURL(const GURL& url);

  
  void UnregisterRenderViewHost(content::RenderViewHost* render_view_host);

  
  
  std::set<content::RenderViewHost*> GetRenderViewHostsForExtension(
      const std::string& extension_id);

  
  
  const Extension* GetExtensionForRenderViewHost(
      content::RenderViewHost* render_view_host);

  
  
  bool IsBackgroundHostClosing(const std::string& extension_id);

  
  
  
  
  int GetLazyKeepaliveCount(const Extension* extension);
  void IncrementLazyKeepaliveCount(const Extension* extension);
  void DecrementLazyKeepaliveCount(const Extension* extension);

  void IncrementLazyKeepaliveCountForView(
      content::RenderViewHost* render_view_host);

  
  
  
  void KeepaliveImpulse(const Extension* extension);

  
  static void OnKeepaliveFromPlugin(int render_process_id,
                                    int render_frame_id,
                                    const std::string& extension_id);

  
  
  void OnShouldSuspendAck(const std::string& extension_id, uint64 sequence_id);

  
  void OnSuspendAck(const std::string& extension_id);

  
  
  void OnNetworkRequestStarted(content::RenderFrameHost* render_frame_host);
  void OnNetworkRequestDone(content::RenderFrameHost* render_frame_host);

  
  
  void CancelSuspend(const Extension* extension);

  
  
  void MaybeCreateStartupBackgroundHosts();

  
  void CloseBackgroundHosts();

  
  
  content::BrowserContext* GetBrowserContext() const;

  
  typedef base::Callback<void(const std::string& extension_id)>
      ImpulseCallbackForTesting;
  void SetKeepaliveImpulseCallbackForTesting(
      const ImpulseCallbackForTesting& callback);
  void SetKeepaliveImpulseDecrementCallbackForTesting(
      const ImpulseCallbackForTesting& callback);

  
  
  static void SetEventPageIdleTimeForTesting(unsigned idle_time_msec);

  
  
  
  static void SetEventPageSuspendingTimeForTesting(
      unsigned suspending_time_msec);

  
  
  
  static ProcessManager* CreateForTesting(content::BrowserContext* context,
                                          ExtensionRegistry* registry);

  
  static ProcessManager* CreateIncognitoForTesting(
      content::BrowserContext* incognito_context,
      content::BrowserContext* original_context,
      ProcessManager* original_manager,
      ExtensionRegistry* registry);

  bool startup_background_hosts_created_for_test() const {
    return startup_background_hosts_created_;
  }

 protected:
  
  
  
  ProcessManager(content::BrowserContext* context,
                 content::BrowserContext* original_context,
                 ExtensionRegistry* registry);

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  content::NotificationRegistrar registrar_;

  
  ExtensionHostSet background_hosts_;

  
  
  
  scoped_refptr<content::SiteInstance> site_instance_;

  
  ExtensionRegistry* extension_registry_;

 private:
  friend class ProcessManagerTest;

  
  struct BackgroundPageData;
  typedef std::string ExtensionId;
  typedef std::map<ExtensionId, BackgroundPageData> BackgroundPageDataMap;
  typedef std::map<content::RenderViewHost*,
      extensions::ViewType> ExtensionRenderViews;

  
  
  void CreateStartupBackgroundHosts();

  
  void OnBackgroundHostCreated(ExtensionHost* host);

  
  void CloseBackgroundHost(ExtensionHost* host);

  
  
  void DecrementLazyKeepaliveCount(const std::string& extension_id);

  
  void OnKeepaliveImpulseCheck();

  
  
  void OnLazyBackgroundPageIdle(const std::string& extension_id,
                                uint64 sequence_id);
  void OnLazyBackgroundPageActive(const std::string& extension_id);
  void CloseLazyBackgroundPageNow(const std::string& extension_id,
                                  uint64 sequence_id);

  
  
  
  
  bool RegisterRenderViewHost(content::RenderViewHost* render_view_host);

  
  
  void UnregisterExtension(const std::string& extension_id);

  
  void ClearBackgroundPageData(const std::string& extension_id);

  void OnDevToolsStateChanged(content::DevToolsAgentHost*, bool attached);

  
  
  
  ExtensionRenderViews all_extension_views_;

  BackgroundPageDataMap background_page_data_;

  
  bool startup_background_hosts_created_;

  base::Callback<void(content::DevToolsAgentHost*, bool)> devtools_callback_;

  ImpulseCallbackForTesting keepalive_impulse_callback_for_testing_;
  ImpulseCallbackForTesting keepalive_impulse_decrement_callback_for_testing_;

  ObserverList<ProcessManagerObserver> observer_list_;

  
  
  
  
  
  
  
  
  
  
  
  
  
  uint64 last_background_close_sequence_id_;

  
  base::WeakPtrFactory<ProcessManager> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ProcessManager);
};

}  

#endif  
