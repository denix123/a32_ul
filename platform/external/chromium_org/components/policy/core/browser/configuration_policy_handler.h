// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_POLICY_CORE_BROWSER_CONFIGURATION_POLICY_HANDLER_H_
#define COMPONENTS_POLICY_CORE_BROWSER_CONFIGURATION_POLICY_HANDLER_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/values.h"
#include "components/policy/core/common/schema.h"
#include "components/policy/policy_export.h"

class PrefValueMap;

namespace policy {

class PolicyErrorMap;
struct PolicyHandlerParameters;
class PolicyMap;

struct POLICY_EXPORT PolicyToPreferenceMapEntry {
  const char* const policy_name;
  const char* const preference_path;
  const base::Value::Type value_type;
};

class POLICY_EXPORT ConfigurationPolicyHandler {
 public:
  static std::string ValueTypeToString(base::Value::Type type);

  ConfigurationPolicyHandler();
  virtual ~ConfigurationPolicyHandler();

  
  
  
  
  virtual bool CheckPolicySettings(const PolicyMap& policies,
                                   PolicyErrorMap* errors) = 0;

  
  
  virtual void ApplyPolicySettingsWithParameters(
      const PolicyMap& policies,
      const PolicyHandlerParameters& parameters,
      PrefValueMap* prefs);

  
  
  
  
  virtual void ApplyPolicySettings(const PolicyMap& policies,
                                   PrefValueMap* prefs);

  
  
  
  virtual void PrepareForDisplaying(PolicyMap* policies) const;

 private:
  DISALLOW_COPY_AND_ASSIGN(ConfigurationPolicyHandler);
};

class POLICY_EXPORT TypeCheckingPolicyHandler
    : public ConfigurationPolicyHandler {
 public:
  TypeCheckingPolicyHandler(const char* policy_name,
                            base::Value::Type value_type);
  virtual ~TypeCheckingPolicyHandler();

  
  virtual bool CheckPolicySettings(const PolicyMap& policies,
                                   PolicyErrorMap* errors) OVERRIDE;

  const char* policy_name() const;

 protected:
  
  bool CheckAndGetValue(const PolicyMap& policies,
                        PolicyErrorMap* errors,
                        const base::Value** value);

 private:
  
  const char* policy_name_;

  
  base::Value::Type value_type_;

  DISALLOW_COPY_AND_ASSIGN(TypeCheckingPolicyHandler);
};

class POLICY_EXPORT IntRangePolicyHandlerBase
    : public TypeCheckingPolicyHandler {
 public:
  IntRangePolicyHandlerBase(const char* policy_name,
                            int min,
                            int max,
                            bool clamp);

  
  virtual bool CheckPolicySettings(const PolicyMap& policies,
                                   PolicyErrorMap* errors) OVERRIDE;

 protected:
  virtual ~IntRangePolicyHandlerBase();

  
  
  
  bool EnsureInRange(const base::Value* input,
                     int* output,
                     PolicyErrorMap* errors);

 private:
  
  int min_;

  
  int max_;

  
  
  bool clamp_;

  DISALLOW_COPY_AND_ASSIGN(IntRangePolicyHandlerBase);
};

class POLICY_EXPORT SimplePolicyHandler : public TypeCheckingPolicyHandler {
 public:
  SimplePolicyHandler(const char* policy_name,
                      const char* pref_path,
                      base::Value::Type value_type);
  virtual ~SimplePolicyHandler();

  
  virtual void ApplyPolicySettings(const PolicyMap& policies,
                                   PrefValueMap* prefs) OVERRIDE;

 private:
  
  const char* pref_path_;

  DISALLOW_COPY_AND_ASSIGN(SimplePolicyHandler);
};

class POLICY_EXPORT StringMappingListPolicyHandler
    : public TypeCheckingPolicyHandler {
 public:
  
  
  class POLICY_EXPORT MappingEntry {
   public:
    MappingEntry(const char* policy_value, scoped_ptr<base::Value> map);
    ~MappingEntry();

    const char* enum_value;
    scoped_ptr<base::Value> mapped_value;
  };

  
  typedef base::Callback<void(ScopedVector<MappingEntry>*)> GenerateMapCallback;

  StringMappingListPolicyHandler(const char* policy_name,
                                 const char* pref_path,
                                 const GenerateMapCallback& map_generator);
  virtual ~StringMappingListPolicyHandler();

  
  virtual bool CheckPolicySettings(const PolicyMap& policies,
                                   PolicyErrorMap* errors) OVERRIDE;
  virtual void ApplyPolicySettings(const PolicyMap& policies,
                                   PrefValueMap* prefs) OVERRIDE;

 private:
  
  
  bool Convert(const base::Value* input,
               base::ListValue* output,
               PolicyErrorMap* errors);

  
  
  scoped_ptr<base::Value> Map(const std::string& entry_value);

  
  const char* pref_path_;

  
  GenerateMapCallback map_getter_;

  
  
  ScopedVector<MappingEntry> map_;

  DISALLOW_COPY_AND_ASSIGN(StringMappingListPolicyHandler);
};

class POLICY_EXPORT IntRangePolicyHandler : public IntRangePolicyHandlerBase {
 public:
  IntRangePolicyHandler(const char* policy_name,
                        const char* pref_path,
                        int min,
                        int max,
                        bool clamp);
  virtual ~IntRangePolicyHandler();

  
  virtual void ApplyPolicySettings(const PolicyMap& policies,
                                   PrefValueMap* prefs) OVERRIDE;

