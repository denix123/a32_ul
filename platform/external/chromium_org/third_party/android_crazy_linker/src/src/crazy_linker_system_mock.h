// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRAZY_LINKER_SYSTEM_MOCK_H
#define CRAZY_LINKER_SYSTEM_MOCK_H

#include <stdint.h>

namespace crazy {

class SystemMock {
 public:
  
  
  SystemMock();

  
  ~SystemMock();

  
  
  
  void AddRegularFile(const char* path, const char* data, size_t data_size);

  void AddEnvVariable(const char* var_name, const char* var_value);

  void SetCurrentDir(const char* path);
};

}  

#endif  
