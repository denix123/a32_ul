// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_RENDERER_EVENT_BINDINGS_H_
#define EXTENSIONS_RENDERER_EVENT_BINDINGS_H_

#include "extensions/renderer/object_backed_native_handler.h"
#include "v8/include/v8.h"

namespace base {
class DictionaryValue;
}

namespace extensions {
class Dispatcher;
class EventFilter;
class EventFilteringInfo;
class EventMatcher;

class EventBindings : public ObjectBackedNativeHandler {
 public:
  EventBindings(Dispatcher* dispatcher, ScriptContext* context);
  virtual ~EventBindings();

 private:
  
  
  void AttachEvent(const v8::FunctionCallbackInfo<v8::Value>& args);

  
  
  
  
  
  void DetachEvent(const v8::FunctionCallbackInfo<v8::Value>& args);

  
  
  
  
  
  void AttachFilteredEvent(const v8::FunctionCallbackInfo<v8::Value>& args);

  
  
  
  
  void DetachFilteredEvent(const v8::FunctionCallbackInfo<v8::Value>& args);

  void MatchAgainstEventFilter(const v8::FunctionCallbackInfo<v8::Value>& args);

  Dispatcher* dispatcher_;
  scoped_ptr<EventMatcher> ParseEventMatcher(
      base::DictionaryValue* filter_dict);
};

}  

#endif  
