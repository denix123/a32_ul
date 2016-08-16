// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_RENDERER_DISPATCHER_H_
#define EXTENSIONS_RENDERER_DISPATCHER_H_

#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "base/scoped_observer.h"
#include "base/timer/timer.h"
#include "content/public/renderer/render_process_observer.h"
#include "extensions/common/event_filter.h"
#include "extensions/common/extension_set.h"
#include "extensions/common/extensions_client.h"
#include "extensions/common/features/feature.h"
#include "extensions/renderer/resource_bundle_source_map.h"
#include "extensions/renderer/script_context.h"
#include "extensions/renderer/script_context_set.h"
#include "extensions/renderer/user_script_set_manager.h"
#include "extensions/renderer/v8_schema_registry.h"
#include "third_party/WebKit/public/platform/WebString.h"
#include "third_party/WebKit/public/platform/WebVector.h"
#include "v8/include/v8.h"

class ChromeRenderViewTest;
class GURL;
class ModuleSystem;
class URLPattern;
struct ExtensionMsg_ExternalConnectionInfo;
struct ExtensionMsg_Loaded_Params;
struct ExtensionMsg_UpdatePermissions_Params;

namespace blink {
class WebFrame;
class WebSecurityOrigin;
}

namespace base {
class DictionaryValue;
class ListValue;
}

namespace content {
class RenderThread;
}

