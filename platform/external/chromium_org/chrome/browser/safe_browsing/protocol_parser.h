// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SAFE_BROWSING_PROTOCOL_PARSER_H_
#define CHROME_BROWSER_SAFE_BROWSING_PROTOCOL_PARSER_H_


#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/scoped_vector.h"
#include "chrome/browser/safe_browsing/safe_browsing_util.h"

namespace base {
class TimeDelta;
};

namespace safe_browsing {


bool ParseUpdate(const char* chunk_data,
                 size_t chunk_len,
                 size_t* next_update_sec,
                 bool* reset,
                 std::vector<SBChunkDelete>* chunk_deletes,
                 std::vector<ChunkUrl>* chunk_urls);

bool ParseChunk(const char* chunk_data,
                size_t chunk_len,
                ScopedVector<SBChunkData>* chunks);

bool ParseGetHash(const char* chunk_data,
                  size_t chunk_len,
                  base::TimeDelta* cache_lifetime,
                  std::vector<SBFullHashResult>* full_hashes);

std::string FormatGetHash(const std::vector<SBPrefix>& prefixes);

std::string FormatList(const SBListChunkRanges& list);

}  

#endif  
