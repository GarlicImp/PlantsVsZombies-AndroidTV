#include "PvZ/Lawn/Music.h"
#include "PvZ/Symbols.h"
#include "PvZ/SexyAppFramework/Graphics.h"
#include "PvZ/Enums.h"
#include "PvZ/GlobalVariable.h"
#include "PvZ/Lawn/Board.h"
#include "PvZ/Lawn/LawnApp.h"

#define HIWORD(a) ((a) >> 16)
#define LOWORD(a) ((a) & 0xFFFF)


void Music_StartGameMusic(Music *music, bool a2) {
    old_Music_StartGameMusic(music, a2);
}


namespace {
bool muteMusic;
int theCounter;
} // namespace

void Music_SetupMusicFileForTune1(Music *music, MusicFile::MusicFile theMusicFile, MusicTune::MusicTune tune) {
    int v7;  // r7
    int v9;  // r9
    int v10; // r8
    int v11; // r4
    int v8;
    float v13; // r3
    bool v14;  // r2
    int v15;   // r2

    if (tune == MusicTune::DayGrasswalk) {
        switch (theMusicFile) {
            case MusicFile::MUSIC_FILE_MAIN_MUSIC:
                v8 = -1;
                v7 = 23;
                v9 = 0;
                v10 = 29;
                break;
            case MusicFile::MUSIC_FILE_DRUMS:
                v8 = -1;
                v7 = 26;
                v9 = 24;
                v10 = 29;
                break;
            case MusicFile::MUSIC_FILE_HIHATS:
                v7 = 27;
                v8 = -1;
                v9 = 27;
                v10 = 29;
                break;
        }
    } else if (tune == MusicTune::PoolWaterygraves) {
        switch (theMusicFile) {
            case MusicFile::MUSIC_FILE_MAIN_MUSIC:
                v8 = -1;
                v7 = 17;
                v10 = 29;
                break;
            case MusicFile::MUSIC_FILE_DRUMS:
                v8 = -1;
                v7 = 28;
                v9 = 18;
                v10 = 29;
                break;
            case MusicFile::MUSIC_FILE_HIHATS:
                v8 = 29;
                v7 = 24;
                v10 = 29;
                v9 = 18;
                break;
        }
    } else if (tune == MusicTune::FogRigormormist) {
        switch (theMusicFile) {
            case MusicFile::MUSIC_FILE_MAIN_MUSIC:
                v9 = 0;
                v8 = -1;
                v7 = 15;
                v10 = 29;
                break;
            case MusicFile::MUSIC_FILE_DRUMS:
                v8 = -1;
                v7 = 22;
                v9 = 16;
                v10 = 29;
                break;
            case MusicFile::MUSIC_FILE_HIHATS:
                v7 = 23;
                v8 = -1;
                v9 = 23;
                v10 = 29;
                break;
        }
    } else if (tune == MusicTune::RoofGrazetheroof) {
        switch (theMusicFile) {
            case MusicFile::MUSIC_FILE_MAIN_MUSIC:
                v8 = -1;
                v7 = 17;
                v9 = 0;
                v10 = 29;
                break;
            case MusicFile::MUSIC_FILE_DRUMS:
                v8 = -1;
                v7 = 20;
                v9 = 18;
                v10 = 29;
                break;
            case MusicFile::MUSIC_FILE_HIHATS:
                v7 = 21;
                v8 = -1;
                v9 = 21;
                v10 = 29;
                break;
        }
    } else if ((unsigned int)(theMusicFile - 1) <= 2) {
        v7 = 29;
        v9 = 0;
        v10 = 29;
        v8 = -1;
    } else {
        v8 = -1;
        v10 = 0;
        v7 = -1;
        v9 = -1;
    }
    v11 = 0;
    do {
        v13 = 1.0;
        v14 = v11 <= v7;
        if (v11 < v9)
            v14 = 0;
        if (!v14) {
            if (v8 == v11)
                v13 = 1.0;
            else
                v13 = 0.0;
        }
        v15 = v11++;
        Sexy_AudiereMusicInterface_SetChannelVolume(music->mMusicInterface, theMusicFile, v15, v13);
    } while (v10 >= v11);
}

