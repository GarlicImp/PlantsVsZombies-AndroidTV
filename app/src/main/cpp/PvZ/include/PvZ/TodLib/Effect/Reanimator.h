#ifndef PVZ_LAWN_REANIMATION_H
#define PVZ_LAWN_REANIMATION_H

#include "AttachEffect.h"
#include "EffectSystem.h"
#include "PvZ/Lawn/Common/ConstEnums.h"
#include "PvZ/SexyAppFramework/Misc/SexyMatrix.h"

namespace Sexy
{
class Font;
class Image;
class Graphics;
class MemoryImage;
};

// ######################################################################################################################################################
// ############################################################### 以下为动画定义相关内容 ###############################################################
// ######################################################################################################################################################

// ====================================================================================================
// ★ 【动画器定义】
// ----------------------------------------------------------------------------------------------------
// 用于描述一种动画类型与该动画的数据文件的文件名及标志之间的对应关系。
// ====================================================================================================
class ReanimatorDefinition {
public:
    ReanimatorTrack *mTracks; // 0
    int mTrackCount;          // 1
    float mFPS;               // 2
    int *mReanimAtlas;        // 3
}; // 大小4个整数

// ====================================================================================================
// ★ 【动画参数】
// ----------------------------------------------------------------------------------------------------
// 用于描述一种动画类型与该动画的数据文件的文件名及标志之间的对应关系。
// ====================================================================================================
class ReanimationParams {
public:
    ReanimationType mReanimationType;
    const char *mReanimFileName;
    int mReanimParamFlags;
};

class ReanimatorTransform {
public:
    float mTransX;        // 0
    float mTransY;        // 1
    float mSkewX;         // 2
    float mSkewY;         // 3
    float mScaleX;        // 4
    float mScaleY;        // 5
    float mFrame;         // 6
    float mAlpha;         // 7
    Sexy::Image *mImage;  // 8
    Sexy::Image *mImage2; // 9
    int *mFont;           // 10
    char *mName;          // 11
}; // 大小12个整数

class ReanimatorTrackInstance {
public:
    int mBlendCounter;                   // 0
    int mBlendTime;                      // 1
    ReanimatorTransform mBlendTransform; // 2 ~ 13
    float mShakeOverride;                // 14
    float mShakeX;                       // 15
    float mShakeY;                       // 16
    unsigned short mAttachmentID;        // 17
    Sexy::Image *mImageOverride;         // 18
    int mRenderGroup;                    // 19
    Sexy::Color mTrackColor;             // 20 ~ 23
    bool mIgnoreClipRect;                // 96
    bool mTruncateDisappearingFrames;    // 97
    bool mIgnoreColorOverride;           // 98
    bool mIgnoreExtraAdditiveColor;      // 99
}; // 大小25个整数

// ######################################################################################################################################################
// ############################################################## 以下正式开始动画相关声明 ##############################################################
// ######################################################################################################################################################

enum { RENDER_GROUP_HIDDEN = -1, RENDER_GROUP_NORMAL = 0 };

class Reanimation {
public:
    int unk1[4];                                // 0 ~ 3
    ReanimationType mReanimationType;           // 4
    float mAnimTime;                            // 5
    float mAnimRate;                            // 6
    ReanimatorDefinition *mDefinition;          // 7
    ReanimLoopType mLoopType;                   // 8
    bool mDead;                                 // 36
    int mFrameStart;                            // 10
    int mFrameCount;                            // 11
    int mFrameBasePose;                         // 12
    Sexy::SexyTransform2D mOverlayMatrix;       // 13 ~ 21
    Sexy::Color mColorOverride;                 // 22 ~ 25
    ReanimatorTrackInstance *mTrackInstances;   // 26
    int mLoopCount;                             // 27
    int *mReanimationHolder;                    // 28
    bool mIsAttachment;                         // 116
    int mRenderOrder;                           // 30
    Sexy::Color mExtraAdditiveColor;            // 31 ~ 34
    bool mEnableExtraAdditiveDraw;              // 140
    Sexy::Color mExtraOverlayColor;             // 36 ~ 39
    bool mEnableExtraOverlayDraw;               // 160
    float mLastFrameTime;                       // 41
    FilterEffect mFilterEffect;                 // 42
    Sexy::Color mCustomFilterEffectColor;       // 43 ~ 46
    int unk2[4];                                // 47 ~ 50
    ReanimatorTransform *mReanimatorTransforms; // 51
    bool unkBool;                               // 208
    float unkFloatWithInitialValue_1;           // 53
    int mReanimationID;                         // 54
    // 大小55个整数

    bool DrawTrack(Sexy::Graphics *g, int theTrackIndex, int theRenderGroup, TodTriangleGroup *theTriangleGroup);
    bool ShouldTriggerTimedEvent(float theEventTime);
    void AssignRenderGroupToTrack(const char *theTrackName, int theRenderGroup);
};

class ReanimationHolder {
public:
    struct ReanimationLists {
    public:
        Reanimation list[1024];
    }; // 225280个整数
public:
    ReanimationLists *mReanimations; // 0
    int unk1;                        // 1
    int mReanimationNum;             // 2
    int unk2[3];                     // 3 ~ 5
    char *mName;                     // 6
};
/***************************************************************************************************************/
inline void (*Reanimation_SetPosition)(Reanimation *a, float a2, float a3);

