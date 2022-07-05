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

int main(int argc, char* argv[])
{
	// libctru automatically inits srv and apt
	launchTitles();
	launchTitles2();
	hidInit(); // Uses ir:rst
	ptmSysmInit();
	launchTitles3();

	APT_PrepareToStartNewestHomeMenu();
	
	gfxInitDefault();
	consoleInit(GFX_BOTTOM, NULL);

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

	graphicsInit();
	printf("\nHello, world!\n");
	printf("Press START to exit.\n");
	printf("Press A to start FBI.\n");
	printf("Then, press X to wakeup FBI.\n");

	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();

		graphicsUpdate();
		
		u32 kDown = hidKeysDown();

		if (kDown & KEY_START)
			break;

		if (kDown & KEY_A) {
			printf("PrepareToStart: %lx\n", APT_PrepareToStartApplication(0x000400000F800100LL, 1));
			printf("Start: %lx\n", APT_StartApplication());

		}
		if (kDown & KEY_X) {
			bool registered = false;
			APT_IsRegistered(0x300, &registered);
			if (registered) {
				printf("registered!\n");

				printf("Wakeup: %lx\n", APT_WakeupApplication());
				APT_NotifyToWait(0x300);
				u8 in = 0;
				u8 out = 0;
				printf("AppletUtility: %lx\n", APT_AppletUtility(0x4, &out, 1, &in, 1));
				graphicsFini();
				gfxExit();
			}
			else {
				printf("not registered :(\n");
			}
		}
	}

	graphicsFini();
	gfxExit();
	PTMSYSM_ShutdownAsync(0);
	ptmSysmExit();
	return 0;
}
