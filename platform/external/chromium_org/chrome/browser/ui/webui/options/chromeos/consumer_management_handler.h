// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_OPTIONS_CHROMEOS_CONSUMER_MANAGEMENT_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_OPTIONS_CHROMEOS_CONSUMER_MANAGEMENT_HANDLER_H_

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/values.h"
#include "chrome/browser/ui/webui/options/options_ui.h"

namespace policy {
class ConsumerManagementService;
}

namespace chromeos {
namespace options {

class ConsumerManagementHandler : public ::options::OptionsPageUIHandler {
 public:
  explicit ConsumerManagementHandler(
      policy::ConsumerManagementService* management_service);
  virtual ~ConsumerManagementHandler();

  
  virtual void GetLocalizedValues(
      base::DictionaryValue* localized_strings) OVERRIDE;
  virtual void RegisterMessages() OVERRIDE;

 private:
  
  void HandleEnrollConsumerManagement(const base::ListValue* args);
  void HandleUnenrollConsumerManagement(const base::ListValue* args);

  policy::ConsumerManagementService* management_service_;

  DISALLOW_COPY_AND_ASSIGN(ConsumerManagementHandler);
};

}  
}  

#endif  
