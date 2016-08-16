// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include <string>
#include <vector>

#include "base/strings/string16.h"
#include "content/common/service_worker/service_worker_status_code.h"
#include "content/common/service_worker/service_worker_types.h"
#include "ipc/ipc_message_macros.h"
#include "ipc/ipc_param_traits.h"
#include "third_party/WebKit/public/platform/WebServiceWorkerCacheError.h"
#include "third_party/WebKit/public/platform/WebServiceWorkerError.h"
#include "third_party/WebKit/public/platform/WebServiceWorkerEventResult.h"
#include "url/gurl.h"

#undef IPC_MESSAGE_EXPORT
#define IPC_MESSAGE_EXPORT CONTENT_EXPORT

#define IPC_MESSAGE_START ServiceWorkerMsgStart

IPC_ENUM_TRAITS_MAX_VALUE(blink::WebServiceWorkerError::ErrorType,
                          blink::WebServiceWorkerError::ErrorTypeLast)

IPC_ENUM_TRAITS_MAX_VALUE(blink::WebServiceWorkerEventResult,
                          blink::WebServiceWorkerEventResultLast)

IPC_ENUM_TRAITS_MAX_VALUE(blink::WebServiceWorkerState,
                          blink::WebServiceWorkerStateLast)

IPC_STRUCT_TRAITS_BEGIN(content::ServiceWorkerFetchRequest)
  IPC_STRUCT_TRAITS_MEMBER(url)
  IPC_STRUCT_TRAITS_MEMBER(method)
  IPC_STRUCT_TRAITS_MEMBER(headers)
  IPC_STRUCT_TRAITS_MEMBER(blob_uuid)
  IPC_STRUCT_TRAITS_MEMBER(blob_size)
  IPC_STRUCT_TRAITS_MEMBER(referrer)
  IPC_STRUCT_TRAITS_MEMBER(is_reload)
IPC_STRUCT_TRAITS_END()

IPC_ENUM_TRAITS_MAX_VALUE(content::ServiceWorkerFetchEventResult,
                          content::SERVICE_WORKER_FETCH_EVENT_LAST)

IPC_STRUCT_TRAITS_BEGIN(content::ServiceWorkerResponse)
  IPC_STRUCT_TRAITS_MEMBER(url)
  IPC_STRUCT_TRAITS_MEMBER(status_code)
  IPC_STRUCT_TRAITS_MEMBER(status_text)
  IPC_STRUCT_TRAITS_MEMBER(headers)
  IPC_STRUCT_TRAITS_MEMBER(blob_uuid)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(content::ServiceWorkerCacheQueryParams)
  IPC_STRUCT_TRAITS_MEMBER(ignore_search)
  IPC_STRUCT_TRAITS_MEMBER(ignore_method)
  IPC_STRUCT_TRAITS_MEMBER(ignore_vary)
  IPC_STRUCT_TRAITS_MEMBER(prefix_match)
IPC_STRUCT_TRAITS_END()

IPC_ENUM_TRAITS_MAX_VALUE(content::ServiceWorkerCacheOperationType,
                          content::SERVICE_WORKER_CACHE_OPERATION_TYPE_LAST)

IPC_STRUCT_TRAITS_BEGIN(content::ServiceWorkerBatchOperation)
  IPC_STRUCT_TRAITS_MEMBER(operation_type)
  IPC_STRUCT_TRAITS_MEMBER(request)
  IPC_STRUCT_TRAITS_MEMBER(response)
  IPC_STRUCT_TRAITS_MEMBER(match_params)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(content::ServiceWorkerObjectInfo)
  IPC_STRUCT_TRAITS_MEMBER(handle_id)
  IPC_STRUCT_TRAITS_MEMBER(scope)
  IPC_STRUCT_TRAITS_MEMBER(url)
  IPC_STRUCT_TRAITS_MEMBER(state)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(content::ServiceWorkerRegistrationObjectInfo)
  IPC_STRUCT_TRAITS_MEMBER(handle_id)
  IPC_STRUCT_TRAITS_MEMBER(scope)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(content::ServiceWorkerVersionAttributes)
  IPC_STRUCT_TRAITS_MEMBER(installing)
  IPC_STRUCT_TRAITS_MEMBER(waiting)
  IPC_STRUCT_TRAITS_MEMBER(active)
