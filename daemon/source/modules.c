#include "modules.h"

int loadInternalModules() {
    
    sceSysmoduleLoadModuleInternal(ORBIS_SYSMODULE_INTERNAL_SYSTEM_SERVICE);
    sceSysmoduleLoadModuleInternal(ORBIS_SYSMODULE_INTERNAL_USER_SERVICE);
	sceSysmoduleLoadModuleInternal(ORBIS_SYSMODULE_INTERNAL_SYSCORE);
	sceSysmoduleLoadModuleInternal(ORBIS_SYSMODULE_INTERNAL_BGFT);  
	sceSysmoduleLoadModuleInternal(ORBIS_SYSMODULE_INTERNAL_APP_INST_UTIL); 
    return 0;
}



int loadLibjbc() {
    int libjbc = sceKernelLoadStartModule(DAEMON_PATH "/sce_module/libjbc.sprx", 0, NULL, 0,0, 0);
    if (libjbc == 0) {
        sceKernelDebugOutText(0, "Failed to load libjbc.sprx\n");
        return -1;
    } else {
        sceKernelDebugOutText(0, "Successfully loaded libjbc.sprx\n");
    }
    
    sceKernelDlsym(libjbc, "Jailbreak", (void**)&jailbreak);
    return 0;
}