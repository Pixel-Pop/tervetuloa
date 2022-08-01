#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>

#include "application.h"

void waitRegistration(NS_APPID appId, bool unregister) {
	bool registered = false;
	APT_IsRegistered(appId, &registered);
	while (registered == unregister) {
		svcSleepThread(10000000);
		APT_IsRegistered(appId, &registered);
	}
}

Result startApp(u64 tid, FS_MediaType mediaType, bool wakeup) {
	Result ret = 0;

	APT_UnlockTransition(0x40);

	printf("PrepareToStart: %lx\n", ret = APT_PrepareToStartApplication(tid, mediaType, !wakeup));
	if (R_FAILED(ret)) return ret;

	GSPGPU_SaveVramSysArea();
	GSPGPU_ReleaseRight();

	printf("Start: %lx\n", ret = APT_StartApplication(wakeup));
	if (R_FAILED(ret)) return ret;

	waitRegistration(APPID_APPLICATION, false);

	if (wakeup) {
		printf("Wakeup: %lx\n", ret = APT_WakeupApplication());
		if (R_FAILED(ret)) return ret;
	}

	APT_NotifyToWait(APPID_APPLICATION);

	printf("AppletUtility: %lx\n", APT_SleepIfShellClosed());
	return ret;
}

Result launchApp(u64 tid, FS_MediaType mediaType, bool wakeup) {
	Result ret = 0;

	bool registered = false;
	printf("IsRegistered: %lx\n", ret = APT_IsRegistered(APPID_APPLICATION, &registered));
	if (R_FAILED(ret)) return ret;

	if (registered) { // Need to close prior application.
		printf("OrderToCloseApplication: %lx\n", ret = APT_OrderToCloseApplication());
		if (R_FAILED(ret)) return ret;

		waitRegistration(APPID_APPLICATION, true);

		aptWaitForWakeUp(TR_JUMPTOMENU);
	}

	return startApp(tid, mediaType, wakeup);
}

Result resumeApp() {
	Result ret = 0;

	bool registered = false;
	printf("IsRegistered: %lx\n", ret = APT_IsRegistered(APPID_APPLICATION, &registered));
	if (R_FAILED(ret)) return ret;

	if (registered) {
		printf("PrepareToLeaveHomeMenu: %lx\n", ret = APT_PrepareToLeaveHomeMenu());
		if (R_FAILED(ret)) return ret;

		GSPGPU_SaveVramSysArea();
		GSPGPU_ReleaseRight();

		printf("LeaveHomeMenu %lx\n", ret = APT_LeaveHomeMenu());
		if (R_FAILED(ret)) return ret;
	}

	return ret;
}

Result jumpApp() {
	u64 currTid;
	u8 currMediaType;
	u64 targetTid;
	u8 targetMediaType;

	APT_GetProgramIdOnApplicationJump(&currTid, &currMediaType, &targetTid, &targetMediaType);
	return startApp(targetTid, targetMediaType, false);
}