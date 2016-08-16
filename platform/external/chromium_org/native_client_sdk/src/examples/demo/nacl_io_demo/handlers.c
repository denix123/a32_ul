/* Copyright (c) 2012 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file. */

#include "handlers.h"

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>

#include "nacl_io/osdirent.h"

#include "nacl_io_demo.h"

#define MAX_OPEN_FILES 10
#define MAX_OPEN_DIRS 10
#define MAX_PARAMS 4

#if defined(WIN32)
#define stat _stat
#endif

static FILE* g_OpenFiles[MAX_OPEN_FILES];

static void* g_OpenDirs[MAX_OPEN_DIRS];

static char* g_ParamStrings[MAX_PARAMS];

static int AddToMap(void** map, int max_map_size, void* object) {
  int i;
  assert(object != NULL);
  for (i = 0; i < max_map_size; ++i) {
    if (map[i] == NULL) {
      map[i] = object;
      return i;
    }
  }

  return -1;
}

static void RemoveFromMap(void** map, int max_map_size, int i) {
  assert(i >= 0 && i < max_map_size);
  map[i] = NULL;
}

static int AddFileToMap(FILE* file) {
  return AddToMap((void**)g_OpenFiles, MAX_OPEN_FILES, file);
}

static void RemoveFileFromMap(int i) {
  RemoveFromMap((void**)g_OpenFiles, MAX_OPEN_FILES, i);
}

#if !defined(WIN32)
static int AddDirToMap(DIR* dir) {
  return AddToMap((void**)g_OpenDirs, MAX_OPEN_DIRS, dir);
}

static void RemoveDirFromMap(int i) {
  RemoveFromMap((void**)g_OpenDirs, MAX_OPEN_DIRS, i);
}
#endif

static uint32_t GetNumParams(struct PP_Var params) {
  return g_ppb_var_array->GetLength(params);
}

static int GetParamString(struct PP_Var params,
                          uint32_t index,
                          char** out_string,
                          uint32_t* out_string_len,
                          const char** out_error) {
  if (index >= MAX_PARAMS) {
    *out_error = PrintfToNewString("Param index %u >= MAX_PARAMS (%d)",
                                   index, MAX_PARAMS);
    return 1;
  }

  struct PP_Var value = g_ppb_var_array->Get(params, index);
  if (value.type != PP_VARTYPE_STRING) {
    *out_error =
        PrintfToNewString("Expected param at index %d to be a string", index);
    return 1;
  }

  uint32_t length;
  const char* var_str = g_ppb_var->VarToUtf8(value, &length);

  char* string = (char*)malloc(length + 1);
  memcpy(string, var_str, length);
  string[length] = 0;

  free(g_ParamStrings[index]);
  g_ParamStrings[index] = string;


  *out_string = string;
  *out_string_len = length;
  return 0;
}

static int GetParamFile(struct PP_Var params,
                        uint32_t index,
                        FILE** out_file,
                        int32_t* out_file_index,
                        const char** out_error) {
  struct PP_Var value = g_ppb_var_array->Get(params, index);
  if (value.type != PP_VARTYPE_INT32) {
    *out_error =
        PrintfToNewString("Expected param at index %d to be an int32", index);
    return 1;
  }

  int32_t file_index = value.value.as_int;
  if (file_index < 0 || file_index >= MAX_OPEN_FILES) {
    *out_error = PrintfToNewString("File index %d is out range", file_index);
    return 1;
  }

  if (g_OpenFiles[file_index] == NULL) {
    *out_error = PrintfToNewString("File index %d is not open", file_index);
    return 1;
  }

  *out_file = g_OpenFiles[file_index];
  *out_file_index = file_index;
  return 0;
}

