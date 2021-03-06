// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GPU_CONFIG_GPU_TEST_EXPECTATIONS_PARSER_H_
#define GPU_CONFIG_GPU_TEST_EXPECTATIONS_PARSER_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "gpu/config/gpu_test_config.h"
#include "gpu/gpu_export.h"

namespace gpu {

class GPU_EXPORT GPUTestExpectationsParser {
 public:
  enum GPUTestExpectation {
    kGpuTestPass = 1 << 0,
    kGpuTestFail = 1 << 1,
    kGpuTestFlaky = 1 << 2,
    kGpuTestTimeout = 1 << 3,
    kGpuTestSkip = 1 << 4,
  };

  GPUTestExpectationsParser();
  ~GPUTestExpectationsParser();

  
  
  
  bool LoadTestExpectations(const std::string& data);
  bool LoadTestExpectations(const base::FilePath& path);

  
  const std::vector<std::string>& GetErrorMessages() const;

  
  int32 GetTestExpectation(const std::string& test_name,
                           const GPUTestBotConfig& bot_config) const;

  
  
  bool ParseConfig(const std::string& config_data, GPUTestConfig* config);

 private:
  struct GPUTestExpectationEntry {
    GPUTestExpectationEntry();

    std::string test_name;
    GPUTestConfig test_config;
    int32 test_expectation;
    size_t line_number;
  };

  
  
  bool ParseLine(const std::string& line_data, size_t line_number);

  
  bool UpdateTestConfig(
      GPUTestConfig* config, int32 token, size_t line_number);

  
  bool UpdateTestConfig(GPUTestConfig* config,
                        const std::string & gpu_device_id,
                        size_t line_number);

  
  
  bool DetectConflictsBetweenEntries();

  
  void PushErrorMessage(const std::string& message, size_t line_number);
  void PushErrorMessage(const std::string& message,
                        size_t entry1_line_number,
                        size_t entry2_line_number);

  std::vector<GPUTestExpectationEntry> entries_;
  std::vector<std::string> error_messages_;
};

}  

#endif  

