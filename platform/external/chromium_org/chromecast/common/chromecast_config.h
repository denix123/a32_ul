// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_COMMON_CHROMECAST_CONFIG_H_
#define CHROMECAST_COMMON_CHROMECAST_CONFIG_H_

#include <string>

#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/prefs/pref_service.h"
#include "base/threading/sequenced_worker_pool.h"
#include "base/threading/thread_checker.h"

class PrefRegistrySimple;

namespace chromecast {

class ChromecastConfig {
 public:
  
  static void Create(PrefRegistrySimple* registry);

  
  static ChromecastConfig* GetInstance();

  
  void Save() const;

  
  const std::string GetValue(const std::string& key) const;

  
  const int GetIntValue(const std::string& key) const;

  
  void SetValue(const std::string& key, const std::string& value) const;

  
  void SetIntValue(const std::string& key, int value) const;

  
  bool HasValue(const std::string& key) const;

  scoped_refptr<base::SequencedWorkerPool> worker_pool() const {
    return worker_pool_;
  }

  PrefService* pref_service() const { return pref_service_.get(); }

 private:
  ChromecastConfig();
  ~ChromecastConfig();

  
  bool Load(PrefRegistrySimple* registry);

  
  void RegisterPlatformPrefs(PrefRegistrySimple* registry);

  
  static ChromecastConfig* g_instance_;

  const base::FilePath config_path_;
  const scoped_refptr<base::SequencedWorkerPool> worker_pool_;
  scoped_ptr<PrefService> pref_service_;

  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(ChromecastConfig);
};

}  

#endif  
