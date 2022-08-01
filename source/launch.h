#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>

#define SYSMODULE 0x00040130ULL << 32

void launchTitles() {
	u32 temp;
	NS_LaunchTitle(SYSMODULE | 0x1D02, 0, &temp); // hid
	NS_LaunchTitle(SYSMODULE | 0x1802, 0, &temp); // codec
	NS_LaunchTitle(SYSMODULE | 0x1A02, 0, &temp); // dsp
	NS_LaunchTitle(SYSMODULE | 0x1502, 0, &temp); // am
	NS_LaunchTitle(SYSMODULE | 0x1C02, 0, &temp); // gsp
}

void launchTitles2() {
	u32 temp;
	NS_LaunchTitle(SYSMODULE | 0x2702, 0, &temp); // csnd
	NS_LaunchTitle(SYSMODULE | 0x1602, 0, &temp); // camera
	NS_LaunchTitle(SYSMODULE | 0x2002, 0, &temp); // mic
	NS_LaunchTitle(SYSMODULE | 0x3302, 0, &temp); // ir
	NS_LaunchTitle(SYSMODULE | 0x2D02, 0, &temp); // nwm
	NS_LaunchTitle(SYSMODULE | 0x2E02, 0, &temp); // socket
	NS_LaunchTitle(SYSMODULE | 0x2902, 0, &temp); // http
	NS_LaunchTitle(SYSMODULE | 0x2F02, 0, &temp); // ssl
	NS_LaunchTitle(SYSMODULE | 0x2602, 0, &temp); // cecd
	NS_LaunchTitle(SYSMODULE | 0x2402, 0, &temp); // ac
	NS_LaunchTitle(SYSMODULE | 0x3202, 0, &temp); // friends
	NS_LaunchTitle(SYSMODULE | 0x3402, 0, &temp); // boss
	NS_LaunchTitle(SYSMODULE | 0x3802, 0, &temp); // act
}

void launchTitles3() {
	u32 temp;
	NS_LaunchTitle(SYSMODULE | 0x3502, 0, &temp); // news
	NS_LaunchTitle(SYSMODULE | 0x2B02, 0, &temp); // ndm
	NS_LaunchTitle(SYSMODULE | 0x2C02, 0, &temp); // nim
	NS_LaunchTitle(SYSMODULE | 0x2802, 0, &temp); // dlp
}

Result startApp(u64 tid, FS_MediaType mediaType, bool wakeup);

Result launchApp(u64 tid, FS_MediaType mediaType, bool wakeup);

Result resumeApp();

Result jumpApp();
