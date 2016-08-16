// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SEARCH_SUGGESTIONS_SUGGESTIONS_SOURCE_H_
#define CHROME_BROWSER_SEARCH_SUGGESTIONS_SUGGESTIONS_SOURCE_H_

#include <map>
#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/weak_ptr.h"
#include "components/suggestions/proto/suggestions.pb.h"
#include "content/public/browser/url_data_source.h"
#include "url/gurl.h"

class Profile;
class SkBitmap;

namespace base {
class RefCountedMemory;
}  

namespace suggestions {

class SuggestionsSource : public content::URLDataSource {
 public:
  explicit SuggestionsSource(Profile* profile);

  
  virtual std::string GetSource() const OVERRIDE;
  virtual void StartDataRequest(
      const std::string& path, int render_process_id, int render_frame_id,
      const content::URLDataSource::GotDataCallback& callback) OVERRIDE;
  virtual std::string GetMimeType(const std::string& path) const OVERRIDE;
  virtual base::MessageLoop* MessageLoopForRequestPath(
      const std::string& path) const OVERRIDE;

 private:
  virtual ~SuggestionsSource();

  
  struct RequestContext {
    RequestContext(
        const suggestions::SuggestionsProfile& suggestions_profile_in,
        const content::URLDataSource::GotDataCallback& callback_in);
    ~RequestContext();

    const suggestions::SuggestionsProfile suggestions_profile;
    const content::URLDataSource::GotDataCallback callback;
    std::map<GURL, std::string> base64_encoded_pngs;
  };

  
  void OnSuggestionsAvailable(
      const content::URLDataSource::GotDataCallback& callback,
      const SuggestionsProfile& suggestions_profile);

  
  void OnThumbnailAvailable(RequestContext* context, base::Closure barrier,
                            const GURL& url, const SkBitmap* bitmap);

  
  
  void OnThumbnailsFetched(RequestContext* context);

  
  Profile* const profile_;

  
  base::WeakPtrFactory<SuggestionsSource> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(SuggestionsSource);
};

}  

#endif  
