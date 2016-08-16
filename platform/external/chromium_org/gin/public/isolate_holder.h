// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GIN_PUBLIC_ISOLATE_HOLDER_H_
#define GIN_PUBLIC_ISOLATE_HOLDER_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "gin/gin_export.h"
#include "v8/include/v8.h"

namespace gin {

class PerIsolateData;
class RunMicrotasksObserver;

class GIN_EXPORT IsolateHolder {
 public:
  
  enum ScriptMode {
    kNonStrictMode,
    kStrictMode
  };

  IsolateHolder();
  ~IsolateHolder();

  
  
  static void Initialize(ScriptMode mode,
                         v8::ArrayBuffer::Allocator* allocator);

  v8::Isolate* isolate() { return isolate_; }

  
  
  
  
  
  
  void AddRunMicrotasksObserver();

  
  
  void RemoveRunMicrotasksObserver();

 private:
  v8::Isolate* isolate_;
  scoped_ptr<PerIsolateData> isolate_data_;
  scoped_ptr<RunMicrotasksObserver> task_observer_;

  DISALLOW_COPY_AND_ASSIGN(IsolateHolder);
};

}  

#endif  
