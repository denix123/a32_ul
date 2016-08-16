/* Copyright (c) 2012 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file. */

#ifndef LIBRARIES_NACL_IO_NACL_IO_H_
#define LIBRARIES_NACL_IO_NACL_IO_H_

#include <ppapi/c/pp_instance.h>
#include <ppapi/c/ppb.h>

#include "nacl_io/ostypes.h"
#include "sdk_util/macros.h"

EXTERN_C_BEGIN

typedef void (*nacl_io_exit_callback_t)(int status, void* user_data);

typedef void (*nacl_io_mount_callback_t)(const char* source,
                                         const char* target,
                                         const char* filesystemtype,
                                         unsigned long mountflags,
                                         const void* data,
                                         dev_t dev,
                                         void* user_data);

int nacl_io_init();

int nacl_io_init_ppapi(PP_Instance instance, PPB_GetInterface get_interface);

int nacl_io_uninit();

void nacl_io_set_exit_callback(nacl_io_exit_callback_t exit_callback,
                               void* user_data);


struct fuse_operations;
int nacl_io_register_fs_type(const char* fs_type,
                             struct fuse_operations* fuse_ops);

int nacl_io_unregister_fs_type(const char* fs_type);

void nacl_io_set_mount_callback(nacl_io_mount_callback_t callback,
                                void* user_data);

EXTERN_C_END

#endif 
