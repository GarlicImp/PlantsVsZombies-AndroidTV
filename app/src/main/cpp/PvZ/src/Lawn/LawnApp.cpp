#include "PvZ/Lawn/LawnApp.h"
#include "PvZ/GlobalVariable.h"
#include "PvZ/Lawn/Board.h"
#include "PvZ/Lawn/ChallengeScreen.h"
#include "PvZ/Lawn/ConfirmBackToMainDialog.h"
#include "PvZ/Lawn/MainMenu.h"
#include "PvZ/Lawn/Music.h"
#include "PvZ/Lawn/Reanimation.h"
#include "PvZ/Misc.h"
#include "PvZ/Symbols.h"

// 此处写明具体每个贴图对应哪个文件.
void LawnApp_LoadAddonImages(LawnApp *lawnApp) {
    addonImages.pole_night = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/pole_night");
    addonImages.trees_night = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/trees_night");
    addonImages.googlyeye = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/googlyeye");
    addonImages.squirrel = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/squirrel");
    addonImages.stripe_day_coop = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/stripe_day_coop");
    addonImages.stripe_pool_coop = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/stripe_pool_coop");
    addonImages.stripe_roof_left = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/stripe_roof_left");
    addonImages.butter_glove = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/butter_glove");
    addonImages.custom_cobcannon = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/custom_cobcannon");
    addonImages.hood1_house = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hood1_house");
    addonImages.hood2_house = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hood2_house");
    addonImages.hood3_house = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hood3_house");
    addonImages.hood4_house = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hood4_house");
    addonImages.house_hill_house = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/house_hill_house");
    addonImages.achievement_homeLawnsecurity = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/achievement_homeLawnsecurity");
    addonImages.achievement_chomp = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/achievement_chomp");
    addonImages.achievement_closeshave = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/achievement_closeshave");
    addonImages.achievement_coop = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/achievement_coop");
    addonImages.achievement_explodonator = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/achievement_explodonator");
    addonImages.achievement_garg = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/achievement_garg");
    addonImages.achievement_immortal = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/achievement_immortal");
    addonImages.achievement_shop = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/achievement_shop");
    addonImages.achievement_soilplants = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/achievement_soilplants");
    addonImages.achievement_tree = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/achievement_tree");
    addonImages.achievement_versusz = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/achievement_versusz");
    addonImages.achievement_morticulturalist = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/achievement_morticulturalist");
    addonImages.hole = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hole");
    addonImages.hole_bjorn = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hole_bjorn");
    addonImages.hole_china = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hole_china");
    addonImages.hole_gems = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hole_gems");
    addonImages.hole_chuzzle = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hole_chuzzle");
    addonImages.hole_heavyrocks = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hole_heavyrocks");
    addonImages.hole_duwei = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hole_duwei");
    addonImages.hole_pipe = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hole_pipe");
    addonImages.hole_tiki = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hole_tiki");
    addonImages.hole_worm = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hole_worm");
    addonImages.hole_top = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hole_top");
    addonImages.plant_can = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/plant_can");
    addonImages.zombie_can = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/zombie_can");
    addonImages.plant_pile01_stack01 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/plant_pile01_stack01");
    addonImages.plant_pile01_stack02 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/plant_pile01_stack02");
    addonImages.plant_pile02_stack01 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/plant_pile02_stack01");
    addonImages.plant_pile02_stack02 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/plant_pile02_stack02");
    addonImages.plant_pile03_stack01 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/plant_pile03_stack01");
    addonImages.plant_pile03_stack02 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/plant_pile03_stack02");
    addonImages.zombie_pile01_stack01 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/zombie_pile01_stack01");
    addonImages.zombie_pile01_stack02 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/zombie_pile01_stack02");
    addonImages.zombie_pile01_stack03 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/zombie_pile01_stack03");
    addonImages.zombie_pile02_stack01 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/zombie_pile02_stack01");
    addonImages.zombie_pile02_stack02 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/zombie_pile02_stack02");
    addonImages.zombie_pile02_stack03 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/zombie_pile02_stack03");
    addonImages.zombie_pile03_stack01 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/zombie_pile03_stack01");
    addonImages.zombie_pile03_stack02 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/zombie_pile03_stack02");
    addonImages.zombie_pile03_stack03 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/zombie_pile03_stack03");
    addonImages.survival_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/survival_button");
    addonImages.leaderboards = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/leaderboards");
    addonImages.SelectorScreen_WoodSign3 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/SelectorScreen_WoodSign3");
    addonImages.SelectorScreen_WoodSign3_press = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/SelectorScreen_WoodSign3_press");
    addonImages.zombatar_portrait = LawnApp_GetImageByFileName(lawnApp, "ZOMBATAR");
    addonImages.crater_night_roof_center = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/crater_night_roof_center");
    addonImages.crater_night_roof_center->mNumRows = 1;
    addonImages.crater_night_roof_center->mNumCols = 2;
    addonImages.crater_night_roof_left = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/crater_night_roof_left");
    addonImages.crater_night_roof_left->mNumRows = 1;
    addonImages.crater_night_roof_left->mNumCols = 2;

    int addonImagesNum = (sizeof(AddonImages) / sizeof(Sexy::Image *));
    lawnApp->mCompletedLoadingThreadTasks += 9 * addonImagesNum;

    //    for (int i = 0; i < addonImagesNum; ++i) {
    //        if (*((Sexy::Image **) ((char *) &AddonImages + i * sizeof(Sexy::Image *))) == NULL){
    //            LOGD("没成功%d",i);
    //        }
    //    }
}

// 此处写明具体每个音频对应哪个文件.
void LawnApp_LoadAddonSounds(LawnApp *lawnApp) {
    addonSounds.achievement = LawnApp_GetSoundByFileName(lawnApp, "addonFiles/sounds/achievement");

    int addonSoundsNum = (sizeof(addonSounds) / sizeof(int));
    lawnApp->mCompletedLoadingThreadTasks += 54 * addonSoundsNum;
}

