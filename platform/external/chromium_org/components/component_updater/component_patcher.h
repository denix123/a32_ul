// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef COMPONENTS_COMPONENT_UPDATER_COMPONENT_PATCHER_H_
#define COMPONENTS_COMPONENT_UPDATER_COMPONENT_PATCHER_H_

#include "base/callback_forward.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/values.h"
#include "components/component_updater/component_unpacker.h"

namespace base {
class FilePath;
}

namespace component_updater {

class ComponentInstaller;
class DeltaUpdateOp;
class OutOfProcessPatcher;

enum PatchType {
  kPatchTypeUnknown,
  kPatchTypeCourgette,
  kPatchTypeBsdiff,
};

class ComponentPatcher : public base::RefCountedThreadSafe<ComponentPatcher> {
 public:
  
  
  
  
  
  ComponentPatcher(const base::FilePath& input_dir,
                   const base::FilePath& unpack_dir,
                   ComponentInstaller* installer,
                   scoped_refptr<OutOfProcessPatcher> out_of_process_patcher,
                   scoped_refptr<base::SequencedTaskRunner> task_runner);

  
  
  
  
  void Start(const ComponentUnpacker::Callback& callback);

 private:
  friend class base::RefCountedThreadSafe<ComponentPatcher>;

  virtual ~ComponentPatcher();

  void StartPatching();

  void PatchNextFile();

  void DonePatchingFile(ComponentUnpacker::Error error, int extended_error);

  void DonePatching(ComponentUnpacker::Error error, int extended_error);

  const base::FilePath input_dir_;
  const base::FilePath unpack_dir_;
  ComponentInstaller* const installer_;
  scoped_refptr<OutOfProcessPatcher> out_of_process_patcher_;
  ComponentUnpacker::Callback callback_;
  scoped_ptr<base::ListValue> commands_;
  base::ValueVector::const_iterator next_command_;
  scoped_refptr<DeltaUpdateOp> current_operation_;
  scoped_refptr<base::SequencedTaskRunner> task_runner_;

  DISALLOW_COPY_AND_ASSIGN(ComponentPatcher);
};

}  

#endif  
