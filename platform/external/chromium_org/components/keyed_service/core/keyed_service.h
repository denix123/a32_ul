// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_KEYED_SERVICE_CORE_KEYED_SERVICE_H_
#define COMPONENTS_KEYED_SERVICE_CORE_KEYED_SERVICE_H_

#include "components/keyed_service/core/keyed_service_export.h"

class KEYED_SERVICE_EXPORT KeyedService {
 public:
  KeyedService();

  
  virtual void Shutdown();

  
  virtual ~KeyedService();
};

#endif  
