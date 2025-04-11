#ifndef PVZ_ENUMS_H
#define PVZ_ENUMS_H

#include "MagicAddr.h"

#include <jni.h>

namespace SeedType {
enum SeedType { // 直接从WP复制过来的，怀疑其中有错误，因为TV有重型武器关卡，多了三个种子
    Peashooter = 0,
    Sunflower = 1,
    Cherrybomb = 2,
    Wallnut = 3,
    Potatomine = 4,
    Snowpea = 5,
    Chomper = 6,
    Repeater = 7,
    Puffshroom = 8,
    Sunshroom = 9,
    Fumeshroom = 10,
    Gravebuster = 11,
    Hypnoshroom = 12,
    Scaredyshroom = 13,
    Iceshroom = 14,
    Doomshroom = 15,
    Lilypad = 16,
    SEED_SQUASH = 17,
    Threepeater = 18,
    Tanglekelp = 19,
    Jalapeno = 20,
    Spikeweed = 21,
    Torchwood = 22,
    Tallnut = 23,
    Seashroom = 24,
    Plantern = 25,
    Cactus = 26,
    Blover = 27,
    Splitpea = 28,
    Starfruit = 29,
    Pumpkinshell = 30,
    Magnetshroom = 31,
    Cabbagepult = 32,
    Flowerpot = 33,
    Kernelpult = 34,
    InstantCoffee = 35,
    Garlic = 36,
    Umbrella = 37,
    Marigold = 38,
    Melonpult = 39,
    Gatlingpea = 40,
    Twinsunflower = 41,
    Gloomshroom = 42,
    Cattail = 43,
    Wintermelon = 44,
    GoldMagnet = 45,
    Spikerock = 46,
    Cobcannon = 47,
    Imitater = 48,
    SeedsInChooserCount = 49,
    ExplodeONut = 50,
    GiantWallnut = 51,
    Sprout = 52,
    Leftpeater = 53,
    NUM_SEED_TYPES = 54,
    BeghouledButtonShuffle = 55,
    BeghouledButtonCrater = 56,
    SlotMachineSun = 57,
    SlotMachineDiamond = 58,
    ZombiquariumSnorkel = 59,
    ZombiquariumTrophy = 60,
    ZombieTombsTone = 61,
    ZombieNormal = 62,
    ZombieTrashBin = 63,
    ZombieTrafficCone = 64,
    ZombiePolevaulter = 65,
    ZombiePail = 66,
    ZombieFlag = 67,
    ZombieNewsPaper = 68,
    ZombieScreenDoor = 69,
    ZombieFootball = 70,
    ZombieDancer = 71,
    Zomboni = 72,
    ZombieJackInTheBox = 73,
    ZombieDigger = 74,
    ZombiePogo = 75,
    ZombieBungee = 76,
    ZombieLadder = 77,
    ZombieCatapult = 78,
    ZombieGargantuar = 79,
    ZombieUnknown = 80,
    ZombieDuckyTube = 81,
    ZombieSnorkel = 82,
    ZombieDolphinRider = 83,
    ZombieImp = 84,
    ZombieBalloon = 85,
    None = -1
};
}

enum ProjectileType {
    PROJECTILE_PEA = 0,
    PROJECTILE_SNOWPEA = 1,
    PROJECTILE_CABBAGE = 2,
    PROJECTILE_MELON = 3,
    PROJECTILE_PUFF = 4,
    PROJECTILE_WINTERMELON = 5,
    PROJECTILE_FIREBALL = 6,
    PROJECTILE_STAR = 7,
    PROJECTILE_SPIKE = 8,
    PROJECTILE_BASKETBALL = 9,
    PROJECTILE_KERNEL = 10,
    PROJECTILE_COBBIG = 11,
    PROJECTILE_BUTTER = 12,
    PROJECTILE_ZOMBIE_PEA = 13,
    NUM_PROJECTILES
};

namespace ScaryPotType {
enum ScaryPotType { None = 0, Seed = 1, Zombie = 2, Sun = 3 };
}
namespace AdviceType {
enum AdviceType {
    None = -1,
    ClickOnSun,
    ClickedOnSun,
    ClickedOnCoin,
    SeedRefresh,
    CantAffordPlant,
    PlantGravebustersOnGraves,
    PlantLilypadOnWater,
    PlantTanglekelpOnWater,
    PlantSeashroomOnWater,
    PlantPotatoMineOnLily,
    PlantWrongArtType,
    PlantNeedPot,
    PlantNotOnGrave,
    PlantNotOnCrater,
    CantPlantThere,
    PlantNotOnWater,
    PlantingNeedsGround,
    BeghouledDragToMatch3,
    BeghouledMatch3,
    BeghouledMatch4,
    BeghouledSaveSun,
    BeghouledUseCrater1,
    BeghouledUseCrater2,
    PlantNotPassedLine,
    PlantOnlyOnRepeaters,
    PlantOnlyOnMelonpult,
    PlantOnlyOnSunflower,
    PlantOnlyOnSpikeweed,
    PlantOnlyOnKernelpult,
    PlantOnlyOnMagnetshroom,
    PlantOnlyOnFumeshroom,
    PlantOnlyOnLilypad,
    PlantNeedsRepeater,
    PlantNeedsMelonpult,
    PlantNeedsSunflower,
    PlantNeedsSpikeweed,
    PlantNeedsKernelpult,
    PlantNeedsMagnetshroom,
    PlantNeedsFumeshroom,
    PlantNeedsLilypad,
    SlotMachinePull,
    HugeWave,
    ShovelRefresh,
    PortalRelocating,
    SlotMachineCollectSun,
    DestroyPotsToFinisihLevel,
    UseShovelOnPots,
    AlmostThere,
    ZombiquariumClickTrophy,
    ZombiquariumCollectSun,
    ZombiquariumClickToFeed,
    ZombiquariumBuySnorkel,
    IZombiePlantsNotReal,
    IZombieNotPassedLine,
    IZombieLeftOfLine,
    SlotMachineSpinAgain,
    IZombieEatAllBrains,
    PeashooterDied,
    StinkySleeping,
    BeghouledNoMoves,
    PlantSunflower5,
    PlantingNeedSleeping,
    ClickToContinue,
    SurviveFlags,
    UnlockedMode,
    NeedWheelbarrow,
    AchievementEarned = 66,
    AdviceTypeCount
};
}

namespace MessageStyle {
enum MessageStyle {
    Off = 0,
    TutorialLevel1 = 1,
    TutorialLevel1Stay = 2,
    TutorialLevel2 = 3,
    TutorialLater = 4,
    TutorialLaterStay = 5,
    HintLong = 6,
    HintFast = 7,
    HintStay = 8,
    HintTallFast = 9,
    HintTallUnlockmessage = 10,
    HintTallLong = 11,
    BigMiddle = 12,
    BigMiddleFast = 13,
    HouseName = 14,
    HugeWave = 15,
    SlotMachine = 16,
    ZenGardenLong = 17,
    Achievement = 3
};
}

namespace ParticleEffect {
enum ParticleEffect {
    None = -1,
    Melonsplash = 0,
    Wintermelon = 1,
    Fumecloud,
    Popcornsplash = 3,
    Powie = 4,
    Jackexplode,
    ZombieHead,
    ZombieArm,
    ZombieTrafficCone,
    ZombiePail,
    ZombieHelmet,
    ZombieFlag,
    ZombieDoor,
    ZombieTrashCan = 13,
    ZombieNewspaper = 14,
    ZombieHeadlight,
    Pow,
    ZombiePogo,
    ZombieNewspaperHead,
    ZombieBalloonHead,
    SodRoll,
    GraveStoneRise,
    Planting = 22,
    PlantingPool = 23,
    ZombieRise,
    GraveBuster,
    GraveBusterDie,
    PoolSplash,
    IceSparkle,
    SeedPacket = 29,
    TallNutBlock,
    Doom,
    DiggerRise,
    DiggerTunnel,
    DancerRise,
    PoolSparkly = 35,
    WallnutEatSmall,
    WallnutEatLarge,
    PeaSplat = 38,
    ButterSplat = 39,
    CabbageSplat = 40,
    PuffSplat = 41,
    StarSplat = 42,
    IceTrap,
    SnowpeaSplat = 44,
    SnowpeaPuff,
    SnowpeaTrail,
    LanternShine,
    SeedPacketPickup,
    PotatoMine,
    PotatoMineRise,
    PuffshroomTrail,
    PuffshroomMuzzle,
    SeedPacketFlash = 53,
    WhackAZombieRise,
    ZombieLadder,
    UmbrellaReflect,
    SeedPacketPick,
    IceTrapZombie,
    IceTrapRelease,
    ZamboniSmoke,
    Gloomcloud,
    ZombiePogoHead,
    ZamboniTire,
    ZamboniExplosion,
    ZamboniExplosion2,
    CatapultExplosion,
    MowerCloud,
    BossIceBall,
    Blastmark = 69,
    CoinPickupArrow = 70,
    PresentPickup,
    ImitaterMorph,
    MoweredZombieHead,
    MoweredZombieArm,
    ZombieHeadPool,
    ZombieBossFireball,
    FireballDeath,
    PARTICLE_ICEBALL_DEATH,
    PARTICLE_ICEBALL_TRAIL,
    FireballTrail,
    BossExplosion,
    ScreenFlash,
    TrophySparkle = 83,
    PortalCircle,
    PortalSquare,
    PottedPlantGlow,
    PottedWaterPlantGlow,
    PottedZenGlow,
    MindControl,
    VaseShatter,
    VaseShatterLeaf,
    VaseShatterZombie,
    AwardPickupArrow = 93,
    ZombieSeaweed,
    ZombieMustache,
    ZombieFutureGlasses,
    Pinata = 97,
    DustSquash,
    DustFoot,
    Daisy = 100,
    Starburst,
    UpsellArrow,
    ParticleCount
};
}


namespace ProjectileMotion {
enum ProjectileMotion { Straight = 0, Lobbed = 1, Threepeater = 2, Bee = 3, BeeBackwards = 4, Puff = 5, Backwards = 6, Star = 7, FloatOver = 8, Homing = 9 };
}

namespace GameObjectType {
enum GameObjectType {
    None = 0,
    Plant = 1,
    Projectile = 2,
    Coin = 3,
    Seedpacket = 4,
    Shovel = 5,
    WateringCan = 6,
    Fertilizer = 7,
    BugSpray = 8,
    Phonograph = 9,
    Chocolate = 10,
    Glove = 11,
    MoneySign = 12,
    Wheelbarrow = 13,
    TreeFood = 14,
    MushRoomGarden = 15,
    QuariumGarden = 16,
    ZenGarden = 17,
    TreeOfWisdomGarden = 18,
    SlotMachineHandle = 22,
    ScaryPot = 23,
    Stinky = 24,
    SeedBankBlank = 49,
    Butter = 50,
};
}

