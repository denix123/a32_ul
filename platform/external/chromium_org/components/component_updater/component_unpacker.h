// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_COMPONENT_UPDATER_COMPONENT_UNPACKER_H_
#define COMPONENTS_COMPONENT_UPDATER_COMPONENT_UNPACKER_H_

#include <stdint.h>
#include <string>
#include <vector>

#include "base/callback.h"
#include "base/files/file_path.h"
#include "base/json/json_file_value_serializer.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/sequenced_task_runner.h"

namespace component_updater {

class ComponentInstaller;
class ComponentPatcher;
class OutOfProcessPatcher;

scoped_ptr<base::DictionaryValue> ReadManifest(
    const base::FilePath& unpack_path);

class ComponentUnpacker : public base::RefCountedThreadSafe<ComponentUnpacker> {
 public:
  
  
  enum Error {
    kNone,
    kInvalidParams,
    kInvalidFile,
    kUnzipPathError,
    kUnzipFailed,
    kNoManifest,
    kBadManifest,
    kBadExtension,
    kInvalidId,
    kInstallerError,
    kIoError,
    kDeltaVerificationFailure,
    kDeltaBadCommands,
    kDeltaUnsupportedCommand,
    kDeltaOperationFailure,
    kDeltaPatchProcessFailure,
    kDeltaMissingExistingFile,
    kFingerprintWriteFailed,
  };

  typedef base::Callback<void(Error, int)> Callback;

  
  
  
  ComponentUnpacker(const std::vector<uint8_t>& pk_hash,
                    const base::FilePath& path,
                    const std::string& fingerprint,
                    ComponentInstaller* installer,
                    scoped_refptr<OutOfProcessPatcher> out_of_process_patcher,
                    scoped_refptr<base::SequencedTaskRunner> task_runner);

  
  
  void Unpack(const Callback& callback);

 private:
  friend class base::RefCountedThreadSafe<ComponentUnpacker>;

  virtual ~ComponentUnpacker();

  bool UnpackInternal();

  
  
  
  bool Verify();

  
  
  bool Unzip();

  
  
  
  bool BeginPatching();

  
  
  void EndPatching(Error error, int extended_error);

  
  void Install();

  
  
  
  
  void Finish();

  std::vector<uint8_t> pk_hash_;
  base::FilePath path_;
  base::FilePath unpack_path_;
  base::FilePath unpack_diff_path_;
  bool is_delta_;
  std::string fingerprint_;
  scoped_refptr<ComponentPatcher> patcher_;
  ComponentInstaller* installer_;
  Callback callback_;
  scoped_refptr<OutOfProcessPatcher> out_of_process_patcher_;
  Error error_;
  int extended_error_;
  scoped_refptr<base::SequencedTaskRunner> task_runner_;

  DISALLOW_COPY_AND_ASSIGN(ComponentUnpacker);
};

}  

#endif  
