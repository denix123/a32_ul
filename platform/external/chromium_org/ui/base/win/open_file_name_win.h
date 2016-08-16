// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_WIN_OPEN_FILE_NAME_WIN_H_
#define UI_BASE_WIN_OPEN_FILE_NAME_WIN_H_

#include <Windows.h>
#include <Commdlg.h>

#include <vector>

#include "base/macros.h"
#include "base/strings/string16.h"
#include "base/tuple.h"
#include "ui/base/ui_base_export.h"

namespace base {
class FilePath;
}  

namespace ui {
namespace win {

class UI_BASE_EXPORT OpenFileName {
 public:
  
  
  
  OpenFileName(HWND parent_window, DWORD flags);
  ~OpenFileName();

  
  void SetFilters(
      const std::vector<Tuple2<base::string16, base::string16> >& filters);

  
  void SetInitialSelection(const base::FilePath& initial_directory,
                           const base::FilePath& initial_filename);

  
  
  
  
  void MaybeInstallWindowPositionHookForSaveAsOnXP();

  
  
  base::FilePath GetSingleResult();

  
  void GetResult(base::FilePath* directory,
                 std::vector<base::FilePath>* filenames);

  
  OPENFILENAME* GetOPENFILENAME() { return &openfilename_; }

  
  const OPENFILENAME* GetOPENFILENAME() const { return &openfilename_; }

  
  
  static void SetResult(const base::FilePath& directory,
                        const std::vector<base::FilePath>& filenames,
                        OPENFILENAME* openfilename);

  
  
  static std::vector<Tuple2<base::string16, base::string16> > GetFilters(
      const OPENFILENAME* openfilename);

 private:
  OPENFILENAME openfilename_;
  base::string16 initial_directory_buffer_;
  wchar_t filename_buffer_[UNICODE_STRING_MAX_CHARS];
  base::string16 filter_buffer_;

  DISALLOW_COPY_AND_ASSIGN(OpenFileName);
};

}  
}  

#endif  
