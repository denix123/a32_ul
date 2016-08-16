// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STORAGE_BROWSER_FILEAPI_RECURSIVE_OPERATION_DELEGATE_H_
#define STORAGE_BROWSER_FILEAPI_RECURSIVE_OPERATION_DELEGATE_H_

#include <queue>
#include <stack>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/weak_ptr.h"
#include "storage/browser/fileapi/file_system_operation.h"
#include "storage/browser/fileapi/file_system_url.h"

namespace storage {

class FileSystemContext;
class FileSystemOperationRunner;

class STORAGE_EXPORT RecursiveOperationDelegate
    : public base::SupportsWeakPtr<RecursiveOperationDelegate> {
 public:
  typedef FileSystemOperation::StatusCallback StatusCallback;
  typedef FileSystemOperation::FileEntryList FileEntryList;

  virtual ~RecursiveOperationDelegate();

  
  
  virtual void Run() = 0;

  
  
  virtual void RunRecursively() = 0;

  
  
  virtual void ProcessFile(const FileSystemURL& url,
                           const StatusCallback& callback) = 0;

  
  
  virtual void ProcessDirectory(const FileSystemURL& url,
                                const StatusCallback& callback) = 0;


  
  
  virtual void PostProcessDirectory(const FileSystemURL& url,
                                    const StatusCallback& callback) = 0;

  
  void Cancel();

 protected:
  explicit RecursiveOperationDelegate(FileSystemContext* file_system_context);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  void StartRecursiveOperation(const FileSystemURL& root,
                               const StatusCallback& callback);

  FileSystemContext* file_system_context() { return file_system_context_; }
  const FileSystemContext* file_system_context() const {
    return file_system_context_;
  }

  FileSystemOperationRunner* operation_runner();

  
  
  virtual void OnCancel();

 private:
  void DidTryProcessFile(const FileSystemURL& root,
                         base::File::Error error);
  void ProcessNextDirectory();
  void DidProcessDirectory(base::File::Error error);
  void DidReadDirectory(const FileSystemURL& parent,
                        base::File::Error error,
                        const FileEntryList& entries,
                        bool has_more);
  void ProcessPendingFiles();
  void DidProcessFile(base::File::Error error);
  void ProcessSubDirectory();
  void DidPostProcessDirectory(base::File::Error error);

  
  void Done(base::File::Error error);

  FileSystemContext* file_system_context_;
  StatusCallback callback_;
  std::stack<FileSystemURL> pending_directories_;
  std::stack<std::queue<FileSystemURL> > pending_directory_stack_;
  std::queue<FileSystemURL> pending_files_;
  int inflight_operations_;
  bool canceled_;

  DISALLOW_COPY_AND_ASSIGN(RecursiveOperationDelegate);
};

}  

#endif  
