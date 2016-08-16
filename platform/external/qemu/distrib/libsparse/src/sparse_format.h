/*
 * Copyright (C) 2010 The Android Open Source Project
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

#ifndef _LIBSPARSE_SPARSE_FORMAT_H_
#define _LIBSPARSE_SPARSE_FORMAT_H_
#include "sparse_defs.h"

typedef struct sparse_header {
  __le32	magic;		
  __le16	major_version;	
  __le16	minor_version;	
  __le16	file_hdr_sz;	
  __le16	chunk_hdr_sz;	
  __le32	blk_sz;		
  __le32	total_blks;	
  __le32	total_chunks;	
  __le32	image_checksum; 
				
				
} sparse_header_t;

#define SPARSE_HEADER_MAGIC	0xed26ff3a

#define CHUNK_TYPE_RAW		0xCAC1
#define CHUNK_TYPE_FILL		0xCAC2
#define CHUNK_TYPE_DONT_CARE	0xCAC3
#define CHUNK_TYPE_CRC32    0xCAC4

typedef struct chunk_header {
  __le16	chunk_type;	
  __le16	reserved1;
  __le32	chunk_sz;	
  __le32	total_sz;	
} chunk_header_t;


#endif
