#ifndef PVZ_LAWN_SEED_BANK_H
#define PVZ_LAWN_SEED_BANK_H

#include "PvZ/Enums.h"
#include "SeedPacket.h"

class HitResult;
class SeedBank : public GameObject {
public:
    int mNumPackets;                    // 13
    int mCutSceneDarken;                // 14
    int mConveyorBeltCounter;           // 15
    bool mIsZombie;                     // 64
    int *mToolTipWidget;                // 17
    SeedPacket mSeedPackets[10];        // 18 ~ 307
    ShopSeedPacket mShopSeedPackets[7]; // 308 ~ 354
    int unknownMembers[100];            // 355 ~ 454
    // 大小455个整数

    SeedBank(bool thePlayerIndex);
    void Create(bool thePlayerIndex);
    void Draw(Sexy::Graphics *g);
    bool MouseHitTest(int x, int y, HitResult *theHitResult);
    void UpdateWidth();
    void Move(int x, int y);
};

/***************************************************************************************************************/
inline int (*SeedBank_GetNumSeedsOnConveyorBelt)(SeedBank *);


inline void (*old_SeedBank_Draw)(SeedBank *seedBank, Sexy::Graphics *graphics);

inline void (*old_SeedBank_SeedBank)(SeedBank *seedBank, bool playerIndex);

inline void (*old_SeedBank_UpdateWidth)(SeedBank *seedBank);

inline bool (*old_SeedBank_BeginDraw)(SeedBank *seedBank, Sexy::Graphics *graphics);

inline void (*old_SeedBank_EndDraw)(SeedBank *seedBank, Sexy::Graphics *graphics);


bool SeedBank_ContainsPoint(SeedBank *, int x, int y);

bool SeedBank_BeginDraw(SeedBank *seedBank, Sexy::Graphics *graphics);

void SeedBank_EndDraw(SeedBank *seedBank, Sexy::Graphics *graphics);

#endif // PVZ_LAWN_SEED_BANK_H
