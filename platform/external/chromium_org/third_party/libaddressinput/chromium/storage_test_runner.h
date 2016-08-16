// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_LIBADDRESSINPUT_CHROMIUM_STORAGE_TEST_RUNNER_H_
#define THIRD_PARTY_LIBADDRESSINPUT_CHROMIUM_STORAGE_TEST_RUNNER_H_

#include "third_party/libaddressinput/src/cpp/include/libaddressinput/storage.h"

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"

namespace autofill {

class StorageTestRunner {
 public:
  
  explicit StorageTestRunner(::i18n::addressinput::Storage* storage);
  ~StorageTestRunner();

  
  void RunAllTests();

 private:
  void ClearValues();
  scoped_ptr< ::i18n::addressinput::Storage::Callback> BuildCallback();
  void OnDataReady(bool success, const std::string& key, std::string* data);

  
  void GetWithoutPutReturnsEmptyData();
  void GetReturnsWhatWasPut();
  void SecondPutOverwritesData();

  ::i18n::addressinput::Storage* storage_;  
  bool success_;
  std::string key_;
  std::string data_;

  DISALLOW_COPY_AND_ASSIGN(StorageTestRunner);
};

}  

#endif  
