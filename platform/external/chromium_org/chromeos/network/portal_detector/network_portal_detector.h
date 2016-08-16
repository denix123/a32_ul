// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_NETWORK_PORTAL_DETECTOR_NETWORK_PORTAL_DETECTOR_H_
#define CHROMEOS_NETWORK_PORTAL_DETECTOR_NETWORK_PORTAL_DETECTOR_H_

#include "base/basictypes.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/network/portal_detector/network_portal_detector_strategy.h"
#include "net/url_request/url_fetcher.h"

namespace chromeos {

class NetworkState;

class CHROMEOS_EXPORT NetworkPortalDetector {
 public:
  enum CaptivePortalStatus {
    CAPTIVE_PORTAL_STATUS_UNKNOWN  = 0,
    CAPTIVE_PORTAL_STATUS_OFFLINE  = 1,
    CAPTIVE_PORTAL_STATUS_ONLINE   = 2,
    CAPTIVE_PORTAL_STATUS_PORTAL   = 3,
    CAPTIVE_PORTAL_STATUS_PROXY_AUTH_REQUIRED = 4,
    CAPTIVE_PORTAL_STATUS_COUNT
  };

  struct CaptivePortalState {
    CaptivePortalState()
        : status(CAPTIVE_PORTAL_STATUS_UNKNOWN),
          response_code(net::URLFetcher::RESPONSE_CODE_INVALID) {
    }

    bool operator==(const CaptivePortalState& o) const {
      return status == o.status && response_code == o.response_code;
    }

    CaptivePortalStatus status;
    int response_code;
    base::TimeTicks time;
  };

  class Observer {
   public:
    
    
    
    
    
    
    
    virtual void OnPortalDetectionCompleted(
        const NetworkState* network,
        const CaptivePortalState& state) = 0;

   protected:
    virtual ~Observer() {}
  };

  
  virtual void AddObserver(Observer* observer) = 0;

  
  
  
  
  
  
  
  
  
  
  virtual void AddAndFireObserver(Observer* observer) = 0;

  
  virtual void RemoveObserver(Observer* observer) = 0;

  
  virtual CaptivePortalState GetCaptivePortalState(
      const std::string& service_path) = 0;

  
  virtual bool IsEnabled() = 0;

  
  
  
  
  
  virtual void Enable(bool start_detection) = 0;

  
  
  
  virtual bool StartDetectionIfIdle() = 0;

  
  
  virtual void SetStrategy(PortalDetectorStrategy::StrategyId id) = 0;

  
  
  
  static void InitializeForTesting(
      NetworkPortalDetector* network_portal_detector);

  
  
  static bool IsInitialized();

  
  static void Shutdown();

  
  
  
  static NetworkPortalDetector* Get();

  
  static std::string CaptivePortalStatusString(CaptivePortalStatus status);

 protected:
  NetworkPortalDetector() {}
  virtual ~NetworkPortalDetector() {}

  static bool set_for_testing() { return set_for_testing_; }
  static NetworkPortalDetector* network_portal_detector() {
    return network_portal_detector_;
  }
  static void set_network_portal_detector(
      NetworkPortalDetector* network_portal_detector) {
    network_portal_detector_ = network_portal_detector;
  }

 private:
  static bool set_for_testing_;
  static NetworkPortalDetector* network_portal_detector_;

  DISALLOW_COPY_AND_ASSIGN(NetworkPortalDetector);
};

class CHROMEOS_EXPORT NetworkPortalDetectorStubImpl
    : public NetworkPortalDetector {
 public:
  NetworkPortalDetectorStubImpl();
  virtual ~NetworkPortalDetectorStubImpl();

 protected:
  
  virtual void AddObserver(Observer* observer) OVERRIDE;
  virtual void AddAndFireObserver(Observer* observer) OVERRIDE;
  virtual void RemoveObserver(Observer* observer) OVERRIDE;
  virtual CaptivePortalState GetCaptivePortalState(
      const std::string& service_path) OVERRIDE;
  virtual bool IsEnabled() OVERRIDE;
  virtual void Enable(bool start_detection) OVERRIDE;
  virtual bool StartDetectionIfIdle() OVERRIDE;
  virtual void SetStrategy(PortalDetectorStrategy::StrategyId id) OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(NetworkPortalDetectorStubImpl);
};

}  

#endif  
