// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef CHROME_BROWSER_EXTENSIONS_API_MEDIA_GALLERIES_PRIVATE_MEDIA_GALLERIES_PRIVATE_EVENT_ROUTER_H_
#define CHROME_BROWSER_EXTENSIONS_API_MEDIA_GALLERIES_PRIVATE_MEDIA_GALLERIES_PRIVATE_EVENT_ROUTER_H_

#include <set>
#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/media_galleries/media_galleries_preferences.h"

class Profile;

namespace base {
class ListValue;
}

namespace extensions {

class MediaGalleriesPrivateEventRouter
    : public base::SupportsWeakPtr<MediaGalleriesPrivateEventRouter> {
 public:
  explicit MediaGalleriesPrivateEventRouter(Profile* profile);
  virtual ~MediaGalleriesPrivateEventRouter();

  
  void OnGalleryChanged(MediaGalleryPrefId gallery_id,
                        const std::set<std::string>& extension_ids);

 private:
  
  Profile* profile_;

  DISALLOW_COPY_AND_ASSIGN(MediaGalleriesPrivateEventRouter);
};

}  

#endif  
