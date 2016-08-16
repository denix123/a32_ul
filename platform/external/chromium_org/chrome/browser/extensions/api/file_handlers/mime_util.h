// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_FILE_HANDLERS_MIME_UTIL_H_
#define CHROME_BROWSER_EXTENSIONS_API_FILE_HANDLERS_MIME_UTIL_H_

#include <string>
#include <vector>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"

class Profile;

namespace base {
class FilePath;
}  

namespace storage {
class FileSystemURL;
}  

namespace extensions {
namespace app_file_handler_util {

void GetMimeTypeForLocalPath(
    Profile* profile,
    const base::FilePath& local_path,
    const base::Callback<void(const std::string&)>& callback);

class MimeTypeCollector {
 public:
  typedef base::Callback<void(scoped_ptr<std::vector<std::string> >)>
      CompletionCallback;

  explicit MimeTypeCollector(Profile* profile);
  virtual ~MimeTypeCollector();

  
  
  void CollectForURLs(const std::vector<storage::FileSystemURL>& urls,
                      const CompletionCallback& callback);

  
  
  void CollectForLocalPaths(const std::vector<base::FilePath>& local_paths,
                            const CompletionCallback& callback);

 private:
  
  void OnMimeTypeCollected(size_t index, const std::string& mime_type);

  Profile* profile_;
  scoped_ptr<std::vector<std::string> > result_;
  size_t left_;
  CompletionCallback callback_;
  base::WeakPtrFactory<MimeTypeCollector> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(MimeTypeCollector);
};

}  
}  

#endif  
