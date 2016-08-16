// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_WIN_SRC_SANDBOX_TYPES_H_
#define SANDBOX_WIN_SRC_SANDBOX_TYPES_H_

namespace sandbox {

enum ResultCode {
  SBOX_ALL_OK = 0,
  
  
  SBOX_ERROR_GENERIC = 1,
  
  SBOX_ERROR_BAD_PARAMS = 2,
  
  SBOX_ERROR_UNSUPPORTED = 3,
  
  SBOX_ERROR_NO_SPACE = 4,
  
  SBOX_ERROR_INVALID_IPC = 5,
  
  SBOX_ERROR_FAILED_IPC = 6,
  
  SBOX_ERROR_NO_HANDLE = 7,
  
  SBOX_ERROR_UNEXPECTED_CALL = 8,
  
  SBOX_ERROR_WAIT_ALREADY_CALLED = 9,
  
  SBOX_ERROR_CHANNEL_ERROR = 10,
  
  SBOX_ERROR_CANNOT_CREATE_DESKTOP = 11,
  
  SBOX_ERROR_CANNOT_CREATE_WINSTATION = 12,
  
  SBOX_ERROR_FAILED_TO_SWITCH_BACK_WINSTATION = 13,
  
  SBOX_ERROR_INVALID_APP_CONTAINER = 14,
  
  SBOX_ERROR_INVALID_CAPABILITY = 15,
  
  SBOX_ERROR_CANNOT_INIT_APPCONTAINER = 16,
  
  SBOX_ERROR_PROC_THREAD_ATTRIBUTES = 17,
  
  SBOX_ERROR_LAST
};

enum TerminationCodes {
  SBOX_FATAL_INTEGRITY = 7006,       
  SBOX_FATAL_DROPTOKEN = 7007,       
  SBOX_FATAL_FLUSHANDLES = 7008,     
  SBOX_FATAL_CACHEDISABLE = 7009,    
  SBOX_FATAL_CLOSEHANDLES = 7010,    
  SBOX_FATAL_MITIGATION = 7011,      
  SBOX_FATAL_MEMORY_EXCEEDED = 7012, 
  SBOX_FATAL_LAST
};

class BrokerServices;
class TargetServices;

struct SandboxInterfaceInfo {
  BrokerServices* broker_services;
  TargetServices* target_services;
};

#if SANDBOX_EXPORTS
#define SANDBOX_INTERCEPT extern "C" __declspec(dllexport)
#else
#define SANDBOX_INTERCEPT extern "C"
#endif

enum InterceptionType {
  INTERCEPTION_INVALID = 0,
  INTERCEPTION_SERVICE_CALL,    
  INTERCEPTION_EAT,
  INTERCEPTION_SIDESTEP,        
  INTERCEPTION_SMART_SIDESTEP,  
  INTERCEPTION_UNLOAD_MODULE,   
  INTERCEPTION_LAST             
};

}  

#endif  