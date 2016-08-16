// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_TEST_RENDER_VIEW_TEST_H_
#define CONTENT_PUBLIC_TEST_RENDER_VIEW_TEST_H_

#include <string>

#include "base/command_line.h"
#include "base/memory/scoped_ptr.h"
#include "base/message_loop/message_loop.h"
#include "base/strings/string16.h"
#include "content/public/browser/native_web_keyboard_event.h"
#include "content/public/common/main_function_params.h"
#include "content/public/common/page_state.h"
#include "content/public/test/mock_render_thread.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "third_party/WebKit/public/platform/Platform.h"
#include "third_party/WebKit/public/web/WebFrame.h"

struct ViewMsg_Resize_Params;

namespace blink {
class WebWidget;
}

namespace gfx {
class Rect;
}

namespace content {
class ContentBrowserClient;
class ContentClient;
class ContentRendererClient;
class MockRenderProcess;
class PageState;
class RendererMainPlatformDelegate;
class RendererWebKitPlatformSupportImplNoSandboxImpl;
class RenderView;

class RenderViewTest : public testing::Test {
 public:
  
  
  class RendererWebKitPlatformSupportImplNoSandbox {
   public:
    RendererWebKitPlatformSupportImplNoSandbox();
    ~RendererWebKitPlatformSupportImplNoSandbox();
    blink::Platform* Get();

   private:
    scoped_ptr<RendererWebKitPlatformSupportImplNoSandboxImpl>
        webkit_platform_support_;
  };

  RenderViewTest();
  virtual ~RenderViewTest();

 protected:
  
  void ProcessPendingMessages();

  
  blink::WebLocalFrame* GetMainFrame();

  
  
  void ExecuteJavaScript(const char* js);

  
  
  
  
  bool ExecuteJavaScriptAndReturnIntValue(const base::string16& script,
                                          int* result);

  
  
  void LoadHTML(const char* html);

  
  PageState GetCurrentPageState();

  
  
  void GoBack(const PageState& state);
  void GoForward(const PageState& state);

  
  void SendNativeKeyEvent(const NativeWebKeyboardEvent& key_event);

  
  void SendWebKeyboardEvent(const blink::WebKeyboardEvent& key_event);

  
  void SendWebMouseEvent(const blink::WebMouseEvent& key_event);

  
  
  gfx::Rect GetElementBounds(const std::string& element_id);

  
  
  
  bool SimulateElementClick(const std::string& element_id);

  
  void SetFocused(const blink::WebNode& node);

  
  void ClearHistory();

  
  void Reload(const GURL& url);

  
  uint32 GetNavigationIPCType();

  
  void Resize(gfx::Size new_size,
              gfx::Rect resizer_rect,
              bool is_fullscreen);

  
  bool OnMessageReceived(const IPC::Message& msg);
  void DidNavigateWithinPage(blink::WebLocalFrame* frame,
                             bool is_new_navigation);
  void SendContentStateImmediately();
  blink::WebWidget* GetWebWidget();

  
  virtual ContentClient* CreateContentClient();
  virtual ContentBrowserClient* CreateContentBrowserClient();
  virtual ContentRendererClient* CreateContentRendererClient();

  
  virtual scoped_ptr<ViewMsg_Resize_Params> InitialSizeParams();

  
  virtual void SetUp() OVERRIDE;

  virtual void TearDown() OVERRIDE;

  base::MessageLoop msg_loop_;
  scoped_ptr<MockRenderProcess> mock_process_;
  
  
  RenderView* view_;
  RendererWebKitPlatformSupportImplNoSandbox webkit_platform_support_;
  scoped_ptr<ContentClient> content_client_;
  scoped_ptr<ContentBrowserClient> content_browser_client_;
  scoped_ptr<ContentRendererClient> content_renderer_client_;
  scoped_ptr<MockRenderThread> render_thread_;

  
  scoped_ptr<RendererMainPlatformDelegate> platform_;
  scoped_ptr<MainFunctionParams> params_;
  scoped_ptr<base::CommandLine> command_line_;

#if defined(OS_MACOSX)
  scoped_ptr<base::mac::ScopedNSAutoreleasePool> autorelease_pool_;
#endif

 private:
  void GoToOffset(int offset, const PageState& state);
};

}  

#endif  