IPC_STRUCT_TRAITS_END()

IPC_ENUM_TRAITS_MAX_VALUE(
    blink::WebServiceWorkerCacheError,
    blink::WebServiceWorkerCacheErrorLast)


IPC_MESSAGE_CONTROL5(ServiceWorkerHostMsg_RegisterServiceWorker,
                     int ,
                     int ,
                     int ,
                     GURL ,
                     GURL )

IPC_MESSAGE_CONTROL4(ServiceWorkerHostMsg_UnregisterServiceWorker,
                     int ,
                     int ,
                     int ,
                     GURL )

IPC_MESSAGE_CONTROL4(ServiceWorkerHostMsg_GetRegistration,
                     int ,
                     int ,
                     int ,
                     GURL )

IPC_MESSAGE_CONTROL3(ServiceWorkerHostMsg_PostMessageToWorker,
                     int ,
                     base::string16 ,
                     std::vector<int> )

IPC_MESSAGE_CONTROL1(ServiceWorkerHostMsg_ProviderCreated,
                     int )

IPC_MESSAGE_CONTROL1(ServiceWorkerHostMsg_ProviderDestroyed,
                     int )

IPC_MESSAGE_CONTROL1(ServiceWorkerHostMsg_IncrementServiceWorkerRefCount,
                     int )
IPC_MESSAGE_CONTROL1(ServiceWorkerHostMsg_DecrementServiceWorkerRefCount,
                     int )

IPC_MESSAGE_CONTROL1(ServiceWorkerHostMsg_IncrementRegistrationRefCount,
                     int )
IPC_MESSAGE_CONTROL1(ServiceWorkerHostMsg_DecrementRegistrationRefCount,
                     int )

IPC_MESSAGE_CONTROL2(ServiceWorkerHostMsg_SetVersionId,
                     int ,
                     int64 )

IPC_MESSAGE_ROUTED2(ServiceWorkerHostMsg_InstallEventFinished,
                    int ,
                    blink::WebServiceWorkerEventResult)
IPC_MESSAGE_ROUTED2(ServiceWorkerHostMsg_ActivateEventFinished,
                    int ,
                    blink::WebServiceWorkerEventResult)
IPC_MESSAGE_ROUTED3(ServiceWorkerHostMsg_FetchEventFinished,
                    int ,
                    content::ServiceWorkerFetchEventResult,
                    content::ServiceWorkerResponse)
IPC_MESSAGE_ROUTED1(ServiceWorkerHostMsg_SyncEventFinished,
                    int )
IPC_MESSAGE_ROUTED1(ServiceWorkerHostMsg_PushEventFinished,
                    int )

IPC_MESSAGE_ROUTED1(ServiceWorkerHostMsg_GetClientDocuments,
                    int )

IPC_MESSAGE_ROUTED3(ServiceWorkerHostMsg_PostMessageToDocument,
                    int ,
                    base::string16 ,
                    std::vector<int> )

IPC_MESSAGE_ROUTED2(ServiceWorkerHostMsg_CacheStorageGet,
                    int ,
                    base::string16 )

IPC_MESSAGE_ROUTED2(ServiceWorkerHostMsg_CacheStorageHas,
                    int ,
                    base::string16 )

IPC_MESSAGE_ROUTED2(ServiceWorkerHostMsg_CacheStorageCreate,
                    int ,
                    base::string16 )

IPC_MESSAGE_ROUTED2(ServiceWorkerHostMsg_CacheStorageDelete,
                    int ,
                    base::string16 )

