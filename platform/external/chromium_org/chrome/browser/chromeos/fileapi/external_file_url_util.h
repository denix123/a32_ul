// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_FILEAPI_EXTERNAL_FILE_URL_UTIL_H_
#define CHROME_BROWSER_CHROMEOS_FILEAPI_EXTERNAL_FILE_URL_UTIL_H_

class GURL;
class Profile;

namespace base {
class FilePath;
}

namespace storage {
class FileSystemURL;
}

namespace chromeos {

GURL FileSystemURLToExternalFileURL(
    const storage::FileSystemURL& file_system_url);

base::FilePath ExternalFileURLToVirtualPath(const GURL& url);

GURL CreateExternalFileURLFromPath(Profile* profile,
                                   const base::FilePath& path);

}  

#endif  
