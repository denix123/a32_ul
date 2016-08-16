// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NATIVE_CLIENT_SRC_TRUSTED_PLUGIN_PNACL_RESOURCES_H_
#define NATIVE_CLIENT_SRC_TRUSTED_PLUGIN_PNACL_RESOURCES_H_

#include <map>
#include <vector>

#include "native_client/src/include/nacl_macros.h"
#include "native_client/src/trusted/desc/nacl_desc_wrapper.h"

#include "ppapi/c/private/ppb_nacl_private.h"
#include "ppapi/cpp/completion_callback.h"

#include "ppapi/native_client/src/trusted/plugin/plugin_error.h"

namespace plugin {

class Plugin;

class PnaclResources {
 public:
  explicit PnaclResources(Plugin* plugin);
  virtual ~PnaclResources();

  
  
  bool ReadResourceInfo();

  
  bool StartLoad();

  const std::string& GetLlcUrl() { return llc_tool_name_; }
  const std::string& GetLdUrl() { return ld_tool_name_; }

  PP_NaClFileInfo TakeLlcFileInfo();
  PP_NaClFileInfo TakeLdFileInfo();

 private:
  NACL_DISALLOW_COPY_AND_ASSIGN(PnaclResources);

  
  Plugin* plugin_;

  
  std::string llc_tool_name_;
  std::string ld_tool_name_;

  
  
  
  PP_NaClFileInfo llc_file_info_;
  PP_NaClFileInfo ld_file_info_;
};

}  
#endif  
