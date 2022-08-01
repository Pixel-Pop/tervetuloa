#include <3ds.h>

Result APT_GetPreparationState(u8* state);

Result APT_SetPreparationState(u8 state);

Result APT_PrepareToStartApplication(u64 programId, FS_MediaType mediaType, u8 flags);

Result APT_StartApplication(bool paused);

Result APT_PrepareToStartNewestHomeMenu();

Result APT_WakeupApplication();

Result APT_OrderToCloseApplication();

Result APT_PrepareToLeaveHomeMenu();

Result APT_LeaveHomeMenu();

Result APT_GetProgramIdOnApplicationJump(u64* currTid, u8* currMediaType, u64* targetTid, u8* targetMediaType);