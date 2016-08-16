// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#include "android/utils/win32_cmdline_quote.h"

#include <string.h>

#include "android/utils/stralloc.h"
#include "android/utils/system.h"

char* win32_cmdline_quote(const char* param) {
  
  size_t n = strcspn(param, " \t\v\n\"");
  if (param[n] == '\0')
      return ASTRDUP(param);

  
  stralloc_t out = STRALLOC_INIT;

  
  stralloc_add_c(&out, '"');

  n = 0;
  while (param[n]) {
      size_t num_backslashes = 0;
      while (param[n] == '\\') {
          n++;
          num_backslashes++;
      }

      if (!param[n]) {
          
          for (; num_backslashes > 0; num_backslashes--)
              stralloc_add_str(&out, "\\\\");
          break;
      }

      if (param[n] == '"') {
          
          for (; num_backslashes > 0; num_backslashes--)
              stralloc_add_str(&out, "\\\\");
          stralloc_add_str(&out, "\\\"");
      } else {
          for (; num_backslashes > 0; num_backslashes--)
              stralloc_add_c(&out, '\\');
          stralloc_add_c(&out, param[n]);
      }
      n++;
  }

  
  stralloc_add_c(&out, '"');

  char* result = ASTRDUP(stralloc_cstr(&out));
  stralloc_reset(&out);
  return result;
}
