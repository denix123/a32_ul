// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_PEPPER_V8OBJECT_VAR_H_
#define CONTENT_RENDERER_PEPPER_V8OBJECT_VAR_H_

#include <string>

#include "base/compiler_specific.h"
#include "content/common/content_export.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/shared_impl/var.h"
#include "v8/include/v8.h"

namespace content {
class PepperPluginInstanceImpl;
}  

namespace ppapi {


class CONTENT_EXPORT V8ObjectVar : public Var {
 public:
  V8ObjectVar(PP_Instance instance, v8::Handle<v8::Object> v8_object);

  
  virtual V8ObjectVar* AsV8ObjectVar() OVERRIDE;
  virtual PP_VarType GetType() const OVERRIDE;

  
  
  v8::Local<v8::Object> GetHandle() const;

  
  
  void InstanceDeleted();

  
  content::PepperPluginInstanceImpl* instance() const { return instance_; }

  
  
  static scoped_refptr<V8ObjectVar> FromPPVar(PP_Var var);

 private:
  virtual ~V8ObjectVar();

  content::PepperPluginInstanceImpl* instance_;

  v8::Persistent<v8::Object> v8_object_;

  DISALLOW_COPY_AND_ASSIGN(V8ObjectVar);
};

}  

#endif  
