// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_DBUS_FAKE_UPDATE_ENGINE_CLIENT_H_
#define CHROMEOS_DBUS_FAKE_UPDATE_ENGINE_CLIENT_H_

#include <queue>
#include <string>

#include "chromeos/dbus/update_engine_client.h"

namespace chromeos {

class FakeUpdateEngineClient : public UpdateEngineClient {
 public:
  FakeUpdateEngineClient();
  virtual ~FakeUpdateEngineClient();

  
  virtual void Init(dbus::Bus* bus) OVERRIDE;
  virtual void AddObserver(Observer* observer) OVERRIDE;
  virtual void RemoveObserver(Observer* observer) OVERRIDE;
  virtual bool HasObserver(Observer* observer) OVERRIDE;
  virtual void RequestUpdateCheck(const UpdateCheckCallback& callback) OVERRIDE;
  virtual void RebootAfterUpdate() OVERRIDE;
  virtual void Rollback() OVERRIDE;
  virtual void CanRollbackCheck(
      const RollbackCheckCallback& callback) OVERRIDE;
  virtual Status GetLastStatus() OVERRIDE;
  virtual void SetChannel(const std::string& target_channel,
                          bool is_powerwash_allowed) OVERRIDE;
  virtual void GetChannel(bool get_current_channel,
                          const GetChannelCallback& callback) OVERRIDE;

  
  
  
  void PushLastStatus(const UpdateEngineClient::Status& status) {
    status_queue_.push(status);
  }

  
  void NotifyObserversThatStatusChanged(
      const UpdateEngineClient::Status& status);

  
  
  void set_default_status(const UpdateEngineClient::Status& status);

  
  void set_update_check_result(
      const UpdateEngineClient::UpdateCheckResult& result);

  void set_can_rollback_check_result(bool result) {
      can_rollback_stub_result_ = result;
  }

  
  int reboot_after_update_call_count() const {
      return reboot_after_update_call_count_;
  }

  
  int request_update_check_call_count() const {
    return request_update_check_call_count_;
  }

  
  int rollback_call_count() const { return rollback_call_count_; }

  
  int can_rollback_call_count() const { return can_rollback_call_count_; }

 private:
  ObserverList<Observer> observers_;
  std::queue<UpdateEngineClient::Status> status_queue_;
  UpdateEngineClient::Status default_status_;
  UpdateEngineClient::UpdateCheckResult update_check_result_;
  bool can_rollback_stub_result_;
  int reboot_after_update_call_count_;
  int request_update_check_call_count_;
  int rollback_call_count_;
  int can_rollback_call_count_;
};

}  

#endif  
