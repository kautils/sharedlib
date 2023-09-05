#include "./sharedlib.h"

#if defined(WIN32) || defined(WIN64) || defined(_MSC_VER)

#include <libloaderapi.h>
#include <errhandlingapi.h>

int rtld_lazy = 0;
int rtld_now = 1;
int rtld_global = 2;
int rtld_local = 4;
int rtld_nodelete = 8;
int rtld_noload = 16;
int rtld_deepbind = 32;

void* kautil_dlopen(const char * path_to_shared_lib, int flags) { return LoadLibraryA((char*)path_to_shared_lib); }
void* kautil_dlsym(void * handle, const char *symbol) { return (void *) GetProcAddress(reinterpret_cast<HMODULE>(handle),(char *)symbol); }
int kautil_dlclose(void * handle) { return FreeLibrary(reinterpret_cast<HMODULE>(handle));}
#else

#include <dlfcn.h>
int rtld_lazy = RTLD_LAZY;
int rtld_now = RTLD_NOW;
int rtld_global = RTLD_GLOBAL;
int rtld_local = RTLD_LOCAL;
int rtld_nodelete = RTLD_NODELETE;
int rtld_noload = RTLD_NOLOAD;
int rtld_deepbind = RTLD_DEEPBIND;

void* kautil_dlopen(const char * path_to_shared_lib, int flags) { return dlopen(path_to_shared_lib,flags); }
void* kautil_dlsym(void * handle, const char *symbol) { return (void *) dlsym(handle,(char *)symbol); }
int kautil_dlclose(void * handle) { return dlclose(handle); }

#endif


#ifdef _MSC_VER
#include <iostream>
#else

// !!!!!!!!!!!!!!!!!!!!! never comment out iostream
// !!!!!!!!!!!!!!!!!!!!! static ios_base::Init __ioinit; // lack of this may cause exit(3)
#include <bits/ios_base.h>	// For ios_base declarations.
// !!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!
#endif



int tmain_kautil_sharedlib_static(){
    auto dl = kautil_dlopen("path_to_library",rtld_lazy|rtld_nodelete);
    kautil_dlsym(dl,"some_symbol");
    kautil_dlclose(dl);
    return 0;
}