// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_ALARMS_ALARM_MANAGER_H__
#define CHROME_BROWSER_EXTENSIONS_API_ALARMS_ALARM_MANAGER_H__

#include <map>
#include <queue>
#include <string>
#include <vector>

#include "base/callback.h"
#include "base/gtest_prod_util.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observer.h"
#include "base/timer/timer.h"
#include "chrome/common/extensions/api/alarms.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"
#include "extensions/browser/extension_registry_observer.h"

namespace base {
class Clock;
}  

namespace content {
class BrowserContext;
}  

namespace extensions {
class ExtensionAlarmsSchedulingTest;
class ExtensionRegistry;

struct Alarm {
  Alarm();
  Alarm(const std::string& name,
        const api::alarms::AlarmCreateInfo& create_info,
        base::TimeDelta min_granularity,
        base::Time now);
  ~Alarm();

  linked_ptr<api::alarms::Alarm> js_alarm;
  
  
  
  
  
  base::TimeDelta granularity;
  
  
  base::TimeDelta minimum_granularity;
};

class AlarmManager : public BrowserContextKeyedAPI,
                     public ExtensionRegistryObserver,
                     public base::SupportsWeakPtr<AlarmManager> {
 public:
  typedef std::vector<Alarm> AlarmList;

  class Delegate {
   public:
    virtual ~Delegate() {}
    
    virtual void OnAlarm(const std::string& extension_id,
                         const Alarm& alarm) = 0;
  };

  explicit AlarmManager(content::BrowserContext* context);
  virtual ~AlarmManager();

  
  void set_delegate(Delegate* delegate) { delegate_.reset(delegate); }

  typedef base::Callback<void()> AddAlarmCallback;
  
  
  void AddAlarm(const std::string& extension_id,
                const Alarm& alarm,
                const AddAlarmCallback& callback);

  typedef base::Callback<void(Alarm*)> GetAlarmCallback;
  
  
  void GetAlarm(const std::string& extension_id,
                const std::string& name,
                const GetAlarmCallback& callback);

  typedef base::Callback<void(const AlarmList*)> GetAllAlarmsCallback;
  
  
  void GetAllAlarms(
      const std::string& extension_id, const GetAllAlarmsCallback& callback);

  typedef base::Callback<void(bool)> RemoveAlarmCallback;
  
  
  void RemoveAlarm(const std::string& extension_id,
                   const std::string& name,
                   const RemoveAlarmCallback& callback);

  typedef base::Callback<void()> RemoveAllAlarmsCallback;
  
  
  void RemoveAllAlarms(
      const std::string& extension_id, const RemoveAllAlarmsCallback& callback);

  
  void SetClockForTesting(base::Clock* clock);

  
  static BrowserContextKeyedAPIFactory<AlarmManager>* GetFactoryInstance();

  
  static AlarmManager* Get(content::BrowserContext* browser_context);

 private:
  friend void RunScheduleNextPoll(AlarmManager*);
  friend class ExtensionAlarmsSchedulingTest;
  FRIEND_TEST_ALL_PREFIXES(ExtensionAlarmsSchedulingTest, PollScheduling);
  FRIEND_TEST_ALL_PREFIXES(ExtensionAlarmsSchedulingTest,
                           ReleasedExtensionPollsInfrequently);
  FRIEND_TEST_ALL_PREFIXES(ExtensionAlarmsSchedulingTest, TimerRunning);
  FRIEND_TEST_ALL_PREFIXES(ExtensionAlarmsSchedulingTest, MinimumGranularity);
  FRIEND_TEST_ALL_PREFIXES(ExtensionAlarmsSchedulingTest,
                           DifferentMinimumGranularities);
  FRIEND_TEST_ALL_PREFIXES(ExtensionAlarmsSchedulingTest,
                           RepeatingAlarmsScheduledPredictably);
  friend class BrowserContextKeyedAPIFactory<AlarmManager>;

  typedef std::string ExtensionId;
  typedef std::map<ExtensionId, AlarmList> AlarmMap;

  typedef base::Callback<void(const std::string&)> ReadyAction;
  typedef std::queue<ReadyAction> ReadyQueue;
  typedef std::map<ExtensionId, ReadyQueue> ReadyMap;

  
  
  typedef std::pair<AlarmMap::iterator, AlarmList::iterator> AlarmIterator;

  
  void AddAlarmWhenReady(const Alarm& alarm,
                         const AddAlarmCallback& callback,
                         const std::string& extension_id);

  
  void GetAlarmWhenReady(const std::string& name,
                         const GetAlarmCallback& callback,
                         const std::string& extension_id);

  
  void GetAllAlarmsWhenReady(const GetAllAlarmsCallback& callback,
                             const std::string& extension_id);

  
  void RemoveAlarmWhenReady(const std::string& name,
                            const RemoveAlarmCallback& callback,
                            const std::string& extension_id);

  
  void RemoveAllAlarmsWhenReady(
      const RemoveAllAlarmsCallback& callback, const std::string& extension_id);

  
  
  
  AlarmIterator GetAlarmIterator(const std::string& extension_id,
                                 const std::string& name);

  
  
  void RemoveAlarmIterator(const AlarmIterator& iter);

  
  void OnAlarm(AlarmIterator iter);

  
  void AddAlarmImpl(const std::string& extension_id,
                    const Alarm& alarm);

  
  void WriteToStorage(const std::string& extension_id);
  void ReadFromStorage(const std::string& extension_id,
                       scoped_ptr<base::Value> value);

  
  
  void SetNextPollTime(const base::Time& time);

  
  
  void ScheduleNextPoll();

  
  
  void PollAlarms();

  
  
  void RunWhenReady(const std::string& extension_id, const ReadyAction& action);

  
  virtual void OnExtensionLoaded(content::BrowserContext* browser_context,
                                 const Extension* extension) OVERRIDE;
  virtual void OnExtensionUninstalled(
      content::BrowserContext* browser_context,
      const Extension* extension,
      extensions::UninstallReason reason) OVERRIDE;

  
  static const char* service_name() {
    return "AlarmManager";
  }
  static const bool kServiceHasOwnInstanceInIncognito = true;

  content::BrowserContext* const browser_context_;
  scoped_ptr<base::Clock> clock_;
  scoped_ptr<Delegate> delegate_;

  
  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver>
      extension_registry_observer_;

  
  base::OneShotTimer<AlarmManager> timer_;

  
  
  AlarmMap alarms_;

  
  
  ReadyMap ready_actions_;

  
  base::Time last_poll_time_;

  
  base::Time next_poll_time_;

  DISALLOW_COPY_AND_ASSIGN(AlarmManager);
};

}  

#endif  