void Music_PlayFromOffset(Music *music, MusicFile::MusicFile theMusicFile, int theOffset, double theVolume) {
    Sexy_AudiereMusicInterface_StopMusic(music->mMusicInterface, theMusicFile);
    Music_SetupMusicFileForTune(music, theMusicFile, music->mCurMusicTune);
    Sexy_AudiereMusicInterface_PlayMusic(music->mMusicInterface, theMusicFile, theOffset, theMusicFile == MusicFile::MUSIC_FILE_CREDITS_ZOMBIES_ON_YOUR_LAWN);
    //    Sexy_AudiereMusicInterface_SetSongVolume(music->mMusicInterface, theMusicFile, theVolume);

    if (theMusicFile == MusicFile::MUSIC_FILE_MAIN_MUSIC) {
        // 加90ms静音，用于去除莫名其妙的开头鼓点声
        muteMusic = true;
        // theCounter = (Sexy_SexyAppBase_GetDialog(music->mApp,Dialogs::DIALOG_STORE) == nullptr || Sexy_SexyAppBase_GetDialog(music->mApp,Dialogs::DIALOG_ALMANAC) == nullptr) ? 10 : 18;
        theCounter = 10;
        Sexy_AudiereMusicInterface_SetVolume(music->mMusicInterface, 0.0);
    }
}

