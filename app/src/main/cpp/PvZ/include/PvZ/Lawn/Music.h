#ifndef PVZ_LAWN_MUSIC_H
#define PVZ_LAWN_MUSIC_H

#include "PvZ/Enums.h"

class Music { // 加载XBOX版xm格式音乐时用。优：音质好、有鼓点。缺：鼓点BUG多，xm格式难以修改
public:
    int *vTable;                                       // 0
    int unkMems[3];                                    // 1 ~ 3
    LawnApp *mApp;                                     // 4
    int *mMusicInterface;                              // 5
    MusicTune::MusicTune mCurMusicTune;                // 6
    MusicTune::MusicTune mLastMusicTune;               // 7
    MusicFile::MusicFile mCurMusicFileMain;            // 8
    MusicFile::MusicFile mCurMusicFileDrums;           // 9
    MusicFile::MusicFile mCurMusicFileHihats;          // 10
    int mBurstOverride;                                // 11
    int mBaseBPM;                                      // 12
    int mBaseModSpeed;                                 // 13
    MusicBurstState::MusicBurstState mMusicBurstState; // 14
    int mBurstStateCounter;                            // 15
    MusicDrumsState::MusicDrumsState mMusicDrumsState; // 16
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
    void PlayMusic(MusicTune::MusicTune theMusicTune, int theOffset, int theDrumsOffset);
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

inline int (*Music_GetMusicOrder)(Music*, MusicFile::MusicFile);

inline void (*Music_SetupMusicFileForTune)(Music*, MusicFile::MusicFile, MusicTune::MusicTune);

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

void Music_PlayFromOffset(Music*, MusicFile::MusicFile, int, double);

void Music_UpdateMusicBurst1(Music*);

void Music_UpdateMusicBurst2(Music*);

#endif // PVZ_LAWN_MUSIC_H
