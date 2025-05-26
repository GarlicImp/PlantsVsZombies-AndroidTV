#ifndef PVZ_ANDROID_OPENSL_H
#define PVZ_ANDROID_OPENSL_H

#include "PvZ/Lawn/Common/ConstEnums.h"

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <jni.h>

inline void (*old_Native_AudioOutput_initialize)(Native::AudioOutput *audioOutput);

inline bool (*old_Native_AudioOutput_setup)(Native::AudioOutput *audioOutput, int sampleRate, int channels, int bits);

inline void (*old_Native_AudioOutput_shutdown)(Native::AudioOutput *audioOutput);

inline int (*old_Native_AudioOutput_write)(Native::AudioOutput *audioOutput, const void *a2, int a3);


void AudioWrite(const void *data, int dataSize);

void Native_AudioOutput_initialize(Native::AudioOutput *audioOutput);

bool Native_AudioOutput_setup(Native::AudioOutput *audioOutput, int sampleRate, int channels, int bits);

void Native_AudioOutput_shutdown(Native::AudioOutput *audioOutput);

int Native_AudioOutput_write(Native::AudioOutput *audioOutput, const void *a2, int a3);

#endif // PVZ_ANDROID_OPENSL_H
