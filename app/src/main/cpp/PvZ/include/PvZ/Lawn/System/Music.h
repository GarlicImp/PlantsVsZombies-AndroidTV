#ifndef PVZ_LAWN_MUSIC_H
#define PVZ_LAWN_MUSIC_H

class LawnApp;

enum MusicTune {
    MUSIC_TUNE_NONE = -1,
    MUSIC_TUNE_DAY_GRASSWALK = 1,				// 白天草地关卡
    MUSIC_TUNE_NIGHT_MOONGRAINS,				// 黑夜草地关卡
    MUSIC_TUNE_POOL_WATERYGRAVES,				// 白天泳池关卡
    MUSIC_TUNE_FOG_RIGORMORMIST,				// 黑夜泳池关卡
    MUSIC_TUNE_ROOF_GRAZETHEROOF,				// 屋顶关卡
    MUSIC_TUNE_CHOOSE_YOUR_SEEDS,				// 选卡界面/小游戏界面
    MUSIC_TUNE_TITLE_CRAZY_DAVE_MAIN_THEME,		// 主菜单
    MUSIC_TUNE_ZEN_GARDEN,						// 禅境花园
    MUSIC_TUNE_PUZZLE_CEREBRAWL,				// 解谜模式
    MUSIC_TUNE_MINIGAME_LOONBOON,				// 小游戏
    MUSIC_TUNE_CONVEYER,						// 传送带关卡
    MUSIC_TUNE_FINAL_BOSS_BRAINIAC_MANIAC,		// 僵王博士关卡
    MUSIC_TUNE_CREDITS_ZOMBIES_ON_YOUR_LAWN,	// MV
    NUM_MUSIC_TUNES
};

enum MusicFile {
    MUSIC_FILE_NONE = -1,
    MUSIC_FILE_MAIN_MUSIC = 1,
    MUSIC_FILE_DRUMS = 2,
    MUSIC_FILE_DRUMS_NIGHTMOONGRAINS = 3,
    MUSIC_FILE_HIHATS = 4,
    MUSIC_FILE_CREDITS_ZOMBIES_ON_YOUR_LAWN = 5,
    NUM_MUSIC_FILES = 6,
};

enum MusicBurstState {
    MUSIC_BURST_OFF = 0,
    MUSIC_BURST_STARTING = 1,
    MUSIC_BURST_ON = 2,
    MUSIC_BURST_FINISHING = 3,
};

enum MusicDrumsState {
    MUSIC_DRUMS_OFF = 0,
    MUSIC_DRUMS_ON_QUEUED = 1,
    MUSIC_DRUMS_ON = 2,
    MUSIC_DRUMS_OFF_QUEUED = 3,
    MUSIC_DRUMS_FADING = 4,
};

class Music { // 加载XBOX版xm格式音乐时用。优：音质好、有鼓点。缺：鼓点BUG多，xm格式难以修改
public:
    int* vTable;                                       // 0
    int unkMems[3];                                    // 1 ~ 3
    LawnApp* mApp;                                     // 4
    int* mMusicInterface;                              // 5
    MusicTune mCurMusicTune;                // 6
    MusicTune mLastMusicTune;               // 7
    MusicFile mCurMusicFileMain;            // 8
    MusicFile mCurMusicFileDrums;           // 9
    MusicFile mCurMusicFileHihats;          // 10
    int mBurstOverride;                                // 11
    int mBaseBPM;                                      // 12
    int mBaseModSpeed;                                 // 13
    MusicBurstState mMusicBurstState;                  // 14
    int mBurstStateCounter;                            // 15
    MusicDrumsState mMusicDrumsState;                  // 16
    int mQueuedDrumTrackPackedOrder;                   // 17
    int mDrumsStateCounter;                            // 18
    int mPauseOffset;                                  // 19
    int mPauseOffsetDrums;                             // 20
    bool mPaused;                                      // 84
    bool mMusicDisabled;                               // 85
    int mFadeOutCounter;                               // 22
    int mFadeOutDuration;                              // 23
    float mPauseVolume;                                // 24
    float mNormalVolume;                               // 25
    // 大小26个整数
public:
    void PlayMusic(MusicTune theMusicTune, int theOffset, int theDrumsOffset);
    void MusicUpdate();
    void UpdateMusicBurst();
};

class Music2 : public Music { // 加载TV版ogg格式音乐时用。无鼓点。

}; // 大小26个整数

inline void (*Music2_Delete)(Music2* music);

inline void (*Music_Music)(Music*);

inline void (*Sexy_AudiereMusicInterface_SetVolume)(int* interface, double theVolume);

inline void (*Sexy_AudiereMusicInterface_SetSongVolume)(int* interface, int theSongId, double theVolume);

inline void (*Sexy_AudiereMusicInterface_PlayMusic)(int* interface, int, int, bool noLoop);

inline void (*Music_StopAllMusic)(Music*);

inline int (*Music_GetMusicOrder)(Music*, MusicFile);

inline void (*Music_SetupMusicFileForTune)(Music*, MusicFile, MusicTune);

inline void (*Sexy_AudiereMusicInterface_StopMusic)(int*, int);

inline void (*Sexy_AudiereMusicInterface_SetChannelVolume)(int*, int, int, float);


inline void (*old_Music_StartGameMusic)(Music* music, bool a2);

inline void (*old_Music_UpdateMusicBurst)(Music* music);

inline void (*old_Music2_Music2)(Music2* music);

inline void (*old_Music2_StopAllMusic)(Music2* music);

inline void (*old_Music2_StartGameMusic)(Music2* music, bool start);

inline void (*old_Music2_GameMusicPause)(Music2* music, bool pause);

inline void (*old_Music2_FadeOut)(Music2* music, int aFadeOutDuration);


void Music2_StopAllMusic(Music2* music);

void Music2_StartGameMusic(Music2* music, bool start);

void Music2_GameMusicPause(Music2* music, bool pause);

void Music2_FadeOut(Music2* music, int aFadeOutDuration);

void Music2_Music2(Music2*);

void Music_MusicResync(Music*);

void Music_StartBurst(Music* music);

void Music_PlayFromOffset(Music*, MusicFile, int, double);

void Music_UpdateMusicBurst1(Music*);

void Music_UpdateMusicBurst2(Music*);

#endif // PVZ_LAWN_MUSIC_H
