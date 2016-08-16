// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_OPTIONS_CHROMEOS_DATE_TIME_OPTIONS_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_OPTIONS_CHROMEOS_DATE_TIME_OPTIONS_HANDLER_H_

#include "base/compiler_specific.h"
#include "chrome/browser/ui/webui/options/options_ui.h"
#include "chromeos/dbus/system_clock_client.h"

namespace chromeos {
namespace options {

class DateTimeOptionsHandler : public ::options::OptionsPageUIHandler,
                               public SystemClockClient::Observer {
 public:
  DateTimeOptionsHandler();
  virtual ~DateTimeOptionsHandler();

  
  virtual void GetLocalizedValues(
      base::DictionaryValue* localized_strings) OVERRIDE;
  virtual void InitializeHandler() OVERRIDE;
  virtual void InitializePage() OVERRIDE;
  virtual void RegisterMessages() OVERRIDE;

 private:
  
  virtual void SystemClockCanSetTimeChanged(bool can_set_time) OVERRIDE;

  
  
  void HandleShowSetTime(const base::ListValue* args);

  
  bool can_set_time_;
  bool page_initialized_;

  DISALLOW_COPY_AND_ASSIGN(DateTimeOptionsHandler);
};

}  
}  

#endif  
