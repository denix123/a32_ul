// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SAFE_BROWSING_SAFE_BROWSING_UTIL_H_
#define CHROME_BROWSER_SAFE_BROWSING_SAFE_BROWSING_UTIL_H_

#include <cstring>
#include <set>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string_piece.h"
#include "base/time/time.h"
#include "chrome/browser/safe_browsing/chunk_range.h"

namespace safe_browsing {
class ChunkData;
};

class GURL;

typedef uint32 SBPrefix;

struct ChunkUrl {
  std::string url;
  std::string list_name;
};

union SBFullHash {
  char full_hash[32];
  SBPrefix prefix;
};

inline bool SBFullHashEqual(const SBFullHash& a, const SBFullHash& b) {
  return !memcmp(a.full_hash, b.full_hash, sizeof(a.full_hash));
}

inline bool SBFullHashLess(const SBFullHash& a, const SBFullHash& b) {
  return memcmp(a.full_hash, b.full_hash, sizeof(a.full_hash)) < 0;
}

SBFullHash SBFullHashForString(const base::StringPiece& str);

class SBChunkData {
 public:
  SBChunkData();
  ~SBChunkData();

  
  
  
  explicit SBChunkData(safe_browsing::ChunkData* chunk_data);

  
  bool ParseFrom(const unsigned char* data, size_t length);

  
  
  
  int ChunkNumber() const;
  bool IsAdd() const;
  bool IsSub() const;
  int AddChunkNumberAt(size_t i) const;
  bool IsPrefix() const;
  size_t PrefixCount() const;
  SBPrefix PrefixAt(size_t i) const;
  bool IsFullHash() const;
  size_t FullHashCount() const;
  SBFullHash FullHashAt(size_t i) const;

 private:
  
  scoped_ptr<safe_browsing::ChunkData> chunk_data_;

  DISALLOW_COPY_AND_ASSIGN(SBChunkData);
};

struct SBFullHashResult {
  SBFullHash hash;
  
  int list_id;
  std::string metadata;
};

struct SBCachedFullHashResult {
  SBCachedFullHashResult();
  explicit SBCachedFullHashResult(const base::Time& in_expire_after);
  ~SBCachedFullHashResult();

  base::Time expire_after;
  std::vector<SBFullHashResult> full_hashes;
};

struct SBListChunkRanges {
  explicit SBListChunkRanges(const std::string& n);

  std::string name;  
  std::string adds;  
  std::string subs;  
};

struct SBChunkDelete {
  SBChunkDelete();
  ~SBChunkDelete();

  std::string list_name;
  bool is_sub_del;
  std::vector<ChunkRange> chunk_del;
};

enum SBThreatType {
  
  SB_THREAT_TYPE_SAFE,

  
  SB_THREAT_TYPE_URL_PHISHING,

  
  SB_THREAT_TYPE_URL_MALWARE,

  
  SB_THREAT_TYPE_URL_HARMFUL,

  
  SB_THREAT_TYPE_BINARY_MALWARE_URL,

  
  
  SB_THREAT_TYPE_CLIENT_SIDE_PHISHING_URL,

  
  SB_THREAT_TYPE_EXTENSION,

  
  
  SB_THREAT_TYPE_CLIENT_SIDE_MALWARE_URL,
};


namespace safe_browsing_util {

extern const char kMalwareList[];
extern const char kPhishingList[];
extern const char kBinUrlList[];
extern const char kCsdWhiteList[];
extern const char kDownloadWhiteList[];
extern const char kExtensionBlacklist[];
extern const char kSideEffectFreeWhitelist[];
extern const char kIPBlacklist[];

extern const char* kAllLists[8];

enum ListType {
  INVALID = -1,
  MALWARE = 0,
  PHISH = 1,
  BINURL = 2,
  
  CSDWHITELIST = 4,
  
  
  
  DOWNLOADWHITELIST = 6,
  
  EXTENSIONBLACKLIST = 8,
  
  SIDEEFFECTFREEWHITELIST = 10,
  
  IPBLACKLIST = 12,
  
};

ListType GetListId(const base::StringPiece& name);

bool GetListName(ListType list_id, std::string* list);

void CanonicalizeUrl(const GURL& url, std::string* canonicalized_hostname,
                     std::string* canonicalized_path,
                     std::string* canonicalized_query);

void GenerateHostsToCheck(const GURL& url, std::vector<std::string>* hosts);

void GeneratePathsToCheck(const GURL& url, std::vector<std::string>* paths);

void GeneratePatternsToCheck(const GURL& url, std::vector<std::string>* urls);

GURL GeneratePhishingReportUrl(const std::string& report_page,
                               const std::string& url_to_report,
                               bool is_client_side_detection);

SBFullHash StringToSBFullHash(const std::string& hash_in);
std::string SBFullHashToString(const SBFullHash& hash_out);

}  

#endif  