namespace CursorType {
enum CursorType {
    Normal = 0,
    PlantFromBank = 1,
    PlantFromUsableCoin = 2,
    PlantFromGlove = 3,
    PlantFromDuplicator = 4,
    PlantFromWheelBarrow = 5,
    Shovel = 6,
    Hammer = 7,
    CobcannonTarget = 8,
    WateringCan = 9,
    Fertilizer = 10,
    BugSpray = 11,
    Phonograph = 12,
    Chocolate = 13,
    Glove = 14,
    MoneySign = 15,
    Wheelbarrow = 16,
    TreeFood = 17,
    MushRoomGarden = 18,
    QuariumGarden = 19,
    ZenGarden = 20,
    TreeOfWisdomGarden = 21
};
}
namespace TouchState {
enum TouchState {
    None = 0,
    SeedBank = 1,
    ShovelRect = 2,
    ButterRect = 3,
    Board = 4,
    BoardMovedFromSeedBank = 5,
    BoardMovedFromShovelRect = 6,
    BoardMovedFromButterRect = 7,
    ValidCobCannon = 8,
    UsefulSeedPacket = 9,
    Unused = 10,
    HeavyWeapon = 11,
    PickingSomething = 12,
    ZenGardenTools = 13,
    BoardMovedFromZenGardenTools = 14,
    ValidCobCannonSecond = 15,
};
}

namespace TouchPlayerIndex {
enum TouchPlayerIndex { None = -1, Player1 = 0, Player2 = 1 };
}

namespace CrazyDaveState {
enum CrazyDaveState { Off = 0, Entering = 1, Leaving = 2, Idling = 3, Talking = 4, HandingTalking = 5, HandingIdling = 6 };
}
namespace BoardResult {
enum BoardResult { None = 0, Won = 1, Lost = 2, Restart = 3, Quit = 4, QuitApp = 5, Cheat = 6, VSPlantWon = 7, VSZombieWon = 8 };
}

namespace GameMode {
enum GameMode {
    Adventure = 0,
    AdventureHide = 1,
    SurvivalNormalStage1 = 2,
    SurvivalNormalStage2 = 3,
    SurvivalNormalStage3 = 4,
    SurvivalNormalStage4 = 5,
    SurvivalNormalStage5 = 6,
    SurvivalHardStage1 = 7,
    SurvivalHardStage2 = 8,
    SurvivalHardStage3 = 9,
    SurvivalHardStage4 = 10,
    SurvivalHardStage5 = 11,
    SurvivalEndlessStage1 = 12,
    SurvivalEndlessStage2 = 13,
    SurvivalEndlessStage3 = 14,
    SurvivalEndlessStage4 = 15,
    SurvivalEndlessStage5 = 16,
    ChallengeWarAndPeas = 17,
    ChallengeWallnutBowling = 18,
    ChallengeSlotMachine = 19,
    ChallengeHeavyWeapon = 20,
    ChallengeBeghouled = 21,
    ChallengeInvisighoul = 22,
    ChallengeSeeingStars = 23,
    ChallengeZombiquarium = 24,
    ChallengeBeghouledTwist = 25,
    ChallengeLittleTrouble = 26,
    ChallengePortalCombat = 27,
    ChallengeColumn = 28,
    ChallengeBobsledBonanza = 29,
    ChallengeSpeed = 30,
    ChallengeWhackAZombie = 31,
    ChallengeLastStand = 32,
    ChallengeWarAndPeas2 = 33,
    ChallengeWallnutBowling2 = 34,
    ChallengePogoParty = 35,
    ChallengeFinalBoss = 36,
    ChallengeArtChallenge1 = 37,
    ChallengeSunnyDay = 38,
    ChallengeResodded = 39,
    ChallengeBigTime = 40,
    ChallengeArtChallenge2 = 41,
    ChallengeAirRaid = 42,
    ChallengeIce = 43,
    GAMEMODE_CHALLENGE_ZEN_GARDEN = 44,
    ChallengeHighGravity = 45,
    ChallengeGraveDanger = 46,
    ChallengeShovel = 47,
    ChallengeStormyNight = 48,
    ChallengeBungeeBlitz = 49,
    ChallengeSquirrel = 50,
    GAMEMODE_TREE_OF_WISDOM = 51,
    ScaryPotter1 = 52,
    PuzzleIZombie1 = 53,
    ScaryPotter2 = 54,
    PuzzleIZombie2 = 55,
    ScaryPotter3 = 56,
    PuzzleIZombie3 = 57,
    ScaryPotter4 = 58,
    PuzzleIZombie4 = 59,
    ScaryPotter5 = 60,
    PuzzleIZombie5 = 61,
    ScaryPotter6 = 62,
    PuzzleIZombie6 = 63,
    ScaryPotter7 = 64,
    PuzzleIZombie7 = 65,
    ScaryPotter8 = 66,
    PuzzleIZombie8 = 67,
    ScaryPotter9 = 68,
    PuzzleIZombie9 = 69,
    ScaryPotterEndless = 70,
    PuzzleIZombieEndless = 71,
    Upsell = 72,
    Intro = 73,
    MultiPlayer = 74,
    TwoPlayerVSHide = 75,
    TwoPlayerVS = 76,
    TwoPlayerCoopDay = 79,
    TwoPlayerCoopNight = 80,
    TwoPlayerCoopPool = 81,
    TwoPlayerCoopRoof = 82,
    TwoPlayerCoopBowling = 83,
    TwoPlayerCoopDayHard = 84,
    TwoPlayerCoopNightHard = 85,
    TwoPlayerCoopPoolHard = 86,
    TwoPlayerCoopRoofHard = 87,
    TwoPlayerCoopBoss = 88,
    TwoPlayerCoopEndless = 89,
    ChallengeRainingSeeds = 90,
    ChallengeButteredPopcorn = 91,
    ChallengePoolParty = 92

};
}


namespace StoreItem {
enum StoreItem {
    STORE_ITEM_PLANT_GATLINGPEA = 0,
    STORE_ITEM_PLANT_TWINSUNFLOWER = 1,
    STORE_ITEM_PLANT_GLOOMSHROOM = 2,
    STORE_ITEM_PLANT_CATTAIL = 3,
    STORE_ITEM_PLANT_WINTERMELON = 4,
    STORE_ITEM_PLANT_GOLD_MAGNET = 5,
    STORE_ITEM_PLANT_SPIKEROCK = 6,
    STORE_ITEM_PLANT_COBCANNON = 7,
    STORE_ITEM_PLANT_IMITATER = 8,
    STORE_ITEM_BONUS_LAWN_MOWER,
    STORE_ITEM_POTTED_MARIGOLD_1,
    STORE_ITEM_POTTED_MARIGOLD_2,
    STORE_ITEM_POTTED_MARIGOLD_3,
    STORE_ITEM_GOLD_WATERINGCAN = 13,
    STORE_ITEM_FERTILIZER = 14,
    STORE_ITEM_BUG_SPRAY = 15,
    STORE_ITEM_PHONOGRAPH = 16,
    STORE_ITEM_GARDENING_GLOVE = 17,
    STORE_ITEM_MUSHROOM_GARDEN = 18,
    STORE_ITEM_WHEEL_BARROW = 19,
    STORE_ITEM_STINKY_THE_SNAIL = 20,
    STORE_ITEM_PACKET_UPGRADE = 21,
    STORE_ITEM_POOL_CLEANER = 22,
    STORE_ITEM_ROOF_CLEANER = 23,
    STORE_ITEM_RAKE = 24,
    STORE_ITEM_AQUARIUM_GARDEN = 25,
    STORE_ITEM_CHOCOLATE = 26,
    STORE_ITEM_TREE_OF_WISDOM = 27,
    STORE_ITEM_TREE_FOOD = 28,
    STORE_ITEM_FIRSTAID = 29,
    STORE_ITEM_PVZ_ICON = 30,
    STORE_ITEM_BLUEPRINT_BLING = 31,
    STORE_ITEM_BLUEPRINT_SCARY = 32,
    STORE_ITEM_BLUEPRINT_TRAILER = 33,
    STORE_ITEM_BLUEPRINT_FUTURE = 34,
    STORE_ITEM_BLUEPRINT_CLOWN = 35,
    STORE_ITEM_BLUEPRINT_CHANGE = 36,
    STORE_ITEM_INVALID = -1
};
}

namespace AchievementId {
enum AchievementId {
    ACHIEVEMENT_HOME_SECURITY = 0,    // 完成冒险模式
    ACHIEVEMENT_MORTICULTURALIST = 1, // 收集全部49种植物
    ACHIEVEMENT_IMMORTAL = 2,         // 生存泳池无尽达到40波
    ACHIEVEMENT_SOILPLANTS = 3,       // 在一个关卡内种植10个豌豆射手
    ACHIEVEMENT_CLOSESHAVE = 4,       // 用完全部小推车过一关
    ACHIEVEMENT_CHOMP = 5,            // 只使用大嘴花、坚果墙、向日葵过一关
    ACHIEVEMENT_VERSUS = 6,           // 对战模式获得5连胜
    ACHIEVEMENT_GARG = 7,             // 打败巨人僵尸
    ACHIEVEMENT_COOP = 8,             // 通关结盟坚果保龄球关卡
    ACHIEVEMENT_SHOP = 9,             // 在戴夫商店消费25000元
    ACHIEVEMENT_EXPLODONATOR = 10,    // 使用一个樱桃炸弹消灭10只僵尸
    ACHIEVEMENT_TREE = 11,            // 让智慧树长到100英尺高
    MAX_ACHIEVEMENTS
};
}

enum MainMenuButtonId {
    START_ADVENTURE_BUTTON = 0,
    ADVENTURE_BUTTON = 1,
    MORE_WAYS_BUTTON = 2,
    HOUSE_BUTTON = 3,
    ACHIEVEMENTS_BUTTON = 4,
    HELP_AND_OPTIONS_BUTTON = 5,
    UNLOCK_BUTTON = 6,
    RETURN_TO_ARCADE_BUTTON = 7,
    MORE_BUTTON = 8,
    BACK_STONE_BUTTON = 9,
    VS_BUTTON = 10,
    VS_COOP_BUTTON = 11,
    MINI_GAMES_BUTTON = 12,
    SURVIVAL_BUTTON = 13,
    PUZZLE_BUTTON = 14,
    BACK_POT_BUTTON = 15,
    STORE_BUTTON = 16,
    ZEN_BUTTON = 17,
    ALMANAC_BUTTON = 18,
    MAIL_BUTTON = 19,
    HELP_BAR = 20,


    ACHIEVEMENTS_BACK_BUTTON = 21
};


namespace SeedChooserTouchState {
enum SeedChooserTouchState { ViewLawnButton, SeedChooser, StoreButton, StartButton, AlmanacButton, None };
}

namespace StoreScreenTouchState {
enum StoreScreenTouchState { Prev, Next, Back, None };
}
namespace DebugTextMode {
enum DebugTextMode { None = 0, ZombieSpawn = 1, Music = 2, Memory = 3, Collision = 4 };
}
namespace DrawStringJustification {
enum DrawStringJustification { Left = 0, Right = 1, Center = 2, LeftVerticalMiddle = 3, RightVerticalMiddle = 4, CenterVerticalMiddle = 5 };
}
namespace TutorialState {
enum TutorialState {
    Off,
    Level1PickUpPeashooter,
    Level1PlantPeashooter,
    Level1RefreshPeashooter,
    Level1Completed,
    Level2PickUpSunflower,
    Level2PlantSunflower,
    Level2RefreshSunflower,
    Level2Completed,
    MoresunPickUpSunflower,
    MoresunPlantSunflower,
    MoresunRefreshSunflower,
    MoresunCompleted,
    SlotMachinePull,
    SlotMachineCompleted,
    ShovelPickup,
    ShovelDig,
    ShovelKeepDigging,
    ShovelCompleted,
    ZombiquariumBuySnorkel,
    ZombiquariumBoughtSnorkel,
    ZombiquariumClickTrophy,
    ZenGardenPickupWater = 22,
    ZenGardenWaterPlant = 23,
    ZenGardenKeepWatering = 24,
    ZenGardenVisitStore = 25,
    ZenGardenFertilizePlants = 26,
    ZenGardenCompleted = 27,
    WhackAZombieBeforePickSeed,
    WhackAZombiePickSeed,
    WhackAZombieCompleted
};
}