 private:
  
  const char* pref_path_;

  DISALLOW_COPY_AND_ASSIGN(IntRangePolicyHandler);
};

class POLICY_EXPORT IntPercentageToDoublePolicyHandler
    : public IntRangePolicyHandlerBase {
 public:
  IntPercentageToDoublePolicyHandler(const char* policy_name,
                                     const char* pref_path,
                                     int min,
                                     int max,
                                     bool clamp);
  virtual ~IntPercentageToDoublePolicyHandler();

  
  virtual void ApplyPolicySettings(const PolicyMap& policies,
                                   PrefValueMap* prefs) OVERRIDE;

 private:
  
  const char* pref_path_;

  DISALLOW_COPY_AND_ASSIGN(IntPercentageToDoublePolicyHandler);
};

class POLICY_EXPORT SchemaValidatingPolicyHandler
    : public ConfigurationPolicyHandler {
 public:
  SchemaValidatingPolicyHandler(const char* policy_name,
                                Schema schema,
                                SchemaOnErrorStrategy strategy);
  virtual ~SchemaValidatingPolicyHandler();

  
  virtual bool CheckPolicySettings(const PolicyMap& policies,
                                   PolicyErrorMap* errors) OVERRIDE;

  const char* policy_name() const;

 protected:
  
  bool CheckAndGetValue(const PolicyMap& policies,
                        PolicyErrorMap* errors,
                        scoped_ptr<base::Value>* output);

 private:
  const char* policy_name_;
  Schema schema_;
  SchemaOnErrorStrategy strategy_;

  DISALLOW_COPY_AND_ASSIGN(SchemaValidatingPolicyHandler);
};

class POLICY_EXPORT SimpleSchemaValidatingPolicyHandler
    : public SchemaValidatingPolicyHandler {
 public:
  enum MandatoryPermission { MANDATORY_ALLOWED, MANDATORY_PROHIBITED };
  enum RecommendedPermission { RECOMMENDED_ALLOWED, RECOMMENDED_PROHIBITED };

  SimpleSchemaValidatingPolicyHandler(
      const char* policy_name,
      const char* pref_path,
      Schema schema,
      SchemaOnErrorStrategy strategy,
      RecommendedPermission recommended_permission,
      MandatoryPermission mandatory_permission);
  virtual ~SimpleSchemaValidatingPolicyHandler();

  
  virtual bool CheckPolicySettings(const PolicyMap& policies,
                                   PolicyErrorMap* errors) OVERRIDE;
  virtual void ApplyPolicySettings(const PolicyMap& policies,
                                   PrefValueMap* prefs) OVERRIDE;

 private:
  const char* pref_path_;
  const bool allow_recommended_;
  const bool allow_mandatory_;

  DISALLOW_COPY_AND_ASSIGN(SimpleSchemaValidatingPolicyHandler);
};

class POLICY_EXPORT LegacyPoliciesDeprecatingPolicyHandler
    : public ConfigurationPolicyHandler {
 public:
  LegacyPoliciesDeprecatingPolicyHandler(
      ScopedVector<ConfigurationPolicyHandler> legacy_policy_handlers,
      scoped_ptr<SchemaValidatingPolicyHandler> new_policy_handler);
  virtual ~LegacyPoliciesDeprecatingPolicyHandler();

  
  virtual bool CheckPolicySettings(const PolicyMap& policies,
                                   PolicyErrorMap* errors) OVERRIDE;
  virtual void ApplyPolicySettings(const PolicyMap& policies,
                                   PrefValueMap* prefs) OVERRIDE;

 private:
  ScopedVector<ConfigurationPolicyHandler> legacy_policy_handlers_;
  scoped_ptr<SchemaValidatingPolicyHandler> new_policy_handler_;

  DISALLOW_COPY_AND_ASSIGN(LegacyPoliciesDeprecatingPolicyHandler);
};

}  

#endif  
