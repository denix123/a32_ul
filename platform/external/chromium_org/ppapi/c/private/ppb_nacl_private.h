/* Copyright (c) 2012 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef PPAPI_C_PRIVATE_PPB_NACL_PRIVATE_H_
#define PPAPI_C_PRIVATE_PPB_NACL_PRIVATE_H_

#include "ppapi/c/pp_bool.h"
#include "ppapi/c/pp_completion_callback.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/c/pp_macros.h"
#include "ppapi/c/pp_stdint.h"
#include "ppapi/c/pp_var.h"
#include "ppapi/c/private/ppp_pexe_stream_handler.h"

#define PPB_NACL_PRIVATE_INTERFACE_1_0 "PPB_NaCl_Private;1.0"
#define PPB_NACL_PRIVATE_INTERFACE PPB_NACL_PRIVATE_INTERFACE_1_0



#include "ppapi/c/private/pp_file_handle.h"
#include "ppapi/c/private/ppb_instance_private.h"

typedef enum {
  PP_NACL_ERROR_LOAD_SUCCESS = 0,
  PP_NACL_ERROR_LOAD_ABORTED = 1,
  PP_NACL_ERROR_UNKNOWN = 2,
  PP_NACL_ERROR_MANIFEST_RESOLVE_URL = 3,
  PP_NACL_ERROR_MANIFEST_LOAD_URL = 4,
  PP_NACL_ERROR_MANIFEST_STAT = 5,
  PP_NACL_ERROR_MANIFEST_TOO_LARGE = 6,
  PP_NACL_ERROR_MANIFEST_OPEN = 7,
  PP_NACL_ERROR_MANIFEST_MEMORY_ALLOC = 8,
  PP_NACL_ERROR_MANIFEST_READ = 9,
  PP_NACL_ERROR_MANIFEST_PARSING = 10,
  PP_NACL_ERROR_MANIFEST_SCHEMA_VALIDATE = 11,
  PP_NACL_ERROR_MANIFEST_GET_NEXE_URL = 12,
  PP_NACL_ERROR_NEXE_LOAD_URL = 13,
  PP_NACL_ERROR_NEXE_ORIGIN_PROTOCOL = 14,
  PP_NACL_ERROR_NEXE_FH_DUP = 15,
  PP_NACL_ERROR_NEXE_STAT = 16,
  PP_NACL_ERROR_ELF_CHECK_IO = 17,
  PP_NACL_ERROR_ELF_CHECK_FAIL = 18,
  PP_NACL_ERROR_SEL_LDR_INIT = 19,
  PP_NACL_ERROR_SEL_LDR_CREATE_LAUNCHER = 20,
  PP_NACL_ERROR_SEL_LDR_FD = 21,
  PP_NACL_ERROR_SEL_LDR_LAUNCH = 22,
  PP_NACL_ERROR_SEL_LDR_SEND_NEXE = 24,
  PP_NACL_ERROR_SEL_LDR_HANDLE_PASSING = 25,
  PP_NACL_ERROR_SEL_LDR_START_MODULE = 26,
  PP_NACL_ERROR_SEL_LDR_START_STATUS = 27,
  PP_NACL_ERROR_SRPC_CONNECTION_FAIL = 28,
  PP_NACL_ERROR_START_PROXY_CHECK_PPP = 29,
  PP_NACL_ERROR_START_PROXY_ALLOC = 30,
  PP_NACL_ERROR_START_PROXY_MODULE = 31,
  PP_NACL_ERROR_START_PROXY_INSTANCE = 32,
  PP_NACL_ERROR_SEL_LDR_COMMUNICATION_CMD_CHANNEL = 33,
  PP_NACL_ERROR_SEL_LDR_COMMUNICATION_REV_SETUP = 34,
  PP_NACL_ERROR_SEL_LDR_COMMUNICATION_WRAPPER = 35,
  PP_NACL_ERROR_SEL_LDR_COMMUNICATION_REV_SERVICE = 36,
  PP_NACL_ERROR_START_PROXY_CRASH = 37,
  PP_NACL_ERROR_MANIFEST_PROGRAM_MISSING_ARCH = 38,
  PP_NACL_ERROR_PNACL_CACHE_OPEN_INPROGRESS = 39,
  PP_NACL_ERROR_PNACL_CACHE_OPEN_NOACCESS = 40,
  PP_NACL_ERROR_PNACL_CACHE_OPEN_NOQUOTA = 41,
  PP_NACL_ERROR_PNACL_CACHE_OPEN_NOSPACE = 42,
  PP_NACL_ERROR_PNACL_CACHE_OPEN_OTHER = 43,
  PP_NACL_ERROR_PNACL_CACHE_DIRECTORY_CREATE = 44,
  PP_NACL_ERROR_PNACL_CACHE_FILEOPEN_NOACCESS = 45,
  PP_NACL_ERROR_PNACL_CACHE_FILEOPEN_NOQUOTA = 46,
  PP_NACL_ERROR_PNACL_CACHE_FILEOPEN_NOSPACE = 47,
  PP_NACL_ERROR_PNACL_CACHE_FILEOPEN_NOTAFILE = 48,
  PP_NACL_ERROR_PNACL_CACHE_FILEOPEN_OTHER = 49,
  PP_NACL_ERROR_PNACL_CACHE_FETCH_NOACCESS = 50,
  PP_NACL_ERROR_PNACL_CACHE_FETCH_NOTFOUND = 51,
  PP_NACL_ERROR_PNACL_CACHE_FETCH_OTHER = 52,
  PP_NACL_ERROR_PNACL_CACHE_FINALIZE_COPY_NOQUOTA = 53,
  PP_NACL_ERROR_PNACL_CACHE_FINALIZE_COPY_NOSPACE = 54,
  PP_NACL_ERROR_PNACL_CACHE_FINALIZE_COPY_OTHER = 55,
  PP_NACL_ERROR_PNACL_CACHE_FINALIZE_RENAME_NOACCESS = 56,
  PP_NACL_ERROR_PNACL_CACHE_FINALIZE_RENAME_OTHER = 57,
  PP_NACL_ERROR_PNACL_RESOURCE_FETCH = 58,
  PP_NACL_ERROR_PNACL_PEXE_FETCH_ABORTED = 59,
  PP_NACL_ERROR_PNACL_PEXE_FETCH_NOACCESS = 60,
  PP_NACL_ERROR_PNACL_PEXE_FETCH_OTHER = 61,
  PP_NACL_ERROR_PNACL_THREAD_CREATE = 62,
  PP_NACL_ERROR_PNACL_LLC_SETUP = 63,
  PP_NACL_ERROR_PNACL_LD_SETUP = 64,
  PP_NACL_ERROR_PNACL_LLC_INTERNAL = 65,
  PP_NACL_ERROR_PNACL_LD_INTERNAL = 66,
  PP_NACL_ERROR_PNACL_CREATE_TEMP = 67,
  PP_NACL_ERROR_PNACL_NOT_ENABLED = 68,
  PP_NACL_ERROR_MANIFEST_NOACCESS_URL = 69,
  PP_NACL_ERROR_NEXE_NOACCESS_URL = 70,
  PP_NACL_ERROR_PNACL_CRASH_THROTTLED = 71,
  PP_NACL_ERROR_MAX
} PP_NaClError;

typedef enum {
  PP_NACL_EVENT_LOADSTART,
  PP_NACL_EVENT_PROGRESS,
  PP_NACL_EVENT_ERROR,
  PP_NACL_EVENT_ABORT,
  PP_NACL_EVENT_LOAD,
  PP_NACL_EVENT_LOADEND,
  PP_NACL_EVENT_CRASH
} PP_NaClEventType;

typedef enum {
  PP_SCHEME_CHROME_EXTENSION,
  PP_SCHEME_DATA,
  PP_SCHEME_OTHER
} PP_UrlSchemeType;

typedef enum {
  
  PP_NACL_READY_STATE_UNSENT = 0,
  
  PP_NACL_READY_STATE_OPENED = 1,
  
  PP_NACL_READY_STATE_LOADING = 3,
  PP_NACL_READY_STATE_DONE = 4
} PP_NaClReadyState;

struct PP_PNaClOptions {
  PP_Bool translate;
  PP_Bool is_debug;
  int32_t opt_level;
};

typedef void (*PP_OpenResourceCompletionCallback)(void* user_data,
                                                  PP_FileHandle file_handle);

struct PP_NaClFileInfo {
  PP_FileHandle handle;
  
  uint64_t token_lo;
  uint64_t token_hi;
};

struct PPB_NaCl_Private_1_0 {
  void (*LaunchSelLdr)(PP_Instance instance,
                       PP_Bool main_service_runtime,
                       const char* alleged_url,
                       const struct PP_NaClFileInfo* nexe_file_info,
                       PP_Bool uses_irt,
                       PP_Bool uses_ppapi,
                       PP_Bool uses_nonsfi_mode,
                       PP_Bool enable_ppapi_dev,
                       PP_Bool enable_dyncode_syscalls,
                       PP_Bool enable_exception_handling,
                       PP_Bool enable_crash_throttling,
                       void* imc_handle,
                       struct PP_CompletionCallback callback);
  PP_Bool (*StartPpapiProxy)(PP_Instance instance);
  int32_t (*UrandomFD)(void);
  PP_Bool (*Are3DInterfacesDisabled)(void);
  int32_t (*BrokerDuplicateHandle)(PP_FileHandle source_handle,
                                   uint32_t process_id,
                                   PP_FileHandle* target_handle,
                                   uint32_t desired_access,
                                   uint32_t options);
  void (*GetReadExecPnaclFd)(const char* url,
                             struct PP_NaClFileInfo* out_file_info);
  PP_FileHandle (*CreateTemporaryFile)(PP_Instance instance);
  
  int32_t (*GetNumberOfProcessors)(void);
  
  PP_Bool (*IsNonSFIModeEnabled)(void);
  void (*ReportTranslationFinished)(PP_Instance instance,
                                    PP_Bool success,
                                    int32_t opt_level,
                                    int64_t pexe_size,
                                    int64_t compile_time_us);
  void (*DispatchEvent)(PP_Instance instance,
                        PP_NaClEventType event_type,
                        const char* resource_url,
                        PP_Bool length_is_computable,
                        uint64_t loaded_bytes,
                        uint64_t total_bytes);
  
  void (*ReportLoadSuccess)(PP_Instance instance,
                            uint64_t loaded_bytes,
                            uint64_t total_bytes);
  
  void (*ReportLoadError)(PP_Instance instance,
                          PP_NaClError error,
                          const char* error_message);
  
  void (*ReportLoadAbort)(PP_Instance instance);
  
  void (*InstanceCreated)(PP_Instance instance);
  
  void (*InstanceDestroyed)(PP_Instance instance);
  PP_Bool (*NaClDebugEnabledForURL)(const char* alleged_nmf_url);
  const char* (*GetSandboxArch)(void);
  
  void (*LogToConsole)(PP_Instance instance, const char* message);
  
  PP_NaClReadyState (*GetNaClReadyState)(PP_Instance instance);
  
  void (*Vlog)(const char* message);
  
  void (*InitializePlugin)(PP_Instance instance,
                           uint32_t argc,
                           const char* argn[],
                           const char* argv[]);
  
  int64_t (*GetNexeSize)(PP_Instance instance);
  
  void (*RequestNaClManifest)(PP_Instance instance,
                              struct PP_CompletionCallback callback);
  struct PP_Var (*GetManifestBaseURL)(PP_Instance instance);
  void (*ProcessNaClManifest)(PP_Instance instance, const char* program_url);
  PP_Bool (*DevInterfacesEnabled)(PP_Instance instance);
  PP_Bool (*GetManifestProgramURL)(PP_Instance instance,
                                   struct PP_Var* full_url,
                                   struct PP_PNaClOptions* pnacl_options,
                                   PP_Bool* uses_nonsfi_mode);
  
  PP_Bool (*GetPnaclResourceInfo)(PP_Instance instance,
                                  struct PP_Var* llc_tool_name,
                                  struct PP_Var* ld_tool_name);
  struct PP_Var (*GetCpuFeatureAttrs)(void);
  void (*DownloadNexe)(PP_Instance instance,
                       const char* url,
                       struct PP_NaClFileInfo* file_info,
                       struct PP_CompletionCallback callback);
  void (*ReportSelLdrStatus)(PP_Instance instance,
                             int32_t load_status,
                             int32_t max_status);
  void (*LogTranslateTime)(const char* histogram_name, int64_t time_us);
  void (*OpenManifestEntry)(PP_Instance instance,
                            PP_Bool is_helper_process,
                            const char* key,
                            struct PP_NaClFileInfo* file_info,
                            struct PP_CompletionCallback callback);
  void (*SetPNaClStartTime)(PP_Instance instance);
  void (*StreamPexe)(PP_Instance instance,
                     const char* pexe_url,
                     int32_t opt_level,
                     const struct PPP_PexeStreamHandler_1_0* stream_handler,
                     void* stream_handler_user_data);
};

typedef struct PPB_NaCl_Private_1_0 PPB_NaCl_Private;

#endif  

