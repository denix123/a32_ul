// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STORAGE_BROWSER_FILEAPI_FILE_OBSERVERS_H_
#define STORAGE_BROWSER_FILEAPI_FILE_OBSERVERS_H_

#include "base/basictypes.h"
#include "storage/browser/storage_browser_export.h"


namespace storage {

class FileSystemURL;

class STORAGE_EXPORT FileUpdateObserver {
 public:
  FileUpdateObserver() {}
  virtual ~FileUpdateObserver() {}

  virtual void OnStartUpdate(const FileSystemURL& url) = 0;
  virtual void OnUpdate(const FileSystemURL& url, int64 delta) = 0;
  virtual void OnEndUpdate(const FileSystemURL& url) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(FileUpdateObserver);
};

class STORAGE_EXPORT FileAccessObserver {
 public:
  FileAccessObserver() {}
  virtual ~FileAccessObserver() {}

  virtual void OnAccess(const FileSystemURL& url) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(FileAccessObserver);
};

class STORAGE_EXPORT FileChangeObserver {
 public:
  FileChangeObserver() {}
  virtual ~FileChangeObserver() {}

  virtual void OnCreateFile(const FileSystemURL& url) = 0;
  virtual void OnCreateFileFrom(const FileSystemURL& url,
                                const FileSystemURL& src) = 0;
  virtual void OnRemoveFile(const FileSystemURL& url) = 0;
  virtual void OnModifyFile(const FileSystemURL& url) = 0;

  virtual void OnCreateDirectory(const FileSystemURL& url) = 0;
  virtual void OnRemoveDirectory(const FileSystemURL& url) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(FileChangeObserver);
};

}  

#endif  
