// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_TRANSLATE_CLD_DATA_HARNESS_H_
#define CHROME_BROWSER_TRANSLATE_CLD_DATA_HARNESS_H_

#include "base/files/file_path.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"

namespace test {

class CldDataHarness {
 public:
  
  
  
  
  
  virtual ~CldDataHarness() {}

  
  
  virtual void Init() = 0;

 protected:
  
  
  
  
  
  const base::FilePath::CharType* GetTestDataSourceCrxVersion();

  
  
  
  void GetTestDataSourceDirectory(base::FilePath* out_path);
};

scoped_ptr<CldDataHarness> CreateCldDataHarness();

}  

#endif  
