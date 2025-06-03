#ifndef PVZ_MISC_H
#define PVZ_MISC_H

#include "PvZ/Lawn/Board/GameObject.h"
#include "PvZ/Lawn/Board/MessageWidget.h"
#include "PvZ/Lawn/Common/ConstEnums.h"
#include "PvZ/Lawn/System/PlayerInfo.h"
#include "PvZ/Lawn/System/ReanimationLawn.h"
#include "PvZ/Lawn/Widget/AchievementsWidget.h"
#include "PvZ/Lawn/Widget/ZombatarWidget.h"
#include "PvZ/SexyAppFramework/Misc/SexyMatrix.h"
#include "PvZ/SexyAppFramework/SexyAppBase.h"
#include "PvZ/SexyAppFramework/Widget/Checkbox.h"
#include "PvZ/SexyAppFramework/Widget/GameButton.h"
#include "PvZ/TodLib/Common/TodFoley.h"
#include "PvZ/TodLib/Common/TodList.h"
#include "TodLib/Common/TodCommon.h"

class TodParticleSystem;

inline int (*WaitForSecondPlayerDialog_GameButtonDown)(int *a1, int a2, int a3);

inline void (*Sexy_StrFormat)(int *holder, const char *theFormat, ...);

inline void (*TodStringTranslate)(int *holder, const char *theText);

inline int (*LawnPlayerInfo_GetFlag)(PlayerInfo *, int);

inline void (*GetFlashingColor)(Sexy::Color *, int, int);

inline bool (*Sexy_GamepadApp_HasGamepad)(LawnApp *);

inline bool (*GameButton_IsMouseOver)(Sexy::GameButton *);

inline void (*GameButton_Resize)(Sexy::GameButton *a, int a2, int a3, int a4, int a5);

inline void (*GameButton_Update)(Sexy::GameButton *a);

inline void (*GameButton_GameButton)(Sexy::GameButton *a, int id, int *);

inline void (*GameButton_SetLabel)(Sexy::GameButton *a, int *);

inline void (*GameButton_SetDisabled)(Sexy::GameButton *a, bool);

inline Sexy::GameButton *(*MakeButton)(int id, Sexy::ButtonListener *listener, Sexy::Widget *theParent, int *name);

inline Sexy::Checkbox *(*MakeNewCheckbox)(int id, int **listener, Sexy::Widget *theParent, bool checkedByDefault);

inline void (*GameButton_Draw)(Sexy::GameButton *a, Sexy::Graphics *a2);

inline void (*GameButton_OnPressed)(Sexy::GameButton *a);

inline void (*GameButton_Delete)(Sexy::GameButton *a);

inline void (*Sexy_SexyMatrix3_SexyMatrix3)(int *);

inline void (*Sexy_SexyTransform2D_SexyTransform2D)(Sexy::SexyTransform2D *);

inline void (*Sexy_SexyTransform2D_Scale)(Sexy::SexyTransform2D *, float, float);

inline void (*Sexy_SexyTransform2D_Translate)(Sexy::SexyTransform2D *, float, float);

inline void (*Sexy_SexyTransform2D_RotateRad)(Sexy::SexyTransform2D *, float);

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

inline void (*TypingCheck_SetPhrase)(int *a1, int *a2);

inline int (*Sexy_SexyAppBase_RegistryReadString)(int *, int *, int *);

inline Sexy::Image *(*Sexy_SexyAppBase_CopyImage)(LawnApp *, Sexy::Image *);

inline Sexy::Image *(*Sexy_SexyAppBase_CopyImage2)(LawnApp *, Sexy::Image *, Sexy::Rect *);

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

inline int *(*Sexy_ResourceManager_GetSoundThrow)(int *, int *);

inline bool (*TodFoley_IsFoleyPlaying)(TodFoley *soundSystem, FoleyType theFoleyType);

inline void (*TodFoley_StopFoley)(TodFoley *soundSystem, FoleyType theFoleyType);

inline FoleyInstance *(*SoundSystemFindInstance)(TodFoley *, FoleyType);

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

inline void (*TodParticleSystem_OverrideColor)(TodParticleSystem *, char *theEmitterName, Sexy::Color *theColor);

inline void (*TodParticleSystem_OverrideImage)(TodParticleSystem *, char *theEmitterName, Sexy::Image *);

