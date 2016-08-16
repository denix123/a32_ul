// Copyright 2011 Google Inc. All Rights Reserved.
// Use of this source code is governed by a BSD-style license

#ifndef WEBP_UTILS_THREAD_H_
#define WEBP_UTILS_THREAD_H_

#ifdef HAVE_CONFIG_H
#include "../webp/config.h"
#endif

#include "../webp/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  NOT_OK = 0,   
  OK,           
  WORK          
} WebPWorkerStatus;

typedef int (*WebPWorkerHook)(void*, void*);

typedef struct WebPWorkerImpl WebPWorkerImpl;

typedef struct {
  WebPWorkerImpl* impl_;
  WebPWorkerStatus status_;
  WebPWorkerHook hook;    
  void* data1;            
  void* data2;            
  int had_error;          
} WebPWorker;

typedef struct {
  
  void (*Init)(WebPWorker* const worker);
  
  
  int (*Reset)(WebPWorker* const worker);
  
  
  int (*Sync)(WebPWorker* const worker);
  
  
  
  void (*Launch)(WebPWorker* const worker);
  
  
  
  
  void (*Execute)(WebPWorker* const worker);
  
  
  void (*End)(WebPWorker* const worker);
} WebPWorkerInterface;

WEBP_EXTERN(int) WebPSetWorkerInterface(
    const WebPWorkerInterface* const interface);

WEBP_EXTERN(const WebPWorkerInterface*) WebPGetWorkerInterface(void);


#ifdef __cplusplus
}    
#endif

#endif  
