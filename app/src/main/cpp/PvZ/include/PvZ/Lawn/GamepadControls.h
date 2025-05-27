#ifndef PVZ_LAWN_GAMEPAD_CONTROLS_H
#define PVZ_LAWN_GAMEPAD_CONTROLS_H

#include "BaseGamepadControls.h"
#include "PvZ/Lawn/Common/ConstEnums.h"
#include "PvZ/Misc.h"

class Zombie;

class GamepadControls : public BaseGamepadControls {
public:
    float mRangeFrom0to30UpdateFresh;  // 43
    int *mSelectorParticle;            // 44
    int mSelectedSeedIndex;            // 45
    SeedType mSelectedSeedType;        // 46
    bool mIsZombie;                    // 188
    bool mCanPickUp;                   // 189
    int mSelectedUpgradableType;       // 48
    int mCobCannonPlantIndexInList;    // 49
    bool mIsCobCannonSelected;         // 200
    float mUpdateAdd_a2_Or_Minus_2xa2; // 51
    ReanimationID mPreviewReanimID1;   // 52
    ReanimationID mCursorReanimID;     // 53
    ReanimationID mPreviewReanimID3;   // 54
    int mUnkCobCannonRelated;          // 55
    ReanimationID mPreviewReanimID4;   // 56
    SeedType mPreviewingSeedType;      // 57
    Sexy::Image *mPreviewImage;        // 58
    Zombie *mButterZombie;             // 59
    int mShovelRelated2;               // 60
    bool mIsShowingDigIndicator;       // 244
    bool mIsInShopSeedBank;            // 245
    int mSelectedShopSeedIndex;        // 62
    int unk4[3];                       // 63 ~ 65
}; // 大小66个整数

class ZenGardenControls : public GamepadControls {
public:
    GameObjectType mObjectType; // 66
}; // 大小67个整数

/***************************************************************************************************************/
// buttonCode 是按键键值，对应关系如下：
enum ButtonCode {
    BUTTONCODE_LUP = 0,
    BUTTONCODE_LDOWN = 1,
    BUTTONCODE_LLEFT = 2,
    BUTTONCODE_LRIGHT = 3,
    BUTTONCODE_UNKNOWN = 4,
    BUTTONCODE_PAUSE = 5,
    BUTTONCODE_A = 6,
    BUTTONCODE_B = 7,
    BUTTONCODE_X = 8,
    BUTTONCODE_Y = 9,
    BUTTONCODE_L1 = 10,
    BUTTONCODE_R1 = 11,
    BUTTONCODE_L2 = 12,
    BUTTONCODE_R2 = 13,
    BUTTONCODE_TL = 14,
    BUTTONCODE_TR = 15,
    BUTTONCODE_UP = 16,
    BUTTONCODE_DOWN = 17,
    BUTTONCODE_LEFT = 18,
    BUTTONCODE_RIGHT = 19
};
// 左摇杆上 0
// 左摇杆下 1
// 左摇杆左 2
// 左摇杆右 3
// 未知键 4
// 暂停键 5
// A 6
// B 7
// X 8
// Y 9
// L1 10
// R1 11
// L2 12
// R2 13
// TL 14
// TR 15
// 上 16
// 下 17
// 左 18
// 右 19


inline SeedBank *(*GamepadControls_GetSeedBank)(GamepadControls *a);

inline void (*GamepadControls_OnButtonDown)(GamepadControls *a1, int buttonCode, int a3, unsigned int a4);

// a3 根据手柄决定是0还是1
// a4 恒定为0
inline void (*GamepadControls_OnButtonUp)(GamepadControls *a1, int a2, int a3, unsigned int a4);

// 确定 13 1096
// 返回 27 1096
// 左 37 1096
// 上 38 1096
// 右 39 1096
// 下 40 1096
// 铲子 49 1112
// 锤子 50 1112
inline void (*GamepadControls_OnKeyDown)(GamepadControls *a1, int a2, unsigned int a3);


inline void (*old_GamepadControls_Draw)(GamepadControls *gamePad, Sexy::Graphics *graphics);

inline void (*old_GamepadControls_Update)(GamepadControls *gamepadControls, float a2);

inline void (*old_GamepadControls_GamepadControls)(GamepadControls *gamePad, Board *board, int a3, int a4);

inline void (*old_GamepadControls_ButtonDownFireCobcannonTest)(GamepadControls *gamepadControls);

inline void (*old_GamepadControls_UpdatePreviewReanim)(GamepadControls *gamePad);

inline void (*old_GamepadControls_DrawPreview)(GamepadControls *gamePad, Sexy::Graphics *graphics);

inline void (*old_ZenGardenControls_Update)(ZenGardenControls *a1, float a2);


void GamepadControls_GamepadControls(GamepadControls *gamepadControls, Board *board, int a3, int a4);

FilterEffect GetFilterEffectTypeBySeedType(SeedType mSeedType);

void GamepadControls_pickUpCobCannon(int, int);

void GamepadControls_DrawPreview(GamepadControls *gamepadControls, Sexy::Graphics *graphics);

void ZenGardenControls_Update(ZenGardenControls *a1, float a2);

void GamepadControls_ButtonDownFireCobcannonTest(GamepadControls *gamepadControls);

void GamepadControls_Draw(GamepadControls *gamepadControls, Sexy::Graphics *graphics);

void GamepadControls_Update(GamepadControls *gamepadControls, float a2);

void GamepadControls_UpdatePreviewReanim(GamepadControls *gamepadControls);

#endif // PVZ_LAWN_GAMEPAD_CONTROLS_H
