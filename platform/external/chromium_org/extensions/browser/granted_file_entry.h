// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_GRANTED_FILE_ENTRY_H_
#define EXTENSIONS_BROWSER_GRANTED_FILE_ENTRY_H_

#include <string>

namespace extensions {

struct GrantedFileEntry {
  GrantedFileEntry();
  ~GrantedFileEntry();

  std::string id;
  std::string filesystem_id;
  std::string registered_name;
};

}  

#endif  