static int GetParamDir(struct PP_Var params,
                       uint32_t index,
                       DIR** out_dir,
                       int32_t* out_dir_index,
                       const char** out_error) {
  struct PP_Var value = g_ppb_var_array->Get(params, index);
  if (value.type != PP_VARTYPE_INT32) {
    *out_error =
        PrintfToNewString("Expected param at index %d to be an int32", index);
    return 1;
  }

  int32_t dir_index = value.value.as_int;
  if (dir_index < 0 || dir_index >= MAX_OPEN_DIRS) {
    *out_error = PrintfToNewString("Dir at index %d is out range", dir_index);
    return 1;
  }

  if (g_OpenDirs[dir_index] == NULL) {
    *out_error = PrintfToNewString("Dir index %d is not open", dir_index);
    return 1;
  }

  *out_dir = g_OpenDirs[dir_index];
  *out_dir_index = dir_index;
  return 0;
}

static int GetParamInt(struct PP_Var params,
                       uint32_t index,
                       int32_t* out_int,
                       const char** out_error) {
  struct PP_Var value = g_ppb_var_array->Get(params, index);
  if (value.type != PP_VARTYPE_INT32) {
    *out_error =
        PrintfToNewString("Expected param at index %d to be an int32", index);
    return 1;
  }

  *out_int = value.value.as_int;
  return 0;
}

static void CreateResponse(struct PP_Var* response_var,
                           const char* cmd,
                           const char** out_error) {
  PP_Bool result;

  struct PP_Var dict_var = g_ppb_var_dictionary->Create();
  struct PP_Var cmd_key = CStrToVar("cmd");
  struct PP_Var cmd_value = CStrToVar(cmd);

  result = g_ppb_var_dictionary->Set(dict_var, cmd_key, cmd_value);
  g_ppb_var->Release(cmd_key);
  g_ppb_var->Release(cmd_value);

  if (!result) {
    g_ppb_var->Release(dict_var);
    *out_error =
        PrintfToNewString("Unable to set \"cmd\" key in result dictionary");
    return;
  }

  struct PP_Var args_key = CStrToVar("args");
  struct PP_Var args_value = g_ppb_var_array->Create();
  result = g_ppb_var_dictionary->Set(dict_var, args_key, args_value);
  g_ppb_var->Release(args_key);
  g_ppb_var->Release(args_value);

  if (!result) {
    g_ppb_var->Release(dict_var);
    *out_error =
        PrintfToNewString("Unable to set \"args\" key in result dictionary");
    return;
  }

  *response_var = dict_var;
}

static void AppendResponseVar(struct PP_Var* response_var,
                              struct PP_Var value,
                              const char** out_error) {
  struct PP_Var args_value = GetDictVar(*response_var, "args");
  uint32_t args_length = g_ppb_var_array->GetLength(args_value);
  PP_Bool result = g_ppb_var_array->Set(args_value, args_length, value);
  if (!result) {
    
    g_ppb_var->Release(*response_var);

    
    *response_var = PP_MakeUndefined();
    *out_error = PrintfToNewString("Unable to append value to result");
    return;
  }
}

static void AppendResponseInt(struct PP_Var* response_var,
                              int32_t value,
                              const char** out_error) {
  AppendResponseVar(response_var, PP_MakeInt32(value), out_error);
}

static void AppendResponseString(struct PP_Var* response_var,
                                 const char* value,
                                 const char** out_error) {
  struct PP_Var value_var = CStrToVar(value);
  AppendResponseVar(response_var, value_var, out_error);
  g_ppb_var->Release(value_var);
}

#define CHECK_PARAM_COUNT(name, expected)                                   \
  if (GetNumParams(params) != expected) {                                   \
    *out_error = PrintfToNewString(#name " takes " #expected " parameters." \
                                   " Got %d", GetNumParams(params));        \
    return 1;                                                               \
  }

