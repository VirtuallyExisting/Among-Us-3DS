// Simple citro2d untextured shape example
#include <citro2d.h>
#include <3ds.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

#define ANIM_DELAY_FRAMES 6 // If the game is running at 60 FPS then this is equaL to a 0.1 second delay.

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


	const int freeplayWidth = 150;
	const int freeplayHeight = 50;
	const int freeplayX = 100 - freeplayWidth / 2; // Top-left X
	const int freeplayY = 100 - freeplayHeight / 2; // Top-left Y

	// Create colors
	u32 clrWhite = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
	u32 clrGreen = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
	u32 clrRed   = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
	u32 clrBlue  = C2D_Color32(0x00, 0x00, 0xFF, 0xFF);

	u32 clrRec1 = C2D_Color32(0x9A, 0x6C, 0xB9, 0xFF);
	u32 clrRec2 = C2D_Color32(0xFF, 0xFF, 0x2C, 0xFF);
	u32 clrRec3 = C2D_Color32(0xD8, 0xF6, 0x0F, 0xFF);
	u32 clrRec4 = C2D_Color32(0x40, 0xEA, 0x87, 0xFF);

	u32 clrClear = C2D_Color32(0x00, 0x00, 0x00, 0x00);


	float playerX;
	playerX = 0;
	float playerY;
	playerY = 0;

	float playerSpriteX;
	playerSpriteX = playerX + 150;
	float playerSpriteY;
	playerSpriteY = playerY + 100;


	float testobjX;
	testobjX = 0;
	float testobjY;
	testobjY = 0;
	float dummy1x;
	dummy1x = 0;
	float dummy1y;
	dummy1y = 0;
	int dummy1dead;
	dummy1dead = 0;

	int playerAnim;
	playerAnim = 0;

	int playerFrame;
	playerFrame = 0;

	int animCounter = 0;

	C2D_SpriteSheet spriteSheet;
	C2D_Sprite sprite;
	C2D_Sprite freeplaybutton;
	C2D_Sprite dummy1;

	spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
	if (!spriteSheet) svcBreak(USERBREAK_PANIC);

	C2D_SpriteFromImage(&sprite, C2D_SpriteSheetGetImage(spriteSheet, 0));
	C2D_SpriteFromImage(&freeplaybutton, C2D_SpriteSheetGetImage(spriteSheet, 4));
	C2D_SpriteFromImage(&dummy1, C2D_SpriteSheetGetImage(spriteSheet, 0));

	


	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();
		touchPosition touch;
		hidTouchRead(&touch);

		






		if (scene == 2) {
			// Set dummy sprite pos
			C2D_SpriteSetPos(&dummy1, 0 - playerX, 0 - playerY); // subtract x and y positions by player positions in order to cause proper camera offset.


			playerSpriteX = playerX + 150;

			playerSpriteY = playerY + 100;













			// Below is mostly annoyingly complicated, the room above is for simpler functions.
			


			// Respond to user input
			u32 kDown = hidKeysHeld();
			if (kDown & KEY_START)
				break; // break in order to return to hbmenu
			if (kDown & KEY_CPAD_RIGHT)
				playerX = playerX + 3;
			if (kDown & KEY_CPAD_LEFT)
				playerX = playerX - 3;
			if (kDown & KEY_CPAD_DOWN)
				playerY = playerY + 3;
			if (kDown & KEY_CPAD_UP)
				playerY = playerY - 3;
			
			if (kDown & KEY_A) {
				if (sqrt(pow(playerSpriteX - dummy1x, 2) + pow(playerSpriteY - dummy1y, 2)) <= 100.0f) {
					dummy1dead = 1;
				}
			}
				
			
			if (!kDown)
				playerAnim = 0;
			if (kDown & (KEY_CPAD_UP | KEY_CPAD_DOWN | KEY_CPAD_LEFT | KEY_CPAD_RIGHT))
				playerAnim = 1;
			
			if (playerAnim == 0) {
				C2D_SpriteFromImage(&sprite, C2D_SpriteSheetGetImage(spriteSheet, 0));
				C2D_SpriteSetPos(&sprite, 150, 100);
				playerFrame = 0;
			}
			if (playerAnim == 1) {
				animCounter++;

				if (playerFrame == 0) {
					if (animCounter >= ANIM_DELAY_FRAMES) {
						playerFrame++;
						animCounter = 0;
					}
					C2D_SpriteFromImage(&sprite, C2D_SpriteSheetGetImage(spriteSheet, 1));
					C2D_SpriteSetPos(&sprite, 150, 100);
				}

				if (playerFrame == 1) {
					if (animCounter >= ANIM_DELAY_FRAMES) {
						playerFrame++;
						animCounter = 0;
					}
					C2D_SpriteFromImage(&sprite, C2D_SpriteSheetGetImage(spriteSheet, 2));
					C2D_SpriteSetPos(&sprite, 150, 100);
				}
				if (playerFrame == 2) {
					if (animCounter >= ANIM_DELAY_FRAMES) {
						playerFrame = 0;
						animCounter = 0;
					}
					C2D_SpriteFromImage(&sprite, C2D_SpriteSheetGetImage(spriteSheet, 3));
					C2D_SpriteSetPos(&sprite, 150, 100);
				}
			}
		}

		if (scene == 1) {
			    // Check if the screen is being touched AND the touch is inside the button
			if (hidKeysHeld() & KEY_TOUCH &&
				touch.px >= freeplayX && touch.px < (freeplayX + freeplayWidth) &&
				touch.py >= freeplayY && touch.py < (freeplayY + freeplayHeight))
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
			// This C2D_DrawRectangle function remains in existence as a comment so that it can be used as future reference for rectangles and offsetting code.
			//	C2D_DrawRectangle(testobjX - playerX, testobjY - playerY, 0, 50, 50, clrRed, clrRed, clrRed, clrRed);
			C2D_DrawSprite(&sprite);
			if (!dummy1dead)
				C2D_DrawSprite(&dummy1);
			
		}


		// Begin rendering on bottom screen
		C2D_TargetClear(bottom, clrClear);
		C2D_SceneBegin(bottom);

		if (scene == 2){
			
		}
		if (scene == 1){
			C2D_DrawSprite(&freeplaybutton);
			C2D_SpriteSetPos(&freeplaybutton, 70, 100);
			
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