IPC_MESSAGE_ROUTED1(ServiceWorkerHostMsg_CacheStorageKeys,
                    int )

IPC_MESSAGE_ROUTED4(ServiceWorkerHostMsg_CacheMatch,
                    int ,
                    int ,
                    content::ServiceWorkerFetchRequest,
                    content::ServiceWorkerCacheQueryParams)

IPC_MESSAGE_ROUTED4(ServiceWorkerHostMsg_CacheMatchAll,
                    int ,
                    int ,
                    content::ServiceWorkerFetchRequest,
                    content::ServiceWorkerCacheQueryParams)

IPC_MESSAGE_ROUTED4(ServiceWorkerHostMsg_CacheKeys,
                    int ,
                    int ,
                    content::ServiceWorkerFetchRequest,
                    content::ServiceWorkerCacheQueryParams);

IPC_MESSAGE_ROUTED3(ServiceWorkerHostMsg_CacheBatch,
                    int ,
                    int ,
                    std::vector<content::ServiceWorkerBatchOperation>);

IPC_MESSAGE_ROUTED1(ServiceWorkerHostMsg_CacheClosed,
                    int );


IPC_MESSAGE_CONTROL4(ServiceWorkerMsg_AssociateRegistration,
                     int ,
                     int ,
                     content::ServiceWorkerRegistrationObjectInfo,
                     content::ServiceWorkerVersionAttributes)
IPC_MESSAGE_CONTROL2(ServiceWorkerMsg_DisassociateRegistration,
                     int ,
                     int )

IPC_MESSAGE_CONTROL4(ServiceWorkerMsg_ServiceWorkerRegistered,
                     int ,
                     int ,
                     content::ServiceWorkerRegistrationObjectInfo,
                     content::ServiceWorkerVersionAttributes)

IPC_MESSAGE_CONTROL3(ServiceWorkerMsg_ServiceWorkerUnregistered,
                     int ,
                     int ,
                     bool )

IPC_MESSAGE_CONTROL4(ServiceWorkerMsg_DidGetRegistration,
                     int ,
                     int ,
                     content::ServiceWorkerRegistrationObjectInfo,
                     content::ServiceWorkerVersionAttributes)

IPC_MESSAGE_CONTROL4(ServiceWorkerMsg_ServiceWorkerRegistrationError,
                     int ,
                     int ,
                     blink::WebServiceWorkerError::ErrorType ,
                     base::string16 )

IPC_MESSAGE_CONTROL4(ServiceWorkerMsg_ServiceWorkerUnregistrationError,
                     int ,
                     int ,
                     blink::WebServiceWorkerError::ErrorType ,
                     base::string16 )

IPC_MESSAGE_CONTROL4(ServiceWorkerMsg_ServiceWorkerGetRegistrationError,
                     int ,
                     int ,
                     blink::WebServiceWorkerError::ErrorType ,
                     base::string16 )

IPC_MESSAGE_CONTROL3(ServiceWorkerMsg_ServiceWorkerStateChanged,
                     int ,
                     int ,
                     blink::WebServiceWorkerState)

IPC_MESSAGE_CONTROL5(ServiceWorkerMsg_SetVersionAttributes,
                     int ,
                     int ,
                     int ,
                     int ,
                     content::ServiceWorkerVersionAttributes)

IPC_MESSAGE_CONTROL2(ServiceWorkerMsg_UpdateFound,
                     int ,
                     content::ServiceWorkerRegistrationObjectInfo)

IPC_MESSAGE_CONTROL3(ServiceWorkerMsg_SetControllerServiceWorker,
                     int ,
                     int ,
                     content::ServiceWorkerObjectInfo)

IPC_MESSAGE_CONTROL5(ServiceWorkerMsg_MessageToDocument,
                     int ,
                     int ,
                     base::string16 ,
                     std::vector<int> ,
                     std::vector<int> )