#define PARAM_STRING(index, var)                                    \
  char* var;                                                        \
  uint32_t var##_len;                                               \
  if (GetParamString(params, index, &var, &var##_len, out_error)) { \
    return 1;                                                       \
  }

#define PARAM_FILE(index, var)                                      \
  FILE* var;                                                        \
  int32_t var##_index;                                              \
  if (GetParamFile(params, index, &var, &var##_index, out_error)) { \
    return 1;                                                       \
  }

#define PARAM_DIR(index, var)                                      \
  DIR* var;                                                        \
  int32_t var##_index;                                             \
  if (GetParamDir(params, index, &var, &var##_index, out_error)) { \
    return 1;                                                      \
  }

#define PARAM_INT(index, var)                        \
  int32_t var;                                       \
  if (GetParamInt(params, index, &var, out_error)) { \
    return 1;                                        \
  }

#define CREATE_RESPONSE(name) CreateResponse(output, #name, out_error)
#define RESPONSE_STRING(var) AppendResponseString(output, var, out_error)
#define RESPONSE_INT(var) AppendResponseInt(output, var, out_error)

int HandleFopen(struct PP_Var params,
                struct PP_Var* output,
                const char** out_error) {
  CHECK_PARAM_COUNT(fopen, 2);
  PARAM_STRING(0, filename);
  PARAM_STRING(1, mode);

  FILE* file = fopen(filename, mode);

  if (!file) {
    *out_error = PrintfToNewString("fopen returned a NULL FILE*");
    return 1;
  }

  int file_index = AddFileToMap(file);
  if (file_index == -1) {
    *out_error = PrintfToNewString("Example only allows %d open file handles",
                                   MAX_OPEN_FILES);
    return 1;
  }

  CREATE_RESPONSE(fopen);
  RESPONSE_STRING(filename);
  RESPONSE_INT(file_index);
  return 0;
}

/**
 * Handle a call to fwrite() made by JavaScript.
 *
 * fwrite expects 2 parameters:
 *   0: The index of the file (which is mapped to a FILE*)
 *   1: A string to write to the file
 * on success, fwrite returns a result in |output|:
 *   0: "fwrite"
 *   1: the file index
 *   2: the number of bytes written
 * on failure, fwrite returns an error string in |out_error|.
 */
int HandleFwrite(struct PP_Var params,
                 struct PP_Var* output,
                 const char** out_error) {
  CHECK_PARAM_COUNT(fwrite, 2);
  PARAM_FILE(0, file);
  PARAM_STRING(1, data);

  size_t bytes_written = fwrite(data, 1, data_len, file);
  if (ferror(file)) {
    *out_error = PrintfToNewString("Wrote %d bytes, but ferror() returns true",
                                   bytes_written);
    return 1;
  }

  CREATE_RESPONSE(fwrite);
  RESPONSE_INT(file_index);
  RESPONSE_INT(bytes_written);
  return 0;
}

int HandleFread(struct PP_Var params,
                struct PP_Var* output,
                const char** out_error) {
  CHECK_PARAM_COUNT(fread, 2);
  PARAM_FILE(0, file);
  PARAM_INT(1, data_len);

  char* buffer = (char*)malloc(data_len + 1);
  size_t bytes_read = fread(buffer, 1, data_len, file);
  buffer[bytes_read] = 0;

  if (ferror(file)) {
    *out_error = PrintfToNewString("Read %d bytes, but ferror() returns true",
                                   bytes_read);
    free(buffer);
    return 1;
  }

  CREATE_RESPONSE(fread);
  RESPONSE_INT(file_index);
  RESPONSE_STRING(buffer);
  free(buffer);
  return 0;
}

int HandleFseek(struct PP_Var params,
                struct PP_Var* output,
                const char** out_error) {
  CHECK_PARAM_COUNT(fseek, 3);
  PARAM_FILE(0, file);
  PARAM_INT(1, offset);
  PARAM_INT(2, whence);

  int result = fseek(file, offset, whence);
  if (result) {
    *out_error = PrintfToNewString("fseek returned error %d", result);
    return 1;
  }

  offset = ftell(file);
  if (offset < 0) {
    *out_error = PrintfToNewString(
        "fseek succeeded, but ftell returned error %d", offset);
    return 1;
  }

  CREATE_RESPONSE(fseek);
  RESPONSE_INT(file_index);
  RESPONSE_INT(offset);
  return 0;
}

int HandleFflush(struct PP_Var params,
                 struct PP_Var* output,
                 const char** out_error) {
  CHECK_PARAM_COUNT(fflush, 1);
  PARAM_FILE(0, file);

  fflush(file);

  CREATE_RESPONSE(fflush);
  RESPONSE_INT(file_index);
  return 0;
}

int HandleFclose(struct PP_Var params,
                 struct PP_Var* output,
                 const char** out_error) {
  CHECK_PARAM_COUNT(fclose, 1);
  PARAM_FILE(0, file);

  int result = fclose(file);
  if (result) {
    *out_error = PrintfToNewString("fclose returned error %d", result);
    return 1;
  }

  RemoveFileFromMap(file_index);

  CREATE_RESPONSE(fclose);
  RESPONSE_INT(file_index);
  return 0;
}

int HandleStat(struct PP_Var params,
               struct PP_Var* output,
               const char** out_error) {
  CHECK_PARAM_COUNT(stat, 1);
  PARAM_STRING(0, filename);

  struct stat buf;
  memset(&buf, 0, sizeof(buf));
  int result = stat(filename, &buf);

  if (result == -1) {
    *out_error = PrintfToNewString("stat returned error %d", errno);
    return 1;
  }

  CREATE_RESPONSE(stat);
  RESPONSE_STRING(filename);
  RESPONSE_INT(buf.st_size);
  return 0;
}

int HandleOpendir(struct PP_Var params,
                  struct PP_Var* output,
                  const char** out_error) {
#if defined(WIN32)
  *out_error = PrintfToNewString("Win32 does not support opendir");
  return 1;
#else
  CHECK_PARAM_COUNT(opendir, 1);
  PARAM_STRING(0, dirname);

  DIR* dir = opendir(dirname);

  if (!dir) {
    *out_error = PrintfToNewString("opendir returned a NULL DIR*");
    return 1;
  }

  int dir_index = AddDirToMap(dir);
  if (dir_index == -1) {
    *out_error = PrintfToNewString("Example only allows %d open dir handles",
                                   MAX_OPEN_DIRS);
    return 1;
  }

  CREATE_RESPONSE(opendir);
  RESPONSE_STRING(dirname);
  RESPONSE_INT(dir_index);
  return 0;
#endif
}

int HandleReaddir(struct PP_Var params,
                  struct PP_Var* output,
                  const char** out_error) {
#if defined(WIN32)
  *out_error = PrintfToNewString("Win32 does not support readdir");
  return 1;
#else
  CHECK_PARAM_COUNT(readdir, 1);
  PARAM_DIR(0, dir);

  struct dirent* entry = readdir(dir);

  CREATE_RESPONSE(readdir);
  RESPONSE_INT(dir_index);
  if (entry != NULL) {
    RESPONSE_INT(entry->d_ino);
    RESPONSE_STRING(entry->d_name);
  }
  return 0;
#endif
}

int HandleClosedir(struct PP_Var params,
                   struct PP_Var* output,
                   const char** out_error) {
#if defined(WIN32)
  *out_error = PrintfToNewString("Win32 does not support closedir");
  return 1;
#else
  CHECK_PARAM_COUNT(closedir, 1);
  PARAM_DIR(0, dir);

  int result = closedir(dir);
  if (result) {
    *out_error = PrintfToNewString("closedir returned error %d", result);
    return 1;
  }

  RemoveDirFromMap(dir_index);

  CREATE_RESPONSE(closedir);
  RESPONSE_INT(dir_index);
  return 0;
#endif
}

int HandleMkdir(struct PP_Var params,
                struct PP_Var* output,
                const char** out_error) {
  CHECK_PARAM_COUNT(mkdir, 2);
  PARAM_STRING(0, dirname);
  PARAM_INT(1, mode);

  int result = mkdir(dirname, mode);

  if (result != 0) {
    *out_error = PrintfToNewString("mkdir returned error: %d", errno);
    return 1;
  }

  CREATE_RESPONSE(mkdir);
  RESPONSE_STRING(dirname);
  return 0;
}

int HandleRmdir(struct PP_Var params,
                struct PP_Var* output,
                const char** out_error) {
  CHECK_PARAM_COUNT(rmdir, 1);
  PARAM_STRING(0, dirname);

  int result = rmdir(dirname);

  if (result != 0) {
    *out_error = PrintfToNewString("rmdir returned error: %d", errno);
    return 1;
  }

  CREATE_RESPONSE(rmdir);
  RESPONSE_STRING(dirname);
  return 0;
}

int HandleChdir(struct PP_Var params,
                struct PP_Var* output,
                const char** out_error) {
  CHECK_PARAM_COUNT(chdir, 1);
  PARAM_STRING(0, dirname);

  int result = chdir(dirname);

  if (result != 0) {
    *out_error = PrintfToNewString("chdir returned error: %d", errno);
    return 1;
  }

  CREATE_RESPONSE(chdir);
  RESPONSE_STRING(dirname);
  return 0;
}

int HandleGetcwd(struct PP_Var params,
                 struct PP_Var* output,
                 const char** out_error) {
  CHECK_PARAM_COUNT(getcwd, 0);

  char cwd[PATH_MAX];
  char* result = getcwd(cwd, PATH_MAX);
  if (result == NULL) {
    *out_error = PrintfToNewString("getcwd returned error: %d", errno);
    return 1;
  }

  CREATE_RESPONSE(getcwd);
  RESPONSE_STRING(cwd);
  return 0;
}

int HandleGetaddrinfo(struct PP_Var params,
                      struct PP_Var* output,
                      const char** out_error) {
  CHECK_PARAM_COUNT(getaddrinfo, 2);
  PARAM_STRING(0, name);
  PARAM_STRING(1, family);

  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_flags = AI_CANONNAME;
  if (!strcmp(family, "AF_INET"))
    hints.ai_family = AF_INET;
  else if (!strcmp(family, "AF_INET6"))
    hints.ai_family = AF_INET6;
  else if (!strcmp(family, "AF_UNSPEC"))
    hints.ai_family = AF_UNSPEC;
  else {
    *out_error = PrintfToNewString("getaddrinfo uknown family: %s", family);
    return 1;
  }

  struct addrinfo* ai;
  int rtn = getaddrinfo(name, NULL, &hints, &ai);
  if (rtn != 0) {
    *out_error = PrintfToNewString("getaddrinfo failed, error is \"%s\"",
                                   gai_strerror(rtn));
    return 2;
  }

  CREATE_RESPONSE(getaddrinfo);
  RESPONSE_STRING(ai->ai_canonname);
  struct addrinfo* current = ai;
  while (current) {
    char addr_str[INET6_ADDRSTRLEN];
    if (ai->ai_family == AF_INET6) {
      struct sockaddr_in6* in6 = (struct sockaddr_in6*)current->ai_addr;
      inet_ntop(
          ai->ai_family, &in6->sin6_addr.s6_addr, addr_str, sizeof(addr_str));
    } else if (ai->ai_family == AF_INET) {
      struct sockaddr_in* in = (struct sockaddr_in*)current->ai_addr;
      inet_ntop(ai->ai_family, &in->sin_addr, addr_str, sizeof(addr_str));
    }

    RESPONSE_STRING(addr_str);
    RESPONSE_STRING(ai->ai_family == AF_INET ? "AF_INET" : "AF_INET6");

    current = current->ai_next;
  }

  freeaddrinfo(ai);
  return 0;
}

int HandleGethostbyname(struct PP_Var params,
                        struct PP_Var* output,
                        const char** out_error) {
  CHECK_PARAM_COUNT(gethostbyname, 1);
  PARAM_STRING(0, name);

  struct hostent* info = gethostbyname(name);
  if (!info) {
    *out_error = PrintfToNewString("gethostbyname failed, error is \"%s\"",
                                   hstrerror(h_errno));
    return 1;
  }

  CREATE_RESPONSE(gethostbyname);
  RESPONSE_STRING(info->h_name);
  RESPONSE_STRING(info->h_addrtype == AF_INET ? "AF_INET" : "AF_INET6");

  struct in_addr** addr_list = (struct in_addr**)info->h_addr_list;
  int i;
  for (i = 0; addr_list[i] != NULL; i++) {
    if (info->h_addrtype == AF_INET) {
      RESPONSE_STRING(inet_ntoa(*addr_list[i]));
    } else {  
      char addr_str[INET6_ADDRSTRLEN];
      inet_ntop(AF_INET6, addr_list[i], addr_str, sizeof(addr_str));
      RESPONSE_STRING(addr_str);
    }
  }
  return 0;
}

int HandleConnect(struct PP_Var params,
                  struct PP_Var* output,
                  const char** out_error) {
  CHECK_PARAM_COUNT(connect, 2);
  PARAM_STRING(0, hostname);
  PARAM_INT(1, port);

  
  struct hostent* hostent = gethostbyname(hostname);
  if (hostent == NULL) {
    *out_error = PrintfToNewString("gethostbyname() returned error: %d", errno);
    return 1;
  }

  struct sockaddr_in addr;
  socklen_t addrlen = sizeof(addr);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  memcpy(&addr.sin_addr.s_addr, hostent->h_addr_list[0], hostent->h_length);

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    *out_error = PrintfToNewString("socket() failed: %s", strerror(errno));
    return 1;
  }

  int result = connect(sock, (struct sockaddr*)&addr, addrlen);
  if (result != 0) {
    *out_error = PrintfToNewString("connect() failed: %s", strerror(errno));
    close(sock);
    return 1;
  }

  CREATE_RESPONSE(connect);
  RESPONSE_INT(sock);
  return 0;
}

int HandleSend(struct PP_Var params,
               struct PP_Var* output,
               const char** out_error) {
  CHECK_PARAM_COUNT(send, 2);
  PARAM_INT(0, sock);
  PARAM_STRING(1, buffer);

  int result = send(sock, buffer, strlen(buffer), 0);
  if (result <= 0) {
    *out_error = PrintfToNewString("send failed: %s", strerror(errno));
    return 1;
  }

  CREATE_RESPONSE(send);
  RESPONSE_INT(result);
  return 0;
}

int HandleRecv(struct PP_Var params,
               struct PP_Var* output,
               const char** out_error) {
  CHECK_PARAM_COUNT(recv, 2);
  PARAM_INT(0, sock);
  PARAM_INT(1, buffersize);

  if (buffersize < 0 || buffersize > 65 * 1024) {
    *out_error =
        PrintfToNewString("recv buffersize must be between 0 and 65k.");
    return 1;
  }

  char* buffer = alloca(buffersize);
  memset(buffer, 0, buffersize);
  int result = recv(sock, buffer, buffersize, 0);
  if (result <= 0) {
    *out_error = PrintfToNewString("recv failed: %s", strerror(errno));
    return 1;
  }

  CREATE_RESPONSE(recv);
  RESPONSE_INT(result);
  RESPONSE_STRING(buffer);
  return 0;
}

int HandleClose(struct PP_Var params,
                struct PP_Var* output,
                const char** out_error) {
  CHECK_PARAM_COUNT(close, 1);
  PARAM_INT(0, sock);

  int result = close(sock);
  if (result != 0) {
    *out_error = PrintfToNewString("close returned error: %d", errno);
    return 1;
  }

  CREATE_RESPONSE(close);
  RESPONSE_INT(sock);
  return 0;
}
