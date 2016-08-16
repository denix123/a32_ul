// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_COMMON_CONSTANTS_H_
#define EXTENSIONS_COMMON_CONSTANTS_H_

#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "ui/base/layout.h"

namespace extensions {

extern const char kExtensionScheme[];

extern const char kExtensionResourceScheme[];

extern const base::FilePath::CharType kManifestFilename[];

extern const base::FilePath::CharType kLocaleFolder[];

extern const base::FilePath::CharType kMessagesFilename[];

extern const base::FilePath::CharType kPlatformSpecificFolder[];

extern const base::FilePath::CharType kMetadataFolder[];

extern const base::FilePath::CharType kVerifiedContentsFilename[];

extern const base::FilePath::CharType kComputedHashesFilename[];

extern const char kInstallDirectoryName[];

extern const char kTempExtensionName[];

extern const char kDecodedImagesFilename[];

extern const char kDecodedMessageCatalogsFilename[];

extern const char kGeneratedBackgroundPageFilename[];

extern const char kModulesDir[];

extern const base::FilePath::CharType kExtensionFileExtension[];

extern const base::FilePath::CharType kExtensionKeyFileExtension[];

extern const int kDefaultUpdateFrequencySeconds;

extern const char kLocalAppSettingsDirectoryName[];

extern const char kLocalExtensionSettingsDirectoryName[];

extern const char kSyncAppSettingsDirectoryName[];

extern const char kSyncExtensionSettingsDirectoryName[];

extern const char kManagedSettingsDirectoryName[];

extern const char kStateStoreName[];

extern const char kRulesStoreName[];

extern const char kAuthUserQueryKey[];

extern const char kMimeTypeJpeg[];
extern const char kMimeTypePng[];

extern const char kWebStoreAppId[];

}  

namespace extension_misc {

const int kUnknownWindowId = -1;

const int kCurrentWindowId = -2;

enum ExtensionIcons {
  EXTENSION_ICON_GIGANTOR = 512,
  EXTENSION_ICON_EXTRA_LARGE = 256,
  EXTENSION_ICON_LARGE = 128,
  EXTENSION_ICON_MEDIUM = 48,
  EXTENSION_ICON_SMALL = 32,
  EXTENSION_ICON_SMALLISH = 24,
  EXTENSION_ICON_ACTION = 19,
  EXTENSION_ICON_BITTY = 16,
  EXTENSION_ICON_INVALID = 0,
};

extern const int kExtensionIconSizes[];
extern const size_t kNumExtensionIconSizes;

struct IconRepresentationInfo {
  
  const int size;
  
  
  const char* const size_string;
  
  const ui::ScaleFactor scale;
};

extern const IconRepresentationInfo kExtensionActionIconSizes[];
const size_t kNumExtensionActionIconSizes = 2u;

}  

#endif  
