// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_OPERATIONS_TEST_UTIL_H_
#define CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_OPERATIONS_TEST_UTIL_H_

#include <vector>

#include "base/files/file.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"

namespace extensions {
struct Event;
}  

namespace chromeos {
namespace file_system_provider {
namespace operations {
namespace util {

class LoggingDispatchEventImpl {
 public:
  explicit LoggingDispatchEventImpl(bool dispatch_reply);
  virtual ~LoggingDispatchEventImpl();

  
  bool OnDispatchEventImpl(scoped_ptr<extensions::Event> event);

  
  ScopedVector<extensions::Event>& events() { return events_; }

 private:
  ScopedVector<extensions::Event> events_;
  bool dispatch_reply_;

  DISALLOW_COPY_AND_ASSIGN(LoggingDispatchEventImpl);
};

typedef std::vector<base::File::Error> StatusCallbackLog;

void LogStatusCallback(StatusCallbackLog* log, base::File::Error result);

}  
}  
}  
}  

#endif  