Sexy::Image *LawnApp_GetImageByFileName(LawnApp *lawnApp, const char *fileName) {
    // 根据贴图文件路径获得贴图
    int holder[1];
    Sexy_StrFormat(holder, fileName);
    Sexy::Image *theImage = Sexy_SexyAppBase_GetImage(lawnApp, holder, 1);
    Sexy_String_Delete(holder);
    return theImage;
}

int LawnApp_GetSoundByFileName(LawnApp *lawnApp, const char *fileName) {
    // 根据音频文件路径获得音频
    int holder[1];
    Sexy_StrFormat(holder, fileName);
    int theSoundId = Sexy_AudiereSoundManager_LoadSound(lawnApp->mSoundManager, holder);
    Sexy_String_Delete(holder);
    return theSoundId;
}

void LawnApp_DoConfirmBackToMain(LawnApp *lawnApp, bool save) {
    // 实现在花园直接退出而不是弹窗退出；同时实现新版暂停菜单
    GameMode gameMode = lawnApp->mGameMode;
    if (gameMode == GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN) {
        lawnApp->mBoardResult = BoardResult::BOARDRESULT_QUIT;
        //        if (save) Board_TryToSaveGame(lawnApp->mBoard);
        LawnApp_DoBackToMain(lawnApp);
        return;
    }
    if ((gameMode == GameMode::GAMEMODE_TWO_PLAYER_VS || gameMode == GameMode::GAMEMODE_TREE_OF_WISDOM || enableNewOptionsDialog) && Sexy_SexyAppBase_GetDialog(lawnApp, Dialogs::DIALOG_NEWOPTIONS) == nullptr) {
        LawnApp_DoNewOptions(lawnApp, false, 0);
        return;
    }
    auto *dialog = (ConfirmBackToMainDialog *)operator new(sizeof(ConfirmBackToMainDialog));
    ConfirmBackToMainDialog_ConfirmBackToMainDialog(dialog, save);
    (*(void (**)(LawnApp *, int, Sexy::Widget *))(*(uint32_t *)lawnApp + 416))(lawnApp, Dialogs::DIALOG_CONFIRM_BACK_TO_MAIN, dialog);
    (*(void (**)(uint32_t, Sexy::Widget *))(**((uint32_t **)lawnApp + 165) + 48))(*((uint32_t *)lawnApp + 165), dialog);
}

void LawnApp_DoBackToMain(LawnApp *lawnApp) {
    // 实现每次退出游戏后都清空2P
    LawnApp_ClearSecondPlayer(lawnApp);
    return old_LawnApp_DoBackToMain(lawnApp);
}

void LawnApp_DoNewOptions(LawnApp *lawnApp, bool a2, unsigned int a3) {
    return old_LawnApp_DoNewOptions(lawnApp, a2, a3);
}

void LawnApp_OnSessionTaskFailed(LawnApp *lawnApp) {
    // 用此空函数替换游戏原有的LawnApp_OnSessionTaskFailed()函数，从而去除启动游戏时的“网络错误：255”弹窗
}

int LawnApp_GamepadToPlayerIndex(LawnApp *lawnApp, unsigned int a2) {
    // 实现双人结盟中1P选卡选满后自动切换为2P选卡
    if (LawnApp_IsCoopMode(lawnApp)) {
        return !m1PChoosingSeeds;
    }
    return old_LawnApp_GamepadToPlayerIndex(lawnApp, a2);
}

void LawnApp_UpdateApp(LawnApp *lawnApp) {
    // 去除道具教学关卡
    PlayerInfo *mPlayerInfo = lawnApp->mPlayerInfo;
    if (mPlayerInfo != nullptr) {
        mPlayerInfo->mPassedShopSeedTutorial = true; // 标记玩家已经通过1-1的道具教学关卡
    }
    if (doCheatDialog) {
        if (!isMainMenu)
            LawnApp_DoCheatDialog(lawnApp);
        doCheatDialog = false;
    }
    if (doCheatCodeDialog) {
        if (!isMainMenu)
            LawnApp_DoCheatCodeDialog(lawnApp);
        doCheatCodeDialog = false;
    }
    if (doKeyboardTwoPlayerDialog && lawnApp->mTitleScreen == nullptr) {
        LawnApp_LawnMessageBox(lawnApp, Dialogs::DIALOG_MESSAGE, "双人模式已开启", "已经进入双人模式；再次按下切换键即可退出此模式。", "[DIALOG_BUTTON_OK]", "", 3);
        doKeyboardTwoPlayerDialog = false;
    }
    old_LawnApp_UpDateApp(lawnApp);
}

void LawnApp_ShowAwardScreen(LawnApp* lawnApp, int a2) {
    //记录当前游戏状态
    return old_LawnApp_ShowAwardScreen(lawnApp, a2);
}

void LawnApp_KillAwardScreen(LawnApp* lawnApp) {
    //记录当前游戏状态
    return old_LawnApp_KillAwardScreen(lawnApp);
}

bool LawnApp_CanShopLevel(LawnApp *lawnApp) {
    // 决定是否在当前关卡显示道具栏
    if (disableShop)
        return false;
    if (lawnApp->mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS || LawnApp_IsCoopMode(lawnApp))
        return false;
    return old_LawnApp_CanShopLevel(lawnApp);
}

void LawnApp_KillDialog(LawnApp *lawnApp, Dialogs id) {
    (*(void (**)(LawnApp *, Dialogs))(*(uint32_t *)lawnApp + 428))(lawnApp, id); // KillDialog(Dialogs::DIALOG_HELPOPTIONS)
}

void LawnApp_ShowCreditScreen(LawnApp *lawnApp, bool isFromMainMenu) {
    // 用于一周目之后点击"制作人员"按钮播放MV
    TodFoley_StopFoley(lawnApp->mSoundSystem, FoleyType::MenuLeft);
    TodFoley_StopFoley(lawnApp->mSoundSystem, FoleyType::MenuCenter);
    TodFoley_StopFoley(lawnApp->mSoundSystem, FoleyType::MenuRight);
    if (isFromMainMenu && LawnApp_HasFinishedAdventure(lawnApp)) {
        isFromMainMenu = false;
        LawnApp_KillMainMenu(lawnApp);
        LawnApp_KillNewOptionsDialog(lawnApp);
        LawnApp_KillDialog(lawnApp, Dialogs::DIALOG_HELPOPTIONS);
    }
    return old_LawnApp_ShowCreditScreen(lawnApp, isFromMainMenu);
}

