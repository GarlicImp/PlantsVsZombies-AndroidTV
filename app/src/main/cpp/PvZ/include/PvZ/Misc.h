#ifndef PVZ_MISC_H
#define PVZ_MISC_H

#include "Enums.h"

inline int (*CursorObject_Draw)(CursorObject *a, Sexy::Graphics *a2);

inline int (*StoreScreen_SetSelectedSlot)(int a1, int a2);

inline int (*Attachment_AttachmentDie)(int *);

inline int (*WaitForSecondPlayerDialog_GameButtonDown)(int *a1, int a2, int a3);

inline int (*ReanimatorCache_DrawCachedZombie)(ReanimatorCache *a1, Sexy::Graphics *a2, float a3, float a4, int a5);

inline void (*Sexy_StrFormat)(int *holder, const char *theFormat, ...);

inline void (*TodStringTranslate)(int *holder, const char *theText);

inline int (*GetRectOverlap)(TRect *a1, TRect *a2);

inline int (*LawnPlayerInfo_GetFlag)(PlayerInfo *, int);

inline void (*GetFlashingColor)(Color *, int, int);

inline bool (*Sexy_GamepadApp_HasGamepad)(LawnApp *);

inline bool (*GameButton_IsMouseOver)(Sexy::GameButton *);

inline void (*GameButton_Resize)(Sexy::GameButton *a, int a2, int a3, int a4, int a5);

inline void (*GameButton_Update)(Sexy::GameButton *a);

inline void (*GameButton_GameButton)(Sexy::GameButton *a, int id, int *);

inline void (*GameButton_SetLabel)(Sexy::GameButton *a, int *);

inline void (*GameButton_SetDisabled)(Sexy::GameButton *a, bool);

inline Sexy::GameButton *(*MakeButton)(int id, Sexy::ButtonListener *listener, Sexy::Widget *theParent, int *name);

inline Sexy::Checkbox *(*MakeNewCheckbox)(int id, int **listener, Sexy::Widget *theParent, bool checkedByDefault);

inline void (*Sexy_ButtonWidget_ButtonWidget)(Sexy::ButtonWidget *, int, Sexy::ButtonListener *);

inline void (*GameButton_Draw)(Sexy::GameButton *a, Sexy::Graphics *a2);

inline void (*GameButton_OnPressed)(Sexy::GameButton *a);

inline void (*GameButton_Delete)(Sexy::GameButton *a);

inline void (*Sexy_SexyMatrix3_SexyMatrix3)(int *);

inline int (*RandRangeInt)(int, int);

inline void (*Sexy_SexyTransform2D_SexyTransform2D)(SexyTransform2D *);

inline void (*Sexy_SexyTransform2D_Scale)(SexyTransform2D *, float, float);

inline void (*Sexy_SexyTransform2D_Translate)(SexyTransform2D *, float, float);

inline void (*Sexy_SexyTransform2D_RotateRad)(SexyTransform2D *, float);

inline bool (*GameObject_BeginDraw)(int *, float *);

inline void (*GameObject_EndDraw)(int *, float *);

inline void (*CursorPreview_Update)(int *);

inline void (*CursorObject_Update)(int *);

inline void (*ShopSeedPacket_Update)(int *seedPacket);

inline Sexy::Image *(*Sexy_SexyAppBase_GetImage)(LawnApp *, int *, int);

inline void (*Sexy_Widget_Resize)(Sexy::Widget *widget, int x, int y, int width, int height);

inline void (*Sexy_Widget_Widget)(Sexy::Widget *widget);

inline void (*Sexy_Widget_SetVisible)(Sexy::Widget *, bool a2);

inline void (*Sexy_WidgetManager_SetFocus)(int *manager, Sexy::Widget *);

inline void (*Sexy_WidgetContainer_SetFocus)(Sexy::WidgetContainer *, Sexy::Widget *);

inline int *(*Sexy_WidgetManager_GetWidgetAt)(int *manager, int x, int y, int *widgetX, int *widgetY);

inline int (*Sexy_Image_GetWidth)(Sexy::Image *);

inline int (*Sexy_Image_GetHeight)(Sexy::Image *);

inline int (*Sexy_Image_GetCelHeight)(Sexy::Image *);

inline float (*PlantDrawHeightOffset)(Board *, int, SeedType, int, int);

inline void (*TypingCheck_SetPhrase)(int *a1, int *a2);

