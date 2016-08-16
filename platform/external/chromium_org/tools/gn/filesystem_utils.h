// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_GN_FILESYSTEM_UTILS_H_
#define TOOLS_GN_FILESYSTEM_UTILS_H_

#include <string>

#include "base/files/file_path.h"
#include "base/strings/string_piece.h"
#include "tools/gn/settings.h"
#include "tools/gn/target.h"

class Err;
class Location;
class Value;

const char* GetExtensionForOutputType(Target::OutputType type,
                                      Settings::TargetOS os);

std::string FilePathToUTF8(const base::FilePath::StringType& str);
inline std::string FilePathToUTF8(const base::FilePath& path) {
  return FilePathToUTF8(path.value());
}
base::FilePath UTF8ToFilePath(const base::StringPiece& sp);


size_t FindExtensionOffset(const std::string& path);

base::StringPiece FindExtension(const std::string* path);


size_t FindFilenameOffset(const std::string& path);

base::StringPiece FindFilename(const std::string* path);

base::StringPiece FindFilenameNoExtension(const std::string* path);

void RemoveFilename(std::string* path);

inline bool IsSlash(const char ch) {
  return ch == '/' || ch == '\\';
}

bool EndsWithSlash(const std::string& s);


base::StringPiece FindDir(const std::string* path);

base::StringPiece FindLastDirComponent(const SourceDir& dir);

bool EnsureStringIsInOutputDir(const SourceDir& dir,
                               const std::string& str,
                               const ParseNode* origin,
                               Err* err);


bool IsPathAbsolute(const base::StringPiece& path);

bool MakeAbsolutePathRelativeIfPossible(const base::StringPiece& source_root,
                                        const base::StringPiece& path,
                                        std::string* dest);

std::string InvertDir(const SourceDir& dir);

void NormalizePath(std::string* path);

void ConvertPathToSystem(std::string* path);

std::string RebaseSourceAbsolutePath(const std::string& input,
                                     const SourceDir& dest_dir);

std::string DirectoryWithNoLastSlash(const SourceDir& dir);

SourceDir SourceDirForPath(const base::FilePath& source_root,
                           const base::FilePath& path);

SourceDir SourceDirForCurrentDirectory(const base::FilePath& source_root);

std::string GetOutputSubdirName(const Label& toolchain_label, bool is_default);


SourceDir GetToolchainOutputDir(const Settings* settings);
SourceDir GetToolchainOutputDir(const BuildSettings* build_settings,
                                const Label& label, bool is_default);

SourceDir GetToolchainGenDir(const Settings* settings);
OutputFile GetToolchainGenDirAsOutputFile(const Settings* settings);
SourceDir GetToolchainGenDir(const BuildSettings* build_settings,
                             const Label& toolchain_label,
                             bool is_default);

SourceDir GetOutputDirForSourceDir(const Settings* settings,
                                   const SourceDir& source_dir);
OutputFile GetOutputDirForSourceDirAsOutputFile(const Settings* settings,
                                                const SourceDir& source_dir);

SourceDir GetGenDirForSourceDir(const Settings* settings,
                                 const SourceDir& source_dir);
OutputFile GetGenDirForSourceDirAsOutputFile(const Settings* settings,
                                             const SourceDir& source_dir);

SourceDir GetTargetOutputDir(const Target* target);
OutputFile GetTargetOutputDirAsOutputFile(const Target* target);
SourceDir GetTargetGenDir(const Target* target);
OutputFile GetTargetGenDirAsOutputFile(const Target* target);

SourceDir GetCurrentOutputDir(const Scope* scope);
SourceDir GetCurrentGenDir(const Scope* scope);

#endif  
