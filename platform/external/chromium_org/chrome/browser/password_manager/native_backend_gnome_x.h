// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PASSWORD_MANAGER_NATIVE_BACKEND_GNOME_X_H_
#define CHROME_BROWSER_PASSWORD_MANAGER_NATIVE_BACKEND_GNOME_X_H_

#define GNOME_KEYRING_DEPRECATED
#define GNOME_KEYRING_DEPRECATED_FOR(x)
#include <gnome-keyring.h>

#include <string>

#include "base/basictypes.h"
#include "base/time/time.h"
#include "chrome/browser/password_manager/password_store_factory.h"
#include "chrome/browser/password_manager/password_store_x.h"
#include "chrome/browser/profiles/profile.h"

namespace autofill {
struct PasswordForm;
}

class GnomeKeyringLoader {
 protected:
  static bool LoadGnomeKeyring();

#define GNOME_KEYRING_FOR_EACH_MOCKED_FUNC(F)      \
  F(is_available)                                  \
  F(store_password)                                \
  F(delete_password)                               \
  F(find_items)                                    \
  F(result_to_message)
#define GNOME_KEYRING_FOR_EACH_NON_MOCKED_FUNC(F)  \
  F(attribute_list_free)                           \
  F(attribute_list_new)                            \
  F(attribute_list_append_string)                  \
  F(attribute_list_append_uint32)
#define GNOME_KEYRING_FOR_EACH_FUNC(F)             \
  GNOME_KEYRING_FOR_EACH_NON_MOCKED_FUNC(F)        \
  GNOME_KEYRING_FOR_EACH_MOCKED_FUNC(F)

#define GNOME_KEYRING_DECLARE_POINTER(name) \
    static typeof(&::gnome_keyring_##name) gnome_keyring_##name;
  GNOME_KEYRING_FOR_EACH_FUNC(GNOME_KEYRING_DECLARE_POINTER)
#undef GNOME_KEYRING_DECLARE_POINTER

  
  static bool keyring_loaded;

 private:
#if defined(DLOPEN_GNOME_KEYRING)
  struct FunctionInfo {
    const char* name;
    void** pointer;
  };

  
  static const FunctionInfo functions[];
#endif  
};

class NativeBackendGnome : public PasswordStoreX::NativeBackend,
                           public GnomeKeyringLoader {
 public:
  explicit NativeBackendGnome(LocalProfileId id);

  virtual ~NativeBackendGnome();

  virtual bool Init() OVERRIDE;

  
  virtual password_manager::PasswordStoreChangeList AddLogin(
      const autofill::PasswordForm& form) OVERRIDE;
  virtual bool UpdateLogin(
      const autofill::PasswordForm& form,
      password_manager::PasswordStoreChangeList* changes) OVERRIDE;
  virtual bool RemoveLogin(const autofill::PasswordForm& form) OVERRIDE;
  virtual bool RemoveLoginsCreatedBetween(
      base::Time delete_begin,
      base::Time delete_end,
      password_manager::PasswordStoreChangeList* changes) OVERRIDE;
  virtual bool RemoveLoginsSyncedBetween(
      base::Time delete_begin,
      base::Time delete_end,
      password_manager::PasswordStoreChangeList* changes) OVERRIDE;
  virtual bool GetLogins(const autofill::PasswordForm& form,
                         PasswordFormList* forms) OVERRIDE;
  virtual bool GetAutofillableLogins(PasswordFormList* forms) OVERRIDE;
  virtual bool GetBlacklistLogins(PasswordFormList* forms) OVERRIDE;

 private:
  enum TimestampToCompare {
    CREATION_TIMESTAMP,
    SYNC_TIMESTAMP,
  };

  
  bool RawAddLogin(const autofill::PasswordForm& form);

  
  bool GetLoginsList(PasswordFormList* forms, bool autofillable);

  
  bool GetAllLogins(PasswordFormList* forms);

  
  
  bool GetLoginsBetween(base::Time get_begin,
                        base::Time get_end,
                        TimestampToCompare date_to_compare,
                        PasswordFormList* forms);

  
  
  bool RemoveLoginsBetween(base::Time get_begin,
                           base::Time get_end,
                           TimestampToCompare date_to_compare,
                           password_manager::PasswordStoreChangeList* changes);

  
  std::string GetProfileSpecificAppString() const;

  
  const LocalProfileId profile_id_;

  
  std::string app_string_;

  DISALLOW_COPY_AND_ASSIGN(NativeBackendGnome);
};

#endif  
