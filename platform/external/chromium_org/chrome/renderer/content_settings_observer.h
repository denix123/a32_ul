// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_RENDERER_CONTENT_SETTINGS_OBSERVER_H_
#define CHROME_RENDERER_CONTENT_SETTINGS_OBSERVER_H_

#include <map>
#include <set>

#include "components/content_settings/core/common/content_settings.h"
#include "components/content_settings/core/common/content_settings_types.h"
#include "content/public/renderer/render_frame_observer.h"
#include "content/public/renderer/render_frame_observer_tracker.h"
#include "third_party/WebKit/public/web/WebPermissionClient.h"

class GURL;

namespace blink {
class WebFrame;
class WebSecurityOrigin;
class WebURL;
}

namespace extensions {
class Dispatcher;
class Extension;
}

class ContentSettingsObserver
    : public content::RenderFrameObserver,
      public content::RenderFrameObserverTracker<ContentSettingsObserver>,
      public blink::WebPermissionClient {
 public:
  ContentSettingsObserver(content::RenderFrame* render_frame,
                          extensions::Dispatcher* extension_dispatcher);
  virtual ~ContentSettingsObserver();

  
  
  
  void SetContentSettingRules(
      const RendererContentSettingRules* content_setting_rules);

  bool IsPluginTemporarilyAllowed(const std::string& identifier);

  
  void DidBlockContentType(ContentSettingsType settings_type);

  
  virtual bool allowDatabase(const blink::WebString& name,
                             const blink::WebString& display_name,
                             unsigned long estimated_size) OVERRIDE;
  virtual void requestFileSystemAccessAsync(
      const blink::WebPermissionCallbacks& callbacks) OVERRIDE;
  virtual bool allowImage(bool enabled_per_settings,
                          const blink::WebURL& image_url) OVERRIDE;
  virtual bool allowIndexedDB(const blink::WebString& name,
                              const blink::WebSecurityOrigin& origin) OVERRIDE;
  virtual bool allowPlugins(bool enabled_per_settings) OVERRIDE;
  virtual bool allowScript(bool enabled_per_settings) OVERRIDE;
  virtual bool allowScriptFromSource(bool enabled_per_settings,
                                     const blink::WebURL& script_url) OVERRIDE;
  virtual bool allowStorage(bool local) OVERRIDE;
  virtual bool allowReadFromClipboard(bool default_value) OVERRIDE;
  virtual bool allowWriteToClipboard(bool default_value) OVERRIDE;
  virtual bool allowMutationEvents(bool default_value) OVERRIDE;
  virtual bool allowPushState() OVERRIDE;
  virtual void didNotAllowPlugins() OVERRIDE;
  virtual void didNotAllowScript() OVERRIDE;
  virtual bool allowDisplayingInsecureContent(
      bool allowed_per_settings,
      const blink::WebSecurityOrigin& context,
      const blink::WebURL& url) OVERRIDE;
  virtual bool allowRunningInsecureContent(
      bool allowed_per_settings,
      const blink::WebSecurityOrigin& context,
      const blink::WebURL& url) OVERRIDE;

  
  bool AreNPAPIPluginsBlocked() const;

 private:
  FRIEND_TEST_ALL_PREFIXES(ContentSettingsObserverTest, WhitelistedSchemes);
  FRIEND_TEST_ALL_PREFIXES(ChromeRenderViewTest,
                           ContentSettingsInterstitialPages);
  FRIEND_TEST_ALL_PREFIXES(ChromeRenderViewTest, PluginsTemporarilyAllowed);

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;
  virtual void DidCommitProvisionalLoad(bool is_new_navigation) OVERRIDE;

  
  void OnLoadBlockedPlugins(const std::string& identifier);
  void OnSetAsInterstitial();
  void OnNPAPINotSupported();
  void OnSetAllowDisplayingInsecureContent(bool allow);
  void OnSetAllowRunningInsecureContent(bool allow);
  void OnReloadFrame();
  void OnRequestFileSystemAccessAsyncResponse(int request_id, bool allowed);

  
  void ClearBlockedContentSettings();

  
  bool IsPlatformApp();

#if defined(ENABLE_EXTENSIONS)
  
  
  const extensions::Extension* GetExtension(
      const blink::WebSecurityOrigin& origin) const;
#endif

  
  
  static bool IsWhitelistedForContentSettings(content::RenderFrame* frame);
  static bool IsWhitelistedForContentSettings(
      const blink::WebSecurityOrigin& origin,
      const GURL& document_url);

#if defined(ENABLE_EXTENSIONS)
  
  extensions::Dispatcher* extension_dispatcher_;
#endif

  
  bool allow_displaying_insecure_content_;
  bool allow_running_insecure_content_;

  
  
  
  
  const RendererContentSettingRules* content_setting_rules_;

  
  bool content_blocked_[CONTENT_SETTINGS_NUM_TYPES];

  
  typedef std::pair<GURL, bool> StoragePermissionsKey;
  std::map<StoragePermissionsKey, bool> cached_storage_permissions_;

  
  std::map<blink::WebFrame*, bool> cached_script_permissions_;

  std::set<std::string> temporarily_allowed_plugins_;
  bool is_interstitial_page_;
  bool npapi_plugins_blocked_;

  int current_request_id_;
  typedef std::map<int, blink::WebPermissionCallbacks> PermissionRequestMap;
  PermissionRequestMap permission_requests_;

  DISALLOW_COPY_AND_ASSIGN(ContentSettingsObserver);
};

#endif  
