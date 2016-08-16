// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_L10N_TIME_FORMAT_H_
#define UI_BASE_L10N_TIME_FORMAT_H_

#include "base/basictypes.h"
#include "base/strings/string16.h"
#include "ui/base/ui_base_export.h"

namespace base {
class Time;
class TimeDelta;
}

namespace ui {

class UI_BASE_EXPORT TimeFormat {
 public:
  enum Format {
    FORMAT_DURATION,   
    FORMAT_REMAINING,  
    FORMAT_ELAPSED,    
    FORMAT_COUNT       
  };

  enum Length {
    LENGTH_SHORT,  
    LENGTH_LONG,   
    LENGTH_COUNT   
  };

  
  
  
  
  static base::string16 Simple(Format format,
                               Length length,
                               const base::TimeDelta& delta);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  static base::string16 Detailed(Format format,
                                 Length length,
                                 int cutoff,
                                 const base::TimeDelta& delta);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  static base::string16 RelativeDate(const base::Time& time,
                                     const base::Time* optional_midnight_today);

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(TimeFormat);
};

}  

#endif  
