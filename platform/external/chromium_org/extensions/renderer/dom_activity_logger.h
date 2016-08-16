// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_RENDERER_DOM_ACTIVITY_LOGGER_H_
#define EXTENSIONS_RENDERER_DOM_ACTIVITY_LOGGER_H_

#include <string>

#include "base/macros.h"
#include "extensions/common/dom_action_types.h"
#include "third_party/WebKit/public/web/WebDOMActivityLogger.h"
#include "v8/include/v8.h"

namespace base {
class ListValue;
}

namespace blink {
class WebString;
class WebURL;
}

namespace content {
class V8ValueConverter;
}

namespace extensions {

class DOMActivityLogger: public blink::WebDOMActivityLogger {
 public:
  static const int kMainWorldId = 0;
  explicit DOMActivityLogger(const std::string& extension_id);
  virtual ~DOMActivityLogger();

  
  
  
  static void AttachToWorld(int world_id,
                            const std::string& extension_id);

 private:
  
  
  
  
  
  
  virtual void logGetter(const blink::WebString& api_name,
                         const blink::WebURL& url,
                         const blink::WebString& title);
  virtual void logSetter(const blink::WebString& api_name,
                         const v8::Handle<v8::Value>& new_value,
                         const blink::WebURL& url,
                         const blink::WebString& title);
  virtual void logSetter(const blink::WebString& api_name,
                         const v8::Handle<v8::Value>& new_value,
                         const v8::Handle<v8::Value>& old_value,
                         const blink::WebURL& url,
                         const blink::WebString& title);
  virtual void logMethod(const blink::WebString& api_name,
                         int argc,
                         const v8::Handle<v8::Value>* argv,
                         const blink::WebURL& url,
                         const blink::WebString& title);
  virtual void logEvent(const blink::WebString& event_name,
                        int argc,
                        const blink::WebString* argv,
                        const blink::WebURL& url,
                        const blink::WebString& title);

  
  void SendDomActionMessage(const std::string& api_call,
                            const GURL& url,
                            const base::string16& url_title,
                            DomActionType::Type call_type,
                            scoped_ptr<base::ListValue> args);

  
  std::string extension_id_;

  DISALLOW_COPY_AND_ASSIGN(DOMActivityLogger);
};

}  

#endif  