void Music::PlayMusic(MusicTune::MusicTune theMusicTune, int theOffset, int theDrumsOffset) {
    if (mMusicDisabled)
        return;
    mLastMusicTune = theMusicTune;
    mCurMusicTune = theMusicTune;
    mCurMusicFileMain = MusicFile::MUSIC_FILE_NONE;
    mCurMusicFileDrums = MusicFile::MUSIC_FILE_NONE;
    mCurMusicFileHihats = MusicFile::MUSIC_FILE_NONE;
    switch (theMusicTune) {
        case MusicTune::DayGrasswalk:
            if (theOffset == -1) {
                theOffset = 0;
            }
            mCurMusicFileMain = MusicFile::MUSIC_FILE_MAIN_MUSIC;
            mCurMusicFileDrums = MusicFile::MUSIC_FILE_DRUMS;
            mCurMusicFileHihats = MusicFile::MUSIC_FILE_HIHATS;
            Music_PlayFromOffset(this, mCurMusicFileMain, theOffset, 1.0);
            Music_PlayFromOffset(this, mCurMusicFileDrums, theOffset, 0.0);
            Music_PlayFromOffset(this, mCurMusicFileHihats, theOffset, 0.0);
            break;
        case MusicTune::NightMoongrains:
            if (theOffset == -1) {
                theDrumsOffset = 0;
                theOffset = 48;
            }
            mCurMusicFileMain = MusicFile::MUSIC_FILE_MAIN_MUSIC;
            mCurMusicFileDrums = MusicFile::MUSIC_FILE_DRUMS_NIGHTMOONGRAINS;
            Music_PlayFromOffset(this, mCurMusicFileMain, theOffset, 1.0);
            Music_PlayFromOffset(this, mCurMusicFileDrums, theDrumsOffset, 0.0);
            break;
        case MusicTune::PoolWaterygraves:
            if (theOffset == -1) {
                theOffset = 94;
            }
            mCurMusicFileMain = MusicFile::MUSIC_FILE_MAIN_MUSIC;
            mCurMusicFileDrums = MusicFile::MUSIC_FILE_DRUMS;
            mCurMusicFileHihats = MusicFile::MUSIC_FILE_HIHATS;
            Music_PlayFromOffset(this, mCurMusicFileMain, theOffset, 1.0);
            Music_PlayFromOffset(this, mCurMusicFileDrums, theOffset, 0.0);
            Music_PlayFromOffset(this, mCurMusicFileHihats, theOffset, 0.0);
            break;
        case MusicTune::FogRigormormist:
            if (theOffset == -1) {
                theOffset = 125;
            }
            mCurMusicFileMain = MusicFile::MUSIC_FILE_MAIN_MUSIC;
            mCurMusicFileDrums = MusicFile::MUSIC_FILE_DRUMS;
            mCurMusicFileHihats = MusicFile::MUSIC_FILE_HIHATS;
            Music_PlayFromOffset(this, mCurMusicFileMain, theOffset, 1.0);
            Music_PlayFromOffset(this, mCurMusicFileDrums, theOffset, 0.0);
            Music_PlayFromOffset(this, mCurMusicFileHihats, theOffset, 0.0);
            break;
        case MusicTune::RoofGrazetheroof:
            if (theOffset == -1) {
                theOffset = 184;
            }
            mCurMusicFileMain = MusicFile::MUSIC_FILE_MAIN_MUSIC;
            mCurMusicFileDrums = MusicFile::MUSIC_FILE_DRUMS;
            mCurMusicFileHihats = MusicFile::MUSIC_FILE_HIHATS;
            Music_PlayFromOffset(this, mCurMusicFileMain, theOffset, 1.0);
            Music_PlayFromOffset(this, mCurMusicFileDrums, theOffset, 0.0);
            Music_PlayFromOffset(this, mCurMusicFileHihats, theOffset, 0.0);
            break;
        case MusicTune::ChooseYourSeeds:
            mCurMusicFileMain = MusicFile::MUSIC_FILE_MAIN_MUSIC;
            if (theOffset == -1) {
                theOffset = 122;
            }
            Music_PlayFromOffset(this, mCurMusicFileMain, theOffset, 1.0);
            break;
        case MusicTune::TitleCrazyDaveMainTheme:
            mCurMusicFileMain = MusicFile::MUSIC_FILE_MAIN_MUSIC;
            if (theOffset == -1) {
                theOffset = 152;
            }
            Music_PlayFromOffset(this, mCurMusicFileMain, theOffset, 1.0);
            break;
        case MusicTune::ZenGarden:
            mCurMusicFileMain = MusicFile::MUSIC_FILE_MAIN_MUSIC;
            if (theOffset == -1) {
                theOffset = 221;
            }
            Music_PlayFromOffset(this, mCurMusicFileMain, theOffset, 1.0);
            break;
        case MusicTune::PuzzleCerebrawl:
            mCurMusicFileMain = MusicFile::MUSIC_FILE_MAIN_MUSIC;
            if (theOffset == -1) {
                theOffset = 177;
            }
            Music_PlayFromOffset(this, mCurMusicFileMain, theOffset, 1.0);
            break;
        case MusicTune::MinigameLoonboon:
            mCurMusicFileMain = MusicFile::MUSIC_FILE_MAIN_MUSIC;
            if (theOffset == -1) {
                theOffset = 166;
            }
            Music_PlayFromOffset(this, mCurMusicFileMain, theOffset, 1.0);
            break;
        case MusicTune::Conveyer:
            mCurMusicFileMain = MusicFile::MUSIC_FILE_MAIN_MUSIC;
            if (theOffset == -1) {
                theOffset = 212;
            }
            Music_PlayFromOffset(this, mCurMusicFileMain, theOffset, 1.0);
            break;
        case MusicTune::FinalBossBrainiacManiac:
            mCurMusicFileMain = MusicFile::MUSIC_FILE_MAIN_MUSIC;
            if (theOffset == -1) {
                theOffset = 158;
            }
            Music_PlayFromOffset(this, mCurMusicFileMain, theOffset, 1.0);
            break;
        case MusicTune::ZombiesOnYourLawn:
            mCurMusicFileMain = MusicFile::MUSIC_FILE_CREDITS_ZOMBIES_ON_YOUR_LAWN;
            if (theOffset == -1) {
                theOffset = 0;
            }
            Music_PlayFromOffset(this, mCurMusicFileMain, theOffset, 1.0);
            break;
        default:
            break;
    }
}

void Music::UpdateMusicBurst() {
    // 加90ms静音，用于去除莫名其妙的开头鼓点声
    if (muteMusic) {
        theCounter--;
        if (theCounter == 0) {
            muteMusic = false;
            PlayerInfo *playerInfo = mApp->mPlayerInfo;
            float theVolume = playerInfo == nullptr ? 1.0f : playerInfo->mMusicVolume / 0.8f;
            Sexy_AudiereMusicInterface_SetVolume(mMusicInterface, theVolume);
        }
    }
    Music_UpdateMusicBurst2(this);
}

