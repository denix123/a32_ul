// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SYSTEM_CHROMEOS_SESSION_LOGOUT_CONFIRMATION_DIALOG_H_
#define ASH_SYSTEM_CHROMEOS_SESSION_LOGOUT_CONFIRMATION_DIALOG_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "ui/views/window/dialog_delegate.h"

namespace views {
class Label;
}

namespace ash {

class LogoutConfirmationController;

class LogoutConfirmationDialog : public views::DialogDelegateView {
 public:
  LogoutConfirmationDialog(LogoutConfirmationController* controller,
                           base::TimeTicks logout_time);
  virtual ~LogoutConfirmationDialog();

  void Update(base::TimeTicks logout_time);

  
  virtual bool Accept() OVERRIDE;
  virtual ui::ModalType GetModalType() const OVERRIDE;
  virtual base::string16 GetWindowTitle() const OVERRIDE;
  virtual base::string16 GetDialogButtonLabel(ui::DialogButton button) const
      OVERRIDE;
  virtual void OnClosed() OVERRIDE;
  virtual void DeleteDelegate() OVERRIDE;

 private:
  void UpdateLabel();

  LogoutConfirmationController* controller_;
  base::TimeTicks logout_time_;

  views::Label* label_;

  base::RepeatingTimer<LogoutConfirmationDialog> update_timer_;

  DISALLOW_COPY_AND_ASSIGN(LogoutConfirmationDialog);
};

}  

#endif  