namespace BackgroundType {
enum BackgroundType { Num1Day = 0, Num2Night = 1, Num3Pool = 2, Num4Fog = 3, Num5Roof = 4, Num6Boss = 5, MushroomGarden = 6, Greenhouse = 7, Zombiquarium = 8, TreeOfWisdom = 9 };
}

namespace PlantRowType {
enum PlantRowType { Dirt = 0, Normal = 1, Pool = 2, HighGround = 3 };
}
namespace GridSquareType {
enum GridSquareType { None, Grass, Dirt, Pool, HighGround };
}
namespace ParticleSystemID {
enum ParticleSystemID { Null };
}


namespace PlantingReason {
enum PlantingReason {
    Ok = 0,
    NotHere = 1,
    OnlyOnGraves = 2,
    OnlyInPool = 3,
    OnlyOnGround = 4,
    NeedsPot = 5,
    NotOnArt = 6,
    NotPassedLine = 7,
    NeedsUpgrade = 8,
    NotOnGrave = 9,
    NotOnCrater = 10,
    NotOnWater = 11,
    NeedsGround = 12,
    NeedsSleeping = 13,
    VSModeNotPassedLine = 15,
};
}


enum ZombieType {
    ZOMBIE_INVALID = -1,
    ZOMBIE_NORMAL = 0,
    ZOMBIE_FLAG = 1,
    ZOMBIE_TRAFFIC_CONE = 2,
    ZOMBIE_POLEVAULTER = 3,
    ZOMBIE_PAIL = 4,
    ZOMBIE_NEWSPAPER = 5,
    ZOMBIE_DOOR = 6,
    ZOMBIE_FOOTBALL = 7,
    ZOMBIE_DANCER = 8,
    ZOMBIE_BACKUP_DANCER = 9,
    ZOMBIE_DUCKY_TUBE = 10,
    ZOMBIE_SNORKEL = 11,
    ZOMBIE_ZAMBONI = 12,
    ZOMBIE_BOBSLED = 13,
    ZOMBIE_DOLPHIN_RIDER = 14,
    ZOMBIE_JACK_IN_THE_BOX = 15,
    ZOMBIE_BALLOON = 16,
    ZOMBIE_DIGGER = 17,
    ZOMBIE_POGO = 18,
    ZOMBIE_YETI = 19,
    ZOMBIE_BUNGEE = 20,
    ZOMBIE_LADDER = 21,
    ZOMBIE_CATAPULT = 22,
    ZOMBIE_GARGANTUAR = 23,
    ZOMBIE_IMP = 24,
    ZOMBIE_BOSS = 25,
    ZOMBIE_TRASH_BIN = 26,
    ZOMBIE_PEA_HEAD = 27,
    ZOMBIE_WALLNUT_HEAD = 28,
    ZOMBIE_JALAPENO_HEAD = 29,
    ZOMBIE_GATLING_HEAD = 30,
    ZOMBIE_SQUASH_HEAD = 31,
    ZOMBIE_TALLNUT_HEAD = 32,
    ZOMBIE_REDEYE_GARGANTUAR = 33,
    NUM_ZOMBIE_TYPES = 34,
    ZOMBIE_CACHED_POLEVAULTER_WITH_POLE = 35,
    NUM_CACHED_ZOMBIE_TYPES = 36
};

namespace ChosenSeedState {
enum ChosenSeedState { SEED_FLYING_TO_BANK = 0, SEED_IN_BANK = 1, SEED_FLYING_TO_CHOOSER = 2, SEED_IN_CHOOSER = 3, SEED_PACKET_HIDDEN = 4 };
}


namespace FoleyType {
enum FoleyType {
    Splat = 1,
    Throw = 3,
    Plant = 7,
    UseShovel = 8,
    Brains = 12,
    Brains2 = 13,
    Jackinthebox = 14,
    ArtChallenge = 15,
    Zamboni = 16,
    Thunder = 17,
    Frozen = 18,
    Zombiesplash = 19,
    Bowlingimpact = 20,
    Squish = 21,
    TirePop = 22,
    Explosion = 23,
    Slurp = 24,
    LimbsPop = 25,
    PogoZombie = 26,
    SnowPeaSparkles = 27,
    ZombieFalling = 28,
    Puff = 29,
    Fume = 30,
    Coin = 31,
    KernelSplat = 32,
    Digger = 33,
    JackSurprise = 34,
    VaseBreaking = 35,
    PoolCleaner = 36,
    Basketball = 37,
    Ignite = 38,
    Firepea = 39,
    Thump = 40,
    SquashHmm = 41,
    Magnetshroom = 42,
    Butter = 43,
    BungeeScream = 44,
    BossExplosionSmall = 45,
    ShieldHit = 46,
    Swing = 47,
    Bonk = 48,
    Rain = 49,
    DolphinBeforeJumping = 50,
    DolphinAppears = 51,
    PlantWater = 52,
    ZombieEnteringWater = 53,
    Gravebusterchomp = 54,
    Cherrybomb = 55,
    JalapenoIgnite = 56,
    ReverseExplosion = 57,
    PlasticHit = 58,
    Winmusic = 59,
    Ballooninflate = 60,
    Bigchomp = 61,
    Melonimpact = 62,
    Plantgrow = 63,
    Shoop = 64,
    Juicy = 65,
    NewspaperRarrgh = 66,
    NewspaperRip = 67,
    Floop = 68,
    Coffee = 69,
    Lowgroan = 70,
    Prize = 71,
    Yuck = 72,
    Umbrella = 73,
    Grassstep = 74,
    Shovel = 75,
    Coblaunch = 76,
    Watering = 77,
    Polevault = 78,
    GravestoneRumble = 79,
    DirtRise = 80,
    Fertilizer = 81,
    Portal = 82,
    Wakeup = 83,
    Bugspray = 84,
    Scream = 85,
    Paper = 86,
    Moneyfalls = 87,
    Imp = 88,
    HydraulicShort = 89,
    Hydraulic = 90,
    Gargantudeath = 91,
    Ceramic = 92,
    Bossboulderattack = 93,
    Chime = 94,
    Crazydaveshort = 95,
    Crazydavelong = 96,
    Crazydaveextralong = 97,
    Crazydavecrazy = 98,
    Phonograph = 99,
    Dancer = 100,
    Finalfanfare = 101,
    Crazydavescream = 102,
    Crazydavescream2 = 103,
    FoleyCount = 104,
    MenuLeft = 105,
    MenuCenter = 106,
    MenuRight = 107
};
}


namespace ShieldType {
enum ShieldType { None = 0, Door = 1, Newspaper = 2, Ladder = 3, TrashBin = 4 };
}

namespace HelmType {
enum HelmType { None = 0, TrafficCone = 1, Pail = 2, Football = 3, Digger = 4, Redeyes = 5, Headband = 6, Bobsled = 7, Wallnut = 8, Tallnut = 9 };
}


namespace FilterEffectType {
enum FilterEffectType { None = -1, WashedOut = 0, LessWashedOut = 1, White = 2, Custom = 3, FilterEffectCount };
}

namespace DrawVariation {
enum DrawVariation {
    Normal = 0,
    Imitater = 1,
    MarigoldWhite,
    MarigoldMagenta,
    MarigoldOrange,
    MarigoldPink,
    MarigoldLightBlue,
    MarigoldRed,
    MarigoldBlue,
    MarigoldViolet,
    MarigoldLavender,
    MarigoldYellow,
    MarigoldLightGreen,
    ZenGarden = 13,
    ZenGardenWater = 14,
    SproutNoFlower = 15,
    ImitaterLess = 16,
    Aquarium,
    Bigidle
};
}

namespace ZombiePhase {
enum ZombiePhase {
    ZombieNormal,
    ZombieDying,
    ZombieBurned,
    ZombieMowered,
    BungeeDiving,
    BungeeDivingScreaming,
    BungeeAtBottom,
    BungeeGrabbing,
    BungeeRising,
    BungeeHitOuchy,
    BungeeCutscene,
    PolevaulterPreVault,
    PolevaulterInVault,
    PolevaulterPostVault,
    RisingFromGrave = 14,
    JackInTheBoxRunning,
    JackInTheBoxPopping,
    BobsledSliding,
    BobsledBoarding,
    BobsledCrashing,
    PogoBouncing,
    PogoHighBounce1,
    PogoHighBounce2,
    PogoHighBounce3,
    PogoHighBounce4,
    PogoHighBounce5,
    PogoHighBounce6,
    PogoForwardBounce2,
    PogoForwardBounce7,
    NewspaperReading,
    NewspaperMaddening,
    NewspaperMad,
    DiggerTunneling,
    DiggerRising,
    DiggerTunnelingPauseWithoutAxe,
    DiggerRiseWithoutAxe,
    DiggerStunned,
    DiggerWalking,
    DiggerWalkingWithoutAxe = 38,
    DiggerCutscene,
    DancerDancingIn = 40,
    DancerSnappingFingers,
    DancerSnappingFingersWithLight,
    DancerSnappingFingersHold,
    DancerDancingLeft,
    DancerWalkToRaise,
    DancerRaiseLeft1,
    DancerRaiseRight1,
    DancerRaiseLeft2,
    DancerRaiseRight2,
    DancerRising,
    DolphinWalking,
    DolphinIntoPool,
    DolphinRiding,
    DolphinInJump,
    DolphinWalkingInPool = 55,
    DolphinWalkingWithoutDolphin,
    SnorkelWalking,
    SnorkelIntoPool,
    SnorkelWalkingInPool = 59,
    SnorkelUpToEat,
    SnorkelEatingInPool,
    SnorkelDownFromEat,
    ZombiquariumAccel,
    ZombiquariumDrift,
    ZombiquariumBackAndForth,
    ZombiquariumBite,
    CatapultLaunching,
    CatapultReloading,
    GargantuarThrowing,
    GargantuarSmashing,
    ImpGettingThrown,
    ImpLanding,
    BalloonFlying,
    BalloonPopping,
    BalloonWalking,
    LadderCarrying,
    LadderPlacing,
    BossEnter,
    BossIdle,
    BossSpawning = 80,
    BossStomping,
    BossBungeesEnter,
    BossBungeesDrop,
    BossBungeesLeave = 84,
    BossDropRv,
    BossHeadEnter,
    BossHeadIdleBeforeSpit,
    BossHeadIdleAfterSpit,
    BossHeadSpit,
    BossHeadLeave,
    YetiRunning,
    SquashPreLaunch,
    SquashRising,
    SquashFalling,
    SquashDoneFalling
};
}

namespace TopPlant {
enum TopPlant { EatingOrder = 0, DiggingOrder = 1, BungeeOrder = 2, CatapultOrder = 3, ZenToolOrder = 4, Any = 5, OnlyNormalPosition = 6, OnlyFlying = 7, OnlyPumpkin = 8, OnlyUnderPlant = 9 };
}

namespace ZombieHeight {
enum ZombieHeight { ZombieNormal = 0, InToPool, OutOfPool, DraggedUnder, UpToHighGround, DownOffHighGround, UpLadder = 6, Falling, InToChimney, GettingBungeeDropped, Zombiquarium };
}


