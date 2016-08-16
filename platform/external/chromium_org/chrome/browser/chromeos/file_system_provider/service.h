// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_SERVICE_H_
#define CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_SERVICE_H_

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "base/files/file.h"
#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/threading/thread_checker.h"
#include "base/values.h"
#include "chrome/browser/chromeos/file_system_provider/observer.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/common/extensions/api/file_system_provider.h"
#include "components/keyed_service/core/keyed_service.h"
#include "content/public/browser/browser_context.h"
#include "extensions/browser/extension_registry_observer.h"
#include "extensions/common/extension.h"

namespace extensions {
class ExtensionRegistry;
}  

namespace user_prefs {
class PrefRegistrySyncable;
}  

namespace chromeos {
namespace file_system_provider {

extern const char kPrefKeyFileSystemId[];
extern const char kPrefKeyDisplayName[];
extern const char kPrefKeyWritable[];

class ProvidedFileSystemFactoryInterface;
class ProvidedFileSystemInfo;
class ProvidedFileSystemInterface;
class ServiceFactory;

void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

class Service : public KeyedService,
                public extensions::ExtensionRegistryObserver {
 public:
  typedef base::Callback<ProvidedFileSystemInterface*(
      Profile* profile,
      const ProvidedFileSystemInfo& file_system_info)>
      FileSystemFactoryCallback;

  
  
  
  enum UnmountReason { UNMOUNT_REASON_USER, UNMOUNT_REASON_SHUTDOWN };

  Service(Profile* profile, extensions::ExtensionRegistry* extension_registry);
  virtual ~Service();

  
  
  void SetFileSystemFactoryForTesting(
      const FileSystemFactoryCallback& factory_callback);

  
  
  
  
  bool MountFileSystem(const std::string& extension_id,
                       const std::string& file_system_id,
                       const std::string& display_name,
                       bool writable);

  
  
  bool UnmountFileSystem(const std::string& extension_id,
                         const std::string& file_system_id,
                         UnmountReason reason);

  
  
  
  bool RequestUnmount(const std::string& extension_id,
                      const std::string& file_system_id);

  
  
  std::vector<ProvidedFileSystemInfo> GetProvidedFileSystemInfoList();

  
  
  ProvidedFileSystemInterface* GetProvidedFileSystem(
      const std::string& extension_id,
      const std::string& file_system_id);

  
  
  ProvidedFileSystemInterface* GetProvidedFileSystem(
      const std::string& mount_point_name);

  
  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  static Service* Get(content::BrowserContext* context);

  
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const extensions::Extension* extension,
      extensions::UnloadedExtensionInfo::Reason reason) OVERRIDE;
  virtual void OnExtensionLoaded(
      content::BrowserContext* browser_context,
      const extensions::Extension* extension) OVERRIDE;

 private:
  
  
  typedef std::pair<std::string, std::string> FileSystemKey;

  typedef std::map<FileSystemKey, ProvidedFileSystemInterface*>
      ProvidedFileSystemMap;
  typedef std::map<std::string, FileSystemKey> MountPointNameToKeyMap;

  
  
  void OnRequestUnmountStatus(const ProvidedFileSystemInfo& file_system_info,
                              base::File::Error error);

  
  
  void RememberFileSystem(const ProvidedFileSystemInfo& file_system_info);

  
  
  void ForgetFileSystem(const std::string& extension_id,
                        const std::string& file_system_id);

  
  
  void RestoreFileSystems(const std::string& extension_id);

  Profile* profile_;
  extensions::ExtensionRegistry* extension_registry_;  
  FileSystemFactoryCallback file_system_factory_;
  ObserverList<Observer> observers_;
  ProvidedFileSystemMap file_system_map_;  
  MountPointNameToKeyMap mount_point_name_to_key_map_;
  base::ThreadChecker thread_checker_;
  base::WeakPtrFactory<Service> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(Service);
};

}  
}  

#endif  
