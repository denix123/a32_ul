// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SEARCH_HOTWORD_SERVICE_H_
#define CHROME_BROWSER_SEARCH_HOTWORD_SERVICE_H_

#include "base/basictypes.h"
#include "base/memory/weak_ptr.h"
#include "base/prefs/pref_change_registrar.h"
#include "base/scoped_observer.h"
#include "components/keyed_service/core/keyed_service.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "extensions/browser/extension_registry.h"
#include "extensions/browser/extension_registry_observer.h"

class ExtensionService;
class HotwordClient;
class Profile;

namespace extensions {
class Extension;
class WebstoreStandaloneInstaller;
}  

namespace hotword_internal {
extern const char kHotwordFieldTrialName[];
extern const char kHotwordFieldTrialDisabledGroupName[];
}  

class HotwordService : public content::NotificationObserver,
                       public extensions::ExtensionRegistryObserver,
                       public KeyedService {
 public:
  
  static bool DoesHotwordSupportLanguage(Profile* profile);

  
  static bool IsExperimentalHotwordingEnabled();

  explicit HotwordService(Profile* profile);
  virtual ~HotwordService();

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual void OnExtensionInstalled(
      content::BrowserContext* browser_context,
      const extensions::Extension* extension,
      bool is_update) OVERRIDE;
  virtual void OnExtensionUninstalled(
      content::BrowserContext* browser_context,
      const extensions::Extension* extension,
      extensions::UninstallReason reason) OVERRIDE;

  
  
  virtual bool IsServiceAvailable();

  
  
  virtual bool IsHotwordAllowed();

  
  
  bool IsOptedIntoAudioLogging();

  
  void EnableHotwordExtension(ExtensionService* extension_service);
  void DisableHotwordExtension(ExtensionService* extension_service);

  
  
  void OnHotwordSearchEnabledChanged(const std::string& pref_name);

  
  void RequestHotwordSession(HotwordClient* client);
  void StopHotwordSession(HotwordClient* client);
  HotwordClient* client() { return client_; }

  
  
  
  bool MaybeReinstallHotwordExtension();

  
  
  bool ShouldReinstallHotwordExtension();

  
  
  virtual bool UninstallHotwordExtension(ExtensionService* extension_service);
  virtual void InstallHotwordExtensionFromWebstore();

  
  void SetPreviousLanguagePref();

  
  
  int error_message() { return error_message_; }

  
  
  
  
  
  
  
  enum LaunchMode {
    AUDIO_HISTORY_ONLY,
    HOTWORD_ONLY,
    HOTWORD_AND_AUDIO_HISTORY,
    SPEECH_TRAINING
  };
  void LaunchHotwordAudioVerificationApp(const LaunchMode& launch_mode);
  virtual LaunchMode GetHotwordAudioVerificationLaunchMode();

 private:
  Profile* profile_;

  PrefChangeRegistrar pref_registrar_;

  content::NotificationRegistrar registrar_;

  
  ScopedObserver<extensions::ExtensionRegistry,
                 extensions::ExtensionRegistryObserver>
      extension_registry_observer_;

  scoped_refptr<extensions::WebstoreStandaloneInstaller> installer_;

  HotwordClient* client_;
  int error_message_;
  bool reinstall_pending_;

  base::WeakPtrFactory<HotwordService> weak_factory_;

  
  LaunchMode hotword_audio_verification_launch_mode_;

  DISALLOW_COPY_AND_ASSIGN(HotwordService);
};

#endif  
