// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_COMPONENT_LOADER_H_
#define CHROME_BROWSER_EXTENSIONS_COMPONENT_LOADER_H_

#include <string>
#include <vector>

#include "base/callback_forward.h"
#include "base/files/file_path.h"
#include "base/gtest_prod_util.h"
#include "base/memory/weak_ptr.h"
#include "base/values.h"

class ExtensionServiceInterface;
class PrefService;

namespace content {
class BrowserContext;
}

namespace extensions {

class ComponentLoader {
 public:
  ComponentLoader(ExtensionServiceInterface* extension_service,
                  PrefService* prefs,
                  PrefService* local_state,
                  content::BrowserContext* browser_context);
  virtual ~ComponentLoader();

  size_t registered_extensions_count() const {
    return component_extensions_.size();
  }

  
  void LoadAll();

  
  
  
  
  
  
  
  
  
  
  
  std::string Add(const std::string& manifest_contents,
                  const base::FilePath& root_directory);

  
  std::string Add(int manifest_resource_id,
                  const base::FilePath& root_directory);

  
  
  std::string AddOrReplace(const base::FilePath& path);

  
  
  std::string GetExtensionID(int manifest_resource_id,
                             const base::FilePath& root_directory);

  
  bool Exists(const std::string& id) const;

  
  
  void Remove(const base::FilePath& root_directory);
  void Remove(const std::string& id);

  
  
  static void EnableBackgroundExtensionsForTesting();

  
  
  
  
  void AddDefaultComponentExtensions(bool skip_session_components);

  
  void AddDefaultComponentExtensionsForKioskMode(bool skip_session_components);

  
  
  base::DictionaryValue* ParseManifest(
      const std::string& manifest_contents) const;

  
  void ClearAllRegistered();

  
  void Reload(const std::string& extension_id);

#if defined(OS_CHROMEOS)
  
  
  
  void AddChromeVoxExtension(const base::Closure& done_cb);
  std::string AddChromeOsSpeechSynthesisExtension();
#endif

 private:
  
  struct ComponentExtensionInfo {
    ComponentExtensionInfo(const base::DictionaryValue* manifest,
                           const base::FilePath& root_directory);

    
    const base::DictionaryValue* manifest;

    
    base::FilePath root_directory;

    
    std::string extension_id;
  };

  std::string Add(const base::DictionaryValue* parsed_manifest,
                  const base::FilePath& root_directory);

  
  void Load(const ComponentExtensionInfo& info);

  void AddDefaultComponentExtensionsWithBackgroundPages(
      bool skip_session_components);
  void AddFileManagerExtension();
  void AddVideoPlayerExtension();
  void AddGalleryExtension();
  void AddHangoutServicesExtension();
  void AddHotwordHelperExtension();
  void AddImageLoaderExtension();
  void AddNetworkSpeechSynthesisExtension();

  void AddWithNameAndDescription(int manifest_resource_id,
                                 const base::FilePath& root_directory,
                                 int name_string_id,
                                 int description_string_id);
  void AddChromeApp();
  void AddHotwordAudioVerificationApp();
  void AddKeyboardApp();
  void AddWebStoreApp();

  
  void UnloadComponent(ComponentExtensionInfo* component);

  
  void EnableFileSystemInGuestMode(const std::string& id);

#if defined(OS_CHROMEOS)
  
  
  
  void AddChromeVoxExtensionWithManifest(
      const base::FilePath& chromevox_path,
      const base::Closure& done_cb,
      scoped_ptr<base::DictionaryValue> manifest);
#endif

  PrefService* profile_prefs_;
  PrefService* local_state_;
  content::BrowserContext* browser_context_;

  ExtensionServiceInterface* extension_service_;

  
  typedef std::vector<ComponentExtensionInfo> RegisteredComponentExtensions;
  RegisteredComponentExtensions component_extensions_;

  base::WeakPtrFactory<ComponentLoader> weak_factory_;

  FRIEND_TEST_ALL_PREFIXES(TtsApiTest, NetworkSpeechEngine);
  FRIEND_TEST_ALL_PREFIXES(TtsApiTest, NoNetworkSpeechEngineWhenOffline);

  DISALLOW_COPY_AND_ASSIGN(ComponentLoader);
};

}  

#endif  
