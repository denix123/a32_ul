// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <sys/prctl.h>
#include <unistd.h>


#define ERR_PREFIX "[PIE Loader] "

typedef int (*main_t)(int, char**);


int main(int argc, char** argv) {
  if (argc < 2) {
    printf("Usage: %s path_to_pie_executable [args]\n", argv[0]);
    return -1;
  }

  
  
  
  int i;
  char* next_argv_start = argv[0];
  for (i = 1; i < argc; ++i) {
    const size_t argv_len = strlen(argv[i]) + 1;
    memcpy(argv[i - 1], argv[i], argv_len);
    next_argv_start += argv_len;
    argv[i] = next_argv_start;
  }
  argv[argc - 1] = NULL;  

  
  prctl(PR_SET_NAME, (long) argv[0]);

  
  
  
  
  void* handle = dlopen(argv[0], RTLD_NOW);
  if (handle == NULL) {
    printf(ERR_PREFIX "dlopen() failed: %s.\n", dlerror());
    return -1;
  }

  main_t pie_main = (main_t) dlsym(handle, "main");
  if (pie_main) {
    return pie_main(argc - 1, argv);
  }

  
  
  
  
  execv(argv[0], argv);

  
  printf(ERR_PREFIX "Both dlsym() and the execv() fallback failed.\n");
  perror("execv");
  return -1;
}
