// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_COMPONENT_UPDATER_COMPONENT_UPDATER_CONFIGURATOR_H_
#define COMPONENTS_COMPONENT_UPDATER_COMPONENT_UPDATER_CONFIGURATOR_H_

#include <string>
#include <vector>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"

class GURL;

namespace base {
class SingleThreadTaskRunner;
class SequencedTaskRunner;
class Version;
}

namespace net {
class URLRequestContextGetter;
}

namespace component_updater {

class OutOfProcessPatcher;

class Configurator {
 public:
  virtual ~Configurator() {}

  
  virtual int InitialDelay() const = 0;

  
  
  virtual int NextCheckDelay() = 0;

  
  virtual int StepDelay() const = 0;

  
  
  
  virtual int StepDelayMedium() = 0;

  
  virtual int MinimumReCheckWait() const = 0;

  
  
  virtual int OnDemandDelay() const = 0;

  
  
  virtual std::vector<GURL> UpdateUrl() const = 0;

  
  
  virtual std::vector<GURL> PingUrl() const = 0;

  
  virtual base::Version GetBrowserVersion() const = 0;

  
  
  
  virtual std::string GetChannel() const = 0;

  
  
  virtual std::string GetLang() const = 0;

  
  virtual std::string GetOSLongName() const = 0;

  
  
  
  virtual std::string ExtraRequestParams() const = 0;

  
  virtual size_t UrlSizeLimit() const = 0;

  
  virtual net::URLRequestContextGetter* RequestContext() const = 0;

  
  
  virtual scoped_refptr<OutOfProcessPatcher> CreateOutOfProcessPatcher()
      const = 0;

  
  virtual bool DeltasEnabled() const = 0;

  
  
  virtual bool UseBackgroundDownloader() const = 0;

  
  virtual scoped_refptr<base::SequencedTaskRunner> GetSequencedTaskRunner()
      const = 0;

  
  
  
  virtual scoped_refptr<base::SingleThreadTaskRunner>
      GetSingleThreadTaskRunner() const = 0;
};

}  

#endif  
