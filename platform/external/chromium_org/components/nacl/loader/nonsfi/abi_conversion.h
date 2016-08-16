// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_NACL_LOADER_NONSFI_ABI_CONVERSION_H_
#define COMPONENTS_NACL_LOADER_NONSFI_ABI_CONVERSION_H_

struct stat;
struct timespec;
struct nacl_abi_stat;
struct nacl_abi_timespec;

namespace nacl {
namespace nonsfi {

void NaClAbiTimeSpecToTimeSpec(const struct nacl_abi_timespec& nacl_timespec,
                               struct timespec* host_timespec);

void TimeSpecToNaClAbiTimeSpec(const struct timespec& host_timespec,
                               struct nacl_abi_timespec* nacl_timespec);


void StatToNaClAbiStat(
    const struct stat& host_stat, struct nacl_abi_stat* nacl_stat);

}  
}  

#endif  
