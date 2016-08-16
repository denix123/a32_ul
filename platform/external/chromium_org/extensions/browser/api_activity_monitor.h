// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_ACTIVITY_MONITOR_H_
#define EXTENSIONS_BROWSER_API_ACTIVITY_MONITOR_H_

#include <string>

#include "base/memory/scoped_ptr.h"

namespace base {
class ListValue;
}

namespace extensions {

class ApiActivityMonitor {
 public:
  
  virtual void OnApiEventDispatched(const std::string& extension_id,
                                    const std::string& event_name,
                                    scoped_ptr<base::ListValue> event_args) = 0;

  
  virtual void OnApiFunctionCalled(const std::string& extension_id,
                                   const std::string& api_name,
                                   scoped_ptr<base::ListValue> args) = 0;

 protected:
  virtual ~ApiActivityMonitor() {}
};

}  

#endif  
