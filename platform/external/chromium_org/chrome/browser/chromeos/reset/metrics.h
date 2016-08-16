// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_RESET_METRICS_H_
#define CHROME_BROWSER_CHROMEOS_RESET_METRICS_H_

namespace chromeos {
namespace reset {

enum DialogViewType {

  
  DIALOG_FROM_OPTIONS,

  
  DIALOG_SHORTCUT_CONFIRMING_POWERWASH_ONLY,

  
  DIALOG_SHORTCUT_CONFIRMING_POWERWASH_AND_ROLLBACK,

  
  DIALOG_SHORTCUT_OFFERING_ROLLBACK_UNAVAILABLE,

  
  DIALOG_SHORTCUT_OFFERING_ROLLBACK_AVAILABLE,

  
  DIALOG_SHORTCUT_RESTART_REQUIRED,

  
  DIALOG_VIEW_TYPE_SIZE
};

}  
}  

#endif  
