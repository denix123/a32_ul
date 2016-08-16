// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_DESKTOP_STREAMS_REGISTRY_H_
#define CHROME_BROWSER_MEDIA_DESKTOP_STREAMS_REGISTRY_H_

#include <map>
#include <string>

#include "chrome/browser/media/desktop_media_list.h"
#include "url/gurl.h"

class DesktopStreamsRegistry {
 public:
  DesktopStreamsRegistry();
  ~DesktopStreamsRegistry();

  
  
  
  
  std::string RegisterStream(int render_process_id,
                             int render_frame_id,
                             const GURL& origin,
                             const content::DesktopMediaID& source,
                             const std::string& extension_name);

  
  
  
  
  
  content::DesktopMediaID RequestMediaForStreamId(const std::string& id,
                                                  int render_process_id,
                                                  int render_frame_id,
                                                  const GURL& origin,
                                                  std::string* extension_name);

 private:
  
  struct ApprovedDesktopMediaStream {
    ApprovedDesktopMediaStream();

    int render_process_id;
    int render_frame_id;
    GURL origin;
    content::DesktopMediaID source;
    std::string extension_name;
  };
  typedef std::map<std::string, ApprovedDesktopMediaStream> StreamsMap;

  
  void CleanupStream(const std::string& id);

  StreamsMap approved_streams_;

  DISALLOW_COPY_AND_ASSIGN(DesktopStreamsRegistry);
};

#endif  
