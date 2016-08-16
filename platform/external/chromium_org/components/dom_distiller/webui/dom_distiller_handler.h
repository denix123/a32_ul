// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DOM_DISTILLER_WEBUI_DOM_DISTILLER_HANDLER_H_
#define COMPONENTS_DOM_DISTILLER_WEBUI_DOM_DISTILLER_HANDLER_H_

#include <string>

#include "base/memory/weak_ptr.h"
#include "base/values.h"
#include "content/public/browser/web_ui_message_handler.h"

namespace dom_distiller {

class DomDistillerService;

class DomDistillerHandler : public content::WebUIMessageHandler {
 public:
  
  DomDistillerHandler(DomDistillerService* service, const std::string& scheme);
  virtual ~DomDistillerHandler();

  
  virtual void RegisterMessages() OVERRIDE;

  
  
  
  void HandleRequestEntries(const base::ListValue* args);

  
  
  void HandleAddArticle(const base::ListValue* args);

  
  
  
  void HandleSelectArticle(const base::ListValue* args);

  
  
  void HandleViewUrl(const base::ListValue* args);

 private:
  
  void OnArticleAdded(bool article_available);

  
  DomDistillerService* service_;

  
  std::string article_scheme_;

  
  base::WeakPtrFactory<DomDistillerHandler> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(DomDistillerHandler);
};

}  

#endif  
