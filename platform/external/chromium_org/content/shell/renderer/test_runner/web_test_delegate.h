// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_SHELL_RENDERER_TEST_RUNNER_WEB_TEST_DELEGATE_H_
#define CONTENT_SHELL_RENDERER_TEST_RUNNER_WEB_TEST_DELEGATE_H_

#include <string>

#include "third_party/WebKit/public/platform/WebScreenOrientationType.h"
#include "third_party/WebKit/public/platform/WebString.h"
#include "third_party/WebKit/public/platform/WebURL.h"
#include "third_party/WebKit/public/platform/WebVector.h"
#include "third_party/WebKit/public/web/WebNotificationPresenter.h"

#define WEBTESTRUNNER_NEW_HISTORY_CAPTURE

namespace blink {
class WebBatteryStatus;
class WebDeviceMotionData;
class WebDeviceOrientationData;
class WebFrame;
class WebGamepad;
class WebGamepads;
class WebHistoryItem;
struct WebRect;
struct WebSize;
struct WebURLError;
}

namespace content {

class DeviceLightData;
class RendererGamepadProvider;
class WebTask;
class WebTestProxyBase;
struct TestPreferences;

class WebTestDelegate {
 public:
  
  
  virtual void ClearEditCommand() = 0;
  virtual void SetEditCommand(const std::string& name,
                              const std::string& value) = 0;

  
  virtual void SetGamepadProvider(
      scoped_ptr<RendererGamepadProvider> provider) = 0;

  
  
  virtual void SetDeviceLightData(const double data) = 0;
  
  
  virtual void SetDeviceMotionData(const blink::WebDeviceMotionData& data) = 0;
  
  
  virtual void SetDeviceOrientationData(
      const blink::WebDeviceOrientationData& data) = 0;

  
  
  virtual void SetScreenOrientation(
      const blink::WebScreenOrientationType& orientation) = 0;

  
  virtual void ResetScreenOrientation() = 0;

  
  virtual void DidChangeBatteryStatus(
      const blink::WebBatteryStatus& status) = 0;

  
  virtual void PrintMessage(const std::string& message) = 0;

  
  
  virtual void PostTask(WebTask* task) = 0;
  virtual void PostDelayedTask(WebTask* task, long long ms) = 0;

  
  
  virtual blink::WebString RegisterIsolatedFileSystem(
      const blink::WebVector<blink::WebString>& absolute_filenames) = 0;

  
  virtual long long GetCurrentTimeInMillisecond() = 0;

  
  virtual blink::WebString GetAbsoluteWebStringFromUTF8Path(
      const std::string& path) = 0;

  
  virtual blink::WebURL LocalFileToDataURL(const blink::WebURL& file_url) = 0;

  
  
  virtual blink::WebURL RewriteLayoutTestsURL(const std::string& utf8_url) = 0;

  
  virtual TestPreferences* Preferences() = 0;
  virtual void ApplyPreferences() = 0;

  
  
  
  // that were written
  
  
  
  
  
  
  virtual void UseUnfortunateSynchronousResizeMode(bool enable) = 0;

  
  virtual void EnableAutoResizeMode(const blink::WebSize& min_size,
                                    const blink::WebSize& max_size) = 0;
  virtual void DisableAutoResizeMode(const blink::WebSize& new_size) = 0;

  
  virtual void ClearDevToolsLocalStorage() = 0;

  
  virtual void ShowDevTools(const std::string& settings,
                            const std::string& frontend_url) = 0;
  virtual void CloseDevTools() = 0;

  
  virtual void EvaluateInWebInspector(long call_id,
                                      const std::string& script) = 0;

  
  virtual void ClearAllDatabases() = 0;
  virtual void SetDatabaseQuota(int quota) = 0;

  
  virtual blink::WebNotificationPresenter::Permission
      CheckWebNotificationPermission(const GURL& origin) = 0;
  virtual void GrantWebNotificationPermission(const GURL& origin,
                                              bool permission_granted) = 0;
  virtual void ClearWebNotificationPermissions() = 0;

  
  virtual void SetDeviceScaleFactor(float factor) = 0;

  
  virtual void SetDeviceColorProfile(const std::string& name) = 0;

  
  virtual void SetFocus(WebTestProxyBase* proxy, bool focus) = 0;

  
  
  virtual void SetAcceptAllCookies(bool accept) = 0;

  
  
  virtual std::string PathToLocalResource(const std::string& resource) = 0;

  
  virtual void SetLocale(const std::string& locale) = 0;

  
  virtual void TestFinished() = 0;

  
  virtual void CloseRemainingWindows() = 0;

  virtual void DeleteAllCookies() = 0;

  
  virtual int NavigationEntryCount() = 0;

  
  virtual void GoToOffset(int offset) = 0;
  virtual void Reload() = 0;
  virtual void LoadURLForFrame(const blink::WebURL& url,
                               const std::string& frame_name) = 0;

  
  virtual bool AllowExternalPages() = 0;

  
  
  virtual std::string DumpHistoryForWindow(WebTestProxyBase* proxy) = 0;
};

}  

#endif  
