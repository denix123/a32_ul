#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include "android/kvm.h"
#include "android/utils/debug.h"

#define D(...) VERBOSE_PRINT(init,__VA_ARGS__)


#ifndef __linux__
#error "This file should only be compiled under linux"
#endif

int
kvm_check_allowed(void)
{

    char* kvm_device = getenv(KVM_DEVICE_NAME_ENV);
    if (NULL == kvm_device) {
      kvm_device = "/dev/kvm";
    }
    
    if (access(kvm_device,F_OK)) {
        
        D("No kvm device file detected");
        return 0;
    }

    
    if (access(kvm_device,R_OK)) {
        D("KVM device file is not readable for this user.");
        return 0;
    }

    D("KVM mode auto-enabled!");
    return 1;
}

