#include <grrlib.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include <wiiuse/wpad.h>
#include <vcplib.h>

#include <freeplaybutton_bmp.h>
#include <Idle_bmp.h>
#include <Walk1_bmp.h>
#include <walk2_bmp.h>
#include <Walk3_bmp.h>
#include <deadbody_bmp.h>
#include <ventclosed_bmp.h>
#include <skeldcafe_bmp.h>
#include <skeldhall1_bmp.h>


#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

#define ANIM_DELAY_FRAMES 6 // If the game is running at 60 FPS then this is equal to a 0.1 second delay.

//---------------------------------------------------------------------------------
int main(int argc, char **argv) {
//---------------------------------------------------------------------------------
	// Init libs
//	romfsInit();
	vcplib_Init();



	

	int scene;
	scene = 1;


	const int freeplayWidth = 250;
	const int freeplayHeight = 50;
	const int freeplayX = 100 - freeplayWidth / 2; // Top-left X
	const int freeplayY = 100 - freeplayHeight / 2; // Top-left Y

	// Create colors
//	u32 clrWhite = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
//	u32 clrGreen = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
//	u32 clrRed   = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
//	u32 clrBlue  = C2D_Color32(0x00, 0x00, 0xFF, 0xFF);

//	u32 clrRec1 = C2D_Color32(0x9A, 0x6C, 0xB9, 0xFF);
//	u32 clrRec2 = C2D_Color32(0xFF, 0xFF, 0x2C, 0xFF);
//	u32 clrRec3 = C2D_Color32(0xD8, 0xF6, 0x0F, 0xFF);
//	u32 clrRec4 = C2D_Color32(0x40, 0xEA, 0x87, 0xFF);

//	u32 clrClear = C2D_Color32(0x00, 0x00, 0x00, 0x00);


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

	float playerscalex;
	playerscalex = 1;

//	C2D_SpriteSheet spriteSheet;
//	C2D_Sprite sprite;
//	C2D_Sprite freeplaybutton;
//	C2D_Sprite dummy1;
//	C2D_Sprite vent1;
//	C2D_Sprite vent2;

//	C2D_Image playersprite; // Swap the contents of this variable to different images to change player sprite (this system may need work)
//	C2D_Image dummy1spr;

//	spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
//	if (!spriteSheet) svcBreak(USERBREAK_PANIC);

	GRRLIB_texImg *freeplaybutton = GRRLIB_LoadTexture(freeplaybutton_bmp);
	GRRLIB_texImg *redcrewidle = GRRLIB_LoadTexture(Idle_bmp);
	GRRLIB_texImg *redcrewwalk1 = GRRLIB_LoadTexture(Walk1_bmp);
	GRRLIB_texImg *redcrewwalk2 = GRRLIB_LoadTexture(walk2_bmp);
	GRRLIB_texImg *redcrewwalk3 = GRRLIB_LoadTexture(Walk3_bmp);
	GRRLIB_texImg *redcrewdead = GRRLIB_LoadTexture(deadbody_bmp);
	GRRLIB_texImg *ventclosed = GRRLIB_LoadTexture(ventclosed_bmp);
	GRRLIB_texImg *skeldcafe = GRRLIB_LoadTexture(skeldcafe_bmp);
	GRRLIB_texImg *skeldhallway1 = GRRLIB_LoadTexture(skeldhall1_bmp);

	GRRLIB_texImg *playersprite = redcrewidle;
	GRRLIB_texImg *dummy1spr = redcrewidle;



//	playersprite = C2D_SpriteSheetGetImage(spriteSheet, 0);
//	dummy1spr = C2D_SpriteSheetGetImage(spriteSheet, 0);
	dummy1spr = redcrewidle;


//	C2D_SpriteFromImage(&freeplaybutton, C2D_SpriteSheetGetImage(spriteSheet, 4)); // spritesheet image position references (to be removed)
//	C2D_SpriteFromImage(&dummy1, C2D_SpriteSheetGetImage(spriteSheet, 0));
//	C2D_SpriteFromImage(&vent1, C2D_SpriteSheetGetImage(spriteSheet, 5));
//	C2D_SpriteFromImage(&vent2, C2D_SpriteSheetGetImage(spriteSheet, 5));

//	C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
//	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

	WPAD_Init();


	// Main loop
	while (1)
	{
	//	hidScanInput();
	//	touchPosition touch;
	//	hidTouchRead(&touch);

	WPAD_ScanPads();


	if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)  break;

		






		if (scene == 2) {


			playerSpriteX = playerX + 150;

			playerSpriteY = playerY + 100;









			if (dummy1dead == 1) {
				dummy1spr = redcrewdead;
				dummy1dead = 0;
			}







			// Most new logic should go above
			


			// Respond to user input
			u32 kDown = WPAD_ButtonsHeld(0);
			u32 kPressed = WPAD_ButtonsDown(0);
			if (!inVent) {
				if (kDown & WPAD_BUTTON_RIGHT) {
					playerX = playerX + 3;
					playerscalex = 1;
				}
				if (kDown & WPAD_BUTTON_LEFT) {
					playerX = playerX - 3;
					playerscalex = -1;
				}
				if (kDown & WPAD_BUTTON_DOWN)
					playerY = playerY + 3;
				if (kDown & WPAD_BUTTON_UP)
					playerY = playerY - 3;
			}
			
			if (kPressed & WPAD_BUTTON_B) {
				if (!inVent) {
					if (sqrt(pow(playerSpriteX - dummy1x, 2) + pow(playerSpriteY - dummy1y, 2)) <= 100.0f) {
						dummy1dead = 1;
					}
				}


				
			

			}
			if (kPressed & WPAD_BUTTON_A) {
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


			if (kPressed & WPAD_BUTTON_2) {
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
			if (kDown & (WPAD_BUTTON_UP | WPAD_BUTTON_DOWN | WPAD_BUTTON_LEFT | WPAD_BUTTON_RIGHT))
				playerAnim = 1;
			
			if (playerAnim == 0) {
				playersprite = redcrewidle;
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
					playersprite = redcrewwalk1;
				//	C2D_SpriteSetPos(&sprite, 150, 100);
				}

				if (playerFrame == 1) {
					if (animCounter >= ANIM_DELAY_FRAMES) {
						playerFrame++;
						animCounter = 0;
					}
					playersprite = redcrewwalk2;
				//	C2D_SpriteSetPos(&sprite, 150, 100);
				}
				if (playerFrame == 2) {
					if (animCounter >= ANIM_DELAY_FRAMES) {
						playerFrame = 0;
						animCounter = 0;
					}
					playersprite = redcrewwalk3;
				//	C2D_SpriteSetPos(&sprite, 150, 100);
				}
			}
		}

		if (scene == 1) {
			    // Check if the screen is being touched AND the touch is inside the button
		//	if (kDown() & KEY_A &&
		//		touch.px >= freeplayX && touch.px < (freeplayX + freeplayWidth) &&
		//		touch.py >= freeplayY && touch.py < (freeplayY + freeplayHeight))
			if (WPAD_ButtonsDown(0) & WPAD_BUTTON_A) {
				scene = 2;
			}

		}
	

			


		// Begin rendering on top screen
		vcplib_FrameBegin();
	//	C2D_TargetClear(top, clrClear);
	//	C2D_SceneBegin(top);


		if (scene == 2){
			// This C2D_DrawRectangle function remains in existence as a comment so that it can be used as future reference for rectangles and offsetting code.
			//	C2D_DrawRectangle(testobjX - playerX, testobjY - playerY, 0, 50, 50, clrRed, clrRed, clrRed, clrRed);
			vcplib_DrawImage(skeldcafe, 0 - playerX, 0 - playerY, 4, 4);
			vcplib_DrawImage(skeldhallway1, -505 - playerX, 265 - playerY, 2, 2);

			vcplib_DrawImage(ventclosed, vent1x - playerX, vent1y - playerY, 1, 1);
			vcplib_DrawImage(ventclosed, vent2x - playerX, vent2y - playerY, 1, 1);
			if (!inVent)
				vcplib_DrawImage(playersprite, 150, 100, playerscalex, 1);
			
			vcplib_DrawImage(dummy1spr, dummy1x - playerX, dummy1y - playerY, 1, 1);
		
		}


		// Begin rendering on bottom screen
    //	C2D_TargetClear(bottom, clrClear);
	//	C2D_SceneBegin(bottom);

		if (scene == 2){
			
		}
		if (scene == 1){
			vcplib_DrawImage(freeplaybutton, 70, 100, 1, 1);
			
		}

		vcplib_FrameEnd();
		
	}

	// Deinit libs
//	C2D_SpriteSheetFree(spriteSheet);
	vcplib_Deinit();
	exit(0);
}