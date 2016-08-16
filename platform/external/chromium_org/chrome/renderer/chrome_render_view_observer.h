// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_RENDERER_CHROME_RENDER_VIEW_OBSERVER_H_
#define CHROME_RENDERER_CHROME_RENDER_VIEW_OBSERVER_H_

#include <set>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/scoped_ptr.h"
#include "base/timer/timer.h"
#include "content/public/common/top_controls_state.h"
#include "content/public/renderer/render_view_observer.h"
#include "ui/gfx/size.h"
#include "url/gurl.h"

class ContentSettingsObserver;
class SkBitmap;
class WebViewColorOverlay;
class WebViewAnimatingOverlay;

namespace blink {
class WebView;
struct WebWindowFeatures;
}

namespace safe_browsing {
class PhishingClassifierDelegate;
}

namespace translate {
class TranslateHelper;
}

namespace web_cache {
class WebCacheRenderProcessObserver;
}

class ChromeRenderViewObserver : public content::RenderViewObserver {
 public:
  
  ChromeRenderViewObserver(
      content::RenderView* render_view,
      web_cache::WebCacheRenderProcessObserver*
          web_cache_render_process_observer);
  virtual ~ChromeRenderViewObserver();

 private:
  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;
  virtual void DidStartLoading() OVERRIDE;
  virtual void DidStopLoading() OVERRIDE;
  virtual void DidCommitProvisionalLoad(blink::WebLocalFrame* frame,
                                        bool is_new_navigation) OVERRIDE;
  virtual void Navigate(const GURL& url) OVERRIDE;

#if !defined(OS_ANDROID) && !defined(OS_IOS)
  void OnWebUIJavaScript(const base::string16& javascript);
#endif
#if defined(ENABLE_EXTENSIONS)
  void OnSetVisuallyDeemphasized(bool deemphasized);
#endif
#if defined(OS_ANDROID)
  void OnUpdateTopControlsState(content::TopControlsState constraints,
                                content::TopControlsState current,
                                bool animate);
  void OnRetrieveMetaTagContent(const GURL& expected_url,
                                const std::string tag_name);
#endif
  void OnGetWebApplicationInfo();
  void OnSetClientSidePhishingDetection(bool enable_phishing_detection);
  void OnSetWindowFeatures(const blink::WebWindowFeatures& window_features);

  void CapturePageInfoLater(bool preliminary_capture,
                            base::TimeDelta delay);

  
  
  void CapturePageInfo(bool preliminary_capture);

  
  
  void CaptureText(blink::WebFrame* frame, base::string16* contents);

  
  bool IsStrictSecurityHost(const std::string& host);

  
  bool HasRefreshMetaTag(blink::WebFrame* frame);

  
  std::vector<base::string16> webui_javascript_;

  
  web_cache::WebCacheRenderProcessObserver* web_cache_render_process_observer_;

  
  translate::TranslateHelper* translate_helper_;
  safe_browsing::PhishingClassifierDelegate* phishing_classifier_;

  
  scoped_ptr<WebViewColorOverlay> dimmed_color_overlay_;

  
  base::Timer capture_timer_;

  DISALLOW_COPY_AND_ASSIGN(ChromeRenderViewObserver);
};

#endif  
