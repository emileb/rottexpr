

extern "C"
{

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


extern "C" int printf (__const char * format, ...)
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
        switch (action)
        {
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
    int usleep(int);
    usleep( 1000 * 200 );
    PortableKeyEvent(0, SDL_SCANCODE_ESCAPE, 0);
}

void PortableAutomapControl(float zoom, float x, float y)
{

}

}

#define BASEMOVE                35
#define RUNMOVE                 70
#define BASETURN                35
#define RUNTURN                 70

void mobile_StartAck()
{
	checkAck = false;
}

bool mobile_CheckAck()
{
	bool ret = checkAck;
	checkAck = false;
	return ret;
}

//NOTE this is cpp
void pollAndroidControls(int tics,int *controlx, int *controly,int *controlstrafe, bool *  buttons)
{
	*controly  -= forwardmove     * tics * BASEMOVE;
	*controlstrafe  += sidemove   * tics * BASEMOVE;


	switch(look_yaw_mode)
	{
	case LOOK_MODE_MOUSE:
		*controlx += -look_yaw_mouse * 8000;
		look_yaw_mouse = 0;
		break;
	case LOOK_MODE_JOYSTICK:
		*controlx += -look_yaw_joy * 80;
		break;
	}

}


