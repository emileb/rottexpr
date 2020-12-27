
#include "rt_def.h"

#include <stdbool.h>

#include "game_interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>

#if USE_SDL
#include "SDL2/SDL.h"
#endif


#ifndef LOGI
#include <android/log.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO,"JNI", __VA_ARGS__))
#endif


int printf (__const char * format, ...)
{
   char buffer[256];
   va_list args;
   va_start (args, format);
   vsnprintf (buffer,256,format, args);
   LOGI ("%s",buffer);
   va_end (args);
   return 0;
}

extern int SDL_SendKeyboardKey(Uint8 state, SDL_Scancode scancode);

int PortableKeyEvent(int state, int code, int unicode){
	LOGI("PortableKeyEvent %d %d %d",state,code,unicode);

	if (state)
		SDL_SendKeyboardKey(SDL_PRESSED, (SDL_Scancode)code);
	else
		SDL_SendKeyboardKey(SDL_RELEASED, (SDL_Scancode) code);

	return 0;

}


static bool checkAck = false;

static boolean android_buttonpoll[NUMBUTTONS] = {0};
extern boolean buttonpoll[NUMBUTTONS];

void PortableAction(int state, int action)
{
	LOGI("PortableAction %d   %d",state,action);

	if (((action >= PORT_ACT_MENU_UP) && (action <= PORT_ACT_MENU_ABORT)) &&
	    (( PortableGetScreenMode() == TS_MENU ) || ( PortableGetScreenMode() == TS_Y_N )))
	{
	    SDL_Scancode scanCode = SDL_SCANCODE_UNKNOWN;

	    switch (action)
		{
		case PORT_ACT_MENU_UP:
		    scanCode = SDL_SCANCODE_UP;
		    break;
        case PORT_ACT_MENU_DOWN:
            scanCode = SDL_SCANCODE_DOWN;
            break;
        case PORT_ACT_MENU_LEFT:
            scanCode = SDL_SCANCODE_LEFT;
            break;
        case PORT_ACT_MENU_RIGHT:
            scanCode = SDL_SCANCODE_RIGHT;
            break;
        case PORT_ACT_MENU_SELECT:
            scanCode = SDL_SCANCODE_RETURN;
            break;
        case PORT_ACT_MENU_BACK:
            scanCode = SDL_SCANCODE_ESCAPE;
            break;
        case PORT_ACT_MENU_CONFIRM:
            scanCode = SDL_SCANCODE_Y;
            break;
        case PORT_ACT_MENU_ABORT:
            scanCode = SDL_SCANCODE_N;
            break;
		}

		if( scanCode != SDL_SCANCODE_UNKNOWN )
			PortableKeyEvent( state, scanCode, 0);
	}
	else
	{
		int key = bt_nobutton;
		switch (action)
		{
			case PORT_ACT_LEFT:
			    key = bt_strafeleft;
			    break;
			case PORT_ACT_RIGHT:
			    key = bt_straferight;
			    break;
			case PORT_ACT_FWD:
			    key = di_north;
			    break;
			case PORT_ACT_BACK:
			    key = di_south;
			    break;

			case PORT_ACT_MOVE_LEFT:
			    key = di_east;
			    break;
			case PORT_ACT_MOVE_RIGHT:
			    key = di_west;
			    break;

			case PORT_ACT_USE:
			    key = bt_use;
			    break;
			case PORT_ACT_ATTACK:
			    key = bt_attack;
			    break;

			case PORT_ACT_MAP:
			    key = bt_map;
			    break;
			case PORT_ACT_MAP_ZOOM_IN:
			    PortableKeyEvent(state,SDL_SCANCODE_EQUALS,0);
			    break;
			case PORT_ACT_MAP_ZOOM_OUT:
			    PortableKeyEvent(state,SDL_SCANCODE_MINUS,0);
			    break;
			case PORT_ACT_NEXT_WEP:
			    //key = e_bi_next_weapon;
			    break;
			case PORT_ACT_PREV_WEP:
			    //key = e_bi_prev_weapon;
			    break;

			case PORT_ACT_QUICKSAVE:
			    //key = e_bi_quick_save;
			    break;
			case PORT_ACT_QUICKLOAD:
			    //key = e_bi_quick_load;
			    break;

			case PORT_ACT_WEAP1:
			    key = bt_pistol;
			    break;
			case PORT_ACT_WEAP2:
			    key = bt_dualpistol;
			    break;
			case PORT_ACT_WEAP3:
			    key = bt_mp40;
			    break;
			case PORT_ACT_WEAP4:
			    key = bt_missileweapon;
			    break;
		}

		if(key != bt_nobutton)
		{
			android_buttonpoll[key] = state;
		}
	}
}


// =================== FORWARD and SIDE MOVMENT ==============

static float forwardmove, sidemove; //Joystick mode

void PortableMoveFwd(float fwd)
{
	if (fwd > 1)
		fwd = 1;
	else if (fwd < -1)
		fwd = -1;

	forwardmove = fwd;
}

void PortableMoveSide(float strafe)
{
	if (strafe > 1)
		strafe = 1;
	else if (strafe < -1)
		strafe = -1;

	sidemove = strafe;
}

void PortableMove(float fwd, float strafe)
{
	PortableMoveFwd(fwd);
	PortableMoveSide(strafe);
}

//======================================================================

//Look up and down
static int look_pitch_mode;
static float look_pitch_mouse,look_pitch_abs,look_pitch_joy;
void PortableLookPitch(int mode, float pitch)
{
	look_pitch_mode = mode;
	switch(mode)
	{
	case LOOK_MODE_MOUSE:
		look_pitch_mouse += pitch;
		break;
	case LOOK_MODE_ABSOLUTE:
		look_pitch_abs = pitch;
		break;
	case LOOK_MODE_JOYSTICK:
		look_pitch_joy = pitch;
		break;
	}
}

//left right
static int look_yaw_mode;
static float look_yaw_mouse,look_yaw_joy;
void PortableLookYaw(int mode, float yaw)
{
	look_yaw_mode = mode;
	switch(mode)
	{
	case LOOK_MODE_MOUSE:
		look_yaw_mouse += yaw;
		break;
	case LOOK_MODE_JOYSTICK:
		look_yaw_joy = yaw;
		break;
	}
}



void PortableInit(int argc,const char ** argv)
{
	int main_mobile (int argc, char *argv[]);
	main_mobile(argc,(char **)argv);
}

extern bool ingame;
extern bool inmenu;
extern bool pickquick;

touchscreemode_t PortableGetScreenMode()
{
	if(ingame && !inmenu)
		return TS_GAME;
	else
		return TS_MENU;
}

void PortableBackButton()
{
    PortableKeyEvent(1, SDL_SCANCODE_ESCAPE,0 );
    // Horrible and risky, wait for 200ms, in this time the game must have run a frame or 2 to pickup the key press
    //int usleep(int);
    usleep( 1000 * 200 );
    PortableKeyEvent(0, SDL_SCANCODE_ESCAPE, 0);
}

void PortableAutomapControl(float zoom, float x, float y)
{

}


void INL_ANDROID_GetMovement(int *side, int *forward, int *yaw, int *pitch)
{

	*side = sidemove       * -600000;
	*forward = -forwardmove   * 1000;
	*yaw = look_yaw_mouse * 150000000;
	*pitch = look_pitch_mouse * -600;

	look_yaw_mouse = 0;
	look_pitch_mouse = 0;

	memcpy( buttonpoll, android_buttonpoll, sizeof(android_buttonpoll));
}




