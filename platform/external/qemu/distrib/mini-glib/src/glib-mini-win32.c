// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#ifdef _WIN32

#include <glib.h>

#include <assert.h>
#include <wchar.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>


void g_atomic_int_inc(int volatile* atomic) {
  assert(sizeof(LONG) == sizeof(int));
  InterlockedIncrement((LONG volatile*)atomic);
}

gboolean g_atomic_int_dec_and_test(int volatile* atomic) {
  assert(sizeof(LONG) == sizeof(int));
  return !InterlockedIncrement((LONG volatile*)atomic);
}


static char*
utf16_to_utf8(const wchar_t* wstring, int wstring_len)
{
  int utf8_len = WideCharToMultiByte(CP_UTF8,          
                                     0,                
                                     (LPWSTR) wstring, 
                                     wstring_len,      
                                     NULL,             
                                     0,                
                                     NULL,             
                                     NULL);            
  if (utf8_len == 0)
    return g_strdup("");

  char* result = g_malloc(utf8_len + 1);

  WideCharToMultiByte(CP_UTF8, 0, (LPWSTR) wstring, wstring_len,
                      result, utf8_len, NULL, NULL);
  result[utf8_len] = '\0';
  return result;
}

char *
g_win32_error_message (int error)
{
  LPWSTR msg = NULL;
  int nchars;
  char* result;

  
  union {
    LPWSTR* address;
    LPWSTR  value;
  } msg_param;
  msg_param.address = &msg;

  FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER
                 |FORMAT_MESSAGE_IGNORE_INSERTS
                 |FORMAT_MESSAGE_FROM_SYSTEM,
                 NULL, error, 0,
                 msg_param.value,
                 0, NULL);
  if (!msg)
    return g_strdup("");

  
  nchars = wcslen (msg);
  if (nchars > 2 && msg[nchars-1] == '\n' && msg[nchars-2] == '\r')
    msg[nchars-2] = '\0';

  result = utf16_to_utf8 (msg, nchars);

  LocalFree (msg);

  return result;
}

#endif  
