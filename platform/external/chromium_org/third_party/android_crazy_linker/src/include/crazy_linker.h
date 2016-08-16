// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRAZY_LINKER_H
#define CRAZY_LINKER_H

#include <dlfcn.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _CRAZY_PUBLIC __attribute__((__visibility__("default")))

typedef enum {
  CRAZY_STATUS_FAILURE = 0,
  CRAZY_STATUS_SUCCESS = 1
} crazy_status_t;

typedef struct crazy_context_t crazy_context_t;

crazy_context_t* crazy_context_create(void) _CRAZY_PUBLIC;

const char* crazy_context_get_error(crazy_context_t* context) _CRAZY_PUBLIC;

void crazy_context_clear_error(crazy_context_t* context) _CRAZY_PUBLIC;

void crazy_context_set_load_address(crazy_context_t* context,
                                    size_t load_address) _CRAZY_PUBLIC;

size_t crazy_context_get_load_address(crazy_context_t* context) _CRAZY_PUBLIC;

void crazy_context_set_file_offset(crazy_context_t* context,
                                   size_t file_offset) _CRAZY_PUBLIC;

size_t crazy_context_get_file_offset(crazy_context_t* context);

crazy_status_t crazy_context_add_search_path(
    crazy_context_t* context,
    const char* file_path) _CRAZY_PUBLIC;

crazy_status_t crazy_context_add_search_path_for_address(
    crazy_context_t* context,
    void* address) _CRAZY_PUBLIC;

void crazy_context_reset_search_paths(crazy_context_t* context) _CRAZY_PUBLIC;

void crazy_context_set_java_vm(crazy_context_t* context,
                               void* java_vm,
                               int minimum_jni_version);

void crazy_context_get_java_vm(crazy_context_t* context,
                               void** java_vm,
                               int* minimum_jni_version);

void crazy_context_destroy(crazy_context_t* context) _CRAZY_PUBLIC;


typedef void (*crazy_callback_handler_t)(void* opaque);

typedef struct {
  crazy_callback_handler_t handler;
  void* opaque;
} crazy_callback_t;

typedef bool (*crazy_callback_poster_t)(
    crazy_callback_t* callback, void* poster_opaque);

void crazy_context_set_callback_poster(crazy_context_t* context,
                                       crazy_callback_poster_t poster,
                                       void* poster_opaque);

void crazy_context_get_callback_poster(crazy_context_t* context,
                                       crazy_callback_poster_t* poster,
                                       void** poster_opaque);

void crazy_callback_run(crazy_callback_t* callback);

typedef struct crazy_library_t crazy_library_t;

crazy_status_t crazy_library_open(crazy_library_t** library,
                                  const char* lib_name,
                                  crazy_context_t* context) _CRAZY_PUBLIC;

crazy_status_t crazy_library_open_in_zip_file(crazy_library_t** library,
                                              const char* zipfile_name,
                                              const char* lib_name,
                                              crazy_context_t* context)
    _CRAZY_PUBLIC;

typedef struct {
  size_t load_address;
  size_t load_size;
  size_t relro_start;
  size_t relro_size;
} crazy_library_info_t;

crazy_status_t crazy_library_get_info(crazy_library_t* library,
                                      crazy_context_t* context,
                                      crazy_library_info_t* info);

crazy_status_t crazy_system_can_share_relro(void);

crazy_status_t crazy_library_create_shared_relro(crazy_library_t* library,
                                                 crazy_context_t* context,
                                                 size_t load_address,
                                                 size_t* relro_start,
                                                 size_t* relro_size,
                                                 int* relro_fd) _CRAZY_PUBLIC;

crazy_status_t crazy_library_use_shared_relro(crazy_library_t* library,
                                              crazy_context_t* context,
                                              size_t relro_start,
                                              size_t relro_size,
                                              int relro_fd) _CRAZY_PUBLIC;

crazy_status_t crazy_library_find_by_name(const char* library_name,
                                          crazy_library_t** library);

crazy_status_t crazy_linker_find_library_from_address(
    void* address,
    crazy_library_t** library) _CRAZY_PUBLIC;

crazy_status_t crazy_library_find_symbol(crazy_library_t* library,
                                         const char* symbol_name,
                                         void** symbol_address) _CRAZY_PUBLIC;

crazy_status_t crazy_linker_find_symbol(const char* symbol_name,
                                        void** symbol_address) _CRAZY_PUBLIC;

crazy_status_t crazy_library_find_from_address(
    void* address,
    crazy_library_t** library) _CRAZY_PUBLIC;

void crazy_library_close(crazy_library_t* library) _CRAZY_PUBLIC;

void crazy_library_close_with_context(crazy_library_t* library,
                                      crazy_context_t* context) _CRAZY_PUBLIC;

#ifdef __cplusplus
} 
#endif

#endif 
