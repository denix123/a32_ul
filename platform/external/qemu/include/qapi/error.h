/*
 * QEMU Error Objects
 *
 * Copyright IBM, Corp. 2011
 *
 * Authors:
 *  Anthony Liguori   <aliguori@us.ibm.com>
 *
 * This work is licensed under the terms of the GNU LGPL, version 2.  See
 * the COPYING.LIB file in the top-level directory.
 */
#ifndef ERROR_H
#define ERROR_H

#include "qemu/compiler.h"
#include "qapi-types.h"
#include <stdbool.h>

typedef struct Error Error;

void error_set(Error **err, ErrorClass err_class, const char *fmt, ...) GCC_FMT_ATTR(3, 4);

void error_set_errno(Error **err, int os_error, ErrorClass err_class, const char *fmt, ...) GCC_FMT_ATTR(4, 5);

#ifdef _WIN32
void error_set_win32(Error **err, int win32_err, ErrorClass err_class, const char *fmt, ...) GCC_FMT_ATTR(4, 5);
#endif

#define error_setg(err, fmt, ...) \
    error_set(err, ERROR_CLASS_GENERIC_ERROR, fmt, ## __VA_ARGS__)
#define error_setg_errno(err, os_error, fmt, ...) \
    error_set_errno(err, os_error, ERROR_CLASS_GENERIC_ERROR, fmt, ## __VA_ARGS__)
#ifdef _WIN32
#define error_setg_win32(err, win32_err, fmt, ...) \
    error_set_win32(err, win32_err, ERROR_CLASS_GENERIC_ERROR, fmt, ## __VA_ARGS__)
#endif

void error_setg_file_open(Error **errp, int os_errno, const char *filename);

bool error_is_set(Error **err);

ErrorClass error_get_class(const Error *err);

Error *error_copy(const Error *err);

const char *error_get_pretty(Error *err);

void error_propagate(Error **dst_err, Error *local_err);

void error_free(Error *err);

#endif
