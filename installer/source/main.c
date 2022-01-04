// Note: I use Scene-Collective/ps4-payload-sdk 
#include "ps4.h"


// FreeBSD <sys/mount.h> set value
// should probably actually import the proper freebsd header

#define	MNT_UPDATE	0x0000000000010000ULL /* not real mount, just update */

int getUsbMountIndex() {
    char targetPath[128];
    memset(targetPath, 0, sizeof(targetPath));
    int usbId = -1;
    int failedCount = 0;
    while (1) {
        for(int i = 0; i < 8; i++) {
            sprintf(targetPath, "/mnt/usb%i/data/daemons/installer/eboot.bin", i);
            int fd = open(targetPath, O_RDONLY, 0644);
            close(fd);
            if (fd > 0) {
                usbId = i;
                goto exit;
            }
        }
        failedCount++;
        if (failedCount >= 5) {
            break;
        }
        sceKernelSleep(1);
    }

exit:
    return usbId;

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
        int usbIndex = getUsbMountIndex();
        if (usbIndex == -1) {
            printf_notification("Fail to find usb.");
            break;
        } else {
            printf_notification("Found match at  /mnt/usb%i/", usbIndex);
        }
    } while (0);

    return 0;
}