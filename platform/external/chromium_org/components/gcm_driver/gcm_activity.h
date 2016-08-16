// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_GCM_DRIVER_GCM_ACTIVITY_H_
#define COMPONENTS_GCM_DRIVER_GCM_ACTIVITY_H_

#include <string>
#include <vector>

#include "base/time/time.h"

namespace gcm {

struct Activity {
  Activity();
  virtual ~Activity();

  base::Time time;
  std::string event;    
  std::string details;  
};

struct ConnectionActivity : Activity {
  ConnectionActivity();
  virtual ~ConnectionActivity();
};

struct CheckinActivity : Activity {
  CheckinActivity();
  virtual ~CheckinActivity();
};

struct RegistrationActivity : Activity {
  RegistrationActivity();
  virtual ~RegistrationActivity();

  std::string app_id;
  std::string sender_ids;  
};

struct ReceivingActivity : Activity {
  ReceivingActivity();
  virtual ~ReceivingActivity();

  std::string app_id;
  std::string from;
  int message_byte_size;
};

struct SendingActivity : Activity {
  SendingActivity();
  virtual ~SendingActivity();

  std::string app_id;
  std::string receiver_id;
  std::string message_id;
};

struct RecordedActivities {
  RecordedActivities();
  virtual ~RecordedActivities();

  std::vector<CheckinActivity> checkin_activities;
  std::vector<ConnectionActivity> connection_activities;
  std::vector<RegistrationActivity> registration_activities;
  std::vector<ReceivingActivity> receiving_activities;
  std::vector<SendingActivity> sending_activities;
};

}  

#endif  
