// Note: I use Scene-Collective/ps4-payload-sdk 
#include "ps4.h"


// FreeBSD <sys/mount.h> set value
// should probably actually import the proper freebsd header

#define	MNT_UPDATE	0x0000000000010000ULL /* not real mount, just update */

#define DAEMON_DIRECTORY "/data/daemons/"
#define DAEMON_TITLE_ID "DAMN00001"
#define true 1 
#define false 0

bool isDaemonDirectoryFound() {
    char targetPath[128];
    memset(targetPath, 0, sizeof(targetPath));
    sprintf(targetPath,DAEMON_DIRECTORY"%s/eboot.bin" , DAEMON_TITLE_ID);
    int fd = open(targetPath, O_RDONLY, 0644);
    if (fd < 0) {
        return true;
    }
    close(fd);
    return false;
}


int _main() {
    initKernel();
    initLibc();

    jailbreak();

    initSysUtil();
    do {
        int ret = mount_large_fs("/dev/da0x4.crypt", "/system", "exfatfs", "511", MNT_UPDATE);
        if (ret < 0) {
            printf_notification("Failed to mount /system for RW. - %08li", ret);
            break;
        } else {
            printf_notification("Successfully mounted /system for RW");
        }

        if (isDaemonDirectoryFound()) {
            printf_notification("Fail to find daemon.");
            break;
        } else {
            printf_notification("Found daemon.");
        }
        
        // Copy to target daemon directory
        char sourcePath[128];
        memset(sourcePath, 0, sizeof(sourcePath));
        sprintf(sourcePath, DAEMON_DIRECTORY"%s", DAEMON_TITLE_ID);

        mkdir("/system/vsh/app/"DAEMON_TITLE_ID"/", 0777);
        copy_dir(sourcePath, "/system/vsh/app/"DAEMON_TITLE_ID);
        printf_notification("Successfully copied files.");
    } while (0);

    return 0;
}