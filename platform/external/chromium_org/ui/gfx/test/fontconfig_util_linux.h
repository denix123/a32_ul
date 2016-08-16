// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GFX_TEST_FONTCONFIG_UTIL_LINUX_H_
#define UI_GFX_TEST_FONTCONFIG_UTIL_LINUX_H_

#include <string>

#include "base/files/file_path.h"

namespace gfx {

extern const char* const kSystemFontsForFontconfig[];
extern const size_t kNumSystemFontsForFontconfig;

extern const char kFontconfigFileHeader[];
extern const char kFontconfigFileFooter[];

extern const char kFontconfigMatchHeader[];
extern const char kFontconfigMatchFooter[];

void SetUpFontconfig();

void TearDownFontconfig();

bool LoadFontIntoFontconfig(const base::FilePath& path);

bool LoadConfigFileIntoFontconfig(const base::FilePath& path);

bool LoadConfigDataIntoFontconfig(const base::FilePath& temp_dir,
                                  const std::string& data);

std::string CreateFontconfigEditStanza(const std::string& name,
                                       const std::string& type,
                                       const std::string& value);

std::string CreateFontconfigTestStanza(const std::string& name,
                                       const std::string& op,
                                       const std::string& type,
                                       const std::string& value);

std::string CreateFontconfigAliasStanza(const std::string& original_family,
                                        const std::string& preferred_family);

}  

#endif  
