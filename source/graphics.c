#include <3ds.h>
#include <citro2d.h>
#include <stdio.h>

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

C3D_RenderTarget* top;

u32 clrWhite, clrGreen, clrRed, clrBlue;
u32 clrCircle1, clrCircle2, clrCircle3;
u32 clrSolidCircle;
u32 clrTri1, clrTri2;
u32 clrRec1, clrRec2, clrRec3, clrRec4;
u32 clrClear;

void graphicsInit() {
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	// Create screens
	top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

	// Create colors
	clrWhite = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
	clrGreen = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
	clrRed = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
	clrBlue = C2D_Color32(0x00, 0x00, 0xFF, 0xFF);

	clrCircle1 = C2D_Color32(0xFF, 0x00, 0xFF, 0xFF);
	clrCircle2 = C2D_Color32(0xFF, 0xFF, 0x00, 0xFF);
	clrCircle3 = C2D_Color32(0x00, 0xFF, 0xFF, 0xFF);

	clrSolidCircle = C2D_Color32(0x68, 0xB0, 0xD8, 0xFF);

	clrTri1 = C2D_Color32(0xFF, 0x15, 0x00, 0xFF);
	clrTri2 = C2D_Color32(0x27, 0x69, 0xE5, 0xFF);

	clrRec1 = C2D_Color32(0x9A, 0x6C, 0xB9, 0xFF);
	clrRec2 = C2D_Color32(0xFF, 0xFF, 0x2C, 0xFF);
	clrRec3 = C2D_Color32(0xD8, 0xF6, 0x0F, 0xFF);
	clrRec4 = C2D_Color32(0x40, 0xEA, 0x87, 0xFF);

	clrClear = C2D_Color32(0xFF, 0xD8, 0xB0, 0x68);
}

void graphicsUpdate() {
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	//C2D_TargetClear(top, clrClear);
	C2D_SceneBegin(top);

	C2D_DrawTriangle(50 / 2, SCREEN_HEIGHT - 50, clrWhite,
		0, SCREEN_HEIGHT, clrTri1,
		50, SCREEN_HEIGHT, clrTri2, 0);
	C2D_DrawRectangle(SCREEN_WIDTH - 50, 0, 0, 50, 50, clrRec1, clrRec2, clrRec3, clrRec4);

	// Circles require a state change (an expensive operation) within citro2d's internals, so draw them last.
	// Although it is possible to draw them in the middle of drawing non-circular objects
	// (sprites, images, triangles, rectangles, etc.) this is not recommended. They should either
	// be drawn before all non-circular objects, or afterwards.
	C2D_DrawEllipse(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, clrCircle1, clrCircle2, clrCircle3, clrWhite);
	C2D_DrawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 50, clrCircle3, clrWhite, clrCircle1, clrCircle2);
	C2D_DrawCircle(25, 25, 0, 25,
		clrRed, clrBlue, clrGreen, clrWhite);
	C2D_DrawCircleSolid(SCREEN_WIDTH - 25, SCREEN_HEIGHT - 25, 0, 25, clrSolidCircle);
	C3D_FrameEnd(0);
}

void graphicsFini() {
	C2D_Fini();
	C3D_Fini();
}