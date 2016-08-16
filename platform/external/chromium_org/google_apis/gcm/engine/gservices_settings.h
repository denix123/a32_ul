// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GOOGLE_APIS_GCM_ENGINE_GSERVICES_SETTINGS_H_
#define GOOGLE_APIS_GCM_ENGINE_GSERVICES_SETTINGS_H_

#include <map>
#include <string>

#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "google_apis/gcm/base/gcm_export.h"
#include "google_apis/gcm/engine/gcm_store.h"
#include "google_apis/gcm/protocol/checkin.pb.h"
#include "url/gurl.h"

namespace gcm {

class GCM_EXPORT GServicesSettings {
 public:
  typedef std::map<std::string, std::string> SettingsMap;

  
  static const base::TimeDelta MinimumCheckinInterval();

  
  static const GURL DefaultCheckinURL();

  
  static std::string CalculateDigest(const SettingsMap& settings);

  GServicesSettings();
  ~GServicesSettings();

  
  bool UpdateFromCheckinResponse(
      const checkin_proto::AndroidCheckinResponse& checkin_response);

  
  
  void UpdateFromLoadResult(const GCMStore::LoadResult& load_result);

  SettingsMap settings_map() const { return settings_; }

  std::string digest() const { return digest_; }

  
  base::TimeDelta GetCheckinInterval() const;

  
  GURL GetCheckinURL() const;

  
  GURL GetMCSMainEndpoint() const;

  
  GURL GetMCSFallbackEndpoint() const;

  
  GURL GetRegistrationURL() const;

 private:
  
  
  
  std::string digest_;

  
  SettingsMap settings_;

  
  base::WeakPtrFactory<GServicesSettings> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(GServicesSettings);
};

}  

#endif  
