/* Copyright 2013 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file. */

#ifndef LIBRARIES_NACL_IO_IOCTL_H_
#define LIBRARIES_NACL_IO_IOCTL_H_

#include <sys/types.h>

/*
 * ioctl to register an output handler with the tty node.  Will fail with
 * EALREADY if a handler is already registered.  Expects an argument of type
 * tioc_nacl_output.  The handler will be called during calls to write() on the
 * thread that calls write(), or, for echoed input during the
 * NACL_IOC_HANDLEMESSAGE ioctl() on the thread calling ioctl(). The handler
 * should return the number of bytes written/handled, or -errno if an error
 * occured.
 */
#define TIOCNACLOUTPUT 0xadcd03

#define NACL_IOC_PIPE_SETNAME 0xadcd04

#define NACL_IOC_PIPE_GETOSPACE 0xadcd06
#define NACL_IOC_PIPE_GETISPACE 0xadcd07

#define NACL_IOC_HANDLEMESSAGE 0xadcd05

typedef char* naclioc_jspipe_name;

typedef ssize_t (*tioc_nacl_output_handler_t)(const char* buf,
                                              size_t count,
                                              void* user_data);

struct tioc_nacl_output {
  tioc_nacl_output_handler_t handler;
  void* user_data;
};


#endif  
