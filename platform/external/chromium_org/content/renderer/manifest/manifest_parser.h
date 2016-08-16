// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MANIFEST_MANIFEST_PARSER_H_
#define CONTENT_RENDERER_MANIFEST_MANIFEST_PARSER_H_

#include "base/strings/string_piece.h"
#include "content/common/content_export.h"

class GURL;

namespace base {
class DictionaryValue;
}

namespace content {

struct Manifest;

class CONTENT_EXPORT ManifestParser {
 public:
  static Manifest Parse(const base::StringPiece&,
                        const GURL& manifest_url,
                        const GURL& document_url);
};

} 

#endif 
