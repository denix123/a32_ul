// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_TEST_INTEGRATION_PASSWORDS_HELPER_H_
#define CHROME_BROWSER_SYNC_TEST_INTEGRATION_PASSWORDS_HELPER_H_

#include <vector>

#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/sync/profile_sync_service.h"
#include "chrome/browser/sync/test/integration/sync_test.h"
#include "components/autofill/core/common/password_form.h"

namespace password_manager {
class PasswordStore;
}

namespace passwords_helper {

void AddLogin(password_manager::PasswordStore* store,
              const autofill::PasswordForm& form);

void UpdateLogin(password_manager::PasswordStore* store,
                 const autofill::PasswordForm& form);

void GetLogins(password_manager::PasswordStore* store,
               std::vector<autofill::PasswordForm>& matches);

void RemoveLogin(password_manager::PasswordStore* store,
                 const autofill::PasswordForm& form);

void RemoveLogins(password_manager::PasswordStore* store);

void SetEncryptionPassphrase(int index,
                             const std::string& passphrase,
                             ProfileSyncService::PassphraseType type);

bool SetDecryptionPassphrase(int index, const std::string& passphrase);

password_manager::PasswordStore* GetPasswordStore(int index);

password_manager::PasswordStore* GetVerifierPasswordStore();

bool ProfileContainsSamePasswordFormsAsVerifier(int index);

bool ProfilesContainSamePasswordForms(int index_a, int index_b);

bool AllProfilesContainSamePasswordFormsAsVerifier();

bool AllProfilesContainSamePasswordForms();

bool AwaitAllProfilesContainSamePasswordForms();

bool AwaitProfileContainsSamePasswordFormsAsVerifier(int index);

int GetPasswordCount(int index);

int GetVerifierPasswordCount();

autofill::PasswordForm CreateTestPasswordForm(int index);

}  

#endif  
