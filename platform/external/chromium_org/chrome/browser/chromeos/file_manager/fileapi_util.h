// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_FILE_MANAGER_FILEAPI_UTIL_H_
#define CHROME_BROWSER_CHROMEOS_FILE_MANAGER_FILEAPI_UTIL_H_

#include <string>

#include "base/callback_forward.h"
#include "base/files/file.h"
#include "base/files/file_path.h"
#include "storage/browser/fileapi/file_system_operation_runner.h"
#include "url/gurl.h"

class Profile;

namespace content {
class RenderViewHost;
}

namespace storage {
class FileSystemContext;
}

namespace file_manager {
namespace util {

struct FileDefinition {
  base::FilePath virtual_path;
  base::FilePath absolute_path;
  bool is_directory;
};

struct EntryDefinition {
  EntryDefinition();
  ~EntryDefinition();

  std::string file_system_root_url;  
  std::string file_system_name;      
  base::FilePath full_path;    
  
  
  bool is_directory;
  base::File::Error error;
};

typedef std::vector<FileDefinition> FileDefinitionList;
typedef std::vector<EntryDefinition> EntryDefinitionList;

typedef base::Callback<void(const EntryDefinition& entry_definition)>
    EntryDefinitionCallback;

typedef base::Callback<void(scoped_ptr<
    EntryDefinitionList> entry_definition_list)> EntryDefinitionListCallback;

storage::FileSystemContext* GetFileSystemContextForExtensionId(
    Profile* profile,
    const std::string& extension_id);

storage::FileSystemContext* GetFileSystemContextForRenderViewHost(
    Profile* profile,
    content::RenderViewHost* render_view_host);

base::FilePath ConvertDrivePathToRelativeFileSystemPath(
    Profile* profile,
    const std::string& extension_id,
    const base::FilePath& drive_path);

GURL ConvertDrivePathToFileSystemUrl(Profile* profile,
                                     const base::FilePath& drive_path,
                                     const std::string& extension_id);

bool ConvertAbsoluteFilePathToFileSystemUrl(Profile* profile,
                                            const base::FilePath& absolute_path,
                                            const std::string& extension_id,
                                            GURL* url);

bool ConvertAbsoluteFilePathToRelativeFileSystemPath(
    Profile* profile,
    const std::string& extension_id,
    const base::FilePath& absolute_path,
    base::FilePath* relative_path);

void ConvertFileDefinitionToEntryDefinition(
    Profile* profile,
    const std::string& extension_id,
    const FileDefinition& file_definition,
    const EntryDefinitionCallback& callback);

void ConvertFileDefinitionListToEntryDefinitionList(
    Profile* profile,
    const std::string& extension_id,
    const FileDefinitionList& file_definition_list,
    const EntryDefinitionListCallback& callback);

void CheckIfDirectoryExists(
    scoped_refptr<storage::FileSystemContext> file_system_context,
    const GURL& url,
    const storage::FileSystemOperationRunner::StatusCallback& callback);

}  
}  

#endif  
