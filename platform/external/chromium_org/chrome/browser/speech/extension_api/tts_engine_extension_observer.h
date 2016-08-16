// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SPEECH_EXTENSION_API_TTS_ENGINE_EXTENSION_OBSERVER_H_
#define CHROME_BROWSER_SPEECH_EXTENSION_API_TTS_ENGINE_EXTENSION_OBSERVER_H_

#include "base/scoped_observer.h"
#include "components/keyed_service/core/keyed_service.h"
#include "extensions/browser/event_router.h"
#include "extensions/browser/extension_registry.h"
#include "extensions/browser/extension_registry_observer.h"

class Profile;

class TtsEngineExtensionObserver
    : public KeyedService,
      public extensions::EventRouter::Observer,
      public extensions::ExtensionRegistryObserver {
 public:
  static TtsEngineExtensionObserver* GetInstance(Profile* profile);

  
  
  bool SawExtensionLoad(const std::string& extension_id, bool update);

  
  virtual void Shutdown() OVERRIDE;

  
  virtual void OnListenerAdded(
      const extensions::EventListenerInfo& details) OVERRIDE;

  
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const extensions::Extension* extension,
      extensions::UnloadedExtensionInfo::Reason reason) OVERRIDE;

 private:
  explicit TtsEngineExtensionObserver(Profile* profile);
  virtual ~TtsEngineExtensionObserver();

  bool IsLoadedTtsEngine(const std::string& extension_id);

  ScopedObserver<extensions::ExtensionRegistry,
                 extensions::ExtensionRegistryObserver>
      extension_registry_observer_;

  Profile* profile_;

  std::set<std::string> engine_extension_ids_;

  friend class TtsEngineExtensionObserverFactory;

  DISALLOW_COPY_AND_ASSIGN(TtsEngineExtensionObserver);
};

#endif  
