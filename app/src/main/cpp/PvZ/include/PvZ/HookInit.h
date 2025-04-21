#ifndef PVZ_HOOK_INIT_H
#define PVZ_HOOK_INIT_H

#include "Homura/HookFunc.h"
#include "Misc.h"
#include "PvZ/Android/IntroVideo.h"
#include "PvZ/Android/OpenSL.h"
#include "PvZ/Lawn/AlmanacDialog.h"
#include "PvZ/Lawn/AwardScreen.h"
#include "PvZ/Lawn/Board.h"
#include "PvZ/Lawn/Challenge.h"
#include "PvZ/Lawn/ChallengeScreen.h"
#include "PvZ/Lawn/Coin.h"
#include "PvZ/Lawn/ConfirmBackToMainDialog.h"
#include "PvZ/Lawn/CutScene.h"
#include "PvZ/Lawn/GamepadControls.h"
#include "PvZ/Lawn/GridItem.h"
#include "PvZ/Lawn/HelpOptionsDialog.h"
#include "PvZ/Lawn/HelpTextScreen.h"
#include "PvZ/Lawn/HouseChooserDialog.h"
#include "PvZ/Lawn/ImitaterDialog.h"
#include "PvZ/Lawn/LawnApp.h"
#include "PvZ/Lawn/MailScreen.h"
#include "PvZ/Lawn/MainMenu.h"
#include "PvZ/Lawn/Music.h"
#include "PvZ/Lawn/Plant.h"
#include "PvZ/Lawn/Projectile.h"
#include "PvZ/Lawn/Reanimation.h"
#include "PvZ/Lawn/SeedBank.h"
#include "PvZ/Lawn/SeedChooserScreen.h"
#include "PvZ/Lawn/SeedPacket.h"
#include "PvZ/Lawn/SettingsDialog.h"
#include "PvZ/Lawn/StoreScreen.h"
#include "PvZ/Lawn/TitleScreen.h"
#include "PvZ/Lawn/VSResultsMenu.h"
#include "PvZ/Lawn/VSSetupMenu.h"
#include "PvZ/Lawn/ZenGarden.h"
#include "PvZ/Lawn/Zombie.h"
#include "PvZ/SexyAppFramework/Graphics.h"
#include "Symbols.h"

