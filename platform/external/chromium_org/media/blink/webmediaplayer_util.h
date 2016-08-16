// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BLINK_WEBMEDIAPLAYER_UTIL_H_
#define MEDIA_BLINK_WEBMEDIAPLAYER_UTIL_H_

#include "base/time/time.h"
#include "media/base/media_export.h"
#include "media/base/pipeline_status.h"
#include "media/base/ranges.h"
#include "third_party/WebKit/public/platform/WebMediaPlayer.h"
#include "third_party/WebKit/public/platform/WebTimeRange.h"
#include "url/gurl.h"

namespace media {

base::TimeDelta MEDIA_EXPORT ConvertSecondsToTimestamp(double seconds);

blink::WebTimeRanges MEDIA_EXPORT ConvertToWebTimeRanges(
    const Ranges<base::TimeDelta>& ranges);

blink::WebMediaPlayer::NetworkState MEDIA_EXPORT PipelineErrorToNetworkState(
    PipelineStatus error);

void MEDIA_EXPORT ReportMediaSchemeUma(const GURL& url);

}  

#endif  
