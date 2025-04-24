#ifndef PVZ_LAWN_COIN_H
#define PVZ_LAWN_COIN_H

#include "PvZ/Enums.h"

class Coin : public GameObject {
public:
    float mPosX;                        // 13
    float mPosY;                        // 14
    float mPrevPosX;                    // 15
    float mPrevPosY;                    // 16
    float mVelX;                        // 17
    float mVelY;                        // 18
    float mScale;                       // 19
    bool mDead;                         // 80
    int mFadeCount;                     // 21
    float mCollectX;                    // 22
    float mCollectY;                    // 23
    int mGroundY;                       // 24
    int mCoinAge;                       // 25
    bool mIsBeingCollected;             // 104
    int mCollectedByPlayerIndex;        // 27
    int mDisappearCounter;              // 28
    CoinType mType;           // 29
    CoinMotion mCoinMotion; // 30
    int mAttachment[3];                 // 31 ~ 33
    float mCollectionDistance;          // 34
    SeedType mUsableSeedType; // 35
    int *mPottedPlantSpec;              // 36
    int unknownMember[4];               // 37 ~ 40
    bool mNeedsBouncyArrow;             // 164
    bool mHasBouncyArrow;               // 165
    bool mHitGround;                    // 166
    int mTimesDropped;                  // 42
    int mPlayerIndex;                   // 43
    float unk2;                         // 44
    bool unk3;                          // 180
    int unk4;                           // 46
    bool unk5;                          // 188
    int mAutoCollectAge;                // 48
    bool unk7;                          // 196
    bool unk8;                          // 197
    int unkInt;                         // 50
    // 大小51个整数

    void GamepadCursorOver(int thePlayerIndex);
    void Update();
    void UpdateFallForAward();
    void UpdateFall();
    bool MouseHitTest(int theX, int theY, int **theHitResult, int thePlayerIndex);
};

/***************************************************************************************************************/
inline bool enableManualCollect;
inline bool BanDropCoin;


inline void (*Coin_Die)(Coin *a);

inline void (*Coin_Collect)(Coin *a1, int a2);

inline void (*Coin_MouseDown)(Coin *coin, int x, int y, int);

inline void (*old_Coin_GamepadCursorOver)(Coin *coin, int a2);

inline bool (*Coin_IsLevelAward)(Coin *);

inline bool (*Coin_IsPresentWithAdvice)(Coin *);

inline bool (*Coin_IsMoney)(Coin *);

inline void (*Coin_PlayGroundSound)(Coin *);

inline int (*Coin_GetDisappearTime)(Coin *);

inline void (*Coin_StartFade)(Coin *);

inline float (*Coin_GetSunScale)(Coin *);


inline void (*old_Coin_Update)(Coin *coin);

inline void (*old_Coin_UpdateFall)(Coin *coin);

inline bool (*old_Coin_MouseHitTest)(Coin *coin, int a2, int a3, int **hitResult, int a5);

#endif // PVZ_LAWN_COIN_H
