// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_RENDERER_MODULE_SYSTEM_TEST_H_
#define EXTENSIONS_RENDERER_MODULE_SYSTEM_TEST_H_

#include "extensions/renderer/module_system.h"
#include "extensions/renderer/scoped_persistent.h"
#include "extensions/renderer/script_context.h"
#include "gin/public/context_holder.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "v8/include/v8.h"

namespace extensions {

class ModuleSystemTestEnvironment {
 public:
  class AssertNatives;
  class StringSourceMap;

  explicit ModuleSystemTestEnvironment(v8::Isolate* isolate);
  ~ModuleSystemTestEnvironment();

  
  void RegisterModule(const std::string& name, const std::string& code);

  
  void RegisterModule(const std::string& name, int resource_id);

  
  
  
  void OverrideNativeHandler(const std::string& name, const std::string& code);

  
  
  void RegisterTestFile(const std::string& module_name,
                        const std::string& file_name);

  
  v8::Handle<v8::Object> CreateGlobal(const std::string& name);

  void ShutdownGin();

  void ShutdownModuleSystem();

  ModuleSystem* module_system() { return context_->module_system(); }

  ScriptContext* context() { return context_.get(); }

  v8::Isolate* isolate() { return isolate_; }

  AssertNatives* assert_natives() { return assert_natives_; }

 private:
  v8::Isolate* isolate_;
  scoped_ptr<gin::ContextHolder> context_holder_;
  v8::HandleScope handle_scope_;
  scoped_ptr<ScriptContext> context_;
  AssertNatives* assert_natives_;
  scoped_ptr<StringSourceMap> source_map_;

  DISALLOW_COPY_AND_ASSIGN(ModuleSystemTestEnvironment);
};

class ModuleSystemTest : public testing::Test {
 public:
  ModuleSystemTest();
  virtual ~ModuleSystemTest();

  virtual void SetUp() OVERRIDE;
  virtual void TearDown() OVERRIDE;

 protected:
  ModuleSystemTestEnvironment* env() { return env_.get(); }

  scoped_ptr<ModuleSystemTestEnvironment> CreateEnvironment();

  
  
  void ExpectNoAssertionsMade();

  
  
  void RunResolvedPromises();

 private:
  v8::Isolate* isolate_;
  scoped_ptr<ModuleSystemTestEnvironment> env_;
  bool should_assertions_be_made_;

 private:
  DISALLOW_COPY_AND_ASSIGN(ModuleSystemTest);
};

}  

#endif  