IPC_MESSAGE_CONTROL2(ServiceWorkerMsg_InstallEvent,
                     int ,
                     int )
IPC_MESSAGE_CONTROL1(ServiceWorkerMsg_ActivateEvent,
                     int )
IPC_MESSAGE_CONTROL2(ServiceWorkerMsg_FetchEvent,
                     int ,
                     content::ServiceWorkerFetchRequest)
IPC_MESSAGE_CONTROL1(ServiceWorkerMsg_SyncEvent,
                     int )
IPC_MESSAGE_CONTROL2(ServiceWorkerMsg_PushEvent,
                     int ,
                     std::string )
IPC_MESSAGE_CONTROL3(ServiceWorkerMsg_MessageToWorker,
                     base::string16 ,
                     std::vector<int> ,
                     std::vector<int> )

IPC_MESSAGE_CONTROL2(ServiceWorkerMsg_DidGetClientDocuments,
                     int ,
                     std::vector<int> )

IPC_MESSAGE_CONTROL2(ServiceWorkerMsg_CacheStorageGetSuccess,
                     int ,
                     int )
IPC_MESSAGE_CONTROL1(ServiceWorkerMsg_CacheStorageHasSuccess,
                     int )
IPC_MESSAGE_CONTROL2(ServiceWorkerMsg_CacheStorageCreateSuccess,
                     int ,
                     int )
IPC_MESSAGE_CONTROL1(ServiceWorkerMsg_CacheStorageDeleteSuccess,
                     int )
IPC_MESSAGE_CONTROL2(ServiceWorkerMsg_CacheStorageKeysSuccess,
                     int ,
                     std::vector<base::string16> )

IPC_MESSAGE_CONTROL2(ServiceWorkerMsg_CacheStorageGetError,
                     int ,
                     blink::WebServiceWorkerCacheError )
IPC_MESSAGE_CONTROL2(ServiceWorkerMsg_CacheStorageHasError,
                     int ,
                     blink::WebServiceWorkerCacheError )
IPC_MESSAGE_CONTROL2(ServiceWorkerMsg_CacheStorageCreateError,
                     int ,
                     blink::WebServiceWorkerCacheError )
IPC_MESSAGE_CONTROL2(ServiceWorkerMsg_CacheStorageDeleteError,
                     int ,
                     blink::WebServiceWorkerCacheError )
IPC_MESSAGE_CONTROL2(ServiceWorkerMsg_CacheStorageKeysError,
                     int ,
                     blink::WebServiceWorkerCacheError )

IPC_MESSAGE_CONTROL2(ServiceWorkerMsg_CacheMatchSuccess,
                     int ,
                     content::ServiceWorkerResponse)
IPC_MESSAGE_CONTROL2(ServiceWorkerMsg_CacheMatchAllSuccess,
                     int ,
                     std::vector<content::ServiceWorkerResponse>)
IPC_MESSAGE_CONTROL2(ServiceWorkerMsg_CacheKeysSuccess,
                     int ,
                     std::vector<content::ServiceWorkerFetchRequest>)
IPC_MESSAGE_CONTROL2(ServiceWorkerMsg_CacheBatchSuccess,
                     int ,
                     std::vector<content::ServiceWorkerResponse>)

IPC_MESSAGE_CONTROL2(ServiceWorkerMsg_CacheMatchError,
                     int ,
                     blink::WebServiceWorkerCacheError)
IPC_MESSAGE_CONTROL2(ServiceWorkerMsg_CacheMatchAllError,
                     int ,
                     blink::WebServiceWorkerCacheError)
IPC_MESSAGE_CONTROL2(ServiceWorkerMsg_CacheKeysError,
                     int ,
                     blink::WebServiceWorkerCacheError)
IPC_MESSAGE_CONTROL2(ServiceWorkerMsg_CacheBatchError,
                     int ,
                     blink::WebServiceWorkerCacheError)
