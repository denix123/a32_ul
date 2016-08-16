// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_BROWSER_MAIN_LOOP_H_
#define CONTENT_BROWSER_BROWSER_MAIN_LOOP_H_

#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/timer/timer.h"
#include "content/browser/browser_process_sub_thread.h"
#include "content/public/browser/browser_main_runner.h"

namespace base {
class CommandLine;
class FilePath;
class HighResolutionTimerManager;
class MessageLoop;
class PowerMonitor;
class SystemMonitor;
namespace debug {
class TraceMemoryController;
class TraceEventSystemStatsMonitor;
}  
}  

namespace media {
class AudioManager;
class MidiManager;
class UserInputMonitor;
}  

namespace net {
class NetworkChangeNotifier;
}  

namespace content {
class BrowserMainParts;
class BrowserOnlineStateObserver;
class BrowserShutdownImpl;
class BrowserThreadImpl;
class MediaStreamManager;
class ResourceDispatcherHostImpl;
class SpeechRecognitionManagerImpl;
class StartupTaskRunner;
class TimeZoneMonitor;
struct MainFunctionParams;

#if defined(OS_LINUX)
class DeviceMonitorLinux;
#elif defined(OS_MACOSX)
class DeviceMonitorMac;
#elif defined(OS_WIN)
class SystemMessageWindowWin;
#endif

class CONTENT_EXPORT BrowserMainLoop {
 public:
  
  
  static BrowserMainLoop* GetInstance();

  explicit BrowserMainLoop(const MainFunctionParams& parameters);
  virtual ~BrowserMainLoop();

  void Init();

  void EarlyInitialization();
  
  
  bool InitializeToolkit();
  void MainMessageLoopStart();

  
  
  
  
  void CreateStartupTasks();

  
  void RunMainMessageLoopParts();

  
  
  void ShutdownThreadsAndCleanUp();

  int GetResultCode() const { return result_code_; }

  media::AudioManager* audio_manager() const { return audio_manager_.get(); }
  MediaStreamManager* media_stream_manager() const {
    return media_stream_manager_.get();
  }
  media::UserInputMonitor* user_input_monitor() const {
    return user_input_monitor_.get();
  }
  media::MidiManager* midi_manager() const { return midi_manager_.get(); }
  base::Thread* indexed_db_thread() const { return indexed_db_thread_.get(); }

  bool is_tracing_startup() const { return is_tracing_startup_; }

  const base::FilePath& startup_trace_file() const {
    return startup_trace_file_;
  }

  void StopStartupTracingTimer();

#if defined(OS_MACOSX) && !defined(OS_IOS)
  DeviceMonitorMac* device_monitor_mac() const {
    return device_monitor_mac_.get();
  }
#endif

 private:
  class MemoryObserver;
  
  friend class BrowserShutdownImpl;

  void InitializeMainThread();

  
  int PreCreateThreads();

  
  int CreateThreads();

  
  int BrowserThreadsStarted();

  int PreMainMessageLoopRun();

  void MainMessageLoopRun();

  base::FilePath GetStartupTraceFileName(
      const base::CommandLine& command_line) const;
  void InitStartupTracing(const base::CommandLine& command_line);
  void EndStartupTracing();

  
  const MainFunctionParams& parameters_;
  const base::CommandLine& parsed_command_line_;
  int result_code_;
  
  bool created_threads_;

  
  scoped_ptr<base::MessageLoop> main_message_loop_;
  scoped_ptr<base::SystemMonitor> system_monitor_;
  scoped_ptr<base::PowerMonitor> power_monitor_;
  scoped_ptr<base::HighResolutionTimerManager> hi_res_timer_manager_;
  scoped_ptr<net::NetworkChangeNotifier> network_change_notifier_;
  
  scoped_ptr<media::UserInputMonitor> user_input_monitor_;
  scoped_ptr<media::AudioManager> audio_manager_;
  scoped_ptr<media::MidiManager> midi_manager_;
  scoped_ptr<MediaStreamManager> media_stream_manager_;
  
  scoped_ptr<BrowserOnlineStateObserver> online_state_observer_;
#if defined(OS_WIN)
  scoped_ptr<SystemMessageWindowWin> system_message_window_;
#elif defined(USE_UDEV)
  scoped_ptr<DeviceMonitorLinux> device_monitor_linux_;
#elif defined(OS_MACOSX) && !defined(OS_IOS)
  scoped_ptr<DeviceMonitorMac> device_monitor_mac_;
#endif
  
  scoped_ptr<StartupTaskRunner> startup_task_runner_;

  
  
  scoped_ptr<BrowserMainParts> parts_;

  
  
  scoped_ptr<BrowserThreadImpl> main_thread_;

  
  scoped_ptr<ResourceDispatcherHostImpl> resource_dispatcher_host_;
  scoped_ptr<SpeechRecognitionManagerImpl> speech_recognition_manager_;
  scoped_ptr<TimeZoneMonitor> time_zone_monitor_;

  
  scoped_ptr<BrowserProcessSubThread> db_thread_;
  scoped_ptr<BrowserProcessSubThread> file_user_blocking_thread_;
  scoped_ptr<BrowserProcessSubThread> file_thread_;
  scoped_ptr<BrowserProcessSubThread> process_launcher_thread_;
  scoped_ptr<BrowserProcessSubThread> cache_thread_;
  scoped_ptr<BrowserProcessSubThread> io_thread_;
  scoped_ptr<base::Thread> indexed_db_thread_;
  scoped_ptr<MemoryObserver> memory_observer_;
  scoped_ptr<base::debug::TraceMemoryController> trace_memory_controller_;
  scoped_ptr<base::debug::TraceEventSystemStatsMonitor> system_stats_monitor_;

  bool is_tracing_startup_;
  base::FilePath startup_trace_file_;

  
  base::OneShotTimer<BrowserMainLoop> startup_trace_timer_;

  DISALLOW_COPY_AND_ASSIGN(BrowserMainLoop);
};

}  

#endif  