inline void InitInGameFunction() {
    Board_Move = (decltype(Board_Move))Board_MoveAddr;
    Board_ProgressMeterHasFlags = (decltype(Board_ProgressMeterHasFlags))Board_ProgressMeterHasFlagsAddr;
    Board_IsSurvivalStageWithRepick = (decltype(Board_IsSurvivalStageWithRepick))Board_IsSurvivalStageWithRepickAddr;
    Board_PickUpTool = (decltype(Board_PickUpTool))Board_PickUpToolAddr;
    Board_IteratePlants = (decltype(Board_IteratePlants))Board_IteratePlantsAddr;
    Board_IterateProjectiles = (decltype(Board_IterateProjectiles))Board_IterateProjectilesAddr;
    Board_IterateCoins = (decltype(Board_IterateCoins))Board_IterateCoinsAddr;
    Board_IterateLawnMowers = (decltype(Board_IterateLawnMowers))Board_IterateLawnMowersAddr;
    Board_IterateParticles = (decltype(Board_IterateParticles))Board_IterateParticlesAddr;
    Board_IterateGridItems = (decltype(Board_IterateGridItems))Board_IterateGridItemsAddr;
    Board_IterateZombies = (decltype(Board_IterateZombies))Board_IterateZombiesAddr;
    Board_AddProjectile = (decltype(Board_AddProjectile))Board_AddProjectileAddr;
    Board_GameAxisMove = (decltype(Board_GameAxisMove))Board_GameAxisMoveAddr;
    Board_InitCoverLayer = (decltype(Board_InitCoverLayer))Board_InitCoverLayerAddr;
    Board_LoadBackgroundImages = (decltype(Board_LoadBackgroundImages))Board_LoadBackgroundImagesAddr;
    Board_HasConveyorBeltSeedBank = (decltype(Board_HasConveyorBeltSeedBank))Board_HasConveyorBeltSeedBankAddr;
    // Board_UpdateGridItems = (int (*)(Board *)) Board_UpdateGridItemsAddr;
    Board_ZombieHitTest = (decltype(Board_ZombieHitTest))Board_ZombieHitTestAddr;
    Board_GetTopPlantAt = (decltype(Board_GetTopPlantAt))Board_GetTopPlantAtAddr;
    Board_NewPlant = (decltype(Board_NewPlant))Board_NewPlantAddr;
    Board_CanUseGameObject = (decltype(Board_CanUseGameObject))Board_CanUseGameObjectAddr;
    Board_ToolHitTest = (decltype(Board_ToolHitTest))Board_ToolHitTestAddr;
    Board_RefreshSeedPacketFromCursor = (decltype(Board_RefreshSeedPacketFromCursor))Board_RefreshSeedPacketFromCursorAddr;
    Board_GetPlantsOnLawn = (decltype(Board_GetPlantsOnLawn))Board_GetPlantsOnLawnAddr;
    Board_GridToPixelX = (decltype(Board_GridToPixelX))Board_GridToPixelXAddr;
    Board_GridToPixelY = (decltype(Board_GridToPixelY))Board_GridToPixelYAddr;
    Board_PixelToGridY = (decltype(Board_PixelToGridY))Board_PixelToGridYAddr;
    Board_PixelToGridX = (decltype(Board_PixelToGridX))Board_PixelToGridXAddr;
    Board_AddALadder = (decltype(Board_AddALadder))Board_AddALadderAddr;
    Board_ClearCursor = (decltype(Board_ClearCursor))Board_ClearCursorAddr;
    Board_MouseDownWithTool = (decltype(Board_MouseDownWithTool))Board_MouseDownWithToolAddr;
    Board_CountPlantByType = (decltype(Board_CountPlantByType))Board_CountPlantByTypeAddr;
    Board_SetTutorialState = (decltype(Board_SetTutorialState))Board_SetTutorialStateAddr;
    Board_DoFwoosh = (decltype(Board_DoFwoosh))Board_DoFwooshAddr;
    //    Board_ShakeBoard = (decltype(Board_ShakeBoard)) Board_ShakeBoardAddr;
    Board_GetButterButtonRect = (decltype(Board_GetButterButtonRect))Board_GetButterButtonRectAddr;
//     Board_GetShovelButtonRect = (void (*)(TRect *, Board *)) Board_GetShovelButtonRectAddr;
    Board_ZombieTryToGet = (decltype(Board_ZombieTryToGet))Board_ZombieTryToGetAddr;
    Board_MakeRenderOrder = (decltype(Board_MakeRenderOrder))Board_MakeRenderOrderAddr;
    Board_PlantUsesAcceleratedPricing = (decltype(Board_PlantUsesAcceleratedPricing))Board_PlantUsesAcceleratedPricingAddr;
    Board_IsPlantInCursor = (decltype(Board_IsPlantInCursor))Board_IsPlantInCursorAddr;
    Board_MouseDownWithPlant = (decltype(Board_MouseDownWithPlant))Board_MouseDownWithPlantAddr;
    Board_CanInteractWithBoardButtons = (decltype(Board_CanInteractWithBoardButtons))Board_CanInteractWithBoardButtonsAddr;
    Board_RemoveAllPlants = (decltype(Board_RemoveAllPlants))Board_RemoveAllPlantsAddr;
    Board_GetSeedBankExtraWidth = (decltype(Board_GetSeedBankExtraWidth))Board_GetSeedBankExtraWidthAddr;
    Board_GetSeedPacketPositionX = (decltype(Board_GetSeedPacketPositionX))Board_GetSeedPacketPositionXAddr;
    Board_AddCoin = (decltype(Board_AddCoin))Board_AddCoinAddr;
    Board_CanTakeSunMoney = (decltype(Board_CanTakeSunMoney))Board_CanTakeSunMoneyAddr;
    Board_GetZenButtonRect = (decltype(Board_GetZenButtonRect))Board_GetZenButtonRectAddr;
    Board_GetGridItemAt = (decltype(Board_GetGridItemAt))Board_GetGridItemAtAddr;
    Board_GetLadderAt = (decltype(Board_GetLadderAt))Board_GetLadderAtAddr;
    Board_PixelToGridXKeepOnBoard = (decltype(Board_PixelToGridXKeepOnBoard))Board_PixelToGridXKeepOnBoardAddr;
    Board_PixelToGridYKeepOnBoard = (decltype(Board_PixelToGridYKeepOnBoard))Board_PixelToGridYKeepOnBoardAddr;
    Board_IsValidCobCannonSpotHelper = (decltype(Board_IsValidCobCannonSpotHelper))Board_IsValidCobCannonSpotHelperAddr;
    Board_PickRowForNewZombie = (decltype(Board_PickRowForNewZombie))Board_PickRowForNewZombieAddr;
    Board_IsPoolSquare = (decltype(Board_IsPoolSquare))Board_IsPoolSquareAddr;
    Board_ZombiePickerInit = (decltype(Board_ZombiePickerInit))Board_ZombiePickerInitAddr;
    Board_GetIntroducedZombieType = (decltype(Board_GetIntroducedZombieType))Board_GetIntroducedZombieTypeAddr;
    Board_ZombiePickerInitForWave = (decltype(Board_ZombiePickerInitForWave))Board_ZombiePickerInitForWaveAddr;
    Board_PutZombieInWave = (decltype(Board_PutZombieInWave))Board_PutZombieInWaveAddr;
    Board_PickZombieType = (decltype(Board_PickZombieType))Board_PickZombieTypeAddr;
    Board_HasLevelAwardDropped = (decltype(Board_HasLevelAwardDropped))Board_HasLevelAwardDroppedAddr;
    Board_SpawnZombiesFromGraves = (decltype(Board_SpawnZombiesFromGraves))Board_SpawnZombiesFromGravesAddr;
    Board_ClearAdvice = (decltype(Board_ClearAdvice))Board_ClearAdviceAddr;
    Board_NextWaveComing = (decltype(Board_NextWaveComing))Board_NextWaveComingAddr;
    Board_TotalZombiesHealthInWave = (decltype(Board_TotalZombiesHealthInWave))Board_TotalZombiesHealthInWaveAddr;
    Board_ClearAdviceImmediately = (decltype(Board_ClearAdviceImmediately))Board_ClearAdviceImmediatelyAddr;
    Board_DisplayAdviceAgain = (decltype(Board_DisplayAdviceAgain))Board_DisplayAdviceAgainAddr;
    Board_GridCellWidth = (decltype(Board_GridCellWidth))Board_GridCellWidthAddr;
    Board_GridCellHeight = (decltype(Board_GridCellHeight))Board_GridCellHeightAddr;
    // Board_GetPumpkinAt=(Plant* (*)(Board*,int,int))Board_GetPumpkinAtAddr;
    Board_GetSeedTypeInCursor = (decltype(Board_GetSeedTypeInCursor))Board_GetSeedTypeInCursorAddr;
    Board_TryToSaveGame = (decltype(Board_TryToSaveGame))Board_TryToSaveGameAddr;
    Board_KillAllZombiesInRadius = (decltype(Board_KillAllZombiesInRadius))Board_KillAllZombiesInRadiusAddr;
    Board_RemoveCutsceneZombies = (decltype(Board_RemoveCutsceneZombies))Board_RemoveCutsceneZombiesAddr;
    Board_CountZombiesOnScreen = (decltype(Board_CountZombiesOnScreen))Board_CountZombiesOnScreenAddr;
    Board_GetPosYBasedOnRow = (decltype(Board_GetPosYBasedOnRow))Board_GetPosYBasedOnRowAddr;
    Board_CanTakeDeathMoney = (decltype(Board_CanTakeDeathMoney))Board_CanTakeDeathMoneyAddr;
    Board_GetBossZombie = (decltype(Board_GetBossZombie))Board_GetBossZombieAddr;
    //    Board_GetFlowerPotAt=(int* (*)(int*,int,int))Board_GetFlowerPotAtAddr;
    Board_RemoveAllMowers = (decltype(Board_RemoveAllMowers))Board_RemoveAllMowersAddr;
    Board_ResetLawnMowers = (decltype(Board_ResetLawnMowers))Board_ResetLawnMowersAddr;
    Board_RemoveAllZombies = (decltype(Board_RemoveAllZombies))Board_RemoveAllZombiesAddr;
    Board_GetGamepadControlsByPlayerIndex = (decltype(Board_GetGamepadControlsByPlayerIndex))Board_GetGamepadControlsByPlayerIndexAddr;


    LawnApp_ClearSecondPlayer = (decltype(LawnApp_ClearSecondPlayer))LawnApp_ClearSecondPlayerAddr;
    LawnApp_IsWhackAZombieLevel = (decltype(LawnApp_IsWhackAZombieLevel))LawnApp_IsWhackAZombieLevelAddr;
    LawnApp_IsScaryPotterLevel = (decltype(LawnApp_IsScaryPotterLevel))LawnApp_IsScaryPotterLevelAddr;
    LawnApp_CanShowStore = (decltype(LawnApp_CanShowStore))LawnApp_CanShowStoreAddr;
    LawnApp_CanShowAlmanac = (decltype(LawnApp_CanShowAlmanac))LawnApp_CanShowAlmanacAddr;
    LawnApp_KillNewOptionsDialog = (decltype(LawnApp_KillNewOptionsDialog))LawnApp_KillNewOptionsDialogAddr;
    LawnApp_KillMainMenu = (decltype(LawnApp_KillMainMenu))LawnApp_KillMainMenuAddr;
    LawnApp_KillChallengeScreen = (decltype(LawnApp_KillChallengeScreen))LawnApp_KillChallengeScreenAddr;
    LawnApp_PreNewGame = (decltype(LawnApp_PreNewGame))LawnApp_PreNewGameAddr;
    LawnApp_PlayFoley = (decltype(LawnApp_PlayFoley))LawnApp_PlayFoleyAddr;
    LawnApp_PlayFoleyPitch = (decltype(LawnApp_PlayFoleyPitch))LawnApp_PlayFoleyPitchAddr;
    LawnApp_DoCheatDialog = (decltype(LawnApp_DoCheatDialog))LawnApp_DoCheatDialogAddr;
    LawnApp_DoCheatCodeDialog = (decltype(LawnApp_DoCheatCodeDialog))LawnApp_DoCheatCodeDialogAddr;
    LawnApp_DoUserDialog = (decltype(LawnApp_DoUserDialog))LawnApp_DoUserDialogAddr;
    LawnApp_ReanimationTryToGet = (decltype(LawnApp_ReanimationTryToGet))LawnApp_ReanimationTryToGetAddr;
    LawnApp_IsFirstTimeAdventureMode = (decltype(LawnApp_IsFirstTimeAdventureMode))LawnApp_IsFirstTimeAdventureModeAddr;
    LawnApp_IsAdventureMode = (decltype(LawnApp_IsAdventureMode))LawnApp_IsAdventureModeAddr;
    LawnApp_IsWallnutBowlingLevel = (decltype(LawnApp_IsWallnutBowlingLevel))LawnApp_IsWallnutBowlingLevelAddr;
    LawnApp_IsCoopMode = (decltype(LawnApp_IsCoopMode))LawnApp_IsCoopModeAddr;
    LawnApp_IsTwinSunbankMode = (decltype(LawnApp_IsTwinSunbankMode))LawnApp_IsTwinSunbankModeAddr;
    LawnApp_LawnMessageBox = (decltype(LawnApp_LawnMessageBox))LawnApp_LawnMessageBoxAddr;
    LawnApp_ReanimationGet = (decltype(LawnApp_ReanimationGet))LawnApp_ReanimationGetAddr;
    LawnApp_IsIZombieLevel = (decltype(LawnApp_IsIZombieLevel))LawnApp_IsIZombieLevelAddr;
    LawnApp_AddTodParticle = (decltype(LawnApp_AddTodParticle))LawnApp_AddTodParticleAddr;
    LawnApp_ParticleGetID = (decltype(LawnApp_ParticleGetID))LawnApp_ParticleGetIDAddr;
    LawnApp_AddReanimation = (decltype(LawnApp_AddReanimation))LawnApp_AddReanimationAddr;
    LawnApp_IsSurvivalMode = (decltype(LawnApp_IsSurvivalMode))LawnApp_IsSurvivalModeAddr;
    LawnApp_IsPuzzleMode = (decltype(LawnApp_IsPuzzleMode))LawnApp_IsPuzzleModeAddr;
    LawnApp_HasFinishedAdventure = (decltype(LawnApp_HasFinishedAdventure))LawnApp_HasFinishedAdventureAddr;
    LawnApp_IsFinalBossLevel = (decltype(LawnApp_IsFinalBossLevel))LawnApp_IsFinalBossLevelAddr;
    LawnApp_IsArtChallenge = (decltype(LawnApp_IsArtChallenge))LawnApp_IsArtChallengeAddr;
    LawnApp_KillVSResultsScreen = (decltype(LawnApp_KillVSResultsScreen))LawnApp_KillVSResultsScreenAddr;
    LawnApp_HideHelpBarWidget = (decltype(LawnApp_HideHelpBarWidget))LawnApp_HideHelpBarWidgetAddr;
    LawnApp_ShowHelpTextScreen = (decltype(LawnApp_ShowHelpTextScreen))LawnApp_ShowHelpTextScreenAddr;
    LawnApp_ShowChallengeScreen = (decltype(LawnApp_ShowChallengeScreen))LawnApp_ShowChallengeScreenAddr;
    LawnApp_GetPottedPlantByIndex = (decltype(LawnApp_GetPottedPlantByIndex))LawnApp_GetPottedPlantByIndexAddr;
    LawnApp_CrazyDaveStopTalking = (decltype(LawnApp_CrazyDaveStopTalking))LawnApp_CrazyDaveStopTalkingAddr;
    LawnApp_DoRetryAchievementsDialog = (decltype(LawnApp_DoRetryAchievementsDialog))LawnApp_DoRetryAchievementsDialogAddr;
    LawnApp_EarnedGoldTrophy = (decltype(LawnApp_EarnedGoldTrophy))LawnApp_EarnedGoldTrophyAddr;
    LawnApp_RemoveReanimation = (decltype(LawnApp_RemoveReanimation))LawnApp_RemoveReanimationAddr;
    LawnApp_ReanimationGetID = (decltype(LawnApp_ReanimationGetID))LawnApp_ReanimationGetIDAddr;
    LawnApp_IsSlotMachineLevel = (decltype(LawnApp_IsSlotMachineLevel))LawnApp_IsSlotMachineLevelAddr;
    LawnApp_KillAlmanacDialog = (decltype(LawnApp_KillAlmanacDialog))LawnApp_KillAlmanacDialogAddr;
    LawnApp_IsLittleTroubleLevel = (decltype(LawnApp_IsLittleTroubleLevel))LawnApp_IsLittleTroubleLevelAddr;
    Sexy_SexyAppBase_GetDialog = (decltype(Sexy_SexyAppBase_GetDialog))Sexy_SexyAppBase_GetDialogAddr;
    Sexy_SexyAppBase_EraseFile = (decltype(Sexy_SexyAppBase_EraseFile))Sexy_SexyAppBase_EraseFileAddr;
    Sexy_Ratio_Set = (decltype(Sexy_Ratio_Set))Sexy_Ratio_SetAddr;
    LawnApp_GetNumTrophies = (decltype(LawnApp_GetNumTrophies))LawnApp_GetNumTrophiesAddr;
    LawnApp_IsSurvivalEndless = (decltype(LawnApp_IsSurvivalEndless))LawnApp_IsSurvivalEndlessAddr;
    LawnApp_ShowMainMenuScreen = (decltype(LawnApp_ShowMainMenuScreen))LawnApp_ShowMainMenuScreenAddr;
    LawnApp_ParticleTryToGet = (decltype(LawnApp_ParticleTryToGet))LawnApp_ParticleTryToGetAddr;
    LawnApp_KillHelpTextScreen = (decltype(LawnApp_KillHelpTextScreen))LawnApp_KillHelpTextScreenAddr;
    LawnApp_NextTestDialog = (decltype(LawnApp_NextTestDialog))LawnApp_NextTestDialogAddr;


    Sexy_Graphics_SetDrawMode = (decltype(Sexy_Graphics_SetDrawMode))Sexy_Graphics_SetDrawModeAddr;
    Sexy_Graphics_SetColorizeImages = (decltype(Sexy_Graphics_SetColorizeImages))Sexy_Graphics_SetColorizeImagesAddr;
    Sexy_Graphics_GetColorizeImages = (decltype(Sexy_Graphics_GetColorizeImages))Sexy_Graphics_GetColorizeImagesAddr;
    Sexy_Graphics_SetFont = (decltype(Sexy_Graphics_SetFont))Sexy_Graphics_SetFontAddr;
    Sexy_Graphics_FillRect = (decltype(Sexy_Graphics_FillRect))Sexy_Graphics_FillRectAddr;
    Sexy_Graphics_DrawRect = (decltype(Sexy_Graphics_DrawRect))Sexy_Graphics_DrawRectAddr;
    Sexy_Graphics_ClipRect = (decltype(Sexy_Graphics_ClipRect))Sexy_Graphics_ClipRectAddr;
    Sexy_Graphics_SetClipRect = (decltype(Sexy_Graphics_SetClipRect))Sexy_Graphics_SetClipRectAddr;
    Sexy_Graphics_ClearClipRect = (decltype(Sexy_Graphics_ClearClipRect))Sexy_Graphics_ClearClipRectAddr;
    Sexy_Graphics_SetLinearBlend = (decltype(Sexy_Graphics_SetLinearBlend))Sexy_Graphics_SetLinearBlendAddr;
    Sexy_Graphics_PushState = (decltype(Sexy_Graphics_PushState))Sexy_Graphics_PushStateAddr;
    Sexy_Graphics_PopState = (decltype(Sexy_Graphics_PopState))Sexy_Graphics_PopStateAddr;
    Sexy_Graphics_DrawString = (decltype(Sexy_Graphics_DrawString))Sexy_Graphics_DrawStringAddr;
    Sexy_Graphics_DrawImageCel = (decltype(Sexy_Graphics_DrawImageCel))Sexy_Graphics_DrawImageCelAddr;
    Sexy_Graphics_Graphics = (decltype(Sexy_Graphics_Graphics))Sexy_Graphics_GraphicsAddr;
    Sexy_Graphics_Graphics2 = (decltype(Sexy_Graphics_Graphics2))Sexy_Graphics_Graphics2Addr;
    Sexy_Graphics_Delete2 = (decltype(Sexy_Graphics_Delete2))Sexy_Graphics_Delete2Addr;
    Sexy_Graphics_Translate = (decltype(Sexy_Graphics_Translate))Sexy_Graphics_TranslateAddr;
    Sexy_Graphics_ClearRect = (decltype(Sexy_Graphics_ClearRect))Sexy_Graphics_ClearRectAddr;
    Sexy_Graphics_SetColor = (decltype(Sexy_Graphics_SetColor))Sexy_Graphics_SetColorAddr;
    Sexy_Graphics_DrawTrianglesTex = (decltype(Sexy_Graphics_DrawTrianglesTex))Sexy_Graphics_DrawTrianglesTexAddr;
    Sexy_Graphics_GetColor = (decltype(Sexy_Graphics_GetColor))Sexy_Graphics_GetColorAddr;
    Sexy_Graphics_SetScale = (decltype(Sexy_Graphics_SetScale))Sexy_Graphics_SetScaleAddr;
    Sexy_Graphics_DrawImage = (decltype(Sexy_Graphics_DrawImage))Sexy_Graphics_DrawImageAddr;
    Sexy_Graphics_DrawImageF = (decltype(Sexy_Graphics_DrawImageF))Sexy_Graphics_DrawImageFAddr;
    Sexy_Graphics_DrawImageMirror = (decltype(Sexy_Graphics_DrawImageMirror))Sexy_Graphics_DrawImageMirrorAddr;
    Sexy_Graphics_DrawImage2 = (decltype(Sexy_Graphics_DrawImage2))Sexy_Graphics_DrawImage2Addr;
    Sexy_Graphics_DrawImageCel2 = (decltype(Sexy_Graphics_DrawImageCel2))Sexy_Graphics_DrawImageCel2Addr;
    Sexy_Graphics_DrawImageMatrix = (decltype(Sexy_Graphics_DrawImageMatrix))Sexy_Graphics_DrawImageMatrixAddr;
    Sexy_GLGraphics_SetWrapMode = (decltype(Sexy_GLGraphics_SetWrapMode))Sexy_GLGraphics_SetWrapModeAddr;
    TodDrawImageCelF = (decltype(TodDrawImageCelF))TodDrawImageCelFAddr;


    Plant_GetImage = (decltype(Plant_GetImage))Plant_GetImageAddr;
    Plant_GetPlantRect = (decltype(Plant_GetPlantRect))Plant_GetPlantRectAddr;
    Plant_NotOnGround = (decltype(Plant_NotOnGround))Plant_NotOnGroundAddr;
    Plant_IsOnBoard = (decltype(Plant_IsOnBoard))Plant_IsOnBoardAddr;
    Plant_UpdateAbilities = (decltype(Plant_UpdateAbilities))Plant_UpdateAbilitiesAddr;
    Plant_Animate = (decltype(Plant_Animate))Plant_AnimateAddr;
    Plant_UpdateReanim = (decltype(Plant_UpdateReanim))Plant_UpdateReanimAddr;
    Plant_IsFlying = (decltype(Plant_IsFlying))Plant_IsFlyingAddr;
    Plant_IsNocturnal = (decltype(Plant_IsNocturnal))Plant_IsNocturnalAddr;
    Plant_IsAquatic = (decltype(Plant_IsAquatic))Plant_IsAquaticAddr;
    Plant_DrawShadow = (decltype(Plant_DrawShadow))Plant_DrawShadowAddr;
    Plant_IsPartOfUpgradableTo = (decltype(Plant_IsPartOfUpgradableTo))Plant_IsPartOfUpgradableToAddr;
    Plant_GetDamageRangeFlags = (decltype(Plant_GetDamageRangeFlags))Plant_GetDamageRangeFlagsAddr;
    Plant_IsInPlay = (decltype(Plant_IsInPlay))Plant_IsInPlayAddr;
    Plant_DrawMagnetItemsOnTop = (decltype(Plant_DrawMagnetItemsOnTop))Plant_DrawMagnetItemsOnTopAddr;
    Plant_DrawMagnetItems = (decltype(Plant_DrawMagnetItems))Plant_DrawMagnetItemsAddr;
    GetPlantDefinition = (decltype(GetPlantDefinition))GetPlantDefinitionAddr;


    Zombie_GetZombieRect = (decltype(Zombie_GetZombieRect))Zombie_GetZombieRectAddr;
    Zombie_IsImmobilizied = (decltype(Zombie_IsImmobilizied))Zombie_IsImmobiliziedAddr;
    Zombie_EffectedByDamage = (decltype(Zombie_EffectedByDamage))Zombie_EffectedByDamageAddr;
    Zombie_RemoveColdEffects = (decltype(Zombie_RemoveColdEffects))Zombie_RemoveColdEffectsAddr;
    Zombie_ApplyButter = (decltype(Zombie_ApplyButter))Zombie_ApplyButterAddr;
    Zombie_ApplyBurn = (decltype(Zombie_ApplyBurn))Zombie_ApplyBurnAddr;
    Zombie_StartEating = (decltype(Zombie_StartEating))Zombie_StartEatingAddr;
    Zombie_TakeDamage = (decltype(Zombie_TakeDamage))Zombie_TakeDamageAddr;
    Zombie_IsWalkingBackwards = (decltype(Zombie_IsWalkingBackwards))Zombie_IsWalkingBackwardsAddr;
    Zombie_AddAttachedParticle = (decltype(Zombie_AddAttachedParticle))Zombie_AddAttachedParticleAddr;
    Zombie_CanBeFrozen = (decltype(Zombie_CanBeFrozen))Zombie_CanBeFrozenAddr;
    Zombie_StopEating = (decltype(Zombie_StopEating))Zombie_StopEatingAddr;
    Zombie_DropArm = (decltype(Zombie_DropArm))Zombie_DropArmAddr;
    Zombie_PlayZombieReanim = (decltype(Zombie_PlayZombieReanim))Zombie_PlayZombieReanimAddr;
    Zombie_SetupReanimLayers = (decltype(Zombie_SetupReanimLayers))Zombie_SetupReanimLayersAddr;
    Zombie_SetupShieldReanims = (decltype(Zombie_SetupShieldReanims))Zombie_SetupShieldReanimsAddr;
    Zombie_UpdateReanim = (decltype(Zombie_UpdateReanim))Zombie_UpdateReanimAddr;
    Zombie_UpdateActions = (decltype(Zombie_UpdateActions))Zombie_UpdateActionsAddr;
    Zombie_UpdatePlaying = (decltype(Zombie_UpdatePlaying))Zombie_UpdatePlayingAddr;
    Zombie_IsDeadOrDying = (decltype(Zombie_IsDeadOrDying))Zombie_IsDeadOrDyingAddr;
    Zombie_IsOnBoard = (decltype(Zombie_IsOnBoard))Zombie_IsOnBoardAddr;
    Zombie_ReanimShowPrefix = (decltype(Zombie_ReanimShowPrefix))Zombie_ReanimShowPrefixAddr;
    Zombie_ReanimShowTrack = (decltype(Zombie_ReanimShowTrack))Zombie_ReanimShowTrackAddr;
    Zombie_TakeHelmDamage = (decltype(Zombie_TakeHelmDamage))Zombie_TakeHelmDamageAddr;
    Zombie_IsFlying = (decltype(Zombie_IsFlying))Zombie_IsFlyingAddr;
    Zombie_TakeFlyingDamage = (decltype(Zombie_TakeFlyingDamage))Zombie_TakeFlyingDamageAddr;
    Zombie_TakeShieldDamage = (decltype(Zombie_TakeShieldDamage))Zombie_TakeShieldDamageAddr;
    Zombie_TakeBodyDamage = (decltype(Zombie_TakeBodyDamage))Zombie_TakeBodyDamageAddr;
    Zombie_UpdateDamageStates = (decltype(Zombie_UpdateDamageStates))Zombie_UpdateDamageStatesAddr;
    Zombie_GetShieldDamageIndex = (decltype(Zombie_GetShieldDamageIndex))Zombie_GetShieldDamageIndexAddr;
    Zombie_GetHelmDamageIndex = (decltype(Zombie_GetHelmDamageIndex))Zombie_GetHelmDamageIndexAddr;
    Zombie_GetBodyDamageIndex = (decltype(Zombie_GetBodyDamageIndex))Zombie_GetBodyDamageIndexAddr;
    Zombie_GetTrackPosition = (decltype(Zombie_GetTrackPosition))Zombie_GetTrackPositionAddr;
    Zombie_UpdateAnimationSpeed = (decltype(Zombie_UpdateAnimationSpeed))Zombie_UpdateAnimationSpeedAddr;
    Zombie_HitIceTrap = (decltype(Zombie_HitIceTrap))Zombie_HitIceTrapAddr;
    Zombie_Zombie = (decltype(Zombie_Zombie))Zombie_ZombieAddr;
    //    GetZombieDefinition=(ZombieDefinition & (*)(ZombieType type))GetZombieDefinitionAddr;


    Reanimation_OverrideScale = (decltype(Reanimation_OverrideScale))Reanimation_OverrideScaleAddr;
    Reanimation_SetPosition = (decltype(Reanimation_SetPosition))Reanimation_SetPositionAddr;
    Reanimation_Reanimation = (decltype(Reanimation_Reanimation))Reanimation_ReanimationAddr;
    Reanimation_ReanimationInitializeType = (decltype(Reanimation_ReanimationInitializeType))Reanimation_ReanimationInitializeTypeAddr;
    Reanimation_Draw = (decltype(Reanimation_Draw))Reanimation_DrawAddr;
    Reanimation_Delete2 = (decltype(Reanimation_Delete2))Reanimation_Delete2Addr;
    Reanimation_PlayReanim = (decltype(Reanimation_PlayReanim))Reanimation_PlayReanimAddr;
    Reanimation_FindTrackIndexById = (decltype(Reanimation_FindTrackIndexById))Reanimation_FindTrackIndexByIdAddr;
    Reanimation_GetCurrentTransform = (decltype(Reanimation_GetCurrentTransform))Reanimation_GetCurrentTransformAddr;
    Reanimation_SetAnimRate = (decltype(Reanimation_SetAnimRate))Reanimation_SetAnimRateAddr;
    Reanimation_IsAnimPlaying = (decltype(Reanimation_IsAnimPlaying))Reanimation_IsAnimPlayingAddr;
    Reanimation_DrawRenderGroup = (decltype(Reanimation_DrawRenderGroup))Reanimation_DrawRenderGroupAddr;
    Reanimation_SetImageOverride = (decltype(Reanimation_SetImageOverride))Reanimation_SetImageOverrideAddr;
    Reanimation_FindTrackIndex = (decltype(Reanimation_FindTrackIndex))Reanimation_FindTrackIndexAddr;
    Reanimation_ReanimationDie = (decltype(Reanimation_ReanimationDie))Reanimation_ReanimationDieAddr;
    Reanimation_GetTrackInstanceByName = (decltype(Reanimation_GetTrackInstanceByName))Reanimation_GetTrackInstanceByNameAddr;
    Reanimation_SetFramesForLayer = (decltype(Reanimation_SetFramesForLayer))Reanimation_SetFramesForLayerAddr;
    Reanimation_TrackExists = (decltype(Reanimation_TrackExists))Reanimation_TrackExistsAddr;
    Reanimation_AttachToAnotherReanimation = (decltype(Reanimation_AttachToAnotherReanimation))Reanimation_AttachToAnotherReanimationAddr;
    Reanimation_Update = (decltype(Reanimation_Update))Reanimation_UpdateAddr;
    Reanimation_AssignRenderGroupToTrack = (decltype(Reanimation_AssignRenderGroupToTrack))Reanimation_AssignRenderGroupToTrackAddr;
    Reanimation_MatrixFromTransform = (decltype(Reanimation_MatrixFromTransform))Reanimation_MatrixFromTransformAddr;
    Reanimation_GetFrameTime = (decltype(Reanimation_GetFrameTime))Reanimation_GetFrameTimeAddr;
    Reanimation_ShowOnlyTrack = (decltype(Reanimation_ShowOnlyTrack))Reanimation_ShowOnlyTrackAddr;
    ReanimatorCache_DrawCachedZombie = (decltype(ReanimatorCache_DrawCachedZombie))ReanimatorCache_DrawCachedZombieAddr;
    ReanimatorTransform_ReanimatorTransform = (decltype(ReanimatorTransform_ReanimatorTransform))ReanimatorTransform_ReanimatorTransformAddr;
    AttachReanim = (decltype(AttachReanim))AttachReanimAddr;
    TodScaleRotateTransformMatrix = (decltype(TodScaleRotateTransformMatrix))TodScaleRotateTransformMatrixAddr;
    Reanimation_GetTrackMatrix = (decltype(Reanimation_GetTrackMatrix))Reanimation_GetTrackMatrixAddr;


    StoreScreen_SetSelectedSlot = (decltype(StoreScreen_SetSelectedSlot))StoreScreen_SetSelectedSlotAddr;
    StoreScreen_AdvanceCrazyDaveDialog = (decltype(StoreScreen_AdvanceCrazyDaveDialog))StoreScreen_AdvanceCrazyDaveDialogAddr;
    StoreScreen_CanInteractWithButtons = (decltype(StoreScreen_CanInteractWithButtons))StoreScreen_CanInteractWithButtonsAddr;
    StoreScreen_GetStoreItemType = (decltype(StoreScreen_GetStoreItemType))StoreScreen_GetStoreItemTypeAddr;
    StoreScreen_GetStoreItemInfo = (decltype(StoreScreen_GetStoreItemInfo))StoreScreen_GetStoreItemInfoAddr;
    StoreScreen_IsItemSoldOut = (decltype(StoreScreen_IsItemSoldOut))StoreScreen_IsItemSoldOutAddr;
    StoreScreen_IsItemUnavailable = (decltype(StoreScreen_IsItemUnavailable))StoreScreen_IsItemUnavailableAddr;
    StoreScreen_IsComingSoon = (decltype(StoreScreen_IsComingSoon))StoreScreen_IsComingSoonAddr;
    StoreScreen_IsPottedPlant = (decltype(StoreScreen_IsPottedPlant))StoreScreen_IsPottedPlantAddr;
    //    StoreScreen_PurchaseItem = (void (*)(int *, a::a)) StoreScreen_PurchaseItemAddr;
    StoreScreen_IsPageShown = (decltype(StoreScreen_IsPageShown))StoreScreen_IsPageShownAddr;
    StoreScreen_EnableButtons = (decltype(StoreScreen_EnableButtons))StoreScreen_EnableButtonsAddr;


    CutScene_IsSurvivalRepick = (decltype(CutScene_IsSurvivalRepick))CutScene_IsSurvivalRepickAddr;
    CutScene_ShouldRunUpsellBoard = (decltype(CutScene_ShouldRunUpsellBoard))CutScene_ShouldRunUpsellBoardAddr;
    CutScene_OnKeyDown = (decltype(CutScene_OnKeyDown))CutScene_OnKeyDownAddr;
    CutScene_MouseDown = (decltype(CutScene_MouseDown))CutScene_MouseDownAddr;
    CutScene_IsBeforePreloading = (decltype(CutScene_IsBeforePreloading))CutScene_IsBeforePreloadingAddr;


    ChallengeScreen_SetScrollTarget = (decltype(ChallengeScreen_SetScrollTarget))ChallengeScreen_SetScrollTargetAddr;
    ChallengeScreen_KeyDown = (decltype(ChallengeScreen_KeyDown))ChallengeScreen_KeyDownAddr;
    //    ChallengeScreen_UpdateButtons=(void (*)(ChallengeScreen *))ChallengeScreen_UpdateButtonsAddr;


    GamepadControls_OnButtonUp = (decltype(GamepadControls_OnButtonUp))GamepadControls_OnButtonUpAddr;
    GamepadControls_OnButtonDown = (decltype(GamepadControls_OnButtonDown))GamepadControls_OnButtonDownAddr;
    GamepadControls_OnKeyDown = (decltype(GamepadControls_OnKeyDown))GamepadControls_OnKeyDownAddr;
    GamepadControls_GetSeedBank = (decltype(GamepadControls_GetSeedBank))GamepadControls_GetSeedBankAddr;


    TodDrawImageCelCenterScaledF = (decltype(TodDrawImageCelCenterScaledF))TodDrawImageCelCenterScaledFAddr;
    TodDrawImageScaledF = (decltype(TodDrawImageScaledF))TodDrawImageScaledFAddr;
    TodDrawImageCelScaledF = (decltype(TodDrawImageCelScaledF))TodDrawImageCelScaledFAddr;
    TodDrawImageCenterScaledF = (decltype(TodDrawImageCenterScaledF))TodDrawImageCenterScaledFAddr;
    TodScaleTransformMatrix = (decltype(TodScaleTransformMatrix))TodScaleTransformMatrixAddr;
    TodDrawStringWrapped = (decltype(TodDrawStringWrapped))TodDrawStringWrappedAddr;
    TodDrawStringWrappedHelper = (decltype(TodDrawStringWrappedHelper))TodDrawStringWrappedHelperAddr;
    TodDrawStringMatrix = (decltype(TodDrawStringMatrix))TodDrawStringMatrixAddr;
    TodDrawString = (decltype(TodDrawString))TodDrawStringAddr;
    TodAnimateCurve = (decltype(TodAnimateCurve))TodAnimateCurveAddr;
    TodAnimateCurveFloat = (decltype(TodAnimateCurveFloat))TodAnimateCurveFloatAddr;
    TodAnimateCurveFloatTime = (decltype(TodAnimateCurveFloatTime))TodAnimateCurveFloatTimeAddr;


    MainMenu_InTransition = (decltype(MainMenu_InTransition))MainMenu_InTransitionAddr;
    MainMenu_SetScene = (decltype(MainMenu_SetScene))MainMenu_SetSceneAddr;
    MainMenu_StartAdventureMode = (decltype(MainMenu_StartAdventureMode))MainMenu_StartAdventureModeAddr;


    CursorObject_Draw = (decltype(CursorObject_Draw))CursorObject_DrawAddr;
    CursorObject_Update = (decltype(CursorObject_Update))CursorObject_UpdateAddr;


    ZenGarden_GetStinky = (decltype(ZenGarden_GetStinky))ZenGarden_GetStinkyAddr;
    ZenGarden_IsStinkyHighOnChocolate = (decltype(ZenGarden_IsStinkyHighOnChocolate))ZenGarden_IsStinkyHighOnChocolateAddr;
    ZenGarden_OpenStore = (decltype(ZenGarden_OpenStore))ZenGarden_OpenStoreAddr;
    ZenGarden_GetPottedPlantInWheelbarrow = (decltype(ZenGarden_GetPottedPlantInWheelbarrow))ZenGarden_GetPottedPlantInWheelbarrowAddr;
    ZenGarden_DrawPottedPlant = (decltype(ZenGarden_DrawPottedPlant))ZenGarden_DrawPottedPlantAddr;
    PlantFlowerPotHeightOffset = (decltype(PlantFlowerPotHeightOffset))PlantFlowerPotHeightOffsetAddr;


    Challenge_IZombieGetBrainTarget = (decltype(Challenge_IZombieGetBrainTarget))Challenge_IZombieGetBrainTargetAddr;
    Challenge_GetArtChallengeSeed = (decltype(Challenge_GetArtChallengeSeed))Challenge_GetArtChallengeSeedAddr;
    Challenge_TreeOfWisdomOpenStore = (decltype(Challenge_TreeOfWisdomOpenStore))Challenge_TreeOfWisdomOpenStoreAddr;
    Challenge_IZombieScoreBrain = (decltype(Challenge_IZombieScoreBrain))Challenge_IZombieScoreBrainAddr;
    Challenge_MouseDown = (decltype(Challenge_MouseDown))Challenge_MouseDownAddr;
    Challenge_IsZombieSeedType = (decltype(Challenge_IsZombieSeedType))Challenge_IsZombieSeedTypeAddr;
    Challenge_IsMPSeedType = (decltype(Challenge_IsMPSeedType))Challenge_IsMPSeedTypeAddr;
    Challenge_IsMPSuddenDeath = (decltype(Challenge_IsMPSuddenDeath))Challenge_IsMPSuddenDeathAddr;
    Challenge_InitZombieWavesFromList = (decltype(Challenge_InitZombieWavesFromList))Challenge_InitZombieWavesFromListAddr;
    // Challenge_IZombieSeedTypeToZombieType = (ZombieType (*)(a::a)) Challenge_IZombieSeedTypeToZombieTypeAddr;
    Challenge_ScaryPotterCountSunInPot = (decltype(Challenge_ScaryPotterCountSunInPot))Challenge_ScaryPotterCountSunInPotAddr;
    Challenge_IZombieSetupPlant = (decltype(Challenge_IZombieSetupPlant))Challenge_IZombieSetupPlantAddr;
    Challenge_IZombiePlaceZombie = (decltype(Challenge_IZombiePlaceZombie))Challenge_IZombiePlaceZombieAddr;
    Challenge_GraveDangerSpawnGraveAt = (decltype(Challenge_GraveDangerSpawnGraveAt))Challenge_GraveDangerSpawnGraveAtAddr;
    Challenge_IZombieSetPlantFilterEffect = (decltype(Challenge_IZombieSetPlantFilterEffect))Challenge_IZombieSetPlantFilterEffectAddr;
    Challenge_PlantAdded = (decltype(Challenge_PlantAdded))Challenge_PlantAddedAddr;


    Projectile_GetProjectileRect = (decltype(Projectile_GetProjectileRect))Projectile_GetProjectileRectAddr;
    Projectile_Die = (decltype(Projectile_Die))Projectile_DieAddr;
    Projectile_FindCollisionTargetPlant = (decltype(Projectile_FindCollisionTargetPlant))Projectile_FindCollisionTargetPlantAddr;
    Projectile_GetProjectileDef = (decltype(Projectile_GetProjectileDef))Projectile_GetProjectileDefAddr;
    Projectile_CantHitHighGround = (decltype(Projectile_CantHitHighGround))Projectile_CantHitHighGroundAddr;
    Projectile_FindCollisionTarget = (decltype(Projectile_FindCollisionTarget))Projectile_FindCollisionTargetAddr;
    Projectile_FindCollisionTargetGridItem = (decltype(Projectile_FindCollisionTargetGridItem))Projectile_FindCollisionTargetGridItemAddr;
    Projectile_DoImpactGridItem = (decltype(Projectile_DoImpactGridItem))Projectile_DoImpactGridItemAddr;
    Projectile_PlayImpactSound = (decltype(Projectile_PlayImpactSound))Projectile_PlayImpactSoundAddr;
    Projectile_IsSplashDamage = (decltype(Projectile_IsSplashDamage))Projectile_IsSplashDamageAddr;
    Projectile_DoSplashDamage = (decltype(Projectile_DoSplashDamage))Projectile_DoSplashDamageAddr;
    Projectile_GetDamageFlags = (decltype(Projectile_GetDamageFlags))Projectile_GetDamageFlagsAddr;
    Projectile_PeaAboutToHitTorchwood = (decltype(Projectile_PeaAboutToHitTorchwood))Projectile_PeaAboutToHitTorchwoodAddr;


    GameButton_IsMouseOver = (decltype(GameButton_IsMouseOver))GameButton_IsMouseOverAddr;
    GameButton_OnPressed = (decltype(GameButton_OnPressed))GameButton_OnPressedAddr;
    GameButton_Delete = (decltype(GameButton_Delete))GameButton_DeleteAddr;
    GameButton_Resize = (decltype(GameButton_Resize))GameButton_ResizeAddr;
    GameButton_GameButton = (decltype(GameButton_GameButton))GameButton_GameButtonAddr;
    GameButton_SetLabel = (decltype(GameButton_SetLabel))GameButton_SetLabelAddr;
    GameButton_SetDisabled = (decltype(GameButton_SetDisabled))GameButton_SetDisabledAddr;
    GameButton_Update = (decltype(GameButton_Update))GameButton_UpdateAddr;
    GameButton_Draw = (decltype(GameButton_Draw))GameButton_DrawAddr;
    MakeButton = (decltype(MakeButton))MakeButtonAddr;
    MakeNewCheckbox = (decltype(MakeNewCheckbox))MakeNewCheckboxAddr;
    Sexy_ButtonWidget_ButtonWidget = (decltype(Sexy_ButtonWidget_ButtonWidget))Sexy_ButtonWidget_ButtonWidgetAddr;


    AlmanacDialog_SeedHitTest = (decltype(AlmanacDialog_SeedHitTest))AlmanacDialog_SeedHitTestAddr;
    AlmanacDialog_ZombieHitTest = (decltype(AlmanacDialog_ZombieHitTest))AlmanacDialog_ZombieHitTestAddr;
    AlmanacDialog_SetupPlant = (decltype(AlmanacDialog_SetupPlant))AlmanacDialog_SetupPlantAddr;
    AlmanacDialog_SetupZombie = (decltype(AlmanacDialog_SetupZombie))AlmanacDialog_SetupZombieAddr;
    AlmanacDialog_KeyDown = (decltype(AlmanacDialog_KeyDown))AlmanacDialog_KeyDownAddr;
    AlmanacDialog_GetSeedPosition = (decltype(AlmanacDialog_GetSeedPosition))AlmanacDialog_GetSeedPositionAddr;


    SeedChooserScreen_CancelLawnView = (decltype(SeedChooserScreen_CancelLawnView))SeedChooserScreen_CancelLawnViewAddr;
    SeedChooserScreen_GetNextSeedInDir = (decltype(SeedChooserScreen_GetNextSeedInDir))SeedChooserScreen_GetNextSeedInDirAddr;
    SeedChooserScreen_GetSeedPositionInChooser = (decltype(SeedChooserScreen_GetSeedPositionInChooser))SeedChooserScreen_GetSeedPositionInChooserAddr;
    //    SeedChooserScreen_GetSeedPositionInBank=(void (*)(SeedChooserScreen*,int,int*,int*,int))SeedChooserScreen_GetSeedPositionInBankAddr;
    SeedChooserScreen_UpdateImitaterButton = (decltype(SeedChooserScreen_UpdateImitaterButton))SeedChooserScreen_UpdateImitaterButtonAddr;
    SeedChooserScreen_SeedHitTest = (decltype(SeedChooserScreen_SeedHitTest))SeedChooserScreen_SeedHitTestAddr;
    //    SeedChooserScreen_ButtonDePress = (void (*)(SeedChooserScreen *, int)) SeedChooserScreen_ButtonDepressAddr;
    SeedChooserScreen_LandFlyingSeed = (decltype(SeedChooserScreen_LandFlyingSeed))SeedChooserScreen_LandFlyingSeedAddr;
    //    SeedChooserScreen_ClickedSeedInBank = (void (*)(int *, int *, unsigned int)) SeedChooserScreen_ClickedSeedInBankAddr;
    //    SeedChooserScreen_GameButtonDown = (int (*)(int *, int, unsigned int)) SeedChooserScreen_GameButtonDownAddr;
    SeedChooserScreen_CloseSeedChooser = (decltype(SeedChooserScreen_CloseSeedChooser))SeedChooserScreen_CloseSeedChooserAddr;
    //    SeedChooserScreen_OnKeyDown = (void (*)(int *, int, unsigned int)) SeedChooserScreen_OnKeyDownAddr;
    SeedChooserScreen_HasPacket = (decltype(SeedChooserScreen_HasPacket))SeedChooserScreen_HasPacketAddr;
    SeedChooserScreen_Has7Rows = (decltype(SeedChooserScreen_Has7Rows))SeedChooserScreen_Has7RowsAddr;


    Sexy_SexyTransform2D_SexyTransform2D = (decltype(Sexy_SexyTransform2D_SexyTransform2D))Sexy_SexyTransform2D_SexyTransform2DAddr;
    Sexy_SexyTransform2D_Scale = (decltype(Sexy_SexyTransform2D_Scale))Sexy_SexyTransform2D_ScaleAddr;
    Sexy_SexyTransform2D_Translate = (decltype(Sexy_SexyTransform2D_Translate))Sexy_SexyTransform2D_TranslateAddr;
    Sexy_SexyTransform2D_RotateRad = (decltype(Sexy_SexyTransform2D_RotateRad))Sexy_SexyTransform2D_RotateRadAddr;


    SeedPacket_DrawBackground = (decltype(SeedPacket_DrawBackground))SeedPacket_DrawBackgroundAddr;
    // SeedPacket_MouseDown = (void (*)(int *, int, int, int)) SeedPacket_MouseDownAddr;
    SeedPacket_CanPickUp = (decltype(SeedPacket_CanPickUp))SeedPacket_CanPickUpAddr;
    SeedPacket_MouseHitTest = (decltype(SeedPacket_MouseHitTest))SeedPacket_MouseHitTestAddr;
    SeedPacket_GetPlayerIndex = (decltype(SeedPacket_GetPlayerIndex))SeedPacket_GetPlayerIndexAddr;
    SeedPacket_DrawMiddle = (decltype(SeedPacket_DrawMiddle))SeedPacket_DrawMiddleAddr;


    GameObject_BeginDraw = (decltype(GameObject_BeginDraw))GameObject_BeginDrawAddr;
    GameObject_EndDraw = (decltype(GameObject_EndDraw))GameObject_EndDrawAddr;


    Coin_MouseDown = (decltype(Coin_MouseDown))Coin_MouseDownAddr;
    Coin_Collect = (decltype(Coin_Collect))Coin_CollectAddr;
    Coin_Die = (decltype(Coin_Die))Coin_DieAddr;
    Coin_IsLevelAward = (decltype(Coin_IsLevelAward))Coin_IsLevelAwardAddr;
    Coin_IsPresentWithAdvice = (decltype(Coin_IsPresentWithAdvice))Coin_IsPresentWithAdviceAddr;
    Coin_IsMoney = (decltype(Coin_IsMoney))Coin_IsMoneyAddr;
    Coin_PlayGroundSound = (decltype(Coin_PlayGroundSound))Coin_PlayGroundSoundAddr;
    Coin_GetDisappearTime = (decltype(Coin_GetDisappearTime))Coin_GetDisappearTimeAddr;
    Coin_StartFade = (decltype(Coin_StartFade))Coin_StartFadeAddr;
    Coin_GetSunScale = (decltype(Coin_GetSunScale))Coin_GetSunScaleAddr;


    GetRectOverlap = (decltype(GetRectOverlap))GetRectOverlapAddr;
    Sexy_StrFormat = (decltype(Sexy_StrFormat))Sexy_StrFormatAddr;
    TodStringTranslate = (decltype(TodStringTranslate))TodStringTranslateAddr;
    //    DrawSeedPacket = (void (*)(Sexy::Graphics *, int, int, int, int, float, int, bool, bool, bool,bool)) DrawSeedPacketAddr;
    VSSetupMenu_GameButtonDown = (decltype(VSSetupMenu_GameButtonDown))VSSetupMenu_GameButtonDownAddr;
    WaitForSecondPlayerDialog_GameButtonDown = (decltype(WaitForSecondPlayerDialog_GameButtonDown))WaitForSecondPlayerDialog_GameButtonDownAddr;
    HelpTextScreen_KeyDown = (decltype(HelpTextScreen_KeyDown))HelpTextScreen_KeyDownAddr;
    Attachment_AttachmentDie = (decltype(Attachment_AttachmentDie))AttachmentDieAddr;
    AwardScreen_StartButtonPressed = (decltype(AwardScreen_StartButtonPressed))AwardScreen_StartButtonPressedAddr;
    CursorPreview_Update = (decltype(CursorPreview_Update))CursorPreview_UpdateAddr;
    ShopSeedPacket_Update = (decltype(ShopSeedPacket_Update))ShopSeedPacket_UpdateAddr;
    GetFlashingColor = (decltype(GetFlashingColor))GetFlashingColorAddr;
    LawnPlayerInfo_GetFlag = (decltype(LawnPlayerInfo_GetFlag))LawnPlayerInfo_GetFlagAddr;
    RandRangeInt = (decltype(RandRangeInt))RandRangeIntAddr;
    //    DrawSeedType = (void (*)(float *, float, float, int, int, float, float,float)) DrawSeedTypeAddr;
    MailScreen_KeyDown = (decltype(MailScreen_KeyDown))MailScreen_KeyDownAddr;
    Sexy_GamepadApp_HasGamepad = (decltype(Sexy_GamepadApp_HasGamepad))Sexy_GamepadApp_HasGamepadAddr;
    Sexy_RandInt = (decltype(Sexy_RandInt))Sexy_RandIntAddr;
    Sexy_SexyMatrix3_SexyMatrix3 = (decltype(Sexy_SexyMatrix3_SexyMatrix3))Sexy_SexyMatrix3_SexyMatrix3Addr;
    GridItem_GridItemDie = (decltype(GridItem_GridItemDie))GridItem_GridItemDieAddr;
    Sexy_SexyAppBase_GetImage = (decltype(Sexy_SexyAppBase_GetImage))Sexy_SexyAppBase_GetImageAddr;
    Sexy_Widget_Resize = (decltype(Sexy_Widget_Resize))Sexy_Widget_ResizeAddr;
    Sexy_Widget_Widget = (decltype(Sexy_Widget_Widget))Sexy_Widget_WidgetAddr;
    Sexy_Widget_SetVisible = (decltype(Sexy_Widget_SetVisible))Sexy_Widget_SetVisibleAddr;
    Sexy_WidgetManager_SetFocus = (decltype(Sexy_WidgetManager_SetFocus))Sexy_WidgetManager_SetFocusAddr;
    Sexy_WidgetContainer_SetFocus = (decltype(Sexy_WidgetContainer_SetFocus))Sexy_WidgetContainer_SetFocusAddr;
    Sexy_WidgetManager_GetWidgetAt = (decltype(Sexy_WidgetManager_GetWidgetAt))Sexy_WidgetManager_GetWidgetAtAddr;
    Sexy_Image_GetWidth = (decltype(Sexy_Image_GetWidth))Sexy_Image_GetWidthAddr;
    Sexy_Image_GetHeight = (decltype(Sexy_Image_GetHeight))Sexy_Image_GetHeightAddr;
    Sexy_Image_GetCelHeight = (decltype(Sexy_Image_GetCelHeight))Sexy_Image_GetCelHeightAddr;
    Sexy_Image_SetWrapMode = (decltype(Sexy_Image_SetWrapMode))Sexy_Image_SetWrapModeAddr;
    Sexy_WidgetContainer_MarkDirty = (decltype(Sexy_WidgetContainer_MarkDirty))Sexy_WidgetContainer_MarkDirtyAddr;
    ImitaterDialog_SeedHitTest = (decltype(ImitaterDialog_SeedHitTest))ImitaterDialog_SeedHitTestAddr;
    SaveGameContext_SyncInt = (decltype(SaveGameContext_SyncInt))SaveGameContext_SyncIntAddr;
    Sexy_ScrollbarWidget_SetMaxValue = (decltype(Sexy_ScrollbarWidget_SetMaxValue))Sexy_ScrollbarWidget_SetMaxValueAddr;
    PlantDrawHeightOffset = (decltype(PlantDrawHeightOffset))PlantDrawHeightOffsetAddr;
    //    GetChallengeDefinition = (ChallengeDefinition& (*)(int)) GetChallengeDefinitionAddr;
    TypingCheck_SetPhrase = (decltype(TypingCheck_SetPhrase))TypingCheck_SetPhraseAddr;
    Sexy_SexyAppBase_RegistryReadString = (decltype(Sexy_SexyAppBase_RegistryReadString))Sexy_SexyAppBase_RegistryReadStringAddr;
    Sexy_SexyAppBase_CopyImage = (decltype(Sexy_SexyAppBase_CopyImage))Sexy_SexyAppBase_CopyImageAddr;
    Sexy_SexyAppBase_CopyImage2 = (decltype(Sexy_SexyAppBase_CopyImage2))Sexy_SexyAppBase_CopyImage2Addr;
    Sexy_MemoryImage_MemoryImage = (decltype(Sexy_MemoryImage_MemoryImage))Sexy_MemoryImage_MemoryImageAddr;
    //    Sexy_MemoryImage_ClearRect=(void (*)(Sexy::Image *,TRect*))Sexy_MemoryImage_ClearRectAddr;
    Sexy_MemoryImage_GetBits = (decltype(Sexy_MemoryImage_GetBits))Sexy_MemoryImage_GetBitsAddr;
    Sexy_MemoryImage_Create = (decltype(Sexy_MemoryImage_Create))Sexy_MemoryImage_CreateAddr;
    Sexy_MemoryImage_SetImageMode = (decltype(Sexy_MemoryImage_SetImageMode))Sexy_MemoryImage_SetImageModeAddr;
    Sexy_MemoryImage_Delete = (decltype(Sexy_MemoryImage_Delete))Sexy_MemoryImage_DeleteAddr;
    Sexy_MemoryImage_WriteToPng = (decltype(Sexy_MemoryImage_WriteToPng))Sexy_MemoryImage_WriteToPngAddr;
    Sexy_MemoryImage_WriteToJPEG = (decltype(Sexy_MemoryImage_WriteToJPEG))Sexy_MemoryImage_WriteToJPEGAddr;
    Sexy_MemoryImage_BitsChanged = (decltype(Sexy_MemoryImage_BitsChanged))Sexy_MemoryImage_BitsChangedAddr;
    FilterEffectDoWashedOut = (decltype(FilterEffectDoWashedOut))FilterEffectDoWashedOutAddr;
    FilterEffectDoLessWashedOut = (decltype(FilterEffectDoLessWashedOut))FilterEffectDoLessWashedOutAddr;
    FilterEffectDoWhite = (decltype(FilterEffectDoWhite))FilterEffectDoWhiteAddr;
    FilterEffectDoLumSat = (decltype(FilterEffectDoLumSat))FilterEffectDoLumSatAddr;
    HouseChooserDialog_GameButtonDown = (decltype(HouseChooserDialog_GameButtonDown))HouseChooserDialog_GameButtonDownAddr;
    ReanimAtlas_GetEncodedReanimAtlas = (decltype(ReanimAtlas_GetEncodedReanimAtlas))ReanimAtlas_GetEncodedReanimAtlasAddr;
    ReanimatorEnsureDefinitionLoaded = (decltype(ReanimatorEnsureDefinitionLoaded))ReanimatorEnsureDefinitionLoadedAddr;
    ReanimatorCache_GetPlantImageSize = (decltype(ReanimatorCache_GetPlantImageSize))ReanimatorCache_GetPlantImageSizeAddr;
    ReanimatorCache_MakeCachedPlantFrame = (decltype(ReanimatorCache_MakeCachedPlantFrame))ReanimatorCache_MakeCachedPlantFrameAddr;
    ReanimatorCache_MakeBlankCanvasImage = (decltype(ReanimatorCache_MakeBlankCanvasImage))ReanimatorCache_MakeBlankCanvasImageAddr;
    ReanimatorCache_DrawReanimatorFrame = (decltype(ReanimatorCache_DrawReanimatorFrame))ReanimatorCache_DrawReanimatorFrameAddr;
    FindGlobalAllocator = (decltype(FindGlobalAllocator))FindGlobalAllocatorAddr;
    AttachParticle = (decltype(AttachParticle))AttachParticleAddr;
    TodLoadResources = (decltype(TodLoadResources))TodLoadResourcesAddr;
    TodParticleSystem_Draw = (decltype(TodParticleSystem_Draw))TodParticleSystem_DrawAddr;
    //    Sexy_SexyAppBase_Is3DAccelerated = (bool (*)(LawnApp *)) Sexy_SexyAppBase_Is3DAcceleratedAddr;
    //    Sexy_SexyAppBase_Set3DAccelerated=(void (*)(LawnApp*,bool))Sexy_SexyAppBase_Set3DAcceleratedAddr;
    Sexy_ResourceManager_GetSoundThrow = (decltype(Sexy_ResourceManager_GetSoundThrow))Sexy_ResourceManager_GetSoundThrowAddr;
    ToolTipWidget_SetWarningText = (decltype(ToolTipWidget_SetWarningText))ToolTipWidget_SetWarningTextAddr;
    TestMenuWidget_TestMenuWidget = (decltype(TestMenuWidget_TestMenuWidget))TestMenuWidget_TestMenuWidgetAddr;
    RandRangeFloat = (decltype(RandRangeFloat))RandRangeFloatAddr;
    PoolEffect_BilinearLookupFixedPoint = (decltype(PoolEffect_BilinearLookupFixedPoint))PoolEffect_BilinearLookupFixedPointAddr;
    Sexy_DefaultProfileMgr_GetAnyProfile = (decltype(Sexy_DefaultProfileMgr_GetAnyProfile))Sexy_DefaultProfileMgr_GetAnyProfileAddr;
    // Sexy_WidgetManager_MouseDown=(int (*)(int *manager, int x, int y, int theClickCount))Sexy_WidgetManager_MouseDownAddr;
    SeedBank_GetNumSeedsOnConveyorBelt = (decltype(SeedBank_GetNumSeedsOnConveyorBelt))SeedBank_GetNumSeedsOnConveyorBeltAddr;
    // SeedBank_ContainsPoint=(bool (*)(SeedBank *, int x, int y))SeedBank_ContainsPointAddr;
    Music2_Delete = (decltype(Music2_Delete))Music2_DeleteAddr;
    Music_Music = (decltype(Music_Music))Music_MusicAddr;
    //    Music2_Music2=(void (*)(Music2*))Music2_Music2Addr;
    Music_StopAllMusic = (decltype(Music_StopAllMusic))Music_StopAllMusicAddr;
    //    Music_MusicResync=(void (*)(Music*))Music_MusicResyncAddr;
    Music_GetMusicOrder = (decltype(Music_GetMusicOrder))Music_GetMusicOrderAddr;
    // Music_PlayFromOffset=(void (*)(Music*,MusicFile::MusicFile,int,double))Music_PlayFromOffsetAddr;
    Music_SetupMusicFileForTune = (decltype(Music_SetupMusicFileForTune))Music_SetupMusicFileForTuneAddr;
    Sexy_AudiereMusicInterface_SetVolume = (decltype(Sexy_AudiereMusicInterface_SetVolume))Sexy_AudiereMusicInterface_SetVolumeAddr;
    Sexy_AudiereMusicInterface_SetSongVolume = (decltype(Sexy_AudiereMusicInterface_SetSongVolume))Sexy_AudiereMusicInterface_SetSongVolumeAddr;
    Sexy_AudiereMusicInterface_PlayMusic = (decltype(Sexy_AudiereMusicInterface_PlayMusic))Sexy_AudiereMusicInterface_PlayMusicAddr;
    Sexy_AudiereMusicInterface_StopMusic = (decltype(Sexy_AudiereMusicInterface_StopMusic))Sexy_AudiereMusicInterface_StopMusicAddr;
    Sexy_AudiereMusicInterface_SetChannelVolume = (decltype(Sexy_AudiereMusicInterface_SetChannelVolume))Sexy_AudiereMusicInterface_SetChannelVolumeAddr;
    TodFoley_IsFoleyPlaying = (decltype(TodFoley_IsFoleyPlaying))TodFoley_IsFoleyPlayingAddr;
    TodFoley_StopFoley = (decltype(TodFoley_StopFoley))TodFoley_StopFoleyAddr;
    SoundSystemFindInstance = (decltype(SoundSystemFindInstance))SoundSystemFindInstanceAddr;
    TodStringListLoad = (decltype(TodStringListLoad))TodStringListLoadAddr;
    TodReplaceString = (decltype(TodReplaceString))TodReplaceStringAddr;
    TodReplaceNumberString = (decltype(TodReplaceNumberString))TodReplaceNumberStringAddr;
    Sexy_AudiereSoundManager_LoadSound = (decltype(Sexy_AudiereSoundManager_LoadSound))Sexy_AudiereSoundManager_LoadSoundAddr;
    MessageWidget_MessageWidget = (decltype(MessageWidget_MessageWidget))MessageWidget_MessageWidgetAddr;
    MessageWidget_Delete = (decltype(MessageWidget_Delete))MessageWidget_DeleteAddr;
    MessageWidget_GetFont = (decltype(MessageWidget_GetFont))MessageWidget_GetFontAddr;
    MaskHelpWidget_MaskHelpWidget = (decltype(MaskHelpWidget_MaskHelpWidget))MaskHelpWidget_MaskHelpWidgetAddr;
    MaskHelpWidget_Delete = (decltype(MaskHelpWidget_Delete))MaskHelpWidget_DeleteAddr;
    DaveHelp_DaveHelp = (decltype(DaveHelp_DaveHelp))DaveHelp_DaveHelpAddr;
    //    TrashBin_TrashBin=(void (*)(ZOMBIE_TRASH_BIN *, int , float ))TrashBin_TrashBinAddr;
    TrashBin_Delete = (decltype(TrashBin_Delete))TrashBin_DeleteAddr;
    ConfirmBackToMainDialog_ConfirmBackToMainDialog = (decltype(ConfirmBackToMainDialog_ConfirmBackToMainDialog))ConfirmBackToMainDialog_ConfirmBackToMainDialogAddr;
    Sexy_Widget_Move = (decltype(Sexy_Widget_Move))Sexy_Widget_MoveAddr;
    TodParticleSystem_OverrideColor = (decltype(TodParticleSystem_OverrideColor))TodParticleSystem_OverrideColorAddr;
    TodParticleSystem_OverrideImage = (decltype(TodParticleSystem_OverrideImage))TodParticleSystem_OverrideImageAddr;
    TodParticleSystem_Delete2 = (decltype(TodParticleSystem_Delete2))TodParticleSystem_Delete2Addr;
    TodParticleSystem_ParticleSystemDie = (decltype(TodParticleSystem_ParticleSystemDie))TodParticleSystem_ParticleSystemDieAddr;
    DrawCheckboxText = (decltype(DrawCheckboxText))DrawCheckboxTextAddr;
    Sexy_Checkbox_Delete = (decltype(Sexy_Checkbox_Delete))Sexy_Checkbox_DeleteAddr;
    CreditScreen_PauseCredits = (decltype(CreditScreen_PauseCredits))CreditScreen_PauseCreditsAddr;
    Sexy_MenuWidget_Draw = (decltype(Sexy_MenuWidget_Draw))Sexy_MenuWidget_DrawAddr;
    Sexy_Widget_DeferOverlay = (decltype(Sexy_Widget_DeferOverlay))Sexy_Widget_DeferOverlayAddr;
    Mailbox_GetNumUnseenMessages = (decltype(Mailbox_GetNumUnseenMessages))Mailbox_GetNumUnseenMessagesAddr;
    LawnMower_StartMower = (decltype(LawnMower_StartMower))LawnMower_StartMowerAddr;

    Native_BridgeApp_getJNIEnv = (decltype(Native_BridgeApp_getJNIEnv))Native_BridgeApp_getJNIEnvAddr;
    Native_NativeApp_getActivity = (decltype(Native_NativeApp_getActivity))Native_NativeApp_getActivityAddr;
    Native_BridgeApp_getSingleton = (decltype(Native_BridgeApp_getSingleton))Native_BridgeApp_getSingletonAddr;
    Native_NativeApp_getPackageName = (decltype(Native_NativeApp_getPackageName))Native_NativeApp_getPackageNameAddr;
}


