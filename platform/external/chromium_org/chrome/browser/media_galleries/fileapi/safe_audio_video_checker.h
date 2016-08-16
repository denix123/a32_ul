// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_GALLERIES_FILEAPI_SAFE_AUDIO_VIDEO_CHECKER_H_
#define CHROME_BROWSER_MEDIA_GALLERIES_FILEAPI_SAFE_AUDIO_VIDEO_CHECKER_H_

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/files/file.h"
#include "base/memory/weak_ptr.h"
#include "content/public/browser/utility_process_host_client.h"
#include "storage/browser/fileapi/copy_or_move_file_validator.h"

namespace content {
class UtilityProcessHost;
}

class SafeAudioVideoChecker : public content::UtilityProcessHostClient {
 public:
  
  SafeAudioVideoChecker(
      base::File file,
      const storage::CopyOrMoveFileValidator::ResultCallback& callback);

  
  void Start();

 private:
  enum State {
    INITIAL_STATE,
    PINGED_STATE,
    STARTED_STATE,
    FINISHED_STATE
  };

  virtual ~SafeAudioVideoChecker();

  
  virtual void OnProcessStarted();

  
  void OnCheckingFinished(bool valid);

  
  virtual void OnProcessCrashed(int exit_code) OVERRIDE;
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  State state_;

  base::File file_;

  const storage::CopyOrMoveFileValidator::ResultCallback callback_;

  base::WeakPtr<content::UtilityProcessHost> utility_process_host_;

  DISALLOW_COPY_AND_ASSIGN(SafeAudioVideoChecker);
};

#endif  
