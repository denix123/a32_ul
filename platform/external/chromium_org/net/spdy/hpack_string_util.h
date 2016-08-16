// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SPDY_HPACK_STRING_UTIL_H_
#define NET_SPDY_HPACK_STRING_UTIL_H_

#include "base/strings/string_piece.h"
#include "net/base/net_export.h"

namespace net {


bool NET_EXPORT_PRIVATE StringPiecesEqualConstantTime(
    base::StringPiece str1,
    base::StringPiece str2);

}  

#endif  
