// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_GALLERIES_IMPORTED_MEDIA_GALLERY_REGISTRY_H_
#define CHROME_BROWSER_MEDIA_GALLERIES_IMPORTED_MEDIA_GALLERY_REGISTRY_H_

#include <set>
#include <string>

#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "base/lazy_instance.h"
#include "base/memory/scoped_ptr.h"

namespace iphoto {
class IPhotoDataProvider;
class IPhotoDataProviderTest;
}

namespace itunes {
class ITunesDataProvider;
class ITunesDataProviderTest;
}

namespace picasa {
class PicasaDataProvider;
class PicasaDataProviderTest;
}

class ImportedMediaGalleryRegistry {
 public:
  static ImportedMediaGalleryRegistry* GetInstance();

  void Initialize();

  
  bool RegisterPicasaFilesystemOnUIThread(const std::string& fs_name,
                                          const base::FilePath& database_path);

  bool RegisterITunesFilesystemOnUIThread(
      const std::string& fs_name,
      const base::FilePath& xml_library_path);

  bool RegisterIPhotoFilesystemOnUIThread(
      const std::string& fs_name,
      const base::FilePath& xml_library_path);

  bool RevokeImportedFilesystemOnUIThread(const std::string& fs_name);

  
  base::FilePath ImportedRoot();

  
#if defined(OS_WIN) || defined(OS_MACOSX)
  static picasa::PicasaDataProvider* PicasaDataProvider();
  static itunes::ITunesDataProvider* ITunesDataProvider();
#endif  

#if defined(OS_MACOSX)
  static iphoto::IPhotoDataProvider* IPhotoDataProvider();
#endif  

 private:
  friend struct base::DefaultLazyInstanceTraits<ImportedMediaGalleryRegistry>;
  friend class iphoto::IPhotoDataProviderTest;
  friend class itunes::ITunesDataProviderTest;
  friend class picasa::PicasaDataProviderTest;

  ImportedMediaGalleryRegistry();
  virtual ~ImportedMediaGalleryRegistry();

#if defined(OS_WIN) || defined(OS_MACOSX)
  void RegisterPicasaFileSystem(const base::FilePath& database_path);
  void RevokePicasaFileSystem();

  void RegisterITunesFileSystem(const base::FilePath& xml_library_path);
  void RevokeITunesFileSystem();
#endif  

#if defined(OS_MACOSX)
  void RegisterIPhotoFileSystem(const base::FilePath& xml_library_path);
  void RevokeIPhotoFileSystem();
#endif  

  base::FilePath imported_root_;

#if defined(OS_WIN) || defined(OS_MACOSX)
  
  scoped_ptr<picasa::PicasaDataProvider> picasa_data_provider_;
  scoped_ptr<itunes::ITunesDataProvider> itunes_data_provider_;

  
  std::set<std::string> picasa_fs_names_;
  std::set<std::string> itunes_fs_names_;

#ifndef NDEBUG
  base::FilePath picasa_database_path_;
  base::FilePath itunes_xml_library_path_;
#endif
#endif  

#if defined(OS_MACOSX)
  scoped_ptr<iphoto::IPhotoDataProvider> iphoto_data_provider_;

  std::set<std::string> iphoto_fs_names_;

#ifndef NDEBUG
  base::FilePath iphoto_xml_library_path_;
#endif
#endif  

  DISALLOW_COPY_AND_ASSIGN(ImportedMediaGalleryRegistry);
};

#endif  
