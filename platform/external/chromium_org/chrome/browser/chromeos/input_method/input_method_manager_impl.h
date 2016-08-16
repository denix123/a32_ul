// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_INPUT_METHOD_INPUT_METHOD_MANAGER_IMPL_H_
#define CHROME_BROWSER_CHROMEOS_INPUT_METHOD_INPUT_METHOD_MANAGER_IMPL_H_

#include <map>
#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/threading/thread_checker.h"
#include "chrome/browser/chromeos/input_method/candidate_window_controller.h"
#include "chrome/browser/chromeos/input_method/input_method_util.h"
#include "chrome/browser/profiles/profile.h"
#include "chromeos/ime/input_method_manager.h"
#include "chromeos/ime/input_method_whitelist.h"

namespace chromeos {
class ComponentExtensionIMEManager;
class ComponentExtensionIMEManagerDelegate;
class InputMethodEngine;
namespace input_method {
class InputMethodDelegate;
class ImeKeyboard;

class InputMethodManagerImpl : public InputMethodManager,
                               public CandidateWindowController::Observer {
 public:
  class StateImpl : public InputMethodManager::State {
   public:
    StateImpl(InputMethodManagerImpl* manager, Profile* profile);

    
    void InitFrom(const StateImpl& other);

    
    bool IsActive() const;

    
    std::string Dump() const;

    
    bool EnableInputMethodImpl(
        const std::string& input_method_id,
        std::vector<std::string>* new_active_input_method_ids) const;

    
    bool InputMethodIsActivated(const std::string& input_method_id) const;

    
    
    
    void SwitchToNextInputMethodInternal(
        const std::vector<std::string>& input_method_ids,
        const std::string& current_input_methodid);

    
    bool MethodAwaitsExtensionLoad(const std::string& input_method_id) const;

    
    virtual scoped_refptr<InputMethodManager::State> Clone() const OVERRIDE;
    virtual void AddInputMethodExtension(
        const std::string& extension_id,
        const InputMethodDescriptors& descriptors,
        InputMethodEngineInterface* instance) OVERRIDE;
    virtual void RemoveInputMethodExtension(
        const std::string& extension_id) OVERRIDE;
    virtual void ChangeInputMethod(const std::string& input_method_id,
                                   bool show_message) OVERRIDE;
    virtual bool EnableInputMethod(
        const std::string& new_active_input_method_id) OVERRIDE;
    virtual void EnableLoginLayouts(
        const std::string& language_code,
        const std::vector<std::string>& initial_layouts) OVERRIDE;
    virtual void EnableLockScreenLayouts() OVERRIDE;
    virtual void GetInputMethodExtensions(
        InputMethodDescriptors* result) OVERRIDE;
    virtual scoped_ptr<InputMethodDescriptors> GetActiveInputMethods()
        const OVERRIDE;
    virtual const std::vector<std::string>& GetActiveInputMethodIds()
        const OVERRIDE;
    virtual const InputMethodDescriptor* GetInputMethodFromId(
        const std::string& input_method_id) const OVERRIDE;
    virtual size_t GetNumActiveInputMethods() const OVERRIDE;
    virtual void SetEnabledExtensionImes(
        std::vector<std::string>* ids) OVERRIDE;
    virtual void SetInputMethodLoginDefault() OVERRIDE;
    virtual void SetInputMethodLoginDefaultFromVPD(
        const std::string& locale,
        const std::string& layout) OVERRIDE;
    virtual bool SwitchToNextInputMethod() OVERRIDE;
    virtual bool SwitchToPreviousInputMethod(
        const ui::Accelerator& accelerator) OVERRIDE;
    virtual bool SwitchInputMethod(const ui::Accelerator& accelerator) OVERRIDE;
    virtual InputMethodDescriptor GetCurrentInputMethod() const OVERRIDE;
    virtual bool ReplaceEnabledInputMethods(
        const std::vector<std::string>& new_active_input_method_ids) OVERRIDE;

    
    Profile* const profile;

    
    InputMethodDescriptor previous_input_method;
    InputMethodDescriptor current_input_method;

    
    std::vector<std::string> active_input_method_ids;

    
    std::string pending_input_method_id;

    
    std::vector<std::string> enabled_extension_imes;

    
    
    std::map<std::string, InputMethodDescriptor> extra_input_methods;

   private:
    InputMethodManagerImpl* const manager_;

   protected:
    friend base::RefCounted<chromeos::input_method::InputMethodManager::State>;
    virtual ~StateImpl();
  };

  
  
  
  InputMethodManagerImpl(scoped_ptr<InputMethodDelegate> delegate,
                         bool enable_extension_loading);
  virtual ~InputMethodManagerImpl();

  
  void SetUISessionState(UISessionState new_ui_session);

  
  virtual UISessionState GetUISessionState() OVERRIDE;
  virtual void AddObserver(InputMethodManager::Observer* observer) OVERRIDE;
  virtual void AddCandidateWindowObserver(
      InputMethodManager::CandidateWindowObserver* observer) OVERRIDE;
  virtual void RemoveObserver(InputMethodManager::Observer* observer) OVERRIDE;
  virtual void RemoveCandidateWindowObserver(
      InputMethodManager::CandidateWindowObserver* observer) OVERRIDE;
  virtual scoped_ptr<InputMethodDescriptors>
      GetSupportedInputMethods() const OVERRIDE;
  virtual void ActivateInputMethodMenuItem(const std::string& key) OVERRIDE;
  virtual bool IsISOLevel5ShiftUsedByCurrentInputMethod() const OVERRIDE;
  virtual bool IsAltGrUsedByCurrentInputMethod() const OVERRIDE;

  virtual ImeKeyboard* GetImeKeyboard() OVERRIDE;
  virtual InputMethodUtil* GetInputMethodUtil() OVERRIDE;
  virtual ComponentExtensionIMEManager*
      GetComponentExtensionIMEManager() OVERRIDE;
  virtual bool IsLoginKeyboard(const std::string& layout) const OVERRIDE;

  virtual bool MigrateInputMethods(
      std::vector<std::string>* input_method_ids) OVERRIDE;

  virtual scoped_refptr<InputMethodManager::State> CreateNewState(
      Profile* profile) OVERRIDE;

  virtual scoped_refptr<InputMethodManager::State> GetActiveIMEState() OVERRIDE;
  virtual void SetState(
      scoped_refptr<InputMethodManager::State> state) OVERRIDE;

  
  void SetCandidateWindowControllerForTesting(
      CandidateWindowController* candidate_window_controller);
  
  void SetImeKeyboardForTesting(ImeKeyboard* keyboard);
  
  void InitializeComponentExtensionForTesting(
      scoped_ptr<ComponentExtensionIMEManagerDelegate> delegate);

 private:
  friend class InputMethodManagerImplTest;

  
  virtual void CandidateClicked(int index) OVERRIDE;
  virtual void CandidateWindowOpened() OVERRIDE;
  virtual void CandidateWindowClosed() OVERRIDE;

  
  
  
  
  void OnScreenLocked();

  
  
  void OnScreenUnlocked();

  
  
  bool ContainsOnlyKeyboardLayout(const std::vector<std::string>& value);

  
  
  void MaybeInitializeCandidateWindowController();

  
  const InputMethodDescriptor* LookupInputMethod(
      const std::string& input_method_id,
      StateImpl* state);

  
  void ChangeInputMethodInternal(const InputMethodDescriptor& descriptor,
                                 bool show_message,
                                 bool notify_menu);

  
  
  void LoadNecessaryComponentExtensions(StateImpl* state);

  
  
  
  void ReconfigureIMFramework(StateImpl* state);

  
  void RecordInputMethodUsage(std::string input_method_id);

  scoped_ptr<InputMethodDelegate> delegate_;

  
  UISessionState ui_session_;

  
  ObserverList<InputMethodManager::Observer> observers_;
  ObserverList<CandidateWindowObserver> candidate_window_observers_;

  scoped_refptr<StateImpl> state_;

  
  
  scoped_ptr<CandidateWindowController> candidate_window_controller_;

  
  
  InputMethodUtil util_;

  
  scoped_ptr<ComponentExtensionIMEManager> component_extension_ime_manager_;

  
  
  scoped_ptr<ImeKeyboard> keyboard_;


  
  bool enable_extension_loading_;

  
  typedef std::map<std::string, InputMethodEngineInterface*> EngineMap;
  EngineMap engine_map_;

  
  
  
  
  
  
  
  
  std::map<std::string, int> stat_id_map_;

  DISALLOW_COPY_AND_ASSIGN(InputMethodManagerImpl);
};

}  
}  

#endif  
