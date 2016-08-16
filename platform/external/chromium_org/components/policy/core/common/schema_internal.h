// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_POLICY_CORE_COMMON_SCHEMA_INTERNAL_H_
#define COMPONENTS_POLICY_CORE_COMMON_SCHEMA_INTERNAL_H_

#include "base/values.h"
#include "components/policy/policy_export.h"

namespace policy {
namespace internal {


struct POLICY_EXPORT SchemaNode {
  
  base::Value::Type type;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  int extra;
};

struct POLICY_EXPORT PropertyNode {
  
  const char* key;

  
  
  int schema;
};

struct POLICY_EXPORT PropertiesNode {
  
  
  int begin;

  
  
  
  
  
  
  
  
  int end;

  
  
  
  
  
  int pattern_end;

  
  
  
  
  
  int additional;
};

union POLICY_EXPORT RestrictionNode {
  
  
  
  
  struct EnumerationRestriction {
    int offset_begin;
    int offset_end;
  } enumeration_restriction;

  
  
  
  
  
  struct RangedRestriction {
    int max_value;
    int min_value;
  } ranged_restriction;

  
  
  
  struct StringPatternRestriction {
    int pattern_index;
    int pattern_index_backup;
  } string_pattern_restriction;
};


struct POLICY_EXPORT SchemaData {
  const SchemaNode* schema_nodes;
  const PropertyNode* property_nodes;
  const PropertiesNode* properties_nodes;
  const RestrictionNode* restriction_nodes;

  const int* int_enums;
  const char** string_enums;
};

}  
}  

#endif  
