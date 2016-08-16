// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

enum BadOne {
  kBadOneInvalid = -1,
  kBadOneRed,
  kBadOneGreen,
  kBadOneBlue,
  kBadOneLast = kBadOneGreen
};

enum FailOne {
  FAIL_ONE_INVALID,
  FAIL_ONE_RED,
  FAIL_ONE_GREEN,
  FAIL_ONE_BLUE = 0xfffffffc,
  FAIL_ONE_LAST = FAIL_ONE_GREEN
};

enum GoodOne {
  kGoodOneInvalid = -1,
  kGoodOneRed,
  kGoodOneGreen,
  kGoodOneBlue,
  kGoodOneLast = kGoodOneBlue
};

enum GoodTwo {
  GOOD_TWO_INVALID,
  GOOD_TWO_RED,
  GOOD_TWO_GREEN,
  GOOD_TWO_BLUE = 0xfffffffc,
  GOOD_TWO_LAST = GOOD_TWO_BLUE
};
