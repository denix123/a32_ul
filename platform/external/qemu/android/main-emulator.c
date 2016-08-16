/* Copyright (C) 2011 The Android Open Source Project
**
** This software is licensed under the terms of the GNU General Public
** License version 2, as published by the Free Software Foundation, and
** may be copied, distributed, and modified under those terms.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
*/


#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <android/utils/compiler.h>
#include <android/utils/host_bitness.h>
#include <android/utils/panic.h>
#include <android/utils/path.h>
#include <android/utils/bufprint.h>
#include <android/utils/win32_cmdline_quote.h>
#include <android/avd/util.h>

int android_verbose;


#define DEBUG 1

#if DEBUG
#  define D(...)  do { if (android_verbose) printf("emulator:" __VA_ARGS__); } while (0)
#else
#  define D(...)  do{}while(0)
#endif

#ifdef _WIN32
#  define DLL_EXTENSION  ".dll"
#elif defined(__APPLE__)
#  define DLL_EXTENSION  ".dylib"
#else
#  define DLL_EXTENSION  ".so"
#endif

#define GLES_EMULATION_LIB    "libOpenglRender" DLL_EXTENSION
#define GLES_EMULATION_LIB64  "lib64OpenglRender" DLL_EXTENSION

static char* getTargetEmulatorPath(const char* progName, const char* avdArch, const int force_32bit);
static char* getSharedLibraryPath(const char* progName, const char* libName);
static void  prependSharedLibraryPath(const char* prefix);

#if defined(_WIN32) && !ANDROID_GCC_PREREQ(4,4)
#  define safe_execv(_filepath,_argv)  execv((_filepath),(const char* const*)(_argv))
#else
#  define safe_execv(_filepath,_argv)  execv((_filepath),(_argv))
#endif

int main(int argc, char** argv)
{
    const char* avdName = NULL;
    char*       avdArch = NULL;
    char*       emulatorPath;
    int         force_32bit = 0;

    const char* debug = getenv("ANDROID_EMULATOR_DEBUG");

    if (debug != NULL && *debug && *debug != '0')
        android_verbose = 1;

    int  nn;
    for (nn = 1; nn < argc; nn++) {
        const char* opt = argv[nn];

        if (!strcmp(opt,"-qemu"))
            break;

        if (!strcmp(opt,"-verbose") || !strcmp(opt,"-debug-all")) {
            android_verbose = 1;
        }

        if (!strcmp(opt,"-debug") && nn + 1 < argc &&
            !strcmp(argv[nn + 1], "all")) {
            android_verbose = 1;
        }

        if (!strcmp(opt,"-force-32bit")) {
            force_32bit = 1;
            continue;
        }

        if (!avdName) {
            if (!strcmp(opt,"-avd") && nn+1 < argc) {
                avdName = argv[nn+1];
            }
            else if (opt[0] == '@' && opt[1] != '\0') {
                avdName = opt+1;
            }
        }
    }

    if (avdName != NULL) {
        D("Found AVD name '%s'\n", avdName);
        avdArch = path_getAvdTargetArch(avdName);
        D("Found AVD target architecture: %s\n", avdArch);
    } else {
        
        const char* androidOut = getenv("ANDROID_PRODUCT_OUT");

        if (androidOut != NULL) {
            D("Found ANDROID_PRODUCT_OUT: %s\n", androidOut);
            avdArch = path_getBuildTargetArch(androidOut);
            D("Found build target architecture: %s\n",
              avdArch ? avdArch : "<NULL>");
        }
    }

    if (avdArch == NULL) {
        avdArch = "arm";
        D("Can't determine target AVD architecture: defaulting to %s\n", avdArch);
    }

    
    emulatorPath = getTargetEmulatorPath(argv[0], avdArch, force_32bit);
    D("Found target-specific emulator binary: %s\n", emulatorPath);

    
    argv[0] = emulatorPath;

    {
        char*  sharedLibPath = getSharedLibraryPath(emulatorPath, GLES_EMULATION_LIB);

        if (!sharedLibPath) {
            
            
            sharedLibPath = getSharedLibraryPath(emulatorPath, GLES_EMULATION_LIB64);
        }

        if (sharedLibPath != NULL) {
            D("Found OpenGLES emulation libraries in %s\n", sharedLibPath);
            prependSharedLibraryPath(sharedLibPath);
        } else {
            D("Could not find OpenGLES emulation host libraries!\n");
        }
    }

#ifdef _WIN32
    
    
    
    int n;
    for (n = 0; n < argc; ++n) {
        
        
        argv[n] = win32_cmdline_quote(argv[n]);
        D("Quoted param: [%s]\n", argv[n]);
    }
#endif

    
    
    
    safe_execv(emulatorPath, argv);

    
    fprintf(stderr, "Could not launch '%s': %s\n", emulatorPath, strerror(errno));
    return errno;
}

