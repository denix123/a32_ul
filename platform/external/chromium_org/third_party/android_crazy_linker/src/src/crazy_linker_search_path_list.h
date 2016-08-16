// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRAZY_LINKER_SEARCH_PATH_LIST_H
#define CRAZY_LINKER_SEARCH_PATH_LIST_H

#include <string.h>

#include "crazy_linker_util.h"  

namespace crazy {

class SearchPathList {
 public:
  SearchPathList() : list_(), env_list_(), full_path_() {}

  
  void Reset();

  
  void ResetFromEnv(const char* var_name);

  
  
  
  void AddPaths(const char* path_list, const char* path_list_end);

  
  void AddPaths(const char* path_list) {
    AddPaths(path_list, path_list + ::strlen(path_list));
  }

  
  
  
  const char* FindFile(const char* file_name);

 private:
  String list_;
  String env_list_;
  String full_path_;
};

}  

#endif  
