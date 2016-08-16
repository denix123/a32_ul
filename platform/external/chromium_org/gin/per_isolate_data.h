// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GIN_PER_ISOLATE_DATA_H_
#define GIN_PER_ISOLATE_DATA_H_

#include <map>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "gin/gin_export.h"
#include "gin/public/wrapper_info.h"
#include "v8/include/v8.h"

namespace base {
class MessageLoopProxy;
}

namespace gin {

class IndexedPropertyInterceptor;
class NamedPropertyInterceptor;
class WrappableBase;

class GIN_EXPORT PerIsolateData {
 public:
  PerIsolateData(v8::Isolate* isolate, v8::ArrayBuffer::Allocator* allocator);
  ~PerIsolateData();

  static PerIsolateData* From(v8::Isolate* isolate);

  
  
  
  void SetObjectTemplate(WrapperInfo* info,
                         v8::Local<v8::ObjectTemplate> object_template);
  void SetFunctionTemplate(WrapperInfo* info,
                           v8::Local<v8::FunctionTemplate> function_template);

  
  
  
  
  v8::Local<v8::ObjectTemplate> GetObjectTemplate(WrapperInfo* info);
  v8::Local<v8::FunctionTemplate> GetFunctionTemplate(WrapperInfo* info);

  
  
  void SetIndexedPropertyInterceptor(WrappableBase* base,
                                     IndexedPropertyInterceptor* interceptor);
  void SetNamedPropertyInterceptor(WrappableBase* base,
                                   NamedPropertyInterceptor* interceptor);

  void ClearIndexedPropertyInterceptor(WrappableBase* base,
                                       IndexedPropertyInterceptor* interceptor);
  void ClearNamedPropertyInterceptor(WrappableBase* base,
                                     NamedPropertyInterceptor* interceptor);

  IndexedPropertyInterceptor* GetIndexedPropertyInterceptor(
      WrappableBase* base);
  NamedPropertyInterceptor* GetNamedPropertyInterceptor(WrappableBase* base);

  v8::Isolate* isolate() { return isolate_; }
  v8::ArrayBuffer::Allocator* allocator() { return allocator_; }
  base::MessageLoopProxy* message_loop_proxy() {
    return message_loop_proxy_.get();
  }

 private:
  typedef std::map<
      WrapperInfo*, v8::Eternal<v8::ObjectTemplate> > ObjectTemplateMap;
  typedef std::map<
      WrapperInfo*, v8::Eternal<v8::FunctionTemplate> > FunctionTemplateMap;
  typedef std::map<WrappableBase*, IndexedPropertyInterceptor*>
      IndexedPropertyInterceptorMap;
  typedef std::map<WrappableBase*, NamedPropertyInterceptor*>
      NamedPropertyInterceptorMap;

  
  
  v8::Isolate* isolate_;
  v8::ArrayBuffer::Allocator* allocator_;
  ObjectTemplateMap object_templates_;
  FunctionTemplateMap function_templates_;
  IndexedPropertyInterceptorMap indexed_interceptors_;
  NamedPropertyInterceptorMap named_interceptors_;
  scoped_refptr<base::MessageLoopProxy> message_loop_proxy_;

  DISALLOW_COPY_AND_ASSIGN(PerIsolateData);
};

}  

#endif  
