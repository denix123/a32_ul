// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_INPUT_INPUT_HANDLER_PROXY_CLIENT_H_
#define CONTENT_RENDERER_INPUT_INPUT_HANDLER_PROXY_CLIENT_H_

namespace blink {
class WebGestureCurve;
struct WebActiveWheelFlingParameters;
struct WebFloatPoint;
struct WebSize;
}

namespace content {

struct DidOverscrollParams;

class InputHandlerProxyClient {
 public:
  
  virtual void WillShutdown() = 0;

  
  
  virtual void TransferActiveWheelFlingAnimation(
      const blink::WebActiveWheelFlingParameters& params) = 0;

  
  
  virtual blink::WebGestureCurve* CreateFlingAnimationCurve(
      blink::WebGestureDevice device_source,
      const blink::WebFloatPoint& velocity,
      const blink::WebSize& cumulative_scroll) = 0;

  virtual void DidOverscroll(const DidOverscrollParams& params) = 0;

  virtual void DidStopFlinging() = 0;

  virtual void DidReceiveInputEvent() = 0;

 protected:
  virtual ~InputHandlerProxyClient() {}
};

}  

#endif  
