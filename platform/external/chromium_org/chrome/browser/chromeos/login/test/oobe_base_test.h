// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_TEST_OOBE_BASE_TEST_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_TEST_OOBE_BASE_TEST_H_

#include <string>

#include "base/callback.h"
#include "base/command_line.h"
#include "chrome/browser/chromeos/login/ui/login_display_host_impl.h"
#include "chrome/browser/chromeos/login/ui/webui_login_display.h"
#include "chrome/browser/extensions/extension_apitest.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "content/public/test/test_utils.h"
#include "google_apis/gaia/fake_gaia.h"
#include "net/test/embedded_test_server/embedded_test_server.h"

namespace content {
class WebUI;
}  

namespace chromeos {

class FakeUserManager;
class NetworkPortalDetectorTestImpl;
class SigninScreenHandler;

class OobeBaseTest : public ExtensionApiTest {
 public:
  OobeBaseTest();
  virtual ~OobeBaseTest();

 protected:
  
  virtual void SetUp() OVERRIDE;
  virtual void SetUpInProcessBrowserTestFixture() OVERRIDE;
  virtual void SetUpOnMainThread() OVERRIDE;
  virtual void TearDownOnMainThread() OVERRIDE;
  virtual void SetUpCommandLine(base::CommandLine* command_line) OVERRIDE;

  
  void SimulateNetworkOffline();
  void SimulateNetworkOnline();
  void SimulateNetworkPortal();

  base::Closure SimulateNetworkOfflineClosure();
  base::Closure SimulateNetworkOnlineClosure();
  base::Closure SimulateNetworkPortalClosure();

  
  void JsExpect(const std::string& expression);

  
  content::WebUI* GetLoginUI();

  
  SigninScreenHandler* GetSigninScreenHandler();

  
  WebUILoginDisplay* GetLoginDisplay();

  scoped_ptr<FakeGaia> fake_gaia_;
  NetworkPortalDetectorTestImpl* network_portal_detector_;

  
  
  bool needs_background_networking_;
};

}  

#endif  
