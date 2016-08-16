// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_REQUEST_MANAGER_H_
#define CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_REQUEST_MANAGER_H_

#include <map>
#include <string>
#include <vector>

#include "base/callback.h"
#include "base/files/file.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "chrome/browser/chromeos/file_system_provider/notification_manager_interface.h"
#include "chrome/browser/chromeos/file_system_provider/provided_file_system_info.h"
#include "chrome/browser/chromeos/file_system_provider/request_value.h"

namespace chromeos {
namespace file_system_provider {

enum RequestType {
  REQUEST_UNMOUNT,
  GET_METADATA,
  READ_DIRECTORY,
  OPEN_FILE,
  CLOSE_FILE,
  READ_FILE,
  CREATE_DIRECTORY,
  DELETE_ENTRY,
  CREATE_FILE,
  COPY_ENTRY,
  MOVE_ENTRY,
  TRUNCATE,
  WRITE_FILE,
  ABORT,
  TESTING
};

std::string RequestTypeToString(RequestType type);

class RequestManager {
 public:
  
  
  class HandlerInterface {
   public:
    virtual ~HandlerInterface() {}

    
    
    virtual bool Execute(int request_id) = 0;

    
    
    
    virtual void OnSuccess(int request_id,
                           scoped_ptr<RequestValue> result,
                           bool has_more) = 0;

    
    
    
    virtual void OnError(int request_id,
                         scoped_ptr<RequestValue> result,
                         base::File::Error error) = 0;
  };

  
  class Observer {
   public:
    virtual ~Observer() {}

    
    virtual void OnRequestCreated(int request_id, RequestType type) = 0;

    
    virtual void OnRequestDestroyed(int request_id) = 0;

    
    virtual void OnRequestExecuted(int request_id) = 0;

    
    virtual void OnRequestFulfilled(int request_id,
                                    const RequestValue& result,
                                    bool has_more) = 0;

    
    virtual void OnRequestRejected(int request_id,
                                   const RequestValue& result,
                                   base::File::Error error) = 0;

    
    virtual void OnRequestTimeouted(int request_id) = 0;
  };

  explicit RequestManager(NotificationManagerInterface* notification_manager);
  virtual ~RequestManager();

  
  
  
  int CreateRequest(RequestType type, scoped_ptr<HandlerInterface> handler);

  
  
  
  bool FulfillRequest(int request_id,
                      scoped_ptr<RequestValue> response,
                      bool has_more);

  
  
  bool RejectRequest(int request_id,
                     scoped_ptr<RequestValue> response,
                     base::File::Error error);

  
  
  void SetTimeoutForTesting(const base::TimeDelta& timeout);

  
  std::vector<int> GetActiveRequestIds() const;

  
  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

 private:
  struct Request {
    Request();
    ~Request();

    
    base::OneShotTimer<RequestManager> timeout_timer;

    
    scoped_ptr<HandlerInterface> handler;

   private:
    DISALLOW_COPY_AND_ASSIGN(Request);
  };

  typedef std::map<int, Request*> RequestMap;

  
  void DestroyRequest(int request_id);

  
  void OnRequestTimeout(int request_id);

  
  
  void OnUnresponsiveNotificationResult(
      int request_id,
      NotificationManagerInterface::NotificationResult result);

  
  void ResetTimer(int request_id);

  RequestMap requests_;
  NotificationManagerInterface* notification_manager_;  
  int next_id_;
  base::TimeDelta timeout_;
  ObserverList<Observer> observers_;
  base::WeakPtrFactory<RequestManager> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(RequestManager);
};

}  
}  

#endif  