namespace Dialogs {
enum Dialogs {
    DIALOG_NEW_GAME,
    DIALOG_OPTIONS,
    DIALOG_NEWOPTIONS = 2,
    DIALOG_HELPOPTIONS = 3,
    DIALOG_SETTINGS = 4,
    DIALOG_ALMANAC = 5,
    DIALOG_STORE = 6,
    DIALOG_PREGAME_NAG,
    DIALOG_LOAD_GAME,
    DIALOG_CONFIRM_UPDATE_CHECK,
    DIALOG_CHECKING_UPDATES,
    DIALOG_REGISTER_ERROR,
    DIALOG_COLORDEPTH_EXP,
    DIALOG_OPENURL_WAIT,
    DIALOG_OPENURL_FAIL,
    DIALOG_CONFIRM_QUIT = 13,
    DIALOG_HIGH_SCORES,
    DIALOG_NAG,
    DIALOG_INFO,
    DIALOG_GAME_OVER = 16,
    DIALOG_LEVEL_COMPLETE,
    DIALOG_PAUSED = 20,
    DIALOG_NO_MORE_MONEY,
    DIALOG_BONUS,
    DIALOG_CONFIRM_BACK_TO_MAIN = 23,
    DIALOG_CONFIRM_IN_GAME_RESTART = 24,
    DIALOG_THANKS_FOR_REGISTERING,
    DIALOG_NOT_ENOUGH_MONEY = 26,
    DIALOG_UPGRADED = 27,
    DIALOG_NO_UPGRADE,
    DIALOG_CHOOSER_WARNING = 29,
    DIALOG_USERDIALOG,
    DIALOG_CREATEUSER,
    DIALOG_CONFIRMDELETEUSER,
    DIALOG_RENAMEUSER,
    DIALOG_CREATEUSERERROR,
    DIALOG_RENAMEUSERERROR,
    DIALOG_CHEAT = 36,
    DIALOG_CHEATCODE = 37,
    DIALOG_CHEATERROR,
    DIALOG_CONTINUE = 39,
    DIALOG_GETREADY,
    DIALOG_RESTARTCONFIRM = 41,
    DIALOG_CONFIRMPURCHASE,
    DIALOG_CONFIRMSELL,
    DIALOG_TIMESUP,
    DIALOG_VIRTUALHELP,
    DIALOG_JUMPAHEAD,
    DIALOG_CRAZY_DAVE,
    DIALOG_STORE_PURCHASE = 48,
    DIALOG_VISIT_TREE_OF_WISDOM = 49,
    DIALOG_ZEN_SELL = 50,
    DIALOG_MESSAGE = 51,
    DIALOG_IMITATER = 52,
    DIALOG_PURCHASE_PACKET_SLOT = 53,
    DIALOG_PROFILE_CHANGED = 54,
    DIALOG_WAITING_FOR_LEADERBOARD = 56,
    DIALOG_MAIL = 60,
    DIALOG_RETRY_LEADERBOARD = 61,
    DIALOG_RETRY_ACHIEVEMENTS = 62,
    DIALOG_HANDLE_OLDGAMEFILE = 63,
    DIALOG_HANDLE_NODEVICE = 64,
    DIALOG_HANDLE_INVALID_LEVEL = 65,
    DIALOG_PROFILE_LOAD_ERROR = 66,
    DIALOG_PROFILE_SAVE_ERROR = 67,
    DIALOG_CONTENT_LOADING = 68,
    DIALOG_ABOUT,
    RESTART_WARNING,
    DIALOG_UPSELL,
    DIALOG_ACHIEVEMENT_LOCKED,
    DIALOG_UPDATE_NOW,
    DIALOG_MORE_GAMES,
    DIALOG_SKIP_TUTORIAL,
    DIALOG_LEADERBOARD,
    NUM_DIALOGS
};
}

namespace HouseType {
enum HouseType {
    Invalid = -1,
    BLUEPRINT_BLING = 0,
    BLUEPRINT_SCARY = 1,
    BLUEPRINT_TRAILER = 2,
    BLUEPRINT_FUTURE = 3,
    BLUEPRINT_CLOWN = 4,
};
}

namespace MusicTune {
enum MusicTune {
    None = -1,
    DayGrasswalk = 1,
    NightMoongrains = 2,
    PoolWaterygraves = 3,
    FogRigormormist = 4,
    RoofGrazetheroof = 5,
    ChooseYourSeeds = 6,
    TitleCrazyDaveMainTheme = 7,
    ZenGarden = 8,
    PuzzleCerebrawl = 9,
    MinigameLoonboon = 10,
    Conveyer = 11,
    FinalBossBrainiacManiac = 12,
    ZombiesOnYourLawn = 13,
    MusicTuneCount = 14
};
}

namespace MusicFile {
enum MusicFile {
    MUSIC_FILE_NONE = -1,
    MUSIC_FILE_MAIN_MUSIC = 1,
    MUSIC_FILE_DRUMS = 2,
    MUSIC_FILE_DRUMS_NIGHTMOONGRAINS = 3,
    MUSIC_FILE_HIHATS = 4,
    MUSIC_FILE_CREDITS_ZOMBIES_ON_YOUR_LAWN = 5,
    NUM_MUSIC_FILES = 6,
};
}
namespace MusicBurstState {
enum MusicBurstState {
    MUSIC_BURST_OFF = 0,
    MUSIC_BURST_STARTING = 1,
    MUSIC_BURST_ON = 2,
    MUSIC_BURST_FINISHING = 3,
};
}
namespace MusicDrumsState {
enum MusicDrumsState {
    MUSIC_DRUMS_OFF = 0,
    MUSIC_DRUMS_ON_QUEUED = 1,
    MUSIC_DRUMS_ON = 2,
    MUSIC_DRUMS_OFF_QUEUED = 3,
    MUSIC_DRUMS_FADING = 4,
};
}

namespace ResType {
enum ResType { ResType_Image, ResType_Sound, ResType_Font, ResType_Music, ResType_Reanim, ResType_Particle, ResType_Trail };
}

namespace GridItemState {
enum GridItemState {
    Normal,
    GravestoneSpecial,
    PortalClosed,
    ScaryPotQuestion,
    ScaryPotLeaf,
    ScaryPotZombie,
    SquirrelWaiting,
    SquirrelPeeking = 7,
    SquirrelRunningUp = 8,
    SquirrelRunningDown = 9,
    SquirrelRunningLeft = 10,
    SquirrelRunningRight = 11,
    SquirrelCaught,
    SquirrelZombie,
    ZenToolWateringCan,
    ZenToolFertilizer,
    ZenToolBugSpray,
    ZenToolPhonograph,
    ZenToolGoldWateringCan,
    StinkyWalkingLeft,
    StinkyTurningLeft,
    StinkyWalkingRight,
    StinkyTurningRight,
    StinkySleeping,
    StinkyFallingAsleep,
    StinkyWakingUp,
    RakeAttracting,
    RakeWaiting,
    RakeTriggered,
    BrainSquished
};
}
namespace GridItemType {
enum GridItemType { None = 0, Gravestone = 1, Crater, Ladder = 3, PortalCircle, PortalSquare, Brain, ScaryPot, Squirrel, ZenTool, Stinky, Rake, IzombieBrain, VSTargetZombie = 14 };
}

namespace ChallengePage {
enum ChallengePage { CHALLENGE_PAGE_SURVIVAL = 0, CHALLENGE_PAGE_CHALLENGE = 1, CHALLENGE_PAGE_LIMBO = 2, CHALLENGE_PAGE_COOP = 3, CHALLENGE_PAGE_PUZZLE = 4, MAX_CHALLANGE_PAGES = 5 };
}
namespace UnlockingState {
enum UnlockingState { Off, Shaking, Fading };
}

namespace CoinMotion {
enum CoinMotion { FromSky = 0, FromSkySlow = 1, FromPlant = 2, Coin = 3, LawnmowerCoin = 4, FromPresent = 5, FromBoss = 6, NearCursor = 7, FromVSWon = 8, FromGrave = 9 };
}

namespace CoinType {
enum CoinType {
    None = 0,
    Silver = 1,
    Gold = 2,
    Diamond = 3,
    Sun = 4,
    Smallsun = 5,
    Largesun = 6,
    FinalSeedPacket = 7,
    Trophy = 8,
    Shovel = 9,
    Almanac = 10,
    Carkeys = 11,
    ScaryPot = 12,
    WateringCan = 13,
    Taco = 14,
    Note = 15,
    UsableSeedPacket = 16,
    PresentPlant = 17,
    AwardMoneyBag = 18,
    AwardPresent = 19,
    AwardBagDiamond = 20,
    SunflowerSilverTrophy = 21,
    SunflowerGoldTrophy = 22,
    Chocolate = 23,
    AwardChocolate = 24,
    PresentMinigames = 25,
    PresentPuzzleMode = 26,
    Present32 = 27,
    Present1024 = 28,
    CoopDoubleSun = 29,
    VSZombieBrain = 30,
    VSPlantTrophy = 31,
    VSZombieTrophy = 32
};
}

namespace GameScenes {
enum GameScenes { Loading = 0, Menu = 1, LevelIntro = 2, Playing = 3, ZombiesWon = 4, Award = 5, Credit = 6, Challenge = 7, Leaderboard = 8 };
}

namespace ChallengeState {
enum ChallengeState {
    Normal = 0,
    BeghouledMoving,
    BeghouledFalling,
    BeghouledNoMatches,
    SlotMachineRolling,
    StormFlash1,
    StormFlash2,
    StormFlash3,
    ZenFading,
    ScaryPotterMalleting,
    LastStandOnslaught = 10,
    TreeJustGrew,
    TreeGiveWisdom,
    TreeWaitingToBabble,
    TreeBabbling,
    ShovelFlashing = 15
};
}
namespace ReanimatorRenderGroup {
enum ReanimatorRenderGroup { RENDER_GROUP_HIDDEN = -1, RENDER_GROUP_NORMAL = 0 };
}


namespace PixelFormat {
enum PixelFormat {
    kPixelFormat_None = -1,
    kPixelFormat_Automatic,
    kPixelFormat_RGBA8888,
    kPixelFormat_RGBA4444,
    kPixelFormat_RGBA5551,
    kPixelFormat_RGB565,
    kPixelFormat_RGB888,
    kPixelFormat_L8,
    kPixelFormat_A8,
    kPixelFormat_LA88,
    kPixelFormat_RGB_PVRTC2,
    kPixelFormat_RGB_PVRTC4,
    kPixelFormat_RGBA_PVRTC2,
    kPixelFormat_RGBA_PVRTC4
};
}



namespace ReanimLoopType {
enum ReanimLoopType { Loop = 0, LoopFullLastFrame = 1, PlayOnce = 2, PlayOnceAndHold = 3, PlayOnceFullLastFrame, PlayOnceFullLastFrameAndHold };
}


namespace DrawMode {
enum DrawMode { DRAWMODE_NORMAL = 0, DRAWMODE_ADDITIVE = 1 };
}
namespace SeedChooserState {
enum SeedChooserState { Normal = 0, ViewLawn = 1 };
}
namespace TodCurves {
enum TodCurves {
    Constant = 0,
    Linear = 1,
    EaseIn = 2,
    EaseOut = 3,
    EaseInOut = 4,
    EaseInOutWeak = 5,
    FastInOut = 6,
    FastInOutWeak = 7,
    WeakFastInOut = 8,
    Bounce = 9,
    BounceFastMiddle = 10,
    BounceSlowMiddle = 11,
    SinWave = 12,
    EaseSinWave = 13
};
}

