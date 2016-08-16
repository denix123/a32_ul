// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GPU_COMMAND_BUFFER_SERVICE_SHADER_TRANSLATOR_H_
#define GPU_COMMAND_BUFFER_SERVICE_SHADER_TRANSLATOR_H_

#include <string>

#include "base/basictypes.h"
#include "base/containers/hash_tables.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "gpu/gpu_export.h"
#include "third_party/angle/include/GLSLANG/ShaderLang.h"

namespace gpu {
namespace gles2 {

class ShaderTranslatorInterface {
 public:
  enum GlslImplementationType {
    kGlsl,
    kGlslES
  };

  struct VariableInfo {
    VariableInfo()
        : type(0),
          size(0),
          precision(SH_PRECISION_UNDEFINED),
          static_use(0) {
    }

    VariableInfo(int _type, int _size, int _precision,
                 int _static_use, std::string _name)
        : type(_type),
          size(_size),
          precision(_precision),
          static_use(_static_use),
          name(_name) {
    }
    bool operator==(
        const ShaderTranslatorInterface::VariableInfo& other) const {
      return type == other.type &&
          size == other.size &&
          precision == other.precision &&
          strcmp(name.c_str(), other.name.c_str()) == 0;
    }

    int type;
    int size;
    int precision;
    int static_use;
    std::string name;  
  };

  
  typedef base::hash_map<std::string, VariableInfo> VariableMap;
  
  typedef base::hash_map<std::string, std::string> NameMap;

  
  
  virtual bool Init(
      sh::GLenum shader_type,
      ShShaderSpec shader_spec,
      const ShBuiltInResources* resources,
      GlslImplementationType glsl_implementation_type,
      ShCompileOptions driver_bug_workarounds) = 0;

  
  
  
  
  
  virtual bool Translate(const std::string& shader_source,
                         std::string* info_log,
                         std::string* translated_shader,
                         VariableMap* attrib_map,
                         VariableMap* uniform_map,
                         VariableMap* varying_map,
                         NameMap* name_map) const = 0;

  
  
  virtual std::string GetStringForOptionsThatWouldAffectCompilation() const = 0;

 protected:
  virtual ~ShaderTranslatorInterface() {}
};

class GPU_EXPORT ShaderTranslator
    : public base::RefCounted<ShaderTranslator>,
      NON_EXPORTED_BASE(public ShaderTranslatorInterface) {
 public:
  class DestructionObserver {
   public:
    DestructionObserver();
    virtual ~DestructionObserver();

    virtual void OnDestruct(ShaderTranslator* translator) = 0;

   private:
    DISALLOW_COPY_AND_ASSIGN(DestructionObserver);
  };

  ShaderTranslator();

  
  virtual bool Init(
      sh::GLenum shader_type,
      ShShaderSpec shader_spec,
      const ShBuiltInResources* resources,
      GlslImplementationType glsl_implementation_type,
      ShCompileOptions driver_bug_workarounds) OVERRIDE;

  
  virtual bool Translate(const std::string& shader_source,
                         std::string* info_log,
                         std::string* translated_source,
                         VariableMap* attrib_map,
                         VariableMap* uniform_map,
                         VariableMap* varying_map,
                         NameMap* name_map) const OVERRIDE;

  virtual std::string GetStringForOptionsThatWouldAffectCompilation() const
      OVERRIDE;

  void AddDestructionObserver(DestructionObserver* observer);
  void RemoveDestructionObserver(DestructionObserver* observer);

 private:
  friend class base::RefCounted<ShaderTranslator>;

  virtual ~ShaderTranslator();
  int GetCompileOptions() const;

  ShHandle compiler_;
  ShBuiltInResources compiler_options_;
  bool implementation_is_glsl_es_;
  ShCompileOptions driver_bug_workarounds_;
  ObserverList<DestructionObserver> destruction_observers_;

  DISALLOW_COPY_AND_ASSIGN(ShaderTranslator);
};

}  
}  

#endif  
