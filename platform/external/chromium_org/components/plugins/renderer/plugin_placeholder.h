// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PLUGINS_RENDERER_PLUGIN_PLACEHOLDER_H_
#define COMPONENTS_PLUGINS_RENDERER_PLUGIN_PLACEHOLDER_H_

#include "components/plugins/renderer/webview_plugin.h"
#include "content/public/common/webplugininfo.h"
#include "content/public/renderer/context_menu_client.h"
#include "content/public/renderer/render_frame_observer.h"
#include "content/public/renderer/render_process_observer.h"
#include "gin/wrappable.h"
#include "third_party/WebKit/public/web/WebPluginParams.h"

namespace content {
struct WebPluginInfo;
}

namespace plugins {
class PluginPlaceholder : public content::RenderFrameObserver,
                          public WebViewPlugin::Delegate,
                          public gin::Wrappable<PluginPlaceholder> {
 public:
  static gin::WrapperInfo kWrapperInfo;

  WebViewPlugin* plugin() { return plugin_; }

  void set_blocked_for_prerendering(bool blocked_for_prerendering) {
    is_blocked_for_prerendering_ = blocked_for_prerendering;
  }

  void set_allow_loading(bool allow_loading) { allow_loading_ = allow_loading; }

 protected:
  
  
  PluginPlaceholder(content::RenderFrame* render_frame,
                    blink::WebLocalFrame* frame,
                    const blink::WebPluginParams& params,
                    const std::string& html_data,
                    GURL placeholderDataUrl);

  virtual ~PluginPlaceholder();

  void OnLoadBlockedPlugins(const std::string& identifier);
  void OnSetIsPrerendering(bool is_prerendering);

  void SetMessage(const base::string16& message);
  void SetPluginInfo(const content::WebPluginInfo& plugin_info);
  const content::WebPluginInfo& GetPluginInfo() const;
  void SetIdentifier(const std::string& identifier);
  blink::WebLocalFrame* GetFrame();
  const blink::WebPluginParams& GetPluginParams() const;
  bool LoadingAllowed() const { return allow_loading_; }

  
  
  void ReplacePlugin(blink::WebPlugin* new_plugin);

  
  void HidePlugin();

  
  void LoadPlugin();

  
  virtual gin::ObjectTemplateBuilder GetObjectTemplateBuilder(
      v8::Isolate* isolate) OVERRIDE;

 private:
  
  virtual void ShowContextMenu(const blink::WebMouseEvent&) OVERRIDE;
  virtual void PluginDestroyed() OVERRIDE;

  
  virtual void OnDestruct() OVERRIDE;

  

  
  void LoadCallback();

  
  void HideCallback();

  void DidFinishLoadingCallback();

  void UpdateMessage();

  blink::WebLocalFrame* frame_;
  blink::WebPluginParams plugin_params_;
  WebViewPlugin* plugin_;

  content::WebPluginInfo plugin_info_;

  base::string16 message_;

  
  
  bool is_blocked_for_prerendering_;
  bool allow_loading_;

  bool hidden_;
  bool finished_loading_;
  std::string identifier_;

  DISALLOW_COPY_AND_ASSIGN(PluginPlaceholder);
};

}  

#endif  
