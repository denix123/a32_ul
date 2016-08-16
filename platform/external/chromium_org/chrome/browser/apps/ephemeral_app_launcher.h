// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_APPS_EPHEMERAL_APP_LAUNCHER_H_
#define CHROME_BROWSER_APPS_EPHEMERAL_APP_LAUNCHER_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/scoped_observer.h"
#include "chrome/browser/extensions/webstore_standalone_installer.h"
#include "chrome/browser/ui/extensions/extension_enable_flow_delegate.h"
#include "content/public/browser/web_contents_observer.h"

class ExtensionEnableFlow;
class Profile;

namespace content {
class WebContents;
}

namespace extensions {
class Extension;
class ExtensionInstallChecker;
class ExtensionRegistry;
}

class EphemeralAppLauncher : public extensions::WebstoreStandaloneInstaller,
                             public content::WebContentsObserver,
                             public ExtensionEnableFlowDelegate {
 public:
  typedef base::Callback<void(extensions::webstore_install::Result result,
                              const std::string& error)> LaunchCallback;

  
  static bool IsFeatureEnabled();

  
  static scoped_refptr<EphemeralAppLauncher> CreateForLauncher(
      const std::string& webstore_item_id,
      Profile* profile,
      gfx::NativeWindow parent_window,
      const LaunchCallback& callback);

  
  static scoped_refptr<EphemeralAppLauncher> CreateForWebContents(
      const std::string& webstore_item_id,
      content::WebContents* web_contents,
      const LaunchCallback& callback);

  
  void Start();

 protected:
  EphemeralAppLauncher(const std::string& webstore_item_id,
                       Profile* profile,
                       gfx::NativeWindow parent_window,
                       const LaunchCallback& callback);
  EphemeralAppLauncher(const std::string& webstore_item_id,
                       content::WebContents* web_contents,
                       const LaunchCallback& callback);

  virtual ~EphemeralAppLauncher();

  
  virtual scoped_ptr<extensions::ExtensionInstallChecker>
      CreateInstallChecker();

  
  virtual scoped_ptr<ExtensionInstallPrompt> CreateInstallUI() OVERRIDE;
  virtual scoped_ptr<extensions::WebstoreInstaller::Approval> CreateApproval()
      const OVERRIDE;

 private:
  friend class base::RefCountedThreadSafe<EphemeralAppLauncher>;
  friend class EphemeralAppLauncherTest;

  
  
  bool CanLaunchInstalledApp(const extensions::Extension* extension,
                             extensions::webstore_install::Result* reason,
                             std::string* error);

  
  void EnableInstalledApp(const extensions::Extension* extension);

  
  
  void MaybeLaunchApp();

  
  
  void LaunchApp(const extensions::Extension* extension) const;

  
  bool LaunchHostedApp(const extensions::Extension* extension) const;

  
  void InvokeCallback(extensions::webstore_install::Result result,
                      const std::string& error);

  
  void AbortLaunch(extensions::webstore_install::Result result,
                   const std::string& error);

  
  void CheckEphemeralInstallPermitted();

  
  void OnInstallChecked(int check_failures);

  
  virtual void InitInstallData(
      extensions::ActiveInstallData* install_data) const OVERRIDE;
  virtual bool CheckRequestorAlive() const OVERRIDE;
  virtual const GURL& GetRequestorURL() const OVERRIDE;
  virtual bool ShouldShowPostInstallUI() const OVERRIDE;
  virtual bool ShouldShowAppInstalledBubble() const OVERRIDE;
  virtual content::WebContents* GetWebContents() const OVERRIDE;
  virtual scoped_refptr<ExtensionInstallPrompt::Prompt> CreateInstallPrompt()
      const OVERRIDE;
  virtual bool CheckInlineInstallPermitted(
      const base::DictionaryValue& webstore_data,
      std::string* error) const OVERRIDE;
  virtual bool CheckRequestorPermitted(
      const base::DictionaryValue& webstore_data,
      std::string* error) const OVERRIDE;
  virtual void OnManifestParsed() OVERRIDE;
  virtual void CompleteInstall(extensions::webstore_install::Result result,
                               const std::string& error) OVERRIDE;

  
  virtual void WebContentsDestroyed() OVERRIDE;

  
  virtual void ExtensionEnableFlowFinished() OVERRIDE;
  virtual void ExtensionEnableFlowAborted(bool user_initiated) OVERRIDE;

  LaunchCallback launch_callback_;

  gfx::NativeWindow parent_window_;
  scoped_ptr<content::WebContents> dummy_web_contents_;

  scoped_ptr<ExtensionEnableFlow> extension_enable_flow_;

  scoped_ptr<extensions::ExtensionInstallChecker> install_checker_;

  DISALLOW_COPY_AND_ASSIGN(EphemeralAppLauncher);
};

#endif  
