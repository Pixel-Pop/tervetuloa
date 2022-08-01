#include <3ds.h>

u32 __ctru_heap_size = 0x1000000;
u32 __ctru_linear_heap_size = 0x1000000;

void __appInit(void)
{
	// Initialize services
	srvInit();
	aptInit();
}