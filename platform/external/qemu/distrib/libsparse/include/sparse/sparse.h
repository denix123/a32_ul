/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _LIBSPARSE_SPARSE_H_
#define _LIBSPARSE_SPARSE_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

struct sparse_file;

/**
 * sparse_file_new - create a new sparse file cookie
 *
 * @block_size - minimum size of a chunk
 * @len - size of the expanded sparse file.
 *
 * Creates a new sparse_file cookie that can be used to associate data
 * blocks.  Can later be written to a file with a variety of options.
 * block_size specifies the minimum size of a chunk in the file.  The maximum
 * size of the file is 2**32 * block_size (16TB for 4k block size).
 *
 * Returns the sparse file cookie, or NULL on error.
 */
struct sparse_file *sparse_file_new(unsigned int block_size, int64_t len);

void sparse_file_destroy(struct sparse_file *s);

int sparse_file_add_data(struct sparse_file *s,
		void *data, unsigned int len, unsigned int block);

int sparse_file_add_fill(struct sparse_file *s,
		uint32_t fill_val, unsigned int len, unsigned int block);

int sparse_file_add_file(struct sparse_file *s,
		const char *filename, int64_t file_offset, unsigned int len,
		unsigned int block);

int sparse_file_add_fd(struct sparse_file *s,
		int fd, int64_t file_offset, unsigned int len, unsigned int block);

/**
 * sparse_file_write - write a sparse file to a file
 *
 * @s - sparse file cookie
 * @fd - file descriptor to write to
 * @gz - write a gzipped file
 * @sparse - write in the Android sparse file format
 * @crc - append a crc chunk
 *
 * Writes a sparse file to a file.  If gz is true, the data will be passed
 * through zlib.  If sparse is true, the file will be written in the Android
 * sparse file format.  If sparse is false, the file will be written by seeking
 * over unused chunks, producing a smaller file if the filesystem supports
 * sparse files.  If crc is true, the crc of the expanded data will be
 * calculated and appended in a crc chunk.
 *
 * Returns 0 on success, negative errno on error.
 */
int sparse_file_write(struct sparse_file *s, int fd, bool gz, bool sparse,
		bool crc);

/**
 * sparse_file_len - return the length of a sparse file if written to disk
 *
 * @s - sparse file cookie
 * @sparse - write in the Android sparse file format
 * @crc - append a crc chunk
 *
 * Returns the size a sparse file would be on disk if it were written in the
 * specified format.  If sparse is true, this is the size of the data in the
 * sparse format.  If sparse is false, this is the size of the normal
 * non-sparse file.
 */
int64_t sparse_file_len(struct sparse_file *s, bool sparse, bool crc);

/**
 * sparse_file_callback - call a callback for blocks in sparse file
 *
 * @s - sparse file cookie
 * @sparse - write in the Android sparse file format
 * @crc - append a crc chunk
 * @write - function to call for each block
 * @priv - value that will be passed as the first argument to write
 *
 * Writes a sparse file by calling a callback function.  If sparse is true, the
 * file will be written in the Android sparse file format.  If crc is true, the
 * crc of the expanded data will be calculated and appended in a crc chunk.
 * The callback 'write' will be called with data and length for each data,
 * and with data==NULL to skip over a region (only used for non-sparse format).
 * The callback should return negative on error, 0 on success.
 *
 * Returns 0 on success, negative errno on error.
 */
int sparse_file_callback(struct sparse_file *s, bool sparse, bool crc,
		int (*write)(void *priv, const void *data, int len), void *priv);

int sparse_file_read(struct sparse_file *s, int fd, bool sparse, bool crc);

struct sparse_file *sparse_file_import(int fd, bool verbose, bool crc);

struct sparse_file *sparse_file_import_auto(int fd, bool crc);

/** sparse_file_resparse - rechunk an existing sparse file into smaller files
 *
 * @in_s - sparse file cookie of the existing sparse file
 * @max_len - maximum file size
 * @out_s - array of sparse file cookies
 * @out_s_count - size of out_s array
 *
 * Splits chunks of an existing sparse file into smaller sparse files such that
 * each sparse file is less than max_len.  Returns the number of sparse_files
 * that would have been written to out_s if out_s were big enough.
 */
int sparse_file_resparse(struct sparse_file *in_s, unsigned int max_len,
		struct sparse_file **out_s, int out_s_count);

void sparse_file_verbose(struct sparse_file *s);

extern void (*sparse_print_verbose)(const char *fmt, ...);

#ifdef	__cplusplus
}
#endif

#endif