inline int (*Sexy_SexyAppBase_RegistryReadString)(int *, int *, int *);

inline Sexy::Image *(*Sexy_SexyAppBase_CopyImage)(LawnApp *, Sexy::Image *);

inline Sexy::Image *(*Sexy_SexyAppBase_CopyImage2)(LawnApp *, Sexy::Image *, TRect *);

inline void (*Sexy_MemoryImage_MemoryImage)(Sexy::Image *);

inline unsigned int *(*Sexy_MemoryImage_GetBits)(Sexy::Image *);

inline void (*Sexy_MemoryImage_Create)(Sexy::Image *, int x, int y);

inline void (*Sexy_MemoryImage_SetImageMode)(Sexy::Image *, bool, bool);

inline void (*Sexy_MemoryImage_WriteToPng)(Sexy::Image *, int *);

inline void (*Sexy_MemoryImage_WriteToJPEG)(Sexy::Image *, int *);

inline void (*Sexy_MemoryImage_Delete)(Sexy::Image *);

inline void (*Sexy_MemoryImage_BitsChanged)(Sexy::Image *);

inline void (*FilterEffectDoWashedOut)(Sexy::Image *);

inline void (*FilterEffectDoLessWashedOut)(Sexy::Image *);

inline void (*FilterEffectDoWhite)(Sexy::Image *);

inline void (*FilterEffectDoLumSat)(Sexy::Image *theImage, float aLum, float aSat);

inline int **(*ReanimAtlas_GetEncodedReanimAtlas)(int *, int *);

inline void (*ReanimatorCache_GetPlantImageSize)(ReanimatorCache *, int, int *, int *, int *, int *);

inline int *(*Sexy_ResourceManager_GetSoundThrow)(int *, int *);

inline float (*RandRangeFloat)(float, float);

inline unsigned int (*PoolEffect_BilinearLookupFixedPoint)(PoolEffect *, unsigned int, unsigned int);

inline bool (*TodFoley_IsFoleyPlaying)(TodFoley *soundSystem, FoleyType::FoleyType theFoleyType);

inline void (*TodFoley_StopFoley)(TodFoley *soundSystem, FoleyType::FoleyType theFoleyType);

inline FoleyInstance *(*SoundSystemFindInstance)(TodFoley *, FoleyType::FoleyType);

inline int (*Sexy_AudiereSoundManager_LoadSound)(int *mSoundManager, int *theFileName);

inline void (*MessageWidget_MessageWidget)(MessageWidget *messageWidget, LawnApp *a2);

inline void (*MessageWidget_Delete)(MessageWidget *messageWidget);

inline Sexy::Font *(*MessageWidget_GetFont)(MessageWidget *messageWidget);

inline void (*TodStringListLoad)(const char *);

inline void (*TodReplaceString)(int *, int *, const char *, int *);

inline void (*TodReplaceNumberString)(int *, int *, const char *, int);

inline void (*Sexy_Widget_Move)(Sexy::Widget *a, int a2, int a3);

inline void (*MaskHelpWidget_MaskHelpWidget)(AchievementsWidget *, LawnApp *);

inline void (*MaskHelpWidget_Delete)(AchievementsWidget *);

inline void (*TrashBin_Delete)(TrashBin *a1);

inline void (*TodParticleSystem_OverrideColor)(TodParticleSystem *, char *theEmitterName, Color *theColor);

inline void (*TodParticleSystem_OverrideImage)(TodParticleSystem *, char *theEmitterName, Sexy::Image *);

inline void (*TodParticleSystem_Delete2)(TodParticleSystem *);

inline void (*TodParticleSystem_ParticleSystemDie)(TodParticleSystem *);

inline PlayerInfo *(*Sexy_DefaultProfileMgr_GetAnyProfile)(int *);

inline void (*DrawCheckboxText)(Sexy::Graphics *graphics, int *text1, Sexy::Checkbox *a3, const char *text2);

inline void (*Sexy_Checkbox_Delete)(Sexy::Checkbox *);

inline void (*CreditScreen_PauseCredits)(Sexy::Widget *);

inline int (*Sexy_RandInt)(int);

inline void (*Sexy_Image_SetWrapMode)(Sexy::Image *, int, int);

inline void (*Sexy_WidgetContainer_MarkDirty)(Sexy::WidgetContainer *);

