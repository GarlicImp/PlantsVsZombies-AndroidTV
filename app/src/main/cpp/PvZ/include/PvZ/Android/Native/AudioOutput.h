//
// Created by 28636 on 2025/5/28.
//

#ifndef PLANTSVSZOMBIES_ANDROIDTV_AUDIOOUTPUT_H
#define PLANTSVSZOMBIES_ANDROIDTV_AUDIOOUTPUT_H

#include <jni.h>

namespace Native {
class NativeApp;

class AudioOutput {
public:
    NativeApp *mNativeApp;
    JNIEnv *mEnv;
    bool mUnkBool;
};
} // namespace Native


#endif // PLANTSVSZOMBIES_ANDROIDTV_AUDIOOUTPUT_H
