// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MAC_OBSOLETE_SYSTEM_H_
#define CHROME_BROWSER_MAC_OBSOLETE_SYSTEM_H_

#include "base/basictypes.h"
#include "base/strings/string16.h"

class ObsoleteSystemMac {
 public:
  
  
  
  static bool Is32BitObsoleteNowOrSoon() {
#if defined(GOOGLE_CHROME_BUILD)
    return true;
#else
    return false;
#endif
  }

  
#if !defined(ARCH_CPU_64_BITS)
  static bool Has32BitOnlyCPU();
#else
  static bool Has32BitOnlyCPU() {
    return false;
  }
#endif

  
  
  
  
  
#if !defined(ARCH_CPU_64_BITS)
  static base::string16 LocalizedObsoleteSystemString();
#else
  static base::string16 LocalizedObsoleteSystemString() {
    return base::string16();
  }
#endif

  
  static bool Is32BitEndOfTheLine() {
    
    
    return false;
  }

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(ObsoleteSystemMac);
};

#endif  
