// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_PEPPER_PEPPER_TRY_CATCH_H_
#define CONTENT_RENDERER_PEPPER_PEPPER_TRY_CATCH_H_

#include "base/basictypes.h"
#include "content/common/content_export.h"
#include "content/renderer/pepper/v8_var_converter.h"
#include "ppapi/c/pp_var.h"
#include "ppapi/shared_impl/scoped_pp_var.h"
#include "v8/include/v8.h"

namespace content {

class PepperPluginInstanceImpl;

class CONTENT_EXPORT PepperTryCatch {
 public:
  
  
  PepperTryCatch(PepperPluginInstanceImpl* instance,
                 V8VarConverter::AllowObjectVars convert_objects);
  virtual ~PepperTryCatch();

  virtual void SetException(const char* message) = 0;
  virtual bool HasException() = 0;
  
  virtual v8::Handle<v8::Context> GetContext() = 0;

  
  
  v8::Handle<v8::Value> ToV8(PP_Var var);
  ppapi::ScopedPPVar FromV8(v8::Handle<v8::Value> v8_value);

 protected:
  
  
  
  
  
  
  
  scoped_refptr<PepperPluginInstanceImpl> instance_;

  
  
  
  V8VarConverter::AllowObjectVars convert_objects_;
};

class PepperTryCatchV8 : public PepperTryCatch {
 public:
  PepperTryCatchV8(PepperPluginInstanceImpl* instance,
                   V8VarConverter::AllowObjectVars convert_objects,
                   v8::Isolate* isolate);
  virtual ~PepperTryCatchV8();

  bool ThrowException();
  void ThrowException(const char* message);
  PP_Var* exception() { return &exception_; }

  
  virtual void SetException(const char* message) OVERRIDE;
  virtual bool HasException() OVERRIDE;
  virtual v8::Handle<v8::Context> GetContext() OVERRIDE;

 private:
  PP_Var exception_;

  DISALLOW_COPY_AND_ASSIGN(PepperTryCatchV8);
};

class PepperTryCatchVar : public PepperTryCatch {
 public:
  
  
  
  PepperTryCatchVar(PepperPluginInstanceImpl* instance,
                    PP_Var* exception);
  virtual ~PepperTryCatchVar();

  
  virtual void SetException(const char* message) OVERRIDE;
  virtual bool HasException() OVERRIDE;
  virtual v8::Handle<v8::Context> GetContext() OVERRIDE;

 private:
  
  
  v8::HandleScope handle_scope_;

  v8::Handle<v8::Context> context_;

  v8::TryCatch try_catch_;

  PP_Var* exception_;
  bool exception_is_set_;

  DISALLOW_COPY_AND_ASSIGN(PepperTryCatchVar);
};

}  

#endif  
