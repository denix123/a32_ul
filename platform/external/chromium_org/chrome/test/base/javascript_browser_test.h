// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_TEST_BASE_JAVASCRIPT_BROWSER_TEST_H_
#define CHROME_TEST_BASE_JAVASCRIPT_BROWSER_TEST_H_

#include "base/memory/scoped_vector.h"
#include "base/strings/string16.h"
#include "base/values.h"
#include "chrome/test/base/in_process_browser_test.h"

class JavaScriptBrowserTest : public InProcessBrowserTest {
 public:
  static const base::FilePath::CharType kA11yAuditLibraryJSPath[];
  static const base::FilePath::CharType kMockJSPath[];
  static const base::FilePath::CharType kWebUILibraryJS[];
  static const base::FilePath::CharType kWebUITestFolder[];

  typedef ScopedVector<const base::Value> ConstValueVector;

  
  
  
  void AddLibrary(const base::FilePath& library_path);

 protected:
  JavaScriptBrowserTest();

  virtual ~JavaScriptBrowserTest();

  
  virtual void SetUpOnMainThread() OVERRIDE;

  
  
  void BuildJavascriptLibraries(std::vector<base::string16>* libraries);

  
  
  
  
  base::string16 BuildRunTestJSCall(bool is_async,
                                    const std::string& test_name,
                                    const ConstValueVector& args);

 private:
  
  std::vector<base::FilePath> user_libraries_;

  
  std::vector<base::FilePath> library_search_paths_;

  DISALLOW_COPY_AND_ASSIGN(JavaScriptBrowserTest);
};

#endif  