inline void InitHookFunction() {
    homura::HookFunction(LawnApp_LawnAppAddr, &LawnApp_LawnApp, &old_LawnApp_LawnApp);
    homura::HookFunction(LawnApp_InitAddr, &LawnApp_Init, &old_LawnApp_Init);
    homura::HookFunction(LawnApp_IsNightAddr, &LawnApp_IsNight, &old_LawnApp_IsNight);
    homura::HookFunction(LawnApp_HardwareInitAddr, &LawnApp_HardwareInit, &old_LawnApp_HardwareInit);
    homura::HookFunction(LawnApp_DoBackToMainAddr, &LawnApp_DoBackToMain, &old_LawnApp_DoBackToMain);
    homura::HookFunction(LawnApp_CanShopLevelAddr, &LawnApp_CanShopLevel, &old_LawnApp_CanShopLevel);
    homura::HookFunction(LawnApp_DoNewOptionsAddr, &LawnApp_DoNewOptions, &old_LawnApp_DoNewOptions);
    homura::HookFunction(LawnApp_GetNumPreloadingTasksAddr, &LawnApp_GetNumPreloadingTasks, &old_LawnApp_GetNumPreloadingTasks);
    homura::HookFunction(LawnApp_DoConfirmBackToMainAddr, &LawnApp_DoConfirmBackToMain, nullptr);
    homura::HookFunction(LawnApp_TrophiesNeedForGoldSunflowerAddr, &LawnApp_TrophiesNeedForGoldSunflower, nullptr);
    homura::HookFunction(LawnApp_GamepadToPlayerIndexAddr, &LawnApp_GamepadToPlayerIndex, &old_LawnApp_GamepadToPlayerIndex);
    homura::HookFunction(LawnApp_ShowCreditScreenAddr, &LawnApp_ShowCreditScreen, &old_LawnApp_ShowCreditScreen);
    homura::HookFunction(LawnApp_OnSessionTaskFailedAddr, &LawnApp_OnSessionTaskFailed, nullptr);
    homura::HookFunction(LawnApp_UpdateAppAddr, &LawnApp_UpdateApp, &old_LawnApp_UpDateApp);
    homura::HookFunction(LawnApp_ShowAwardScreenAddr, &LawnApp_ShowAwardScreen, &old_LawnApp_ShowAwardScreen);
    homura::HookFunction(LawnApp_KillAwardScreenAddr, &LawnApp_KillAwardScreen, &old_LawnApp_KillAwardScreen);
    homura::HookFunction(LawnApp_LoadLevelConfigurationAddr, &LawnApp_LoadLevelConfiguration, &old_LawnApp_LoadLevelConfiguration);
    homura::HookFunction(LawnApp_LoadingThreadProcAddr, &LawnApp_LoadingThreadProc, &old_LawnApp_LoadingThreadProc);
    homura::HookFunction(LawnApp_IsChallengeWithoutSeedBankAddr, &LawnApp_IsChallengeWithoutSeedBank, &old_LawnApp_IsChallengeWithoutSeedBank);
    homura::HookFunction(LawnApp_TryHelpTextScreenAddr, &LawnApp_TryHelpTextScreen, nullptr);
    homura::HookFunction(LawnApp_KillSeedChooserScreenAddr, &LawnApp_KillSeedChooserScreen, &old_LawnApp_KillSeedChooserScreen);
//    homura::HookFunction(LawnApp_HasSeedTypeAddr, &LawnApp_HasSeedType, &old_LawnApp_HasSeedType);


    homura::HookFunction(Board_UpdateAddr, &Board::Update, &old_Board_Update);
    homura::HookFunction(Board_BoardAddr, &Board::Create, &old_Board_Board);
    homura::HookFunction(Board_InitLevelAddr, &Board::InitLevel, &old_Board_InitLevel);
    homura::HookFunction(Board_RemovedFromManagerAddr, &Board::RemovedFromManager, &old_Board_RemovedFromManager);
    homura::HookFunction(Board_FadeOutLevelAddr, &Board::FadeOutLevel, &old_Board_FadeOutLevel);
    homura::HookFunction(Board_AddPlantAddr, &Board::AddPlant, &old_Board_AddPlant);
    homura::HookFunction(Board_AddSunMoneyAddr, &Board::AddSunMoney, &old_Board_AddSunMoney);
    homura::HookFunction(Board_AddDeathMoneyAddr, &Board::AddDeathMoney, &old_Board_AddDeathMoney);
    homura::HookFunction(Board_CanPlantAtAddr, &Board::CanPlantAt, &old_Board_CanPlantAt);
    homura::HookFunction(Board_PlantingRequirementsMetAddr, &Board::PlantingRequirementsMet, &old_Board_PlantingRequirementsMet);
    homura::HookFunction(Board_GetFlowerPotAtAddr, &Board::GetFlowerPotAt, nullptr);
    homura::HookFunction(Board_GetPumpkinAtAddr, &Board::GetPumpkinAt, nullptr);
    homura::HookFunction(Board_ZombiesWonAddr, &Board::ZombiesWon, &old_BoardZombiesWon);
    homura::HookFunction(Board_KeyDownAddr, &Board::KeyDown, &old_Board_KeyDown);
    homura::HookFunction(Board_UpdateSunSpawningAddr, &Board::UpdateSunSpawning, &old_Board_UpdateSunSpawning);
    homura::HookFunction(Board_UpdateZombieSpawningAddr, &Board::UpdateZombieSpawning, &old_Board_UpdateZombieSpawning);
    homura::HookFunction(Board_PickBackgroundAddr, &Board::PickBackground, &old_Board_PickBackground);
    homura::HookFunction(Board_DrawCoverLayerAddr, &Board::DrawCoverLayer, nullptr);
    homura::HookFunction(Board_UpdateGameAddr, &Board::UpdateGame, &old_Board_UpdateGame);
    homura::HookFunction(Board_UpdateGameObjectsAddr, &Board::UpdateGameObjects, &old_Board_UpdateGameObjects);
    homura::HookFunction(Board_IsFlagWaveAddr, &Board::IsFlagWave, &old_Board_IsFlagWave);
    homura::HookFunction(Board_SpawnZombieWaveAddr, &Board::SpawnZombieWave, &old_Board_SpawnZombieWave);
    homura::HookFunction(Board_DrawProgressMeterAddr, &Board::DrawProgressMeter, &old_Board_DrawProgressMeter);
    homura::HookFunction(Board_GetNumWavesPerFlagAddr, &Board::GetNumWavesPerFlag, nullptr);
    homura::HookFunction(Board_IsLevelDataLoadedAddr, &Board::IsLevelDataLoaded, &old_Board_IsLevelDataLoaded);
    homura::HookFunction(Board_NeedSaveGameAddr, &Board::NeedSaveGame, &old_Board_NeedSaveGame);
    homura::HookFunction(Board_UpdateFwooshAddr, &Board::UpdateFwoosh, &old_Board_UpdateFwoosh);
    homura::HookFunction(Board_UpdateFogAddr, &Board::UpdateFog, &old_Board_UpdateFog);
    homura::HookFunction(Board_DrawFogAddr, &Board::DrawFog, &old_Board_DrawFog);
    homura::HookFunction(Board_UpdateIceAddr, &Board::UpdateIce, &old_Board_UpdateIce);
    homura::HookFunction(Board_DrawBackdropAddr, &Board::DrawBackdrop, &old_Board_DrawBackdrop);
    homura::HookFunction(Board_RowCanHaveZombieTypeAddr, &Board::RowCanHaveZombieType, &old_Board_RowCanHaveZombieType);
    homura::HookFunction(Board_DrawDebugTextAddr, &Board::DrawDebugText, &old_Board_DrawDebugText);
    homura::HookFunction(Board_DrawDebugObjectRectsAddr, &Board::DrawDebugObjectRects, &old_Board_DrawDebugObjectRects);
    homura::HookFunction(Board_DrawFadeOutAddr, &Board::DrawFadeOut, nullptr);
    homura::HookFunction(Board_GetCurrentPlantCostAddr, &Board::GetCurrentPlantCost, &old_Board_GetCurrentPlantCost);
    homura::HookFunction(Board_PauseAddr, &Board::Pause, &old_Board_Pause);
    homura::HookFunction(Board_AddSecondPlayerAddr, &Board::AddSecondPlayer, nullptr);
    homura::HookFunction(Board_IsLastStandFinalStageAddr, &Board::IsLastStandFinalStage, nullptr);
    homura::HookFunction(Board_MouseHitTestAddr, &Board::MouseHitTest, &old_Board_MouseHitTest);
    homura::HookFunction(Board_DrawShovelAddr, &Board::DrawShovel, nullptr);
    homura::HookFunction(Board_StageHasPoolAddr, &Board::StageHasPool, nullptr);
    homura::HookFunction(Board_AddZombieInRowAddr, &Board::AddZombieInRow, &old_Board_AddZombieInRow);
    homura::HookFunction(Board_DoPlantingEffectsAddr, &Board::DoPlantingEffects, nullptr);
    homura::HookFunction(Board_InitLawnMowersAddr, &Board::InitLawnMowers, &old_Board_InitLawnMowers);
    homura::HookFunction(Board_PickZombieWavesAddr, &Board::PickZombieWaves, &old_Board_PickZombieWaves);
    homura::HookFunction(Board_DrawUITopAddr, &Board::DrawUITop, &old_Board_DrawUITop);
    homura::HookFunction(Board_GetShovelButtonRectAddr, &Board_GetShovelButtonRect, &old_Board_GetShovelButtonRect);
    homura::HookFunction(Board_UpdateLevelEndSequenceAddr, &Board::UpdateLevelEndSequence, &old_Board_UpdateLevelEndSequence);
    homura::HookFunction(Board_UpdateGridItemsAddr, &Board::UpdateGridItems, &old_Board_UpdateGridItems);
    homura::HookFunction(Board_ShakeBoardAddr, &Board::ShakeBoard, &old_Board_ShakeBoard);
    homura::HookFunction(Board_DrawZenButtonsAddr, &Board::DrawZenButtons, &old_Board_DrawZenButtons);
//    homura::HookFunction(Board_GetNumSeedsInBankAddr, &Board::GetNumSeedsInBank, &old_Board_GetNumSeedsInBank);


    homura::HookFunction(FixBoardAfterLoadAddr, &FixBoardAfterLoad, &old_FixBoardAfterLoad);
    homura::HookFunction(LawnSaveGameAddr, &LawnSaveGame, &old_LawnSaveGame);


    homura::HookFunction(Challenge_UpdateAddr, &Challenge::Update, &old_Challenge_Update);
    homura::HookFunction(Challenge_ChallengeAddr, &Challenge::Create, &old_Challenge_Challenge);
    homura::HookFunction(Challenge_HeavyWeaponFireAddr, &Challenge::HeavyWeaponFire, &old_Challenge_HeavyWeaponFire);
    homura::HookFunction(Challenge_IZombieDrawPlantAddr, &Challenge::IZombieDrawPlant, nullptr);
    homura::HookFunction(Challenge_HeavyWeaponUpdateAddr, &Challenge::HeavyWeaponUpdate, &old_Challenge_HeavyWeaponUpdate);
    homura::HookFunction(Challenge_IZombieEatBrainAddr, &Challenge::IZombieEatBrain, nullptr);
    homura::HookFunction(Challenge_DrawArtChallengeAddr, &Challenge::DrawArtChallenge, nullptr);
    homura::HookFunction(Challenge_CanPlantAtAddr, &Challenge::CanPlantAt, nullptr);
    homura::HookFunction(Challenge_InitLevelAddr, &Challenge::InitLevel, &old_Challenge_InitLevel);
    homura::HookFunction(Challenge_InitZombieWavesAddr, &Challenge::InitZombieWaves, &old_Challenge_InitZombieWaves);
    homura::HookFunction(Challenge_TreeOfWisdomFertilizeAddr, &Challenge::TreeOfWisdomFertilize, &old_Challenge_TreeOfWisdomFertilize);
    homura::HookFunction(Challenge_LastStandUpdateAddr, &Challenge::LastStandUpdate, nullptr);
    homura::HookFunction(Challenge_DrawHeavyWeaponAddr, &Challenge::DrawHeavyWeapon, nullptr);
    homura::HookFunction(Challenge_UpdateZombieSpawningAddr, &Challenge::UpdateZombieSpawning, &old_Challenge_UpdateZombieSpawning);
    homura::HookFunction(Challenge_HeavyWeaponPacketClickedAddr, &Challenge::HeavyWeaponPacketClicked, &old_Challenge_HeavyWeaponPacketClicked);
    homura::HookFunction(Challenge_IZombieSeedTypeToZombieTypeAddr, &Challenge::IZombieSeedTypeToZombieType, &old_Challenge_IZombieSeedTypeToZombieType);
    homura::HookFunction(Challenge_StartLevelAddr, &Challenge::StartLevel, &old_Challenge_StartLevel);
    homura::HookFunction(Challenge_DeleteAddr, &Challenge::Delete, &old_Challenge_Delete);


    homura::HookFunction(ChallengeScreen_AddedToManagerAddr, &ChallengeScreen_AddedToManager, &old_ChallengeScreen_AddedToManager);
    homura::HookFunction(ChallengeScreen_RemovedFromManagerAddr, &ChallengeScreen_RemovedFromManager, &old_ChallengeScreen_RemovedFromManager);
    homura::HookFunction(ChallengeScreen_Delete2Addr, &ChallengeScreen_Delete2, &old_ChallengeScreen_Delete2);
    homura::HookFunction(ChallengeScreen_UpdateAddr, &ChallengeScreen_Update, &old_ChallengeScreen_Update);
    homura::HookFunction(ChallengeScreen_ChallengeScreenAddr, &ChallengeScreen_ChallengeScreen, &old_ChallengeScreen_ChallengeScreen);
    homura::HookFunction(ChallengeScreen_DrawAddr, &ChallengeScreen_Draw, &old_ChallengeScreen_Draw);
    homura::HookFunction(ChallengeScreen_ButtonDepressAddr, &ChallengeScreen_ButtonDepress, nullptr);
    homura::HookFunction(ChallengeScreen_UpdateButtonsAddr, &ChallengeScreen_UpdateButtons, nullptr);
    homura::HookFunction(GetChallengeDefinitionAddr, &GetChallengeDefinition, &old_GetChallengeDefinition);


    homura::HookFunction(Coin_UpadteAddr, &Coin_Update, &old_Coin_Update);
    homura::HookFunction(Coin_GamepadCursorOverAddr, &Coin_GamepadCursorOver, &old_Coin_GamepadCursorOver);
    homura::HookFunction(Coin_MouseHitTestAddr, &Coin_MouseHitTest, &old_Coin_MouseHitTest);
    homura::HookFunction(Coin_UpdateFallAddr, &Coin_UpdateFall, &old_Coin_UpdateFall);


    homura::HookFunction(GamepadControls_ButtonDownFireCobcannonTestAddr, &GamepadControls_ButtonDownFireCobcannonTest, &old_GamepadControls_ButtonDownFireCobcannonTest);
    homura::HookFunction(GamepadControls_DrawAddr, &GamepadControls_Draw, &old_GamepadControls_Draw);
    homura::HookFunction(GamepadControls_GamepadControlsAddr, &GamepadControls_GamepadControls, &old_GamepadControls_GamepadControls);
    homura::HookFunction(GamepadControls_UpdateAddr, &GamepadControls_Update, &old_GamepadControls_Update);
    homura::HookFunction(GamepadControls_DrawPreviewAddr, &GamepadControls_DrawPreview, &old_GamepadControls_DrawPreview);
    homura::HookFunction(GamepadControls_UpdatePreviewReanimAddr, &GamepadControls_UpdatePreviewReanim, &old_GamepadControls_UpdatePreviewReanim);


    homura::HookFunction(GridItem_UpdateAddr, &GridItem_Update, &old_GridItem_Update);
    homura::HookFunction(GridItem_UpdateScaryPotAddr, &GridItem_UpdateScaryPot, &old_GridItem_UpdateScaryPot);
    homura::HookFunction(GridItem_DrawStinkyAddr, &GridItem_DrawStinky, &old_GridItem_DrawStinky);
    homura::HookFunction(GridItem_DrawSquirrelAddr, &GridItem_DrawSquirrel, nullptr);
    homura::HookFunction(GridItem_DrawScaryPotAddr, &GridItem_DrawScaryPot, nullptr);
    homura::HookFunction(GridItem_DrawCraterAddr, &GridItem_DrawCrater, nullptr);


    homura::HookFunction(AlmanacDialog_RemovedFromManagerAddr, &AlmanacDialog_RemovedFromManager, &old_AlmanacDialog_RemovedFromManager);
    homura::HookFunction(AlmanacDialog_AlmanacDialogAddr, &AlmanacDialog_AlmanacDialog, &old_AlmanacDialog_AlmanacDialog);
    homura::HookFunction(AlmanacDialog_SetPageAddr, &AlmanacDialog_SetPage, &old_AlmanacDialog_SetPage);
    homura::HookFunction(AlmanacDialog_MouseDownAddr, &AlmanacDialog_MouseDown, nullptr);
    homura::HookFunction(AlmanacDialog_MouseUpAddr, &AlmanacDialog_MouseUp, nullptr);
    homura::HookFunction(AlmanacDialog_ButtonDepressAddr, &AlmanacDialog_ButtonDepress, nullptr);
    homura::HookFunction(AlmanacDialog_Delete2Addr, &AlmanacDialog_Delete2, &old_AlmanacDialog_Delete2);
    homura::HookFunction(AlmanacDialog_DrawPlantsAddr, &AlmanacDialog_DrawPlants, &old_AlmanacDialog_DrawPlants);
    homura::HookFunction(AlmanacDialog_SetupLayoutPlantsAddr, &AlmanacDialog_SetupLayoutPlants, &old_AlmanacDialog_SetupLayoutPlants);


    homura::HookFunction(SeedChooserScreen_EnableStartButtonAddr, &SeedChooserScreen_EnableStartButton, &old_SeedChooserScreen_EnableStartButton);
    homura::HookFunction(SeedChooserScreen_RebuildHelpbarAddr, &SeedChooserScreen_RebuildHelpbar, &old_SeedChooserScreen_RebuildHelpbar);
    homura::HookFunction(SeedChooserScreen_SeedChooserScreenAddr, &SeedChooserScreen_SeedChooserScreen, &old_SeedChooserScreen_SeedChooserScreen);
    homura::HookFunction(SeedChooserScreen_GetZombieSeedTypeAddr, &SeedChooserScreen_GetZombieSeedType, nullptr);
    homura::HookFunction(SeedChooserScreen_GetZombieTypeAddr, &SeedChooserScreen_GetZombieType, nullptr);
    homura::HookFunction(SeedChooserScreen_ClickedSeedInChooserAddr, &SeedChooserScreen_ClickedSeedInChooser, &old_SeedChooserScreen_ClickedSeedInChooser);
    homura::HookFunction(SeedChooserScreen_CrazyDavePickSeedsAddr, &SeedChooserScreen_CrazyDavePickSeeds, &old_SeedChooserScreen_CrazyDavePickSeeds);
    homura::HookFunction(SeedChooserScreen_OnStartButtonAddr, &SeedChooserScreen_OnStartButton, &old_SeedChooserScreen_OnStartButton);
    homura::HookFunction(SeedChooserScreen_UpdateAddr, &SeedChooserScreen_Update, &old_SeedChooserScreen_Update);
    homura::HookFunction(SeedChooserScreen_SeedNotAllowedToPickAddr, &SeedChooserScreen_SeedNotAllowedToPick, &old_SeedChooserScreen_SeedNotAllowedToPick);
    homura::HookFunction(SeedChooserScreen_ClickedSeedInBankAddr, &SeedChooserScreen_ClickedSeedInBank, &old_SeedChooserScreen_ClickedSeedInBank);
    homura::HookFunction(SeedChooserScreen_GameButtonDownAddr, &SeedChooserScreen_GameButtonDown, &old_SeedChooserScreen_GameButtonDown);
    homura::HookFunction(SeedChooserScreen_DrawPacketAddr, &SeedChooserScreen_DrawPacket, nullptr);
    homura::HookFunction(SeedChooserScreen_ButtonDepressAddr, &SeedChooserScreen_ButtonDepress, &old_SeedChooserScreen_ButtonDepress);
    homura::HookFunction(SeedChooserScreen_GetSeedPositionInBankAddr, &SeedChooserScreen_GetSeedPositionInBank, &old_SeedChooserScreen_GetSeedPositionInBank);
    homura::HookFunction(SeedChooserScreen_ShowToolTipAddr, &SeedChooserScreen_ShowToolTip, &old_SeedChooserScreen_ShowToolTip);


    homura::HookFunction(MainMenu_KeyDownAddr, &MainMenu::KeyDown, &old_MainMenu_KeyDown);
    homura::HookFunction(MainMenu_ButtonDepressAddr, &MainMenu::ButtonDepress, &old_MainMenu_ButtonDepress);
    homura::HookFunction(MainMenu_UpdateAddr, &MainMenu::Update, &old_MainMenu_Update);
    homura::HookFunction(MainMenu_SyncProfileAddr, &MainMenu::SyncProfile, &old_MainMenu_SyncProfile);
    homura::HookFunction(MainMenu_EnterAddr, &MainMenu_Enter, &old_MainMenu_Enter);
    homura::HookFunction(MainMenu_ExitAddr, &MainMenu::Exit, &old_MainMenu_Exit);
    homura::HookFunction(MainMenu_UpdateExitAddr, &MainMenu::UpdateExit, &old_MainMenu_UpdateExit);
    homura::HookFunction(MainMenu_OnExitAddr, &MainMenu::OnExit, &old_MainMenu_OnExit);
    //    MSHookFunction(MainMenu_SetSceneAddr, (void *) MainMenu_SetScene, (void **) &old_MainMenu_SetScene);
    homura::HookFunction(MainMenu_OnSceneAddr, &MainMenu::OnScene, &old_MainMenu_OnScene);
    homura::HookFunction(MainMenu_SyncButtonsAddr, &MainMenu_SyncButtons, &old_MainMenu_SyncButtons);
    homura::HookFunction(MainMenu_MainMenuAddr, &MainMenu::Creat, &old_MainMenu_MainMenu);
    homura::HookFunction(MainMenu_UpdateCameraPositionAddr, &MainMenu::UpdateCameraPosition, &old_MainMenu_UpdateCameraPosition);
    homura::HookFunction(MainMenu_AddedToManagerAddr, &MainMenu::AddedToManager, &old_MainMenu_AddedToManager);
    homura::HookFunction(MainMenu_RemovedFromManagerAddr, &MainMenu::RemovedFromManager, &old_MainMenu_RemovedFromManager);
    homura::HookFunction(MainMenu_DrawOverlayAddr, &MainMenu::DrawOverlay, &old_MainMenu_DrawOverlay);
    homura::HookFunction(MainMenu_DrawFadeAddr, &MainMenu::DrawFade, &old_MainMenu_DrawFade);
    homura::HookFunction(MainMenu_Delete2Addr, &MainMenu::Delete2, &old_MainMenu_Delete2);
    homura::HookFunction(MainMenu_DrawAddr, &MainMenu::Draw, &old_MainMenu_Draw);


    homura::HookFunction(StoreScreen_UpdateAddr, &StoreScreen_Update, &old_StoreScreen_Update);
    homura::HookFunction(StoreScreen_SetupPageAddr, &StoreScreen_SetupPage, &old_StoreScreen_SetupPage);
    homura::HookFunction(StoreScreen_ButtonDepressAddr, &StoreScreen_ButtonDepress, &old_StoreScreen_ButtonDepress);
    homura::HookFunction(StoreScreen_AddedToManagerAddr, &StoreScreen_AddedToManager, &old_StoreScreen_AddedToManager);
    homura::HookFunction(StoreScreen_RemovedFromManagerAddr, &StoreScreen_RemovedFromManager, &old_StoreScreen_RemovedFromManager);
    homura::HookFunction(StoreScreen_PurchaseItemAddr, &StoreScreen_PurchaseItem, &old_StoreScreen_PurchaseItem);
    homura::HookFunction(StoreScreen_DrawAddr, &StoreScreen_Draw, &old_StoreScreen_Draw);
    homura::HookFunction(StoreScreen_DrawItemAddr, &StoreScreen_DrawItem, &old_StoreScreen_DrawItem);


    homura::HookFunction(Plant_UpdateAddr, &Plant::Update, &old_Plant_Update);
    homura::HookFunction(Plant_GetRefreshTimeAddr, &Plant::GetRefreshTime, &old_Plant_GetRefreshTime);
    homura::HookFunction(Plant_DoSpecialAddr, &Plant::DoSpecial, &old_Plant_DoSpecial);
    homura::HookFunction(Plant_DrawAddr, &Plant::Draw, &old_Plant_Draw);
    homura::HookFunction(Plant_DrawSeedTypeAddr, &Plant::DrawSeedType, nullptr);
    homura::HookFunction(Plant_IsUpgradeAddr, &Plant::IsUpgrade, &old_Plant_IsUpgrade);
    //    MSHookFunction(Plant_CobCannonFireAddr, (void *) Plant_CobCannonFire, (void **) &old_Plant_CobCannonFire);
    homura::HookFunction(Plant_PlantInitializeAddr, &Plant::PlantInitialize, &old_Plant_PlantInitialize);
    homura::HookFunction(Plant_SetSleepingAddr, &Plant::SetSleeping, &old_Plant_SetSleeping);
    homura::HookFunction(Plant_UpdateReanimColorAddr, &Plant::UpdateReanimColor, &old_Plant_UpdateReanimColor);
    homura::HookFunction(Plant_FindTargetGridItemAddr, &Plant::FindTargetGridItem, nullptr);
    homura::HookFunction(Plant_GetCostAddr, &Plant::GetCost, &old_Plant_GetCost);
    homura::HookFunction(Plant_DieAddr, &Plant::Die, &old_Plant_Die);
    //    MSHookFunction(Plant_UpdateReanimAddr, (void *) Plant_UpdateReanim, (void **) &old_Plant_UpdateReanim);


    homura::HookFunction(Projectile_ProjectileInitializeAddr, &Projectile_ProjectileInitialize, &old_Projectile_ProjectileInitialize);
    homura::HookFunction(Projectile_ConvertToFireballAddr, &Projectile_ConvertToFireball, &old_Projectile_ConvertToFireball);
    homura::HookFunction(Projectile_ConvertToPeaAddr, &Projectile_ConvertToPea, &old_Projectile_ConvertToPea);
    homura::HookFunction(Projectile_UpdateAddr, &Projectile::Update, &old_Projectile_Update);
    homura::HookFunction(Projectile_DoImpactAddr, &Projectile_DoImpact, &old_Projectile_DoImpact);
    homura::HookFunction(Projectile_CheckForCollisionAddr, &Projectile_CheckForCollision, nullptr);


    homura::HookFunction(SeedPacket_UpdateAddr, &SeedPacket_Update, &old_SeedPacket_Update);
    homura::HookFunction(SeedPacket_UpdateSelectedAddr, &SeedPacket::UpdateSelected, &old_SeedPacket_UpdateSelected);
    homura::HookFunction(SeedPacket_DrawOverlayAddr, &SeedPacket_DrawOverlay, &old_SeedPacket_DrawOverlay);
    homura::HookFunction(SeedPacket_DrawAddr, &SeedPacket_Draw, &old_SeedPacket_Draw);
    homura::HookFunction(SeedPacket_FlashIfReadyAddr, &SeedPacket::FlashIfReady, &old_SeedPacket_FlashIfReady);
    //    MSHookFunction(SeedPacket_MouseDownAddr, (void *) SeedPacket_MouseDown, (void **) &old_SeedPacket_MouseDown);


    homura::HookFunction(Zombie_UpdateAddr, &Zombie::Update, &old_Zombie_Update);
    homura::HookFunction(Zombie_UpdateZombiePeaHeadAddr, &Zombie::UpdateZombiePeaHead, nullptr);
    homura::HookFunction(Zombie_UpdateZombieGatlingHeadAddr, &Zombie::UpdateZombieGatlingHead, nullptr);
    homura::HookFunction(Zombie_UpdateZombieJalapenoHeadAddr, &Zombie::UpdateZombieJalapenoHead, &old_Zombie_UpdateZombieJalapenoHead);
    homura::HookFunction(Zombie_GetDancerFrameAddr, &Zombie::GetDancerFrame, nullptr);
    homura::HookFunction(Zombie_RiseFromGraveAddr, &Zombie::RiseFromGrave, &old_Zombie_RiseFromGrave);
    homura::HookFunction(Zombie_EatPlantAddr, &Zombie::EatPlant, &old_Zombie_EatPlant);
    homura::HookFunction(Zombie_DetachShieldAddr, &Zombie::DetachShield, &old_Zombie_DetachShield);
    homura::HookFunction(Zombie_CheckForBoardEdgeAddr, &Zombie::CheckForBoardEdge, nullptr);
    homura::HookFunction(Zombie_DrawAddr, &Zombie::Draw, &old_Zombie_Draw);
    homura::HookFunction(Zombie_DrawBossPartAddr, &Zombie::DrawBossPart, &old_Zombie_DrawBossPart);
    homura::HookFunction(ZombieTypeCanGoInPoolAddr, &Zombie::ZombieTypeCanGoInPool, &old_ZombieTypeCanGoInPool);
    homura::HookFunction(Zombie_BossSpawnAttackAddr, &Zombie::BossSpawnAttack, nullptr);
    homura::HookFunction(Zombie_DrawBungeeCordAddr, &Zombie::DrawBungeeCord, nullptr);
    homura::HookFunction(Zombie_IsTangleKelpTargetAddr, &Zombie::IsTangleKelpTarget, nullptr);
    homura::HookFunction(Zombie_IsTangleKelpTarget2Addr, &Zombie::IsTangleKelpTarget, nullptr);
    homura::HookFunction(Zombie_DrawReanimAddr, &Zombie::DrawReanim, &old_Zombie_DrawReanim);
    homura::HookFunction(Zombie_DropHeadAddr, &Zombie::DropHead, &old_Zombie_DropHead);
    homura::HookFunction(Zombie_ZombieInitializeAddr, &Zombie::ZombieInitialize, &old_Zombie_ZombieInitialize);
    homura::HookFunction(Zombie_DieNoLootAddr, &Zombie::DieNoLoot, &old_Zombie_DieNoLoot);
    homura::HookFunction(GetZombieDefinitionAddr, &GetZombieDefinition, &old_GetZombieDefinition);


    homura::HookFunction(Sexy_Dialog_AddedToManagerWidgetManagerAddr, &SexyDialog_AddedToManager, &old_SexyDialog_AddedToManager);
    homura::HookFunction(Sexy_Dialog_RemovedFromManagerAddr, &SexyDialog_RemovedFromManager, &old_SexyDialog_RemovedFromManager);


    homura::HookFunction(SeedBank_DrawAddr, &SeedBank::Draw, &old_SeedBank_Draw);
    homura::HookFunction(SeedBank_MouseHitTestAddr, &SeedBank::MouseHitTest, nullptr);
//    homura::HookFunction(SeedBank_SeedBankAddr, &SeedBank::Create, &old_SeedBank_SeedBank);
//    homura::HookFunction(SeedBank_UpdateWidthAddr, &SeedBank::UpdateWidth, &old_SeedBank_UpdateWidth);
    homura::HookFunction(SeedBank_MoveAddr, &SeedBank::Move, nullptr);


    homura::HookFunction(AwardScreen_MouseDownAddr, &AwardScreen_MouseDown, &old_AwardScreen_MouseDown);
    homura::HookFunction(AwardScreen_MouseUpAddr, &AwardScreen_MouseUp, &old_AwardScreen_MouseUp);


    homura::HookFunction(VSSetupMenu_UpdateAddr, &VSSetupMenu_Update, &old_VSSetupMenu_Update);
    homura::HookFunction(VSSetupMenu_KeyDownAddr, &VSSetupMenu_KeyDown, &old_VSSetupMenu_KeyDown);


    homura::HookFunction(VSResultsMenu_UpdateAddr, &VSResultsMenu_Update, &old_VSResultsMenu_Update);
    homura::HookFunction(VSResultsMenu_OnExitAddr, &VSResultsMenu_OnExit, &old_VSResultsMenu_OnExit);
    homura::HookFunction(VSResultsMenu_DrawInfoBoxAddr, &VSResultsMenu_DrawInfoBox, &old_VSResultsMenu_DrawInfoBox);
    homura::HookFunction(VSResultsMenu_ButtonDepressAddr, &VSResultsMenu_ButtonDepress, nullptr);


    homura::HookFunction(ImitaterDialog_ImitaterDialogAddr, &ImitaterDialog_ImitaterDialog, &old_ImitaterDialog_ImitaterDialog);
    homura::HookFunction(ImitaterDialog_MouseDownAddr, &ImitaterDialog_MouseDown, &old_ImitaterDialog_MouseDown);
    //    MSHookFunction(ImitaterDialog_OnKeyDownAddr, (void *) ImitaterDialog_OnKeyDown,(void **) &old_ImitaterDialog_OnKeyDown);
    homura::HookFunction(ImitaterDialog_KeyDownAddr, &ImitaterDialog_KeyDown, &old_ImitaterDialog_KeyDown);
    homura::HookFunction(ImitaterDialog_ShowToolTipAddr, &ImitaterDialog_ShowToolTip, &old_ImitaterDialog_ShowToolTip);


    homura::HookFunction(MailScreen_MailScreenAddr, &MailScreen_MailScreen, &old_MailScreen_MailScreen);
    homura::HookFunction(MailScreen_AddedToManagerAddr, &MailScreen_AddedToManager, &old_MailScreen_AddedToManager);
    homura::HookFunction(MailScreen_RemovedFromManagerAddr, &MailScreen_RemovedFromManager, &old_MailScreen_RemovedFromManager);
    homura::HookFunction(MailScreen_Delete2Addr, &MailScreen_Delete2, &old_MailScreen_Delete2);


    homura::HookFunction(ZenGardenControls_UpdateAddr, &ZenGardenControls_Update, &old_ZenGardenControls_Update);
    homura::HookFunction(ZenGarden_DrawBackdropAddr, &ZenGarden_DrawBackdrop, &old_ZenGarden_DrawBackdrop);
    //    MSHookFunction(ZenGarden_MouseDownWithFeedingToolAddr, (void *) ZenGarden_MouseDownWithFeedingTool, (void **) &old_ZenGarden_MouseDownWithFeedingTool);
    // MSHookFunction(ZenGarden_DrawPottedPlantAddr, (void *) ZenGarden_DrawPottedPlant, nullptr);

    //    MSHookFunction( Sexy_GamepadApp_CheckGamepadAddr,(void *) Sexy_GamepadApp_CheckGamepad,nullptr);
    //    MSHookFunction( Sexy_GamepadApp_HasGamepadAddr,(void *) Sexy_GamepadApp_HasGamepad,nullptr);


    homura::HookFunction(CutScene_ShowShovelAddr, &CutScene_ShowShovel, &old_CutScene_ShowShovel);
    homura::HookFunction(BaseGamepadControls_GetGamepadVelocityAddr, &BaseGamepadControls::GetGamepadVelocity, nullptr);
    homura::HookFunction(LookupFoleyAddr, &LookupFoley, &old_LookupFoley);
    //    MSHookFunction(TodDrawStringWrappedHelperAddr, (void *) TodDrawStringWrappedHelper, (void **) &old_TodDrawStringWrappedHelper);
    homura::HookFunction(MessageWidget_ClearLabelAddr, &MessageWidget_ClearLabel, &old_MessageWidget_ClearLabel);
    homura::HookFunction(MessageWidget_SetLabelAddr, &MessageWidget_SetLabel, &old_MessageWidget_SetLabel);
    homura::HookFunction(MessageWidget_UpdateAddr, &MessageWidget_Update, &old_MessageWidget_Update);
    homura::HookFunction(MessageWidget_DrawAddr, &MessageWidget_Draw, &old_MessageWidget_Draw);
    homura::HookFunction(Sexy_ExtractLoadingSoundsResourcesAddr, &Sexy_ExtractLoadingSoundsResources, &old_Sexy_ExtractLoadingSoundsResources);
    homura::HookFunction(CutScene_UpdateAddr, &CutScene_Update, &old_CutScene_Update);
    //    MSHookFunction(Sexy_ScrollbarWidget_MouseDownAddr, (void *) Sexy_ScrollbarWidget_MouseDown,nullptr);
    homura::HookFunction(CustomScrollbarWidget_RemoveScrollButtonsAddr, &CustomScrollbarWidget_RemoveScrollButtons, nullptr);
    homura::HookFunction(CreditScreen_CreditScreenAddr, &CreditScreen_CreditScreen, &old_CreditScreen_CreditScreen);
    homura::HookFunction(CreditScreen_RemovedFromManagerAddr, &CreditScreen_RemovedFromManager, &old_CreditScreen_RemovedFromManager);
    homura::HookFunction(CreditScreen_Delete2Addr, &CreditScreen_Delete2, &old_CreditScreen_Delete2);

    homura::HookFunction(HelpTextScreen_AddedToManagerAddr, &HelpTextScreen_AddedToManager, &old_HelpTextScreen_AddedToManager);
    homura::HookFunction(HelpTextScreen_RemovedFromManagerAddr, &HelpTextScreen_RemovedFromManager, &old_HelpTextScreen_RemovedFromManager);
    homura::HookFunction(HelpTextScreen_HelpTextScreenAddr, &HelpTextScreen_HelpTextScreen, &old_HelpTextScreen_HelpTextScreen);
    homura::HookFunction(HelpTextScreen_Delete2Addr, &HelpTextScreen_Delete2, &old_HelpTextScreen_Delete2);
    homura::HookFunction(HelpTextScreen_UpdateAddr, &HelpTextScreen_Update, &old_HelpTextScreen_Update);
    homura::HookFunction(HelpOptionsDialog_ButtonDepressAddr, &HelpOptionsDialog_ButtonDepress, &old_HelpOptionsDialog_ButtonDepress);
    homura::HookFunction(HelpOptionsDialog_HelpOptionsDialogAddr, &HelpOptionsDialog_HelpOptionsDialog, &old_HelpOptionsDialog_HelpOptionsDialog);
    homura::HookFunction(HelpOptionsDialog_ResizeAddr, &HelpOptionsDialog_Resize, &old_HelpOptionsDialog_Resize);

    MSHookFunction(
        WaitForSecondPlayerDialog_WaitForSecondPlayerDialogAddr, (void *)WaitForSecondPlayerDialog_WaitForSecondPlayerDialog, (void **)&old_WaitForSecondPlayerDialog_WaitForSecondPlayerDialog);
    //    MSHookFunction(Sexy_WidgetManager_MouseDownAddr, (void *) Sexy_WidgetManager_MouseDown,(void **) &old_Sexy_WidgetManager_MouseDown);
    //    MSHookFunction(Sexy_WidgetManager_AxisMovedAddr, (void *) Sexy_WidgetManager_AxisMoved, nullptr);
    homura::HookFunction(LawnMower_UpdateAddr, &LawnMower_Update, &old_LawnMower_Update);
    homura::HookFunction(ConfirmBackToMainDialog_ButtonDepressAddr, &ConfirmBackToMainDialog_ButtonDepress, &old_ConfirmBackToMainDialog_ButtonDepress);
    homura::HookFunction(ConfirmBackToMainDialog_AddedToManagerAddr, &ConfirmBackToMainDialog_AddedToManager, &old_ConfirmBackToMainDialog_AddedToManager);
    //    MSHookFunction(FilterEffectDisposeForAppAddr,(void *) FilterEffectDisposeForApp,nullptr);
    //    MSHookFunction(FilterEffectGetImageAddr,(void *) FilterEffectGetImage,nullptr);
    homura::HookFunction(Reanimation_DrawTrackAddr, &Reanimation::DrawTrack, &old_Reanimation_DrawTrack);
    homura::HookFunction(ReanimatorCache_DrawCachedPlantAddr, &ReanimatorCache_DrawCachedPlant, &old_ReanimatorCache_DrawCachedPlant);
    homura::HookFunction(ReanimatorCache_UpdateReanimationForVariationAddr, &ReanimatorCache::UpdateReanimationForVariation, &old_ReanimatorCache_UpdateReanimationForVariation);
    homura::HookFunction(ReanimatorCache_LoadCachedImagesAddr, &ReanimatorCache::LoadCachedImages, &old_ReanimatorCache_LoadCachedImages);
    homura::HookFunction(ReanimatorCache_MakeCachedZombieFrameAddr, &ReanimatorCache::MakeCachedZombieFrame, &old_ReanimatorCache_MakeCachedZombieFrame);


    homura::HookFunction(HelpBarWidget_HelpBarWidgetAddr, &HelpBarWidget_HelpBarWidget, &old_HelpBarWidget_HelpBarWidget);
    homura::HookFunction(DrawSeedTypeAddr, &DrawSeedType, nullptr);
    homura::HookFunction(DrawSeedPacketAddr, &DrawSeedPacket, nullptr);
    homura::HookFunction(Music_PlayMusicAddr, &Music::PlayMusic, nullptr);
    homura::HookFunction(Music_MusicUpdateAddr, &Music::MusicUpdate, nullptr);
    homura::HookFunction(Music_UpdateMusicBurstAddr, &Music::UpdateMusicBurst, &old_Music_UpdateMusicBurst);
    homura::HookFunction(Music2_Music2Addr, &Music2_Music2, &old_Music2_Music2);
    homura::HookFunction(LawnPlayerInfo_AddCoinsAddr, &LawnPlayerInfo_AddCoins, nullptr);
    homura::HookFunction(MaskHelpWidget_UpdateAddr, &MaskHelpWidget_Update, nullptr);
    homura::HookFunction(MaskHelpWidget_DrawAddr, &MaskHelpWidget_Draw, nullptr);
    //    MSHookFunction(DaveHelp_DaveHelpAddr, (void *) DaveHelp_DaveHelp, (void **) &old_DaveHelp_DaveHelp);
    homura::HookFunction(DaveHelp_UpdateAddr, &DaveHelp_Update, nullptr);
    homura::HookFunction(DaveHelp_DrawAddr, &DaveHelp_Draw, nullptr);
    homura::HookFunction(DaveHelp_Delete2Addr, &DaveHelp_Delete2, &old_DaveHelp_Delete2);
    homura::HookFunction(DaveHelp_DealClickAddr, &DaveHelp_DealClick, nullptr);
    homura::HookFunction(TrashBin_TrashBinAddr, &TrashBin::Create, &old_TrashBin_TrashBin);
    homura::HookFunction(Sexy_SexyAppBase_Is3DAcceleratedAddr, &Sexy_SexyAppBase_Is3DAccelerated, nullptr);
    homura::HookFunction(Sexy_SexyAppBase_SexyAppBaseAddr, &Sexy_SexyAppBase_SexyAppBase, &old_Sexy_SexyAppBase_SexyAppBase);
    homura::HookFunction(SettingsDialog_AddedToManagerAddr, &SettingsDialog_AddedToManager, &old_SettingsDialog_AddedToManager);
    homura::HookFunction(SettingsDialog_RemovedFromManagerAddr, &SettingsDialog_RemovedFromManager, &old_SettingsDialog_RemovedFromManager);
    homura::HookFunction(SettingsDialog_DrawAddr, &SettingsDialog_Draw, &old_SettingsDialog_Draw);
    homura::HookFunction(SettingsDialog_Delete2Addr, &SettingsDialog_Delete2, &old_SettingsDialog_Delete2);
    homura::HookFunction(ReanimatorLoadDefinitionsAddr, &ReanimatorLoadDefinitions, &old_ReanimatorLoadDefinitions);
    homura::HookFunction(DefinitionGetCompiledFilePathFromXMLFilePathAddr, &DefinitionGetCompiledFilePathFromXMLFilePath, &old_DefinitionGetCompiledFilePathFromXMLFilePath);
    homura::HookFunction(TestMenuWidget_DeleteAddr, &TestMenuWidget_Delete, &old_TestMenuWidget_Delete);
    homura::HookFunction(TestMenuWidget_Delete2Addr, &TestMenuWidget_Delete2, &old_TestMenuWidget_Delete2);
    homura::HookFunction(SaveGameContext_SyncReanimationDefAddr, &SaveGameContext_SyncReanimationDef, nullptr);
    homura::HookFunction(PoolEffect_PoolEffectDrawAddr, &PoolEffect_PoolEffectDraw, nullptr);
    homura::HookFunction(Sexy_MemoryImage_ClearRectAddr, &Sexy_MemoryImage_ClearRect, nullptr);


    homura::HookFunction(TitleScreen_DrawAddr, &TitleScreen_Draw, &old_TitleScreen_Draw);
    homura::HookFunction(TitleScreen_UpdateAddr, &TitleScreen_Update, &old_TitleScreen_Update);
    homura::HookFunction(TitleScreen_SwitchStateAddr, &TitleScreen_SwitchState, nullptr);
}

