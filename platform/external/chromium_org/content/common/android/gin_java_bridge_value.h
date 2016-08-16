// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_ANDROID_GIN_JAVA_BRIDGE_VALUE_H_
#define CONTENT_COMMON_ANDROID_GIN_JAVA_BRIDGE_VALUE_H_

#include "base/memory/scoped_ptr.h"
#include "base/pickle.h"
#include "base/values.h"
#include "content/common/content_export.h"


namespace content {

class GinJavaBridgeValue {
 public:
  enum Type {
    TYPE_FIRST_VALUE = 0,
    
    TYPE_UNDEFINED = 0,
    
    TYPE_NONFINITE,
    
    TYPE_OBJECT_ID,
    TYPE_LAST_VALUE
  };

  
  CONTENT_EXPORT static scoped_ptr<base::BinaryValue> CreateUndefinedValue();
  CONTENT_EXPORT static scoped_ptr<base::BinaryValue> CreateNonFiniteValue(
      float in_value);
  CONTENT_EXPORT static scoped_ptr<base::BinaryValue> CreateNonFiniteValue(
      double in_value);
  CONTENT_EXPORT static scoped_ptr<base::BinaryValue> CreateObjectIDValue(
      int32 in_value);

  
  CONTENT_EXPORT static bool ContainsGinJavaBridgeValue(
      const base::Value* value);
  CONTENT_EXPORT static scoped_ptr<const GinJavaBridgeValue> FromValue(
      const base::Value* value);

  CONTENT_EXPORT Type GetType() const;
  CONTENT_EXPORT bool IsType(Type type) const;

  CONTENT_EXPORT bool GetAsNonFinite(float* out_value) const;
  CONTENT_EXPORT bool GetAsObjectID(int32* out_object_id) const;

 private:
  explicit GinJavaBridgeValue(Type type);
  explicit GinJavaBridgeValue(const base::BinaryValue* value);
  base::BinaryValue* SerializeToBinaryValue();

  Pickle pickle_;

  DISALLOW_COPY_AND_ASSIGN(GinJavaBridgeValue);
};

}  

#endif  
