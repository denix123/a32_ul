// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_FAKE_PROVIDED_FILE_SYSTEM_H_
#define CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_FAKE_PROVIDED_FILE_SYSTEM_H_

#include <map>
#include <string>
#include <vector>

#include "base/callback.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/task/cancelable_task_tracker.h"
#include "chrome/browser/chromeos/file_system_provider/provided_file_system_info.h"
#include "chrome/browser/chromeos/file_system_provider/provided_file_system_interface.h"

class Profile;

namespace base {
class Time;
}  

namespace net {
class IOBuffer;
}  

namespace chromeos {
namespace file_system_provider {

class RequestManager;

extern const char kFakeFilePath[];

struct FakeEntry {
  FakeEntry();
  FakeEntry(scoped_ptr<EntryMetadata> metadata, const std::string& contents);
  ~FakeEntry();

  scoped_ptr<EntryMetadata> metadata;
  std::string contents;

 private:
  DISALLOW_COPY_AND_ASSIGN(FakeEntry);
};

class FakeProvidedFileSystem : public ProvidedFileSystemInterface {
 public:
  explicit FakeProvidedFileSystem(
      const ProvidedFileSystemInfo& file_system_info);
  virtual ~FakeProvidedFileSystem();

  
  void AddEntry(const base::FilePath& entry_path,
                bool is_directory,
                const std::string& name,
                int64 size,
                base::Time modification_time,
                std::string mime_type,
                std::string contents);

  
  
  
  const FakeEntry* GetEntry(const base::FilePath& entry_path) const;

  
  virtual AbortCallback RequestUnmount(
      const storage::AsyncFileUtil::StatusCallback& callback) OVERRIDE;
  virtual AbortCallback GetMetadata(
      const base::FilePath& entry_path,
      ProvidedFileSystemInterface::MetadataFieldMask fields,
      const ProvidedFileSystemInterface::GetMetadataCallback& callback)
      OVERRIDE;
  virtual AbortCallback ReadDirectory(
      const base::FilePath& directory_path,
      const storage::AsyncFileUtil::ReadDirectoryCallback& callback) OVERRIDE;
  virtual AbortCallback OpenFile(const base::FilePath& file_path,
                                 OpenFileMode mode,
                                 const OpenFileCallback& callback) OVERRIDE;
  virtual AbortCallback CloseFile(
      int file_handle,
      const storage::AsyncFileUtil::StatusCallback& callback) OVERRIDE;
  virtual AbortCallback ReadFile(
      int file_handle,
      net::IOBuffer* buffer,
      int64 offset,
      int length,
      const ReadChunkReceivedCallback& callback) OVERRIDE;
  virtual AbortCallback CreateDirectory(
      const base::FilePath& directory_path,
      bool recursive,
      const storage::AsyncFileUtil::StatusCallback& callback) OVERRIDE;
  virtual AbortCallback DeleteEntry(
      const base::FilePath& entry_path,
      bool recursive,
      const storage::AsyncFileUtil::StatusCallback& callback) OVERRIDE;
  virtual AbortCallback CreateFile(
      const base::FilePath& file_path,
      const storage::AsyncFileUtil::StatusCallback& callback) OVERRIDE;
  virtual AbortCallback CopyEntry(
      const base::FilePath& source_path,
      const base::FilePath& target_path,
      const storage::AsyncFileUtil::StatusCallback& callback) OVERRIDE;
  virtual AbortCallback MoveEntry(
      const base::FilePath& source_path,
      const base::FilePath& target_path,
      const storage::AsyncFileUtil::StatusCallback& callback) OVERRIDE;
  virtual AbortCallback Truncate(
      const base::FilePath& file_path,
      int64 length,
      const storage::AsyncFileUtil::StatusCallback& callback) OVERRIDE;
  virtual AbortCallback WriteFile(
      int file_handle,
      net::IOBuffer* buffer,
      int64 offset,
      int length,
      const storage::AsyncFileUtil::StatusCallback& callback) OVERRIDE;
  virtual const ProvidedFileSystemInfo& GetFileSystemInfo() const OVERRIDE;
  virtual RequestManager* GetRequestManager() OVERRIDE;
  virtual base::WeakPtr<ProvidedFileSystemInterface> GetWeakPtr() OVERRIDE;

  
  
  static ProvidedFileSystemInterface* Create(
      Profile* profile,
      const ProvidedFileSystemInfo& file_system_info);

 private:
  typedef std::map<base::FilePath, linked_ptr<FakeEntry> > Entries;
  typedef std::map<int, base::FilePath> OpenedFilesMap;

  
  
  AbortCallback PostAbortableTask(const base::Closure& callback);

  
  
  void Abort(int task_id,
             const storage::AsyncFileUtil::StatusCallback& callback);

  
  
  
  void AbortMany(const std::vector<int>& task_ids,
                 const storage::AsyncFileUtil::StatusCallback& callback);

  ProvidedFileSystemInfo file_system_info_;
  Entries entries_;
  OpenedFilesMap opened_files_;
  int last_file_handle_;
  base::CancelableTaskTracker tracker_;

  base::WeakPtrFactory<FakeProvidedFileSystem> weak_ptr_factory_;
  DISALLOW_COPY_AND_ASSIGN(FakeProvidedFileSystem);
};

}  
}  

#endif  
