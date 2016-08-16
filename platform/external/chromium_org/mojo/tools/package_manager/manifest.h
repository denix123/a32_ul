// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_TOOLS_PACKAGE_MANAGER_MANIFEST_H_
#define MOJO_TOOLS_PACKAGE_MANAGER_MANIFEST_H_

#include <string>
#include <vector>

#include "mojo/public/cpp/system/macros.h"

class GURL;

namespace base {
class DictionaryValue;
class FilePath;
}

namespace mojo {

class Manifest {
 public:
  Manifest();
  ~Manifest();

  
  
  bool Parse(const std::string& str, std::string* err_msg);

  
  bool ParseFromFile(const base::FilePath& file_name, std::string* err_msg);

  const std::vector<GURL>& deps() const { return deps_; }

 private:
  bool PopulateDeps(const base::DictionaryValue* root, std::string* err_msg);

  std::vector<GURL> deps_;

  MOJO_DISALLOW_COPY_AND_ASSIGN(Manifest);
};

}  

#endif  
