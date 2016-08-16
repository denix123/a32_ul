// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_BINDINGS_JS_HANDLE_H_
#define MOJO_BINDINGS_JS_HANDLE_H_

#include "base/observer_list.h"
#include "gin/converter.h"
#include "gin/handle.h"
#include "gin/wrappable.h"
#include "mojo/public/cpp/system/core.h"

namespace gin {
class HandleCloseObserver;

class HandleWrapper : public gin::Wrappable<HandleWrapper> {
 public:
  static gin::WrapperInfo kWrapperInfo;

  static gin::Handle<HandleWrapper> Create(v8::Isolate* isolate,
                                           MojoHandle handle) {
    return gin::CreateHandle(isolate, new HandleWrapper(handle));
  }

  mojo::Handle get() const { return handle_.get(); }
  mojo::Handle release() { return handle_.release(); }
  void Close();

  void AddCloseObserver(HandleCloseObserver* observer);
  void RemoveCloseObserver(HandleCloseObserver* observer);

 protected:
  HandleWrapper(MojoHandle handle);
  virtual ~HandleWrapper();
  void NotifyCloseObservers();

  mojo::ScopedHandle handle_;
  ObserverList<HandleCloseObserver> close_observers_;
};

template<>
struct Converter<mojo::Handle> {
  static v8::Handle<v8::Value> ToV8(v8::Isolate* isolate,
                                    const mojo::Handle& val);
  static bool FromV8(v8::Isolate* isolate, v8::Handle<v8::Value> val,
                     mojo::Handle* out);
};

template<>
struct Converter<gin::Handle<gin::HandleWrapper> > {
  static v8::Handle<v8::Value> ToV8(
        v8::Isolate* isolate, const gin::Handle<gin::HandleWrapper>& val) {
    return val.ToV8();
  }

  static bool FromV8(v8::Isolate* isolate, v8::Handle<v8::Value> val,
                     gin::Handle<gin::HandleWrapper>* out) {
    if (val->IsNull()) {
      *out = HandleWrapper::Create(isolate, MOJO_HANDLE_INVALID);
      return true;
    }

    gin::HandleWrapper* object = NULL;
    if (!Converter<gin::HandleWrapper*>::FromV8(isolate, val, &object)) {
      return false;
    }
    *out = gin::Handle<gin::HandleWrapper>(val, object);
    return true;
  }
};

}  

#endif  
