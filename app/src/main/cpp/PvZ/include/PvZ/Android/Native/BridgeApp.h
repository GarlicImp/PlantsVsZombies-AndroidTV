//
// Created by 28636 on 2025/5/28.
//

#ifndef PLANTSVSZOMBIES_ANDROIDTV_BRIDGEAPP_H
#define PLANTSVSZOMBIES_ANDROIDTV_BRIDGEAPP_H


namespace Native {
class NativeApp;

class BridgeApp {
public:
    int *mVtable;
    NativeApp *mNativeApp;
};

}


#endif // PLANTSVSZOMBIES_ANDROIDTV_BRIDGEAPP_H
