// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_POLICY_SCHEMA_REGISTRY_SERVICE_H_
#define CHROME_BROWSER_POLICY_SCHEMA_REGISTRY_SERVICE_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "components/keyed_service/core/keyed_service.h"

namespace policy {

class CombinedSchemaRegistry;
class Schema;
class SchemaRegistry;

class SchemaRegistryService : public KeyedService {
 public:
  
  
  
  SchemaRegistryService(scoped_ptr<SchemaRegistry> registry,
                        const Schema& chrome_schema,
                        CombinedSchemaRegistry* global_registry);
  virtual ~SchemaRegistryService();

  SchemaRegistry* registry() const { return registry_.get(); }

 private:
  scoped_ptr<SchemaRegistry> registry_;

  DISALLOW_COPY_AND_ASSIGN(SchemaRegistryService);
};

}  

#endif  
