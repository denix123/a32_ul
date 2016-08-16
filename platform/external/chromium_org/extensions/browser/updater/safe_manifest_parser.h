// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_UPDATER_SAFE_MANIFEST_PARSER_H_
#define EXTENSIONS_BROWSER_UPDATER_SAFE_MANIFEST_PARSER_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "content/public/browser/utility_process_host_client.h"
#include "extensions/browser/updater/manifest_fetch_data.h"
#include "extensions/common/update_manifest.h"

namespace extensions {

class SafeManifestParser : public content::UtilityProcessHostClient {
 public:
  
  typedef base::Callback<void(const ManifestFetchData&,
                              const UpdateManifest::Results*)> UpdateCallback;

  
  SafeManifestParser(const std::string& xml,
                     ManifestFetchData* fetch_data,
                     const UpdateCallback& update_callback);

  
  
  void Start();

 private:
  virtual ~SafeManifestParser();

  
  void ParseInSandbox();

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  void OnParseUpdateManifestSucceeded(const UpdateManifest::Results& results);
  void OnParseUpdateManifestFailed(const std::string& error_message);

  const std::string xml_;

  
  scoped_ptr<ManifestFetchData> fetch_data_;
  UpdateCallback update_callback_;

  DISALLOW_COPY_AND_ASSIGN(SafeManifestParser);
};

}  

#endif  