enum ReanimationType {
    REANIM_NONE = -1,
    REANIM_LOADBAR_SPROUT,
    REANIM_LOADBAR_ZOMBIEHEAD,
    REANIM_SODROLL,
    REANIM_FINAL_WAVE,
    REANIM_PEASHOOTER,
    REANIM_WALLNUT,
    REANIM_LILYPAD,
    REANIM_SUNFLOWER,
    REANIM_LAWNMOWER,
    REANIM_READYSETPLANT,
    REANIM_CHERRYBOMB,
    REANIM_SQUASH,
    REANIM_DOOMSHROOM,
    REANIM_SNOWPEA,
    REANIM_REPEATER,
    REANIM_SUNSHROOM,
    REANIM_TALLNUT,
    REANIM_FUMESHROOM,
    REANIM_PUFFSHROOM,
    REANIM_HYPNOSHROOM,
    REANIM_CHOMPER,
    REANIM_ZOMBIE,
    REANIM_SUN,
    REANIM_POTATOMINE,
    REANIM_SPIKEWEED,
    REANIM_SPIKEROCK,
    REANIM_THREEPEATER,
    REANIM_MARIGOLD,
    REANIM_ICESHROOM,
    REANIM_ZOMBIE_FOOTBALL,
    REANIM_ZOMBIE_NEWSPAPER,
    REANIM_ZOMBIE_ZAMBONI,
    REANIM_SPLASH,
    REANIM_JALAPENO,
    REANIM_JALAPENO_FIRE,
    REANIM_COIN_SILVER,
    REANIM_ZOMBIE_CHARRED,
    REANIM_ZOMBIE_CHARRED_IMP,
    REANIM_ZOMBIE_CHARRED_DIGGER,
    REANIM_ZOMBIE_CHARRED_ZAMBONI,
    REANIM_ZOMBIE_CHARRED_CATAPULT,
    REANIM_ZOMBIE_CHARRED_GARGANTUAR,
    REANIM_SCRAREYSHROOM,
    REANIM_PUMPKIN,
    REANIM_PLANTERN,
    REANIM_TORCHWOOD,
    REANIM_SPLITPEA,
    REANIM_SEASHROOM,
    REANIM_BLOVER,
    REANIM_FLOWER_POT,
    REANIM_CACTUS,
    REANIM_DANCER,
    REANIM_TANGLEKELP,
    REANIM_STARFRUIT,
    REANIM_POLEVAULTER,
    REANIM_BALLOON,
    REANIM_GARGANTUAR,
    REANIM_IMP,
    REANIM_DIGGER,
    REANIM_DIGGER_DIRT,
    REANIM_ZOMBIE_DOLPHINRIDER,
    REANIM_POGO,
    REANIM_BACKUP_DANCER,
    REANIM_BOBSLED,
    REANIM_JACKINTHEBOX,
    REANIM_SNORKEL,
    REANIM_BUNGEE,
    REANIM_CATAPULT,
    REANIM_LADDER,
    REANIM_PUFF,
    REANIM_SLEEPING,
    REANIM_GRAVE_BUSTER,
    REANIM_ZOMBIES_WON,
    REANIM_MAGNETSHROOM,
    REANIM_BOSS,
    REANIM_CABBAGEPULT,
    REANIM_KERNELPULT,
    REANIM_MELONPULT,
    REANIM_COFFEEBEAN,
    REANIM_UMBRELLALEAF,
    REANIM_GATLINGPEA,
    REANIM_CATTAIL,
    REANIM_GLOOMSHROOM,
    REANIM_BOSS_ICEBALL,
    REANIM_BOSS_FIREBALL,
    REANIM_COBCANNON,
    REANIM_GARLIC,
    REANIM_GOLD_MAGNET,
    REANIM_WINTER_MELON,
    REANIM_TWIN_SUNFLOWER,
    REANIM_POOL_CLEANER,
    REANIM_ROOF_CLEANER,
    REANIM_FIRE_PEA,
    REANIM_IMITATER,
    REANIM_YETI,
    REANIM_BOSS_DRIVER,
    REANIM_LAWN_MOWERED_ZOMBIE,
    REANIM_CRAZY_DAVE,
    REANIM_TEXT_FADE_ON,
    REANIM_HAMMER,
    REANIM_SLOT_MACHINE_HANDLE,
    REANIM_SELECTOR_SCREEN,
    REANIM_PORTAL_CIRCLE,
    REANIM_PORTAL_SQUARE,
    REANIM_ZENGARDEN_SPROUT,
    REANIM_ZENGARDEN_WATERINGCAN,
    REANIM_ZENGARDEN_FERTILIZER,
    REANIM_ZENGARDEN_BUGSPRAY,
    REANIM_ZENGARDEN_PHONOGRAPH,
    REANIM_DIAMOND,
    REANIM_STINKY,
    REANIM_RAKE,
    REANIM_RAIN_CIRCLE,
    REANIM_RAIN_SPLASH,
    REANIM_ZOMBIE_SURPRISE,
    REANIM_COIN_GOLD,
    Woodsign,
    ZombieFlagpole = 141,
    LeaderboardsHouse = 147,
    LeaderboardsHouseScene = 148,
    LeaderboardsHouseBgTrees = 149,
    LeaderboardsHouseBgHouses = 150,
    LeaderboardsHouseClouds = 151,
    AchievementHomeSecurity = 162,
    AchievementMorticulturalist = 163,
    AchievementSmartyBranches = 164,
    AchievementCrashOfTheTitan = 165,
    AchievementZffs4Evr = 166,
    AchievementAliveAndPlanting = 167,
    AchievementVersus = 168,
    AchievementSoilYourPlants = 169,
    AchievementExplodonator = 170,
    AchievementCloseShave = 171,
    AchievementShop = 172,
    AchievementNomNomNom = 173,
    ZombatarHead = 178,
    NUM_REANIMS
};

struct ChallengeDefinition {
    GameMode::GameMode mChallengeMode;  // 0
    int mChallengeIconIndex;            // 1
    ChallengePage::ChallengePage mPage; // 2
    int mRow;                           // 3 无用
    int mCol;                           // 4 无用
    const char *mChallengeName;         // 5
};

typedef std::string			SexyString;
#define _S(x)				x

typedef SexyString::value_type					SexyChar;

struct SexyRGBA {unsigned char b,g,r,a;};
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
//typedef __int64 int64;

class Color {
public:
    int mRed;
    int mGreen;
    int mBlue;
    int mAlpha;

    static Color Black;
    static Color White;

public:
    Color();
    Color(int theColor);
    Color(int theColor, int theAlpha);
    Color(int theRed, int theGreen, int theBlue);
    Color(int theRed, int theGreen, int theBlue, int theAlpha);
    Color(const SexyRGBA &theColor);
    Color(const uchar* theElements);
    Color(const int* theElements);

    int						GetRed() const;
    int						GetGreen() const;
    int						GetBlue() const;
    int						GetAlpha() const;
    ulong					ToInt() const;
    SexyRGBA				ToRGBA() const;

    int&					operator[](int theIdx);
    int						operator[](int theIdx) const;
};

Color Color::Black(0, 0, 0);
Color Color::White(255, 255, 255);

Color::Color() :
    mRed(0),
    mGreen(0),
    mBlue(0),
    mAlpha(255)
{
}

Color::Color(int theColor) :
    mAlpha((theColor >> 24) & 0xFF),
    mRed((theColor   >> 16) & 0xFF),
    mGreen((theColor >> 8 ) & 0xFF),
    mBlue((theColor       ) & 0xFF)
{
    if(mAlpha==0)
        mAlpha = 0xff;
}

Color::Color(int theColor, int theAlpha) :
    mRed((theColor   >> 16) & 0xFF),
    mGreen((theColor >> 8 ) & 0xFF),
    mBlue((theColor       ) & 0xFF),
    mAlpha(theAlpha)
{
}

Color::Color(int theRed, int theGreen, int theBlue) :
    mRed(theRed),
    mGreen(theGreen),
    mBlue(theBlue),
    mAlpha(0xFF)
{
}

Color::Color(int theRed, int theGreen, int theBlue, int theAlpha) :
    mRed(theRed),
    mGreen(theGreen),
    mBlue(theBlue),
    mAlpha(theAlpha)
{
}

Color::Color(const SexyRGBA &theColor) :
    mRed(theColor.r),
    mGreen(theColor.g),
    mBlue(theColor.b),
    mAlpha(theColor.a)
{
}

Color::Color(const uchar* theElements) :
    mRed(theElements[0]),
    mGreen(theElements[1]),
    mBlue(theElements[2]),
    mAlpha(0xFF)
{
}

Color::Color(const int* theElements) :
    mRed(theElements[0]),
    mGreen(theElements[1]),
    mBlue(theElements[2]),
    mAlpha(0xFF)
{
}

int	Color::GetRed() const
{
    return mRed;
}

int Color::GetGreen() const
{
    return mGreen;
}

int	Color::GetBlue() const
{
    return mBlue;
}

int	Color::GetAlpha() const
{
    return mAlpha;
}

int& Color::operator[](int theIdx)
{
    static int aJunk = 0;

    switch (theIdx)
    {
        case 0:
            return mRed;
        case 1:
            return mGreen;
        case 2:
            return mBlue;
        case 3:
            return mAlpha;
        default:
            return aJunk;
    }
}

int Color::operator[](int theIdx) const
{
    switch (theIdx)
    {
        case 0:
            return mRed;
        case 1:
            return mGreen;
        case 2:
            return mBlue;
        case 3:
            return mAlpha;
        default:
            return 0;
    }
}

ulong Color::ToInt() const
{
    return (mAlpha << 24) | (mRed << 16) | (mGreen << 8) | (mBlue);
}

SexyRGBA Color::ToRGBA() const
{
    SexyRGBA anRGBA;
    anRGBA.r = mRed;
    anRGBA.g = mGreen;
    anRGBA.b = mBlue;
    anRGBA.a = mAlpha;

    return anRGBA;
}


struct TRect {
    int mX;
    int mY;
    int mWidth;
    int mHeight;
};

struct MotionTrailFrame {
    float mPosX;
    float mPosY;
    float mAnimTime;
};


struct ChosenSeed {
    int mX;                                      // 0
    int mY;                                      // 1
    int mTimeStartMotion;                        // 2
    int mTimeEndMotion;                          // 3
    int mStartX;                                 // 4
    int mStartY;                                 // 5
    int mEndX;                                   // 6
    int mEndY;                                   // 7
    int mChosenPlayerIndex;                      // 8
    SeedType::SeedType mSeedType;                // 9
    ChosenSeedState::ChosenSeedState mSeedState; // 10
    int mSeedIndexInBank;                        // 11
    bool mRefreshing;                            // 12
    int mRefreshCounter;                         // 13
    SeedType::SeedType mImitaterType;            // 14
    bool mCrazyDavePicked;                       // 60
};

class Board;
class GamepadControls;
class PlayerInfo;
class PoolEffect;
class Reanimation;
class SeedChooserScreen;
class Music;
class Music2;

