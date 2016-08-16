// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DOM_DISTILLER_CONTENT_DOM_DISTILLER_VIEWER_SOURCE_H_
#define COMPONENTS_DOM_DISTILLER_CONTENT_DOM_DISTILLER_VIEWER_SOURCE_H_

#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "content/public/browser/url_data_source.h"

namespace dom_distiller {

class DomDistillerServiceInterface;
class DomDistillerViewerSourceTest;
class ViewerHandle;
class ViewRequestDelegate;

class DomDistillerViewerSource : public content::URLDataSource {
 public:
  DomDistillerViewerSource(DomDistillerServiceInterface* dom_distiller_service,
                           const std::string& scheme);
  virtual ~DomDistillerViewerSource();

  class RequestViewerHandle;

  
  virtual std::string GetSource() const OVERRIDE;
  virtual void StartDataRequest(
      const std::string& path,
      int render_process_id,
      int render_frame_id,
      const content::URLDataSource::GotDataCallback& callback) OVERRIDE;
  virtual std::string GetMimeType(const std::string& path) const OVERRIDE;
  virtual bool ShouldServiceRequest(
      const net::URLRequest* request) const OVERRIDE;
  virtual void WillServiceRequest(const net::URLRequest* request,
                                  std::string* path) const OVERRIDE;
  virtual std::string GetContentSecurityPolicyObjectSrc() const OVERRIDE;

 private:
  friend class DomDistillerViewerSourceTest;

  
  std::string scheme_;

  
  
  DomDistillerServiceInterface* dom_distiller_service_;

  DISALLOW_COPY_AND_ASSIGN(DomDistillerViewerSource);
};

}  

#endif  
