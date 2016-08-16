// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_HOME_PUBLIC_APP_MODEL_BUILDER_H_
#define ATHENA_HOME_PUBLIC_APP_MODEL_BUILDER_H_

#include "athena/athena_export.h"

namespace app_list {
class AppListModel;
}  

namespace athena {

class ATHENA_EXPORT AppModelBuilder {
 public:
  virtual ~AppModelBuilder() {}

  
  virtual void PopulateApps(app_list::AppListModel* model) = 0;
};

}  

#endif  
