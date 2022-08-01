#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include "launch.h"
#include "application.h"
#include "graphics.h"

#include <citro2d.h>

extern u32 __ctru_heap;
extern u32 __ctru_linear_heap;

void printMem() {
	Result rc = 0;
	// Retrieve handle to the resource limit object for our process
	Handle reslimit = 0;
	rc = svcGetResourceLimit(&reslimit, CUR_PROCESS_HANDLE);
	if (R_FAILED(rc))
		svcBreak(USERBREAK_PANIC);

	// Retrieve information about total/used memory
	s64 maxCommit = 0, currentCommit = 0;
	ResourceLimitType reslimitType = RESLIMIT_COMMIT;
	svcGetResourceLimitLimitValues(&maxCommit, reslimit, &reslimitType, 1); // for APPLICATION this is equal to APPMEMALLOC at all times
	svcGetResourceLimitCurrentValues(&currentCommit, reslimit, &reslimitType, 1);
	svcCloseHandle(reslimit);

	printf("maxCommit: %07llx\n", maxCommit);
	printf("currentCommit: %07llx\n", currentCommit);
	printf("heap start: %07lx\n", __ctru_heap);
	printf("linear start: %07lx\n", __ctru_linear_heap);

	printf("application size: %07lx\n", osGetMemRegionSize(MEMREGION_APPLICATION));
	printf("application used: %07lx\n", osGetMemRegionUsed(MEMREGION_APPLICATION));
	printf("application free: %07lx\n", osGetMemRegionFree(MEMREGION_APPLICATION));
	printf("system size: %07lx\n", osGetMemRegionSize(MEMREGION_SYSTEM));
	printf("system used: %07lx\n", osGetMemRegionUsed(MEMREGION_SYSTEM));
	printf("system free: %07lx\n", osGetMemRegionFree(MEMREGION_SYSTEM));
	printf("base size: %07lx\n", osGetMemRegionSize(MEMREGION_BASE));
	printf("base used: %07lx\n", osGetMemRegionUsed(MEMREGION_BASE));
	printf("base free: %07lx\n", osGetMemRegionFree(MEMREGION_BASE));
	printf("app mem type: %lx\n", *((u32*)0x1FF80030));

	printf("max system region alloc: %lx\n", *((u32*)0x1FF80044));
}

void handleWakeup() {
	APT_Command cmd;
	while (true) {
		cmd = aptWaitForWakeUp(TR_JUMPTOMENU);
		printf("apt cmd: %x\n", cmd);

		switch (cmd) {
		case APTCMD_WAKEUP_EXIT: // Application closed.
			GSPGPU_SetLcdForceBlack(0);
			return;
			break;
		case APTCMD_WAKEUP_PAUSE: // Application paused by pressing home button.
			printf("Press X to resume application.\n");
			return;
			break;
		case APTCMD_WAKEUP_LAUNCHAPP: // Application jumping to another application (such as from titles in FBI).
			jumpApp();
			break;
		default:
			return;
		}
	}
}

int main(int argc, char* argv[])
{
	aptSetHomeAllowed(false);

	nsInit();
	launchTitles();
	launchTitles2();
	hidInit(); // Uses ir:rst
	ptmSysmInit();
	launchTitles3();

	APT_PrepareToStartNewestHomeMenu();
	
	gfxInitDefault();
	consoleInit(GFX_BOTTOM, NULL);

	printMem();

	graphicsInit();
	printf("\nHello, world!\n");
	printf("Press START to exit.\n");
	printf("Press A to start FBI.\n");

	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();

		graphicsUpdate();
		
		u32 kDown = hidKeysDown();

		if (kDown & KEY_START)
			break;

		if (kDown & KEY_A) {
			if (R_SUCCEEDED(launchApp(0x000400000F800100LL, 1, true))) { // FBI
				handleWakeup();
			}
		}
		else if (kDown & KEY_X) {
			if (R_SUCCEEDED(resumeApp())) {
				handleWakeup();
			}
		}
	}

	graphicsFini();
	gfxExit();
	PTMSYSM_ShutdownAsync(0);
	ptmSysmExit();
	return 0;
}
