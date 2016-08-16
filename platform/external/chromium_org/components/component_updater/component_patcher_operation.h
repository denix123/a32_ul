// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_COMPONENT_UPDATER_COMPONENT_PATCHER_OPERATION_H_
#define COMPONENTS_COMPONENT_UPDATER_COMPONENT_PATCHER_OPERATION_H_

#include <string>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "components/component_updater/component_unpacker.h"

namespace base {
class DictionaryValue;
}  

namespace component_updater {

extern const char kOp[];
extern const char kBsdiff[];
extern const char kCourgette[];
extern const char kInput[];
extern const char kPatch[];

class ComponentInstaller;

class DeltaUpdateOp : public base::RefCountedThreadSafe<DeltaUpdateOp> {
 public:
  DeltaUpdateOp();

  
  
  void Run(const base::DictionaryValue* command_args,
           const base::FilePath& input_dir,
           const base::FilePath& unpack_dir,
           ComponentInstaller* installer,
           const ComponentUnpacker::Callback& callback,
           scoped_refptr<base::SequencedTaskRunner> task_runner);

 protected:
  virtual ~DeltaUpdateOp();

  scoped_refptr<base::SequencedTaskRunner> GetTaskRunner();

  std::string output_sha256_;
  base::FilePath output_abs_path_;

 private:
  friend class base::RefCountedThreadSafe<DeltaUpdateOp>;

  ComponentUnpacker::Error CheckHash();

  
  
  
  virtual ComponentUnpacker::Error DoParseArguments(
      const base::DictionaryValue* command_args,
      const base::FilePath& input_dir,
      ComponentInstaller* installer) = 0;

  
  
  
  virtual void DoRun(const ComponentUnpacker::Callback& callback) = 0;

  
  
  
  void DoneRunning(ComponentUnpacker::Error error, int extended_error);

  ComponentUnpacker::Callback callback_;
  scoped_refptr<base::SequencedTaskRunner> task_runner_;

  DISALLOW_COPY_AND_ASSIGN(DeltaUpdateOp);
};

class DeltaUpdateOpCopy : public DeltaUpdateOp {
 public:
  DeltaUpdateOpCopy();

 private:
  virtual ~DeltaUpdateOpCopy();

  
  virtual ComponentUnpacker::Error DoParseArguments(
      const base::DictionaryValue* command_args,
      const base::FilePath& input_dir,
      ComponentInstaller* installer) OVERRIDE;

  virtual void DoRun(const ComponentUnpacker::Callback& callback) OVERRIDE;

  base::FilePath input_abs_path_;

  DISALLOW_COPY_AND_ASSIGN(DeltaUpdateOpCopy);
};

class DeltaUpdateOpCreate : public DeltaUpdateOp {
 public:
  DeltaUpdateOpCreate();

 private:
  virtual ~DeltaUpdateOpCreate();

  
  virtual ComponentUnpacker::Error DoParseArguments(
      const base::DictionaryValue* command_args,
      const base::FilePath& input_dir,
      ComponentInstaller* installer) OVERRIDE;

  virtual void DoRun(const ComponentUnpacker::Callback& callback) OVERRIDE;

  base::FilePath patch_abs_path_;

  DISALLOW_COPY_AND_ASSIGN(DeltaUpdateOpCreate);
};

class OutOfProcessPatcher
    : public base::RefCountedThreadSafe<OutOfProcessPatcher> {
 public:
  virtual void Patch(const std::string& operation,
                     scoped_refptr<base::SequencedTaskRunner> task_runner,
                     const base::FilePath& input_abs_path,
                     const base::FilePath& patch_abs_path,
                     const base::FilePath& output_abs_path,
                     base::Callback<void(int result)> callback) = 0;

 protected:
  friend class base::RefCountedThreadSafe<OutOfProcessPatcher>;

  virtual ~OutOfProcessPatcher() {}
};

class DeltaUpdateOpPatch : public DeltaUpdateOp {
 public:
  
  DeltaUpdateOpPatch(const std::string& operation,
                     scoped_refptr<OutOfProcessPatcher> out_of_process_patcher);

 private:
  virtual ~DeltaUpdateOpPatch();

  
  virtual ComponentUnpacker::Error DoParseArguments(
      const base::DictionaryValue* command_args,
      const base::FilePath& input_dir,
      ComponentInstaller* installer) OVERRIDE;

  virtual void DoRun(const ComponentUnpacker::Callback& callback) OVERRIDE;

  
  
  void DonePatching(const ComponentUnpacker::Callback& callback, int result);

  std::string operation_;
  scoped_refptr<OutOfProcessPatcher> out_of_process_patcher_;
  base::FilePath patch_abs_path_;
  base::FilePath input_abs_path_;

  DISALLOW_COPY_AND_ASSIGN(DeltaUpdateOpPatch);
};

DeltaUpdateOp* CreateDeltaUpdateOp(
    const std::string& operation,
    scoped_refptr<OutOfProcessPatcher> out_of_process_patcher);

}  

#endif  
