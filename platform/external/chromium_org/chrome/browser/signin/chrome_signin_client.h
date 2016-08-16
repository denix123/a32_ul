// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SIGNIN_CHROME_SIGNIN_CLIENT_H_
#define CHROME_BROWSER_SIGNIN_CHROME_SIGNIN_CLIENT_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "components/signin/core/browser/signin_client.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "content/public/browser/render_process_host_observer.h"

class CookieSettings;
class Profile;

class ChromeSigninClient : public SigninClient,
                           public content::NotificationObserver,
                           public content::RenderProcessHostObserver {
 public:
  explicit ChromeSigninClient(Profile* profile);
  virtual ~ChromeSigninClient();

  
  static bool ProfileAllowsSigninCookies(Profile* profile);
  static bool SettingsAllowSigninCookies(CookieSettings* cookie_settings);

  
  
  
  
  
  
  
  
  virtual void SetSigninProcess(int host_id) OVERRIDE;
  virtual void ClearSigninProcess() OVERRIDE;
  virtual bool IsSigninProcess(int host_id) const OVERRIDE;
  virtual bool HasSigninProcess() const OVERRIDE;

  
  virtual void RenderProcessHostDestroyed(content::RenderProcessHost* host)
      OVERRIDE;

  
  virtual PrefService* GetPrefs() OVERRIDE;
  virtual scoped_refptr<TokenWebData> GetDatabase() OVERRIDE;
  virtual bool CanRevokeCredentials() OVERRIDE;
  virtual std::string GetSigninScopedDeviceId() OVERRIDE;
  virtual void ClearSigninScopedDeviceId() OVERRIDE;
  virtual net::URLRequestContextGetter* GetURLRequestContext() OVERRIDE;
  virtual bool ShouldMergeSigninCredentialsIntoCookieJar() OVERRIDE;
  virtual bool IsFirstRun() const OVERRIDE;
  virtual base::Time GetInstallDate() OVERRIDE;

  
  
  
  virtual std::string GetProductVersion() OVERRIDE;
  virtual scoped_ptr<CookieChangedCallbackList::Subscription>
      AddCookieChangedCallback(const CookieChangedCallback& callback) OVERRIDE;
  virtual void GoogleSigninSucceeded(const std::string& account_id,
                                     const std::string& username,
                                     const std::string& password) OVERRIDE;

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

 private:
  void RegisterForCookieChangedNotification();
  void UnregisterForCookieChangedNotification();

  Profile* profile_;
  content::NotificationRegistrar registrar_;

  
  
  base::CallbackList<void(const net::CanonicalCookie* cookie)> callbacks_;

  
  
  int signin_host_id_;

  
  std::set<content::RenderProcessHost*> signin_hosts_observed_;

  DISALLOW_COPY_AND_ASSIGN(ChromeSigninClient);
};

#endif  
