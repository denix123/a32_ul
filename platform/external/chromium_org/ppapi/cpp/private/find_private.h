// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_CPP_PRIVATE_FIND_PRIVATE_H_
#define PPAPI_CPP_PRIVATE_FIND_PRIVATE_H_

#include <string>
#include <vector>

#include "ppapi/c/private/ppp_find_private.h"
#include "ppapi/cpp/instance_handle.h"

namespace pp {

class Instance;
class Rect;

class Find_Private {
 public:
  
  Find_Private(Instance* instance);
  virtual ~Find_Private();

  
  
  virtual bool StartFind(const std::string& text, bool case_sensitive) = 0;
  virtual void SelectFindResult(bool forward) = 0;
  virtual void StopFind() = 0;

  
  void SetPluginToHandleFindRequests();
  void NumberOfFindResultsChanged(int32_t total, bool final_result);
  void SelectedFindResultChanged(int32_t index);
  void SetTickmarks(const std::vector<pp::Rect>& tickmarks);

 private:
  InstanceHandle associated_instance_;
};

}  

#endif  
