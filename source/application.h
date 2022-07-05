#include <3ds.h>

Result APT_GetPreparationState();

Result APT_SetPreparationState();

Result APT_PrepareToStartApplication(u64 programId, FS_MediaType mediaType);

Result APT_StartApplication();

Result APT_WakeupApplication();

Result APT_PrepareToStartNewestHomeMenu();