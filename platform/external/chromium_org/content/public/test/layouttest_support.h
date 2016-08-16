// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_TEST_LAYOUTTEST_SUPPORT_H_
#define CONTENT_PUBLIC_TEST_LAYOUTTEST_SUPPORT_H_

#include <string>
#include <vector>

#include "base/callback_forward.h"
#include "cc/layers/texture_layer.h"
#include "third_party/WebKit/public/platform/WebScreenOrientationType.h"

class GURL;

namespace blink {
class WebBatteryStatus;
class WebDeviceMotionData;
class WebDeviceOrientationData;
class WebGamepad;
class WebGamepads;
class WebLayer;
struct WebSize;
class WebView;
class WebURLResponse;
}

namespace content {

class PageState;
class RenderFrame;
class RendererGamepadProvider;
class RenderView;
class WebTestProxyBase;

void EnableBrowserLayoutTestMode();


void EnableRendererLayoutTestMode();

void EnableWebTestProxyCreation(
    const base::Callback<void(RenderView*, WebTestProxyBase*)>& callback);

typedef base::Callback<void(const blink::WebURLResponse& response,
                            const std::string& data)> FetchManifestCallback;
void FetchManifest(blink::WebView* view, const GURL& url,
                   const FetchManifestCallback&);

void SetMockGamepadProvider(scoped_ptr<RendererGamepadProvider> provider);

void SetMockDeviceLightData(const double data);

void SetMockDeviceMotionData(const blink::WebDeviceMotionData& data);

void SetMockDeviceOrientationData(const blink::WebDeviceOrientationData& data);

void MockBatteryStatusChanged(const blink::WebBatteryStatus& status);

int GetLocalSessionHistoryLength(RenderView* render_view);

void SyncNavigationState(RenderView* render_view);

void SetFocusAndActivate(RenderView* render_view, bool enable);

void ForceResizeRenderView(RenderView* render_view,
                           const blink::WebSize& new_size);

void SetDeviceScaleFactor(RenderView* render_view, float factor);

void SetDeviceColorProfile(RenderView* render_view, const std::string& name);

// some tests that were written before browsers had multi-process architecture
void UseSynchronousResizeMode(RenderView* render_view, bool enable);

void EnableAutoResizeMode(RenderView* render_view,
                          const blink::WebSize& min_size,
                          const blink::WebSize& max_size);
void DisableAutoResizeMode(RenderView* render_view,
                           const blink::WebSize& new_size);

std::string DumpBackForwardList(std::vector<PageState>& page_state,
                                size_t current_index);

blink::WebLayer* InstantiateWebLayer(scoped_refptr<cc::TextureLayer> layer);

}  

#endif  
