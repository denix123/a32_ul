// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_TEST_NACL_NACL_BROWSERTEST_UTIL_H_
#define CHROME_TEST_NACL_NACL_BROWSERTEST_UTIL_H_

#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/test/base/in_process_browser_test.h"
#include "content/public/test/javascript_test_observer.h"

class StructuredMessageHandler : public content::TestMessageHandler {
 public:
  virtual MessageResponse HandleMessage(const std::string& json) OVERRIDE;

  
  
  
  
  
  
  virtual MessageResponse HandleStructuredMessage(
      const std::string& type,
      base::DictionaryValue* msg) = 0;

 protected:
  
  MessageResponse MissingField(
      const std::string& type,
      const std::string& field) WARN_UNUSED_RESULT;

  
  MessageResponse InternalError(const std::string& reason) WARN_UNUSED_RESULT;
};

class LoadTestMessageHandler : public StructuredMessageHandler {
 public:
  LoadTestMessageHandler();

  void Log(const std::string& type, const std::string& message);

  virtual MessageResponse HandleStructuredMessage(
      const std::string& type,
      base::DictionaryValue* msg) OVERRIDE;

  bool test_passed() const {
    return test_passed_;
  }

 private:
  bool test_passed_;

  DISALLOW_COPY_AND_ASSIGN(LoadTestMessageHandler);
};

class NaClBrowserTestBase : public InProcessBrowserTest {
 public:
  NaClBrowserTestBase();
  virtual ~NaClBrowserTestBase();

  virtual void SetUpCommandLine(base::CommandLine* command_line) OVERRIDE;

  virtual void SetUpOnMainThread() OVERRIDE;

  
  
  
  virtual base::FilePath::StringType Variant() = 0;

  
  virtual bool GetDocumentRoot(base::FilePath* document_root);

  virtual bool IsAPnaclTest();

  
  
  GURL TestURL(const base::FilePath::StringType& url_fragment);

  
  
  
  bool RunJavascriptTest(const GURL& url, content::TestMessageHandler* handler);

  
  
  void RunLoadTest(const base::FilePath::StringType& test_file);

  // Run a test that was originally written to use NaCl's integration testing
  
  
  
  
  
  
  
  
  void RunNaClIntegrationTest(const base::FilePath::StringType& url,
                              bool full_url = false);

 private:
  bool StartTestServer();

  scoped_ptr<net::SpawnedTestServer> test_server_;
};

class NaClBrowserTestNewlib : public NaClBrowserTestBase {
 public:
  virtual base::FilePath::StringType Variant() OVERRIDE;
};

class NaClBrowserTestGLibc : public NaClBrowserTestBase {
 public:
  virtual base::FilePath::StringType Variant() OVERRIDE;
};

class NaClBrowserTestPnacl : public NaClBrowserTestBase {
 public:
  virtual base::FilePath::StringType Variant() OVERRIDE;

  virtual bool IsAPnaclTest() OVERRIDE;
};

class NaClBrowserTestPnaclNonSfi : public NaClBrowserTestBase {
 public:
  virtual void SetUpCommandLine(base::CommandLine* command_line) OVERRIDE;
  virtual base::FilePath::StringType Variant() OVERRIDE;
};

class NaClBrowserTestNonSfiMode : public NaClBrowserTestBase {
 public:
  virtual void SetUpCommandLine(base::CommandLine* command_line) OVERRIDE;
  virtual base::FilePath::StringType Variant() OVERRIDE;
};

class NaClBrowserTestStatic : public NaClBrowserTestBase {
 public:
  virtual base::FilePath::StringType Variant() OVERRIDE;
  virtual bool GetDocumentRoot(base::FilePath* document_root) OVERRIDE;
};

class NaClBrowserTestNewlibExtension : public NaClBrowserTestNewlib {
 public:
  virtual void SetUpCommandLine(base::CommandLine* command_line) OVERRIDE;
};

class NaClBrowserTestGLibcExtension : public NaClBrowserTestGLibc {
 public:
  virtual void SetUpCommandLine(base::CommandLine* command_line) OVERRIDE;
};

#if (defined(OS_WIN) && !defined(NDEBUG))
#  define MAYBE_PNACL(test_name) DISABLED_##test_name
#else
#  define MAYBE_PNACL(test_name) test_name
#endif

#if defined(ARCH_CPU_X86_FAMILY)
#  define MAYBE_GLIBC(test_name) test_name
#else
#  define MAYBE_GLIBC(test_name) DISABLED_##test_name
#endif

#if defined(OS_LINUX) && !defined(ADDRESS_SANITIZER) && \
    !defined(THREAD_SANITIZER) && !defined(MEMORY_SANITIZER) && \
    !defined(LEAK_SANITIZER)
#  define MAYBE_NONSFI(test_case) test_case
#else
#  define MAYBE_NONSFI(test_case) DISABLED_##test_case
#endif

#if defined(OS_LINUX) && defined(ARCH_CPU_X86)
#  define MAYBE_PNACL_NONSFI(test_case) test_case
#else
#  define MAYBE_PNACL_NONSFI(test_case) DISABLED_##test_case
#endif

#define NACL_BROWSER_TEST_F(suite, name, body) \
IN_PROC_BROWSER_TEST_F(suite##Newlib, name) \
body \
IN_PROC_BROWSER_TEST_F(suite##GLibc, MAYBE_GLIBC(name)) \
body \
IN_PROC_BROWSER_TEST_F(suite##Pnacl, MAYBE_PNACL(name)) \
body

#endif  