void LawnApp_LoadLevelConfiguration(LawnApp *lawnApp, int a2, int a3) {
    // 如果开启了恢复出怪，则什么都不做，以做到禁止从levels.xml加载出怪。
    if (normalLevel)
        return;
    old_LawnApp_LoadLevelConfiguration(lawnApp, a2, a3);
}

void LawnApp_TryHelpTextScreen(LawnApp *lawnApp, int a2) {
    // 空函数替换，去除初次进入对战结盟模式时的操作提示。
}

void LawnApp_PlaySample(LawnApp *lawnApp, int soundAddr) {
    (*(void (**)(LawnApp *, int, int))(*(uint32_t *)lawnApp + LAWNAPP_PLAYSAMPLE_OFFSET))(lawnApp, soundAddr, 1);
}

void LawnApp_LawnApp(LawnApp *lawnApp) {
    old_LawnApp_LawnApp(lawnApp);
    lawnApp->mLawnMouseMode = true; // 开启触控
}

void LawnApp_Init(LawnApp *lawnApp) {
    // 试图修复默认加载名为player用户的问题。

    old_LawnApp_Init(lawnApp);
    if (lawnApp->mPlayerInfo == nullptr && lawnApp->mProfileMgr[7] > 0) {
        lawnApp->mPlayerInfo = Sexy_DefaultProfileMgr_GetAnyProfile(lawnApp->mProfileMgr);
    }

    lawnApp->mNewIs3DAccelerated = lawnApp->mPlayerInfo == nullptr || !lawnApp->mPlayerInfo->mIs3DAcceleratedClosed;
}

void LawnApp_Load(LawnApp *lawnApp, const char *theGroupName) {
    int holder[1];
    Sexy_StrFormat(holder, "%s", theGroupName);
    TodLoadResources(holder);
    Sexy_String_Delete(holder);
}

void LawnApp_DoConvertImitaterImages(LawnApp *lawnApp) {
    for (int i = 0;; ++i) {
        int holder[1];
        int holder1[1];
        int holder2[1];
        Sexy_StrFormat(holder, "convertImitaterImages/pic%d", i);
        Sexy_StrFormat(holder1, "ImitaterNormalpic%d.png", i);
        Sexy_StrFormat(holder2, "ImitaterLesspic%d.png", i);
        Sexy::Image *imageFromFile = Sexy_SexyAppBase_GetImage(lawnApp, holder, 1);

        if (imageFromFile == nullptr) {
            break;
        }
        Sexy::Image *imageImitater = FilterEffectGetImage(imageFromFile, FilterEffectType::FILTEREFFECT_WASHED_OUT);
        Sexy::Image *imageImitaterLess = FilterEffectGetImage(imageFromFile, FilterEffectType::FILTEREFFECT_LESS_WASHED_OUT);
        Sexy_MemoryImage_WriteToPng(imageImitater, holder1);
        Sexy_MemoryImage_WriteToPng(imageImitaterLess, holder2);
        Sexy_MemoryImage_Delete(imageFromFile);
        Sexy_MemoryImage_Delete(imageImitater);
        Sexy_MemoryImage_Delete(imageImitaterLess);

        Sexy_String_Delete(holder);
        Sexy_String_Delete(holder1);
        Sexy_String_Delete(holder2);
    }
}

void LawnApp_LoadingThreadProc(LawnApp *lawnApp) {
    // 加载新增资源用
    old_LawnApp_LoadingThreadProc(lawnApp);
    LawnApp_LoadAddonImages(lawnApp);
    LawnApp_LoadAddonSounds(lawnApp);
    //    LawnApp_DoConvertImitaterImages(lawnApp);
    TodStringListLoad("addonFiles/properties/AddonStrings.txt"); // 加载自定义字符串

    // 加载三个主界面背景白噪音Foley
    *gFoleyParamArraySizeAddr += 3;
    gMenuLeftFoley.mSfxID[0] = Sexy_SOUND_MENU_L_ST_Addr;
    gMenuCenterFoley.mSfxID[0] = Sexy_SOUND_MENU_C_ST_Addr;
    gMenuRightFoley.mSfxID[0] = Sexy_SOUND_MENU_R_ST_Addr;

    //    //试图修复偶现的地图错位现象。不知道是否有效
    //    LawnApp_Load(lawnApp,"DelayLoad_Background1");
    //    LawnApp_Load(lawnApp,"DelayLoad_BackgroundUnsodded");
    //    LawnApp_Load(lawnApp,"DelayLoad_Background2");
    //    LawnApp_Load(lawnApp,"DelayLoad_Background3");
    //    LawnApp_Load(lawnApp,"DelayLoad_Background4");
    //    LawnApp_Load(lawnApp,"DelayLoad_Background5");
    //    LawnApp_Load(lawnApp,"DelayLoad_Background6");

    if (showHouse) {
        ReanimatorEnsureDefinitionLoaded(ReanimationType::REANIM_LEADERBOARDS_HOUSE, true);
        lawnApp->mCompletedLoadingThreadTasks += 136;
    }
    ReanimatorEnsureDefinitionLoaded(ReanimationType::REANIM_ZOMBATAR_HEAD, true);
    lawnApp->mCompletedLoadingThreadTasks += 136;
}

bool LawnApp_IsChallengeWithoutSeedBank(LawnApp *lawnApp) {
    // 黄油爆米花专用
    return lawnApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_BUTTERED_POPCORN || old_LawnApp_IsChallengeWithoutSeedBank(lawnApp);
}

int LawnApp_GetSeedsAvailable(LawnApp *lawnApp, int isZombieChooser) {
    // 解锁僵尸方六张隐藏卡片
    if (isZombieChooser) {
        return 86;
    }
    return old_LawnApp_GetSeedsAvailable(lawnApp, isZombieChooser);
}

