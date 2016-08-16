// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_NTP_LOGGING_EVENTS_H_
#define CHROME_COMMON_NTP_LOGGING_EVENTS_H_

enum NTPLoggingEventType {
  
  NTP_SERVER_SIDE_SUGGESTION = 0,

  
  NTP_CLIENT_SIDE_SUGGESTION = 1,

  
  
  NTP_TILE = 2,

  
  NTP_THUMBNAIL_TILE = 3,

  
  
  NTP_GRAY_TILE = 4,

  
  NTP_EXTERNAL_TILE = 5,

  
  
  NTP_THUMBNAIL_ERROR = 6,

  
  NTP_GRAY_TILE_FALLBACK = 7,

  
  NTP_EXTERNAL_TILE_FALLBACK = 8,

  
  NTP_MOUSEOVER = 9,

  NTP_NUM_EVENT_TYPES
};

#endif  
