// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WIN8_VIEWER_METRO_VIEWER_PROCESS_HOST_H_
#define WIN8_VIEWER_METRO_VIEWER_PROCESS_HOST_H_

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "base/threading/non_thread_safe.h"
#include "ipc/ipc_channel_proxy.h"
#include "ipc/ipc_listener.h"
#include "ipc/ipc_sender.h"
#include "ipc/message_filter.h"
#include "ui/gfx/native_widget_types.h"
#include "win8/viewer/metro_viewer_exports.h"

namespace base {
class SingleThreadTaskRunner;
class WaitableEvent;
}

namespace IPC {
class ChannelProxy;
class Message;
}

namespace win8 {

class METRO_VIEWER_EXPORT MetroViewerProcessHost : public IPC::Listener,
                                                   public IPC::Sender,
                                                   public base::NonThreadSafe {
 public:
  typedef base::Callback<void(const base::FilePath&, int, void*)>
      OpenFileCompletion;

  typedef base::Callback<void(const std::vector<base::FilePath>&, void*)>
      OpenMultipleFilesCompletion;

  typedef base::Callback<void(const base::FilePath&, int, void*)>
      SaveFileCompletion;

  typedef base::Callback<void(const base::FilePath&, int, void*)>
      SelectFolderCompletion;

  typedef base::Callback<void(void*)> FileSelectionCanceled;

  
  
  
  
  
  
  explicit MetroViewerProcessHost(
      base::SingleThreadTaskRunner* ipc_task_runner);
  virtual ~MetroViewerProcessHost();

  
  
  base::ProcessId GetViewerProcessId();

  
  
  
  
  
  bool LaunchViewerAndWaitForConnection(
      const base::string16& app_user_model_id);

  
  
  
  static void HandleActivateDesktop(const base::FilePath& shortcut,
                                    bool ash_exit);

  
  
  static void HandleMetroExit();

  
  
  
  static void HandleOpenFile(const base::string16& title,
                             const base::FilePath& default_path,
                             const base::string16& filter,
                             const OpenFileCompletion& on_success,
                             const FileSelectionCanceled& on_failure);

  
  
  
  static void HandleOpenMultipleFiles(
      const base::string16& title,
      const base::FilePath& default_path,
      const base::string16& filter,
      const OpenMultipleFilesCompletion& on_success,
      const FileSelectionCanceled& on_failure);

  
  
  
  static void HandleSaveFile(const base::string16& title,
                             const base::FilePath& default_path,
                             const base::string16& filter,
                             int filter_index,
                             const base::string16& default_extension,
                             const SaveFileCompletion& on_success,
                             const FileSelectionCanceled& on_failure);

  
  
  
  static void HandleSelectFolder(const base::string16& title,
                                 const SelectFolderCompletion& on_success,
                                 const FileSelectionCanceled& on_failure);

 protected:
  
  virtual bool Send(IPC::Message* msg) OVERRIDE;

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;
  virtual void OnChannelError() OVERRIDE = 0;

 private:
  
  
  void HandleOpenFileImpl(const base::string16& title,
                          const base::FilePath& default_path,
                          const base::string16& filter,
                          const OpenFileCompletion& on_success,
                          const FileSelectionCanceled& on_failure);
  void HandleOpenMultipleFilesImpl(
      const base::string16& title,
      const base::FilePath& default_path,
      const base::string16& filter,
      const OpenMultipleFilesCompletion& on_success,
      const FileSelectionCanceled& on_failure);
  void HandleSaveFileImpl(const base::string16& title,
                          const base::FilePath& default_path,
                          const base::string16& filter,
                          int filter_index,
                          const base::string16& default_extension,
                          const SaveFileCompletion& on_success,
                          const FileSelectionCanceled& on_failure);
  void HandleSelectFolderImpl(const base::string16& title,
                              const SelectFolderCompletion& on_success,
                              const FileSelectionCanceled& on_failure);

  
  
  virtual void OnSetTargetSurface(gfx::NativeViewId target_surface,
                                  float device_scale) = 0;

  
  
  virtual void OnOpenURL(const base::string16& url) = 0;

  
  
  
  virtual void OnHandleSearchRequest(const base::string16& search_string) = 0;

  
  virtual void OnWindowSizeChanged(uint32 width, uint32 height) = 0;

  void NotifyChannelConnected();

  
  void OnFileSaveAsDone(bool success,
                        const base::FilePath& filename,
                        int filter_index);
  void OnFileOpenDone(bool success, const base::FilePath& filename);
  void OnMultiFileOpenDone(bool success,
                           const std::vector<base::FilePath>& files);
  void OnSelectFolderDone(bool success, const base::FilePath& folder);

  
  
  
  
  class InternalMessageFilter : public IPC::MessageFilter {
   public:
    InternalMessageFilter(MetroViewerProcessHost* owner);

    
    virtual void OnChannelConnected(int32 peer_pid) OVERRIDE;

   private:
    MetroViewerProcessHost* owner_;
    DISALLOW_COPY_AND_ASSIGN(InternalMessageFilter);
  };

  scoped_ptr<IPC::ChannelProxy> channel_;
  scoped_ptr<base::WaitableEvent> channel_connected_event_;
  scoped_refptr<InternalMessageFilter> message_filter_;

  static MetroViewerProcessHost* instance_;

  
  
  OpenFileCompletion file_open_completion_callback_;
  OpenMultipleFilesCompletion multi_file_open_completion_callback_;
  SaveFileCompletion file_saveas_completion_callback_;
  SelectFolderCompletion select_folder_completion_callback_;
  FileSelectionCanceled failure_callback_;

  DISALLOW_COPY_AND_ASSIGN(MetroViewerProcessHost);
};

}  

#endif  