namespace extensions {
class ContentWatcher;
class DispatcherDelegate;
class Extension;
class FilteredEventRouter;
class ManifestPermissionSet;
class RequestSender;
class ScriptContext;
class ScriptInjectionManager;
struct Message;

class Dispatcher : public content::RenderProcessObserver,
                   public UserScriptSetManager::Observer {
 public:
  explicit Dispatcher(DispatcherDelegate* delegate);
  virtual ~Dispatcher();

  const std::set<std::string>& function_names() const {
    return function_names_;
  }

  bool is_extension_process() const { return is_extension_process_; }

  const ExtensionSet* extensions() const { return &extensions_; }

  const ScriptContextSet& script_context_set() const {
    return script_context_set_;
  }

  V8SchemaRegistry* v8_schema_registry() { return v8_schema_registry_.get(); }

  ContentWatcher* content_watcher() { return content_watcher_.get(); }

  RequestSender* request_sender() { return request_sender_.get(); }

  void OnRenderViewCreated(content::RenderView* render_view);

  bool IsExtensionActive(const std::string& extension_id) const;

  
  
  
  
  const Extension* GetExtensionFromFrameAndWorld(const blink::WebFrame* frame,
                                                 int world_id,
                                                 bool use_effective_url);

  void DidCreateScriptContext(blink::WebFrame* frame,
                              const v8::Handle<v8::Context>& context,
                              int extension_group,
                              int world_id);

  void WillReleaseScriptContext(blink::WebFrame* frame,
                                const v8::Handle<v8::Context>& context,
                                int world_id);

  void DidCreateDocumentElement(blink::WebFrame* frame);

  void DidMatchCSS(
      blink::WebFrame* frame,
      const blink::WebVector<blink::WebString>& newly_matching_selectors,
      const blink::WebVector<blink::WebString>& stopped_matching_selectors);

  void OnExtensionResponse(int request_id,
                           bool success,
                           const base::ListValue& response,
                           const std::string& error);

  
  
  
  bool CheckContextAccessToExtensionAPI(const std::string& function_name,
                                        ScriptContext* context) const;

  
  void DispatchEvent(const std::string& extension_id,
                     const std::string& event_name) const;

  
  void InvokeModuleSystemMethod(content::RenderView* render_view,
                                const std::string& extension_id,
                                const std::string& module_name,
                                const std::string& function_name,
                                const base::ListValue& args,
                                bool user_gesture);

  void ClearPortData(int port_id);

  
  
  static std::vector<std::pair<std::string, int> > GetJsResources();
  static void RegisterNativeHandlers(ModuleSystem* module_system,
                                     ScriptContext* context,
                                     Dispatcher* dispatcher,
                                     RequestSender* request_sender,
                                     V8SchemaRegistry* v8_schema_registry);

  bool WasWebRequestUsedBySomeExtensions() const { return webrequest_used_; }

 private:
  friend class ::ChromeRenderViewTest;
  FRIEND_TEST_ALL_PREFIXES(RendererPermissionsPolicyDelegateTest,
                           CannotScriptWebstore);

  
  virtual bool OnControlMessageReceived(const IPC::Message& message) OVERRIDE;
  virtual void WebKitInitialized() OVERRIDE;
  virtual void IdleNotification() OVERRIDE;
  virtual void OnRenderProcessShutdown() OVERRIDE;

  void OnActivateExtension(const std::string& extension_id);
  void OnCancelSuspend(const std::string& extension_id);
  void OnClearTabSpecificPermissions(
      int tab_id,
      const std::vector<std::string>& extension_ids);
  void OnDeliverMessage(int target_port_id, const Message& message);
  void OnDispatchOnConnect(int target_port_id,
                           const std::string& channel_name,
                           const base::DictionaryValue& source_tab,
                           const ExtensionMsg_ExternalConnectionInfo& info,
                           const std::string& tls_channel_id);
  void OnDispatchOnDisconnect(int port_id, const std::string& error_message);
  void OnLoaded(
      const std::vector<ExtensionMsg_Loaded_Params>& loaded_extensions);
  void OnLoadedInternal(scoped_refptr<const Extension> extension);
  void OnMessageInvoke(const std::string& extension_id,
                       const std::string& module_name,
                       const std::string& function_name,
                       const base::ListValue& args,
                       bool user_gesture);
  void OnSetChannel(int channel);
  void OnSetFunctionNames(const std::vector<std::string>& names);
  void OnSetScriptingWhitelist(
      const ExtensionsClient::ScriptingWhitelist& extension_ids);
  void OnSetSystemFont(const std::string& font_family,
                       const std::string& font_size);
  void OnShouldSuspend(const std::string& extension_id, uint64 sequence_id);
  void OnSuspend(const std::string& extension_id);
  void OnTransferBlobs(const std::vector<std::string>& blob_uuids);
  void OnUnloaded(const std::string& id);
  void OnUpdatePermissions(const ExtensionMsg_UpdatePermissions_Params& params);
  void OnUpdateTabSpecificPermissions(const GURL& url,
                                      int tab_id,
                                      const std::string& extension_id,
                                      const URLPatternSet& origin_set);
  void OnUsingWebRequestAPI(bool webrequest_used);

  
  virtual void OnUserScriptsUpdated(
      const std::set<std::string>& changed_extensions,
      const std::vector<UserScript*>& scripts) OVERRIDE;

  void UpdateActiveExtensions();

  
  void InitOriginPermissions(const Extension* extension);

  
  
  void UpdateOriginPermissions(const Extension* extension,
                               const URLPatternSet& old_patterns,
                               const URLPatternSet& new_patterns);

  
  void EnableCustomElementWhiteList();

  
  
  void UpdateBindings(const std::string& extension_id);

  void UpdateBindingsForContext(ScriptContext* context);

  void RegisterBinding(const std::string& api_name, ScriptContext* context);

  void RegisterNativeHandlers(ModuleSystem* module_system,
                              ScriptContext* context);

  
  void PopulateSourceMap();

  
  bool IsWithinPlatformApp();

  bool IsSandboxedPage(const GURL& url) const;

  
  Feature::Context ClassifyJavaScriptContext(
      const Extension* extension,
      int extension_group,
      const GURL& url,
      const blink::WebSecurityOrigin& origin);

  
  
  v8::Handle<v8::Object> GetOrCreateObject(const v8::Handle<v8::Object>& object,
                                           const std::string& field,
                                           v8::Isolate* isolate);

  v8::Handle<v8::Object> GetOrCreateBindObjectIfAvailable(
      const std::string& api_name,
      std::string* bind_name,
      ScriptContext* context);

  
  
  DispatcherDelegate* delegate_;

  
  bool is_extension_process_;

  
  
  
  ExtensionSet extensions_;

  
  
  std::map<std::string, std::string> extension_load_errors_;

  
  
  ScriptContextSet script_context_set_;

  scoped_ptr<ContentWatcher> content_watcher_;

  scoped_ptr<UserScriptSetManager> user_script_set_manager_;

  scoped_ptr<ScriptInjectionManager> script_injection_manager_;

  
  
  scoped_ptr<base::RepeatingTimer<content::RenderThread> > forced_idle_timer_;

  
  std::set<std::string> function_names_;

  
  std::set<std::string> active_extension_ids_;

  ResourceBundleSourceMap source_map_;

  
  scoped_ptr<V8SchemaRegistry> v8_schema_registry_;

  
  scoped_ptr<RequestSender> request_sender_;

  
  std::string system_font_family_;
  std::string system_font_size_;

  
  std::map<int, int> port_to_tab_id_map_;

  
  bool is_webkit_initialized_;

  
  
  ScopedObserver<UserScriptSetManager, UserScriptSetManager::Observer>
      user_script_set_manager_observer_;

  
  bool webrequest_used_;

  DISALLOW_COPY_AND_ASSIGN(Dispatcher);
};

}  

#endif  