void LawnApp_HardwareInit(LawnApp *lawnApp) {
    old_LawnApp_HardwareInit(lawnApp);
    //    if (useXboxMusic) {
    //        Music2_Delete(lawnApp->mMusic);
    //        lawnApp->mMusic = (Music2*) operator new(104u);
    //        Music_Music(lawnApp->mMusic); // 使用Music而非Music2
    //    }
}

int LawnApp_GetNumPreloadingTasks(LawnApp *lawnApp) {
    int oldResult = old_LawnApp_GetNumPreloadingTasks(lawnApp);

    int addonReanimsNum = (ReanimationType::NUM_REANIMS - ReanimationType::REANIM_ZOMBATAR_HEAD) + (showHouse ? 1 : 0);
    int addonSoundsNum = (sizeof(addonSounds) / sizeof(int));
    int addonImagesNum = (sizeof(AddonImages) / sizeof(Sexy::Image *));

    oldResult += 136 * addonReanimsNum;
    oldResult += 54 * addonSoundsNum;
    oldResult += 9 * addonImagesNum;

    return oldResult;
}

bool LawnApp_GrantAchievement(LawnApp *lawnApp, AchievementId::AchievementId theAchievementId) {
    // 一些非Board的成就在这里处理
    PlayerInfo *playerInfo = lawnApp->mPlayerInfo;
    if (!playerInfo->mAchievements[theAchievementId]) {
        LawnApp_PlaySample(lawnApp, addonSounds.achievement);
        //    int holder[1];
        //    Sexy_StrFormat(holder,"一二三四五六 成就达成！");
        //    ((CustomMessageWidget*)board->mAdvice)->mIcon = GetIconByAchievementId(theAchievementId);
        //    Board_DisplayAdviceAgain(board, holder, a::MESSAGE_STYLE_ACHIEVEMENT, AdviceType::ADVICE_NEED_ACHIVEMENT_EARNED);
        //    Sexy_String_Delete(holder);
        playerInfo->mAchievements[theAchievementId] = true;
        return true;
    }
    return false;
}

bool LawnApp_IsNight(LawnApp *lawnApp) {
    // 添加非冒险模式（如：小游戏、花园、智慧树）关卡内进商店的昼夜判定
    if (lawnApp->mBoard != nullptr) {
        return Board_StageIsNight(lawnApp->mBoard);
    }
    return old_LawnApp_IsNight(lawnApp);
}

int LawnApp_TrophiesNeedForGoldSunflower(LawnApp *lawnApp) {
    // 修复新增的小游戏不记入金向日葵达成条件
    int theNumMiniGames = 0;
    for (int i = 0; i < 94; ++i) {
        if (GetChallengeDefinition(i).mPage == ChallengePage::CHALLENGE_PAGE_CHALLENGE) {
            theNumMiniGames++;
        }
    }
    return theNumMiniGames + 18 + 10 - LawnApp_GetNumTrophies(lawnApp, ChallengePage::CHALLENGE_PAGE_SURVIVAL) - LawnApp_GetNumTrophies(lawnApp, ChallengePage::CHALLENGE_PAGE_CHALLENGE)
        - LawnApp_GetNumTrophies(lawnApp, ChallengePage::CHALLENGE_PAGE_PUZZLE);
}

void LawnApp_SetFoleyVolume(LawnApp *lawnApp, FoleyType::FoleyType type, double theVolume) {
    TodFoley *mSoundSystem = lawnApp->mSoundSystem;
    FoleyTypeData *foleyTypeData = &mSoundSystem->mTypeData[type];
    for (FoleyInstance &foleyInstance : foleyTypeData->mFoleyInstances) {
        if (foleyInstance.mRefCount != 0) {
            int *mInstance = foleyInstance.mInstance;
            (*(void (**)(int *, uint32_t, double))(*mInstance + 28))(mInstance, *(uint32_t *)(*mInstance + 28), theVolume);
        }
    }
}

void Sexy_SexyAppBase_SexyAppBase(SexyAppBase *appBase) {
    old_Sexy_SexyAppBase_SexyAppBase(appBase);
    //    LOGD("%d",*((uint32_t *)appBase + 464));
    //    *((uint32_t *)appBase + 464) = 0; ;
    //    *((uint32_t *)appBase + 380) = 100;

    //    Sexy_Ratio_Set((int *)appBase + 399, 16, 10);
    //    Sexy_Ratio_Set((int *)appBase + 395, 4, 3);
    //    Sexy_Ratio_Set((int *)appBase + 397, 4, 3);
    //    *((uint32_t *)appBase + 403) = 600;
    //    *((uint32_t *)appBase + 402) = 800;
}

void LawnApp_ShowLeaderboards(LawnApp *lawnApp) {
    mMainMenuLeaderboardsWidget = (LeaderboardsWidget *)operator new(sizeof(LeaderboardsWidget));
    LeaderboardsWidget_LeaderboardsWidget(mMainMenuLeaderboardsWidget, lawnApp);
    (*(void (**)(int *, Sexy::Widget *))(*lawnApp->mWidgetManager + 24))(lawnApp->mWidgetManager, mMainMenuLeaderboardsWidget); // AddWidget()
    (*(void (**)(int *, Sexy::Widget *))(*lawnApp->mWidgetManager + 48))(lawnApp->mWidgetManager, mMainMenuLeaderboardsWidget); // SetFocusedWidget()
}

void LawnApp_KillLeaderboards(LawnApp *lawnApp) {
    if (mMainMenuLeaderboardsWidget == nullptr)
        return;
    (*(void (**)(int *, Sexy::Widget *))(*lawnApp->mWidgetManager + 28))(lawnApp->mWidgetManager, mMainMenuLeaderboardsWidget); // RemoveWidget()
    (*((void (**)(LawnApp *, Sexy::Widget *))lawnApp->vTable + 47))(lawnApp, mMainMenuLeaderboardsWidget);                      // MSGBOX()
    mMainMenuLeaderboardsWidget = nullptr;
}