inline void (*TodParticleSystem_Delete2)(TodParticleSystem *);

inline void (*TodParticleSystem_ParticleSystemDie)(TodParticleSystem *);

inline PlayerInfo *(*Sexy_DefaultProfileMgr_GetAnyProfile)(int *);

inline void (*DrawCheckboxText)(Sexy::Graphics *graphics, int *text1, Sexy::Checkbox *a3, const char *text2);

inline void (*Sexy_Checkbox_Delete)(Sexy::Checkbox *);

inline void (*CreditScreen_PauseCredits)(Sexy::Widget *);

inline void (*Sexy_Image_SetWrapMode)(Sexy::Image *, int, int);

inline void (*Sexy_WidgetContainer_MarkDirty)(Sexy::WidgetContainer *);

inline void (*ReanimatorEnsureDefinitionLoaded)(ReanimationType type, bool b);

inline void (*Sexy_Widget_DeferOverlay)(Sexy::Widget *, int);

inline int (*Mailbox_GetNumUnseenMessages)(int *);

inline TodAllocator *(*FindGlobalAllocator)(int aSize);

inline void (*AttachParticle)(AttachmentID *, TodParticleSystem *, float, float);

inline void (*TodLoadResources)(int *);

inline void (*TodParticleSystem_Draw)(TodParticleSystem *, Sexy::Graphics *);

inline void (*ToolTipWidget_SetWarningText)(int *, int *);

inline void (*TestMenuWidget_TestMenuWidget)(ZombatarWidget *);

inline void (*SaveGameContext_SyncInt)(int *, int *);

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

inline void (*old_HelpBarWidget_HelpBarWidget)(Sexy::Widget *a);

inline void (*old_Sexy_ExtractLoadingSoundsResources)(int *a, int *theManager);

inline FoleyParams *(*old_LookupFoley)(FoleyType type);

inline void (*old_MessageWidget_Draw)(CustomMessageWidget *messageWidget, Sexy::Graphics *a2);

inline void (*old_MessageWidget_ClearLabel)(CustomMessageWidget *messageWidget);

inline void (*old_MessageWidget_SetLabel)(CustomMessageWidget *messageWidget, int *label, MessageStyle theStyle);

inline void (*old_MessageWidget_Update)(CustomMessageWidget *messageWidget);


int randomInt(int a, int b);

void DrawSeedPacket(
    Sexy::Graphics *g, float x, float y, SeedType seedType, SeedType imitaterType, float coolDownPercent, int grayness, bool drawCostText, bool isInGame, bool isZombieSeed, bool a11);

void DrawSeedType(Sexy::Graphics *g, float x, float y, SeedType theSeedType, SeedType theImitaterType, float xOffset, float yOffset, float scale);

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

void Sexy_MemoryImage_ClearRect(Sexy::Image *a1, Sexy::Rect *a2);

bool Sexy_SexyAppBase_Is3DAccelerated(LawnApp *);

void Sexy_SexyAppBase_Set3DAccelerated(LawnApp *, bool);

int SexyDialog_AddedToManager(void *instance, void *instance1);

int SexyDialog_RemovedFromManager(void *instance, void *instance1);

FoleyParams *LookupFoley(FoleyType theFoleyType);

void CreditScreen_ButtonDepress(Sexy::Widget *creditScreen, int id);

void MessageWidget_ClearLabel(CustomMessageWidget *messageWidget);

void MessageWidget_SetLabel(CustomMessageWidget *messageWidget, int *label, MessageStyle theStyle);

void MessageWidget_Update(CustomMessageWidget *messageWidget);

void MessageWidget_Draw(CustomMessageWidget *messageWidget, Sexy::Graphics *graphics);

void Sexy_ExtractLoadingSoundsResources(int *a, int *theManager);

void WaitForSecondPlayerDialog_WaitForSecondPlayerDialog(int *a, int *a2);

void HelpBarWidget_HelpBarWidget(Sexy::Widget *a);

void LawnPlayerInfo_AddCoins(PlayerInfo *playerInfo, int theAmount);

void SaveGameContext_SyncReanimationDef(int *theSaveGameContext, ReanimatorDefinition **a2);


#endif // PVZ_MISC_H
