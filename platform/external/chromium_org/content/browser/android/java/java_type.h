// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_ANDROID_JAVA_JAVA_TYPE_H_
#define CONTENT_BROWSER_ANDROID_JAVA_JAVA_TYPE_H_

#include <string>

#include "base/memory/scoped_ptr.h"
#include "content/common/content_export.h"

namespace content {

struct CONTENT_EXPORT JavaType {
  JavaType();
  JavaType(const JavaType& other);
  ~JavaType();
  JavaType& operator=(const JavaType& other);

  
  
  static JavaType CreateFromBinaryName(const std::string& binary_name);

  
  std::string JNIName() const;
  
  std::string JNISignature() const;

  enum Type {
    TypeBoolean,
    TypeByte,
    TypeChar,
    TypeShort,
    TypeInt,
    TypeLong,
    TypeFloat,
    TypeDouble,
    
    
    TypeVoid,
    TypeArray,
    
    TypeString,
    TypeObject,
  };

  Type type;
  scoped_ptr<JavaType> inner_type;  
  std::string class_jni_name;  
};

}  

#endif  
