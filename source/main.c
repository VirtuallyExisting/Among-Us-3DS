// Simple citro2d untextured shape example
#include <citro2d.h>
#include <3ds.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

//---------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
//---------------------------------------------------------------------------------
	// Init libs
	romfsInit();
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();

	// Create screens
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);



	

	int scene;
	scene = 1;


	const int buttonWidth = 50;
	const int buttonHeight = 50;
	const int buttonX = SCREEN_WIDTH / 2 - buttonWidth / 2; // Top-left X
	const int buttonY = SCREEN_HEIGHT / 2 - buttonHeight / 2; // Top-left Y

	// Create colors
	u32 clrWhite = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
	u32 clrGreen = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
	u32 clrRed   = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
	u32 clrBlue  = C2D_Color32(0x00, 0x00, 0xFF, 0xFF);

	u32 clrRec1 = C2D_Color32(0x9A, 0x6C, 0xB9, 0xFF);
	u32 clrRec2 = C2D_Color32(0xFF, 0xFF, 0x2C, 0xFF);
	u32 clrRec3 = C2D_Color32(0xD8, 0xF6, 0x0F, 0xFF);
	u32 clrRec4 = C2D_Color32(0x40, 0xEA, 0x87, 0xFF);

	u32 clrClear = C2D_Color32(0xFF, 0xD8, 0xB0, 0x68);


	float playerX;
	playerX = 0;
	float playerY;
	playerY = 0;
	float testobjX;
	testobjX = 0;
	float testobjY;
	testobjY = 0;

	C2D_SpriteSheet spriteSheet;
	C2D_Sprite sprite;

	spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
	if (!spriteSheet) svcBreak(USERBREAK_PANIC);

	C2D_SpriteFromImage(&sprite, C2D_SpriteSheetGetImage(spriteSheet, 0));

	C2D_SpriteSetPos(&sprite, 200, 120);


	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();
		touchPosition touch;
		hidTouchRead(&touch);

		






		if (scene == 2) {
			// Respond to user input
			u32 kDown = hidKeysHeld();
			if (kDown & KEY_START)
				break; // break in order to return to hbmenu
			if (kDown & KEY_DRIGHT)
				playerX = playerX + 3;
			if (kDown & KEY_DLEFT)
				playerX = playerX - 3;
			if (kDown & KEY_DDOWN)
				playerY = playerY + 3;
			if (kDown & KEY_DUP)
				playerY = playerY - 3;
		}

		if (scene == 1) {
			    // Check if the screen is being touched AND the touch is inside the button
			if (hidKeysHeld() & KEY_TOUCH &&
				touch.px >= buttonX && touch.px < (buttonX + buttonWidth) &&
				touch.py >= buttonY && touch.py < (buttonY + buttonHeight))
			{
				scene = 2;
				clrGreen = clrBlue;

				
			}

		}
	

			


		// Begin rendering on top screen
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, clrClear);
		C2D_SceneBegin(top);


		if (scene == 2){
			C2D_DrawRectangle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 50, 50, clrRed, clrRed, clrRed, clrRed);
			C2D_DrawRectangle(testobjX - playerX, testobjY - playerY, 0, 50, 50, clrRed, clrRed, clrRed, clrRed);
			C2D_DrawSprite(&sprite);
		}


		// Begin rendering on bottom screen
		C2D_TargetClear(bottom, clrClear);
		C2D_SceneBegin(bottom);

		if (scene == 2){
			
		}
		if (scene == 1){
			C2D_DrawRectangle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 50, 50, clrGreen, clrGreen, clrGreen, clrGreen);
			
		}

		C3D_FrameEnd(0);
		
	}

	// Deinit libs
	C2D_SpriteSheetFree(spriteSheet);
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}
