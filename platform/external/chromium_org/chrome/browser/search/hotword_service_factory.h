// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SEARCH_HOTWORD_SERVICE_FACTORY_H_
#define CHROME_BROWSER_SEARCH_HOTWORD_SERVICE_FACTORY_H_

#include "base/memory/singleton.h"
#include "chrome/browser/media/media_capture_devices_dispatcher.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

class HotwordService;
class Profile;

class HotwordServiceFactory : public MediaCaptureDevicesDispatcher::Observer,
                              public BrowserContextKeyedServiceFactory {
 public:
  
  static HotwordService* GetForProfile(content::BrowserContext* context);

  static HotwordServiceFactory* GetInstance();

  
  static bool IsServiceAvailable(content::BrowserContext* context);

  
  static bool IsHotwordAllowed(content::BrowserContext* context);

  
  
  static int GetCurrentError(content::BrowserContext* context);

  
  
  static bool IsMicrophoneAvailable();

  
  virtual void OnUpdateAudioDevices(
      const content::MediaStreamDevices& devices) OVERRIDE;

  
  
  
  
  
  
  void UpdateMicrophoneState();

 private:
  friend struct DefaultSingletonTraits<HotwordServiceFactory>;

  HotwordServiceFactory();
  virtual ~HotwordServiceFactory();

  
  virtual void RegisterProfilePrefs(
      user_prefs::PrefRegistrySyncable* registry) OVERRIDE;
  virtual KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* context) const OVERRIDE;

  
  
  void InitializeMicrophoneObserver();

  bool microphone_available() { return microphone_available_; }

  bool microphone_available_;

  DISALLOW_COPY_AND_ASSIGN(HotwordServiceFactory);
};

#endif  
