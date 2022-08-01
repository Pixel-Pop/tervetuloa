#include <3ds.h>
#include <stdio.h>

Result APT_GetPreparationState(u8* state) {
   u32 cmdbuf[16];

   cmdbuf[0] = IPC_MakeHeader(0x13,0,0); // 0x130000

   Result ret = aptSendCommand(cmdbuf);
   if (R_SUCCEEDED(ret)) {
      *state = cmdbuf[2];
   }

   return ret;
}

Result APT_SetPreparationState(u8 state) {
   u32 cmdbuf[16];

   cmdbuf[0] = IPC_MakeHeader(0x14,1,0); // 0x140040
   cmdbuf[1] = state;

   return aptSendCommand(cmdbuf);
}

Result APT_PrepareToStartApplication(u64 programId, FS_MediaType mediaType, u8 flags) {
   u32 cmdbuf[16];

   cmdbuf[0] = IPC_MakeHeader(0x15,5,0); // 0x150140
   cmdbuf[1] = programId & 0xFFFFFFFF;
   cmdbuf[2] = programId >> 32;
   cmdbuf[3] = mediaType;
   cmdbuf[4] = 0; // padding
   cmdbuf[5] = flags;

   return aptSendCommand(cmdbuf);
}

Result APT_StartApplication(bool paused) {
   u32 cmdbuf[16];

   cmdbuf[0] = IPC_MakeHeader(0x1B,3,4); // 0x1B00C4
   cmdbuf[1] = 0; // parameter size
   cmdbuf[2] = 0; // hmac size
   cmdbuf[3] = paused; // 1 on initial launch, 0 on jumps.
   cmdbuf[4] = IPC_Desc_StaticBuffer(0, 0);
   cmdbuf[5] = 0; // parameter
   cmdbuf[6] = IPC_Desc_StaticBuffer(0, 2);
   cmdbuf[7] = 0; // hmac

   return aptSendCommand(cmdbuf);
}

Result APT_PrepareToStartNewestHomeMenu() {
   u32 cmdbuf[16];

   cmdbuf[0] = IPC_MakeHeader(0x1A,0,0); // 0x1A0000

   return aptSendCommand(cmdbuf);
}

Result APT_WakeupApplication() {
   u32 cmdbuf[16];

   cmdbuf[0] = IPC_MakeHeader(0x1C,0,0); // 0x1C0000

   return aptSendCommand(cmdbuf);
}

Result APT_OrderToCloseApplication() {
   u32 cmdbuf[16];

   cmdbuf[0] = IPC_MakeHeader(0x21,0,0); // 0x210000

   return aptSendCommand(cmdbuf);
}

Result APT_PrepareToLeaveHomeMenu() {
   u32 cmdbuf[16];

   cmdbuf[0] = IPC_MakeHeader(0x2D,0,0); // 0x2D0000

   return aptSendCommand(cmdbuf);
}

Result APT_LeaveHomeMenu() {
   u32 cmdbuf[16];

   cmdbuf[0] = IPC_MakeHeader(0x2E,1,4); // 0x2E0044
   cmdbuf[1] = 0; 
   cmdbuf[2] = 0;
   cmdbuf[3] = 0;
   cmdbuf[4] = IPC_Desc_StaticBuffer(0, 0);
   cmdbuf[5] = 0;

   return aptSendCommand(cmdbuf);
}

Result APT_GetProgramIdOnApplicationJump(u64* currTid, u8* currMediaType, u64* targetTid, u8* targetMediaType) {
   u32 cmdbuf[16];

   cmdbuf[0] = IPC_MakeHeader(0x33,0,0); // 0x330000

   Result ret = aptSendCommand(cmdbuf);

   if (R_SUCCEEDED(ret)) {
      *currTid = cmdbuf[2] | (u64)cmdbuf[3] << 32;
      *currMediaType = cmdbuf[4];
      *targetTid = cmdbuf[5] | (u64)cmdbuf[6] << 32;
      *targetMediaType = cmdbuf[7];
   }

   return ret;
}
