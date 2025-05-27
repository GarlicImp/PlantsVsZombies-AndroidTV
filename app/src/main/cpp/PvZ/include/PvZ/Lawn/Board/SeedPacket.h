#ifndef PVZ_LAWN_SEED_PACKET_H
#define PVZ_LAWN_SEED_PACKET_H

#include "GameObject.h"
#include "PvZ/Lawn/Common/ConstEnums.h"

class HitResult;
class SeedBank;
class SeedPacket : public GameObject {
public:
    int mRefreshCounter;             // 13
    int mRefreshTime;                // 14
    int mIndex;                      // 15
    int mOffsetY;                    // 16
    SeedType mPacketType;            // 17
    SeedType mImitaterType;          // 18
    int mSlotMachineCountDown;       // 19
    SeedType mSlotMachiningNextSeed; // 20
    float mSlotMachiningPosition;    // 21
    bool mActive;                    // 88
    bool mRefreshing;                // 89
    int mTimesUsed;                  // 23
    SeedBank *mSeedBank;             // 24
    float mLastSelectedTime;         // 25
    int unknownIntMember1;           // 26
    int unknownIntMember2;           // 27
    bool mSelectedBy2P;              // 112
    bool mSelectedBy1P;              // 113
    // 大小29个整数
public:
    void Update();
    void UpdateSelected();
    void DrawOverlay(Sexy::Graphics *g);
    void Draw(Sexy::Graphics *g);
    void FlashIfReady();
};

/***************************************************************************************************************/
inline bool showCoolDown;

inline void (*SeedPacket_DrawBackground)(SeedPacket *seedPacket, Sexy::Graphics *graphics);

inline bool (*SeedPacket_CanPickUp)(SeedPacket *seedPacket);

inline bool (*SeedPacket_MouseHitTest)(SeedPacket *, int, int, HitResult *);

inline bool (*SeedPacket_GetPlayerIndex)(SeedPacket *);

inline void (*SeedPacket_DrawMiddle)(SeedPacket *seedPacket, Sexy::Graphics *graphics);


inline void (*old_SeedPacket_Update)(SeedPacket *seedPacket);

inline void (*old_SeedPacket_UpdateSelected)(SeedPacket *seedPacket);

inline void (*old_SeedPacket_DrawOverlay)(SeedPacket *seedPacket, Sexy::Graphics *graphics);

inline void (*old_SeedPacket_Draw)(SeedPacket *seedPacket, Sexy::Graphics *graphics);

inline void (*old_SeedPacket_MouseDown)(SeedPacket *seedPacket, int x, int y, int c, int unk);

inline bool (*old_SeedPacket_BeginDraw)(SeedPacket *, Sexy::Graphics *);

inline void (*old_SeedPacket_EndDraw)(SeedPacket *, Sexy::Graphics *);

inline void (*old_SeedPacket_FlashIfReady)(SeedPacket *seedPacket);


bool SeedPacket_BeginDraw(SeedPacket *a, Sexy::Graphics *a2);

void SeedPacket_EndDraw(SeedPacket *a, Sexy::Graphics *a2);


#endif // PVZ_LAWN_SEED_PACKET_H
