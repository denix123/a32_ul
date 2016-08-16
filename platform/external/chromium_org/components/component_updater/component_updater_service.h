// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_COMPONENT_UPDATER_COMPONENT_UPDATER_SERVICE_H_
#define COMPONENTS_COMPONENT_UPDATER_COMPONENT_UPDATER_SERVICE_H_

#include <stdint.h>
#include <string>
#include <vector>

#include "base/callback_forward.h"
#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "base/version.h"
#include "url/gurl.h"

class ComponentsUI;

namespace base {
class DictionaryValue;
class FilePath;
class SequencedTaskRunner;
}

namespace net {
class URLRequestContextGetter;
class URLRequest;
}

namespace content {
class ResourceThrottle;
}

namespace component_updater {

class Configurator;
class OnDemandUpdater;

class ComponentInstaller {
 public:
  
  
  
  virtual void OnUpdateError(int error) = 0;

  
  
  
  
  
  virtual bool Install(const base::DictionaryValue& manifest,
                       const base::FilePath& unpack_path) = 0;

  
  
  
  
  virtual bool GetInstalledFile(const std::string& file,
                                base::FilePath* installed_file) = 0;

  virtual ~ComponentInstaller() {}
};

struct CrxComponent {
  std::vector<uint8_t> pk_hash;
  ComponentInstaller* installer;
  Version version;
  std::string fingerprint;
  std::string name;
  bool allow_background_download;
  CrxComponent();
  ~CrxComponent();
};

struct CrxUpdateItem;

class ComponentUpdateService {
 public:
  enum Status { kOk, kReplaced, kInProgress, kError };

  
  
  
  class Observer {
   public:
    enum Events {
      
      COMPONENT_UPDATER_STARTED,

      
      COMPONENT_UPDATER_SLEEPING,

      
      
      COMPONENT_UPDATE_FOUND,

      
      
      COMPONENT_UPDATE_READY,

      
      COMPONENT_UPDATED,

      
      
      COMPONENT_NOT_UPDATED,

      
      COMPONENT_UPDATE_DOWNLOADING,
    };

    virtual ~Observer() {}

    
    
    
    
    virtual void OnEvent(Events event, const std::string& id) = 0;
  };

  
  
  virtual void AddObserver(Observer* observer) = 0;

  
  
  virtual void RemoveObserver(Observer* observer) = 0;

  
  
  virtual Status Start() = 0;

  
  
  virtual Status Stop() = 0;

  
  
  virtual Status RegisterComponent(const CrxComponent& component) = 0;

  
  virtual std::vector<std::string> GetComponentIDs() const = 0;

  
  
  virtual OnDemandUpdater& GetOnDemandUpdater() = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  virtual void MaybeThrottle(const std::string& crx_id,
                             const base::Closure& callback) = 0;

  
  virtual scoped_refptr<base::SequencedTaskRunner> GetSequencedTaskRunner() = 0;

  virtual ~ComponentUpdateService() {}

 private:
  
  
  virtual bool GetComponentDetails(const std::string& component_id,
                                   CrxUpdateItem* item) const = 0;

  friend class ::ComponentsUI;
};

typedef ComponentUpdateService::Observer ServiceObserver;

class OnDemandUpdater {
 public:
  virtual ~OnDemandUpdater() {}

 private:
  friend class OnDemandTester;
  friend class ::ComponentsUI;

  
  
  
  
  
  
  virtual ComponentUpdateService::Status OnDemandUpdate(
      const std::string& component_id) = 0;
};

ComponentUpdateService* ComponentUpdateServiceFactory(Configurator* config);

}  

#endif  