inline void (*Reanimation_OverrideScale)(Reanimation *ream, float a2, float a3);

inline void (*Reanimation_DrawRenderGroup)(Reanimation *a, Sexy::Graphics *graphics, int a3);

inline void (*Reanimation_Reanimation)(Reanimation *a);

inline void (*Reanimation_ReanimationInitializeType)(Reanimation *a1, float a2, float a3, ReanimationType a4);

inline bool *(*Reanimation_Draw)(Reanimation *a, Sexy::Graphics *a2);

inline void (*Reanimation_Delete2)(Reanimation *a);

inline int (*Reanimation_FindTrackIndexById)(Reanimation *a, char *a2);

inline void (*Reanimation_GetCurrentTransform)(Reanimation *, int, ReanimatorTransform *);

inline void (*ReanimatorTransform_ReanimatorTransform)(ReanimatorTransform *a);

inline void (*Reanimation_PlayReanim)(Reanimation *a1, const char *a2, ReanimLoopType a3, int a4, float a5);

inline void (*Reanimation_SetAnimRate)(Reanimation *a, float a2);

inline bool (*Reanimation_IsAnimPlaying)(Reanimation *a, char *a2);

inline void (*Reanimation_SetImageOverride)(Reanimation *, const char *, Sexy::Image *);

inline int (*Reanimation_FindTrackIndex)(Reanimation *, const char *);

inline void (*Reanimation_ShowOnlyTrack)(Reanimation *, const char *);

inline void (*Reanimation_ReanimationDie)(Reanimation *reanim);

inline ReanimatorTrackInstance *(*Reanimation_GetTrackInstanceByName)(Reanimation *reanim, const char *);

inline AttachEffect *(*AttachReanim)(unsigned short *, Reanimation *, float, float);

inline void (*Reanimation_SetFramesForLayer)(Reanimation *, const char *);

inline bool (*Reanimation_TrackExists)(Reanimation *, const char *);

inline void (*Reanimation_AttachToAnotherReanimation)(Reanimation *, Reanimation *reanim, const char *trackName);

inline void (*Reanimation_Update)(Reanimation *);

inline void (*Reanimation_MatrixFromTransform)(ReanimatorTransform *, Sexy::SexyMatrix3 *);

inline void (*Reanimation_GetFrameTime)(Reanimation *, ReanimatorFrameTime *pTime);

inline void (*TodScaleRotateTransformMatrix)(Sexy::SexyMatrix3 *, float, float, float, float, float);

inline void (*Reanimation_GetTrackMatrix)(Reanimation *pInstance, int i, Sexy::SexyTransform2D *pD);


inline bool (*old_Reanimation_DrawTrack)(Reanimation *reanim, Sexy::Graphics *g, int theTrackIndex, int theRenderGroup, TodTriangleGroup *theTriangleGroup);

inline void (*old_ReanimatorLoadDefinitions)(ReanimationParams *theReanimationParamArray, int theReanimationParamArraySize);

inline void (*old_DefinitionGetCompiledFilePathFromXMLFilePath)(int *absPath, int *defPathString);


void Reanimation_SetImageOrigin(Reanimation *, const char *, Sexy::Image *);

void Reanimation_SetImageDefinition(Reanimation *reanim, const char *trackName, Sexy::Image *theImage);

int Reanimation_HideTrack(Reanimation *reanim, const char *trackName, bool hide);

void Reanimation_HideTrackById(Reanimation *reanim, int trackIndex, bool hide);

void Reanimation_HideTrackByPrefix(Reanimation *reanim, const char *trackPrefix, bool hide);

void Reanimation_SetZombatarReanim(Reanimation *zombatarReanim);

void Reanimation_SetZombatarHats(Reanimation *zombatarReanim, unsigned char hats, unsigned char hatsColor);

void Reanimation_SetZombatarHair(Reanimation *zombatarReanim, unsigned char hair, unsigned char hairColor);

void Reanimation_SetZombatarFHair(Reanimation *zombatarReanim, unsigned char facialHair, unsigned char facialHairColor);

void Reanimation_SetZombatarAccessories(Reanimation *zombatarReanim, unsigned char accessories, unsigned char accessoriesColor);

void Reanimation_SetZombatarEyeWear(Reanimation *zombatarReanim, unsigned char eyeWear, unsigned char eyeWearColor);

void Reanimation_SetZombatarTidBits(Reanimation *zombatarReanim, unsigned char tidBits, unsigned char tidBitsColor);

void Reanimation_GetZombatarTrackIndex(Reanimation *zombatarReanim, int *indexArray);

int Reanimation_GetZombatarHatTrackIndex(Reanimation *zombatarReanim);

int Reanimation_GetZombatarEyeWearTrackIndex(Reanimation *zombatarReanim);

void ReanimatorLoadDefinitions(ReanimationParams *theReanimationParamArray, int theReanimationParamArraySize);

void DefinitionGetCompiledFilePathFromXMLFilePath(int *absPath, int *defPathString);


#endif // PVZ_LAWN_REANIMATION_H
