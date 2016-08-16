// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CDM_PPAPI_CDM_FILE_IO_TEST_H_
#define MEDIA_CDM_PPAPI_CDM_FILE_IO_TEST_H_

#include <list>
#include <stack>
#include <string>
#include <vector>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "media/cdm/ppapi/api/content_decryption_module.h"

namespace media {

typedef base::Callback<void(bool success)> CompletionCB;
typedef base::Callback<cdm::FileIO*(cdm::FileIOClient* client)> CreateFileIOCB;

class FileIOTest : public cdm::FileIOClient {
 public:
  
  
  
  enum StepType {
    ACTION_CREATE,
    ACTION_OPEN,  
    RESULT_OPEN,
    ACTION_READ,
    RESULT_READ,
    ACTION_WRITE,
    RESULT_WRITE,
    ACTION_CLOSE  
                  
  };

  FileIOTest(const CreateFileIOCB& create_file_io_cb,
             const std::string& test_name);
  ~FileIOTest();

  
  
  void AddTestStep(
      StepType type, Status status, const uint8* data, uint32 data_size);

  
  void Run(const CompletionCB& completion_cb);

 private:
  struct TestStep {
    
    
    TestStep(StepType type, Status status, const uint8* data, uint32 data_size)
        : type(type), status(status), data(data), data_size(data_size) {}

    StepType type;

    
    Status status;

    
    const uint8* data;
    uint32 data_size;
  };

  
  static bool IsResult(const TestStep& test_step);

  
  static bool MatchesResult(const TestStep& a, const TestStep& b);

  
  virtual void OnOpenComplete(Status status) OVERRIDE;
  virtual void OnReadComplete(Status status,
                              const uint8_t* data,
                              uint32_t data_size) OVERRIDE;
  virtual void OnWriteComplete(Status status) OVERRIDE;

  
  void RunNextStep();

  void OnResult(const TestStep& result);

  
  
  bool CheckResult(const TestStep& result);

  void OnTestComplete(bool success);

  CreateFileIOCB create_file_io_cb_;
  CompletionCB completion_cb_;

  std::string test_name_;
  std::list<TestStep> test_steps_;

  
  
  
  
  std::stack<cdm::FileIO*> file_io_stack_;
};

class FileIOTestRunner {
 public:
  explicit FileIOTestRunner(const CreateFileIOCB& create_file_io_cb);
  ~FileIOTestRunner();

  void AddTests();

  
  
  void RunAllTests(const CompletionCB& completion_cb);

 private:
  void OnTestComplete(bool success);
  void RunNextTest();

  CreateFileIOCB create_file_io_cb_;
  CompletionCB completion_cb_;
  std::list<FileIOTest> remaining_tests_;
  std::vector<uint8> large_data_;
  size_t total_num_tests_;  
  size_t num_passed_tests_;  

  DISALLOW_COPY_AND_ASSIGN (FileIOTestRunner);
};

}  

#endif  