void LawnApp_ShowZombatarScreen(LawnApp *lawnApp) {
    mMainMenuZombatarWidget = (ZombatarWidget *)operator new(sizeof(ZombatarWidget));
    ZombatarWidget_ZombatarWidget(mMainMenuZombatarWidget, lawnApp);
    //    Sexy_Widget_Resize(mMainMenuZombatarWidget,-80,-60,960,720);
    (*(void (**)(int *, Sexy::Widget *))(*lawnApp->mWidgetManager + 24))(lawnApp->mWidgetManager, mMainMenuZombatarWidget); // AddWidget()
    (*(void (**)(int *, Sexy::Widget *))(*lawnApp->mWidgetManager + 48))(lawnApp->mWidgetManager, mMainMenuZombatarWidget); // SetFocusedWidget()
}

void LawnApp_KillZombatarScreen(LawnApp *lawnApp) {
    if (mMainMenuZombatarWidget == nullptr)
        return;
    (*(void (**)(int *, Sexy::Widget *))(*lawnApp->mWidgetManager + 28))(lawnApp->mWidgetManager, mMainMenuZombatarWidget); // RemoveWidget()
    (*((void (**)(LawnApp *, Sexy::Widget *))lawnApp->vTable + 47))(lawnApp, mMainMenuZombatarWidget);                      // MSGBOX()
    mMainMenuZombatarWidget = nullptr;
}


namespace {
char houseControl[6][15] = {"anim_house_1_1", "anim_house_1_1", "anim_house_1_2", "anim_house_1_3", "anim_house_1_4", "anim_house_1_5"};
char housePrefix[5][8] = {"house_1", "house_2", "house_3", "house_4", "house_5"};
} // namespace

void LawnApp_SetHouseReanim(LawnApp *lawnApp, Reanimation *houseAnimation) {
    PlayerInfo *mPlayerInfo = lawnApp->mPlayerInfo;
    if (mPlayerInfo == nullptr)
        return;
    HouseType::HouseType currentHouseType = mPlayerInfo->mGameStats.mHouseType;
    int currentHouseLevel = mPlayerInfo->mPurchases[StoreItem::STORE_ITEM_BLUEPRINT_BLING + currentHouseType];
    if (currentHouseType == HouseType::BLUEPRINT_BLING) {
        if (LawnApp_CanShowStore(lawnApp)) {
            currentHouseLevel += 3;
        } else if (LawnApp_CanShowAlmanac(lawnApp)) {
            currentHouseLevel += 2;
        } else {
            currentHouseLevel += 1;
        }
    }

    Reanimation_PlayReanim(houseAnimation, houseControl[currentHouseLevel], ReanimLoopType::REANIM_LOOP, 0, 12.0f);

    for (int i = 0; i < 5; ++i) {
        Reanimation_HideTrackByPrefix(houseAnimation, housePrefix[i], i != currentHouseType);
    }

    Reanimation_HideTrackByPrefix(houseAnimation, "achievement", true);
}


static bool zombatarResLoaded;

