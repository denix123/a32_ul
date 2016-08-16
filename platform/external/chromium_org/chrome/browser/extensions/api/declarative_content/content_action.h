// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_DECLARATIVE_CONTENT_CONTENT_ACTION_H_
#define CHROME_BROWSER_EXTENSIONS_API_DECLARATIVE_CONTENT_CONTENT_ACTION_H_

#include <string>
#include <vector>

#include "base/memory/ref_counted.h"
#include "chrome/browser/extensions/declarative_user_script_master.h"
#include "extensions/browser/api/declarative/declarative_rule.h"

namespace base {
class Time;
class Value;
}

namespace content {
class BrowserContext;
class WebContents;
}

namespace extensions {
class Extension;

class ContentAction : public base::RefCounted<ContentAction> {
 public:
  
  enum Type {
    ACTION_SHOW_PAGE_ACTION,
    ACTION_REQUEST_CONTENT_SCRIPT,
    ACTION_SET_ICON,
  };

  struct ApplyInfo {
    content::BrowserContext* browser_context;
    content::WebContents* tab;
    int priority;
  };

  ContentAction();

  virtual Type GetType() const = 0;

  
  
  
  
  virtual void Apply(const std::string& extension_id,
                     const base::Time& extension_install_time,
                     ApplyInfo* apply_info) const = 0;
  virtual void Reapply(const std::string& extension_id,
                       const base::Time& extension_install_time,
                       ApplyInfo* apply_info) const = 0;
  virtual void Revert(const std::string& extension_id,
                      const base::Time& extension_install_time,
                      ApplyInfo* apply_info) const = 0;

  
  
  
  
  
  
  static scoped_refptr<ContentAction> Create(
      content::BrowserContext* browser_context,
      const Extension* extension,
      const base::Value& json_action,
      std::string* error,
      bool* bad_message);

  
  static void ResetErrorData(std::string* error, bool* bad_message) {
    *error = "";
    *bad_message = false;
  }

  
  static bool Validate(const base::Value& json_action,
                       std::string* error,
                       bool* bad_message,
                       const base::DictionaryValue** action_dict,
                       std::string* instance_type);

 protected:
  friend class base::RefCounted<ContentAction>;
  virtual ~ContentAction();
};

class RequestContentScript : public ContentAction {
 public:
  struct ScriptData;

  RequestContentScript(content::BrowserContext* browser_context,
                       const Extension* extension,
                       const ScriptData& script_data);
  RequestContentScript(DeclarativeUserScriptMaster* master,
                       const Extension* extension,
                       const ScriptData& script_data);

  static scoped_refptr<ContentAction> Create(
      content::BrowserContext* browser_context,
      const Extension* extension,
      const base::DictionaryValue* dict,
      std::string* error,
      bool* bad_message);

  static scoped_refptr<ContentAction> CreateForTest(
      DeclarativeUserScriptMaster* master,
      const Extension* extension,
      const base::Value& json_action,
      std::string* error,
      bool* bad_message);

  static bool InitScriptData(const base::DictionaryValue* dict,
                             std::string* error,
                             bool* bad_message,
                             ScriptData* script_data);

  
  virtual Type GetType() const OVERRIDE;

  virtual void Apply(const std::string& extension_id,
                     const base::Time& extension_install_time,
                     ApplyInfo* apply_info) const OVERRIDE;

  virtual void Reapply(const std::string& extension_id,
                       const base::Time& extension_install_time,
                       ApplyInfo* apply_info) const OVERRIDE;

  virtual void Revert(const std::string& extension_id,
                      const base::Time& extension_install_time,
                      ApplyInfo* apply_info) const OVERRIDE;

 private:
  void InitScript(const Extension* extension, const ScriptData& script_data);

  void AddScript() {
    DCHECK(master_);
    master_->AddScript(script_);
  }

  virtual ~RequestContentScript();

  void InstructRenderProcessToInject(content::WebContents* contents,
                                     const std::string& extension_id) const;

  UserScript script_;
  DeclarativeUserScriptMaster* master_;

  DISALLOW_COPY_AND_ASSIGN(RequestContentScript);
};

typedef DeclarativeActionSet<ContentAction> ContentActionSet;

}  

#endif  