class SexyAppBase {
public:
    int *vTable;                            // 0
    int unkMem1[164];                       // 1 ~ 164
    int *mWidgetManager;                    // 165
    int unkMem2[70];                        // 166 ~ 235, musicinterface 193
    bool mLawnMouseMode;                    // 944
    int unkMem3[77];                        // 237 ~ 313
    int *mSoundManager;                     // 314
    int unkMem4[39];                        // 315 ~ 353
    int mNumLoadingThreadTasks;             // 354
    int mCompletedLoadingThreadTasks;       // 355
    int unkMem5[30];                        // 356 ~ 385
    bool mIs3DAcclerated;                   // 1544
    int unkMem6[SexyAppBasePartSize - 387]; // 387 ~ 525
    bool unkBool1;                          // 2104
    bool mGamePad1IsOn;                     // 2105
    int unkMem7[22];                        // 527 ~ 548
    bool unkBool2;                          // 2196
    bool mGamePad2IsOn;                     // 2197
    int unkMem8[2];                         // 550 ~ 551
}; // 115： 552 , 111： 553


struct FoleyParams {
    FoleyType::FoleyType mFoleyType;
    float mPitchRange;
    int *mSfxID[10];
    uint mFoleyFlags;
};

struct FoleyInstance {
    int *mInstance;
    int mRefCount;
    bool _paused;
    int mStartTime;
    int mPauseOffset;
};

struct FoleyTypeData {
    FoleyInstance mFoleyInstances[8];
    int mLastVariationPlayed;
};

struct TodFoley {
    FoleyTypeData mTypeData[110];
};

class ReanimatorCache;


struct FlagsMod {
public:
    int mAddFlags;
    int mRemoveFlags;
};

struct TodSmoothArray {
    int mItem;
    float mWeight;
    float mLastPicked;
    float mSecondLastPicked;
};

struct Insets {
public:
    int mLeft;
    int mTop;
    int mRight;
    int mBottom;
};

class LawnApp;

class Sexy {
public:
    class Image {
    public:
        int *vTable;                      // 0
        int placeHolder[2];               // 1 ~ 2
        bool unkBool;                     // 12
        int unkMmWidthems1[2];            // 4 ~ 5
        int *stringUnk1;                  // 6
        int *stringUnk2;                  // 7
        int *stringUnk3;                  // 8
        int mWidth;                       // 9
        int mHeight;                      // 10
        int mPitch;                       // 11
        int mStride;                      // 12
        PixelFormat::PixelFormat mFormat; // 13
        int mPixelFormatHint;             // 14
        int mNumRows;                     // 15
        int mNumCols;                     // 16
        int *mAnimInfo;                   // 17
        int unk[6];                       // 18 ~ 23
        int mHorizonWrapMode;             // 24
        int mVertWrapMode;                // 25
        int mTag;                         // 26
        int unkMems3;                     // 27 ，实际上Sexy::Image就到这里，下面是MemoryImage的成员
        LawnApp *mApp;                    // 28
        int unkMems4;                     // 29
        unsigned int *mBits;              // 30
        int mBitsChangedCount;            // 31
        int unk1[4];                      // 32 ~ 35
        bool mUnkModeRelated;             // 144
        bool mUnkMode1;                   // 145
        bool mUnkMode2;                   // 146
        bool mUnkBool;                    // 147
        bool mVolatile;                   // 148
        int unk2[20];                     // 38 ~ 57
    }; // 大小58个整数


public:
    class Font {
    public:
        int *vTable;
        int mAscent;
        int mAscentPadding;
        int mHeight;
        int mLineSpacingOffset;
    };

public:
    class Graphics {
    public:
        int *vTable;                  // 0
        Sexy::Image *mDestImage;      // 1
        float mTransX;                // 2
        float mTransY;                // 3
        float mScaleX;                // 4
        float mScaleY;                // 5
        float unk1[2];                // 6 ~ 7
        TRect mClipRect;              // 8 ~ 11
        int unk2[3];                  // 12 ~ 14
        Color mColorUnknown;          // 15 ~ 18
        Color mColor;                 // 19 ~ 22
        int *mFont;                   // 23
        DrawMode::DrawMode mDrawMode; // 24
        bool mColorizeImages;         // 100
        bool mFastStretch;            // 101
        bool unkbool1;                // 102
        bool mLinearBlend;            // 103
        bool unkbool2;                // 104
        bool mGlobalScale;            // 105
        bool mGlobalTrackDeviceState; // 106
        int *unkPushPopTramsform;     // 27
        int unkInt;                   // 28
        int m3D;                      // 29
        int unk3[6];                  // 30 ~ 35
    }; // 大小36个整数

public:
    class WidgetContainer {
    public:
        int *vTable;                  // 0
        int mWidgetsUnk[5];           // 1 ~ 5
        int *mWidgetManager;          // 6
        WidgetContainer *mParent;     // 7
        bool mUpdateIteratorModified; // 32
        int *mUpdateIterator;         // 9
        int mLastWMUpdateCount;       // 10
        int mUpdateCnt;               // 11
        int unkMember;                // 12
        int mX;                       // 13
        int mY;                       // 14
        int mWidth;                   // 15
        int mHeight;                  // 16
        bool mHasAlpha;               // 68
        bool mClip;                   // 69
        FlagsMod mWidgetFlagsMod;     // 18 ~ 19
        int mPriority;                // 20
        int mZOrder;                  // 21
        int unk[6];                   // 22 ~ 27
        int mWidgetId;                // 28
    }; // 大小未知，目前认为是29个整数。反正Widget是64个整数，足够了。

    class Widget : public WidgetContainer {
    public:
        bool mVisible;               // 116
        bool mMouseVisible;          // 117
        bool mDisabled;              // 118
        bool mHasFocus;              // 119
        bool mIsDown;                // 120
        bool mIsOver;                // 121
        bool mHasTransparencies;     // 122
        int mColorsUnk[2];           // 32 ~ 33
        Insets mMouseInsets;         // 34 ~ 37
        bool mDoFinger;              // 152
        bool mWantsFocus;            // 153
        int unk1[11];                // 38 ~ 48
        Widget *mFocusLinks[4];      // 49 ~ 52 ，上下左右
        int unk2[2];                 // 53 ~ 54
        Widget *mFocusedChildWidget; // 55
        int unk3[4];                 // 56 ~ 59
        int *mAnimatorForState[4];   // 60 ~ 63
    }; // 大小64个整数！

    class Checkbox : public Widget {
    public:
        int unknownMember[8];   // 64 ~ 71
        int *mListener;         // 72
        Image *mUncheckedImage; // 73
        Image *mCheckedImage;   // 74
        int mId;                // 75
        bool mChecked;          // 304
        TRect mCheckedRect;     // 77 ~ 80
        TRect mUncheckedRect;   // 81 ~ 84
        Color mOutlineColor;    // 85 ~ 88
        Color mBkgColor;        // 89 ~ 92
        Color mCheckColor;      // 93 ~ 96
    }; // 大小97个整数


    class SelectableWidget : public Widget {
    public:
        Color mUnkColor;  // 64 ~ 67
        float unkMems[4]; // 68 ~ 71
    }; // 大小72个整数

    struct TextLayout {
        int unk[84];
    }; // 大小84个整数

    class ButtonWidget : public SelectableWidget {
    public:
        int *mLabel;            // 72
        int *mStringUnk2;       // 73
        TextLayout mTextLayout; // 74 ~ 157
        int unkMem1[9];         // 158 ~ 166
        Insets mInsets;         // 167 ~ 170
        int unkMems2[2];        // 171 ~ 172
        Image *mButtonImage;    // 173
        Image *mOverImage;      // 174
        Image *mDownImage;      // 175
        Image *mDisabledImage;  // 176
        TRect mNormalRect;      // 177 ~ 180
        TRect mOverRect;        // 181 ~ 184
        TRect mDownRect;        // 185 ~ 188
        TRect mDisabledRect;    // 189 ~ 192
        bool unkBool1;          // 772
        bool mBtnNoDraw;        // 773
        bool unkBool2;          // 774
        int unkMems3[2];        // 194 ~ 195
        double mOverAlpha;      // 197 ~ 198
        int unkMems4[4];        // 198 ~ 201
        bool unkBool3;          // 808
        bool unkBool4;          // 809
        int unkMem2;            // 203
    }; // 大小204个整数

    class DialogButton : public ButtonWidget {
    public:
        Image *mImage;   // 204
        int unkMems4[4]; // 205 ~ 208
        LawnApp *mApp;   // 209
    }; // 大小210个整数

    class GameButton : public DialogButton {
    public:
        int unkMems4[2];                // 210  ~ 211
        bool unkBool5;                  // 848
        int unkMems5[2];                // 213 ~ 214
        Sexy::Image *mOverOverlayImage; // 215
        bool mDrawStoneButton;          // 864
        int unkMems6[13];               // 217 ~ 229
    }; // 大小230个整数


    class ScrollbarWidget : public Widget {
    public:
        int unkMem;             // 64
        Widget *mUpButton;      // 65
        Widget *mDownButton;    // 66
        bool mInvisIfNoScroll;  // 268
        int mId;                // 68
        double mValue;          // 69 ~ 70
        double mMaxValue;       // 71 ~ 72
        double mPageSize;       // 73 ~ 74
        bool mHorizontal;       // 300
        int mButtonLength;      // 76
        bool mPressedOnThumb;   // 77
        int mMouseDownThumbPos; // 78
        int mMouseDownX;        // 79
        int mMouseDownY;        // 80
        int mUpdateMode;        // 81
        int mUpdateAcc;         // 82
        int mButtonAcc;         // 83
        int mLastMouseX;        // 84
        int mLastMouseY;        // 85
        int *mScrollListener;   // 86
        Image *mThumbImage;     // 87
        Image *mBarImage;       // 88
        Image *mPagingImage;    // 89
    }; // 大小90个整数

    class CustomScrollbarWidget : public ScrollbarWidget {
        // 没有新增任何成员，6，这个类不知道什么意义
    }; // 大小90个整数


    class MemoryImage : public Image {}; // 大小58个整数

    struct SexyMatrix3 {
        float m[3][3]; // 9
    };

    struct ButtonListenerVTable {
        void *Delete;
        void *Delete2;
        void *ButtonPress;
        void *ButtonPress2;
        void *ButtonDepress;
        void *ButtonDownTick;
        void *ButtonMouseEnter;
        void *ButtonMouseLeave;
        void *ButtonMouseMove;
    };

    struct ButtonListener {
        ButtonListenerVTable *vTable;
    };

    class MenuWidget : public Widget {
    public:
        Sexy::ButtonListener mButtonListener; // 64
        bool mIsFading;                       // 260
        bool unkBool2;                        // 261
        int *mMenuParser;                     // 66
        int *mSourceFileName;                 // 67
        int unkInt1;                          // 68
        Sexy::Image *mImage;                  // 69
    }; // 大小70个整数

    class Dialog : public Widget {
    public:
        Sexy::ButtonListener mButtonListener; // 64
        int *mDialogListener;                 // 65
        Image *mComponentImage;               // 66
        DialogButton *mYesButton;             // 67
        DialogButton *mNoButton;              // 68
        int mNumButtons;                      // 69
        int *mDialogHeader;                   // 70
        int *mDialogFooter;                   // 71
        int *mDialogLines;                    // 72
        int *mUnkText;                        // 73
        TextLayout mTextLayout;               // 74 ~ 157
        int unk1[3];                          // 158 ~ 160
        int mButtonMode;                      // 161
        int *mHeaderFont;                     // 162
        int *mLinesFont;                      // 163
        int mTextAlign;                       // 164
        int mLineSpacingOffset;               // 165
        int mButtonHeight;                    // 166
        Insets mBackgroundInsets;             // 167 ~ 170
        Insets mContentInsets;                // 171 ~ 174
        int mSpaceAfterHeader;                // 175
        bool mDragging;                       // 176
        int mDragMouseX;                      // 177
        int mDragMouseY;                      // 178
        int mId;                              // 179
        bool mIsModal;                        // 180
        int mResult;                          // 181
        int mButtonHorzSpacing;               // 182
        int mButtonSidePadding;               // 183
    }; // 大小184个整数