void LawnApp_LoadZombatarResources(LawnApp *lawnApp) {
    if (zombatarResLoaded)
        return;
    addonZombatarImages.zombatar_main_bg = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_main_bg");
    addonZombatarImages.zombatar_widget_bg = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_widget_bg");
    addonZombatarImages.zombatar_widget_inner_bg = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_widget_inner_bg");
    addonZombatarImages.zombatar_display_window = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_display_window");
    addonZombatarImages.zombatar_mainmenuback_highlight = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_mainmenuback_highlight");
    addonZombatarImages.zombatar_finished_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_finished_button");
    addonZombatarImages.zombatar_finished_button_highlight = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_finished_button_highlight");
    addonZombatarImages.zombatar_view_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_view_button");
    addonZombatarImages.zombatar_view_button_highlight = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_view_button_highlight");
    addonZombatarImages.zombatar_skin_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_skin_button");
    addonZombatarImages.zombatar_skin_button_highlight = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_skin_button_highlight");
    addonZombatarImages.zombatar_hair_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_button");
    addonZombatarImages.zombatar_hair_button_highlight = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_button_highlight");
    addonZombatarImages.zombatar_fhair_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_fhair_button");
    addonZombatarImages.zombatar_fhair_button_highlight = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_fhair_button_highlight");
    addonZombatarImages.zombatar_tidbits_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_button");
    addonZombatarImages.zombatar_tidbits_button_highlight = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_button_highlight");
    addonZombatarImages.zombatar_eyewear_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_button");
    addonZombatarImages.zombatar_eyewear_button_highlight = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_button_highlight");
    addonZombatarImages.zombatar_clothes_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_button");
    addonZombatarImages.zombatar_clothes_button_highlight = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_button_highlight");
    addonZombatarImages.zombatar_accessory_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_button");
    addonZombatarImages.zombatar_accessory_button_highlight = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_button_highlight");
    addonZombatarImages.zombatar_hats_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_button");
    addonZombatarImages.zombatar_hats_button_highlight = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_button_highlight");
    addonZombatarImages.zombatar_next_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_next_button");
    addonZombatarImages.zombatar_prev_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_prev_button");
    addonZombatarImages.zombatar_backdrops_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_backdrops_button");
    addonZombatarImages.zombatar_backdrops_button_highlight = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_backdrops_button_highlight");
    addonZombatarImages.zombatar_background_crazydave = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_crazydave");
    addonZombatarImages.zombatar_background_menu = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_menu");
    addonZombatarImages.zombatar_background_menu_dos = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_menu_dos");
    addonZombatarImages.zombatar_background_roof = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_roof");
    addonZombatarImages.zombatar_background_blank = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_blank");
    addonZombatarImages.zombatar_background_aquarium = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_aquarium");
    addonZombatarImages.zombatar_background_crazydave_night = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_crazydave_night");
    addonZombatarImages.zombatar_background_day_RV = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_day_RV");
    addonZombatarImages.zombatar_background_fog_sunshade = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_fog_sunshade");
    addonZombatarImages.zombatar_background_garden_hd = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_garden_hd");
    addonZombatarImages.zombatar_background_garden_moon = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_garden_moon");
    addonZombatarImages.zombatar_background_garden_mushrooms = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_garden_mushrooms");
    addonZombatarImages.zombatar_background_hood = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_hood");
    addonZombatarImages.zombatar_background_hood_blue = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_hood_blue");
    addonZombatarImages.zombatar_background_hood_brown = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_hood_brown");
    addonZombatarImages.zombatar_background_hood_yellow = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_hood_yellow");
    addonZombatarImages.zombatar_background_mausoleum = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_mausoleum");
    addonZombatarImages.zombatar_background_moon = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_moon");
    addonZombatarImages.zombatar_background_moon_distant = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_moon_distant");
    addonZombatarImages.zombatar_background_night_RV = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_night_RV");
    addonZombatarImages.zombatar_background_pool_sunshade = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_pool_sunshade");
    addonZombatarImages.zombatar_background_roof_distant = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_roof_distant");
    addonZombatarImages.zombatar_background_sky_day = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_sky_day");
    addonZombatarImages.zombatar_background_sky_night = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_sky_night");
    addonZombatarImages.zombatar_background_sky_purple = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_sky_purple");
    addonZombatarImages.zombatar_background_7 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_7");
    addonZombatarImages.zombatar_background_8 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_8");
    addonZombatarImages.zombatar_background_9 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_9");
    addonZombatarImages.zombatar_background_10 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_10");
    addonZombatarImages.zombatar_background_11 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_11");
    addonZombatarImages.zombatar_background_11_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_11_1");
    addonZombatarImages.zombatar_background_12 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_12");
    addonZombatarImages.zombatar_background_12_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_12_1");
    addonZombatarImages.zombatar_background_13 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_13");
    addonZombatarImages.zombatar_background_13_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_13_1");
    addonZombatarImages.zombatar_background_14 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_14");
    addonZombatarImages.zombatar_background_14_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_14_1");
    addonZombatarImages.zombatar_background_15 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_15");
    addonZombatarImages.zombatar_background_15_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_15_1");
    addonZombatarImages.zombatar_background_16 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_16");
    addonZombatarImages.zombatar_background_16_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_16_1");
    addonZombatarImages.zombatar_background_17 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_17");
    addonZombatarImages.zombatar_background_17_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_17_1");
    addonZombatarImages.zombatar_background_bej3_bridge_shroom_castles = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_bridge_shroom_castles");
    addonZombatarImages.zombatar_background_bej3_canyon_wall = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_canyon_wall");
    addonZombatarImages.zombatar_background_bej3_crystal_mountain_peak = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_crystal_mountain_peak");
    addonZombatarImages.zombatar_background_bej3_dark_cave_thing = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_dark_cave_thing");
    addonZombatarImages.zombatar_background_bej3_desert_pyramids_sunset = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_desert_pyramids_sunset");
    addonZombatarImages.zombatar_background_bej3_fairy_cave_village = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_fairy_cave_village");
    addonZombatarImages.zombatar_background_bej3_floating_rock_city = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_floating_rock_city");
    addonZombatarImages.zombatar_background_bej3_horse_forset_tree = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_horse_forset_tree");
    addonZombatarImages.zombatar_background_bej3_jungle_ruins_path = LawnApp_GetImageByFileName(lawnApp, "PvZ/addonFiles/images/ZombatarWidget/zombatar_background_bej3_jungle_ruins_pa.h");
    addonZombatarImages.zombatar_background_bej3_lantern_plants_world = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_lantern_plants_world");
    addonZombatarImages.zombatar_background_bej3_lightning = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_lightning");
    addonZombatarImages.zombatar_background_bej3_lion_tower_cascade = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_lion_tower_cascade");
    addonZombatarImages.zombatar_background_bej3_pointy_ice_path = LawnApp_GetImageByFileName(lawnApp, "PvZ/addonFiles/images/ZombatarWidget/zombatar_background_bej3_pointy_ice_pa.h");
    addonZombatarImages.zombatar_background_bej3_pointy_ice_path_purple = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_pointy_ice_path_purple");
    addonZombatarImages.zombatar_background_bej3_rock_city_lake = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_rock_city_lake");
    addonZombatarImages.zombatar_background_bej3_snowy_cliffs_castle = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_snowy_cliffs_castle");
    addonZombatarImages.zombatar_background_bej3_treehouse_waterfall = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_treehouse_waterfall");
    addonZombatarImages.zombatar_background_bej3_tube_forest_night = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_tube_forest_night");
    addonZombatarImages.zombatar_background_bej3_water_bubble_city = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_water_bubble_city");
    addonZombatarImages.zombatar_background_bej3_water_fall_cliff = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_water_fall_cliff");
    addonZombatarImages.zombatar_background_bejblitz_6 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bejblitz_6");
    addonZombatarImages.zombatar_background_bejblitz_8 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bejblitz_8");
    addonZombatarImages.zombatar_background_bejblitz_main_menu = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bejblitz_main_menu");
    addonZombatarImages.zombatar_background_peggle_bunches = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_bunches");
    addonZombatarImages.zombatar_background_peggle_fever = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_fever");
    addonZombatarImages.zombatar_background_peggle_level1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_level1");
    addonZombatarImages.zombatar_background_peggle_level4 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_level4");
    addonZombatarImages.zombatar_background_peggle_level5 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_level5");
    addonZombatarImages.zombatar_background_peggle_menu = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_menu");
    addonZombatarImages.zombatar_background_peggle_nights_bjorn3 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_nights_bjorn3");
    addonZombatarImages.zombatar_background_peggle_nights_bjorn4 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_nights_bjorn4");
    addonZombatarImages.zombatar_background_peggle_nights_claude5 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_nights_claude5");
    addonZombatarImages.zombatar_background_peggle_nights_kalah1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_nights_kalah1");
    addonZombatarImages.zombatar_background_peggle_nights_kalah4 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_nights_kalah4");
    addonZombatarImages.zombatar_background_peggle_nights_master5 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_nights_master5");
    addonZombatarImages.zombatar_background_peggle_nights_renfield5 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_nights_renfield5");
    addonZombatarImages.zombatar_background_peggle_nights_tut5 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_nights_tut5");
    addonZombatarImages.zombatar_background_peggle_nights_warren3 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_nights_warren3");
    addonZombatarImages.zombatar_background_peggle_paperclips = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_paperclips");
    addonZombatarImages.zombatar_background_peggle_waves = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_waves");
    addonZombatarImages.zombatar_hair_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_1");
    addonZombatarImages.zombatar_hair_1_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_1_mask");
    addonZombatarImages.zombatar_hair_2 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_2");
    addonZombatarImages.zombatar_hair_2_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_2_mask");
    addonZombatarImages.zombatar_hair_3 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_3");
    addonZombatarImages.zombatar_hair_4 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_4");
    addonZombatarImages.zombatar_hair_5 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_5");
    addonZombatarImages.zombatar_hair_6 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_6");
    addonZombatarImages.zombatar_hair_7 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_7");
    addonZombatarImages.zombatar_hair_8 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_8");
    addonZombatarImages.zombatar_hair_9 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_9");
    addonZombatarImages.zombatar_hair_10 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_10");
    addonZombatarImages.zombatar_hair_11 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_11");
    addonZombatarImages.zombatar_hair_11_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_11_mask");
    addonZombatarImages.zombatar_hair_12 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_12");
    addonZombatarImages.zombatar_hair_12_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_12_mask");
    addonZombatarImages.zombatar_hair_13 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_13");
    addonZombatarImages.zombatar_hair_13_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_13_mask");
    addonZombatarImages.zombatar_hair_14 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_14");
    addonZombatarImages.zombatar_hair_14_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_14_mask");
    addonZombatarImages.zombatar_hair_15 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_15");
    addonZombatarImages.zombatar_hair_15_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_15_mask");
    addonZombatarImages.zombatar_hair_16 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_16");
    addonZombatarImages.zombatar_facialhair_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_1");
    addonZombatarImages.zombatar_facialhair_1_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_1_mask");
    addonZombatarImages.zombatar_facialhair_2 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_2");
    addonZombatarImages.zombatar_facialhair_3 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_3");
    addonZombatarImages.zombatar_facialhair_4 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_4");
    addonZombatarImages.zombatar_facialhair_4_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_4_mask");
    addonZombatarImages.zombatar_facialhair_5 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_5");
    addonZombatarImages.zombatar_facialhair_6 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_6");
    addonZombatarImages.zombatar_facialhair_7 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_7");
    addonZombatarImages.zombatar_facialhair_8 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_8");
    addonZombatarImages.zombatar_facialhair_8_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_8_mask");
    addonZombatarImages.zombatar_facialhair_9 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_9");
    addonZombatarImages.zombatar_facialhair_9_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_9_mask");
    addonZombatarImages.zombatar_facialhair_10 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_10");
    addonZombatarImages.zombatar_facialhair_10_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_10_mask");
    addonZombatarImages.zombatar_facialhair_11 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_11");
    addonZombatarImages.zombatar_facialhair_11_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_11_mask");
    addonZombatarImages.zombatar_facialhair_12 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_12");
    addonZombatarImages.zombatar_facialhair_12_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_12_mask");
    addonZombatarImages.zombatar_facialhair_13 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_13");
    addonZombatarImages.zombatar_facialhair_14 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_14");
    addonZombatarImages.zombatar_facialhair_14_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_14_mask");
    addonZombatarImages.zombatar_facialhair_15 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_15");
    addonZombatarImages.zombatar_facialhair_15_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_15_mask");
    addonZombatarImages.zombatar_facialhair_16 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_16");
    addonZombatarImages.zombatar_facialhair_16_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_16_mask");
    addonZombatarImages.zombatar_facialhair_17 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_17");
    addonZombatarImages.zombatar_facialhair_18 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_18");
    addonZombatarImages.zombatar_facialhair_18_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_18_mask");
    addonZombatarImages.zombatar_facialhair_19 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_19");
    addonZombatarImages.zombatar_facialhair_20 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_20");
    addonZombatarImages.zombatar_facialhair_21 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_21");
    addonZombatarImages.zombatar_facialhair_21_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_21_mask");
    addonZombatarImages.zombatar_facialhair_22 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_22");
    addonZombatarImages.zombatar_facialhair_22_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_22_mask");
    addonZombatarImages.zombatar_facialhair_23 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_23");
    addonZombatarImages.zombatar_facialhair_23_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_23_mask");
    addonZombatarImages.zombatar_facialhair_24 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_24");
    addonZombatarImages.zombatar_facialhair_24_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_24_mask");
    addonZombatarImages.zombatar_eyewear_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_1");
    addonZombatarImages.zombatar_eyewear_1_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_1_mask");
    addonZombatarImages.zombatar_eyewear_2 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_2");
    addonZombatarImages.zombatar_eyewear_2_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_2_mask");
    addonZombatarImages.zombatar_eyewear_3 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_3");
    addonZombatarImages.zombatar_eyewear_3_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_3_mask");
    addonZombatarImages.zombatar_eyewear_4 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_4");
    addonZombatarImages.zombatar_eyewear_4_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_4_mask");
    addonZombatarImages.zombatar_eyewear_5 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_5");
    addonZombatarImages.zombatar_eyewear_5_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_5_mask");
    addonZombatarImages.zombatar_eyewear_6 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_6");
    addonZombatarImages.zombatar_eyewear_6_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_6_mask");
    addonZombatarImages.zombatar_eyewear_7 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_7");
    addonZombatarImages.zombatar_eyewear_7_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_7_mask");
    addonZombatarImages.zombatar_eyewear_8 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_8");
    addonZombatarImages.zombatar_eyewear_8_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_8_mask");
    addonZombatarImages.zombatar_eyewear_9 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_9");
    addonZombatarImages.zombatar_eyewear_9_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_9_mask");
    addonZombatarImages.zombatar_eyewear_10 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_10");
    addonZombatarImages.zombatar_eyewear_10_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_10_mask");
    addonZombatarImages.zombatar_eyewear_11 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_11");
    addonZombatarImages.zombatar_eyewear_11_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_11_mask");
    addonZombatarImages.zombatar_eyewear_12 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_12");
    addonZombatarImages.zombatar_eyewear_12_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_12_mask");
    addonZombatarImages.zombatar_eyewear_13 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_13");
    addonZombatarImages.zombatar_eyewear_14 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_14");
    addonZombatarImages.zombatar_eyewear_15 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_15");
    addonZombatarImages.zombatar_eyewear_16 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_16");
    addonZombatarImages.zombatar_accessory_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_1");
    addonZombatarImages.zombatar_accessory_2 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_2");
    addonZombatarImages.zombatar_accessory_3 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_3");
    addonZombatarImages.zombatar_accessory_4 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_4");
    addonZombatarImages.zombatar_accessory_5 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_5");
    addonZombatarImages.zombatar_accessory_6 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_6");
    addonZombatarImages.zombatar_accessory_8 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_8");
    addonZombatarImages.zombatar_accessory_9 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_9");
    addonZombatarImages.zombatar_accessory_10 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_10");
    addonZombatarImages.zombatar_accessory_11 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_11");
    addonZombatarImages.zombatar_accessory_12 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_12");
    addonZombatarImages.zombatar_accessory_13 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_13");
    addonZombatarImages.zombatar_accessory_14 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_14");
    addonZombatarImages.zombatar_accessory_15 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_15");
    addonZombatarImages.zombatar_accessory_16 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_16");
    addonZombatarImages.zombatar_hats_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_1");
    addonZombatarImages.zombatar_hats_1_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_1_mask");
    addonZombatarImages.zombatar_hats_2 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_2");
    addonZombatarImages.zombatar_hats_3 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_3");
    addonZombatarImages.zombatar_hats_3_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_3_mask");
    addonZombatarImages.zombatar_hats_4 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_4");
    addonZombatarImages.zombatar_hats_5 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_5");
    addonZombatarImages.zombatar_hats_6 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_6");
    addonZombatarImages.zombatar_hats_6_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_6_mask");
    addonZombatarImages.zombatar_hats_7 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_7");
    addonZombatarImages.zombatar_hats_7_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_7_mask");
    addonZombatarImages.zombatar_hats_8 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_8");
    addonZombatarImages.zombatar_hats_8_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_8_mask");
    addonZombatarImages.zombatar_hats_9 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_9");
    addonZombatarImages.zombatar_hats_9_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_9_mask");
    addonZombatarImages.zombatar_hats_10 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_10");
    addonZombatarImages.zombatar_hats_11 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_11");
    addonZombatarImages.zombatar_hats_11_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_11_mask");
    addonZombatarImages.zombatar_hats_12 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_12");
    addonZombatarImages.zombatar_hats_13 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_13");
    addonZombatarImages.zombatar_hats_14 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_14");
    addonZombatarImages.zombatar_tidbits_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_1");
    addonZombatarImages.zombatar_tidbits_2 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_2");
    addonZombatarImages.zombatar_tidbits_3 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_3");
    addonZombatarImages.zombatar_tidbits_4 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_4");
    addonZombatarImages.zombatar_tidbits_5 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_5");
    addonZombatarImages.zombatar_tidbits_6 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_6");
    addonZombatarImages.zombatar_tidbits_7 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_7");
    addonZombatarImages.zombatar_tidbits_8 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_8");
    addonZombatarImages.zombatar_tidbits_9 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_9");
    addonZombatarImages.zombatar_tidbits_10 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_10");
    addonZombatarImages.zombatar_tidbits_11 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_11");
    addonZombatarImages.zombatar_tidbits_12 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_12");
    addonZombatarImages.zombatar_tidbits_13 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_13");
    addonZombatarImages.zombatar_tidbits_14 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_14");
    addonZombatarImages.zombatar_clothes_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_1");
    addonZombatarImages.zombatar_clothes_2 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_2");
    addonZombatarImages.zombatar_clothes_3 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_3");
    addonZombatarImages.zombatar_clothes_4 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_4");
    addonZombatarImages.zombatar_clothes_5 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_5");
    addonZombatarImages.zombatar_clothes_6 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_6");
    addonZombatarImages.zombatar_clothes_7 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_7");
    addonZombatarImages.zombatar_clothes_8 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_8");
    addonZombatarImages.zombatar_clothes_9 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_9");
    addonZombatarImages.zombatar_clothes_10 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_10");
    addonZombatarImages.zombatar_clothes_11 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_11");
    addonZombatarImages.zombatar_clothes_12 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_12");
    addonZombatarImages.zombatar_zombie_blank = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_zombie_blank");
    addonZombatarImages.zombatar_zombie_blank_skin = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_zombie_blank_skin");
    int xClip = 130;
    int yClip = 130;
    TRect rect = {addonZombatarImages.zombatar_zombie_blank->mWidth - xClip, addonZombatarImages.zombatar_zombie_blank->mHeight - yClip, xClip, yClip};
    addonZombatarImages.zombatar_zombie_blank_part = Sexy_SexyAppBase_CopyImage2(lawnApp, addonZombatarImages.zombatar_zombie_blank, &rect);
    addonZombatarImages.zombatar_zombie_blank_skin_part = Sexy_SexyAppBase_CopyImage2(lawnApp, addonZombatarImages.zombatar_zombie_blank_skin, &rect);
    addonZombatarImages.zombatar_colors_bg = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_colors_bg");
    addonZombatarImages.zombatar_colorpicker = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_colorpicker");
    addonZombatarImages.zombatar_colorpicker_none = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_colorpicker_none");
    addonZombatarImages.zombatar_accessory_bg = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_bg");
    addonZombatarImages.zombatar_accessory_bg_highlight = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_bg_highlight");
    addonZombatarImages.zombatar_accessory_bg_none = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_bg_none");
    zombatarResLoaded = true;
}
