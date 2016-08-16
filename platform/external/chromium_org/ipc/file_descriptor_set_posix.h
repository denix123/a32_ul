// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IPC_FILE_DESCRIPTOR_SET_POSIX_H_
#define IPC_FILE_DESCRIPTOR_SET_POSIX_H_

#include <vector>

#include "base/basictypes.h"
#include "base/files/file.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_vector.h"
#include "ipc/ipc_export.h"

class IPC_EXPORT FileDescriptorSet
    : public base::RefCountedThreadSafe<FileDescriptorSet> {
 public:
  FileDescriptorSet();

  
  
  
  
  
  
  
  
  static const size_t kMaxDescriptorsPerMessage = 7;

  
  

  
  bool AddToBorrow(base::PlatformFile fd);
  
  
  bool AddToOwn(base::ScopedFD fd);

  


  
  

  
  unsigned size() const { return descriptors_.size(); }
  
  bool empty() const { return 0 == size(); }
  
  
  
  
  
  
  
  base::PlatformFile TakeDescriptorAt(unsigned n);

  


  
  

  
  
  
  void PeekDescriptors(base::PlatformFile* buffer) const;
  
  
  
  void CommitAll();
  
  
  bool ContainsDirectoryDescriptor() const;
  
  
  void ReleaseFDsToClose(std::vector<base::PlatformFile>* fds);

  


  
  

  
  
  
  void AddDescriptorsToOwn(const base::PlatformFile* buffer, unsigned count);

  

 private:
  friend class base::RefCountedThreadSafe<FileDescriptorSet>;

  ~FileDescriptorSet();

  
  
  
  
  std::vector<base::PlatformFile> descriptors_;
  ScopedVector<base::ScopedFD> owned_descriptors_;

  
  
  
  
  mutable unsigned consumed_descriptor_highwater_;

  DISALLOW_COPY_AND_ASSIGN(FileDescriptorSet);
};

#endif  
