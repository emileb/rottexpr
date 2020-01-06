LOCAL_PATH := $(call my-dir)/../

include $(CLEAR_VARS)

LOCAL_MODULE := rottexpr

LOCAL_CFLAGS = -DSHAREWARE=0  -DSUPERROTT=0 -DSITELICENSE=0 -DUSE_SDL=1 -DPLATFORM_UNIX=1 -D_GNU_SOURCE -fsigned-char -D__MOBILE__ -DENGINE_NAME=\"rottexpr\" -Wno-error=format-security


LOCAL_C_INCLUDES = $(TOP_DIR)/ \
	               $(LOCAL_PATH)/../../../Clibs_OpenTouch/idtech1

#also include my SDL for SDL_android_extra.h 
LOCAL_C_INCLUDES += $(SDL_INCLUDE_PATHS) \
                    $(TOP_DIR)/MobileTouchControls \
                    $(TOP_DIR)/Clibs_OpenTouch

LOCAL_SRC_FILES += mobile/game_interface.cpp

LOCAL_SRC_FILES += ../../../Clibs_OpenTouch/alpha/android_jni.cpp
LOCAL_SRC_FILES += ../../../Clibs_OpenTouch/alpha/touch_interface.cpp


LOCAL_SRC_FILES += cin_actr.c
LOCAL_SRC_FILES += cin_efct.c
LOCAL_SRC_FILES += cin_evnt.c
LOCAL_SRC_FILES += cin_glob.c
LOCAL_SRC_FILES += cin_main.c
LOCAL_SRC_FILES += cin_util.c
LOCAL_SRC_FILES += dosutil.c
LOCAL_SRC_FILES += engine.c
LOCAL_SRC_FILES += isr.c
LOCAL_SRC_FILES += modexlib.c
LOCAL_SRC_FILES += rt_actor.c
LOCAL_SRC_FILES += rt_battl.c
LOCAL_SRC_FILES += rt_build.c
LOCAL_SRC_FILES += rt_cfg.c
LOCAL_SRC_FILES += rt_crc.c
LOCAL_SRC_FILES += rt_com.c
LOCAL_SRC_FILES += rt_debug.c
LOCAL_SRC_FILES += rt_dmand.c
LOCAL_SRC_FILES += rt_door.c
LOCAL_SRC_FILES += rt_draw.c
LOCAL_SRC_FILES += rt_floor.c
LOCAL_SRC_FILES += rt_game.c
LOCAL_SRC_FILES += rt_in.c
LOCAL_SRC_FILES += rt_main.c
LOCAL_SRC_FILES += rt_map.c
LOCAL_SRC_FILES += rt_menu.c
LOCAL_SRC_FILES += rt_msg.c
LOCAL_SRC_FILES += rt_net.c
LOCAL_SRC_FILES += rt_playr.c
LOCAL_SRC_FILES += rt_rand.c
LOCAL_SRC_FILES += rt_scale.c
LOCAL_SRC_FILES += rt_sound.c
LOCAL_SRC_FILES += rt_sqrt.c
LOCAL_SRC_FILES += rt_stat.c
LOCAL_SRC_FILES += rt_state.c
LOCAL_SRC_FILES += rt_str.c
LOCAL_SRC_FILES += rt_ted.c
LOCAL_SRC_FILES += rt_util.c
LOCAL_SRC_FILES += rt_view.c
LOCAL_SRC_FILES += rt_vid.c
LOCAL_SRC_FILES += rt_err.c
LOCAL_SRC_FILES += scriplib.c
LOCAL_SRC_FILES += w_wad.c
LOCAL_SRC_FILES += watcom.c
LOCAL_SRC_FILES += z_zone.c
LOCAL_SRC_FILES += byteordr.c
LOCAL_SRC_FILES += dukemusc.c
LOCAL_SRC_FILES += winrott.c
LOCAL_SRC_FILES += queue.c
LOCAL_SRC_FILES += HashTable.c


LOCAL_SRC_FILES += audiolib/fx_man.c
LOCAL_SRC_FILES += audiolib/dsl.c
LOCAL_SRC_FILES += audiolib/ll_man.c
LOCAL_SRC_FILES += audiolib/multivoc.c
LOCAL_SRC_FILES += audiolib/mv_mix.c
LOCAL_SRC_FILES += audiolib/mvreverb.c
LOCAL_SRC_FILES += audiolib/nodpmi.c
LOCAL_SRC_FILES += audiolib/pitch.c
LOCAL_SRC_FILES += audiolib/user.c
LOCAL_SRC_FILES += audiolib/usrhooks.c



LOCAL_LDLIBS := -lEGL -ldl -llog -lz -lm -lc -lGLESv1_CM
LOCAL_STATIC_LIBRARIES := logwritter
LOCAL_SHARED_LIBRARIES := touchcontrols  SDL2 SDL2_mixer core_shared

LOCAL_STATIC_LIBRARIES +=

include $(BUILD_SHARED_LIBRARY)






