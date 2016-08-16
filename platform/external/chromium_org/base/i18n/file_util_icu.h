// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_I18N_FILE_UTIL_ICU_H_
#define BASE_I18N_FILE_UTIL_ICU_H_


#include "base/files/file_path.h"
#include "base/i18n/base_i18n_export.h"
#include "base/strings/string16.h"

namespace base {
namespace i18n {

BASE_I18N_EXPORT bool IsFilenameLegal(const string16& file_name);

BASE_I18N_EXPORT void ReplaceIllegalCharactersInPath(
    FilePath::StringType* file_name,
    char replace_char);

BASE_I18N_EXPORT bool LocaleAwareCompareFilenames(const FilePath& a,
                                                  const FilePath& b);

BASE_I18N_EXPORT void NormalizeFileNameEncoding(FilePath* file_name);

}  
}  

#endif  
