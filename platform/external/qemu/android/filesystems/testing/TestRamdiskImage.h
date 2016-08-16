// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#ifndef ANDROID_FILESYSTEMS_TESTING_TEST_RAMDISK_IMAGE_H
#define ANDROID_FILESYSTEMS_TESTING_TEST_RAMDISK_IMAGE_H


static const unsigned char kTestRamdiskImage[] = {
  0x1f, 0x8b, 0x08, 0x00, 0x6d, 0x1a, 0xa8, 0x53, 0x02, 0x03, 0xbd, 0x8e,
  0x41, 0x0a, 0x83, 0x30, 0x10, 0x45, 0xb3, 0xee, 0x29, 0x26, 0x37, 0x98,
  0xc4, 0x46, 0xd3, 0x65, 0xac, 0x86, 0x16, 0x5c, 0x49, 0xa1, 0x6b, 0x4b,
  0x63, 0x11, 0x06, 0x43, 0xad, 0x7a, 0xfe, 0x2a, 0x41, 0x90, 0x2e, 0x8a,
  0xdd, 0xf4, 0x6d, 0xfe, 0x1f, 0x66, 0x60, 0x1e, 0x26, 0x98, 0xa0, 0x40,
  0x14, 0xb9, 0xd4, 0x07, 0x8b, 0x13, 0x5a, 0x98, 0x39, 0x30, 0xb6, 0x26,
  0x9d, 0x53, 0x44, 0x5a, 0x63, 0x40, 0xa8, 0xc8, 0x4c, 0xeb, 0x38, 0x0b,
  0xa3, 0x54, 0x21, 0xed, 0x11, 0xbf, 0xa3, 0x96, 0x72, 0xab, 0x3a, 0xc9,
  0x58, 0x51, 0xc1, 0xd8, 0x38, 0x70, 0xaf, 0x1e, 0x86, 0x16, 0xc8, 0xb7,
  0x0f, 0xa8, 0xc9, 0x0d, 0xa3, 0x83, 0xbe, 0xab, 0xda, 0xe7, 0xd0, 0x10,
  0xb9, 0x1d, 0x63, 0x0c, 0xd7, 0x6e, 0xd9, 0x6f, 0x6e, 0x98, 0x6d, 0x74,
  0xdb, 0x2f, 0xa5, 0xf6, 0x7e, 0xfa, 0x79, 0x72, 0x44, 0x1e, 0xae, 0xbe,
  0xa3, 0x3b, 0x5f, 0x3b, 0x6c, 0x62, 0xeb, 0xdd, 0x27, 0xe9, 0x52, 0x2e,
  0xa5, 0x39, 0x17, 0x79, 0xc9, 0x39, 0x67, 0x7f, 0xe2, 0x0d, 0xb9, 0x32,
  0x87, 0xaa, 0x00, 0x02, 0x00, 0x00
};

static const size_t kTestRamdiskImageSize = sizeof(kTestRamdiskImage);

#endif  