inline void (*ReanimatorEnsureDefinitionLoaded)(ReanimationType type, bool b);

inline void (*Sexy_MenuWidget_Draw)(Sexy::MenuWidget *, Sexy::Graphics *);

inline void (*Sexy_Widget_DeferOverlay)(Sexy::Widget *, int);

inline int (*Mailbox_GetNumUnseenMessages)(int *);

inline void (*LawnMower_StartMower)(int *);

inline Sexy::Image *(*ReanimatorCache_MakeCachedPlantFrame)(ReanimatorCache *, SeedType, DrawVariation);

inline Sexy::MemoryImage *(*ReanimatorCache_MakeBlankCanvasImage)(ReanimatorCache *, int, int);

inline void (*ReanimatorCache_DrawReanimatorFrame)(
    ReanimatorCache *, Sexy::Graphics *g, float x, float y, ReanimationType reanimType, char *trackName, DrawVariation variation);

inline TodAllocator *(*FindGlobalAllocator)(int aSize);

inline void (*AttachParticle)(int *, TodParticleSystem *, float, float);

inline void (*TodLoadResources)(int *);

inline void (*TodParticleSystem_Draw)(TodParticleSystem *, Sexy::Graphics *);

inline void (*ToolTipWidget_SetWarningText)(int *, int *);

inline void (*TestMenuWidget_TestMenuWidget)(ZombatarWidget *);

inline void (*Sexy_SexyAppBase_EraseFile)(SexyAppBase *, int *);

inline void (*SaveGameContext_SyncInt)(int *, int *);

inline void (*Sexy_ScrollbarWidget_SetMaxValue)(Sexy::ScrollbarWidget *, double);

inline void (*Sexy_Ratio_Set)(int *, int, int);


inline void (*old_WaitForSecondPlayerDialog_WaitForSecondPlayerDialog)(int *a, int *a2);

inline void (*old_Sexy_Image_PushTransform)(Sexy::Image *image, int *transform, bool concatenate);

inline void (*old_Sexy_Image_PopTransform)(Sexy::Image *image);

inline void (*old_Sexy_GLImage_PushTransform)(Sexy::Image *image, int *transform, bool concatenate);

inline void (*old_Sexy_GLImage_PopTransform)(Sexy::Image *image);

inline void (*old_Sexy_MemoryImage_PushTransform)(Sexy::Image *image, int *transform, bool concatenate);

inline void (*old_Sexy_MemoryImage_PopTransform)(Sexy::Image *image);

inline int (*old_SexyDialog_AddedToManager)(void *instance, void *instance1);

inline int (*old_SexyDialog_RemovedFromManager)(void *instance, void *instance1);

inline void (*old_LawnMower_Update)(int *lawnMover);

inline void (*old_ReanimatorCache_LoadCachedImages)(ReanimatorCache *a1);

inline void (*old_ReanimatorCache_UpdateReanimationForVariation)(ReanimatorCache *a1, Reanimation *a, DrawVariation theDrawVariation);

inline void (*old_ReanimatorCache_DrawCachedPlant)(
    ReanimatorCache *a1, Sexy::Graphics *graphics, float thePosX, float thePosY, SeedType theSeedType, DrawVariation drawVariation);

inline Sexy::Image *(*old_ReanimatorCache_MakeCachedZombieFrame)(ReanimatorCache *reanimatorCache, ZombieType zombieType);

inline void (*old_HelpBarWidget_HelpBarWidget)(Sexy::Widget *a);

inline bool (*old_CursorObject_BeginDraw)(CursorObject *cursorObject, Sexy::Graphics *graphics);

inline void (*old_CursorObject_EndDraw)(CursorObject *cursorObject, Sexy::Graphics *graphics);

inline void (*old_Sexy_ExtractLoadingSoundsResources)(int *a, int *theManager);

inline FoleyParams *(*old_LookupFoley)(FoleyType::FoleyType type);

inline void (*old_MessageWidget_Draw)(CustomMessageWidget *messageWidget, Sexy::Graphics *a2);

inline void (*old_MessageWidget_ClearLabel)(CustomMessageWidget *messageWidget);

inline void (*old_MessageWidget_SetLabel)(CustomMessageWidget *messageWidget, int *label, MessageStyle theStyle);

inline void (*old_MessageWidget_Update)(CustomMessageWidget *messageWidget);

inline void (*old_CreditScreen_CreditScreen)(Sexy::Widget *a, LawnApp *a2, bool a3);

