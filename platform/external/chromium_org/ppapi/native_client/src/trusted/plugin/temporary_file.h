// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NATIVE_CLIENT_SRC_TRUSTED_PLUGIN_TEMPORARY_FILE_H_
#define NATIVE_CLIENT_SRC_TRUSTED_PLUGIN_TEMPORARY_FILE_H_

#include "native_client/src/include/nacl_macros.h"
#include "native_client/src/trusted/desc/nacl_desc_wrapper.h"

#include "ppapi/c/private/pp_file_handle.h"

namespace plugin {

class Plugin;

//     written by: llc     (passed in explicitly through SRPC)
//     written by: ld      (passed in explicitly through SRPC)

class TempFile {
 public:
  
  TempFile(Plugin* plugin, PP_FileHandle handle);
  ~TempFile();

  
  
  
  int32_t Open(bool writeable);
  
  bool Reset();

  
  
  nacl::DescWrapper* write_wrapper() { return write_wrapper_.get(); }
  nacl::DescWrapper* read_wrapper() { return read_wrapper_.get(); }

  
  
  PP_FileHandle TakeFileHandle();

 private:
  NACL_DISALLOW_COPY_AND_ASSIGN(TempFile);

  Plugin* plugin_;
  nacl::scoped_ptr<nacl::DescWrapper> read_wrapper_;
  nacl::scoped_ptr<nacl::DescWrapper> write_wrapper_;
  PP_FileHandle internal_handle_;
};

}  

#endif  
