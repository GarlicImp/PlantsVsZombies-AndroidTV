#ifndef PVZ_ANDROID_INTRO_VIDEO_H
#define PVZ_ANDROID_INTRO_VIDEO_H

#include "PvZ/Android/Native/BridgeApp.h"

#include <jni.h>

inline JNIEnv *(*Native_BridgeApp_getJNIEnv)(Native::BridgeApp *);

inline jobject (*Native_NativeApp_getActivity)(Native::NativeApp *);

inline Native::BridgeApp *(*Native_BridgeApp_getSingleton)();

inline char *(*Native_NativeApp_getPackageName)(Native::NativeApp *);


int AGVideoOpen(const char *videoPath);

bool AGVideoIsPlaying();

bool AGVideoShow(bool show);

bool AGVideoPlay();

int AGVideoEnable(bool show);

#endif // PVZ_ANDROID_INTRO_VIDEO_H