void Music_UpdateMusicBurst2(Music *music) {
    LawnApp *mApp;                                     // ecx
    MusicTune::MusicTune mCurMusicTune;                // eax
    int MusicOrder;                                    // ebx
    int mBurstStateCounter;                            // eax
    int mDrumsStateCounter;                            // eax
    double v7;                                         // st7
    MusicBurstState::MusicBurstState mMusicBurstState; // eax
    double v9;                                         // st6
    int v11;                                           // eax
    MusicDrumsState::MusicDrumsState mMusicDrumsState; // eax
    unsigned int v14;                                  // eax
    MusicTune::MusicTune v15;                          // ebx
    int v16;                                           // edi
    int mQueuedDrumTrackPackedOrder_low;               // ecx
    int v18;                                           // eax
    float thePositionStart;                            // [esp+4h] [ebp-2Ch]
    float thePositionEnd;                              // [esp+8h] [ebp-28h]
    float aFadeTrackVolume;                            // [esp+1Ch] [ebp-14h]
    float aMainTrackVolume;                            // [esp+20h] [ebp-10h]
    float aDrumsJumpOrder;                             // [esp+24h] [ebp-Ch]
    unsigned int aPackedOrderMain;                     // [esp+28h] [ebp-8h]
    unsigned short v29;                                // [esp+2Ch] [ebp-4h]

    mApp = music->mApp;
    if (mApp->mBoard == nullptr || mApp->mGameMode == GameMode::Intro) {
        return;
    }
    if (music->mCurMusicTune > MusicTune::RoofGrazetheroof) {
        return;
    }
    mCurMusicTune = music->mCurMusicTune;
    bool isNightMoonGrainsMode = mCurMusicTune == MusicTune::NightMoongrains;
    MusicOrder = Music_GetMusicOrder(music, music->mCurMusicFileMain);
    mBurstStateCounter = music->mBurstStateCounter;
    v29 = MusicOrder;
    if (mBurstStateCounter > 0)
        music->mBurstStateCounter = mBurstStateCounter - 1;
    mDrumsStateCounter = music->mDrumsStateCounter;
    if (mDrumsStateCounter > 0)
        music->mDrumsStateCounter = mDrumsStateCounter - 1;
    v7 = 0.0;
    mMusicBurstState = music->mMusicBurstState;
    aMainTrackVolume = 0.0;
    aFadeTrackVolume = 0.0;
    v9 = 1.0;
    aDrumsJumpOrder = 1.0;
    switch (mMusicBurstState) {
        case MusicBurstState::MUSIC_BURST_OFF:
            if (Board_CountZombiesOnScreen(music->mApp->mBoard) > 10 || music->mBurstOverride == 1) {
                music->mMusicBurstState = MusicBurstState::MUSIC_BURST_STARTING;
                music->mBurstStateCounter = 400;
            }
            break;
        case MusicBurstState::MUSIC_BURST_STARTING:
            if (!isNightMoonGrainsMode) {
                aMainTrackVolume = TodAnimateCurveFloat(400, 0, music->mBurstStateCounter, 0.0, 1.0, TodCurves::Linear);
                v11 = music->mBurstStateCounter;
                if (v11 == 300) {
                    music->mMusicDrumsState = MusicDrumsState::MUSIC_DRUMS_ON_QUEUED;
                    music->mQueuedDrumTrackPackedOrder = MusicOrder;
                }
                if (v11 == 0) {
                    music->mMusicBurstState = MusicBurstState::MUSIC_BURST_ON;
                    music->mBurstStateCounter = 800;
                }
                break;
            }
            if (isNightMoonGrainsMode) {
                mMusicDrumsState = music->mMusicDrumsState;
                if (mMusicDrumsState != MusicDrumsState::MUSIC_DRUMS_OFF) {
                    if (mMusicDrumsState != MusicDrumsState::MUSIC_DRUMS_ON_QUEUED) {
                        aDrumsJumpOrder = TodAnimateCurveFloat(400, 0, music->mBurstStateCounter, 1.0, 0.0, TodCurves::Linear);
                        if (!music->mBurstStateCounter) {
                            music->mMusicBurstState = MusicBurstState::MUSIC_BURST_ON;
                            music->mBurstStateCounter = 800;
                        }
                        break;
                    }
                    music->mBurstStateCounter = 400;
                } else {
                    music->mMusicDrumsState = MusicDrumsState::MUSIC_DRUMS_ON_QUEUED;
                    music->mQueuedDrumTrackPackedOrder = MusicOrder;
                    music->mBurstStateCounter = 400;
                }
            }
            break;
        case MusicBurstState::MUSIC_BURST_ON:
            aMainTrackVolume = 1.0;
            if (isNightMoonGrainsMode)
                aDrumsJumpOrder = 0.0;
            if (music->mBurstStateCounter)
                break;
            if (Board_CountZombiesOnScreen(music->mApp->mBoard) < 4 && music->mBurstOverride == -1 || music->mBurstOverride == 2) {
                if (!isNightMoonGrainsMode) {
                    music->mMusicBurstState = MusicBurstState::MUSIC_BURST_FINISHING;
                    music->mBurstStateCounter = 800;
                    music->mMusicDrumsState = MusicDrumsState::MUSIC_DRUMS_OFF_QUEUED;
                    music->mQueuedDrumTrackPackedOrder = MusicOrder;
                } else if (isNightMoonGrainsMode) {
                    music->mMusicBurstState = MusicBurstState::MUSIC_BURST_FINISHING;
                    music->mBurstStateCounter = 1100;
                    music->mMusicDrumsState = MusicDrumsState::MUSIC_DRUMS_FADING;
                    music->mDrumsStateCounter = 800;
                }
            }
            break;
        case MusicBurstState::MUSIC_BURST_FINISHING:
            if (!isNightMoonGrainsMode)
                aMainTrackVolume = TodAnimateCurveFloat(800, 0, music->mBurstStateCounter, 1.0, 0.0, TodCurves::Linear);
            else
                aDrumsJumpOrder = TodAnimateCurveFloat(400, 0, music->mBurstStateCounter, 0.0, 1.0, TodCurves::Linear);
            if (!music->mBurstStateCounter && music->mMusicDrumsState == MusicDrumsState::MUSIC_DRUMS_OFF)
                music->mMusicBurstState = MusicBurstState::MUSIC_BURST_OFF;
            break;
    }
    v14 = MusicOrder;
    v15 = music->mCurMusicTune;
    v16 = 0;
    mQueuedDrumTrackPackedOrder_low = 0;
    v18 = HIWORD(v14);
    aPackedOrderMain = -1;
    if (!isNightMoonGrainsMode) {
        v16 = v18 / 128;
        mQueuedDrumTrackPackedOrder_low = HIWORD(music->mQueuedDrumTrackPackedOrder) / 128;
    } else if (isNightMoonGrainsMode) {
        v16 = v29;
        mQueuedDrumTrackPackedOrder_low = LOWORD(music->mQueuedDrumTrackPackedOrder);
        if (v18 > 252)
            v16 = v29 + 1;
        if (HIWORD(music->mQueuedDrumTrackPackedOrder) > 252u)
            ++mQueuedDrumTrackPackedOrder_low;
    }

    switch (music->mMusicDrumsState) {
        case MusicDrumsState::MUSIC_DRUMS_ON_QUEUED:
            if (isNightMoonGrainsMode) {
                if (v16 != mQueuedDrumTrackPackedOrder_low) {
                    aFadeTrackVolume = v9;
                    music->mMusicDrumsState = MusicDrumsState::MUSIC_DRUMS_ON;
                    aPackedOrderMain = (v16 % 2 != 0) + 74;
                }
            } else {
                aFadeTrackVolume = TodAnimateCurveFloat(300, 0, music->mBurstStateCounter, 0.0, 1.0, TodCurves::Linear);
                if (music->mBurstStateCounter == 1) {
                    music->mMusicDrumsState = MusicDrumsState::MUSIC_DRUMS_ON;
                }
            }

            break;
        case MusicDrumsState::MUSIC_DRUMS_ON:
            aFadeTrackVolume = v9;
            break;
        case MusicDrumsState::MUSIC_DRUMS_OFF_QUEUED:
            aFadeTrackVolume = v9;
            if (!isNightMoonGrainsMode) {
                music->mMusicDrumsState = MusicDrumsState::MUSIC_DRUMS_FADING;
                music->mDrumsStateCounter = 50;
            }
            break;
        case MusicDrumsState::MUSIC_DRUMS_FADING:
            thePositionEnd = v7;
            thePositionStart = v9;
            aFadeTrackVolume = TodAnimateCurveFloat(isNightMoonGrainsMode ? 800 : 50, 0, music->mDrumsStateCounter, thePositionStart, thePositionEnd, TodCurves::Linear);
            if (music->mDrumsStateCounter == 0)
                music->mMusicDrumsState = MusicDrumsState::MUSIC_DRUMS_OFF;
            break;
    }
    if (!isNightMoonGrainsMode) {
        Sexy_AudiereMusicInterface_SetSongVolume(music->mMusicInterface, MusicFile::MUSIC_FILE_HIHATS, aMainTrackVolume * music->mPauseVolume);
        Sexy_AudiereMusicInterface_SetSongVolume(music->mMusicInterface, MusicFile::MUSIC_FILE_DRUMS, aFadeTrackVolume * music->mPauseVolume);
    } else if (isNightMoonGrainsMode) {
        Sexy_AudiereMusicInterface_SetSongVolume(music->mMusicInterface, MusicFile::MUSIC_FILE_MAIN_MUSIC, aDrumsJumpOrder * music->mPauseVolume);
        Sexy_AudiereMusicInterface_SetSongVolume(music->mMusicInterface, MusicFile::MUSIC_FILE_DRUMS_NIGHTMOONGRAINS, aFadeTrackVolume * music->mPauseVolume);
        if (aPackedOrderMain != -1) {
            Sexy_AudiereMusicInterface_PlayMusic(music->mMusicInterface, music->mCurMusicFileDrums, aPackedOrderMain, 0);
        }
    }
}