inline void (*old_CreditScreen_RemovedFromManager)(Sexy::Widget *creditScreen, int a2);

inline void (*old_CreditScreen_Delete2)(Sexy::Widget *creditScreen);


int randomInt(int a, int b);

void DrawSeedPacket(Sexy::Graphics *graphics,
                    float x,
                    float y,
                    SeedType seedType,
                    SeedType imitaterType,
                    float coolDownPercent,
                    int grayness,
                    bool drawCostText,
                    bool isInGame,
                    bool isZombieSeed,
                    bool a11);

void ReanimatorCache_DrawCachedPlant(ReanimatorCache *a1, Sexy::Graphics *graphics, float thePosX, float thePosY, SeedType theSeedType, DrawVariation theDrawVariation);

void DrawSeedType(Sexy::Graphics *graphics, float x, float y, SeedType theSeedType, SeedType theImitaterType, float xOffset, float yOffset, float scale);

void LawnMower_Update(int *lawnMover);

void Sexy_Widget_MarkDirty(Sexy::Widget *widget);

void Sexy_Widget_AddWidget(Sexy::Widget *parent, Sexy::Widget *child);

void Sexy_Widget_RemoveWidget(Sexy::Widget *parent, Sexy::Widget *child);

Sexy::Widget *Sexy_Widget_FindWidget(Sexy::Widget *parent, int id);

void Sexy_String_Delete(int *holder);

void Sexy_Image_PushTransform(Sexy::Image *image, int *transform, bool concatenate);

void Sexy_Image_PopTransform(Sexy::Image *image);

void Sexy_GLImage_PushTransform(Sexy::Image *image, int *transform, bool concatenate);

void Sexy_GLImage_PopTransform(Sexy::Image *image);

void Sexy_MemoryImage_PushTransform(Sexy::Image *image, int *transform, bool concatenate);

void Sexy_MemoryImage_PopTransform(Sexy::Image *image);

void Sexy_MemoryImage_ClearRect(Sexy::Image *a1, TRect *a2);

Sexy::Image *FilterEffectCreateImage(Sexy::Image *image, FilterEffectType);

Sexy::Image *FilterEffectGetImage(Sexy::Image *image, FilterEffectType);

bool Sexy_SexyAppBase_Is3DAccelerated(LawnApp *);

void Sexy_SexyAppBase_Set3DAccelerated(LawnApp *, bool);

bool CursorObject_BeginDraw(CursorObject *cursorObject, Sexy::Graphics *graphics);

void CursorObject_EndDraw(CursorObject *cursorObject, Sexy::Graphics *graphics);

void PoolEffect_PoolEffectDraw(PoolEffect *poolEffect, Sexy::Graphics *graphics, bool theIsNight);

int SexyDialog_AddedToManager(void *instance, void *instance1);

int SexyDialog_RemovedFromManager(void *instance, void *instance1);

FoleyParams *LookupFoley(FoleyType::FoleyType theFoleyType);

void CreditScreen_ButtonDepress(Sexy::Widget *creditScreen, int id);

void MessageWidget_ClearLabel(CustomMessageWidget *messageWidget);

void MessageWidget_SetLabel(CustomMessageWidget *messageWidget, int *label, MessageStyle theStyle);

void MessageWidget_Update(CustomMessageWidget *messageWidget);

void MessageWidget_Draw(CustomMessageWidget *messageWidget, Sexy::Graphics *graphics);

void Sexy_ExtractLoadingSoundsResources(int *a, int *theManager);

void CustomScrollbarWidget_RemoveScrollButtons(Sexy::CustomScrollbarWidget *scrollbarWidget);

void CreditScreen_CreditScreen(Sexy::Widget *creditScreen, LawnApp *a2, bool a3);

void CreditScreen_RemovedFromManager(Sexy::Widget *creditScreen, int a2);

void CreditScreen_Delete2(Sexy::Widget *creditScreen);

void WaitForSecondPlayerDialog_WaitForSecondPlayerDialog(int *a, int *a2);

void HelpBarWidget_HelpBarWidget(Sexy::Widget *a);

void LawnPlayerInfo_AddCoins(PlayerInfo *playerInfo, int theAmount);

void SaveGameContext_SyncReanimationDef(int *theSaveGameContext, ReanimatorDefinition **a2);



#endif // PVZ_MISC_H
