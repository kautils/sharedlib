#ifndef KAUTIL_SHAREDLIB_SHAREDLIB_H
#define KAUTIL_SHAREDLIB_SHAREDLIB_H

/// @note on windows, some flags of them may be meaningless . currently i not implement yet
extern int rtld_lazy;
extern int rtld_now;
extern int rtld_global;
extern int rtld_local;
extern int rtld_nodelete;
extern int rtld_noload;
extern int rtld_deepbind;


void* kautil_dlopen(const char * path_to_shared_lib,int flags);
void* kautil_dlsym(void * handle, const char *symbol);
int kautil_dlclose(void * handle);

#define __dlopen(path_to_shared_lib,flags) kautil_dlopen(path_to_shared_lib,flags)    /* future =>  load library ex  */
#define __dlsym(hdl,symname) (decltype(symname)*) kautil_dlsym(hdl,#symname)
#define __dlclose(hdl) kautil_dlclose(hdl)

#endif