//
// Created by 28636 on 2025/5/27.
//

#ifndef PLANTSVSZOMBIES_ANDROIDTV_PROFILEMGR_H
#define PLANTSVSZOMBIES_ANDROIDTV_PROFILEMGR_H

class ProfileMgr {
public:
    int *vTable;                // 0
    int *mProfileEventListener; // 1
};

class DefaultProfileMgr : public ProfileMgr {
public:
    int *mProfileMap;    // 2
    int *mProfileMapEnd; // 3

    int mNumProfiles; // 7

    int mNextProfileUseSeq; // 9
};

#endif // PLANTSVSZOMBIES_ANDROIDTV_PROFILEMGR_H
