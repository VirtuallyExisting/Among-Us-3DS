#include <grrlib.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <vcplib.h>

#include <freeplaybutton_png.h>
#include <Idle_png.h>
#include <Walk1_png.h>
#include <walk2_png.h>
#include <Walk3_png.h>
#include <deadbody_png.h>
#include <ventclosed_png.h>


#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

#define ANIM_DELAY_FRAMES 6 // If the game is running at 60 FPS then this is equal to a 0.1 second delay.

//---------------------------------------------------------------------------------
int main(int argc, char **argv) {
//---------------------------------------------------------------------------------
	// Init libs
	romfsInit();
	vcplib_Init();



	

	int scene;
	scene = 1;


	const int freeplayWidth = 250;
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
	


	float vent1x;
	float vent1y;
	vent1x = -50;
	vent1y = 0;

	float vent2x;
	float vent2y;
	vent2x = 50;
	vent2y = 0;

	int inVent;
	inVent = 0;
	int ventIn;
	ventIn = 0;







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
	C2D_Sprite vent1;
	C2D_Sprite vent2;

	C2D_Image playersprite; // Swap the contents of this variable to different images to change player sprite (this system may need work)
	C2D_Image dummy1spr;

	spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
	if (!spriteSheet) svcBreak(USERBREAK_PANIC);

	GRRLIB_texImg *freeplaybutton = GRRLIB_LoadTexture(freeplaybutton_png);



	playersprite = C2D_SpriteSheetGetImage(spriteSheet, 0);
	dummy1spr = C2D_SpriteSheetGetImage(spriteSheet, 0);
//	C2D_SpriteFromImage(&freeplaybutton, C2D_SpriteSheetGetImage(spriteSheet, 4)); // spritesheet image position references (to be removed)
//	C2D_SpriteFromImage(&dummy1, C2D_SpriteSheetGetImage(spriteSheet, 0));
//	C2D_SpriteFromImage(&vent1, C2D_SpriteSheetGetImage(spriteSheet, 5));
//	C2D_SpriteFromImage(&vent2, C2D_SpriteSheetGetImage(spriteSheet, 5));

	C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

	


	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();
		touchPosition touch;
		hidTouchRead(&touch);

		






		if (scene == 2) {


			playerSpriteX = playerX + 150;

			playerSpriteY = playerY + 100;









			if (dummy1dead == 1) {
				dummy1spr = C2D_SpriteSheetGetImage(spriteSheet, 6);
				dummy1dead = 0;
			}







			// Most new logic should go above
			


			// Respond to user input
			u32 kDown = hidKeysHeld();
			u32 kPressed = hidKeysDown();
			if (!inVent) {
				if (kDown & KEY_CPAD_RIGHT)
					playerX = playerX + 3;
				if (kDown & KEY_CPAD_LEFT)
					playerX = playerX - 3;
				if (kDown & KEY_CPAD_DOWN)
					playerY = playerY + 3;
				if (kDown & KEY_CPAD_UP)
					playerY = playerY - 3;
			}
			
			if (kPressed & KEY_A) {
				if (!inVent) {
					if (sqrt(pow(playerSpriteX - dummy1x, 2) + pow(playerSpriteY - dummy1y, 2)) <= 100.0f) {
						dummy1dead = 1;
					}
				}


				
			

			}
			if (kPressed & KEY_B) {
				if (!inVent) {
					if (sqrt(pow(playerSpriteX - vent1x, 2) + pow(playerSpriteY - vent1y, 2)) <= 100.0f) {
						inVent = 1;
						ventIn = 1;
					}
					if (sqrt(pow(playerSpriteX - vent2x, 2) + pow(playerSpriteY - vent2y, 2)) <= 100.0f) {
						inVent = 1;
						ventIn = 2;
					}
				}
				else if (inVent) {
					inVent = 0;
				}
			}


			if (kPressed & KEY_X) {
				if (inVent) {
					if (ventIn == 1) {
						playerX = vent2x - 150;
						playerY = vent2y - 85;
						ventIn = 2;
					}
					else if (ventIn == 2) {
						playerX = vent1x - 150;
						playerY = vent1y - 85;
						ventIn = 1;
					}
				}
			}
			

				
			
			if (!kDown)
				playerAnim = 0;
			if (kDown & (KEY_CPAD_UP | KEY_CPAD_DOWN | KEY_CPAD_LEFT | KEY_CPAD_RIGHT))
				playerAnim = 1;
			
			if (playerAnim == 0) {
				playersprite = C2D_SpriteSheetGetImage(spriteSheet, 0);
			//	C2D_SpriteSetPos(&sprite, 150, 100);
				playerFrame = 0;
			}
			if (playerAnim == 1) {
				animCounter++;

				if (playerFrame == 0) {
					if (animCounter >= ANIM_DELAY_FRAMES) {
						playerFrame++;
						animCounter = 0;
					}
					playersprite = C2D_SpriteSheetGetImage(spriteSheet, 1);
				//	C2D_SpriteSetPos(&sprite, 150, 100);
				}

				if (playerFrame == 1) {
					if (animCounter >= ANIM_DELAY_FRAMES) {
						playerFrame++;
						animCounter = 0;
					}
					playersprite = C2D_SpriteSheetGetImage(spriteSheet, 2);
				//	C2D_SpriteSetPos(&sprite, 150, 100);
				}
				if (playerFrame == 2) {
					if (animCounter >= ANIM_DELAY_FRAMES) {
						playerFrame = 0;
						animCounter = 0;
					}
					playersprite = C2D_SpriteSheetGetImage(spriteSheet, 3);
				//	C2D_SpriteSetPos(&sprite, 150, 100);
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
		vcplib_FrameBegin();
		C2D_TargetClear(top, clrClear);
		C2D_SceneBegin(top);


		if (scene == 2){
			// This C2D_DrawRectangle function remains in existence as a comment so that it can be used as future reference for rectangles and offsetting code.
			//	C2D_DrawRectangle(testobjX - playerX, testobjY - playerY, 0, 50, 50, clrRed, clrRed, clrRed, clrRed);
			vcplib_DrawImage(C2D_SpriteSheetGetImage(spriteSheet, 5), vent1x - playerX, vent1y - playerY, 1);
			vcplib_DrawImage(C2D_SpriteSheetGetImage(spriteSheet, 5), vent2x - playerX, vent2y - playerY, 1);
			if (!inVent)
				vcplib_DrawImage(playersprite, 150, 100, 1);
			
			vcplib_DrawImage(dummy1spr, dummy1x - playerX, dummy1y - playerY, 1);
		
		}


		// Begin rendering on bottom screen
    	C2D_TargetClear(bottom, clrClear);
		C2D_SceneBegin(bottom);

		if (scene == 2){
			
		}
		if (scene == 1){
			vcplib_DrawImage(C2D_SpriteSheetGetImage(spriteSheet, 4), 70, 100, 1);
			
		}

		C3D_FrameEnd(0);
		
	}

	// Deinit libs
	C2D_SpriteSheetFree(spriteSheet);
	vcplib_Deinit();
	exit(0);
}