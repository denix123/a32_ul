// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_RENDERER_MESSAGING_BINDINGS_H_
#define EXTENSIONS_RENDERER_MESSAGING_BINDINGS_H_

#include <string>

#include "extensions/renderer/script_context_set.h"

struct ExtensionMsg_ExternalConnectionInfo;

namespace base {
class DictionaryValue;
}

namespace content {
class RenderView;
}

namespace v8 {
class Extension;
}

namespace extensions {
class Dispatcher;
struct Message;
class ObjectBackedNativeHandler;
class ScriptContextSet;

class MessagingBindings {
 public:
  
  static ObjectBackedNativeHandler* Get(Dispatcher* dispatcher,
                                        ScriptContext* context);

  
  
  
  static void DispatchOnConnect(const ScriptContextSet& context_set,
                                int target_port_id,
                                const std::string& channel_name,
                                const base::DictionaryValue& source_tab,
                                const ExtensionMsg_ExternalConnectionInfo& info,
                                const std::string& tls_channel_id,
                                content::RenderView* restrict_to_render_view);

  
  
  
  static void DeliverMessage(const ScriptContextSet& context_set,
                             int target_port_id,
                             const Message& message,
                             content::RenderView* restrict_to_render_view);

  
  static void DispatchOnDisconnect(
      const ScriptContextSet& context_set,
      int port_id,
      const std::string& error_message,
      content::RenderView* restrict_to_render_view);
};

}  

#endif  