inline void InitVTableHookFunction() {
    homura::HookVirtualFunc(vTableForCursorObjectAddr, 4, &CursorObject_BeginDraw, &old_CursorObject_BeginDraw);
    homura::HookVirtualFunc(vTableForCursorObjectAddr, 5, &CursorObject_EndDraw, &old_CursorObject_EndDraw);

    homura::HookVirtualFunc(vTableForBoardAddr, 77, &Board::MouseMove, &old_Board_MouseMove);
    homura::HookVirtualFunc(vTableForBoardAddr, 78, &Board::MouseDown, &old_Board_MouseDown);
    homura::HookVirtualFunc(vTableForBoardAddr, 81, &Board::MouseUp, &old_Board_MouseUp);
    homura::HookVirtualFunc(vTableForBoardAddr, 83, &Board::MouseDrag, &old_Board_MouseDrag);
    homura::HookVirtualFunc(vTableForBoardAddr, 133, &Board::ButtonDepress, &old_Board_ButtonDepress);

    homura::HookVirtualFunc(vTableForStoreScreenAddr, 78, &StoreScreen_MouseDown, &old_StoreScreen_MouseDown);
    homura::HookVirtualFunc(vTableForStoreScreenAddr, 81, &StoreScreen_MouseUp, &old_StoreScreen_MouseUp);
    //    VTableHookFunction(vTableForStoreScreenAddr, 83, (void *) StoreScreen_MouseDrag,(void **) &old_StoreScreen_MouseDrag);

    homura::HookVirtualFunc(vTableForMailScreenAddr, 78, &MailScreen::MouseDown, &old_MailScreen_MouseDown);
    homura::HookVirtualFunc(vTableForMailScreenAddr, 81, &MailScreen::MouseUp, &old_MailScreen_MouseUp);
    homura::HookVirtualFunc(vTableForMailScreenAddr, 83, &MailScreen::MouseDrag, &old_MailScreen_MouseDrag);
    homura::HookVirtualFunc(vTableForMailScreenAddr, 140, &MailScreen::ButtonPress, &old_MailScreen_ButtonPress);
    homura::HookVirtualFunc(vTableForMailScreenAddr, 141, &MailScreen::ButtonDepress, &old_MailScreen_ButtonDepress);

    homura::HookVirtualFunc(vTableForChallengeScreenAddr, 78, &ChallengeScreen::MouseDown, &old_ChallengeScreen_MouseDown);
    homura::HookVirtualFunc(vTableForChallengeScreenAddr, 81, &ChallengeScreen::MouseUp, &old_ChallengeScreen_MouseUp);
    homura::HookVirtualFunc(vTableForChallengeScreenAddr, 83, &ChallengeScreen::MouseDrag, &old_ChallengeScreen_MouseDrag);
    homura::HookVirtualFunc(vTableForChallengeScreenAddr, 130, &ChallengeScreen::ButtonPress, nullptr);

    //    VTableHookFunction(vTableForVSResultsMenuAddr, 78, (void *) VSResultsMenu_MouseDown,(void **) &old_VSResultsMenu_MouseDown);
    //    VTableHookFunction(vTableForVSResultsMenuAddr, 81, (void *) VSResultsMenu_MouseUp,(void **) &old_VSResultsMenu_MouseUp);
    //    VTableHookFunction(vTableForVSResultsMenuAddr, 83, (void *) VSResultsMenu_MouseDrag,(void **) &old_VSResultsMenu_MouseDrag);

    homura::HookVirtualFunc(vTableForSeedChooserScreenAddr, 77, &SeedChooserScreen::MouseMove, &old_SeedChooserScreen_MouseMove);
    homura::HookVirtualFunc(vTableForSeedChooserScreenAddr, 78, &SeedChooserScreen::MouseDown, &old_SeedChooserScreen_MouseDown);
    homura::HookVirtualFunc(vTableForSeedChooserScreenAddr, 81, &SeedChooserScreen::MouseUp, &old_SeedChooserScreen_MouseUp);
    homura::HookVirtualFunc(vTableForSeedChooserScreenAddr, 83, &SeedChooserScreen::MouseDrag, &old_SeedChooserScreen_MouseDrag);
    homura::HookVirtualFunc(vTableForSeedChooserScreenAddr, 135, &SeedChooserScreen::ButtonPress, nullptr);


    homura::HookVirtualFunc(vTableForHelpTextScreenAddr, 38, &HelpTextScreen_Draw, &old_HelpTextScreen_Draw);
    homura::HookVirtualFunc(vTableForHelpTextScreenAddr, 78, &HelpTextScreen_MouseDown, &old_HelpTextScreen_MouseDown);
    //    VTableHookFunction(vTableForHelpTextScreenAddr, 81, (void *) HelpTextScreen_MouseUp,(void **) &old_HelpTextScreen_MouseUp);
    //    VTableHookFunction(vTableForHelpTextScreenAddr, 83, (void *) HelpTextScreen_MouseDrag,(void **) &old_HelpTextScreen_MouseDrag);
    homura::HookVirtualFunc(vTableForHelpTextScreenAddr, 136, &HelpTextScreen_ButtonDepress, &old_HelpTextScreen_ButtonDepress);

    homura::HookVirtualFunc(vTableForAlmanacDialogAddr, 83, &AlmanacDialog_MouseDrag, &old_AlmanacDialog_MouseDrag);

    homura::HookVirtualFunc(vTableForHouseChooserDialogAddr, 73, &HouseChooserDialog_KeyDown, &old_HouseChooserDialog_KeyDown);
    homura::HookVirtualFunc(vTableForHouseChooserDialogAddr, 78, &HouseChooserDialog_MouseDown, &old_HouseChooserDialog_MouseDown);

    homura::HookVirtualFunc(vTableForSeedPacketAddr, 4, &SeedPacket_BeginDraw, &old_SeedPacket_BeginDraw);
    homura::HookVirtualFunc(vTableForSeedPacketAddr, 5, &SeedPacket_EndDraw, &old_SeedPacket_EndDraw);

    homura::HookVirtualFunc(vTableForSeedBankAddr, 4, &SeedBank_BeginDraw, &old_SeedBank_BeginDraw);
    homura::HookVirtualFunc(vTableForSeedBankAddr, 5, &SeedBank_EndDraw, &old_SeedBank_EndDraw);

    homura::HookVirtualFunc(vTableForGraphicsAddr, 4, &Sexy_Graphics_PushTransform, &old_Sexy_Graphics_PushTransform);
    homura::HookVirtualFunc(vTableForGraphicsAddr, 5, &Sexy_Graphics_PopTransform, &old_Sexy_Graphics_PopTransform);


    homura::HookVirtualFunc(vTableForImageAddr, 37, &Sexy_Image_PushTransform, &old_Sexy_Image_PushTransform);
    homura::HookVirtualFunc(vTableForImageAddr, 38, &Sexy_Image_PopTransform, &old_Sexy_Image_PopTransform);

    homura::HookVirtualFunc(vTableForGLImageAddr, 37, &Sexy_GLImage_PushTransform, &old_Sexy_GLImage_PushTransform);
    homura::HookVirtualFunc(vTableForGLImageAddr, 38, &Sexy_GLImage_PopTransform, &old_Sexy_GLImage_PopTransform);

    homura::HookVirtualFunc(vTableForMemoryImageAddr, 37, &Sexy_MemoryImage_PushTransform, &old_Sexy_MemoryImage_PushTransform);
    homura::HookVirtualFunc(vTableForMemoryImageAddr, 38, &Sexy_MemoryImage_PopTransform, &old_Sexy_MemoryImage_PopTransform);


    homura::HookVirtualFunc(vTableForMusic2Addr, 7, &Music2_StopAllMusic, &old_Music2_StopAllMusic);
    homura::HookVirtualFunc(vTableForMusic2Addr, 8, &Music2_StartGameMusic, &old_Music2_StartGameMusic);
    homura::HookVirtualFunc(vTableForMusic2Addr, 11, &Music2_GameMusicPause, &old_Music2_GameMusicPause);
    //    VTableHookFunction(vTableForMusic2Addr, 12, (void *) Music2_UpdateMusicBurst,(void **) &old_Music2_UpdateMusicBurst);
    //    VTableHookFunction(vTableForMusic2Addr, 13, (void *) Music2_StartBurst,(void **) &old_Music2_StartBurst);
    homura::HookVirtualFunc(vTableForMusic2Addr, 17, &Music2_FadeOut, &old_Music2_FadeOut);


    //    VTableHookFunction(vTableForMaskHelpWidgetAddr, 71, (void *) MaskHelpWidget_KeyDown,nullptr);
    homura::HookVirtualFunc(vTableForMaskHelpWidgetAddr, 78, &MaskHelpWidget_MouseDown, nullptr);
    homura::HookVirtualFunc(vTableForMaskHelpWidgetAddr, 81, &MaskHelpWidget_MouseUp, nullptr);
    homura::HookVirtualFunc(vTableForMaskHelpWidgetAddr, 83, &MaskHelpWidget_MouseDrag, nullptr);


    homura::HookVirtualFunc(vTableForDaveHelpAddr, 78, &DaveHelp_MouseDown, nullptr);
    homura::HookVirtualFunc(vTableForDaveHelpAddr, 81, &DaveHelp_MouseUp, nullptr);
    homura::HookVirtualFunc(vTableForDaveHelpAddr, 83, &DaveHelp_MouseDrag, nullptr);
    homura::HookVirtualFunc(vTableForDaveHelpAddr, 73, &DaveHelp_KeyDown, nullptr);


    homura::HookVirtualFunc(vTableForTestMenuWidgetAddr, 32, &TestMenuWidget_RemovedFromManager, &old_TestMenuWidget_RemovedFromManager);
    homura::HookVirtualFunc(vTableForTestMenuWidgetAddr, 33, &TestMenuWidget_Update, nullptr);
    homura::HookVirtualFunc(vTableForTestMenuWidgetAddr, 38, &TestMenuWidget_Draw, nullptr);
    homura::HookVirtualFunc(vTableForTestMenuWidgetAddr, 78, &TestMenuWidget_MouseDown, nullptr);
    homura::HookVirtualFunc(vTableForTestMenuWidgetAddr, 81, &TestMenuWidget_MouseUp, nullptr);
    homura::HookVirtualFunc(vTableForTestMenuWidgetAddr, 83, &TestMenuWidget_MouseDrag, nullptr);
    homura::HookVirtualFunc(vTableForTestMenuWidgetAddr, 73, &TestMenuWidget_KeyDown, nullptr);


    homura::HookVirtualFunc(vTableForTrashBinAddr, 38, &TrashBin::Draw, nullptr);

    homura::HookVirtualFunc(vTableForConfirmBackToMainDialogAddr, 83, &ConfirmBackToMainDialog_MouseDrag, &old_ConfirmBackToMainDialog_MouseDrag);

    homura::HookVirtualFunc(vTableForSettingsDialogAddr, 153, &SettingsDialog_CheckboxChecked, nullptr);

    homura::HookVirtualFunc(vTableForCreditScreenAddr, 133, &CreditScreen_ButtonDepress, nullptr);

    homura::HookVirtualFunc(vTableForMainMenuAddr, 139, &MainMenu::ButtonPress, nullptr);
}

