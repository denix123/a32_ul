// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_BOOT_TIMES_LOADER_H_
#define CHROME_BROWSER_CHROMEOS_BOOT_TIMES_LOADER_H_

#include <set>
#include <string>

#include "base/atomic_sequence_num.h"
#include "base/callback_forward.h"
#include "base/compiler_specific.h"
#include "base/task/cancelable_task_tracker.h"
#include "base/time/time.h"
#include "chromeos/login_event_recorder.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "content/public/browser/render_widget_host.h"

class PrefService;

namespace chromeos {

class BootTimesLoader : public content::NotificationObserver,
                        public LoginEventRecorder::Delegate {
 public:
  BootTimesLoader();
  virtual ~BootTimesLoader();

  static BootTimesLoader* Get();

  
  virtual void AddLoginTimeMarker(const std::string& marker_name,
                                  bool send_to_uma) OVERRIDE;
  virtual void RecordAuthenticationSuccess() OVERRIDE;
  virtual void RecordAuthenticationFailure() OVERRIDE;

  
  
  
  
  void AddLogoutTimeMarker(const std::string& marker_name, bool send_to_uma);

  
  
  
  // Existing stats files will not be overwritten.
  void RecordCurrentStats(const std::string& name);

  
  
  void SaveChromeMainStats();

  
  // file thread. Existing stats files will not be overwritten.
  void RecordChromeMainStats();

  
  
  void RecordLoginAttempted();

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  void LoginDone(bool is_user_new);

  
  
  
  void WriteLogoutTimes();

  
  void set_restart_requested() { restart_requested_ = true; }

  
  void OnChromeProcessStart();

  
  void OnLogoutStarted(PrefService* state);

 private:
  
  
  class Backend : public base::RefCountedThreadSafe<Backend> {
   public:
    Backend() {}

   private:
    friend class base::RefCountedThreadSafe<Backend>;

    ~Backend() {}

    DISALLOW_COPY_AND_ASSIGN(Backend);
  };

  class TimeMarker {
   public:
    TimeMarker(const std::string& name, bool send_to_uma)
        : name_(name),
          time_(base::Time::NowFromSystemTime()),
          send_to_uma_(send_to_uma) {}
    std::string name() const { return name_; }
    base::Time time() const { return time_; }
    bool send_to_uma() const { return send_to_uma_; }

    
    bool operator<(const TimeMarker& other) const {
      return time_ < other.time_;
    }

   private:
    friend class std::vector<TimeMarker>;
    std::string name_;
    base::Time time_;
    bool send_to_uma_;
  };

  class Stats {
   public:
    
    static Stats GetCurrentStats();

    
    std::string SerializeToString() const;

    
    static Stats DeserializeFromString(const std::string& value);

    const std::string& uptime() const { return uptime_; }
    const std::string& disk() const { return disk_; }

    
    
    bool UptimeDouble(double* result) const;

    void RecordStats(const std::string& name) const;
    void RecordStatsWithCallback(const std::string& name,
                                 const base::Closure& callback) const;

   private:
    
    void RecordStatsImpl(const std::string& name) const;

    std::string uptime_;
    std::string disk_;
  };

  static void WriteTimes(const std::string base_name,
                         const std::string uma_name,
                         const std::string uma_prefix,
                         std::vector<TimeMarker> login_times);
  static void AddMarker(std::vector<TimeMarker>* vector, TimeMarker marker);

  
  
  static void ClearLogoutStartedLastPreference();

  
  Stats chrome_main_stats_;
  scoped_refptr<Backend> backend_;

  
  content::NotificationRegistrar registrar_;
  base::AtomicSequenceNumber num_tabs_;
  bool have_registered_;

  std::vector<TimeMarker> login_time_markers_;
  std::vector<TimeMarker> logout_time_markers_;
  std::set<content::RenderWidgetHost*> render_widget_hosts_loading_;

  bool login_done_;

  bool restart_requested_;

  DISALLOW_COPY_AND_ASSIGN(BootTimesLoader);
};

}  

#endif  