static char*
probeTargetEmulatorPath(const char* progDir,
                        const char* archSuffix,
                        bool search_for_64bit_emulator,
                        bool try_current_path)
{
    char path[PATH_MAX], *pathEnd = path + sizeof(path), *p;

    static const char kEmulatorPrefix[] = "emulator-";
    static const char kEmulator64Prefix[] = "emulator64-";
#ifdef _WIN32
    const char kExeExtension[] = ".exe";
#else
    const char kExeExtension[] = "";
#endif

    
    if (search_for_64bit_emulator) {
        p = path;
        if (progDir) {
            p = bufprint(p, pathEnd, "%s/", progDir);
        }
        p = bufprint(p, pathEnd, "%s%s%s", kEmulator64Prefix,
                        archSuffix, kExeExtension);
        D("Probing program: %s\n", path);
        if (p < pathEnd && path_exists(path)) {
            return strdup(path);
        }
    }

    
    p = path;
    if (progDir) {
        p = bufprint(p, pathEnd, "%s/", progDir);
    }
    p = bufprint(p, pathEnd, "%s%s%s", kEmulatorPrefix,
                    archSuffix, kExeExtension);
    D("Probing program: %s\n", path);
    if (p < pathEnd && path_exists(path)) {
        return strdup(path);
    }

    
    if (try_current_path) {
        char* result;

        if (search_for_64bit_emulator) {
            p = bufprint(path, pathEnd, "%s%s%s", kEmulator64Prefix,
                          archSuffix, kExeExtension);
            if (p < pathEnd) {
                D("Probing path for: %s\n", path);
                result = path_search_exec(path);
                if (result) {
                    return result;
                }
            }
        }

        p = bufprint(path, pathEnd, "%s%s%s", kEmulatorPrefix,
                      archSuffix, kExeExtension);
        if (p < pathEnd) {
            D("Probing path for: %s\n", path);
            result = path_search_exec(path);
            if (result) {
                return result;
            }
        }
    }

    return NULL;
}

static char*
getTargetEmulatorPath(const char* progName,
                      const char* avdArch,
                      const int force_32bit)
{
    char*  progDir;
    char*  result;
#ifdef _WIN32
    bool search_for_64bit_emulator = false;
#else
    bool search_for_64bit_emulator =
            !force_32bit && android_getHostBitness() == 64;
#endif

#ifdef _WIN32
    bool try_current_path =
            (!strchr(progName, '/') && !strchr(progName, '\\'));
#else
    bool try_current_path = !strchr(progName, '/');
#endif

    
    path_split(progName, &progDir, NULL);

    const char* emulatorSuffix;

    
    
    if (!strcmp(avdArch, "x86_64")) {
        emulatorSuffix = "x86_64";

        D("Looking for emulator backend for %s CPU\n", avdArch);

        result = probeTargetEmulatorPath(progDir,
                                         emulatorSuffix,
                                         search_for_64bit_emulator,
                                         try_current_path);
        if (result) {
            return result;
        }
    }

    
    
    if (!strcmp(avdArch, "arm64")) {
        emulatorSuffix = "arm64";

        D("Looking for emulator backend for %s CPU\n", avdArch);

        result = probeTargetEmulatorPath(progDir,
                                         emulatorSuffix,
                                         search_for_64bit_emulator,
                                         try_current_path);
        if (result) {
            return result;
        }
    }

    
    emulatorSuffix = emulator_getBackendSuffix(avdArch);
    if (!emulatorSuffix) {
        APANIC("This emulator cannot emulate %s CPUs!\n", avdArch);
    }
    D("Looking for emulator-%s to emulate '%s' CPU\n", emulatorSuffix,
      avdArch);

    result = probeTargetEmulatorPath(progDir,
                                     emulatorSuffix,
                                     search_for_64bit_emulator,
                                     try_current_path);
    if (result) {
        return result;
    }

    
    APANIC("Missing emulator engine program for '%s' CPUS.\n", avdArch);
    return NULL;
}

static int
probePathForFile(const char* path, const char* filename)
{
    char  temp[PATH_MAX], *p=temp, *end=p+sizeof(temp);
    p = bufprint(temp, end, "%s/%s", path, filename);
    D("Probing for: %s\n", temp);
    return (p < end && path_exists(temp));
}


static char*
getSharedLibraryPath(const char* progName, const char* libName)
{
    char* progDir;
    char* result = NULL;
    char  temp[PATH_MAX], *p=temp, *end=p+sizeof(temp);

    
    path_split(progName, &progDir, NULL);

    if (probePathForFile(progDir, libName)) {
        return progDir;
    }

    {
        p = bufprint(temp, end, "%s/lib", progDir);
        if (p < end && probePathForFile(temp, libName)) {
            result = strdup(temp);
            goto EXIT;
        }
    }

    {
        char* parentDir = path_parent(progDir, 1);

        if (parentDir == NULL) {
            parentDir = strdup(".");
        }
        p = bufprint(temp, end, "%s/lib", parentDir);
        free(parentDir);
        if (p < end && probePathForFile(temp, libName)) {
            result = strdup(temp);
            goto EXIT;
        }
    }

    
EXIT:
    free(progDir);
    return result;
}

static void
prependSharedLibraryPath(const char* prefix)
{
    size_t len = 0;
    char *temp = NULL;
    const char* path = NULL;

#ifdef _WIN32
    path = getenv("PATH");
#else
    path = getenv("LD_LIBRARY_PATH");
#endif

    
    len = 7 + strlen(prefix) + (path ? strlen(path) : 0);
    temp = malloc(len);
    if (!temp)
        return;

    if (path && path[0] != '\0') {
#ifdef _WIN32
        bufprint(temp, temp + len, "PATH=%s;%s", prefix, path);
#else
        bufprint(temp, temp + len, "%s:%s", prefix, path);
#endif
    } else {
#ifdef _WIN32
        bufprint(temp, temp + len, "PATH=%s", prefix);
#else
        strcpy(temp, prefix);
#endif
    }

#ifdef _WIN32
    D("Setting %s\n", temp);
    putenv(strdup(temp));
#else
    D("Setting LD_LIBRARY_PATH=%s\n", temp);
    setenv("LD_LIBRARY_PATH", temp, 1);
#endif
}
