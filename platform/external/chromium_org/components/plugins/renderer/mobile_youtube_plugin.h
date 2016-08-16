// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PLUGINS_RENDERER_MOBILE_YOUTUBE_PLUGIN_H_
#define COMPONENTS_PLUGINS_RENDERER_MOBILE_YOUTUBE_PLUGIN_H_

#include "components/plugins/renderer/plugin_placeholder.h"

namespace plugins {

class MobileYouTubePlugin : public PluginPlaceholder {
 public:
  MobileYouTubePlugin(content::RenderFrame* render_frame,
                      blink::WebLocalFrame* frame,
                      const blink::WebPluginParams& params,
                      base::StringPiece& template_html,
                      GURL placeholderDataUrl);

  
  static bool IsYouTubeURL(const GURL& url, const std::string& mime_type);

 private:
  virtual ~MobileYouTubePlugin();

  
  void OpenYoutubeUrlCallback();

  
  virtual void BindWebFrame(blink::WebFrame* frame) OVERRIDE;

  
  virtual gin::ObjectTemplateBuilder GetObjectTemplateBuilder(
      v8::Isolate* isolate) OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(MobileYouTubePlugin);
};

}  

#endif  