    enum KeyCode { Invalid = -1, Ok = 13, Back = 27, Back2 = 305, Left = 37, Up = 38, Right = 39, Down = 40, Shovel = 49, Hammer = 50 };

    class WidgetAnimator {
    public:
        int *vTable;            // 0
        int unk[2];             // 1 ~ 2
        Widget *mWidget;        // 3
        int mUpdateCounter;     // 4
        bool mHideOnCompletion; // 20
    };
};

class ReanimTrackWidgetAnimator : public Sexy::WidgetAnimator {
public:
    LawnApp *mApp;                 // 6
    Sexy::Widget *mLawnMenuWidget; // 7
    int *mTrackName1;              // 8
    int *mTrackName2;              // 9
    int *mTrackName3;              // 10
    int unk2[2];                   // 11 ~ 12
};

class CreditScreen;

class MainMenu;

class ChallengeScreen;

class TitleScreen;

class EffectSystem;



struct SexyTransform2D : Sexy::SexyMatrix3 {};


class ChallengeScreen;



class ReanimatorTrackInstance;

class ReanimatorTransform;

class ReanimatorDefinition;



class GameObject {
public:
    int *vTable;        // 0
    int placeHolder[3]; // 1 ~ 3
    LawnApp *mApp;      // 4
    Board *mBoard;      // 5
    int mX;             // 6
    int mY;             // 7
    int mWidth;         // 8
    int mHeight;        // 9
    bool mVisible;      // 40
    int mRow;           // 11
    int mRenderOrder;   // 12
}; // 大小13个整数

class SeedPacket;
class SeedBank;
class Plant;
class Zombie;
class Coin;


class CursorObject : public GameObject {
public:
    int mSeedBankIndex;                 // 13
    SeedType::SeedType mType;           // 14
    SeedType::SeedType mImitaterType;   // 15
    CursorType::CursorType mCursorType; // 16
    Coin *mCoinID;                      // 17
    Plant *mGlovePlantID;               // 18
    Plant *mDuplicatorPlantID;          // 19
    Plant *mCobCannonPlantID;           // 20
    int mHammerDownCounter;             // 21
    int mReanimCursorID;                // 22
}; // 大小23个整数


class CursorPreview : public GameObject {
public:
    int mGridX;      // 13
    int mGridY;      // 14
    int playerIndex; // 15
}; // 大小16个整数

struct ShopSeedPacket {
    int unknown[21];
}; // 大小21个整数



class MessageWidget;

class Challenge;

struct PlantRbTree {
    int unk[6];
};



class BaseGamepadControls {
public:
    int *mVtable;                    // 0
    GameObject mGameObject;          // 1 ~ 13
    Board *mBoard;                   // 14
    SeedBank *mSeedBank;             // 15
    float mUnkFirstHighlightRelated; // 16
    int mShovelRelated1;             // 17
    float mGamepadAccLeftX;
    float mGamepadAccLeftY;
    float mGridCenterPositionX;    // 20
    float mGridCenterPositionY;    // 21
    float mRightPositionX;         // 22
    float mRightPositionY;         // 23
    int mGamepadState;             // 24
    int unk1;                      // 25
    float mDigIndicatorPercentage; // 26 , 每按下一次铲除键就加2.3
    float mCursorPositionX;        // 27
    float mCursorPositionY;        // 28
    float mGamepadVelocityLeftX;   // 29
    float mGamepadVelocityLeftY;   // 30
    float mGamepadVelocityRightX;  // 31
    float mGamepadVelocityRightY;  // 32
    int unk2[4];                   // 33 ~ 36
    int mPlayerIndex1;             // 37
    int mPlayerIndex2;             // 38
    float mCursorPositionYJitter;  // 39
    float mUpdateAdd0Dot016;       // 40
    int unkMems[2];                // 41 ~ 42
    // 大小43个整数
public:
    void GetGamepadVelocity(float *horizontal, float *vertical);
};


struct GameStats {

    enum MiscStat { ZOMBIES_KILLED = 0, PLANTS_KILLED = 1, MONEY = 2, TREE_HEIGHT = 4, ENDLESS_FLAGS = 5, MOWED_ZOMBIES = 6, STINKY_CHOCOLATES = 7 };

    HouseType::HouseType mHouseType; // 0
    int unk;                         // 1
    int mMiscStats[9];               // 2 ~ 10
    char mFavoritePlants[49];        // 44 ~ 92
    char mFavoriteZombies[47];       // 93 ~ 139
    float mSurvivalCompletion;       // 35
    float mMiniGameCompletion;       // 36
    float mPuzzleCompletion;         // 37
}; // 大小38个整数

struct PottedPlant {

    enum PottedPlantAge // Prefix: PLANTAGE
    {
        Sprout,
        Small,
        Medium,
        Full
    };

    enum GardenType // Prefix: GARDEN
    {
        Main,
        Mushroom,
        Wheelbarrow,
        Aquarium
    };

    enum FacingDirection // Prefix: FACING
    {
        Right,
        Left
    };

    enum PottedPlantNeed { None, Water, Fertilizer, Bugspray, Phonograph };

    SeedType::SeedType mSeedType : 7;
    FacingDirection mFacing : 1;

    GardenType mWhichZenGarden : 2;
    int mY : 2;
    DrawVariation::DrawVariation mDrawVariation : 4;

    int mX : 3;
    PottedPlantNeed mPlantNeed : 3;
    PottedPlantAge mPlantAge : 2;

    int mTimesFed : 3;
    int mFeedingsPerGrow : 3;
    int : 2;

    int mLastWateredTime;       // 1
    int mLastNeedFulfilledTime; // 2
    int mLastFertilizedTime;    // 3
    int mLastChocolateTime;     // 4
};

class PlayerInfo {
public:
    int *vTable;                // 0
    int unk1;                   // 1
    int *mProFileMgr;           // 2
    int unk2;                   // 3
    char *mName;                // 4
    int mUseSeq;                // 5
    int mId;                    // 6
    int mProfileId;             // 7
    int mFlags;                 // 8
    int mLevel;                 // 9
    int mCoins;                 // 10
    int mChallengeRecords[100]; // 11 ~ 110 ， 但末尾6个完全不会用到，可以成为我的自己存数据的空间。
    int mPurchases[36];         // 111 ~ 146 ，本应该是mPurchases[80]，111 ~ 190，但仅用到了前36个。
    bool mAchievements[12];     // 147 ~ 149, 从mPurchases[80]分出来的
    bool mUnused[145];          // 150 ~
    bool mIsVibrateClosed;
    bool mZombatarEnabled;
    unsigned char mZombatarHat;
    unsigned char mZombatarHatColor;
    unsigned char mZombatarHair;
    unsigned char mZombatarHairColor;
    unsigned char mZombatarFacialHair;
    unsigned char mZombatarFacialHairColor;
    unsigned char mZombatarAccessory;
    unsigned char mZombatarAccessoryColor;
    unsigned char mZombatarEyeWear;
    unsigned char mZombatarEyeWearColor;
    unsigned char mZombatarTidBit;
    unsigned char mZombatarTidBitColor;
    bool mIs3DAcceleratedClosed;   // ~ 189, 从mPurchases[80]分出来的
    int mUsedCoins;                // 190, 从mPurchases[80]分出来的
    int unkMem4[2];                // 191 ~ 192
    int mLastStinkyChocolateTime;  // 193
    int mStinkyPosX;               // 194
    int mStinkyPosY;               // 195
    int mNumPottedPlants;          // 196
    int unk4;                      // 197
    PottedPlant mPottedPlants[50]; // 198 ~ 447
    double mMusicVolume;           // 448 ~ 449
    double mSoundVolume;           // 450 ~ 451
    int unkMems6[5];               // 452 ~ 456
    bool mHelpTextSeen[6];         // 1828 ~ 1833
    int unk5;                      // 459
    bool unkBool1;                 // 1840
    bool unkBool2;                 // 1841
    bool mPassedShopSeedTutorial;  // 1842
    bool mMailMessageRead[32];     // 1843 ~ 1874 ，紧密存放，可以存放32x8个bool
    bool mMailMessageSeen[32];     // 1875 ~ 1906 ，紧密存放，可以存放32x8个bool
    GameStats mGameStats;          // 477 ~ 514
    int unk6;                      // 515
}; // 大小516个整数

struct CausticEffect {
    bool mTextureAlpha[256][256];
};


struct SexyVertex2D {
    float x;
    float y;
    int unk1;
    int unk2;
    unsigned int color;
    int unk3;
    float u;
    float v;
};

struct TriVertex {
    float x;
    float y;
    float u;
    float v;
    unsigned int color;
};


class PoolEffect {
public:
    CausticEffect *mCausticGrayscaleImage; // 0
    Sexy::Image *mCausticImage;            // 1
    LawnApp *mApp;                         // 2
    int mPoolCounter;                      // 3
}; // 大小4个整数



class ProfileMgr {
public:
    int *vTable;                // 0
    int *mProfileEventListener; // 1
};

class DefaultProfileMgr : public ProfileMgr {
public:
    int *mProfileMap;    // 2
    int *mProfileMapEnd; // 3

    int mNumProfiles; // 7

    int mNextProfileUseSeq; // 9
};

class BaseRes {
public:
    int *vTable;            // 0
    ResType::ResType mType; // 1
    int *mResourceRef;      // 2
    int unk[8];             // 3 ~ 10
    char *mPath;            // 11
    int unk2[13];           // 12 ~ 24
}; // 大小25个整数

class SoundRes : public BaseRes {
public:
    int mSoundId;   // 25
    double mVolume; // 26 ~ 27
    int mPanning;   // 28
    int unk3;       // 29
}; // 大小30个整数

class MessageWidget {
public:
    int *vTable;                                  // 0
    int unk[3];                                   // 1 ~ 3
    LawnApp *mApp;                                // 4
    char mLabel[128];                             // 5 ~ 36
    int mDisplayTime;                             // 37
    int mDuration;                                // 38
    MessageStyle::MessageStyle mMessageStyle;     // 39
    Reanimation *mTextReanimID[128];              // 40 ~ 167
    ReanimationType mReanimType; // 168
    int mSlideOffTime;                            // 169
    float unkFloatWithInitValue1;                 // 170
    char mLabelNext[128];                         // 171 ~ 202
    MessageStyle::MessageStyle mMessageStyleNext; // 203
}; // 大小204个整数

class CustomMessageWidget : public MessageWidget {
public:
    Sexy::Image *mIcon; // 204
}; // 大小205个整数

struct Curve1DUtil {
    int unk[16];
};




class AchievementsWidget : public Sexy::Widget {
public:
    Sexy::ButtonListener mButtonListener; // 64
    LawnApp *mApp;                        // 65
    int mMouseDownY;
    int mLastDownY;
    int mLastDownY1;
    long mLastTimeMs;
    long mLastTimeMs1;
    float mVelocity;
    float mAccY;
    bool mIsScrolling;
}; // 我想用AchievementsWidget取代MaskHelpWidget。MaskHelpWidget的大小是66个整数。

struct LeaderboardReanimations {
    Reanimation *backgroundReanim[5];
    Reanimation *achievementReanim[12];
};

