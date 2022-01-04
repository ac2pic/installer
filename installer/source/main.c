// Note: I use Scene-Collective/ps4-payload-sdk 
#include "ps4.h"


// FreeBSD <sys/mount.h> set value
// should probably actually import the proper freebsd header

#define	MNT_UPDATE	0x0000000000010000ULL /* not real mount, just update */

int _main() {
    initKernel();
    initLibc();

    jailbreak();

    initSysUtil();
    // int ret = mount_large_fs("/dev/da0x4.crypt", "/system", "exfatfs", "511", MNT_UPDATE);
    printf_notification("Test");
    return 0;
}