// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_COMMON_MANIFEST_TEST_H_
#define EXTENSIONS_COMMON_MANIFEST_TEST_H_

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/values.h"
#include "extensions/common/extension.h"
#include "extensions/common/manifest.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace base {
class FilePath;
}

namespace extensions {

class ManifestTest : public testing::Test {
 public:
  ManifestTest();
  virtual ~ManifestTest();

 protected:
  
  
  class ManifestData {
   public:
    explicit ManifestData(const char* name);
    ManifestData(base::DictionaryValue* manifest, const char* name);
    explicit ManifestData(scoped_ptr<base::DictionaryValue> manifest);
    
    
    
    
    
    
    
    
    
    ManifestData(const ManifestData& m);

    ~ManifestData();

    const std::string& name() const { return name_; };

    base::DictionaryValue* GetManifest(base::FilePath manifest_path,
                                       std::string* error) const;

   private:
    const std::string name_;
    mutable base::DictionaryValue* manifest_;
    mutable scoped_ptr<base::DictionaryValue> manifest_holder_;
  };

  
  
  virtual base::FilePath GetTestDataDir();

  scoped_ptr<base::DictionaryValue> LoadManifest(
      char const* manifest_name,
      std::string* error);

  scoped_refptr<extensions::Extension> LoadExtension(
      const ManifestData& manifest,
      std::string* error,
      extensions::Manifest::Location location =
          extensions::Manifest::INTERNAL,
      int flags = extensions::Extension::NO_FLAGS);

  scoped_refptr<extensions::Extension> LoadAndExpectSuccess(
      const ManifestData& manifest,
      extensions::Manifest::Location location =
          extensions::Manifest::INTERNAL,
      int flags = extensions::Extension::NO_FLAGS);

  scoped_refptr<extensions::Extension> LoadAndExpectSuccess(
      char const* manifest_name,
      extensions::Manifest::Location location =
          extensions::Manifest::INTERNAL,
      int flags = extensions::Extension::NO_FLAGS);

  scoped_refptr<extensions::Extension> LoadAndExpectWarning(
      const ManifestData& manifest,
      const std::string& expected_error,
      extensions::Manifest::Location location =
          extensions::Manifest::INTERNAL,
      int flags = extensions::Extension::NO_FLAGS);

  scoped_refptr<extensions::Extension> LoadAndExpectWarning(
      char const* manifest_name,
      const std::string& expected_error,
      extensions::Manifest::Location location =
          extensions::Manifest::INTERNAL,
      int flags = extensions::Extension::NO_FLAGS);

  void VerifyExpectedError(extensions::Extension* extension,
                           const std::string& name,
                           const std::string& error,
                           const std::string& expected_error);

  void LoadAndExpectError(char const* manifest_name,
                          const std::string& expected_error,
                          extensions::Manifest::Location location =
                              extensions::Manifest::INTERNAL,
                          int flags = extensions::Extension::NO_FLAGS);

  void LoadAndExpectError(const ManifestData& manifest,
                          const std::string& expected_error,
                          extensions::Manifest::Location location =
                              extensions::Manifest::INTERNAL,
                          int flags = extensions::Extension::NO_FLAGS);

  void AddPattern(extensions::URLPatternSet* extent,
                  const std::string& pattern);

  
  
  enum ExpectType {
    EXPECT_TYPE_ERROR,
    EXPECT_TYPE_WARNING,
    EXPECT_TYPE_SUCCESS
  };

  struct Testcase {
    std::string manifest_filename_;
    std::string expected_error_; 
    extensions::Manifest::Location location_;
    int flags_;

    Testcase(std::string manifest_filename, std::string expected_error,
        extensions::Manifest::Location location, int flags);

    Testcase(std::string manifest_filename, std::string expected_error);

    explicit Testcase(std::string manifest_filename);

    Testcase(std::string manifest_filename,
             extensions::Manifest::Location location,
             int flags);
  };

  void RunTestcases(const Testcase* testcases,
                    size_t num_testcases,
                    ExpectType type);

  void RunTestcase(const Testcase& testcase, ExpectType type);

  bool enable_apps_;

 private:
  DISALLOW_COPY_AND_ASSIGN(ManifestTest);
};

}  

#endif  