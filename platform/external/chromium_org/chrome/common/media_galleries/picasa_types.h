// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_MEDIA_GALLERIES_PICASA_TYPES_H_
#define CHROME_COMMON_MEDIA_GALLERIES_PICASA_TYPES_H_

#include <map>
#include <set>
#include <string>

#include "base/files/file.h"
#include "base/files/file_path.h"
#include "base/move.h"
#include "ipc/ipc_platform_file.h"

namespace picasa {

struct AlbumInfo;

typedef std::map<std::string, base::FilePath> AlbumImages;
typedef std::set<std::string> AlbumUIDSet;
typedef std::map<std::string, AlbumImages> AlbumImagesMap;
typedef std::map<std::string, AlbumInfo> AlbumMap;

extern const char kPicasaDatabaseDirName[];
extern const char kPicasaTempDirName[];
extern const char kPicasaINIFilename[];

extern const char kPicasaAlbumTableName[];
extern const char kAlbumTokenPrefix[];

extern const uint32 kAlbumCategoryAlbum;
extern const uint32 kAlbumCategoryFolder;
extern const uint32 kAlbumCategoryInvalid;

struct AlbumInfo {
  AlbumInfo();
  AlbumInfo(const std::string& name, const base::Time& timestamp,
            const std::string& uid, const base::FilePath& path);

  ~AlbumInfo();

  std::string name;
  base::Time timestamp;
  std::string uid;
  base::FilePath path;
};

struct AlbumTableFiles {
  MOVE_ONLY_TYPE_FOR_CPP_03(AlbumTableFiles, RValue)
 public:
  AlbumTableFiles();
  explicit AlbumTableFiles(const base::FilePath& directory_path);
  ~AlbumTableFiles();

  
  AlbumTableFiles(RValue other);
  AlbumTableFiles& operator=(RValue other);

  
  base::File indicator_file;

  base::File category_file;
  base::File date_file;
  base::File filename_file;
  base::File name_file;
  base::File token_file;
  base::File uid_file;
};

struct AlbumTableFilesForTransit {
  AlbumTableFilesForTransit();
  IPC::PlatformFileForTransit indicator_file;

  IPC::PlatformFileForTransit category_file;
  IPC::PlatformFileForTransit date_file;
  IPC::PlatformFileForTransit filename_file;
  IPC::PlatformFileForTransit name_file;
  IPC::PlatformFileForTransit token_file;
  IPC::PlatformFileForTransit uid_file;
};

struct FolderINIContents {
  base::FilePath folder_path;
  std::string ini_contents;

  bool operator<(const FolderINIContents& that) const {
    return folder_path < that.folder_path;
  }
};

}  

#endif  