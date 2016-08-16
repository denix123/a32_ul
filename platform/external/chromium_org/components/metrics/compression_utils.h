// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_METRICS_COMPRESSION_UTILS_H_
#define COMPONENTS_METRICS_COMPRESSION_UTILS_H_

#include <string>

namespace metrics {

bool GzipCompress(const std::string& input, std::string* output);

bool GzipUncompress(const std::string& input, std::string* output);

}  

#endif  
