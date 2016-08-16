// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_COMMON_FILE_UTIL_H_
#define EXTENSIONS_COMMON_FILE_UTIL_H_

#include <map>
#include <string>
#include <vector>

#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "extensions/common/manifest.h"

class ExtensionIconSet;
class GURL;

namespace base {
class FilePath;
}

namespace extensions {
class Extension;
struct InstallWarning;
class MessageBundle;

namespace file_util {

extern const base::FilePath::CharType kTempDirectoryName[];

base::FilePath InstallExtension(const base::FilePath& unpacked_source_dir,
                                const std::string& id,
                                const std::string& version,
                                const base::FilePath& extensions_dir);

void UninstallExtension(const base::FilePath& extensions_dir,
                        const std::string& id);

scoped_refptr<Extension> LoadExtension(const base::FilePath& extension_root,
                                       Manifest::Location location,
                                       int flags,
                                       std::string* error);

scoped_refptr<Extension> LoadExtension(const base::FilePath& extension_root,
                                       const std::string& extension_id,
                                       Manifest::Location location,
                                       int flags,
                                       std::string* error);

base::DictionaryValue* LoadManifest(const base::FilePath& extension_root,
                                    std::string* error);

base::DictionaryValue* LoadManifest(
    const base::FilePath& extension_root,
    const base::FilePath::CharType* manifest_filename,
    std::string* error);

bool ValidateExtension(const Extension* extension,
                       std::string* error,
                       std::vector<InstallWarning>* warnings);

std::vector<base::FilePath> FindPrivateKeyFiles(
    const base::FilePath& extension_dir);

bool CheckForIllegalFilenames(const base::FilePath& extension_path,
                              std::string* error);

base::FilePath GetInstallTempDir(const base::FilePath& extensions_dir);

void DeleteFile(const base::FilePath& path, bool recursive);

base::FilePath ExtensionURLToRelativeFilePath(const GURL& url);

base::FilePath ExtensionResourceURLToFilePath(const GURL& url,
                                              const base::FilePath& root);

bool ValidateExtensionIconSet(const ExtensionIconSet& icon_set,
                              const Extension* extension,
                              int error_message_id,
                              std::string* error);

MessageBundle* LoadMessageBundle(const base::FilePath& extension_path,
                                 const std::string& default_locale,
                                 std::string* error);

std::map<std::string, std::string>* LoadMessageBundleSubstitutionMap(
    const base::FilePath& extension_path,
    const std::string& extension_id,
    const std::string& default_locale);

base::FilePath GetVerifiedContentsPath(const base::FilePath& extension_path);
base::FilePath GetComputedHashesPath(const base::FilePath& extension_path);

}  
}  

#endif  
