// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_TEST_DATA_UTIL_H_
#define MEDIA_BASE_TEST_DATA_UTIL_H_

#include <string>
#include <utility>
#include <vector>

#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"

namespace media {

class DecoderBuffer;

typedef std::vector<std::pair<std::string, std::string> > QueryParams;

base::FilePath GetTestDataFilePath(const std::string& name);

base::FilePath GetTestDataPath();

std::string GetURLQueryString(const QueryParams& query_params);

scoped_refptr<DecoderBuffer> ReadTestDataFile(const std::string& name);

}  

#endif  
