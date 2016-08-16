// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_PEPPER_MESSAGE_CHANNEL_H_
#define CONTENT_RENDERER_PEPPER_MESSAGE_CHANNEL_H_

#include <deque>
#include <list>
#include <map>

#include "base/basictypes.h"
#include "base/memory/weak_ptr.h"
#include "gin/handle.h"
#include "gin/interceptor.h"
#include "gin/wrappable.h"
#include "ppapi/proxy/host_dispatcher.h"
#include "ppapi/shared_impl/resource.h"
#include "third_party/WebKit/public/web/WebSerializedScriptValue.h"
#include "v8/include/v8.h"

struct PP_Var;

namespace gin {
class Arguments;
}  

namespace ppapi {
class ScopedPPVar;
}  

namespace content {

class PepperPluginInstanceImpl;
class PluginObject;

class MessageChannel :
    public gin::Wrappable<MessageChannel>,
    public gin::NamedPropertyInterceptor,
    public ppapi::proxy::HostDispatcher::SyncMessageStatusObserver {
 public:
  static gin::WrapperInfo kWrapperInfo;

  
  
  
  static MessageChannel* Create(PepperPluginInstanceImpl* instance,
                                v8::Persistent<v8::Object>* result);

  virtual ~MessageChannel();

  
  
  void InstanceDeleted();

  
  
  void PostMessageToJavaScript(PP_Var message_data);

  
  
  
  void Start();

  
  
  
  
  void SetPassthroughObject(v8::Handle<v8::Object> passthrough);

  PepperPluginInstanceImpl* instance() { return instance_; }

  void SetReadOnlyProperty(PP_Var key, PP_Var value);

 private:
  
  struct VarConversionResult;

  explicit MessageChannel(PepperPluginInstanceImpl* instance);

  
  virtual v8::Local<v8::Value> GetNamedProperty(
      v8::Isolate* isolate,
      const std::string& property) OVERRIDE;
  virtual bool SetNamedProperty(v8::Isolate* isolate,
                                const std::string& property,
                                v8::Local<v8::Value> value) OVERRIDE;
  virtual std::vector<std::string> EnumerateNamedProperties(
      v8::Isolate* isolate) OVERRIDE;

  
  virtual gin::ObjectTemplateBuilder GetObjectTemplateBuilder(
      v8::Isolate* isolate) OVERRIDE;

  
  virtual void BeginBlockOnSyncMessage() OVERRIDE;
  virtual void EndBlockOnSyncMessage() OVERRIDE;

  
  
  void PostMessageToNative(gin::Arguments* args);
  
  
  void PostBlockingMessageToNative(gin::Arguments* args);

  
  
  void PostMessageToJavaScriptImpl(
      const blink::WebSerializedScriptValue& message_data);

  PluginObject* GetPluginObject(v8::Isolate* isolate);

  void EnqueuePluginMessage(v8::Handle<v8::Value> v8_value);

  void FromV8ValueComplete(VarConversionResult* result_holder,
                           const ppapi::ScopedPPVar& result_var,
                           bool success);

  
  
  
  void DrainCompletedPluginMessages();
  
  void DrainJSMessageQueue();
  
  
  
  void DrainJSMessageQueueSoon();

  void UnregisterSyncMessageStatusObserver();

  PepperPluginInstanceImpl* instance_;

  
  
  
  
  
  v8::Persistent<v8::Object> passthrough_object_;

  enum MessageQueueState {
    WAITING_TO_START,  
    QUEUE_MESSAGES,  
    SEND_DIRECTLY,   
  };

  
  std::deque<blink::WebSerializedScriptValue> js_message_queue_;
  MessageQueueState js_message_queue_state_;
  
  
  
  
  
  int blocking_message_depth_;

  
  
  
  
  
  
  
  
  std::list<VarConversionResult> plugin_message_queue_;
  MessageQueueState plugin_message_queue_state_;

  std::map<std::string, ppapi::ScopedPPVar> internal_named_properties_;

  
  
  base::Closure unregister_observer_callback_;

  
  
  base::WeakPtrFactory<MessageChannel> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(MessageChannel);
};

}  

#endif  
