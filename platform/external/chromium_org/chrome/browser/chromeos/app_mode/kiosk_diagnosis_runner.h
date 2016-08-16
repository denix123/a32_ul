// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_APP_MODE_KIOSK_DIAGNOSIS_RUNNER_H_
#define CHROME_BROWSER_CHROMEOS_APP_MODE_KIOSK_DIAGNOSIS_RUNNER_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/extensions/api/feedback_private/feedback_service.h"
#include "components/keyed_service/core/keyed_service.h"

class Profile;

namespace chromeos {

class KioskDiagnosisRunner : public KeyedService {
 public:
  
  static void Run(Profile* profile, const std::string& app_id);

 private:
  
  class Factory;

  explicit KioskDiagnosisRunner(Profile* profile);
  virtual ~KioskDiagnosisRunner();

  void Start(const std::string& app_id);

  void StartSystemLogCollection();
  void SendSysLogFeedback(const extensions::SystemInformationList& sys_info);
  void OnFeedbackSent(bool sent);

  Profile* profile_;
  std::string app_id_;
  base::WeakPtrFactory<KioskDiagnosisRunner> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(KioskDiagnosisRunner);
};

}  

#endif  