inline void InitOpenSL() {
    homura::HookFunction(Native_AudioOutput_setupAddr, &Native_AudioOutput_setup, &old_Native_AudioOutput_setup);
    homura::HookFunction(Native_AudioOutput_shutdownAddr, &Native_AudioOutput_shutdown, &old_Native_AudioOutput_shutdown);
    // MSHookFunction(Native_AudioOutput_writeAddr,(void *) Native_AudioOutput_write,(void **) &old_Native_AudioOutput_write);
    homura::HookFunction(j_AGAudioWriteAddr, &AudioWrite, nullptr);
}

inline void InitIntroVideo() {

//        MSHookFunction(j_AGVideoOpenAddr,(void *) AGVideoOpen,nullptr);
    //    MSHookFunction(j_AGVideoShowAddr,(void *) AGVideoShow,nullptr);
    //    MSHookFunction(j_AGVideoEnableAddr,(void *) AGVideoEnable,nullptr);
    //    MSHookFunction(j_AGVideoIsPlayingAddr,(void *) AGVideoIsPlaying,nullptr);
    //    MSHookFunction(j_AGVideoPlayAddr,(void *) AGVideoPlay,nullptr);
    //    MSHookFunction(j_AGVideoPauseAddr,(void *) AGVideoPause,nullptr);
    //    MSHookFunction(j_AGVideoResumeAddr,(void *) AGVideoResume,nullptr);

    const std::string libGameMain{"libGameMain.so"};
//    homura::HookPltFunction(libGameMain, AGVideoOpenOffset, AGVideoOpen, nullptr);
//    homura::HookPltFunction(libGameMain, AGVideoShowOffset, AGVideoShow, nullptr);
//    homura::HookPltFunction(libGameMain, AGVideoEnableOffset, AGVideoEnable, nullptr);
//    homura::HookPltFunction(libGameMain, AGVideoIsPlayingOffset, AGVideoIsPlaying, nullptr);
//    homura::HookPltFunction(libGameMain, AGVideoPlayOffset, AGVideoPlay, nullptr);
}


inline void CallHook() {
    InitInGameFunction();
    InitHookFunction();
    InitVTableHookFunction();
    //    InitIntroVideo();
}

#endif // PVZ_HOOK_INIT_H
