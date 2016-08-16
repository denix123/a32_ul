// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_GN_NINJA_UTILS_H_
#define TOOLS_GN_NINJA_UTILS_H_

#include <string>

class Settings;
class SourceFile;
class Target;

SourceFile GetNinjaFileForTarget(const Target* target);

SourceFile GetNinjaFileForToolchain(const Settings* settings);

std::string GetNinjaRulePrefixForToolchain(const Settings* settings);

#endif  
