// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_MANAGER_INTERNALS_SERVICE_H_
#define COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_MANAGER_INTERNALS_SERVICE_H_

#include <string>

#include "components/keyed_service/core/keyed_service.h"
#include "components/password_manager/core/browser/log_router.h"

namespace content {
class BrowserContext;
}

namespace password_manager {

class PasswordManagerInternalsService : public KeyedService,
                                        public LogRouter {
 public:
  
  
  
  
  
  PasswordManagerInternalsService();
  virtual ~PasswordManagerInternalsService();

 private:
  DISALLOW_COPY_AND_ASSIGN(PasswordManagerInternalsService);
};

}  

#endif  
