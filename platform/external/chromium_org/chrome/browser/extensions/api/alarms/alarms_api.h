// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_ALARMS_ALARMS_API_H__
#define CHROME_BROWSER_EXTENSIONS_API_ALARMS_ALARMS_API_H__

#include <vector>

#include "chrome/browser/extensions/chrome_extension_function.h"

namespace base {
class Clock;
}  

namespace extensions {
struct Alarm;
typedef std::vector<Alarm> AlarmList;

class AlarmsCreateFunction : public ChromeAsyncExtensionFunction {
 public:
  AlarmsCreateFunction();
  
  
  explicit AlarmsCreateFunction(base::Clock* clock);
 protected:
  virtual ~AlarmsCreateFunction();

  
  virtual bool RunAsync() OVERRIDE;
  DECLARE_EXTENSION_FUNCTION("alarms.create", ALARMS_CREATE)
 private:
  void Callback();

  base::Clock* const clock_;
  
  
  
  bool owns_clock_;
};

class AlarmsGetFunction : public ChromeAsyncExtensionFunction {
 protected:
  virtual ~AlarmsGetFunction() {}

  
  virtual bool RunAsync() OVERRIDE;

 private:
  void Callback(const std::string& name, Alarm* alarm);
  DECLARE_EXTENSION_FUNCTION("alarms.get", ALARMS_GET)
};

class AlarmsGetAllFunction : public ChromeAsyncExtensionFunction {
 protected:
  virtual ~AlarmsGetAllFunction() {}

  
  virtual bool RunAsync() OVERRIDE;

 private:
  void Callback(const AlarmList* alarms);
  DECLARE_EXTENSION_FUNCTION("alarms.getAll", ALARMS_GETALL)
};

class AlarmsClearFunction : public ChromeAsyncExtensionFunction {
 protected:
  virtual ~AlarmsClearFunction() {}

  
  virtual bool RunAsync() OVERRIDE;

 private:
  void Callback(const std::string& name, bool success);
  DECLARE_EXTENSION_FUNCTION("alarms.clear", ALARMS_CLEAR)
};

class AlarmsClearAllFunction : public ChromeAsyncExtensionFunction {
 protected:
  virtual ~AlarmsClearAllFunction() {}

  
  virtual bool RunAsync() OVERRIDE;

 private:
  void Callback();
  DECLARE_EXTENSION_FUNCTION("alarms.clearAll", ALARMS_CLEARALL)
};

} 

#endif  