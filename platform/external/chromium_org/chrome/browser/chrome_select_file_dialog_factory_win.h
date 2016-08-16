// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROME_SELECT_FILE_DIALOG_FACTORY_WIN_H_
#define CHROME_BROWSER_CHROME_SELECT_FILE_DIALOG_FACTORY_WIN_H_

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "ui/shell_dialogs/select_file_dialog_factory.h"

namespace base {
class SequencedTaskRunner;
}  

class ChromeSelectFileDialogFactory : public ui::SelectFileDialogFactory {
 public:
  
  explicit ChromeSelectFileDialogFactory(
      const scoped_refptr<base::SequencedTaskRunner>& blocking_task_runner);
  virtual ~ChromeSelectFileDialogFactory();

  
  virtual ui::SelectFileDialog* Create(ui::SelectFileDialog::Listener* listener,
                                       ui::SelectFilePolicy* policy) OVERRIDE;

 private:
  scoped_refptr<base::SequencedTaskRunner> blocking_task_runner_;

  DISALLOW_COPY_AND_ASSIGN(ChromeSelectFileDialogFactory);
};

#endif  
