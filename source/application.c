#include <3ds.h>
#include <stdio.h>

Result APT_GetPreparationState() {
   u32 cmdbuf[16];

   cmdbuf[0] = 0x00130000;

   Result x = aptSendCommand(cmdbuf);
   if (R_SUCCEEDED(x)) {
      printf("state: %lu\n", cmdbuf[2]);
   }

   return x;
}

Result APT_SetPreparationState(u8 preparationState) {
   u32 cmdbuf[16];

   cmdbuf[0] = 0x00140040;
   cmdbuf[1] = preparationState;

   return aptSendCommand(cmdbuf);
}

Result APT_PrepareToStartApplication(u64 programId, FS_MediaType mediaType) {
   u32 cmdbuf[16];

   cmdbuf[0] = 0x00150140;
   cmdbuf[1] = programId & 0xFFFFFFFF;
   cmdbuf[2] = programId >> 32;
   cmdbuf[3] = mediaType;
   cmdbuf[4] = 0;
   cmdbuf[5] = 0;

   return aptSendCommand(cmdbuf);
}

Result APT_StartApplication() {
   u32 cmdbuf[16];

   cmdbuf[0] = 0x001B00C4;
   cmdbuf[1] = 0;
   cmdbuf[2] = 0;
   cmdbuf[3] = 1; // Paused to true (home menu does this)
   cmdbuf[4] = 0 | 2;
   cmdbuf[5] = 0;
   cmdbuf[6] = 0 | 0x802;
   cmdbuf[7] = 0;

   return aptSendCommand(cmdbuf);
}

Result APT_WakeupApplication() {
   u32 cmdbuf[16];

   cmdbuf[0] = 0x001C0000;

   return aptSendCommand(cmdbuf);
}

Result APT_PrepareToStartNewestHomeMenu() {
   u32 cmdbuf[16];

   cmdbuf[0] = 0x001A0000;

   return aptSendCommand(cmdbuf);
}