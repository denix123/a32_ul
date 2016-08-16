// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_NACL_RENDERER_JSON_MANIFEST_H
#define COMPONENTS_NACL_RENDERER_JSON_MANIFEST_H

#include <set>
#include <string>

#include "base/memory/scoped_ptr.h"
#include "ppapi/c/pp_array_output.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/c/private/ppb_nacl_private.h"
#include "third_party/jsoncpp/source/include/json/value.h"

namespace nacl {
class JsonManifest;
class NexeLoadManager;

void AddJsonManifest(PP_Instance instance, scoped_ptr<JsonManifest> manifest);

JsonManifest* GetJsonManifest(PP_Instance instance);
void DeleteJsonManifest(PP_Instance instance);

class JsonManifest {
 public:
  struct ErrorInfo {
    PP_NaClError error;
    std::string string;
  };

  JsonManifest(const std::string& manifest_base_url,
               const std::string& sandbox_isa,
               bool nonsfi_enabled,
               bool pnacl_debug);

  
  
  bool Init(const std::string& json_manifest, ErrorInfo* error_info);

  
  
  bool GetProgramURL(std::string* full_url,
                     PP_PNaClOptions* pnacl_options,
                     bool* uses_nonsfi_mode,
                     ErrorInfo* error_info) const;

  
  
  
  
  bool ResolveKey(const std::string& key,
                  std::string* full_url,
                  PP_PNaClOptions* pnacl_options) const;

 private:
  bool MatchesSchema(ErrorInfo* error_info);
  bool GetKeyUrl(const Json::Value& dictionary,
                 const std::string& key,
                 std::string* full_url,
                 PP_PNaClOptions* pnacl_options) const;
  bool GetURLFromISADictionary(const Json::Value& dictionary,
                               const std::string& parent_key,
                               std::string* url,
                               PP_PNaClOptions* pnacl_options,
                               bool* uses_nonsfi_mode,
                               ErrorInfo* error_info) const;

  std::string manifest_base_url_;
  std::string sandbox_isa_;
  bool nonsfi_enabled_;
  bool pnacl_debug_;

  
  Json::Value dictionary_;
};

}  

#endif  