class TrashBin : public Sexy::Widget {
public:
    enum TrashPileType { PLANT_PILE = 0, ZOMBIE_PILE = 1 };

    TrashPileType mTrashPileType; // 64
    float mTrashHeight;           // 65
    Sexy::Image *mPileImage[10];  // 66 ~ 75
    bool mMirrorPile[10];         // 76 ~ 78
    int mRandomPileWeight[6];     // 79 ~ 84
    int mPileNum;                 // 85
    // 大小86个整数
public:
    void Creat(TrashPileType theTrashPileType, float theHeight);
    void Draw(Sexy::Graphics *g);

};

class LeaderboardsWidget : public Sexy::Widget {
public:
    LawnApp *mApp;                                     // 64
    TrashBin *mZombieTrashBin;                         // 65
    TrashBin *mPlantTrashBin;                          // 66
    bool mAchievements[12];                            // 67 ~ 69
    LeaderboardReanimations *mLeaderboardReanimations; // 70
    int mLongestRecordPool;                            // 71
    Sexy::GameButton *mBackButton;
    Sexy::ButtonListener *mButtonListener;
    int mFocusedAchievementIndex;
    bool mHighLightAchievement;
}; // 我想用LeaderboardsWidget取代DaveHelp。

class ZombatarWidget : public Sexy::MenuWidget {
public:
    enum TabType { SKIN = 0, HAIR = 1, FHAIR = 2, TIDBIT = 3, EYEWEAR = 4, CLOTHES = 5, ACCESSORY = 6, HAT = 7, BACKGROUND = 8, MaxTabNum = 9 };

    enum AccessoryNum {
        HairNum = 16,
        FHairNum = 24,
        TidBitNum = 14,
        EyeWearNum = 16,
        ClothNum = 12,
        AccessoryNum = 15,
        HatNum = 14,
        BackgroundNum = 83,
    };

    Sexy::ButtonListener *mButtonListener;
    LawnApp *mApp;
    Zombie *mPreviewZombie;
    Sexy::GameButton *mBackButton;
    Sexy::GameButton *mFinishButton;
    Sexy::GameButton *mViewPortraitButton;
    Sexy::GameButton *mNewButton;
    Sexy::GameButton *mDeleteButton;
    Reanimation *mZombatarReanim;
    bool mShowExistingZombatarPortrait;
    bool mShowZombieTypeSelection;
    unsigned char mSelectedTab;
    unsigned char mSelectedSkinColor;
    unsigned char mSelectedHair;
    unsigned char mSelectedHairColor;
    unsigned char mSelectedFHair;
    unsigned char mSelectedFHairColor;
    unsigned char mSelectedFHairPage; // 0 or 1
    unsigned char mSelectedTidBit;
    unsigned char mSelectedTidBitColor;
    unsigned char mSelectedEyeWear;
    unsigned char mSelectedEyeWearColor;
    unsigned char mSelectedCloth;
    unsigned char mSelectedAccessory;
    unsigned char mSelectedAccessoryColor;
    unsigned char mSelectedHat;
    unsigned char mSelectedHatColor;
    unsigned char mSelectedBackground;
    unsigned char mSelectedBackgroundColor;
    unsigned char mSelectedBackgroundPage;

}; // 我想用ZombatarWidget取代TestMenuWidget。






struct ReanimatorTrack {
    int unk;
    char *name;
    ReanimatorTransform *mTransforms;
    int mTransformCount;
    bool IsAttacher;
};

struct ReanimatorFrameTime {
    float mFraction;         // 0
    int mAnimFrameBeforeInt; // 1
    int mAnimFrameAfterInt;  // 2
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

class Attachment;

class ReanimatorTrackInstance {
public:
    int mBlendCounter;                                         // 0
    int mBlendTime;                                            // 1
    ReanimatorTransform mBlendTransform;                       // 2 ~ 13
    float mShakeOverride;                                      // 14
    float mShakeX;                                             // 15
    float mShakeY;                                             // 16
    unsigned short mAttachmentID;                              // 17
    Sexy::Image *mImageOverride;                               // 18
    ReanimatorRenderGroup::ReanimatorRenderGroup mRenderGroup; // 19
    Color mTrackColor;                                         // 20 ~ 23
    bool mIgnoreClipRect;                                      // 96
    bool mTruncateDisappearingFrames;                          // 97
    bool mIgnoreColorOverride;                                 // 98
    bool mIgnoreExtraAdditiveColor;                            // 99
}; // 大小25个整数

class ReanimatorDefinition {
public:
    ReanimatorTrack *mTracks; // 0
    int mTrackCount;          // 1
    float mFPS;               // 2
    int *mReanimAtlas;        // 3
}; // 大小4个整数

class ReanimationParams {
public:
    ReanimationType mReanimationType;
    const char *mReanimFileName;
    int mReanimParamFlags;
};

class TodParticleSystem {
public:
    int *vTable;                                // 0
    int unk1[3];                                // 1 ~ 3
    ParticleEffect::ParticleEffect mEffectType; // 4
    int *mParticleDef;                          // 5
    int *mParticleHolder;                       // 6
    int mEmitterList[4];                        // 7 ~ 10
    bool mDead;                                 // 44
    bool mIsAttachment;                         // 45
    int mRenderOrder;                           // 12
    bool mDontUpdate;                           // 52
    bool mActive;                               // 53
    int mParticleId;                            // 14
}; // 大小15个整数


struct AttachEffect {
    enum EffectType { Particle, Trail, Reanim, Attachment, Other };
    int mEffectID;                // 0
    EffectType mEffectType;       // 1
    SexyTransform2D mOffset;      // 2 ~ 10
    bool mDontDrawIfParentHidden; // 44
    bool mDontPropogateColor;     // 45
}; // 大小12个整数

class Attachment {
public:
    int unk[4];                    // 0 ~ 3
    AttachEffect mEffectArray[16]; // 4 ~ 195
    int mNumEffects;               // 196
    bool mDead;                    //
    bool mActive;
    bool mUsesClipping;
    int mAttachmentID;
}; // 大小199个整数

struct ReanimCacheImageVariation {
    SeedType::SeedType mSeedType;
    DrawVariation::DrawVariation mDrawVariation;
    Sexy::Image *mImage;
};

struct TodListNode_ReanimCacheImageVariation {
    ReanimCacheImageVariation mValue;
    TodListNode_ReanimCacheImageVariation *mNext;
    TodListNode_ReanimCacheImageVariation *mPrev;
};

struct TodAllocator {
    void *mFreeList;
    void *mBlockList;
    int mGrowCount;
    int mTotalItems;
    int mItemSize;
};

struct TodList_ReanimCacheImageVariation {
    TodListNode_ReanimCacheImageVariation *mHead;
    TodListNode_ReanimCacheImageVariation *mTail;
    int mSize;
    TodAllocator *mpAllocator;
};

class ReanimatorCache {
public:
    TodList_ReanimCacheImageVariation mImageVariationList;
    Sexy::MemoryImage *mPlantImages[SeedType::NUM_SEED_TYPES];             // 4 ~ 57
    Sexy::MemoryImage *mLawnMowers[4];                                    // 58 ~ 61
    Sexy::MemoryImage *mZombieImages[ZombieType::NUM_CACHED_ZOMBIE_TYPES]; // 62 ~ 97
    LawnApp *mApp;                                                        // 98
    // 大小99个整数
public:
    void UpdateReanimationForVariation(Reanimation *theReanim, DrawVariation::DrawVariation theDrawVariation);
    void LoadCachedImages();
    Sexy::Image* MakeCachedZombieFrame(ZombieType theZombieType);
};


struct PerfTimer {
    int unk[5];
};

class CreditScreen : public Sexy::Widget {
public:
    enum CreditsPhase {
        CREDITS_MAIN1 = 0,
        CREDITS_MAIN2 = 1,
        CREDITS_MAIN3 = 2,
        CREDITS_END = 3,
    };

public:
    Sexy::ButtonListener mButtonListener; // 64
    LawnApp *mApp;                        // 65
    CreditsPhase mCreditsPhase;           // 66
    int mCreditsPhaseCounter;             // 67
    int mCreditsReanimID;                 // 68
    int mFogParticleID;                   // 69
    int mBlinkCountdown;                  // 70
    Sexy::Widget *mOverlayWidget;         // 71
    bool mDrawBrain;                      // 288
    float mBrainPosX;                     // 73
    float mBrainPosY;                     // 74
    int mUpdateCount;                     // 75
    int mDrawCount;                       // 76
    int unkInt1;                          // 77
    PerfTimer mTimerSinceStart;           // 78 ~ 82
    int unkInt2;                          // 83
    bool mDontSync;                       // 336
    bool mCreditsPaused;                  // 337
    int unkInt3[3];                       // 85 ~ 87
    bool mPreloaded;                      // 352
    int unkInt4;                          // 89
    double mScrollPositionY1;             // 90 ~ 91
    double mScrollPositionY2;             // 92 ~ 93
    bool mIsFromMainMenu;                 // 376,即94

}; // 大小95个整数


class LawnDialog : public Sexy::Dialog {
public:
    LawnApp *mApp; // 184
#ifdef VERSION_111
    int mIsZombie;
#endif
    int mButtonDelay;                 // 185
    Sexy::Widget *mReanimationWidget; // 186
    bool mDrawStandardBack;           // 748
    Sexy::GameButton *mLawnYesButton; // 188
    Sexy::GameButton *mLawnNoButton;  // 189
    bool mTallBottom;                 // 760
    bool mVerticalCenterText;         // 761
    bool unkBool;                     // 762
#ifdef VERSION_111
    int unk2;
#endif
}; // 115: 191, 111: 193

namespace ImageLib {
class Image {
public:
    int *vTable;         // 0
    int mWidth;          // 1
    int mHeight;         // 2
    unsigned int *mBits; // 3
    int *mText1;         // 4
    int *mText2;         // 5
    bool unkBool;        // 24
    int unk1[256];       // 7 ~ 262
    int unkInt;          // 263
}; // 264个整数
} // namespace ImageLib

class TodParticleHolder {};
class TrailHolder {};



class AttachmentHolder {};

class ReanimationHolder;

class EffectSystem {
public:
    TodParticleHolder *mParticleHolder;
    TrailHolder *mTrailHolder;
    ReanimationHolder *mReanimationHolder;
    AttachmentHolder *mAttachmentHolder;
};


namespace Native {
class NativeApp;

class BridgeApp {
public:
    int *mVtable;
    NativeApp *mNativeApp;
};

class AudioOutput {
public:
    Native::NativeApp *mNativeApp;
    JNIEnv *mEnv;
    bool mUnkBool;
};
} // namespace Native

struct TodWeightedGridArray
{
    int mX;
    int mY;
    int mWeight;
};

class TodTriVertex
{
public:
    float                       x;
    float                       y;
    float                       u;
    float                       v;
    unsigned long               color;
};

#define MAX_TRIANGLES 256

class TodTriangleGroup
{
public:
    Sexy::Image*                      mImage;
    TriVertex                   mVertArray[MAX_TRIANGLES][3];
    int                         mTriangleCount;
    int                         mDrawMode;

//    TodTriangleGroup();
//    void                        DrawGroup(Sexy::Graphics* g);
//    void                        AddTriangle(Sexy::Graphics* g, Sexy::Image* theImage, const SexyMatrix3& theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, const Rect& theSrcRect);
};
#endif // PVZ_ENUMS_H
