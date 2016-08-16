// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_NET_CRL_SET_FETCHER_H_
#define CHROME_BROWSER_NET_CRL_SET_FETCHER_H_

#include <string>

#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "components/component_updater/component_updater_service.h"

namespace base {
class DictionaryValue;
class FilePath;
}

namespace net {
class CRLSet;
}

class CRLSetFetcher : public component_updater::ComponentInstaller,
                      public base::RefCountedThreadSafe<CRLSetFetcher> {
 public:
  CRLSetFetcher();

  void StartInitialLoad(component_updater::ComponentUpdateService* cus,
                        const base::FilePath& path);

  
  void DeleteFromDisk(const base::FilePath& path);

  
  virtual void OnUpdateError(int error) OVERRIDE;
  virtual bool Install(const base::DictionaryValue& manifest,
                       const base::FilePath& unpack_path) OVERRIDE;
  virtual bool GetInstalledFile(const std::string& file,
                                base::FilePath* installed_file) OVERRIDE;

 private:
  friend class base::RefCountedThreadSafe<CRLSetFetcher>;

  virtual ~CRLSetFetcher();

  
  
  base::FilePath GetCRLSetFilePath() const;

  
  void SetCRLSetFilePath(const base::FilePath& path);

  
  
  
  void DoInitialLoadFromDisk();

  
  
  void LoadFromDisk(base::FilePath load_from,
                    scoped_refptr<net::CRLSet>* out_crl_set);

  
  
  void SetCRLSetIfNewer(scoped_refptr<net::CRLSet> crl_set);

  
  void RegisterComponent(uint32 sequence_of_loaded_crl);

  
  
  void DoDeleteFromDisk();

  component_updater::ComponentUpdateService* cus_;

  
  base::FilePath crl_path_;

  
  
  scoped_refptr<net::CRLSet> crl_set_;

  DISALLOW_COPY_AND_ASSIGN(CRLSetFetcher);
};

#endif  