void Music_StartBurst(Music *music) {
    if (music->mMusicBurstState == MusicBurstState::MUSIC_BURST_OFF) {
        music->mMusicBurstState = MusicBurstState::MUSIC_BURST_STARTING;
        music->mBurstStateCounter = 400;
    }
}

void Music::MusicUpdate() {
    if (mFadeOutCounter <= 0) {
        if (mNormalVolume != mPauseVolume) {
            mNormalVolume = mPauseVolume;
            Sexy_AudiereMusicInterface_SetSongVolume(mMusicInterface, mCurMusicFileMain, mPauseVolume);
        }
    } else {
        mFadeOutCounter--;
        if (mFadeOutCounter > 0) {
            float theVolume = TodAnimateCurveFloat(mFadeOutDuration, 0, mFadeOutCounter, 1.0, 0.0, TodCurves::Linear);
            Sexy_AudiereMusicInterface_SetSongVolume(mMusicInterface, mCurMusicFileMain, theVolume * mPauseVolume);
        } else {
            Music_StopAllMusic(this);
        }
    }
    UpdateMusicBurst();
    Board *board = mApp->mBoard;
    if ((board == nullptr || !board->mPaused) && mCurMusicFileMain != MusicFile::MUSIC_FILE_NONE) {
        Music_MusicResync(this);
    }
}

