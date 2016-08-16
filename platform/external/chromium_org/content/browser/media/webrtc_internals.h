// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_MEDIA_WEBRTC_INTERNALS_H_
#define CONTENT_BROWSER_MEDIA_WEBRTC_INTERNALS_H_

#include "base/gtest_prod_util.h"
#include "base/lazy_instance.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/process/process.h"
#include "base/values.h"
#include "content/common/content_export.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "ui/shell_dialogs/select_file_dialog.h"

namespace content {

class PowerSaveBlocker;
class WebContents;
class WebRTCInternalsUIObserver;

class CONTENT_EXPORT WebRTCInternals : public NotificationObserver,
                                       public ui::SelectFileDialog::Listener {
 public:
  static WebRTCInternals* GetInstance();

  
  
  
  
  
  
  
  
  
  void OnAddPeerConnection(int render_process_id,
                           base::ProcessId pid,
                           int lid,
                           const std::string& url,
                           const std::string& rtc_configuration,
                           const std::string& constraints);

  
  
  void OnRemovePeerConnection(base::ProcessId pid, int lid);

  
  
  
  void OnUpdatePeerConnection(base::ProcessId pid,
                              int lid,
                              const std::string& type,
                              const std::string& value);

  
  
  
  void OnAddStats(base::ProcessId pid, int lid, const base::ListValue& value);

  
  
  
  
  
  
  
  
  void OnGetUserMedia(int render_process_id,
                      base::ProcessId pid,
                      const std::string& origin,
                      bool audio,
                      bool video,
                      const std::string& audio_constraints,
                      const std::string& video_constraints);

  
  void AddObserver(WebRTCInternalsUIObserver *observer);
  void RemoveObserver(WebRTCInternalsUIObserver *observer);

  
  void UpdateObserver(WebRTCInternalsUIObserver* observer);

  
  void EnableAecDump(content::WebContents* web_contents);
  void DisableAecDump();

  bool aec_dump_enabled() {
    return aec_dump_enabled_;
  }

  base::FilePath aec_dump_file_path() {
    return aec_dump_file_path_;
  }

  void ResetForTesting();

 private:
  friend struct base::DefaultLazyInstanceTraits<WebRTCInternals>;
  FRIEND_TEST_ALL_PREFIXES(WebRtcAecDumpBrowserTest, CallWithAecDump);
  FRIEND_TEST_ALL_PREFIXES(WebRtcAecDumpBrowserTest,
                           CallWithAecDumpEnabledThenDisabled);
  FRIEND_TEST_ALL_PREFIXES(WebRtcAecDumpBrowserTest, TwoCallsWithAecDump);
  FRIEND_TEST_ALL_PREFIXES(WebRTCInternalsTest,
                           AecRecordingFileSelectionCanceled);

  WebRTCInternals();
  virtual ~WebRTCInternals();

  void SendUpdate(const std::string& command, base::Value* value);

  
  virtual void Observe(int type,
                       const NotificationSource& source,
                       const NotificationDetails& details) OVERRIDE;

  
  virtual void FileSelected(const base::FilePath& path,
                            int index,
                            void* unused_params) OVERRIDE;
  virtual void FileSelectionCanceled(void* params) OVERRIDE;

  
  void OnRendererExit(int render_process_id);

#if defined(ENABLE_WEBRTC)
  
  void EnableAecDumpOnAllRenderProcessHosts();
#endif

  
  
  
  void CreateOrReleasePowerSaveBlocker();

  ObserverList<WebRTCInternalsUIObserver> observers_;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  base::ListValue peer_connection_data_;

  
  
  
  
  
  
  
  base::ListValue get_user_media_requests_;

  NotificationRegistrar registrar_;

  
  scoped_refptr<ui::SelectFileDialog> select_file_dialog_;

  
  bool aec_dump_enabled_;
  base::FilePath aec_dump_file_path_;

  
  
  
  scoped_ptr<PowerSaveBlocker> power_save_blocker_;
};

}  

#endif  
