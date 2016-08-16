// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_GN_ESCAPE_H_
#define TOOLS_GN_ESCAPE_H_

#include <iosfwd>

#include "base/strings/string_piece.h"

enum EscapingMode {
  
  ESCAPE_NONE,

  
  ESCAPE_NINJA,

  
  
  
  ESCAPE_NINJA_COMMAND,

  
  
  
  
  ESCAPE_NINJA_PREFORMATTED_COMMAND,
};

enum EscapingPlatform {
  
  ESCAPE_PLATFORM_CURRENT,

  
  ESCAPE_PLATFORM_POSIX,
  ESCAPE_PLATFORM_WIN,
};

struct EscapeOptions {
  EscapeOptions()
      : mode(ESCAPE_NONE),
        platform(ESCAPE_PLATFORM_CURRENT),
        inhibit_quoting(false) {
  }

  EscapingMode mode;

  
  
  EscapingPlatform platform;

  
  
  
  
  
  
  
  
  bool inhibit_quoting;
};

// (if inhibit_quoting was set) quoted will be written to it. This value should
// be initialized to false by the caller and will be written to only if it's
std::string EscapeString(const base::StringPiece& str,
                         const EscapeOptions& options,
                         bool* needed_quoting);

void EscapeStringToStream(std::ostream& out,
                          const base::StringPiece& str,
                          const EscapeOptions& options);

#endif  