void Music_ResyncChannel(Music *music, MusicFile::MusicFile theFile1, MusicFile::MusicFile theFile2) {}

void Music2_Music2(Music2 *music) {
    // 选择使用哪一版本的音乐。xbox版是xm格式，有鼓点；TV版则是ogg格式，无鼓点。
    if (useXboxMusic) {
        return Music_Music(music);
    }
    return old_Music2_Music2(music);
}

void Music_MusicResync(Music *music) {
    if (music->mCurMusicFileMain != MusicFile::MUSIC_FILE_NONE) {
        if (music->mCurMusicFileDrums != MusicFile::MUSIC_FILE_NONE)
            Music_ResyncChannel(music, music->mCurMusicFileMain, music->mCurMusicFileDrums);
        if (music->mCurMusicFileHihats != MusicFile::MUSIC_FILE_NONE)
            Music_ResyncChannel(music, music->mCurMusicFileMain, music->mCurMusicFileHihats);
    }
}

void Music2_StopAllMusic(Music2 *music) {
    old_Music2_StopAllMusic(music);
}

void Music2_StartGameMusic(Music2 *music, bool start) {
    old_Music2_StartGameMusic(music, start);
}

void Music2_GameMusicPause(Music2 *music, bool pause) {
    old_Music2_GameMusicPause(music, pause);
}

void Music2_FadeOut(Music2 *music, int aFadeOutDuration) {
    old_Music2_FadeOut(music, aFadeOutDuration);
}
