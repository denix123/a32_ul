/* Copyright (c) 2011 The WebM project authors. All Rights Reserved. */
/* Use of this source code is governed by a BSD-style license */
/* that can be found in the LICENSE file in the root of the source */
static const char* const cfg = "--force-target=mips32-android-gcc --disable-runtime-cpu-detect --sdk-path=/usr/local/google/home/hkuang/Downloads/android-ndk-r9d --disable-examples --disable-docs --enable-realtime-only";
const char *vpx_codec_build_config(void) {return cfg;}
