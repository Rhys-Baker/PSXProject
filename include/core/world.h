#pragma once
#include "bsp.h"


///////////////////////////////////////////////
// BSP Tree Definition and Shape Definitions //
///////////////////////////////////////////////
#pragma region BSPTree
int numTextures = 17;
BSPTextureInfo bspTextureInfo[] = {
    {
        "01F7.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01F1.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "SAVE.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01F5.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01L3.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01L4.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01L1.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01F6.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01DOOR.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01L0.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01F2.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "MISSING.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01F0.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01F8.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01F4.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01L2.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01F3.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
};
BSPNode3 bspNodes_hitscan[] = {
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 0,
        .children = {
            1, 414
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 655360,
        .children = {
            2, 227
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2293760,
        .children = {
            3, 56
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 983040,
        .children = {
            -1, 4
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 327680,
        .children = {
            5, 49
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3604480,
        .children = {
            6, 26
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4259840,
        .children = {
            7, 15
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
        .children = {
            8, 10
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            -1, 9
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4653056,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            -1, 11
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            12, 14
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 13
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3932160,
        .children = {
            16, 21
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            -1, 17
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            18, 20
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 19
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            -1, 22
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            23, 25
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 24
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2949120,
        .children = {
            27, 38
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3276800,
        .children = {
            28, 33
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            -1, 29
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            30, 32
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 31
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            -1, 34
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            35, 37
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 36
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2621440,
        .children = {
            39, 44
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            -1, 40
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            41, 43
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 42
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            -1, 45
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            46, 48
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 47
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            50, 54
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3604480,
        .children = {
            51, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4259840,
        .children = {
            52, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
        .children = {
            53, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4653056,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
        .children = {
            55, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4653056,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 327680,
        .children = {
            57, 156
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 983040,
        .children = {
            58, 112
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 491520,
        .children = {
            59, 83
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            60, 65
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            -1, 61
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1343488,
        .children = {
            -1, 62
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1638400,
        .children = {
            63, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1966080,
        .children = {
            64, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2293760,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1966080,
        .children = {
            66, 75
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 655360,
        .children = {
            67, 70
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            -1, 68
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2260992,
        .children = {
            -1, 69
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 688128,
        .children = {
            71, 73
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            -1, 72
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2293760,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2260992,
        .children = {
            -1, 74
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 688128,
        .children = {
            76, 77
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 655360,
        .children = {
            78, 81
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            -1, 79
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1671168,
        .children = {
            80, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1671168,
        .children = {
            82, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            84, 104
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2260992,
        .children = {
            85, 90
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2293760,
        .children = {
            -1, 86
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 98304,
        .children = {
            87, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            88, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 688128,
        .children = {
            89, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 655360,
        .children = {
            91, 99
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            92, 94
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            -1, 93
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1671168,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1671168,
        .children = {
            95, 97
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 2896,
            .z = 2896
        },
        .distance = 1529251,
        .children = {
            -2, 96
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -2896,
            .z = 2896
        },
        .distance = 1251205,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1638400,
        .children = {
            98, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 98304,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1671168,
        .children = {
            100, 102
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 2896,
            .z = 2896
        },
        .distance = 1529251,
        .children = {
            -2, 101
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -2896,
            .z = 2896
        },
        .distance = 1251205,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1638400,
        .children = {
            103, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 98304,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 655360,
        .children = {
            105, 109
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            -1, 106
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1769472,
        .children = {
            107, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2162688,
        .children = {
            -1, 108
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1769472,
        .children = {
            110, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2162688,
        .children = {
            -1, 111
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            113, 116
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1048576,
        .children = {
            -1, 114
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            115, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 65536,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 983040,
        .children = {
            117, 136
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1638400,
        .children = {
            118, 127
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1966080,
        .children = {
            119, 123
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            120, 122
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 121
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            124, 126
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 125
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1310720,
        .children = {
            128, 132
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            129, 131
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 130
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            133, 135
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 134
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 327680,
        .children = {
            137, 146
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 655360,
        .children = {
            138, 142
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            139, 141
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 140
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            143, 145
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 144
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            147, 151
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            148, 150
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, 149
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 655360,
        .children = {
            152, 154
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            153, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            -1, 155
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1310720,
        .children = {
            157, 203
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1966080,
        .children = {
            158, 181
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2293760,
        .children = {
            159, 166
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            160, 163
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 229376,
        .children = {
            -1, 161
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2326528,
        .children = {
            -1, 162
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1310720,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            -1, 164
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2326528,
        .children = {
            -1, 165
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 688128,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 491520,
        .children = {
            167, 173
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 688128,
        .children = {
            168, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1343488,
        .children = {
            -1, 169
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            170, 172
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1310720,
        .children = {
            -2, 171
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2260992,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1310720,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2260992,
        .children = {
            174, 177
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 32768,
        .children = {
            175, 176
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 98304,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 98304,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            178, 179
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 2896,
            .z = 2896
        },
        .distance = 1529251,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2162688,
        .children = {
            -1, 180
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1638400,
        .children = {
            182, 193
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 491520,
        .children = {
            183, 186
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 688128,
        .children = {
            184, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1310720,
        .children = {
            185, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1343488,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            187, 192
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            188, 190
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1671168,
        .children = {
            189, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -2896,
            .z = 2896
        },
        .distance = 1251205,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -2896,
            .z = 2896
        },
        .distance = 1251205,
        .children = {
            -1, 191
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 2896,
            .z = 0
        },
        .distance = 139022,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 491520,
        .children = {
            194, 197
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 688128,
        .children = {
            195, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1310720,
        .children = {
            196, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1343488,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            198, 201
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            199, 200
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 98304,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 2896,
            .z = 0
        },
        .distance = 139022,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            -1, 202
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            204, 223
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            205, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 655360,
        .children = {
            206, 213
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 983040,
        .children = {
            207, 210
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 688128,
        .children = {
            208, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1310720,
        .children = {
            209, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1343488,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1638400,
        .children = {
            -2, 211
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1310720,
        .children = {
            -2, 212
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 688128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 950272,
        .children = {
            214, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 491520,
        .children = {
            215, 218
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            -2, 216
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            -2, 217
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 982528,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 983040,
        .children = {
            219, 222
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            220, 221
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 98304,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 2896,
            .z = 0
        },
        .distance = 139022,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 983040,
        .children = {
            224, 226
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 196608,
        .children = {
            -1, 225
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2293760,
        .children = {
            228, 324
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1048576,
        .children = {
            229, 246
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            -1, 230
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 0,
        .children = {
            231, 238
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 327680,
        .children = {
            232, 234
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
        .children = {
            233, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4653056,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3604480,
        .children = {
            235, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4259840,
        .children = {
            236, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
        .children = {
            237, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4653056,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -327680,
        .children = {
            239, 243
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3604480,
        .children = {
            240, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4259840,
        .children = {
            241, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
        .children = {
            242, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4653056,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -983040,
        .children = {
            244, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
        .children = {
            245, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4653056,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -983040,
        .children = {
            247, 318
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3604480,
        .children = {
            248, 279
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4259840,
        .children = {
            249, 260
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
        .children = {
            250, 251
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4653056,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            252, 255
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            253, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1092476,
        .children = {
            -2, 254
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1092476,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 327680,
        .children = {
            256, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            257, 258
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, 259
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3932160,
        .children = {
            261, 270
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            262, 265
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            263, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1092476,
        .children = {
            -2, 264
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1092476,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 327680,
        .children = {
            266, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            267, 268
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, 269
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            271, 274
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            272, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1092476,
        .children = {
            -2, 273
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1092476,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 327680,
        .children = {
            275, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            276, 277
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, 278
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2949120,
        .children = {
            280, 299
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3276800,
        .children = {
            281, 290
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            282, 285
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            283, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1092476,
        .children = {
            -2, 284
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1092476,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 327680,
        .children = {
            286, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            287, 288
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, 289
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            291, 294
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            292, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1092476,
        .children = {
            -2, 293
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1092476,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 327680,
        .children = {
            295, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            296, 297
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, 298
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2621440,
        .children = {
            300, 309
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            301, 304
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            302, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1092476,
        .children = {
            -2, 303
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1092476,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 327680,
        .children = {
            305, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            306, 307
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, 308
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            310, 313
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            311, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1092476,
        .children = {
            -2, 312
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1092476,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 327680,
        .children = {
            314, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            315, 316
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, 317
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 327680,
        .children = {
            -1, 319
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1048576,
        .children = {
            320, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3276800,
        .children = {
            321, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3932160,
        .children = {
            322, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4259840,
        .children = {
            323, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 0,
        .children = {
            325, 345
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            -1, 326
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 327680,
        .children = {
            327, 336
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1092476,
        .children = {
            328, 334
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 983040,
        .children = {
            329, 332
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1638400,
        .children = {
            330, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1966080,
        .children = {
            331, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1048576,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 327680,
        .children = {
            -2, 333
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            335, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1048576,
        .children = {
            337, 340
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 196608,
        .children = {
            -2, 338
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 65536,
        .children = {
            -2, 339
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -1, 341
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            342, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 655360,
        .children = {
            343, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            344, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -32768,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -327680,
        .children = {
            346, 357
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1048576,
        .children = {
            347, 352
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            -1, 348
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 163840,
        .children = {
            -2, 349
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -163840,
        .children = {
            350, 351
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -1, 353
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            354, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 655360,
        .children = {
            355, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            356, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -32768,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -983040,
        .children = {
            358, 409
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            359, 369
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1092476,
        .children = {
            360, 367
        }
    },
    {
        .normal = {
            .x = 4095,
            .y = 0,
            .z = 1
        },
        .distance = 1113907,
        .children = {
            -1, 361
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1310720,
        .children = {
            362, 364
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1966080,
        .children = {
            363, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1048576,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 655360,
        .children = {
            -2, 365
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 327680,
        .children = {
            -2, 366
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            368, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 327680,
        .children = {
            370, 407
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 983040,
        .children = {
            371, 374
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1048576,
        .children = {
            -1, 372
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            373, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 65536,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 983040,
        .children = {
            375, 393
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1638400,
        .children = {
            376, 385
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1966080,
        .children = {
            377, 381
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            378, 379
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, 380
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            382, 383
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, 384
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1310720,
        .children = {
            386, 390
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            387, 388
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, 389
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            -2, 391
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            -1, 392
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1158523,
        .children = {
            394, 396
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 327680,
        .children = {
            -2, 395
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            397, 403
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            -1, 398
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 327680,
        .children = {
            399, 402
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 655360,
        .children = {
            400, 401
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = 175851,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 655360,
        .children = {
            404, 405
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            406, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            408, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 327680,
        .children = {
            -1, 410
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1048576,
        .children = {
            411, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 983040,
        .children = {
            -2, 412
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 327680,
        .children = {
            -2, 413
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 655360,
        .children = {
            415, 606
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2293760,
        .children = {
            416, 469
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 983040,
        .children = {
            -1, 417
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -327680,
        .children = {
            418, 425
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            419, 423
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3604480,
        .children = {
            420, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4259840,
        .children = {
            421, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
        .children = {
            422, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4653056,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
        .children = {
            424, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4653056,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3604480,
        .children = {
            426, 446
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4259840,
        .children = {
            427, 435
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
        .children = {
            428, 430
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            429, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4653056,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            431, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            432, 434
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            433, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3932160,
        .children = {
            436, 441
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            437, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            438, 440
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            439, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            442, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            443, 445
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            444, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2949120,
        .children = {
            447, 458
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3276800,
        .children = {
            448, 453
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            449, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            450, 452
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            451, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            454, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            455, 457
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            456, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2621440,
        .children = {
            459, 464
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            460, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            461, 463
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            462, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            465, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            466, 468
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            467, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -327680,
        .children = {
            470, 547
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1638400,
        .children = {
            471, 512
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1966080,
        .children = {
            472, 502
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2293760,
        .children = {
            473, 480
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            474, 477
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -229376,
        .children = {
            475, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2326528,
        .children = {
            -1, 476
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1310720,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
        .children = {
            478, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2326528,
        .children = {
            -1, 479
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 688128,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 491520,
        .children = {
            481, 487
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 688128,
        .children = {
            482, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1343488,
        .children = {
            -1, 483
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
        .children = {
            484, 485
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1310720,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1310720,
        .children = {
            -2, 486
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2260992,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            488, 499
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            489, 498
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2260992,
        .children = {
            490, 491
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 98304,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -262144,
        .children = {
            492, 496
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2228224,
        .children = {
            493, 494
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 2896,
            .z = 2896
        },
        .distance = 1529251,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 2896,
            .z = 2896
        },
        .distance = 1529251,
        .children = {
            -2, 495
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = -2896,
            .z = 0
        },
        .distance = -139022,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2228224,
        .children = {
            -2, 497
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = -2896,
            .z = 0
        },
        .distance = -139022,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 98304,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
        .children = {
            500, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2162688,
        .children = {
            -1, 501
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 491520,
        .children = {
            503, 506
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 688128,
        .children = {
            504, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1310720,
        .children = {
            505, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1343488,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            507, 510
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            508, 509
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = -2896,
            .z = 0
        },
        .distance = -139022,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 98304,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
        .children = {
            511, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1310720,
        .children = {
            513, 523
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 491520,
        .children = {
            514, 517
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 688128,
        .children = {
            515, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1310720,
        .children = {
            516, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1343488,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            518, 521
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            519, 520
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = -2896,
            .z = 0
        },
        .distance = -139022,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 98304,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
        .children = {
            522, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            524, 543
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            525, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 655360,
        .children = {
            526, 533
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 983040,
        .children = {
            527, 530
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 688128,
        .children = {
            528, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1310720,
        .children = {
            529, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1343488,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1638400,
        .children = {
            -2, 531
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1310720,
        .children = {
            -2, 532
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 688128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 950272,
        .children = {
            534, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 491520,
        .children = {
            535, 538
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            -2, 536
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
        .children = {
            537, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 982528,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 983040,
        .children = {
            539, 542
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            540, 541
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = -2896,
            .z = 0
        },
        .distance = -139022,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 98304,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 983040,
        .children = {
            544, 546
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -196608,
        .children = {
            545, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 983040,
        .children = {
            548, 559
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            549, 554
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            550, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1343488,
        .children = {
            -1, 551
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1638400,
        .children = {
            552, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1966080,
        .children = {
            553, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2293760,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            555, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 688128,
        .children = {
            556, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1638400,
        .children = {
            557, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1966080,
        .children = {
            558, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2293760,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 983040,
        .children = {
            560, 583
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1638400,
        .children = {
            561, 572
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1966080,
        .children = {
            562, 567
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            563, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            564, 566
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            565, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            568, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            569, 571
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            570, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1310720,
        .children = {
            573, 578
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            574, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            575, 577
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            576, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            579, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            580, 582
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            581, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 327680,
        .children = {
            584, 595
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 655360,
        .children = {
            585, 590
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            586, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            587, 589
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            588, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            591, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            592, 594
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            593, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            596, 601
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            597, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            598, 600
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            599, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = 1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -655360,
        .children = {
            602, 604
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            -1, 603
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            605, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1158523,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2293760,
        .children = {
            607, 703
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1048576,
        .children = {
            608, 686
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -983040,
        .children = {
            609, 680
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3604480,
        .children = {
            610, 641
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4259840,
        .children = {
            611, 622
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
        .children = {
            612, 613
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4653056,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            614, 619
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -327680,
        .children = {
            -1, 615
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            616, 617
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            618, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            620, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1092476,
        .children = {
            621, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1092476,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3932160,
        .children = {
            623, 632
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            624, 629
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -327680,
        .children = {
            -1, 625
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            626, 627
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            628, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            630, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1092476,
        .children = {
            631, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1092476,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            633, 638
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -327680,
        .children = {
            -1, 634
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            635, 636
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            637, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            639, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1092476,
        .children = {
            640, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1092476,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2949120,
        .children = {
            642, 661
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3276800,
        .children = {
            643, 652
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            644, 649
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -327680,
        .children = {
            -1, 645
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            646, 647
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            648, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            650, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1092476,
        .children = {
            651, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1092476,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            653, 658
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -327680,
        .children = {
            -1, 654
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            655, 656
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            657, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            659, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1092476,
        .children = {
            660, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1092476,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2621440,
        .children = {
            662, 671
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            663, 668
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -327680,
        .children = {
            -1, 664
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            665, 666
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            667, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            669, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1092476,
        .children = {
            670, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1092476,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            672, 677
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -327680,
        .children = {
            -1, 673
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            674, 675
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            676, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            678, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1092476,
        .children = {
            679, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1092476,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -327680,
        .children = {
            681, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1048576,
        .children = {
            682, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3276800,
        .children = {
            683, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3932160,
        .children = {
            684, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4259840,
        .children = {
            685, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            687, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 0,
        .children = {
            688, 695
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 327680,
        .children = {
            689, 691
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
        .children = {
            690, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4653056,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3604480,
        .children = {
            692, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4259840,
        .children = {
            693, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
        .children = {
            694, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4653056,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -327680,
        .children = {
            696, 700
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3604480,
        .children = {
            697, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4259840,
        .children = {
            698, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
        .children = {
            699, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4653056,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -983040,
        .children = {
            701, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4587520,
        .children = {
            702, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4653056,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -327680,
        .children = {
            704, 740
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 0,
        .children = {
            705, 730
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 327680,
        .children = {
            706, 720
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1092476,
        .children = {
            707, 713
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            708, 710
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -327680,
        .children = {
            709, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            711, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -655360,
        .children = {
            712, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -327680,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4095,
            .y = 0,
            .z = 1
        },
        .distance = -1113907,
        .children = {
            714, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 983040,
        .children = {
            715, 718
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1638400,
        .children = {
            716, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1966080,
        .children = {
            717, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1048576,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 327680,
        .children = {
            -2, 719
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1048576,
        .children = {
            721, 726
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -1, 722
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            723, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -655360,
        .children = {
            -2, 724
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            -2, 725
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -32768,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            727, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 983040,
        .children = {
            -2, 728
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 327680,
        .children = {
            -2, 729
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1048576,
        .children = {
            731, 736
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -1, 732
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            733, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -655360,
        .children = {
            -2, 734
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            -2, 735
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -32768,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1114112,
        .children = {
            737, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 983040,
        .children = {
            -2, 738
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 327680,
        .children = {
            -2, 739
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -983040,
        .children = {
            741, 793
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -655360,
        .children = {
            742, 752
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1092476,
        .children = {
            743, 745
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            744, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4095,
            .y = 0,
            .z = -1
        },
        .distance = -1113907,
        .children = {
            746, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 983040,
        .children = {
            747, 750
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1638400,
        .children = {
            748, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1966080,
        .children = {
            749, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1048576,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 327680,
        .children = {
            -2, 751
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -327680,
        .children = {
            753, 755
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            754, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 983040,
        .children = {
            756, 778
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1638400,
        .children = {
            757, 768
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1966080,
        .children = {
            758, 763
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            759, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            760, 761
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            762, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            764, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            765, 766
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            767, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1310720,
        .children = {
            769, 774
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            770, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            771, 772
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            773, -2
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            775, 777
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            -1, 776
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1158523,
        .children = {
            779, 790
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            780, 786
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            -1, 781
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 327680,
        .children = {
            782, 785
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 655360,
        .children = {
            783, 784
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 3663,
            .y = 0,
            .z = -1831
        },
        .distance = -175851,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -655360,
        .children = {
            787, 789
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -917504,
        .children = {
            788, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -983040,
        .children = {
            791, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 327680,
        .children = {
            -2, 792
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -327680,
        .children = {
            794, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1048576,
        .children = {
            795, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 983040,
        .children = {
            -2, 796
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 327680,
        .children = {
            -2, 797
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -2, -1
        }
    },
};
BSPTree3 bsp_hitscan = {.nodes=bspNodes_hitscan, .numNodes = 798};

BSPNode3 bspNodes_player[] = {
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 0,
        .children = {
            1, 981
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 622592,
        .children = {
            2, 491
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 622592,
        .children = {
            3, 186
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2162688,
        .children = {
            4, 67
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            -1, 5
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            6, 9
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1146880,
        .children = {
            -1, 7
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            8, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 950272,
        .children = {
            10, 44
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3473408,
        .children = {
            11, 25
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4128768,
        .children = {
            12, 20
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            13, 18
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            14, 16
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            15, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            17, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            19, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3801088,
        .children = {
            21, 24
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            22, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            -1, 23
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4063232,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2818048,
        .children = {
            26, 34
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3145728,
        .children = {
            27, 31
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            28, 29
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3407872,
        .children = {
            30, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            32, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            -1, 33
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3080192,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2490368,
        .children = {
            35, 39
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2752512,
        .children = {
            36, 37
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            38, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2424832,
        .children = {
            40, 42
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            41, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            43, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3407872,
        .children = {
            45, 56
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4063232,
        .children = {
            46, 54
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            47, 52
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            48, 49
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            -2, 50
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1112182,
        .children = {
            -2, 51
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1112182,
        .children = {
            -2, 53
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1112182,
        .children = {
            -2, 55
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2752512,
        .children = {
            57, 62
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3080192,
        .children = {
            58, 60
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1112182,
        .children = {
            -2, 59
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1112182,
        .children = {
            -2, 61
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2424832,
        .children = {
            63, 65
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1112182,
        .children = {
            -2, 64
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1112182,
        .children = {
            -2, 66
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            68, 117
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            69, 74
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1048576,
        .children = {
            -1, 70
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1638400,
        .children = {
            71, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2293760,
        .children = {
            -1, 72
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            73, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 622592,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 655360,
        .children = {
            -1, 75
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            76, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2326528,
        .children = {
            -1, 77
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1638400,
        .children = {
            78, 114
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 622592,
        .children = {
            79, 81
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1933312,
        .children = {
            80, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2293760,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2293760,
        .children = {
            82, 85
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 655360,
        .children = {
            83, 84
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -32768,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -32768,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 360448,
        .children = {
            -2, 86
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            87, 109
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2228224,
        .children = {
            -2, 88
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 229375,
        .children = {
            89, 91
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1703936,
        .children = {
            90, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 950272,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 688128,
        .children = {
            92, 102
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1736704,
        .children = {
            93, 99
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            94, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2129920,
        .children = {
            95, 97
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 950272,
        .children = {
            -2, 96
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -2896,
            .z = -2896
        },
        .distance = -1413398,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 950272,
        .children = {
            -2, 98
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -2896,
            .z = 2896
        },
        .distance = 1367058,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -32768,
        .children = {
            100, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 950272,
        .children = {
            -2, 101
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -2896,
            .z = 2896
        },
        .distance = 1367058,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1736704,
        .children = {
            103, 107
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            104, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2129920,
        .children = {
            105, 106
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -2896,
            .z = -2896
        },
        .distance = -1413398,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -2896,
            .z = 2896
        },
        .distance = 1367058,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -32768,
        .children = {
            108, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -2896,
            .z = 2896
        },
        .distance = 1367058,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 688128,
        .children = {
            110, 112
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1736704,
        .children = {
            111, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2195456,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1736704,
        .children = {
            113, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2195456,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1605632,
        .children = {
            115, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -32768,
        .children = {
            116, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 622592,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            118, 152
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 950272,
        .children = {
            119, 138
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            120, 131
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1507328,
        .children = {
            121, 128
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2097152,
        .children = {
            122, 125
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -1, 123
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            124, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            126, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1146880,
        .children = {
            -1, 127
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1146880,
        .children = {
            -1, 129
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            130, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 851968,
        .children = {
            132, 135
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1146880,
        .children = {
            -1, 133
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            134, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1146880,
        .children = {
            -1, 136
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            137, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1441792,
        .children = {
            139, 147
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1769472,
        .children = {
            140, 145
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2097152,
        .children = {
            141, 143
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1112182,
        .children = {
            -2, 142
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1112182,
        .children = {
            -2, 144
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1112182,
        .children = {
            -2, 146
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            148, 150
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1112182,
        .children = {
            -2, 149
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1112182,
        .children = {
            -2, 151
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 196608,
        .children = {
            153, 159
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 950272,
        .children = {
            154, 157
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1146880,
        .children = {
            -1, 155
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            156, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1112182,
        .children = {
            -2, 158
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            160, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 950272,
        .children = {
            161, 172
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1146880,
        .children = {
            -1, 162
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            163, 168
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            164, 166
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            165, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            -1, 167
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1131034,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -2, 169
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            170, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, 171
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1204864,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            173, 183
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            174, 181
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 688128,
        .children = {
            175, 178
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1204864,
        .children = {
            -2, 176
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1112182,
        .children = {
            -2, 177
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 950272,
        .children = {
            -2, 179
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            180, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 688128,
        .children = {
            182, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1204864,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            184, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            185, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = 1112182,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -294912,
        .children = {
            187, 323
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 163840,
        .children = {
            188, 282
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2162688,
        .children = {
            189, 234
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1146880,
        .children = {
            -1, 190
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 950272,
        .children = {
            191, 232
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            192, 203
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            193, 194
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            195, 199
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            196, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            197, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            198, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            200, 202
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            -2, 201
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1053918,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            204, 225
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3080192,
        .children = {
            205, 212
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3735552,
        .children = {
            206, 209
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            207, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -1, 208
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4063232,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            210, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -1, 211
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3407872,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2424832,
        .children = {
            213, 222
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2490368,
        .children = {
            214, 219
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            215, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            216, 217
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2752512,
        .children = {
            218, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            220, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            221, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            223, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            224, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            226, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1053918,
        .children = {
            227, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2424832,
        .children = {
            228, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2752512,
        .children = {
            229, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3407872,
        .children = {
            230, 231
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4063232,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3080192,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            233, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1146880,
        .children = {
            -1, 235
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            236, 268
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 229376,
        .children = {
            237, 260
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            238, 244
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            239, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1507328,
        .children = {
            240, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2097152,
        .children = {
            241, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            242, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            243, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 196608,
        .children = {
            -2, 245
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            246, 254
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -2, 247
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            248, 251
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            249, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, 250
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1131034,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            252, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, 253
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -2, 255
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -2, 256
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -163840,
        .children = {
            257, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -65536,
        .children = {
            -2, 258
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            259, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
        .children = {
            -2, 261
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -2, 262
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 65536,
        .children = {
            -2, 263
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -2, 264
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -65536,
        .children = {
            -2, 265
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -163840,
        .children = {
            266, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            267, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            269, 279
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 950272,
        .children = {
            270, 277
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            271, 272
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1053918,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 196608,
        .children = {
            273, 274
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1053918,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            275, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            276, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = 1053918,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            278, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -1, 280
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -163840,
        .children = {
            -2, 281
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2162688,
        .children = {
            283, 300
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1146880,
        .children = {
            -1, 284
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -32768,
        .children = {
            285, 292
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            286, 290
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3735552,
        .children = {
            287, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            288, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            289, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            291, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            293, 298
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3407872,
        .children = {
            294, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4063232,
        .children = {
            295, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            296, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            297, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            299, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1146880,
        .children = {
            -1, 301
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            302, 321
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 32768,
        .children = {
            303, 309
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -2, 304
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 0,
        .children = {
            -2, 305
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -65536,
        .children = {
            -2, 306
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, 307
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -1, 308
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -163840,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -32768,
        .children = {
            310, 316
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            -2, 311
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -2, 312
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -65536,
        .children = {
            -2, 313
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, 314
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -1, 315
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -163840,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 458752,
        .children = {
            -2, 317
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 294912,
        .children = {
            -2, 318
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, 319
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -1, 320
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -163840,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -1, 322
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2162688,
        .children = {
            324, 394
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            325, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1146880,
        .children = {
            -1, 326
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2490368,
        .children = {
            327, 384
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            328, 349
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            329, 347
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            330, 335
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            331, 332
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            333, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            -2, 334
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3145728,
        .children = {
            336, 342
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4063231,
        .children = {
            337, 339
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            -2, 338
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            -2, 340
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -1, 341
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3473409,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2818048,
        .children = {
            343, 345
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            -2, 344
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            -2, 346
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            348, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            350, 361
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            351, 352
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 950272,
        .children = {
            353, 356
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            -2, 354
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            355, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1053918,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            357, 358
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            -2, 359
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
        .children = {
            -2, 360
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            362, 368
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 950272,
        .children = {
            363, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1053918,
        .children = {
            364, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2818049,
        .children = {
            365, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4063231,
        .children = {
            -2, 366
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3473409,
        .children = {
            -2, 367
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3145728,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3145728,
        .children = {
            369, 378
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 950272,
        .children = {
            -2, 370
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3801088,
        .children = {
            371, 373
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
        .children = {
            -2, 372
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3735552,
        .children = {
            374, 376
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
        .children = {
            -2, 375
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
        .children = {
            -2, 377
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 950272,
        .children = {
            -2, 379
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3080192,
        .children = {
            380, 382
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
        .children = {
            -2, 381
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
        .children = {
            -2, 383
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            385, 388
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            386, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            387, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 950272,
        .children = {
            389, 391
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            390, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1053918,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            -1, 392
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
        .children = {
            -2, 393
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            395, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1146880,
        .children = {
            -1, 396
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            397, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 950272,
        .children = {
            398, 456
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            399, 418
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1053918,
        .children = {
            400, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            401, 410
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1441792,
        .children = {
            402, 409
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1769472,
        .children = {
            403, 407
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            404, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2097152,
        .children = {
            405, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            406, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            408, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1507328,
        .children = {
            411, 414
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1835008,
        .children = {
            -2, 412
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            413, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1769472,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            415, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            416, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1441792,
        .children = {
            417, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            419, 437
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 786432,
        .children = {
            420, 422
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            -2, 421
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1053918,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 458752,
        .children = {
            423, 425
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            -2, 424
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1053918,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            426, 432
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            427, 429
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            -2, 428
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1053918,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            430, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            431, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            433, 436
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1131034,
        .children = {
            -2, 434
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            435, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1053918,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1131034,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 196608,
        .children = {
            438, 446
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 786432,
        .children = {
            439, 441
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            440, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 458752,
        .children = {
            442, 444
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            443, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            445, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1015808,
        .children = {
            447, 452
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            448, 450
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            -2, 449
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 1081344,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            451, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = 1131034,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -2, 453
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            -2, 454
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, 455
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1204864,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            457, 458
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 851968,
        .children = {
            459, 472
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1507328,
        .children = {
            460, 465
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1835008,
        .children = {
            461, 463
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
        .children = {
            -2, 462
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
        .children = {
            -2, 464
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            466, 468
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
        .children = {
            -2, 467
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 720896,
        .children = {
            469, 470
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            471, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 196608,
        .children = {
            473, 482
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            474, 478
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 720896,
        .children = {
            475, 476
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            477, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 720896,
        .children = {
            479, 480
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            481, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            483, 487
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 720896,
        .children = {
            484, 485
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            486, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1112182,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            -2, 488
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, 489
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 688128,
        .children = {
            490, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = 1204864,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 622592,
        .children = {
            492, 768
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2162688,
        .children = {
            493, 501
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            -1, 494
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            495, 499
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3407872,
        .children = {
            496, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            497, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            498, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            500, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1277952,
        .children = {
            502, 683
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1474560,
        .children = {
            -1, 503
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            504, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1933312,
        .children = {
            505, 587
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2326528,
        .children = {
            506, 513
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 950272,
        .children = {
            507, 510
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 262144,
        .children = {
            -1, 508
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2359296,
        .children = {
            -1, 509
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1441792,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 229376,
        .children = {
            -1, 511
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2359296,
        .children = {
            -1, 512
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 557056,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 360448,
        .children = {
            514, 550
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            515, 530
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 884736,
        .children = {
            516, 520
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1998848,
        .children = {
            517, 519
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            518, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 393216,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 393216,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 622592,
        .children = {
            521, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1998848,
        .children = {
            522, 527
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            523, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2293760,
        .children = {
            524, 525
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 393216,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 393216,
        .children = {
            526, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 655360,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            528, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 393216,
        .children = {
            529, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 655360,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 950272,
        .children = {
            531, 540
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1998848,
        .children = {
            532, 539
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2228224,
        .children = {
            533, 538
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 262144,
        .children = {
            -2, 534
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1441792,
        .children = {
            -2, 535
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -2, 536
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 163840,
        .children = {
            -2, 537
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2260992,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 622592,
        .children = {
            541, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 32768,
        .children = {
            542, 548
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2228224,
        .children = {
            543, 547
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 229376,
        .children = {
            -2, 544
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
        .children = {
            545, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2260992,
        .children = {
            -2, 546
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 163840,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
        .children = {
            549, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2260992,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 32768,
        .children = {
            551, 573
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2293760,
        .children = {
            552, 555
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 327680,
        .children = {
            553, 554
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -32768,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -32768,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 229375,
        .children = {
            556, 559
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 327680,
        .children = {
            557, 558
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2228224,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2228224,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2228224,
        .children = {
            560, 561
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            562, 564
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2129920,
        .children = {
            563, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -2896,
            .z = -2896
        },
        .distance = -1413398,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2129920,
        .children = {
            565, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            566, 568
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2195456,
        .children = {
            567, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            569, 571
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2195456,
        .children = {
            570, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2195456,
        .children = {
            572, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1998848,
        .children = {
            574, 586
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2228224,
        .children = {
            575, 579
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 229375,
        .children = {
            -2, 576
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            577, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -32768,
        .children = {
            -2, 578
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2293760,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            580, 583
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2129920,
        .children = {
            581, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 229375,
        .children = {
            -1, 582
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -2896,
            .z = -2896
        },
        .distance = -1413398,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2129920,
        .children = {
            584, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2195456,
        .children = {
            585, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1146880,
        .children = {
            588, 603
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1605632,
        .children = {
            589, 593
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            590, 591
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 393216,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -2, 592
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 393216,
        .children = {
            -1, 594
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 32768,
        .children = {
            595, 602
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1343488,
        .children = {
            596, 599
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            -2, 597
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            -2, 598
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            -2, 600
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            -2, 601
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 884736,
        .children = {
            604, 609
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1605632,
        .children = {
            605, 607
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            606, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 393216,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            608, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 393216,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 360448,
        .children = {
            610, 641
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 32768,
        .children = {
            611, 638
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 262144,
        .children = {
            612, 637
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1343488,
        .children = {
            613, 630
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            614, 629
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
        .children = {
            615, 616
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 393216,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1605632,
        .children = {
            617, 626
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1703936,
        .children = {
            618, 622
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 557056,
        .children = {
            619, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            620, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 393216,
        .children = {
            621, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 655360,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 393216,
        .children = {
            623, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 655360,
        .children = {
            -1, 624
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 622592,
        .children = {
            625, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1638400,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            627, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 393216,
        .children = {
            -1, 628
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 557056,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            631, 633
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 393216,
        .children = {
            -1, 632
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 557056,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 557056,
        .children = {
            634, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 622592,
        .children = {
            635, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
        .children = {
            636, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1605632,
        .children = {
            639, 640
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 163840,
        .children = {
            642, 682
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            643, 677
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1343488,
        .children = {
            644, 669
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1802240,
        .children = {
            645, 646
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1703936,
        .children = {
            647, 654
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            648, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            649, 652
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            650, 651
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -2896,
            .z = 2896
        },
        .distance = 1367058,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -2896,
            .z = 2896
        },
        .distance = 1367059,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -2896,
            .z = 2896
        },
        .distance = 1367059,
        .children = {
            -1, 653
        }
    },
    {
        .normal = {
            .x = -2896,
            .y = -2896,
            .z = 0
        },
        .distance = -23170,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            655, 659
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1605632,
        .children = {
            656, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 229375,
        .children = {
            -2, 657
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -32768,
        .children = {
            -2, 658
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1638400,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
        .children = {
            660, 662
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            -2, 661
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = -2896,
            .y = -2896,
            .z = 0
        },
        .distance = -23170,
        .children = {
            663, 664
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -2896,
            .z = 2896
        },
        .distance = 1367059,
        .children = {
            -2, 665
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 229376,
        .children = {
            666, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1605632,
        .children = {
            -2, 667
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -32768,
        .children = {
            -2, 668
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 327680,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 262144,
        .children = {
            670, 674
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            -1, 671
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 229375,
        .children = {
            -2, 672
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -32768,
        .children = {
            -2, 673
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 327680,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            675, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 229375,
        .children = {
            -1, 676
        }
    },
    {
        .normal = {
            .x = -2896,
            .y = -2896,
            .z = 0
        },
        .distance = -23170,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 229376,
        .children = {
            678, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1605632,
        .children = {
            679, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            680, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            681, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1736704,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            684, 762
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1146880,
        .children = {
            685, 703
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 32768,
        .children = {
            686, 697
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2097152,
        .children = {
            687, 688
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1769472,
        .children = {
            689, 690
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1474560,
        .children = {
            691, 692
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            693, 696
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            694, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            695, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 393216,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1507328,
        .children = {
            698, 699
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            700, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 950272,
        .children = {
            701, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            702, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1474560,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            704, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            705, 709
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            706, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 950272,
        .children = {
            707, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            708, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 393216,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            710, 724
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            711, 716
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 950272,
        .children = {
            712, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 393216,
        .children = {
            713, 714
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            715, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 557056,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 262144,
        .children = {
            717, 723
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 950272,
        .children = {
            718, 721
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            -2, 719
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 622592,
        .children = {
            720, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            -2, 722
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            725, 731
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 196608,
        .children = {
            726, 727
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            -1, 728
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -2, 729
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 950272,
        .children = {
            730, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            732, 759
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 262144,
        .children = {
            733, 744
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 950272,
        .children = {
            734, 738
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 196608,
        .children = {
            -2, 735
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            736, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -32768,
        .children = {
            -2, 737
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 327680,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 196608,
        .children = {
            739, 741
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            -2, 740
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            742, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            -2, 743
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            745, 758
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 360448,
        .children = {
            746, 749
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            -2, 747
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 949760,
        .children = {
            -2, 748
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 163840,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 950272,
        .children = {
            750, 756
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            751, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 163840,
        .children = {
            752, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 229375,
        .children = {
            753, 754
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            755, -2
        }
    },
    {
        .normal = {
            .x = -2896,
            .y = -2896,
            .z = 0
        },
        .distance = -23170,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            757, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 163840,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 950272,
        .children = {
            760, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            761, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 229376,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            763, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            764, 765
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            766, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 32768,
        .children = {
            -1, 767
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -294912,
        .children = {
            769, 863
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            770, 819
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 32768,
        .children = {
            771, 800
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            772, 781
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            773, 777
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            774, 776
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            775, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            778, 780
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            779, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            782, 791
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            783, 787
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            784, 786
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            785, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            788, 790
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            789, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            792, 796
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            793, 795
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            794, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            797, 799
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            798, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            801, 810
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -32768,
        .children = {
            802, 806
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            803, 805
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            804, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            807, 809
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            808, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -32768,
        .children = {
            811, 815
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            812, 814
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            813, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            816, 818
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            817, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 32768,
        .children = {
            820, 844
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            821, 828
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
        .children = {
            822, 824
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            823, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            825, 827
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            826, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 32768,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            829, 835
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
        .children = {
            830, 832
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            831, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            833, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 32768,
        .children = {
            834, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 32768,
        .children = {
            836, 840
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            837, 839
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            838, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            841, 843
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            842, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -32768,
        .children = {
            845, 854
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 32768,
        .children = {
            846, 850
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            847, 849
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            848, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            851, 853
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            852, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 32768,
        .children = {
            855, 859
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            856, 858
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            857, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            860, 862
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            861, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2162688,
        .children = {
            864, 923
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1081344,
        .children = {
            865, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2490368,
        .children = {
            866, 918
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            867, 869
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            868, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3801088,
        .children = {
            870, 891
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            871, 873
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            872, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 32768,
        .children = {
            874, 889
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            875, 881
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            876, 880
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            -2, 877
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            878, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            -2, 879
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            882, 883
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            884, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4063232,
        .children = {
            885, 887
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            886, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            888, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            890, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 32768,
        .children = {
            892, 917
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3080192,
        .children = {
            893, 913
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3735552,
        .children = {
            894, 899
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            895, 896
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            897, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            898, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3407872,
        .children = {
            900, 905
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            901, 902
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            903, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            904, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            906, 907
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            908, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3145728,
        .children = {
            909, 911
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            910, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            912, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            914, 915
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            916, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            919, 921
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            920, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            922, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1081344,
        .children = {
            924, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            925, 953
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 32768,
        .children = {
            926, 952
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, 927
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1507328,
        .children = {
            928, 937
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1835008,
        .children = {
            929, 933
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            930, 931
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            932, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            934, 935
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            936, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            938, 942
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            939, 940
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            941, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 851968,
        .children = {
            943, 947
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            944, 945
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            946, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            948, 951
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            -2, 949
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, 950
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            954, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 196608,
        .children = {
            955, 960
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            956, 958
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            957, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            959, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            961, 962
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 32768,
        .children = {
            963, 976
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            964, 974
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 294912,
        .children = {
            965, 971
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            966, 968
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            967, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            -2, 969
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            970, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            972, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            973, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = 360448,
        .children = {
            -1, 975
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            977, 980
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            978, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            979, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -622592,
        .children = {
            982, 1395
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 622592,
        .children = {
            983, 1217
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2162688,
        .children = {
            984, 993
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            -1, 985
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            986, 991
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3407872,
        .children = {
            987, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4063232,
        .children = {
            988, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            989, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            990, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            992, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            994, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            995, 1213
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1474560,
        .children = {
            996, 997
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1343488,
        .children = {
            998, 1128
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -393216,
        .children = {
            999, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1998848,
        .children = {
            1000, 1072
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2326528,
        .children = {
            1001, 1008
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 950272,
        .children = {
            1002, 1005
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -262144,
        .children = {
            1003, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2359296,
        .children = {
            -1, 1004
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1441792,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -229376,
        .children = {
            1006, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2359296,
        .children = {
            -1, 1007
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 557056,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            1009, 1070
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            1010, 1068
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 950272,
        .children = {
            1011, 1023
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -32768,
        .children = {
            1012, 1015
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1441792,
        .children = {
            -2, 1013
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -2, 1014
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2260992,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            1016, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2228224,
        .children = {
            1017, 1022
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -262144,
        .children = {
            1018, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1441792,
        .children = {
            -2, 1019
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -2, 1020
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -163840,
        .children = {
            1021, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2260992,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 622592,
        .children = {
            1024, 1031
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            1025, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2228224,
        .children = {
            1026, 1030
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -229376,
        .children = {
            1027, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
        .children = {
            1028, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2260992,
        .children = {
            -2, 1029
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -163840,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -327680,
        .children = {
            1032, 1065
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 557056,
        .children = {
            -2, 1033
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2293760,
        .children = {
            1034, 1035
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -32768,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 229375,
        .children = {
            1036, 1043
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -229376,
        .children = {
            1037, 1039
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 360448,
        .children = {
            -2, 1038
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2228224,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2228224,
        .children = {
            -2, 1040
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 360448,
        .children = {
            -2, 1041
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -262144,
        .children = {
            1042, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2195456,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -229376,
        .children = {
            1044, 1054
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2260992,
        .children = {
            -2, 1045
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1046, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2228224,
        .children = {
            -2, 1047
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2129920,
        .children = {
            1048, 1052
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -163840,
        .children = {
            1049, 1050
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -2896,
            .z = -2896
        },
        .distance = -1413398,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -2896,
            .z = -2896
        },
        .distance = -1413398,
        .children = {
            1051, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = -2896,
            .z = 0
        },
        .distance = -23170,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -163840,
        .children = {
            -1, 1053
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = -2896,
            .z = 0
        },
        .distance = -23170,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -32768,
        .children = {
            1055, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2260992,
        .children = {
            -2, 1056
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            1057, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2228224,
        .children = {
            -2, 1058
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2129920,
        .children = {
            1059, 1063
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -262144,
        .children = {
            1060, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2195456,
        .children = {
            -2, 1061
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -2896,
            .z = -2896
        },
        .distance = -1413398,
        .children = {
            1062, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = -2896,
            .z = 0
        },
        .distance = -23170,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -262144,
        .children = {
            1064, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = -2896,
            .z = 0
        },
        .distance = -23170,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 557056,
        .children = {
            -2, 1066
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 360448,
        .children = {
            -2, 1067
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -32768,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -229376,
        .children = {
            1069, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 2195456,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 884736,
        .children = {
            -2, 1071
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 557056,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 884736,
        .children = {
            1073, 1080
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1605632,
        .children = {
            1074, 1078
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -32768,
        .children = {
            1075, 1076
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            1077, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            1079, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 360448,
        .children = {
            1081, 1105
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1605632,
        .children = {
            1082, 1099
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -32768,
        .children = {
            1083, 1086
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1933312,
        .children = {
            1084, 1085
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1671168,
        .children = {
            1087, 1092
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            1088, 1091
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 557056,
        .children = {
            1089, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
        .children = {
            1090, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 557056,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            1093, 1095
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 622592,
        .children = {
            1094, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
        .children = {
            -2, 1096
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 622592,
        .children = {
            -2, 1097
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 557056,
        .children = {
            -2, 1098
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            1100, 1104
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 557056,
        .children = {
            1101, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 622592,
        .children = {
            1102, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            1103, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 557056,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1671168,
        .children = {
            1106, 1117
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            1107, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1108, 1112
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -262144,
        .children = {
            1109, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -163840,
        .children = {
            -1, 1110
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 229375,
        .children = {
            -1, 1111
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = -2896,
            .z = 0
        },
        .distance = -23170,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -229376,
        .children = {
            -2, 1113
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            1114, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, 1115
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -32768,
        .children = {
            -2, 1116
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -327680,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            1118, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1119, 1123
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -262144,
        .children = {
            1120, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -163840,
        .children = {
            -1, 1121
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 229375,
        .children = {
            -1, 1122
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = -2896,
            .z = 0
        },
        .distance = -23170,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -229376,
        .children = {
            -2, 1124
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            1125, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, 1126
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -32768,
        .children = {
            -2, 1127
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -327680,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 819200,
        .children = {
            1129, 1145
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1277952,
        .children = {
            1130, 1133
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -393216,
        .children = {
            1131, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            1132, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            1134, 1135
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            1136, 1139
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            1137, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            -2, 1138
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -393216,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 950272,
        .children = {
            1140, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            1141, 1143
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -393216,
        .children = {
            -2, 1142
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -393216,
        .children = {
            -2, 1144
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -32768,
        .children = {
            1146, 1155
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1277952,
        .children = {
            1147, 1149
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1148, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 360448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1150, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 360448,
        .children = {
            1151, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1048576,
        .children = {
            -2, 1152
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 786432,
        .children = {
            -2, 1153
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            -2, 1154
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 949760,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            1156, 1199
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 786432,
        .children = {
            -2, 1157
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 360448,
        .children = {
            1158, 1172
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            -2, 1159
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -262144,
        .children = {
            1160, 1164
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            -2, 1161
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            1162, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 949760,
        .children = {
            -2, 1163
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -163840,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            -2, 1165
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 458752,
        .children = {
            1166, 1169
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 950272,
        .children = {
            -2, 1167
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            1168, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 950272,
        .children = {
            -2, 1170
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            1171, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 950272,
        .children = {
            1173, 1193
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            1174, 1189
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -229376,
        .children = {
            1175, 1179
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1176, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -163840,
        .children = {
            -1, 1177
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            1178, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = -2896,
            .z = 0
        },
        .distance = -23170,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -262144,
        .children = {
            1180, 1185
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1181, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 229375,
        .children = {
            1182, 1183
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            1184, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = -2896,
            .z = 0
        },
        .distance = -23170,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            1186, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 229375,
        .children = {
            -2, 1187
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -32768,
        .children = {
            -2, 1188
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -327680,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1277952,
        .children = {
            1190, 1191
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -229376,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            1192, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -229376,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            1194, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            1195, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -163840,
        .children = {
            1196, 1197
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1198, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 917504,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 458752,
        .children = {
            1200, 1209
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 786432,
        .children = {
            1201, 1204
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 950272,
        .children = {
            1202, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            1203, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -393216,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 950272,
        .children = {
            1205, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -393216,
        .children = {
            1206, 1208
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            1207, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 557056,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            -1, 1210
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -2, 1211
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 950272,
        .children = {
            1212, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1214, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            1215, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            -1, 1216
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -294912,
        .children = {
            1218, 1278
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            1219, 1242
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            1220, 1233
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            1221, 1228
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
        .children = {
            1222, 1224
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            1223, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -2, 1225
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            1226, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -32768,
        .children = {
            -2, 1227
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
        .children = {
            1229, 1231
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            1230, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -2, 1232
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -32768,
        .children = {
            1234, 1238
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1235, 1237
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            1236, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1239, 1241
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            1240, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            1243, 1264
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            1244, 1255
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            1245, 1250
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
        .children = {
            1246, 1248
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            1247, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, 1249
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 262144,
        .children = {
            1251, 1253
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            1252, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -2, 1254
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            1256, 1260
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1257, 1259
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            1258, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1261, 1263
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            1262, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 32768,
        .children = {
            1265, 1269
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1266, 1268
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            1267, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            1270, 1274
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1271, 1273
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            1272, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1275, 1277
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            1276, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2162688,
        .children = {
            1279, 1335
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1081344,
        .children = {
            1280, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3145728,
        .children = {
            1281, 1312
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3801088,
        .children = {
            1282, 1303
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            1283, 1294
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            1284, 1286
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            1285, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            1287, 1293
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            1288, 1289
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            1290, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            1291, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            1292, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, 1295
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            1296, 1297
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            -2, 1298
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4128768,
        .children = {
            1299, 1301
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            -2, 1300
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, 1302
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, 1304
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            1305, 1306
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            -2, 1307
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3473408,
        .children = {
            1308, 1310
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, 1309
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            -2, 1311
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2490368,
        .children = {
            1313, 1327
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2818048,
        .children = {
            1314, 1321
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            1315, 1317
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            -1, 1316
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -32768,
        .children = {
            -2, 1318
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            -2, 1319
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            -2, 1320
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            1322, 1324
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            -1, 1323
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -32768,
        .children = {
            -2, 1325
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            -2, 1326
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -32768,
        .children = {
            1328, 1329
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, 1330
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            1331, 1334
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            1332, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            1333, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1081344,
        .children = {
            1336, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 196608,
        .children = {
            1337, 1379
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, 1338
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            1339, 1362
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1769472,
        .children = {
            1340, 1350
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1835008,
        .children = {
            1341, 1345
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            1342, 1344
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            1343, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            1346, 1349
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            1347, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            1348, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -32768,
        .children = {
            1351, 1352
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1507328,
        .children = {
            1353, 1358
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            1354, 1357
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            1355, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            1356, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            1359, 1361
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            1360, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            1363, 1372
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 851968,
        .children = {
            1364, 1368
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            1365, 1367
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            1366, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            1369, 1371
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            1370, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -32768,
        .children = {
            1373, 1374
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            1375, 1376
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            -2, 1377
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, 1378
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            1380, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1381, 1387
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, 1382
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            1383, 1384
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            -2, 1385
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            -2, 1386
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            -2, 1388
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            1389, 1393
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -294912,
        .children = {
            -2, 1390
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -950272,
        .children = {
            -2, 1391
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, 1392
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -360448,
        .children = {
            1394, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 622592,
        .children = {
            1396, 1529
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2162688,
        .children = {
            1397, 1453
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            -1, 1398
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            1399, 1450
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3473408,
        .children = {
            1400, 1425
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4128768,
        .children = {
            1401, 1413
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            1402, 1403
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -950272,
        .children = {
            1404, 1410
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            1405, 1408
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            -2, 1406
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            1407, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            1409, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            -2, 1411
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            -2, 1412
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -950272,
        .children = {
            1414, 1422
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4063232,
        .children = {
            1415, 1417
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            1416, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3735552,
        .children = {
            1418, 1420
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            1419, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            1421, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3801088,
        .children = {
            1423, 1424
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -950272,
        .children = {
            1426, 1440
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3080192,
        .children = {
            1427, 1432
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3407872,
        .children = {
            1428, 1430
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            1429, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            1431, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2752512,
        .children = {
            1433, 1435
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            1434, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2424832,
        .children = {
            1436, 1438
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            1437, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            1439, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2490368,
        .children = {
            1441, 1448
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2818048,
        .children = {
            1442, 1446
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3145728,
        .children = {
            1443, 1445
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            1444, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            -2, 1447
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            -2, 1449
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1146880,
        .children = {
            1451, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            1452, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 1015808,
        .children = {
            -1, 1454
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 851968,
        .children = {
            1455, 1486
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -950272,
        .children = {
            1456, 1470
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1769472,
        .children = {
            1457, 1462
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2097152,
        .children = {
            1458, 1460
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            1459, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            1461, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1441792,
        .children = {
            1463, 1465
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            1464, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1114112,
        .children = {
            1466, 1468
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            1467, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            1469, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            1471, 1483
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1507328,
        .children = {
            1472, 1480
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1146880,
        .children = {
            1473, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1835008,
        .children = {
            1474, 1478
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            1475, 1476
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            -2, 1477
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2097152,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            1479, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1146880,
        .children = {
            1481, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            -2, 1482
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1146880,
        .children = {
            1484, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            -2, 1485
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            1487, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 196608,
        .children = {
            1488, 1511
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            1489, 1500
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -720896,
        .children = {
            1490, 1495
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 786432,
        .children = {
            1491, 1493
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            1492, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            1494, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -950272,
        .children = {
            1496, 1497
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1146880,
        .children = {
            1498, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            -2, 1499
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -720896,
        .children = {
            1501, 1506
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 458752,
        .children = {
            1502, 1504
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            1503, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            1505, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -950272,
        .children = {
            1507, 1508
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1146880,
        .children = {
            1509, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            -2, 1510
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -950272,
        .children = {
            1512, 1519
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1513, 1515
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1112182,
        .children = {
            1514, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 884736,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            1516, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, 1517
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -688128,
        .children = {
            -2, 1518
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1204864,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1146880,
        .children = {
            1520, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 688128,
        .children = {
            1521, 1525
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            1522, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -2, 1523
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, 1524
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = -2896
        },
        .distance = -1204864,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            -2, 1526
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -2, 1527
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, 1528
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1131034,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -294912,
        .children = {
            1530, 1623
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2162688,
        .children = {
            1531, 1570
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1146880,
        .children = {
            1532, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            1533, 1542
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2490368,
        .children = {
            1534, 1541
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            1535, 1536
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1053918,
        .children = {
            -1, 1537
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4128768,
        .children = {
            -2, 1538
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3145728,
        .children = {
            1539, 1540
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3473408,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2818048,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1053918,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3473408,
        .children = {
            1543, 1554
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -32768,
        .children = {
            1544, 1551
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4128768,
        .children = {
            1545, 1550
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            1546, 1548
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            1547, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            1549, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4128768,
        .children = {
            1552, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            1553, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 32768,
        .children = {
            1555, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3080192,
        .children = {
            1556, 1564
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            1557, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3407872,
        .children = {
            1558, 1560
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            -2, 1559
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            1561, 1563
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            1562, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3145728,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2490368,
        .children = {
            1565, 1568
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            1566, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            1567, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2818048,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            1569, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1146880,
        .children = {
            1571, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            1572, 1594
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -32768,
        .children = {
            1573, 1593
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            1574, 1588
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1507328,
        .children = {
            1575, 1586
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 32768,
        .children = {
            1576, 1583
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            1577, 1579
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2097152,
        .children = {
            -1, 1578
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1053918,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            1580, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1835008,
        .children = {
            1581, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2097152,
        .children = {
            1582, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1835008,
        .children = {
            1584, 1585
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            1587, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1053918,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 851968,
        .children = {
            1589, 1591
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            1590, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1053918,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            1592, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1053918,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            1595, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 196608,
        .children = {
            1596, 1600
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -32768,
        .children = {
            1597, 1599
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            1598, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1053918,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 32768,
        .children = {
            1601, 1618
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -950272,
        .children = {
            1602, 1603
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 360448,
        .children = {
            1604, 1609
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            1605, 1608
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1131034,
        .children = {
            1606, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1607, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1053918,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1131034,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1610, 1612
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            1611, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = -803
        },
        .distance = -1053918,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            -2, 1613
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            1614, 1617
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = 294912,
        .children = {
            -2, 1615
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, 1616
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -163840,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            1619, 1620
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, 1621
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            1622, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -163840,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2162688,
        .children = {
            1624, 1698
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            1625, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2490368,
        .children = {
            1626, 1687
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1146880,
        .children = {
            1627, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            1628, 1657
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            1629, 1635
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            1630, 1631
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4128768,
        .children = {
            1632, 1633
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1053918,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1053918,
        .children = {
            -1, 1634
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2818048,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3145728,
        .children = {
            1636, 1651
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4390912,
        .children = {
            1637, 1643
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            1638, 1639
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -950272,
        .children = {
            1640, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
        .children = {
            1641, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            1642, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3801088,
        .children = {
            1644, 1649
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -950272,
        .children = {
            1645, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -720896,
        .children = {
            1646, 1648
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            1647, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
        .children = {
            1650, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2818048,
        .children = {
            1652, 1654
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
        .children = {
            1653, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -950272,
        .children = {
            1655, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
        .children = {
            1656, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3473408,
        .children = {
            1658, 1674
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4128768,
        .children = {
            1659, 1665
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4456448,
        .children = {
            1660, 1662
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4718592,
        .children = {
            1661, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 4784128,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            1663, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            -2, 1664
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3801088,
        .children = {
            1666, 1670
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            1667, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            1668, 1669
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            1671, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            1672, 1673
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2818048,
        .children = {
            1675, 1684
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 3145728,
        .children = {
            1676, 1680
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            1677, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            1678, 1679
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            1681, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            1682, 1683
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            1685, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            -2, 1686
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            1688, 1694
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -950272,
        .children = {
            1689, 1692
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            -1, 1690
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
        .children = {
            1691, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            1693, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1053918,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            1695, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1146880,
        .children = {
            1696, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            -2, 1697
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -1015808,
        .children = {
            1699, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1146880,
        .children = {
            1700, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 851968,
        .children = {
            1701, 1734
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1179648,
        .children = {
            1702, 1723
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            1703, 1717
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -950272,
        .children = {
            1704, 1713
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            -1, 1705
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1835008,
        .children = {
            1706, 1708
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
        .children = {
            1707, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1507328,
        .children = {
            1709, 1711
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
        .children = {
            1710, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
        .children = {
            1712, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1053918,
        .children = {
            -1, 1714
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1769472,
        .children = {
            1715, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            1716, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2097152,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            1718, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 1507328,
        .children = {
            1719, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 2097152,
        .children = {
            1720, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            1721, 1722
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            1724, 1732
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -950272,
        .children = {
            1725, 1730
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            -1, 1726
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -720896,
        .children = {
            1727, 1729
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            1728, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            1731, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1053918,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            -2, 1733
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 196608,
        .children = {
            1735, 1758
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 524288,
        .children = {
            1736, 1747
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            1737, 1745
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -950272,
        .children = {
            1738, 1743
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            -1, 1739
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -720896,
        .children = {
            1740, 1742
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            1741, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            1744, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1053918,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            -2, 1746
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            1748, 1756
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -950272,
        .children = {
            1749, 1754
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            -1, 1750
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -720896,
        .children = {
            1751, 1753
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            1752, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            1755, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1053918,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -360448,
        .children = {
            -2, 1757
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -262144,
        .children = {
            1759, -1
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1015808,
        .children = {
            1760, 1776
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -622592,
        .children = {
            1761, 1763
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1762, -2
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1053918,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -950272,
        .children = {
            1764, 1773
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = 131072,
        .children = {
            1765, 1769
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -720896,
        .children = {
            1766, 1768
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -884736,
        .children = {
            1767, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1112182,
        .children = {
            -1, -2
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            -2, 1770
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, 1771
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -688128,
        .children = {
            -2, 1772
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1204864,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, 1774
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            -2, 1775
        }
    },
    {
        .normal = {
            .x = 2896,
            .y = 0,
            .z = 2896
        },
        .distance = -1204864,
        .children = {
            -2, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = 0,
            .z = 4096
        },
        .distance = -688128,
        .children = {
            1777, -1
        }
    },
    {
        .normal = {
            .x = 0,
            .y = -4096,
            .z = 0
        },
        .distance = -131072,
        .children = {
            -2, 1778
        }
    },
    {
        .normal = {
            .x = 4096,
            .y = 0,
            .z = 0
        },
        .distance = -1081344,
        .children = {
            1779, -1
        }
    },
    {
        .normal = {
            .x = 4016,
            .y = 0,
            .z = 803
        },
        .distance = -1131034,
        .children = {
            -2, -1
        }
    },
};
BSPTree3 bsp_player = {.nodes=bspNodes_player, .numNodes = 1780};

int numTris = 12;
Tri3_texturedFlat tris[] = {
    {
        {983040, 0, 655360},
        {1048576, 0, 327680},
        {983040, 0, 327680},
        {63, 96},
        {32, 101},
        {32, 96},
        10
    },
    {
        {655360, 0, 983040},
        {983040, 0, 655360},
        {655360, 0, 655360},
        {64, 160},
        {95, 191},
        {64, 191},
        10
    },
    {
        {-983040, 0, 655360},
        {-983040, 0, 327680},
        {-1048576, 0, 327680},
        {63, 159},
        {32, 159},
        {32, 153},
        10
    },
    {
        {-655360, 0, 983040},
        {-655360, 0, 655360},
        {-983040, 0, 655360},
        {191, 160},
        {191, 191},
        {160, 191},
        10
    },
    {
        {-983040, 0, -327680},
        {-983040, 0, -655360},
        {-1048576, 0, -327680},
        {223, 159},
        {192, 159},
        {223, 153},
        10
    },
    {
        {-655360, 0, -655360},
        {-655360, 0, -983040},
        {-983040, 0, -655360},
        {191, 64},
        {191, 95},
        {160, 64},
        10
    },
    {
        {1048576, 0, -327680},
        {983040, 0, -655360},
        {983040, 0, -327680},
        {223, 101},
        {192, 96},
        {223, 96},
        10
    },
    {
        {983040, 0, -655360},
        {655360, 0, -983040},
        {655360, 0, -655360},
        {95, 64},
        {64, 95},
        {64, 64},
        10
    },
    {
        {196608, 0, 1769472},
        {327680, -131072, 1638400},
        {196608, 0, 1638400},
        {48, 80},
        {79, 111},
        {48, 111},
        11
    },
    {
        {327680, -131072, 1638400},
        {327680, 0, 1638400},
        {196608, 0, 1638400},
        {79, 224},
        {79, 255},
        {48, 255},
        11
    },
    {
        {327680, 0, 1769472},
        {327680, -131072, 1638400},
        {196608, 0, 1769472},
        {79, 80},
        {79, 111},
        {48, 80},
        11
    },
    {
        {327680, -131072, 1638400},
        {327680, 0, 1769472},
        {327680, 0, 1638400},
        {144, 224},
        {175, 255},
        {144, 255},
        11
    },
};
int numQuads = 569;
Quad3_texturedFlat quads[] = {
    {
        {0, 0, 0},
        {327680, 0, 0},
        {0, 0, -327680},
        {327680, 0, -327680},
        {255, 255},
        {224, 255},
        {255, 224},
        {224, 224},
        12
    },
    {
        {0, 0, -983040},
        {327680, 0, -983040},
        {0, -327680, -983040},
        {327680, -327680, -983040},
        {0, 255},
        {31, 255},
        {0, 224},
        {31, 224},
        16
    },
    {
        {327680, 0, -983040},
        {327680, 0, -917504},
        {327680, -327680, -983040},
        {327680, -327680, -917504},
        {16, 255},
        {31, 255},
        {16, 176},
        {31, 176},
        11
    },
    {
        {327680, 0, -917504},
        {655360, 0, -917504},
        {327680, -327680, -917504},
        {655360, -327680, -917504},
        {32, 255},
        {63, 255},
        {32, 224},
        {63, 224},
        15
    },
    {
        {688128, -327680, -983040},
        {655360, -327680, -917504},
        {688128, 0, -983040},
        {655360, 0, -917504},
        {0, 176},
        {15, 176},
        {0, 255},
        {15, 255},
        11
    },
    {
        {-688128, 0, -983040},
        {-655360, 0, -917504},
        {-688128, -327680, -983040},
        {-655360, -327680, -917504},
        {0, 0},
        {15, 0},
        {0, 175},
        {15, 175},
        11
    },
    {
        {-655360, 0, -917504},
        {-327680, 0, -917504},
        {-655360, -327680, -917504},
        {-327680, -327680, -917504},
        {192, 255},
        {223, 255},
        {192, 224},
        {223, 224},
        15
    },
    {
        {-327680, -327680, -983040},
        {-327680, -327680, -917504},
        {-327680, 0, -983040},
        {-327680, 0, -917504},
        {0, 176},
        {15, 176},
        {0, 255},
        {15, 255},
        11
    },
    {
        {-983040, 0, -655360},
        {-655360, 0, -983040},
        {-983040, -327680, -655360},
        {-655360, -327680, -983040},
        {0, 193},
        {0, 162},
        {31, 193},
        {31, 162},
        16
    },
    {
        {-1048576, -327680, -327680},
        {-1048576, -327680, 0},
        {-1048576, 0, -327680},
        {-1048576, 0, 0},
        {224, 224},
        {255, 224},
        {224, 255},
        {255, 255},
        16
    },
    {
        {327680, -327680, -983040},
        {327680, -327680, -917504},
        {327680, -655360, -983040},
        {327680, -655360, -917504},
        {0, 176},
        {15, 176},
        {0, 95},
        {15, 95},
        11
    },
    {
        {327680, -327680, -917504},
        {655360, -327680, -917504},
        {327680, -655360, -917504},
        {655360, -655360, -917504},
        {32, 223},
        {63, 223},
        {32, 192},
        {63, 192},
        6
    },
    {
        {688128, -655360, -983040},
        {655360, -655360, -917504},
        {688128, -327680, -983040},
        {655360, -327680, -917504},
        {0, 96},
        {15, 96},
        {0, 175},
        {15, 175},
        11
    },
    {
        {327680, -655360, -983040},
        {327680, -655360, -917504},
        {327680, -983040, -983040},
        {327680, -983040, -917504},
        {0, 96},
        {15, 96},
        {0, 15},
        {15, 15},
        11
    },
    {
        {327680, -655360, -917504},
        {655360, -655360, -917504},
        {327680, -983040, -917504},
        {655360, -983040, -917504},
        {32, 191},
        {63, 191},
        {32, 160},
        {63, 160},
        6
    },
    {
        {688128, -983040, -983040},
        {655360, -983040, -917504},
        {688128, -655360, -983040},
        {655360, -655360, -917504},
        {0, 16},
        {15, 16},
        {0, 95},
        {15, 95},
        11
    },
    {
        {327680, -983040, -983040},
        {327680, -983040, -917504},
        {327680, -1310720, -983040},
        {327680, -1310720, -917504},
        {0, 15},
        {15, 15},
        {0, 192},
        {15, 192},
        11
    },
    {
        {327680, -983040, -917504},
        {655360, -983040, -917504},
        {327680, -1310720, -917504},
        {655360, -1310720, -917504},
        {32, 159},
        {63, 159},
        {32, 128},
        {63, 128},
        9
    },
    {
        {688128, -1310720, -983040},
        {655360, -1310720, -917504},
        {688128, -983040, -983040},
        {655360, -983040, -917504},
        {0, 192},
        {15, 192},
        {0, 15},
        {15, 15},
        11
    },
    {
        {-688128, -327680, -983040},
        {-655360, -327680, -917504},
        {-688128, -655360, -983040},
        {-655360, -655360, -917504},
        {0, 176},
        {15, 176},
        {0, 95},
        {15, 95},
        11
    },
    {
        {-655360, -327680, -917504},
        {-327680, -327680, -917504},
        {-655360, -655360, -917504},
        {-327680, -655360, -917504},
        {192, 223},
        {223, 223},
        {192, 192},
        {223, 192},
        6
    },
    {
        {-327680, -655360, -983040},
        {-327680, -655360, -917504},
        {-327680, -327680, -983040},
        {-327680, -327680, -917504},
        {0, 96},
        {15, 96},
        {0, 175},
        {15, 175},
        11
    },
    {
        {-688128, -655360, -983040},
        {-655360, -655360, -917504},
        {-688128, -983040, -983040},
        {-655360, -983040, -917504},
        {0, 96},
        {15, 96},
        {0, 15},
        {15, 15},
        11
    },
    {
        {-655360, -655360, -917504},
        {-327680, -655360, -917504},
        {-655360, -983040, -917504},
        {-327680, -983040, -917504},
        {192, 192},
        {223, 192},
        {192, 159},
        {223, 159},
        6
    },
    {
        {-327680, -983040, -983040},
        {-327680, -983040, -917504},
        {-327680, -655360, -983040},
        {-327680, -655360, -917504},
        {0, 16},
        {15, 16},
        {0, 95},
        {15, 95},
        11
    },
    {
        {-688128, -983040, -983040},
        {-655360, -983040, -917504},
        {-688128, -1310720, -983040},
        {-655360, -1310720, -917504},
        {0, 15},
        {15, 15},
        {0, 192},
        {15, 192},
        11
    },
    {
        {-655360, -983040, -917504},
        {-327680, -983040, -917504},
        {-655360, -1310720, -917504},
        {-327680, -1310720, -917504},
        {192, 160},
        {223, 160},
        {192, 127},
        {223, 127},
        9
    },
    {
        {-327680, -1310720, -983040},
        {-327680, -1310720, -917504},
        {-327680, -983040, -983040},
        {-327680, -983040, -917504},
        {0, 192},
        {15, 192},
        {0, 15},
        {15, 15},
        11
    },
    {
        {-327680, 0, 0},
        {0, 0, 0},
        {-327680, 0, -327680},
        {0, 0, -327680},
        {255, 224},
        {255, 255},
        {224, 224},
        {224, 255},
        12
    },
    {
        {0, 0, 327680},
        {327680, 0, 327680},
        {0, 0, 0},
        {327680, 0, 0},
        {224, 255},
        {224, 224},
        {255, 255},
        {255, 224},
        12
    },
    {
        {-327680, 0, 327680},
        {0, 0, 327680},
        {-327680, 0, 0},
        {0, 0, 0},
        {224, 224},
        {255, 224},
        {224, 255},
        {255, 255},
        12
    },
    {
        {0, 0, 655360},
        {327680, 0, 655360},
        {0, 0, 327680},
        {327680, 0, 327680},
        {0, 192},
        {31, 192},
        {0, 223},
        {31, 223},
        1
    },
    {
        {-327680, 0, 327680},
        {-327680, 0, 655360},
        {-327680, -131072, 327680},
        {-327680, -131072, 655360},
        {64, 255},
        {143, 255},
        {64, 224},
        {143, 224},
        1
    },
    {
        {-327680, -131072, 327680},
        {0, -131072, 327680},
        {-327680, 0, 327680},
        {0, 0, 327680},
        {192, 224},
        {15, 224},
        {192, 255},
        {15, 255},
        1
    },
    {
        {-327680, 0, 327680},
        {0, 0, 327680},
        {-327680, 0, 655360},
        {0, 0, 655360},
        {192, 192},
        {15, 192},
        {192, 111},
        {15, 111},
        1
    },
    {
        {-327680, -131072, 655360},
        {0, -131072, 655360},
        {-327680, -131072, 327680},
        {0, -131072, 327680},
        {224, 192},
        {255, 192},
        {224, 223},
        {255, 223},
        1
    },
    {
        {-327680, 0, 655360},
        {0, 0, 655360},
        {-327680, -131072, 655360},
        {0, -131072, 655360},
        {192, 0},
        {15, 0},
        {192, 223},
        {15, 223},
        1
    },
    {
        {0, -131072, 327680},
        {0, -131072, 655360},
        {0, 0, 327680},
        {0, 0, 655360},
        {64, 224},
        {143, 224},
        {64, 255},
        {143, 255},
        1
    },
    {
        {-327680, 0, 983040},
        {0, 0, 983040},
        {-327680, 0, 655360},
        {0, 0, 655360},
        {224, 160},
        {255, 160},
        {224, 191},
        {255, 191},
        1
    },
    {
        {0, 0, 983040},
        {327680, 0, 983040},
        {0, 0, 655360},
        {327680, 0, 655360},
        {0, 160},
        {31, 160},
        {0, 191},
        {31, 191},
        1
    },
    {
        {-983040, 0, 0},
        {-655360, 0, 0},
        {-983040, 0, -327680},
        {-655360, 0, -327680},
        {255, 160},
        {255, 191},
        {224, 160},
        {224, 191},
        1
    },
    {
        {-983040, 0, 327680},
        {-655360, 0, 327680},
        {-983040, 0, 0},
        {-655360, 0, 0},
        {31, 160},
        {31, 191},
        {0, 160},
        {0, 191},
        1
    },
    {
        {-655360, 0, 327680},
        {-327680, 0, 327680},
        {-655360, 0, 0},
        {-327680, 0, 0},
        {31, 192},
        {31, 223},
        {0, 192},
        {0, 223},
        1
    },
    {
        {-655360, 0, 0},
        {-327680, 0, 0},
        {-655360, 0, -327680},
        {-327680, 0, -327680},
        {255, 192},
        {255, 223},
        {224, 192},
        {224, 223},
        1
    },
    {
        {327680, 0, 0},
        {655360, 0, 0},
        {327680, 0, -327680},
        {655360, 0, -327680},
        {255, 32},
        {255, 63},
        {224, 32},
        {224, 63},
        1
    },
    {
        {327680, 0, 327680},
        {655360, 0, 327680},
        {327680, 0, 0},
        {655360, 0, 0},
        {31, 32},
        {31, 63},
        {0, 32},
        {0, 63},
        1
    },
    {
        {655360, 0, 327680},
        {983040, 0, 327680},
        {655360, 0, 0},
        {983040, 0, 0},
        {31, 64},
        {31, 95},
        {0, 64},
        {0, 95},
        1
    },
    {
        {655360, 0, 0},
        {983040, 0, 0},
        {655360, 0, -327680},
        {983040, 0, -327680},
        {255, 64},
        {255, 95},
        {224, 64},
        {224, 95},
        1
    },
    {
        {-327680, 0, -655360},
        {0, 0, -655360},
        {-327680, 0, -983040},
        {0, 0, -983040},
        {224, 64},
        {255, 64},
        {224, 95},
        {255, 95},
        1
    },
    {
        {-327680, 0, -327680},
        {0, 0, -327680},
        {-327680, 0, -655360},
        {0, 0, -655360},
        {224, 32},
        {255, 32},
        {224, 63},
        {255, 63},
        1
    },
    {
        {0, 0, -327680},
        {327680, 0, -327680},
        {0, 0, -655360},
        {327680, 0, -655360},
        {0, 32},
        {31, 32},
        {0, 63},
        {31, 63},
        1
    },
    {
        {0, 0, -655360},
        {327680, 0, -655360},
        {0, 0, -983040},
        {327680, 0, -983040},
        {0, 64},
        {31, 64},
        {0, 95},
        {31, 95},
        1
    },
    {
        {-1048576, 0, 327680},
        {-983040, 0, 327680},
        {-1048576, 0, 0},
        {-983040, 0, 0},
        {31, 153},
        {31, 159},
        {0, 153},
        {0, 159},
        1
    },
    {
        {-1048576, 0, 0},
        {-983040, 0, 0},
        {-1048576, 0, -327680},
        {-983040, 0, -327680},
        {255, 153},
        {255, 159},
        {224, 153},
        {224, 159},
        1
    },
    {
        {983040, 0, 0},
        {1048576, 0, 0},
        {983040, 0, -327680},
        {1048576, 0, -327680},
        {255, 96},
        {255, 101},
        {224, 96},
        {224, 101},
        1
    },
    {
        {983040, 0, 327680},
        {1048576, 0, 327680},
        {983040, 0, 0},
        {1048576, 0, 0},
        {31, 96},
        {31, 101},
        {0, 96},
        {0, 101},
        1
    },
    {
        {327680, 0, 917504},
        {655360, 0, 917504},
        {327680, 0, 655360},
        {655360, 0, 655360},
        {89, 32},
        {89, 63},
        {64, 32},
        {64, 63},
        10
    },
    {
        {327680, 0, 655360},
        {655360, 0, 655360},
        {327680, 0, 327680},
        {655360, 0, 327680},
        {63, 32},
        {63, 63},
        {32, 32},
        {32, 63},
        10
    },
    {
        {655360, 0, 655360},
        {983040, 0, 655360},
        {655360, 0, 327680},
        {983040, 0, 327680},
        {63, 64},
        {63, 95},
        {32, 64},
        {32, 95},
        10
    },
    {
        {-655360, 0, 655360},
        {-327680, 0, 655360},
        {-655360, 0, 327680},
        {-327680, 0, 327680},
        {63, 192},
        {63, 223},
        {32, 192},
        {32, 223},
        10
    },
    {
        {-983040, 0, 655360},
        {-655360, 0, 655360},
        {-983040, 0, 327680},
        {-655360, 0, 327680},
        {63, 160},
        {63, 191},
        {32, 160},
        {32, 191},
        10
    },
    {
        {-655360, 0, 917504},
        {-327680, 0, 917504},
        {-655360, 0, 655360},
        {-327680, 0, 655360},
        {89, 192},
        {89, 223},
        {64, 192},
        {64, 223},
        10
    },
    {
        {-655360, 0, -327680},
        {-327680, 0, -327680},
        {-655360, 0, -655360},
        {-327680, 0, -655360},
        {223, 192},
        {223, 223},
        {192, 192},
        {192, 223},
        10
    },
    {
        {-983040, 0, -327680},
        {-655360, 0, -327680},
        {-983040, 0, -655360},
        {-655360, 0, -655360},
        {223, 160},
        {223, 191},
        {192, 160},
        {192, 191},
        10
    },
    {
        {-655360, 0, -655360},
        {-327680, 0, -655360},
        {-655360, 0, -917504},
        {-327680, 0, -917504},
        {191, 192},
        {191, 223},
        {166, 192},
        {166, 223},
        10
    },
    {
        {327680, 0, -327680},
        {655360, 0, -327680},
        {327680, 0, -655360},
        {655360, 0, -655360},
        {223, 32},
        {223, 63},
        {192, 32},
        {192, 63},
        10
    },
    {
        {655360, 0, -327680},
        {983040, 0, -327680},
        {655360, 0, -655360},
        {983040, 0, -655360},
        {223, 64},
        {223, 95},
        {192, 64},
        {192, 95},
        10
    },
    {
        {327680, 0, -655360},
        {655360, 0, -655360},
        {327680, 0, -917504},
        {655360, 0, -917504},
        {191, 32},
        {191, 63},
        {166, 32},
        {166, 63},
        10
    },
    {
        {-983040, -327680, -655360},
        {-655360, -327680, -983040},
        {-983040, -655360, -655360},
        {-655360, -655360, -983040},
        {32, 193},
        {32, 162},
        {63, 193},
        {63, 162},
        16
    },
    {
        {-983040, -655360, -655360},
        {-655360, -655360, -983040},
        {-983040, -983040, -655360},
        {-655360, -983040, -983040},
        {64, 193},
        {64, 162},
        {95, 193},
        {95, 162},
        16
    },
    {
        {-983040, -983040, -655360},
        {-655360, -983040, -983040},
        {-983040, -1310720, -655360},
        {-655360, -1310720, -983040},
        {96, 193},
        {96, 162},
        {127, 193},
        {127, 162},
        16
    },
    {
        {-983040, -1966080, -655360},
        {-655360, -1966080, -983040},
        {-983040, -2293760, -655360},
        {-655360, -2293760, -983040},
        {192, 194},
        {192, 161},
        {223, 194},
        {223, 161},
        16
    },
    {
        {-983040, -2293760, -655360},
        {-655360, -2293760, -983040},
        {-983040, -2621440, -655360},
        {-655360, -2621440, -983040},
        {224, 194},
        {224, 161},
        {255, 194},
        {255, 161},
        16
    },
    {
        {-983040, -1638400, -655360},
        {-655360, -1638400, -983040},
        {-983040, -1966080, -655360},
        {-655360, -1966080, -983040},
        {160, 193},
        {160, 162},
        {191, 193},
        {191, 162},
        16
    },
    {
        {-983040, -1310720, -655360},
        {-655360, -1310720, -983040},
        {-983040, -1638400, -655360},
        {-655360, -1638400, -983040},
        {128, 193},
        {128, 162},
        {159, 193},
        {159, 162},
        16
    },
    {
        {-983040, -3276800, -655360},
        {-655360, -3276800, -983040},
        {-983040, -3604480, -655360},
        {-655360, -3604480, -983040},
        {64, 194},
        {64, 161},
        {95, 194},
        {95, 161},
        16
    },
    {
        {-983040, -3604480, -655360},
        {-655360, -3604480, -983040},
        {-983040, -3932160, -655360},
        {-655360, -3932160, -983040},
        {96, 194},
        {96, 161},
        {127, 194},
        {127, 161},
        16
    },
    {
        {-983040, -2949120, -655360},
        {-655360, -2949120, -983040},
        {-983040, -3276800, -655360},
        {-655360, -3276800, -983040},
        {32, 194},
        {32, 161},
        {63, 194},
        {63, 161},
        16
    },
    {
        {-983040, -2621440, -655360},
        {-655360, -2621440, -983040},
        {-983040, -2949120, -655360},
        {-655360, -2949120, -983040},
        {0, 194},
        {0, 161},
        {31, 194},
        {31, 161},
        16
    },
    {
        {-983040, -4259840, -655360},
        {-655360, -4259840, -983040},
        {-983040, -4587520, -655360},
        {-655360, -4587520, -983040},
        {160, 194},
        {160, 161},
        {191, 194},
        {191, 161},
        16
    },
    {
        {-983040, -3932160, -655360},
        {-655360, -3932160, -983040},
        {-983040, -4259840, -655360},
        {-655360, -4259840, -983040},
        {128, 194},
        {128, 161},
        {159, 194},
        {159, 161},
        16
    },
    {
        {-983040, 0, 655360},
        {-983040, -327680, 655360},
        {-655360, 0, 983040},
        {-655360, -327680, 983040},
        {0, 66},
        {31, 66},
        {0, 97},
        {31, 97},
        16
    },
    {
        {-983040, -327680, 655360},
        {-983040, -655360, 655360},
        {-655360, -327680, 983040},
        {-655360, -655360, 983040},
        {32, 66},
        {63, 66},
        {32, 97},
        {63, 97},
        16
    },
    {
        {-983040, -655360, 655360},
        {-983040, -983040, 655360},
        {-655360, -655360, 983040},
        {-655360, -983040, 983040},
        {64, 66},
        {95, 66},
        {64, 97},
        {95, 97},
        16
    },
    {
        {-983040, -983040, 655360},
        {-983040, -1310720, 655360},
        {-655360, -983040, 983040},
        {-655360, -1310720, 983040},
        {96, 66},
        {127, 66},
        {96, 97},
        {127, 97},
        16
    },
    {
        {-983040, -1310720, 655360},
        {-983040, -1638400, 655360},
        {-655360, -1310720, 983040},
        {-655360, -1638400, 983040},
        {128, 66},
        {159, 66},
        {128, 97},
        {159, 97},
        16
    },
    {
        {-983040, -1638400, 655360},
        {-983040, -1966080, 655360},
        {-655360, -1638400, 983040},
        {-655360, -1966080, 983040},
        {160, 66},
        {191, 66},
        {160, 97},
        {191, 97},
        16
    },
    {
        {-983040, -1966080, 655360},
        {-983040, -2293760, 655360},
        {-655360, -1966080, 983040},
        {-655360, -2293760, 983040},
        {192, 66},
        {223, 66},
        {192, 97},
        {223, 97},
        16
    },
    {
        {-983040, -2293760, 655360},
        {-983040, -2621440, 655360},
        {-655360, -2293760, 983040},
        {-655360, -2621440, 983040},
        {224, 66},
        {255, 66},
        {224, 97},
        {255, 97},
        16
    },
    {
        {-983040, -2621440, 655360},
        {-983040, -2949120, 655360},
        {-655360, -2621440, 983040},
        {-655360, -2949120, 983040},
        {0, 66},
        {31, 66},
        {0, 97},
        {31, 97},
        16
    },
    {
        {-983040, -2949120, 655360},
        {-983040, -3276800, 655360},
        {-655360, -2949120, 983040},
        {-655360, -3276800, 983040},
        {32, 66},
        {63, 66},
        {32, 97},
        {63, 97},
        16
    },
    {
        {-983040, -3276800, 655360},
        {-983040, -3604480, 655360},
        {-655360, -3276800, 983040},
        {-655360, -3604480, 983040},
        {64, 66},
        {95, 66},
        {64, 97},
        {95, 97},
        16
    },
    {
        {-983040, -3604480, 655360},
        {-983040, -3932160, 655360},
        {-655360, -3604480, 983040},
        {-655360, -3932160, 983040},
        {96, 66},
        {127, 66},
        {96, 97},
        {127, 97},
        16
    },
    {
        {-983040, -3932160, 655360},
        {-983040, -4259840, 655360},
        {-655360, -3932160, 983040},
        {-655360, -4259840, 983040},
        {128, 66},
        {159, 66},
        {128, 97},
        {159, 97},
        16
    },
    {
        {-983040, -4259840, 655360},
        {-983040, -4587520, 655360},
        {-655360, -4259840, 983040},
        {-655360, -4587520, 983040},
        {160, 66},
        {191, 66},
        {160, 97},
        {191, 97},
        16
    },
    {
        {655360, 0, -983040},
        {983040, 0, -655360},
        {655360, -327680, -983040},
        {983040, -327680, -655360},
        {0, 162},
        {0, 193},
        {31, 162},
        {31, 193},
        16
    },
    {
        {655360, -327680, -983040},
        {983040, -327680, -655360},
        {655360, -655360, -983040},
        {983040, -655360, -655360},
        {32, 162},
        {32, 193},
        {63, 162},
        {63, 193},
        16
    },
    {
        {655360, -655360, -983040},
        {983040, -655360, -655360},
        {655360, -983040, -983040},
        {983040, -983040, -655360},
        {64, 162},
        {64, 193},
        {95, 162},
        {95, 193},
        16
    },
    {
        {655360, -983040, -983040},
        {983040, -983040, -655360},
        {655360, -1310720, -983040},
        {983040, -1310720, -655360},
        {96, 162},
        {96, 193},
        {127, 162},
        {127, 193},
        16
    },
    {
        {655360, -1310720, -983040},
        {983040, -1310720, -655360},
        {655360, -1638400, -983040},
        {983040, -1638400, -655360},
        {128, 162},
        {128, 193},
        {159, 162},
        {159, 193},
        16
    },
    {
        {655360, -1638400, -983040},
        {983040, -1638400, -655360},
        {655360, -1966080, -983040},
        {983040, -1966080, -655360},
        {160, 162},
        {160, 193},
        {191, 162},
        {191, 193},
        16
    },
    {
        {655360, -1966080, -983040},
        {983040, -1966080, -655360},
        {655360, -2293760, -983040},
        {983040, -2293760, -655360},
        {192, 162},
        {192, 193},
        {223, 162},
        {223, 193},
        16
    },
    {
        {655360, -2293760, -983040},
        {983040, -2293760, -655360},
        {655360, -2621440, -983040},
        {983040, -2621440, -655360},
        {224, 162},
        {224, 193},
        {255, 162},
        {255, 193},
        16
    },
    {
        {655360, -2621440, -983040},
        {983040, -2621440, -655360},
        {655360, -2949120, -983040},
        {983040, -2949120, -655360},
        {0, 162},
        {0, 193},
        {31, 162},
        {31, 193},
        16
    },
    {
        {655360, -2949120, -983040},
        {983040, -2949120, -655360},
        {655360, -3276800, -983040},
        {983040, -3276800, -655360},
        {32, 162},
        {32, 193},
        {63, 162},
        {63, 193},
        16
    },
    {
        {655360, -3276800, -983040},
        {983040, -3276800, -655360},
        {655360, -3604480, -983040},
        {983040, -3604480, -655360},
        {64, 162},
        {64, 193},
        {95, 162},
        {95, 193},
        16
    },
    {
        {655360, -3604480, -983040},
        {983040, -3604480, -655360},
        {655360, -3932160, -983040},
        {983040, -3932160, -655360},
        {96, 162},
        {96, 193},
        {127, 162},
        {127, 193},
        16
    },
    {
        {655360, -3932160, -983040},
        {983040, -3932160, -655360},
        {655360, -4259840, -983040},
        {983040, -4259840, -655360},
        {128, 162},
        {128, 193},
        {159, 162},
        {159, 193},
        16
    },
    {
        {655360, -4259840, -983040},
        {983040, -4259840, -655360},
        {655360, -4587520, -983040},
        {983040, -4587520, -655360},
        {160, 162},
        {160, 193},
        {191, 162},
        {191, 193},
        16
    },
    {
        {655360, -327680, 983040},
        {983040, -327680, 655360},
        {655360, 0, 983040},
        {983040, 0, 655360},
        {31, 97},
        {31, 66},
        {0, 97},
        {0, 66},
        16
    },
    {
        {655360, -655360, 983040},
        {983040, -655360, 655360},
        {655360, -327680, 983040},
        {983040, -327680, 655360},
        {63, 97},
        {63, 66},
        {32, 97},
        {32, 66},
        16
    },
    {
        {655360, -983040, 983040},
        {983040, -983040, 655360},
        {655360, -655360, 983040},
        {983040, -655360, 655360},
        {95, 97},
        {95, 66},
        {64, 97},
        {64, 66},
        16
    },
    {
        {655360, -1310720, 983040},
        {983040, -1310720, 655360},
        {655360, -983040, 983040},
        {983040, -983040, 655360},
        {127, 97},
        {127, 66},
        {96, 97},
        {96, 66},
        16
    },
    {
        {655360, -1638400, 983040},
        {983040, -1638400, 655360},
        {655360, -1310720, 983040},
        {983040, -1310720, 655360},
        {159, 98},
        {159, 65},
        {128, 98},
        {128, 65},
        16
    },
    {
        {655360, -1966080, 983040},
        {983040, -1966080, 655360},
        {655360, -1638400, 983040},
        {983040, -1638400, 655360},
        {191, 98},
        {191, 65},
        {160, 98},
        {160, 65},
        16
    },
    {
        {655360, -2293760, 983040},
        {983040, -2293760, 655360},
        {655360, -1966080, 983040},
        {983040, -1966080, 655360},
        {223, 98},
        {223, 65},
        {192, 98},
        {192, 65},
        16
    },
    {
        {655360, -2621440, 983040},
        {983040, -2621440, 655360},
        {655360, -2293760, 983040},
        {983040, -2293760, 655360},
        {255, 98},
        {255, 65},
        {224, 98},
        {224, 65},
        16
    },
    {
        {655360, -2949120, 983040},
        {983040, -2949120, 655360},
        {655360, -2621440, 983040},
        {983040, -2621440, 655360},
        {31, 98},
        {31, 65},
        {0, 98},
        {0, 65},
        16
    },
    {
        {655360, -3276800, 983040},
        {983040, -3276800, 655360},
        {655360, -2949120, 983040},
        {983040, -2949120, 655360},
        {63, 98},
        {63, 65},
        {32, 98},
        {32, 65},
        16
    },
    {
        {655360, -3604480, 983040},
        {983040, -3604480, 655360},
        {655360, -3276800, 983040},
        {983040, -3276800, 655360},
        {95, 98},
        {95, 65},
        {64, 98},
        {64, 65},
        16
    },
    {
        {655360, -3932160, 983040},
        {983040, -3932160, 655360},
        {655360, -3604480, 983040},
        {983040, -3604480, 655360},
        {127, 98},
        {127, 65},
        {96, 98},
        {96, 65},
        16
    },
    {
        {655360, -4259840, 983040},
        {983040, -4259840, 655360},
        {655360, -3932160, 983040},
        {983040, -3932160, 655360},
        {159, 98},
        {159, 65},
        {128, 98},
        {128, 65},
        16
    },
    {
        {655360, -4587520, 983040},
        {983040, -4587520, 655360},
        {655360, -4259840, 983040},
        {983040, -4259840, 655360},
        {191, 98},
        {191, 65},
        {160, 98},
        {160, 65},
        16
    },
    {
        {-327680, 0, -983040},
        {0, 0, -983040},
        {-327680, -327680, -983040},
        {0, -327680, -983040},
        {224, 255},
        {255, 255},
        {224, 224},
        {255, 224},
        16
    },
    {
        {-327680, -327680, -983040},
        {0, -327680, -983040},
        {-327680, -655360, -983040},
        {0, -655360, -983040},
        {224, 224},
        {255, 224},
        {224, 191},
        {255, 191},
        0
    },
    {
        {0, -327680, -983040},
        {327680, -327680, -983040},
        {0, -655360, -983040},
        {327680, -655360, -983040},
        {0, 223},
        {31, 223},
        {0, 192},
        {31, 192},
        0
    },
    {
        {-1048576, -327680, 327680},
        {-983040, -327680, 655360},
        {-1048576, 0, 327680},
        {-983040, 0, 655360},
        {223, 224},
        {192, 224},
        {223, 255},
        {192, 255},
        14
    },
    {
        {-1048576, -327680, 0},
        {-1048576, -327680, 327680},
        {-1048576, 0, 0},
        {-1048576, 0, 327680},
        {0, 224},
        {31, 224},
        {0, 255},
        {31, 255},
        16
    },
    {
        {-1048576, -655360, -327680},
        {-1048576, -655360, 0},
        {-1048576, -327680, -327680},
        {-1048576, -327680, 0},
        {224, 192},
        {255, 192},
        {224, 223},
        {255, 223},
        15
    },
    {
        {-1048576, -655360, 0},
        {-1048576, -655360, 327680},
        {-1048576, -327680, 0},
        {-1048576, -327680, 327680},
        {0, 192},
        {31, 192},
        {0, 223},
        {31, 223},
        15
    },
    {
        {-1048576, -983040, -327680},
        {-1048576, -983040, 0},
        {-1048576, -655360, -327680},
        {-1048576, -655360, 0},
        {0, 160},
        {31, 160},
        {0, 191},
        {31, 191},
        6
    },
    {
        {-1048576, -983040, 0},
        {-1048576, -983040, 327680},
        {-1048576, -655360, 0},
        {-1048576, -655360, 327680},
        {32, 160},
        {63, 160},
        {32, 191},
        {63, 191},
        6
    },
    {
        {-1048576, -1310720, -327680},
        {-1048576, -1310720, 0},
        {-1048576, -983040, -327680},
        {-1048576, -983040, 0},
        {0, 128},
        {31, 128},
        {0, 159},
        {31, 159},
        6
    },
    {
        {-1048576, -1310720, 0},
        {-1048576, -1310720, 327680},
        {-1048576, -983040, 0},
        {-1048576, -983040, 327680},
        {32, 128},
        {63, 128},
        {32, 159},
        {63, 159},
        6
    },
    {
        {-1048576, -1638400, -327680},
        {-1048576, -1638400, 0},
        {-1048576, -1310720, -327680},
        {-1048576, -1310720, 0},
        {0, 96},
        {31, 96},
        {0, 127},
        {31, 127},
        6
    },
    {
        {-1048576, -1638400, 0},
        {-1048576, -1638400, 327680},
        {-1048576, -1310720, 0},
        {-1048576, -1310720, 327680},
        {32, 96},
        {63, 96},
        {32, 127},
        {63, 127},
        6
    },
    {
        {-1048576, -1966080, -327680},
        {-1048576, -1966080, 0},
        {-1048576, -1638400, -327680},
        {-1048576, -1638400, 0},
        {0, 64},
        {31, 64},
        {0, 95},
        {31, 95},
        9
    },
    {
        {-1048576, -1966080, 0},
        {-1048576, -1966080, 327680},
        {-1048576, -1638400, 0},
        {-1048576, -1638400, 327680},
        {32, 64},
        {63, 64},
        {32, 95},
        {63, 95},
        9
    },
    {
        {1048576, -1638400, -327680},
        {1048576, -1638400, 0},
        {1048576, -1966080, -327680},
        {1048576, -1966080, 0},
        {0, 95},
        {31, 95},
        {0, 64},
        {31, 64},
        9
    },
    {
        {1048576, -1310720, -327680},
        {1048576, -1310720, 0},
        {1048576, -1638400, -327680},
        {1048576, -1638400, 0},
        {0, 127},
        {31, 127},
        {0, 96},
        {31, 96},
        6
    },
    {
        {1048576, -983040, -327680},
        {1048576, -983040, 0},
        {1048576, -1310720, -327680},
        {1048576, -1310720, 0},
        {0, 159},
        {31, 159},
        {0, 128},
        {31, 128},
        6
    },
    {
        {1048576, -655360, -327680},
        {1048576, -655360, 0},
        {1048576, -983040, -327680},
        {1048576, -983040, 0},
        {0, 191},
        {31, 191},
        {0, 160},
        {31, 160},
        6
    },
    {
        {1048576, -327680, -327680},
        {1048576, -327680, 0},
        {1048576, -655360, -327680},
        {1048576, -655360, 0},
        {224, 224},
        {255, 224},
        {224, 191},
        {255, 191},
        15
    },
    {
        {1048576, -327680, 0},
        {1048576, -327680, 327680},
        {1048576, -655360, 0},
        {1048576, -655360, 327680},
        {0, 223},
        {31, 223},
        {0, 192},
        {31, 192},
        15
    },
    {
        {1048576, -655360, 0},
        {1048576, -655360, 327680},
        {1048576, -983040, 0},
        {1048576, -983040, 327680},
        {32, 191},
        {63, 191},
        {32, 160},
        {63, 160},
        6
    },
    {
        {1048576, -983040, 0},
        {1048576, -983040, 327680},
        {1048576, -1310720, 0},
        {1048576, -1310720, 327680},
        {32, 159},
        {63, 159},
        {32, 128},
        {63, 128},
        6
    },
    {
        {1048576, -1310720, 0},
        {1048576, -1310720, 327680},
        {1048576, -1638400, 0},
        {1048576, -1638400, 327680},
        {32, 127},
        {63, 127},
        {32, 96},
        {63, 96},
        6
    },
    {
        {1048576, -1638400, 0},
        {1048576, -1638400, 327680},
        {1048576, -1966080, 0},
        {1048576, -1966080, 327680},
        {32, 95},
        {63, 95},
        {32, 64},
        {63, 64},
        9
    },
    {
        {-1048576, -1966080, 327680},
        {-1048576, -2293760, 327680},
        {-983040, -1966080, 655360},
        {-983040, -2293760, 655360},
        {39, 64},
        {39, 31},
        {70, 64},
        {70, 31},
        7
    },
    {
        {-1048576, -2293760, 327680},
        {-1048576, -2621440, 327680},
        {-983040, -2293760, 655360},
        {-983040, -2621440, 655360},
        {39, 31},
        {39, 0},
        {70, 31},
        {70, 0},
        7
    },
    {
        {-1048576, -2621440, 327680},
        {-1048576, -2949120, 327680},
        {-983040, -2621440, 655360},
        {-983040, -2949120, 655360},
        {39, 255},
        {39, 224},
        {70, 255},
        {70, 224},
        7
    },
    {
        {-1048576, -2949120, 327680},
        {-1048576, -3276800, 327680},
        {-983040, -2949120, 655360},
        {-983040, -3276800, 655360},
        {39, 223},
        {39, 192},
        {70, 223},
        {70, 192},
        7
    },
    {
        {-1048576, -3276800, 327680},
        {-1048576, -3604480, 327680},
        {-983040, -3276800, 655360},
        {-983040, -3604480, 655360},
        {39, 191},
        {39, 160},
        {70, 191},
        {70, 160},
        7
    },
    {
        {-1048576, -3604480, 327680},
        {-1048576, -3932160, 327680},
        {-983040, -3604480, 655360},
        {-983040, -3932160, 655360},
        {39, 159},
        {39, 128},
        {70, 159},
        {70, 128},
        7
    },
    {
        {-1048576, -3932160, 327680},
        {-1048576, -4259840, 327680},
        {-983040, -3932160, 655360},
        {-983040, -4259840, 655360},
        {39, 127},
        {39, 96},
        {70, 127},
        {70, 96},
        7
    },
    {
        {-1048576, -4259840, 327680},
        {-1048576, -4587520, 327680},
        {-983040, -4259840, 655360},
        {-983040, -4587520, 655360},
        {39, 95},
        {39, 64},
        {70, 95},
        {70, 64},
        7
    },
    {
        {-1048576, -1966080, -327680},
        {-983040, -1966080, -655360},
        {-1048576, -2293760, -327680},
        {-983040, -2293760, -655360},
        {216, 64},
        {185, 64},
        {216, 31},
        {185, 31},
        7
    },
    {
        {-1048576, -2293760, -327680},
        {-983040, -2293760, -655360},
        {-1048576, -2621440, -327680},
        {-983040, -2621440, -655360},
        {216, 31},
        {185, 31},
        {216, 0},
        {185, 0},
        7
    },
    {
        {-1048576, -2621440, -327680},
        {-983040, -2621440, -655360},
        {-1048576, -2949120, -327680},
        {-983040, -2949120, -655360},
        {216, 255},
        {185, 255},
        {216, 224},
        {185, 224},
        7
    },
    {
        {-1048576, -2949120, -327680},
        {-983040, -2949120, -655360},
        {-1048576, -3276800, -327680},
        {-983040, -3276800, -655360},
        {216, 223},
        {185, 223},
        {216, 192},
        {185, 192},
        7
    },
    {
        {-1048576, -3276800, -327680},
        {-983040, -3276800, -655360},
        {-1048576, -3604480, -327680},
        {-983040, -3604480, -655360},
        {216, 191},
        {185, 191},
        {216, 160},
        {185, 160},
        7
    },
    {
        {-1048576, -3604480, -327680},
        {-983040, -3604480, -655360},
        {-1048576, -3932160, -327680},
        {-983040, -3932160, -655360},
        {216, 160},
        {185, 160},
        {216, 127},
        {185, 127},
        7
    },
    {
        {-1048576, -3932160, -327680},
        {-983040, -3932160, -655360},
        {-1048576, -4259840, -327680},
        {-983040, -4259840, -655360},
        {216, 128},
        {185, 128},
        {216, 95},
        {185, 95},
        7
    },
    {
        {-1048576, -4259840, -327680},
        {-983040, -4259840, -655360},
        {-1048576, -4587520, -327680},
        {-983040, -4587520, -655360},
        {216, 96},
        {185, 96},
        {216, 63},
        {185, 63},
        7
    },
    {
        {983040, -4259840, -655360},
        {1048576, -4259840, -327680},
        {983040, -4587520, -655360},
        {1048576, -4587520, -327680},
        {185, 96},
        {216, 96},
        {185, 63},
        {216, 63},
        7
    },
    {
        {983040, -4587520, 655360},
        {1048576, -4587520, 327680},
        {983040, -4259840, 655360},
        {1048576, -4259840, 327680},
        {70, 64},
        {39, 64},
        {70, 95},
        {39, 95},
        7
    },
    {
        {983040, -3932160, -655360},
        {1048576, -3932160, -327680},
        {983040, -4259840, -655360},
        {1048576, -4259840, -327680},
        {185, 128},
        {216, 128},
        {185, 95},
        {216, 95},
        7
    },
    {
        {983040, -4259840, 655360},
        {1048576, -4259840, 327680},
        {983040, -3932160, 655360},
        {1048576, -3932160, 327680},
        {70, 96},
        {39, 96},
        {70, 127},
        {39, 127},
        7
    },
    {
        {983040, -3932160, 655360},
        {1048576, -3932160, 327680},
        {983040, -3604480, 655360},
        {1048576, -3604480, 327680},
        {70, 128},
        {39, 128},
        {70, 159},
        {39, 159},
        7
    },
    {
        {983040, -3604480, 655360},
        {1048576, -3604480, 327680},
        {983040, -3276800, 655360},
        {1048576, -3276800, 327680},
        {70, 160},
        {39, 160},
        {70, 191},
        {39, 191},
        7
    },
    {
        {983040, -3276800, 655360},
        {1048576, -3276800, 327680},
        {983040, -2949120, 655360},
        {1048576, -2949120, 327680},
        {70, 192},
        {39, 192},
        {70, 223},
        {39, 223},
        7
    },
    {
        {983040, -2949120, 655360},
        {1048576, -2949120, 327680},
        {983040, -2621440, 655360},
        {1048576, -2621440, 327680},
        {70, 224},
        {39, 224},
        {70, 255},
        {39, 255},
        7
    },
    {
        {983040, -2621440, 655360},
        {1048576, -2621440, 327680},
        {983040, -2293760, 655360},
        {1048576, -2293760, 327680},
        {70, 0},
        {39, 0},
        {70, 31},
        {39, 31},
        7
    },
    {
        {983040, -2293760, 655360},
        {1048576, -2293760, 327680},
        {983040, -1966080, 655360},
        {1048576, -1966080, 327680},
        {70, 32},
        {39, 32},
        {70, 63},
        {39, 63},
        7
    },
    {
        {983040, -1966080, -655360},
        {1048576, -1966080, -327680},
        {983040, -2293760, -655360},
        {1048576, -2293760, -327680},
        {185, 64},
        {216, 64},
        {185, 31},
        {216, 31},
        7
    },
    {
        {983040, -2293760, -655360},
        {1048576, -2293760, -327680},
        {983040, -2621440, -655360},
        {1048576, -2621440, -327680},
        {185, 31},
        {216, 31},
        {185, 0},
        {216, 0},
        7
    },
    {
        {983040, -2621440, -655360},
        {1048576, -2621440, -327680},
        {983040, -2949120, -655360},
        {1048576, -2949120, -327680},
        {185, 255},
        {216, 255},
        {185, 224},
        {216, 224},
        7
    },
    {
        {983040, -2949120, -655360},
        {1048576, -2949120, -327680},
        {983040, -3276800, -655360},
        {1048576, -3276800, -327680},
        {185, 223},
        {216, 223},
        {185, 192},
        {216, 192},
        7
    },
    {
        {983040, -3276800, -655360},
        {1048576, -3276800, -327680},
        {983040, -3604480, -655360},
        {1048576, -3604480, -327680},
        {185, 192},
        {216, 192},
        {185, 159},
        {216, 159},
        7
    },
    {
        {983040, -3604480, -655360},
        {1048576, -3604480, -327680},
        {983040, -3932160, -655360},
        {1048576, -3932160, -327680},
        {185, 160},
        {216, 160},
        {185, 127},
        {216, 127},
        7
    },
    {
        {1048576, -1966080, 0},
        {1048576, -1966080, 327680},
        {1048576, -2293760, 0},
        {1048576, -2293760, 327680},
        {32, 63},
        {63, 63},
        {32, 32},
        {63, 32},
        3
    },
    {
        {1048576, -1966080, -327680},
        {1048576, -1966080, 0},
        {1048576, -2293760, -327680},
        {1048576, -2293760, 0},
        {0, 63},
        {31, 63},
        {0, 32},
        {31, 32},
        3
    },
    {
        {1048576, -2293760, -327680},
        {1048576, -2293760, 0},
        {1048576, -2621440, -327680},
        {1048576, -2621440, 0},
        {0, 31},
        {31, 31},
        {0, 0},
        {31, 0},
        3
    },
    {
        {1048576, -2293760, 0},
        {1048576, -2293760, 327680},
        {1048576, -2621440, 0},
        {1048576, -2621440, 327680},
        {32, 31},
        {63, 31},
        {32, 0},
        {63, 0},
        3
    },
    {
        {1048576, -2949120, -327680},
        {1048576, -2949120, 0},
        {1048576, -3276800, -327680},
        {1048576, -3276800, 0},
        {0, 223},
        {31, 223},
        {0, 192},
        {31, 192},
        3
    },
    {
        {1048576, -2949120, 0},
        {1048576, -2949120, 327680},
        {1048576, -3276800, 0},
        {1048576, -3276800, 327680},
        {32, 223},
        {63, 223},
        {32, 192},
        {63, 192},
        3
    },
    {
        {1048576, -2621440, -327680},
        {1048576, -2621440, 0},
        {1048576, -2949120, -327680},
        {1048576, -2949120, 0},
        {0, 255},
        {31, 255},
        {0, 224},
        {31, 224},
        3
    },
    {
        {1048576, -2621440, 0},
        {1048576, -2621440, 327680},
        {1048576, -2949120, 0},
        {1048576, -2949120, 327680},
        {32, 255},
        {63, 255},
        {32, 224},
        {63, 224},
        3
    },
    {
        {1048576, -3604480, -327680},
        {1048576, -3604480, 0},
        {1048576, -3932160, -327680},
        {1048576, -3932160, 0},
        {0, 159},
        {31, 159},
        {0, 128},
        {31, 128},
        3
    },
    {
        {1048576, -3604480, 0},
        {1048576, -3604480, 327680},
        {1048576, -3932160, 0},
        {1048576, -3932160, 327680},
        {32, 159},
        {63, 159},
        {32, 128},
        {63, 128},
        3
    },
    {
        {1048576, -3276800, -327680},
        {1048576, -3276800, 0},
        {1048576, -3604480, -327680},
        {1048576, -3604480, 0},
        {0, 191},
        {31, 191},
        {0, 160},
        {31, 160},
        3
    },
    {
        {1048576, -3276800, 0},
        {1048576, -3276800, 327680},
        {1048576, -3604480, 0},
        {1048576, -3604480, 327680},
        {32, 191},
        {63, 191},
        {32, 160},
        {63, 160},
        3
    },
    {
        {1048576, -4259840, -327680},
        {1048576, -4259840, 0},
        {1048576, -4587520, -327680},
        {1048576, -4587520, 0},
        {0, 95},
        {31, 95},
        {0, 64},
        {31, 64},
        3
    },
    {
        {1048576, -4259840, 0},
        {1048576, -4259840, 327680},
        {1048576, -4587520, 0},
        {1048576, -4587520, 327680},
        {32, 95},
        {63, 95},
        {32, 64},
        {63, 64},
        3
    },
    {
        {1048576, -3932160, -327680},
        {1048576, -3932160, 0},
        {1048576, -4259840, -327680},
        {1048576, -4259840, 0},
        {0, 127},
        {31, 127},
        {0, 96},
        {31, 96},
        3
    },
    {
        {1048576, -3932160, 0},
        {1048576, -3932160, 327680},
        {1048576, -4259840, 0},
        {1048576, -4259840, 327680},
        {32, 127},
        {63, 127},
        {32, 96},
        {63, 96},
        3
    },
    {
        {-1048576, -2293760, 0},
        {-1048576, -2293760, 327680},
        {-1048576, -1966080, 0},
        {-1048576, -1966080, 327680},
        {32, 32},
        {63, 32},
        {32, 63},
        {63, 63},
        3
    },
    {
        {-1048576, -2293760, -327680},
        {-1048576, -2293760, 0},
        {-1048576, -1966080, -327680},
        {-1048576, -1966080, 0},
        {0, 32},
        {31, 32},
        {0, 63},
        {31, 63},
        3
    },
    {
        {-1048576, -2621440, -327680},
        {-1048576, -2621440, 0},
        {-1048576, -2293760, -327680},
        {-1048576, -2293760, 0},
        {0, 0},
        {31, 0},
        {0, 31},
        {31, 31},
        3
    },
    {
        {-1048576, -2949120, -327680},
        {-1048576, -2949120, 0},
        {-1048576, -2621440, -327680},
        {-1048576, -2621440, 0},
        {0, 224},
        {31, 224},
        {0, 255},
        {31, 255},
        3
    },
    {
        {-1048576, -3276800, -327680},
        {-1048576, -3276800, 0},
        {-1048576, -2949120, -327680},
        {-1048576, -2949120, 0},
        {0, 192},
        {31, 192},
        {0, 223},
        {31, 223},
        3
    },
    {
        {-1048576, -3604480, -327680},
        {-1048576, -3604480, 0},
        {-1048576, -3276800, -327680},
        {-1048576, -3276800, 0},
        {0, 160},
        {31, 160},
        {0, 191},
        {31, 191},
        3
    },
    {
        {-1048576, -3932160, -327680},
        {-1048576, -3932160, 0},
        {-1048576, -3604480, -327680},
        {-1048576, -3604480, 0},
        {0, 128},
        {31, 128},
        {0, 159},
        {31, 159},
        3
    },
    {
        {-1048576, -4259840, -327680},
        {-1048576, -4259840, 0},
        {-1048576, -3932160, -327680},
        {-1048576, -3932160, 0},
        {0, 96},
        {31, 96},
        {0, 127},
        {31, 127},
        3
    },
    {
        {-1048576, -4587520, -327680},
        {-1048576, -4587520, 0},
        {-1048576, -4259840, -327680},
        {-1048576, -4259840, 0},
        {0, 64},
        {31, 64},
        {0, 95},
        {31, 95},
        3
    },
    {
        {-1048576, -4587520, 0},
        {-1048576, -4587520, 327680},
        {-1048576, -4259840, 0},
        {-1048576, -4259840, 327680},
        {32, 64},
        {63, 64},
        {32, 95},
        {63, 95},
        3
    },
    {
        {-1048576, -4259840, 0},
        {-1048576, -4259840, 327680},
        {-1048576, -3932160, 0},
        {-1048576, -3932160, 327680},
        {32, 96},
        {63, 96},
        {32, 127},
        {63, 127},
        3
    },
    {
        {-1048576, -3932160, 0},
        {-1048576, -3932160, 327680},
        {-1048576, -3604480, 0},
        {-1048576, -3604480, 327680},
        {32, 128},
        {63, 128},
        {32, 159},
        {63, 159},
        3
    },
    {
        {-1048576, -3604480, 0},
        {-1048576, -3604480, 327680},
        {-1048576, -3276800, 0},
        {-1048576, -3276800, 327680},
        {32, 160},
        {63, 160},
        {32, 191},
        {63, 191},
        3
    },
    {
        {-1048576, -3276800, 0},
        {-1048576, -3276800, 327680},
        {-1048576, -2949120, 0},
        {-1048576, -2949120, 327680},
        {32, 192},
        {63, 192},
        {32, 223},
        {63, 223},
        3
    },
    {
        {-1048576, -2949120, 0},
        {-1048576, -2949120, 327680},
        {-1048576, -2621440, 0},
        {-1048576, -2621440, 327680},
        {32, 224},
        {63, 224},
        {32, 255},
        {63, 255},
        3
    },
    {
        {-1048576, -2621440, 0},
        {-1048576, -2621440, 327680},
        {-1048576, -2293760, 0},
        {-1048576, -2293760, 327680},
        {32, 0},
        {63, 0},
        {32, 31},
        {63, 31},
        3
    },
    {
        {0, -983040, -983040},
        {327680, -983040, -983040},
        {0, -1310720, -983040},
        {327680, -1310720, -983040},
        {128, 0},
        {128, 31},
        {159, 0},
        {159, 31},
        7
    },
    {
        {-327680, -983040, -983040},
        {0, -983040, -983040},
        {-327680, -1310720, -983040},
        {0, -1310720, -983040},
        {128, 224},
        {128, 255},
        {159, 224},
        {159, 255},
        7
    },
    {
        {0, -655360, -983040},
        {327680, -655360, -983040},
        {0, -983040, -983040},
        {327680, -983040, -983040},
        {64, 0},
        {64, 31},
        {95, 0},
        {95, 31},
        7
    },
    {
        {-327680, -655360, -983040},
        {0, -655360, -983040},
        {-327680, -983040, -983040},
        {0, -983040, -983040},
        {64, 224},
        {64, 255},
        {95, 224},
        {95, 255},
        7
    },
    {
        {0, -1638400, -983040},
        {327680, -1638400, -983040},
        {0, -1966080, -983040},
        {327680, -1966080, -983040},
        {32, 95},
        {63, 95},
        {32, 64},
        {63, 64},
        16
    },
    {
        {-327680, -1638400, -983040},
        {0, -1638400, -983040},
        {-327680, -1966080, -983040},
        {0, -1966080, -983040},
        {0, 95},
        {31, 95},
        {0, 64},
        {31, 64},
        16
    },
    {
        {-327680, -1310720, -983040},
        {0, -1310720, -983040},
        {-327680, -1638400, -983040},
        {0, -1638400, -983040},
        {0, 127},
        {31, 127},
        {0, 96},
        {31, 96},
        0
    },
    {
        {0, -1310720, -983040},
        {327680, -1310720, -983040},
        {0, -1638400, -983040},
        {327680, -1638400, -983040},
        {32, 127},
        {63, 127},
        {32, 96},
        {63, 96},
        0
    },
    {
        {0, -1966080, -983040},
        {327680, -1966080, -983040},
        {0, -2293760, -983040},
        {327680, -2293760, -983040},
        {32, 63},
        {63, 63},
        {32, 32},
        {63, 32},
        3
    },
    {
        {-327680, -1966080, -983040},
        {0, -1966080, -983040},
        {-327680, -2293760, -983040},
        {0, -2293760, -983040},
        {0, 63},
        {31, 63},
        {0, 32},
        {31, 32},
        3
    },
    {
        {-327680, -2293760, -983040},
        {0, -2293760, -983040},
        {-327680, -2621440, -983040},
        {0, -2621440, -983040},
        {0, 31},
        {31, 31},
        {0, 0},
        {31, 0},
        3
    },
    {
        {0, -2293760, -983040},
        {327680, -2293760, -983040},
        {0, -2621440, -983040},
        {327680, -2621440, -983040},
        {32, 31},
        {63, 31},
        {32, 0},
        {63, 0},
        3
    },
    {
        {-327680, -2621440, -983040},
        {0, -2621440, -983040},
        {-327680, -2949120, -983040},
        {0, -2949120, -983040},
        {0, 255},
        {31, 255},
        {0, 224},
        {31, 224},
        3
    },
    {
        {0, -2949120, -983040},
        {327680, -2949120, -983040},
        {0, -3276800, -983040},
        {327680, -3276800, -983040},
        {32, 223},
        {63, 223},
        {32, 192},
        {63, 192},
        3
    },
    {
        {-327680, -2949120, -983040},
        {0, -2949120, -983040},
        {-327680, -3276800, -983040},
        {0, -3276800, -983040},
        {0, 223},
        {31, 223},
        {0, 192},
        {31, 192},
        3
    },
    {
        {0, -2621440, -983040},
        {327680, -2621440, -983040},
        {0, -2949120, -983040},
        {327680, -2949120, -983040},
        {32, 255},
        {63, 255},
        {32, 224},
        {63, 224},
        3
    },
    {
        {-327680, -3276800, -983040},
        {0, -3276800, -983040},
        {-327680, -3604480, -983040},
        {0, -3604480, -983040},
        {0, 191},
        {31, 191},
        {0, 160},
        {31, 160},
        3
    },
    {
        {0, -3604480, -983040},
        {327680, -3604480, -983040},
        {0, -3932160, -983040},
        {327680, -3932160, -983040},
        {32, 159},
        {63, 159},
        {32, 128},
        {63, 128},
        3
    },
    {
        {-327680, -3604480, -983040},
        {0, -3604480, -983040},
        {-327680, -3932160, -983040},
        {0, -3932160, -983040},
        {0, 159},
        {31, 159},
        {0, 128},
        {31, 128},
        3
    },
    {
        {0, -3276800, -983040},
        {327680, -3276800, -983040},
        {0, -3604480, -983040},
        {327680, -3604480, -983040},
        {32, 191},
        {63, 191},
        {32, 160},
        {63, 160},
        3
    },
    {
        {-327680, -3932160, -983040},
        {0, -3932160, -983040},
        {-327680, -4259840, -983040},
        {0, -4259840, -983040},
        {0, 127},
        {31, 127},
        {0, 96},
        {31, 96},
        3
    },
    {
        {0, -4259840, -983040},
        {327680, -4259840, -983040},
        {0, -4587520, -983040},
        {327680, -4587520, -983040},
        {32, 95},
        {63, 95},
        {32, 64},
        {63, 64},
        3
    },
    {
        {-327680, -4259840, -983040},
        {0, -4259840, -983040},
        {-327680, -4587520, -983040},
        {0, -4587520, -983040},
        {0, 95},
        {31, 95},
        {0, 64},
        {31, 64},
        3
    },
    {
        {0, -3932160, -983040},
        {327680, -3932160, -983040},
        {0, -4259840, -983040},
        {327680, -4259840, -983040},
        {32, 127},
        {63, 127},
        {32, 96},
        {63, 96},
        3
    },
    {
        {-688128, -1310720, -983040},
        {-655360, -1310720, -917504},
        {-688128, -1638400, -983040},
        {-655360, -1638400, -917504},
        {0, 192},
        {15, 192},
        {0, 111},
        {15, 111},
        11
    },
    {
        {-655360, -1310720, -917504},
        {-327680, -1310720, -917504},
        {-655360, -1638400, -917504},
        {-327680, -1638400, -917504},
        {192, 128},
        {223, 128},
        {192, 95},
        {223, 95},
        4
    },
    {
        {-327680, -1638400, -983040},
        {-327680, -1638400, -917504},
        {-327680, -1310720, -983040},
        {-327680, -1310720, -917504},
        {0, 112},
        {15, 112},
        {0, 191},
        {15, 191},
        11
    },
    {
        {-688128, -1638400, -983040},
        {-655360, -1638400, -917504},
        {-688128, -1966080, -983040},
        {-655360, -1966080, -917504},
        {0, 112},
        {15, 112},
        {0, 31},
        {15, 31},
        11
    },
    {
        {-655360, -1638400, -917504},
        {-327680, -1638400, -917504},
        {-655360, -1966080, -917504},
        {-327680, -1966080, -917504},
        {192, 96},
        {223, 96},
        {192, 63},
        {223, 63},
        4
    },
    {
        {-327680, -1966080, -983040},
        {-327680, -1966080, -917504},
        {-327680, -1638400, -983040},
        {-327680, -1638400, -917504},
        {0, 32},
        {15, 32},
        {0, 111},
        {15, 111},
        11
    },
    {
        {327680, -1310720, -983040},
        {327680, -1310720, -917504},
        {327680, -1638400, -983040},
        {327680, -1638400, -917504},
        {0, 192},
        {15, 192},
        {0, 111},
        {15, 111},
        11
    },
    {
        {327680, -1310720, -917504},
        {655360, -1310720, -917504},
        {327680, -1638400, -917504},
        {655360, -1638400, -917504},
        {32, 127},
        {63, 127},
        {32, 96},
        {63, 96},
        4
    },
    {
        {688128, -1638400, -983040},
        {655360, -1638400, -917504},
        {688128, -1310720, -983040},
        {655360, -1310720, -917504},
        {0, 112},
        {15, 112},
        {0, 191},
        {15, 191},
        11
    },
    {
        {327680, -1638400, -983040},
        {327680, -1638400, -917504},
        {327680, -1966080, -983040},
        {327680, -1966080, -917504},
        {0, 112},
        {15, 112},
        {0, 31},
        {15, 31},
        11
    },
    {
        {327680, -1638400, -917504},
        {655360, -1638400, -917504},
        {327680, -1966080, -917504},
        {655360, -1966080, -917504},
        {32, 95},
        {63, 95},
        {32, 64},
        {63, 64},
        4
    },
    {
        {688128, -1966080, -983040},
        {655360, -1966080, -917504},
        {688128, -1638400, -983040},
        {655360, -1638400, -917504},
        {0, 32},
        {15, 32},
        {0, 111},
        {15, 111},
        11
    },
    {
        {-688128, -1966080, -983040},
        {-655360, -1966080, -917504},
        {-688128, -2293760, -983040},
        {-655360, -2293760, -917504},
        {0, 31},
        {15, 31},
        {0, 208},
        {15, 208},
        11
    },
    {
        {-655360, -1966080, -917504},
        {-327680, -1966080, -917504},
        {-655360, -2293760, -917504},
        {-327680, -2293760, -917504},
        {192, 64},
        {223, 64},
        {192, 31},
        {223, 31},
        15
    },
    {
        {-327680, -2293760, -983040},
        {-327680, -2293760, -917504},
        {-327680, -1966080, -983040},
        {-327680, -1966080, -917504},
        {0, 208},
        {15, 208},
        {0, 31},
        {15, 31},
        11
    },
    {
        {-688128, -2293760, -983040},
        {-655360, -2293760, -917504},
        {-688128, -2621440, -983040},
        {-655360, -2621440, -917504},
        {0, 208},
        {15, 208},
        {0, 127},
        {15, 127},
        11
    },
    {
        {-655360, -2293760, -917504},
        {-327680, -2293760, -917504},
        {-655360, -2621440, -917504},
        {-327680, -2621440, -917504},
        {192, 31},
        {223, 31},
        {192, 0},
        {223, 0},
        6
    },
    {
        {-327680, -2621440, -983040},
        {-327680, -2621440, -917504},
        {-327680, -2293760, -983040},
        {-327680, -2293760, -917504},
        {0, 128},
        {15, 128},
        {0, 207},
        {15, 207},
        11
    },
    {
        {-688128, -2621440, -983040},
        {-655360, -2621440, -917504},
        {-688128, -2949120, -983040},
        {-655360, -2949120, -917504},
        {0, 128},
        {15, 128},
        {0, 47},
        {15, 47},
        11
    },
    {
        {-655360, -2621440, -917504},
        {-327680, -2621440, -917504},
        {-655360, -2949120, -917504},
        {-327680, -2949120, -917504},
        {192, 255},
        {223, 255},
        {192, 224},
        {223, 224},
        6
    },
    {
        {-327680, -2949120, -983040},
        {-327680, -2949120, -917504},
        {-327680, -2621440, -983040},
        {-327680, -2621440, -917504},
        {0, 48},
        {15, 48},
        {0, 127},
        {15, 127},
        11
    },
    {
        {-688128, -2949120, -983040},
        {-655360, -2949120, -917504},
        {-688128, -3276800, -983040},
        {-655360, -3276800, -917504},
        {0, 47},
        {15, 47},
        {0, 224},
        {15, 224},
        11
    },
    {
        {-655360, -2949120, -917504},
        {-327680, -2949120, -917504},
        {-655360, -3276800, -917504},
        {-327680, -3276800, -917504},
        {192, 223},
        {223, 223},
        {192, 192},
        {223, 192},
        9
    },
    {
        {-327680, -3276800, -983040},
        {-327680, -3276800, -917504},
        {-327680, -2949120, -983040},
        {-327680, -2949120, -917504},
        {0, 224},
        {15, 224},
        {0, 47},
        {15, 47},
        11
    },
    {
        {327680, -2949120, -983040},
        {327680, -2949120, -917504},
        {327680, -3276800, -983040},
        {327680, -3276800, -917504},
        {0, 47},
        {15, 47},
        {0, 224},
        {15, 224},
        11
    },
    {
        {327680, -2949120, -917504},
        {655360, -2949120, -917504},
        {327680, -3276800, -917504},
        {655360, -3276800, -917504},
        {32, 223},
        {63, 223},
        {32, 192},
        {63, 192},
        9
    },
    {
        {688128, -3276800, -983040},
        {655360, -3276800, -917504},
        {688128, -2949120, -983040},
        {655360, -2949120, -917504},
        {0, 224},
        {15, 224},
        {0, 47},
        {15, 47},
        11
    },
    {
        {327680, -1966080, -983040},
        {327680, -1966080, -917504},
        {327680, -2293760, -983040},
        {327680, -2293760, -917504},
        {16, 31},
        {31, 31},
        {16, 208},
        {31, 208},
        11
    },
    {
        {327680, -1966080, -917504},
        {655360, -1966080, -917504},
        {327680, -2293760, -917504},
        {655360, -2293760, -917504},
        {32, 63},
        {63, 63},
        {32, 32},
        {63, 32},
        15
    },
    {
        {688128, -2293760, -983040},
        {655360, -2293760, -917504},
        {688128, -1966080, -983040},
        {655360, -1966080, -917504},
        {0, 208},
        {15, 208},
        {0, 31},
        {15, 31},
        11
    },
    {
        {327680, -2293760, -983040},
        {327680, -2293760, -917504},
        {327680, -2621440, -983040},
        {327680, -2621440, -917504},
        {0, 208},
        {15, 208},
        {0, 127},
        {15, 127},
        11
    },
    {
        {327680, -2293760, -917504},
        {655360, -2293760, -917504},
        {327680, -2621440, -917504},
        {655360, -2621440, -917504},
        {32, 31},
        {63, 31},
        {32, 0},
        {63, 0},
        6
    },
    {
        {688128, -2621440, -983040},
        {655360, -2621440, -917504},
        {688128, -2293760, -983040},
        {655360, -2293760, -917504},
        {0, 128},
        {15, 128},
        {0, 207},
        {15, 207},
        11
    },
    {
        {327680, -2621440, -983040},
        {327680, -2621440, -917504},
        {327680, -2949120, -983040},
        {327680, -2949120, -917504},
        {0, 128},
        {15, 128},
        {0, 47},
        {15, 47},
        11
    },
    {
        {327680, -2621440, -917504},
        {655360, -2621440, -917504},
        {327680, -2949120, -917504},
        {655360, -2949120, -917504},
        {32, 255},
        {63, 255},
        {32, 224},
        {63, 224},
        6
    },
    {
        {688128, -2949120, -983040},
        {655360, -2949120, -917504},
        {688128, -2621440, -983040},
        {655360, -2621440, -917504},
        {0, 48},
        {15, 48},
        {0, 127},
        {15, 127},
        11
    },
    {
        {327680, -3604480, -983040},
        {327680, -3604480, -917504},
        {327680, -3932160, -983040},
        {327680, -3932160, -917504},
        {0, 144},
        {15, 144},
        {0, 63},
        {15, 63},
        11
    },
    {
        {327680, -3604480, -917504},
        {655360, -3604480, -917504},
        {327680, -3932160, -917504},
        {655360, -3932160, -917504},
        {32, 159},
        {63, 159},
        {32, 128},
        {63, 128},
        4
    },
    {
        {688128, -3932160, -983040},
        {655360, -3932160, -917504},
        {688128, -3604480, -983040},
        {655360, -3604480, -917504},
        {0, 64},
        {15, 64},
        {0, 143},
        {15, 143},
        11
    },
    {
        {327680, -3276800, -983040},
        {327680, -3276800, -917504},
        {327680, -3604480, -983040},
        {327680, -3604480, -917504},
        {0, 224},
        {15, 224},
        {0, 143},
        {15, 143},
        11
    },
    {
        {327680, -3276800, -917504},
        {655360, -3276800, -917504},
        {327680, -3604480, -917504},
        {655360, -3604480, -917504},
        {32, 191},
        {63, 191},
        {32, 160},
        {63, 160},
        4
    },
    {
        {688128, -3604480, -983040},
        {655360, -3604480, -917504},
        {688128, -3276800, -983040},
        {655360, -3276800, -917504},
        {0, 144},
        {15, 144},
        {0, 223},
        {15, 223},
        11
    },
    {
        {327680, -4259840, -983040},
        {327680, -4259840, -917504},
        {327680, -4587520, -983040},
        {327680, -4587520, -917504},
        {0, 240},
        {15, 240},
        {0, 159},
        {15, 159},
        11
    },
    {
        {327680, -4259840, -917504},
        {655360, -4259840, -917504},
        {327680, -4587520, -917504},
        {655360, -4587520, -917504},
        {32, 95},
        {63, 95},
        {32, 64},
        {63, 64},
        4
    },
    {
        {688128, -4587520, -983040},
        {655360, -4587520, -917504},
        {688128, -4259840, -983040},
        {655360, -4259840, -917504},
        {0, 160},
        {15, 160},
        {0, 239},
        {15, 239},
        11
    },
    {
        {327680, -3932160, -983040},
        {327680, -3932160, -917504},
        {327680, -4259840, -983040},
        {327680, -4259840, -917504},
        {0, 63},
        {15, 63},
        {0, 240},
        {15, 240},
        11
    },
    {
        {327680, -3932160, -917504},
        {655360, -3932160, -917504},
        {327680, -4259840, -917504},
        {655360, -4259840, -917504},
        {32, 127},
        {63, 127},
        {32, 96},
        {63, 96},
        4
    },
    {
        {688128, -4259840, -983040},
        {655360, -4259840, -917504},
        {688128, -3932160, -983040},
        {655360, -3932160, -917504},
        {0, 240},
        {15, 240},
        {0, 63},
        {15, 63},
        11
    },
    {
        {-688128, -3604480, -983040},
        {-655360, -3604480, -917504},
        {-688128, -3932160, -983040},
        {-655360, -3932160, -917504},
        {0, 144},
        {15, 144},
        {0, 63},
        {15, 63},
        11
    },
    {
        {-655360, -3604480, -917504},
        {-327680, -3604480, -917504},
        {-655360, -3932160, -917504},
        {-327680, -3932160, -917504},
        {192, 160},
        {223, 160},
        {192, 127},
        {223, 127},
        4
    },
    {
        {-327680, -3932160, -983040},
        {-327680, -3932160, -917504},
        {-327680, -3604480, -983040},
        {-327680, -3604480, -917504},
        {0, 64},
        {15, 64},
        {0, 143},
        {15, 143},
        11
    },
    {
        {-688128, -3276800, -983040},
        {-655360, -3276800, -917504},
        {-688128, -3604480, -983040},
        {-655360, -3604480, -917504},
        {0, 224},
        {15, 224},
        {0, 143},
        {15, 143},
        11
    },
    {
        {-655360, -3276800, -917504},
        {-327680, -3276800, -917504},
        {-655360, -3604480, -917504},
        {-327680, -3604480, -917504},
        {192, 192},
        {223, 192},
        {192, 159},
        {223, 159},
        4
    },
    {
        {-327680, -3604480, -983040},
        {-327680, -3604480, -917504},
        {-327680, -3276800, -983040},
        {-327680, -3276800, -917504},
        {0, 144},
        {15, 144},
        {0, 223},
        {15, 223},
        11
    },
    {
        {-688128, -4259840, -983040},
        {-655360, -4259840, -917504},
        {-688128, -4587520, -983040},
        {-655360, -4587520, -917504},
        {0, 240},
        {15, 240},
        {0, 159},
        {15, 159},
        11
    },
    {
        {-655360, -4259840, -917504},
        {-327680, -4259840, -917504},
        {-655360, -4587520, -917504},
        {-327680, -4587520, -917504},
        {192, 96},
        {223, 96},
        {192, 63},
        {223, 63},
        4
    },
    {
        {-327680, -4587520, -983040},
        {-327680, -4587520, -917504},
        {-327680, -4259840, -983040},
        {-327680, -4259840, -917504},
        {0, 160},
        {15, 160},
        {0, 239},
        {15, 239},
        11
    },
    {
        {-688128, -3932160, -983040},
        {-655360, -3932160, -917504},
        {-688128, -4259840, -983040},
        {-655360, -4259840, -917504},
        {0, 63},
        {15, 63},
        {0, 240},
        {15, 240},
        11
    },
    {
        {-655360, -3932160, -917504},
        {-327680, -3932160, -917504},
        {-655360, -4259840, -917504},
        {-327680, -4259840, -917504},
        {192, 128},
        {223, 128},
        {192, 95},
        {223, 95},
        4
    },
    {
        {-327680, -4259840, -983040},
        {-327680, -4259840, -917504},
        {-327680, -3932160, -983040},
        {-327680, -3932160, -917504},
        {0, 240},
        {15, 240},
        {0, 63},
        {15, 63},
        11
    },
    {
        {327680, -4259840, 917504},
        {327680, -4259840, 983040},
        {327680, -4587520, 917504},
        {327680, -4587520, 983040},
        {208, 239},
        {223, 239},
        {208, 160},
        {223, 160},
        11
    },
    {
        {327680, -4587520, 917504},
        {655360, -4587520, 917504},
        {327680, -4259840, 917504},
        {655360, -4259840, 917504},
        {32, 64},
        {63, 64},
        {32, 95},
        {63, 95},
        4
    },
    {
        {655360, -4587520, 917504},
        {688128, -4587520, 983040},
        {655360, -4259840, 917504},
        {688128, -4259840, 983040},
        {208, 160},
        {223, 160},
        {208, 239},
        {223, 239},
        11
    },
    {
        {327680, -3932160, 917504},
        {327680, -3932160, 983040},
        {327680, -4259840, 917504},
        {327680, -4259840, 983040},
        {208, 63},
        {223, 63},
        {208, 240},
        {223, 240},
        11
    },
    {
        {327680, -4259840, 917504},
        {655360, -4259840, 917504},
        {327680, -3932160, 917504},
        {655360, -3932160, 917504},
        {32, 96},
        {63, 96},
        {32, 127},
        {63, 127},
        4
    },
    {
        {655360, -4259840, 917504},
        {688128, -4259840, 983040},
        {655360, -3932160, 917504},
        {688128, -3932160, 983040},
        {208, 240},
        {223, 240},
        {208, 63},
        {223, 63},
        11
    },
    {
        {327680, -3604480, 917504},
        {327680, -3604480, 983040},
        {327680, -3932160, 917504},
        {327680, -3932160, 983040},
        {208, 144},
        {223, 144},
        {208, 63},
        {223, 63},
        11
    },
    {
        {327680, -3932160, 917504},
        {655360, -3932160, 917504},
        {327680, -3604480, 917504},
        {655360, -3604480, 917504},
        {32, 128},
        {63, 128},
        {32, 159},
        {63, 159},
        4
    },
    {
        {655360, -3932160, 917504},
        {688128, -3932160, 983040},
        {655360, -3604480, 917504},
        {688128, -3604480, 983040},
        {208, 64},
        {223, 64},
        {208, 143},
        {223, 143},
        11
    },
    {
        {327680, -3276800, 917504},
        {327680, -3276800, 983040},
        {327680, -3604480, 917504},
        {327680, -3604480, 983040},
        {208, 223},
        {223, 223},
        {208, 144},
        {223, 144},
        11
    },
    {
        {327680, -3604480, 917504},
        {655360, -3604480, 917504},
        {327680, -3276800, 917504},
        {655360, -3276800, 917504},
        {32, 160},
        {63, 160},
        {32, 191},
        {63, 191},
        4
    },
    {
        {655360, -3604480, 917504},
        {688128, -3604480, 983040},
        {655360, -3276800, 917504},
        {688128, -3276800, 983040},
        {208, 144},
        {223, 144},
        {208, 223},
        {223, 223},
        11
    },
    {
        {327680, -2949120, 917504},
        {327680, -2949120, 983040},
        {327680, -3276800, 917504},
        {327680, -3276800, 983040},
        {208, 47},
        {223, 47},
        {208, 224},
        {223, 224},
        11
    },
    {
        {327680, -3276800, 917504},
        {655360, -3276800, 917504},
        {327680, -2949120, 917504},
        {655360, -2949120, 917504},
        {32, 192},
        {63, 192},
        {32, 223},
        {63, 223},
        9
    },
    {
        {655360, -3276800, 917504},
        {688128, -3276800, 983040},
        {655360, -2949120, 917504},
        {688128, -2949120, 983040},
        {208, 224},
        {223, 224},
        {208, 47},
        {223, 47},
        11
    },
    {
        {327680, -2621440, 917504},
        {327680, -2621440, 983040},
        {327680, -2949120, 917504},
        {327680, -2949120, 983040},
        {208, 128},
        {223, 128},
        {208, 47},
        {223, 47},
        11
    },
    {
        {327680, -2949120, 917504},
        {655360, -2949120, 917504},
        {327680, -2621440, 917504},
        {655360, -2621440, 917504},
        {32, 224},
        {63, 224},
        {32, 255},
        {63, 255},
        6
    },
    {
        {655360, -2949120, 917504},
        {688128, -2949120, 983040},
        {655360, -2621440, 917504},
        {688128, -2621440, 983040},
        {208, 48},
        {223, 48},
        {208, 127},
        {223, 127},
        11
    },
    {
        {327680, -2293760, 917504},
        {327680, -2293760, 983040},
        {327680, -2621440, 917504},
        {327680, -2621440, 983040},
        {208, 208},
        {223, 208},
        {208, 127},
        {223, 127},
        11
    },
    {
        {327680, -2621440, 917504},
        {655360, -2621440, 917504},
        {327680, -2293760, 917504},
        {655360, -2293760, 917504},
        {32, 0},
        {63, 0},
        {32, 31},
        {63, 31},
        6
    },
    {
        {655360, -2621440, 917504},
        {688128, -2621440, 983040},
        {655360, -2293760, 917504},
        {688128, -2293760, 983040},
        {208, 128},
        {223, 128},
        {208, 207},
        {223, 207},
        11
    },
    {
        {327680, -1966080, 917504},
        {327680, -1966080, 983040},
        {327680, -2293760, 917504},
        {327680, -2293760, 983040},
        {224, 31},
        {239, 31},
        {224, 208},
        {239, 208},
        11
    },
    {
        {327680, -2293760, 917504},
        {655360, -2293760, 917504},
        {327680, -1966080, 917504},
        {655360, -1966080, 917504},
        {32, 32},
        {63, 32},
        {32, 63},
        {63, 63},
        15
    },
    {
        {655360, -2293760, 917504},
        {688128, -2293760, 983040},
        {655360, -1966080, 917504},
        {688128, -1966080, 983040},
        {208, 208},
        {223, 208},
        {208, 31},
        {223, 31},
        11
    },
    {
        {327680, -1638400, 917504},
        {327680, -1638400, 983040},
        {327680, -1966080, 917504},
        {327680, -1966080, 983040},
        {208, 112},
        {223, 112},
        {208, 31},
        {223, 31},
        11
    },
    {
        {327680, -1966080, 917504},
        {655360, -1966080, 917504},
        {327680, -1638400, 917504},
        {655360, -1638400, 917504},
        {32, 64},
        {63, 64},
        {32, 95},
        {63, 95},
        4
    },
    {
        {655360, -1966080, 917504},
        {688128, -1966080, 983040},
        {655360, -1638400, 917504},
        {688128, -1638400, 983040},
        {208, 32},
        {223, 32},
        {208, 111},
        {223, 111},
        11
    },
    {
        {327680, -1310720, 917504},
        {327680, -1310720, 983040},
        {327680, -1638400, 917504},
        {327680, -1638400, 983040},
        {208, 192},
        {223, 192},
        {208, 111},
        {223, 111},
        11
    },
    {
        {327680, -1638400, 917504},
        {655360, -1638400, 917504},
        {327680, -1310720, 917504},
        {655360, -1310720, 917504},
        {32, 96},
        {63, 96},
        {32, 127},
        {63, 127},
        4
    },
    {
        {655360, -1638400, 917504},
        {688128, -1638400, 983040},
        {655360, -1310720, 917504},
        {688128, -1310720, 983040},
        {208, 112},
        {223, 112},
        {208, 191},
        {223, 191},
        11
    },
    {
        {327680, -983040, 917504},
        {327680, -983040, 983040},
        {327680, -1310720, 917504},
        {327680, -1310720, 983040},
        {208, 15},
        {223, 15},
        {208, 192},
        {223, 192},
        11
    },
    {
        {327680, -1310720, 917504},
        {655360, -1310720, 917504},
        {327680, -983040, 917504},
        {655360, -983040, 917504},
        {32, 128},
        {63, 128},
        {32, 159},
        {63, 159},
        9
    },
    {
        {655360, -1310720, 917504},
        {688128, -1310720, 983040},
        {655360, -983040, 917504},
        {688128, -983040, 983040},
        {208, 192},
        {223, 192},
        {208, 15},
        {223, 15},
        11
    },
    {
        {-655360, -4259840, 917504},
        {-688128, -4259840, 983040},
        {-655360, -4587520, 917504},
        {-688128, -4587520, 983040},
        {208, 239},
        {223, 239},
        {208, 160},
        {223, 160},
        11
    },
    {
        {-655360, -4587520, 917504},
        {-327680, -4587520, 917504},
        {-655360, -4259840, 917504},
        {-327680, -4259840, 917504},
        {192, 64},
        {223, 64},
        {192, 95},
        {223, 95},
        4
    },
    {
        {-327680, -4587520, 917504},
        {-327680, -4587520, 983040},
        {-327680, -4259840, 917504},
        {-327680, -4259840, 983040},
        {208, 160},
        {223, 160},
        {208, 239},
        {223, 239},
        11
    },
    {
        {-655360, -3932160, 917504},
        {-688128, -3932160, 983040},
        {-655360, -4259840, 917504},
        {-688128, -4259840, 983040},
        {208, 63},
        {223, 63},
        {208, 240},
        {223, 240},
        11
    },
    {
        {-655360, -4259840, 917504},
        {-327680, -4259840, 917504},
        {-655360, -3932160, 917504},
        {-327680, -3932160, 917504},
        {192, 96},
        {223, 96},
        {192, 127},
        {223, 127},
        4
    },
    {
        {-327680, -4259840, 917504},
        {-327680, -4259840, 983040},
        {-327680, -3932160, 917504},
        {-327680, -3932160, 983040},
        {208, 240},
        {223, 240},
        {208, 63},
        {223, 63},
        11
    },
    {
        {-655360, -3604480, 917504},
        {-688128, -3604480, 983040},
        {-655360, -3932160, 917504},
        {-688128, -3932160, 983040},
        {208, 144},
        {223, 144},
        {208, 63},
        {223, 63},
        11
    },
    {
        {-655360, -3932160, 917504},
        {-327680, -3932160, 917504},
        {-655360, -3604480, 917504},
        {-327680, -3604480, 917504},
        {192, 128},
        {223, 128},
        {192, 159},
        {223, 159},
        4
    },
    {
        {-327680, -3932160, 917504},
        {-327680, -3932160, 983040},
        {-327680, -3604480, 917504},
        {-327680, -3604480, 983040},
        {208, 64},
        {223, 64},
        {208, 143},
        {223, 143},
        11
    },
    {
        {-655360, -3276800, 917504},
        {-688128, -3276800, 983040},
        {-655360, -3604480, 917504},
        {-688128, -3604480, 983040},
        {208, 223},
        {223, 223},
        {208, 144},
        {223, 144},
        11
    },
    {
        {-655360, -3604480, 917504},
        {-327680, -3604480, 917504},
        {-655360, -3276800, 917504},
        {-327680, -3276800, 917504},
        {192, 160},
        {223, 160},
        {192, 191},
        {223, 191},
        4
    },
    {
        {-327680, -3604480, 917504},
        {-327680, -3604480, 983040},
        {-327680, -3276800, 917504},
        {-327680, -3276800, 983040},
        {208, 144},
        {223, 144},
        {208, 223},
        {223, 223},
        11
    },
    {
        {-655360, -2949120, 917504},
        {-688128, -2949120, 983040},
        {-655360, -3276800, 917504},
        {-688128, -3276800, 983040},
        {208, 47},
        {223, 47},
        {208, 224},
        {223, 224},
        11
    },
    {
        {-655360, -3276800, 917504},
        {-327680, -3276800, 917504},
        {-655360, -2949120, 917504},
        {-327680, -2949120, 917504},
        {192, 192},
        {223, 192},
        {192, 223},
        {223, 223},
        9
    },
    {
        {-327680, -3276800, 917504},
        {-327680, -3276800, 983040},
        {-327680, -2949120, 917504},
        {-327680, -2949120, 983040},
        {208, 224},
        {223, 224},
        {208, 47},
        {223, 47},
        11
    },
    {
        {-655360, -2621440, 917504},
        {-688128, -2621440, 983040},
        {-655360, -2949120, 917504},
        {-688128, -2949120, 983040},
        {208, 128},
        {223, 128},
        {208, 47},
        {223, 47},
        11
    },
    {
        {-655360, -2949120, 917504},
        {-327680, -2949120, 917504},
        {-655360, -2621440, 917504},
        {-327680, -2621440, 917504},
        {192, 224},
        {223, 224},
        {192, 255},
        {223, 255},
        6
    },
    {
        {-327680, -2949120, 917504},
        {-327680, -2949120, 983040},
        {-327680, -2621440, 917504},
        {-327680, -2621440, 983040},
        {208, 48},
        {223, 48},
        {208, 127},
        {223, 127},
        11
    },
    {
        {-655360, -2293760, 917504},
        {-688128, -2293760, 983040},
        {-655360, -2621440, 917504},
        {-688128, -2621440, 983040},
        {208, 208},
        {223, 208},
        {208, 127},
        {223, 127},
        11
    },
    {
        {-655360, -2621440, 917504},
        {-327680, -2621440, 917504},
        {-655360, -2293760, 917504},
        {-327680, -2293760, 917504},
        {192, 0},
        {223, 0},
        {192, 31},
        {223, 31},
        6
    },
    {
        {-327680, -2621440, 917504},
        {-327680, -2621440, 983040},
        {-327680, -2293760, 917504},
        {-327680, -2293760, 983040},
        {208, 128},
        {223, 128},
        {208, 207},
        {223, 207},
        11
    },
    {
        {-655360, -1966080, 917504},
        {-688128, -1966080, 983040},
        {-655360, -2293760, 917504},
        {-688128, -2293760, 983040},
        {208, 31},
        {223, 31},
        {208, 208},
        {223, 208},
        11
    },
    {
        {-655360, -2293760, 917504},
        {-327680, -2293760, 917504},
        {-655360, -1966080, 917504},
        {-327680, -1966080, 917504},
        {192, 32},
        {223, 32},
        {192, 63},
        {223, 63},
        15
    },
    {
        {-327680, -2293760, 917504},
        {-327680, -2293760, 983040},
        {-327680, -1966080, 917504},
        {-327680, -1966080, 983040},
        {208, 208},
        {223, 208},
        {208, 31},
        {223, 31},
        11
    },
    {
        {-655360, -1638400, 917504},
        {-688128, -1638400, 983040},
        {-655360, -1966080, 917504},
        {-688128, -1966080, 983040},
        {208, 112},
        {223, 112},
        {208, 31},
        {223, 31},
        11
    },
    {
        {-655360, -1966080, 917504},
        {-327680, -1966080, 917504},
        {-655360, -1638400, 917504},
        {-327680, -1638400, 917504},
        {192, 64},
        {223, 64},
        {192, 95},
        {223, 95},
        4
    },
    {
        {-327680, -1966080, 917504},
        {-327680, -1966080, 983040},
        {-327680, -1638400, 917504},
        {-327680, -1638400, 983040},
        {208, 32},
        {223, 32},
        {208, 111},
        {223, 111},
        11
    },
    {
        {-655360, -1310720, 917504},
        {-688128, -1310720, 983040},
        {-655360, -1638400, 917504},
        {-688128, -1638400, 983040},
        {208, 192},
        {223, 192},
        {208, 111},
        {223, 111},
        11
    },
    {
        {-655360, -1638400, 917504},
        {-327680, -1638400, 917504},
        {-655360, -1310720, 917504},
        {-327680, -1310720, 917504},
        {192, 96},
        {223, 96},
        {192, 127},
        {223, 127},
        4
    },
    {
        {-327680, -1638400, 917504},
        {-327680, -1638400, 983040},
        {-327680, -1310720, 917504},
        {-327680, -1310720, 983040},
        {208, 112},
        {223, 112},
        {208, 191},
        {223, 191},
        11
    },
    {
        {-655360, -983040, 917504},
        {-688128, -983040, 983040},
        {-655360, -1310720, 917504},
        {-688128, -1310720, 983040},
        {208, 15},
        {223, 15},
        {208, 192},
        {223, 192},
        11
    },
    {
        {-655360, -1310720, 917504},
        {-327680, -1310720, 917504},
        {-655360, -983040, 917504},
        {-327680, -983040, 917504},
        {192, 128},
        {223, 128},
        {192, 159},
        {223, 159},
        9
    },
    {
        {-327680, -1310720, 917504},
        {-327680, -1310720, 983040},
        {-327680, -983040, 917504},
        {-327680, -983040, 983040},
        {208, 192},
        {223, 192},
        {208, 15},
        {223, 15},
        11
    },
    {
        {-655360, -655360, 917504},
        {-688128, -655360, 983040},
        {-655360, -983040, 917504},
        {-688128, -983040, 983040},
        {208, 96},
        {223, 96},
        {208, 15},
        {223, 15},
        11
    },
    {
        {-655360, -983040, 917504},
        {-327680, -983040, 917504},
        {-655360, -655360, 917504},
        {-327680, -655360, 917504},
        {192, 160},
        {223, 160},
        {192, 191},
        {223, 191},
        6
    },
    {
        {-327680, -983040, 917504},
        {-327680, -983040, 983040},
        {-327680, -655360, 917504},
        {-327680, -655360, 983040},
        {208, 16},
        {223, 16},
        {208, 95},
        {223, 95},
        11
    },
    {
        {-655360, -327680, 917504},
        {-688128, -327680, 983040},
        {-655360, -655360, 917504},
        {-688128, -655360, 983040},
        {208, 176},
        {223, 176},
        {208, 95},
        {223, 95},
        11
    },
    {
        {-655360, -655360, 917504},
        {-327680, -655360, 917504},
        {-655360, -327680, 917504},
        {-327680, -327680, 917504},
        {192, 192},
        {223, 192},
        {192, 223},
        {223, 223},
        6
    },
    {
        {-327680, -655360, 917504},
        {-327680, -655360, 983040},
        {-327680, -327680, 917504},
        {-327680, -327680, 983040},
        {208, 96},
        {223, 96},
        {208, 175},
        {223, 175},
        11
    },
    {
        {-655360, 0, 917504},
        {-688128, 0, 983040},
        {-655360, -327680, 917504},
        {-688128, -327680, 983040},
        {208, 255},
        {223, 255},
        {208, 176},
        {223, 176},
        11
    },
    {
        {-655360, -327680, 917504},
        {-327680, -327680, 917504},
        {-655360, 0, 917504},
        {-327680, 0, 917504},
        {192, 224},
        {223, 224},
        {192, 255},
        {223, 255},
        15
    },
    {
        {-327680, -327680, 917504},
        {-327680, -327680, 983040},
        {-327680, 0, 917504},
        {-327680, 0, 983040},
        {208, 176},
        {223, 176},
        {208, 255},
        {223, 255},
        11
    },
    {
        {327680, 0, 917504},
        {327680, 0, 983040},
        {327680, -327680, 917504},
        {327680, -327680, 983040},
        {224, 255},
        {239, 255},
        {224, 176},
        {239, 176},
        11
    },
    {
        {327680, -327680, 917504},
        {655360, -327680, 917504},
        {327680, 0, 917504},
        {655360, 0, 917504},
        {32, 224},
        {63, 224},
        {32, 255},
        {63, 255},
        15
    },
    {
        {655360, -327680, 917504},
        {688128, -327680, 983040},
        {655360, 0, 917504},
        {688128, 0, 983040},
        {208, 176},
        {223, 176},
        {208, 255},
        {223, 255},
        11
    },
    {
        {327680, -327680, 917504},
        {327680, -327680, 983040},
        {327680, -655360, 917504},
        {327680, -655360, 983040},
        {208, 176},
        {223, 176},
        {208, 95},
        {223, 95},
        11
    },
    {
        {327680, -655360, 917504},
        {655360, -655360, 917504},
        {327680, -327680, 917504},
        {655360, -327680, 917504},
        {32, 192},
        {63, 192},
        {32, 223},
        {63, 223},
        6
    },
    {
        {655360, -655360, 917504},
        {688128, -655360, 983040},
        {655360, -327680, 917504},
        {688128, -327680, 983040},
        {208, 96},
        {223, 96},
        {208, 175},
        {223, 175},
        11
    },
    {
        {327680, -655360, 917504},
        {327680, -655360, 983040},
        {327680, -983040, 917504},
        {327680, -983040, 983040},
        {208, 96},
        {223, 96},
        {208, 15},
        {223, 15},
        11
    },
    {
        {327680, -983040, 917504},
        {655360, -983040, 917504},
        {327680, -655360, 917504},
        {655360, -655360, 917504},
        {32, 160},
        {63, 160},
        {32, 191},
        {63, 191},
        6
    },
    {
        {655360, -983040, 917504},
        {688128, -983040, 983040},
        {655360, -655360, 917504},
        {688128, -655360, 983040},
        {208, 16},
        {223, 16},
        {208, 95},
        {223, 95},
        11
    },
    {
        {0, -1638400, 917504},
        {327680, -1638400, 917504},
        {0, -1310720, 917504},
        {327680, -1310720, 917504},
        {32, 96},
        {63, 96},
        {32, 127},
        {63, 127},
        0
    },
    {
        {0, -1310720, 917504},
        {327680, -1310720, 917504},
        {0, -1310720, 983040},
        {327680, -1310720, 983040},
        {0, 171},
        {31, 171},
        {0, 166},
        {31, 166},
        11
    },
    {
        {-327680, -1638400, 917504},
        {0, -1638400, 917504},
        {-327680, -1310720, 917504},
        {0, -1310720, 917504},
        {0, 96},
        {31, 96},
        {0, 127},
        {31, 127},
        0
    },
    {
        {-327680, -1310720, 917504},
        {0, -1310720, 917504},
        {-327680, -1310720, 983040},
        {0, -1310720, 983040},
        {224, 172},
        {255, 172},
        {224, 165},
        {255, 165},
        11
    },
    {
        {-327680, -1966080, 917504},
        {0, -1966080, 917504},
        {-327680, -1638400, 917504},
        {0, -1638400, 917504},
        {0, 64},
        {31, 64},
        {0, 95},
        {31, 95},
        16
    },
    {
        {-327680, -2293760, 917504},
        {0, -2293760, 917504},
        {-327680, -1966080, 917504},
        {0, -1966080, 917504},
        {0, 32},
        {31, 32},
        {0, 63},
        {31, 63},
        3
    },
    {
        {-327680, -2621440, 917504},
        {0, -2621440, 917504},
        {-327680, -2293760, 917504},
        {0, -2293760, 917504},
        {0, 0},
        {31, 0},
        {0, 31},
        {31, 31},
        3
    },
    {
        {-327680, -2949120, 917504},
        {0, -2949120, 917504},
        {-327680, -2621440, 917504},
        {0, -2621440, 917504},
        {0, 224},
        {31, 224},
        {0, 255},
        {31, 255},
        3
    },
    {
        {-327680, -3276800, 917504},
        {0, -3276800, 917504},
        {-327680, -2949120, 917504},
        {0, -2949120, 917504},
        {0, 192},
        {31, 192},
        {0, 223},
        {31, 223},
        3
    },
    {
        {-327680, -3604480, 917504},
        {0, -3604480, 917504},
        {-327680, -3276800, 917504},
        {0, -3276800, 917504},
        {0, 160},
        {31, 160},
        {0, 191},
        {31, 191},
        3
    },
    {
        {-327680, -3932160, 917504},
        {0, -3932160, 917504},
        {-327680, -3604480, 917504},
        {0, -3604480, 917504},
        {0, 128},
        {31, 128},
        {0, 159},
        {31, 159},
        3
    },
    {
        {-327680, -4259840, 917504},
        {0, -4259840, 917504},
        {-327680, -3932160, 917504},
        {0, -3932160, 917504},
        {0, 96},
        {31, 96},
        {0, 127},
        {31, 127},
        3
    },
    {
        {-327680, -4587520, 917504},
        {0, -4587520, 917504},
        {-327680, -4259840, 917504},
        {0, -4259840, 917504},
        {0, 64},
        {31, 64},
        {0, 95},
        {31, 95},
        3
    },
    {
        {0, -4587520, 917504},
        {327680, -4587520, 917504},
        {0, -4259840, 917504},
        {327680, -4259840, 917504},
        {32, 64},
        {63, 64},
        {32, 95},
        {63, 95},
        3
    },
    {
        {0, -4259840, 917504},
        {327680, -4259840, 917504},
        {0, -3932160, 917504},
        {327680, -3932160, 917504},
        {32, 96},
        {63, 96},
        {32, 127},
        {63, 127},
        3
    },
    {
        {0, -3932160, 917504},
        {327680, -3932160, 917504},
        {0, -3604480, 917504},
        {327680, -3604480, 917504},
        {32, 128},
        {63, 128},
        {32, 159},
        {63, 159},
        3
    },
    {
        {0, -3604480, 917504},
        {327680, -3604480, 917504},
        {0, -3276800, 917504},
        {327680, -3276800, 917504},
        {32, 160},
        {63, 160},
        {32, 191},
        {63, 191},
        3
    },
    {
        {0, -3276800, 917504},
        {327680, -3276800, 917504},
        {0, -2949120, 917504},
        {327680, -2949120, 917504},
        {32, 192},
        {63, 192},
        {32, 223},
        {63, 223},
        3
    },
    {
        {0, -2949120, 917504},
        {327680, -2949120, 917504},
        {0, -2621440, 917504},
        {327680, -2621440, 917504},
        {32, 224},
        {63, 224},
        {32, 255},
        {63, 255},
        3
    },
    {
        {0, -2621440, 917504},
        {327680, -2621440, 917504},
        {0, -2293760, 917504},
        {327680, -2293760, 917504},
        {32, 0},
        {63, 0},
        {32, 31},
        {63, 31},
        3
    },
    {
        {0, -2293760, 917504},
        {327680, -2293760, 917504},
        {0, -1966080, 917504},
        {327680, -1966080, 917504},
        {32, 32},
        {63, 32},
        {32, 63},
        {63, 63},
        3
    },
    {
        {0, -1966080, 917504},
        {327680, -1966080, 917504},
        {0, -1638400, 917504},
        {327680, -1638400, 917504},
        {32, 64},
        {63, 64},
        {32, 95},
        {63, 95},
        16
    },
    {
        {-327680, -655360, 950272},
        {-196608, -655360, 950272},
        {-327680, 0, 950272},
        {-196608, 0, 950272},
        {176, 96},
        {207, 96},
        {176, 255},
        {207, 255},
        11
    },
    {
        {-327680, 0, 983040},
        {-196608, 0, 983040},
        {-327680, -655360, 983040},
        {-196608, -655360, 983040},
        {176, 255},
        {207, 255},
        {176, 96},
        {207, 96},
        11
    },
    {
        {-196608, -655360, 950272},
        {-196608, -655360, 983040},
        {-196608, 0, 950272},
        {-196608, 0, 983040},
        {232, 96},
        {239, 96},
        {232, 255},
        {239, 255},
        11
    },
    {
        {196608, 0, 950272},
        {196608, 0, 983040},
        {196608, -655360, 950272},
        {196608, -655360, 983040},
        {232, 255},
        {239, 255},
        {232, 96},
        {239, 96},
        11
    },
    {
        {196608, -655360, 950272},
        {327680, -655360, 950272},
        {196608, 0, 950272},
        {327680, 0, 950272},
        {48, 96},
        {79, 96},
        {48, 255},
        {79, 255},
        11
    },
    {
        {196608, 0, 983040},
        {327680, 0, 983040},
        {196608, -655360, 983040},
        {327680, -655360, 983040},
        {48, 255},
        {79, 255},
        {48, 96},
        {79, 96},
        11
    },
    {
        {-229376, -491520, 982528},
        {-229376, -491520, 1015808},
        {-229376, -655360, 982528},
        {-229376, -655360, 1015808},
        {71, 217},
        {73, 217},
        {71, 203},
        {73, 203},
        11
    },
    {
        {-229376, -655360, 982528},
        {229376, -655360, 982528},
        {-229376, -491520, 982528},
        {229376, -491520, 982528},
        {249, 189},
        {37, 189},
        {249, 204},
        {37, 204},
        5
    },
    {
        {-229376, -491520, 982528},
        {229376, -491520, 982528},
        {-229376, -491520, 1015808},
        {229376, -491520, 1015808},
        {219, 174},
        {3, 174},
        {219, 171},
        {3, 171},
        11
    },
    {
        {-229376, -655360, 1015808},
        {229376, -655360, 1015808},
        {-229376, -655360, 982528},
        {229376, -655360, 982528},
        {219, 171},
        {3, 171},
        {219, 174},
        {3, 174},
        11
    },
    {
        {-229376, -491520, 1015808},
        {229376, -491520, 1015808},
        {-229376, -655360, 1015808},
        {229376, -655360, 1015808},
        {219, 218},
        {3, 218},
        {219, 203},
        {3, 203},
        11
    },
    {
        {229376, -655360, 982528},
        {229376, -655360, 1015808},
        {229376, -491520, 982528},
        {229376, -491520, 1015808},
        {71, 203},
        {73, 203},
        {71, 217},
        {73, 217},
        11
    },
    {
        {-327680, -688128, 917504},
        {0, -688128, 917504},
        {-327680, -655360, 917504},
        {0, -655360, 917504},
        {176, 88},
        {255, 88},
        {176, 95},
        {255, 95},
        11
    },
    {
        {-327680, -655360, 917504},
        {0, -655360, 917504},
        {-327680, -655360, 983040},
        {0, -655360, 983040},
        {176, 32},
        {255, 32},
        {176, 15},
        {255, 15},
        11
    },
    {
        {-327680, -688128, 983040},
        {0, -688128, 983040},
        {-327680, -688128, 917504},
        {0, -688128, 917504},
        {176, 16},
        {255, 16},
        {176, 31},
        {255, 31},
        11
    },
    {
        {0, -688128, 917504},
        {327680, -688128, 917504},
        {0, -655360, 917504},
        {327680, -655360, 917504},
        {0, 88},
        {79, 88},
        {0, 95},
        {79, 95},
        11
    },
    {
        {0, -655360, 917504},
        {327680, -655360, 917504},
        {0, -655360, 983040},
        {327680, -655360, 983040},
        {0, 32},
        {79, 32},
        {0, 15},
        {79, 15},
        11
    },
    {
        {0, -688128, 983040},
        {327680, -688128, 983040},
        {0, -688128, 917504},
        {327680, -688128, 917504},
        {0, 16},
        {79, 16},
        {0, 31},
        {79, 31},
        11
    },
    {
        {-1048576, -655360, 327680},
        {-983040, -655360, 655360},
        {-1048576, -327680, 327680},
        {-983040, -327680, 655360},
        {223, 192},
        {192, 192},
        {223, 223},
        {192, 223},
        14
    },
    {
        {-1048576, -983040, 327680},
        {-983040, -983040, 655360},
        {-1048576, -655360, 327680},
        {-983040, -655360, 655360},
        {223, 160},
        {192, 160},
        {223, 191},
        {192, 191},
        14
    },
    {
        {-1048576, -1310720, 327680},
        {-983040, -1310720, 655360},
        {-1048576, -983040, 327680},
        {-983040, -983040, 655360},
        {223, 128},
        {192, 128},
        {223, 159},
        {192, 159},
        14
    },
    {
        {-1048576, -1638400, 327680},
        {-983040, -1638400, 655360},
        {-1048576, -1310720, 327680},
        {-983040, -1310720, 655360},
        {223, 96},
        {192, 96},
        {223, 127},
        {192, 127},
        14
    },
    {
        {-1048576, -1966080, 327680},
        {-983040, -1966080, 655360},
        {-1048576, -1638400, 327680},
        {-983040, -1638400, 655360},
        {223, 64},
        {192, 64},
        {223, 95},
        {192, 95},
        14
    },
    {
        {-983040, -327680, -655360},
        {-1048576, -327680, -327680},
        {-983040, 0, -655360},
        {-1048576, 0, -327680},
        {63, 224},
        {32, 224},
        {63, 255},
        {32, 255},
        14
    },
    {
        {-983040, -655360, -655360},
        {-1048576, -655360, -327680},
        {-983040, -327680, -655360},
        {-1048576, -327680, -327680},
        {63, 192},
        {32, 192},
        {63, 223},
        {32, 223},
        14
    },
    {
        {-983040, -983040, -655360},
        {-1048576, -983040, -327680},
        {-983040, -655360, -655360},
        {-1048576, -655360, -327680},
        {63, 160},
        {32, 160},
        {63, 191},
        {32, 191},
        14
    },
    {
        {-983040, -1310720, -655360},
        {-1048576, -1310720, -327680},
        {-983040, -983040, -655360},
        {-1048576, -983040, -327680},
        {63, 128},
        {32, 128},
        {63, 159},
        {32, 159},
        14
    },
    {
        {-983040, -1638400, -655360},
        {-1048576, -1638400, -327680},
        {-983040, -1310720, -655360},
        {-1048576, -1310720, -327680},
        {63, 96},
        {32, 96},
        {63, 127},
        {32, 127},
        14
    },
    {
        {-983040, -1966080, -655360},
        {-1048576, -1966080, -327680},
        {-983040, -1638400, -655360},
        {-1048576, -1638400, -327680},
        {63, 64},
        {32, 64},
        {63, 95},
        {32, 95},
        14
    },
    {
        {983040, -1638400, -655360},
        {1048576, -1638400, -327680},
        {983040, -1966080, -655360},
        {1048576, -1966080, -327680},
        {63, 95},
        {32, 95},
        {63, 64},
        {32, 64},
        14
    },
    {
        {983040, -1310720, -655360},
        {1048576, -1310720, -327680},
        {983040, -1638400, -655360},
        {1048576, -1638400, -327680},
        {63, 127},
        {32, 127},
        {63, 96},
        {32, 96},
        14
    },
    {
        {983040, -983040, -655360},
        {1048576, -983040, -327680},
        {983040, -1310720, -655360},
        {1048576, -1310720, -327680},
        {63, 159},
        {32, 159},
        {63, 128},
        {32, 128},
        14
    },
    {
        {983040, -655360, -655360},
        {1048576, -655360, -327680},
        {983040, -983040, -655360},
        {1048576, -983040, -327680},
        {63, 191},
        {32, 191},
        {63, 160},
        {32, 160},
        14
    },
    {
        {983040, -327680, -655360},
        {1048576, -327680, -327680},
        {983040, -655360, -655360},
        {1048576, -655360, -327680},
        {63, 223},
        {32, 223},
        {63, 192},
        {32, 192},
        14
    },
    {
        {983040, 0, -655360},
        {1048576, 0, -327680},
        {983040, -327680, -655360},
        {1048576, -327680, -327680},
        {63, 255},
        {32, 255},
        {63, 224},
        {32, 224},
        14
    },
    {
        {1048576, 0, 327680},
        {983040, 0, 655360},
        {1048576, -327680, 327680},
        {983040, -327680, 655360},
        {223, 255},
        {192, 255},
        {223, 224},
        {192, 224},
        14
    },
    {
        {1048576, -327680, 327680},
        {983040, -327680, 655360},
        {1048576, -655360, 327680},
        {983040, -655360, 655360},
        {223, 223},
        {192, 223},
        {223, 192},
        {192, 192},
        14
    },
    {
        {1048576, -655360, 327680},
        {983040, -655360, 655360},
        {1048576, -983040, 327680},
        {983040, -983040, 655360},
        {223, 191},
        {192, 191},
        {223, 160},
        {192, 160},
        14
    },
    {
        {1048576, -983040, 327680},
        {983040, -983040, 655360},
        {1048576, -1310720, 327680},
        {983040, -1310720, 655360},
        {223, 160},
        {192, 160},
        {223, 127},
        {192, 127},
        14
    },
    {
        {1048576, -1310720, 327680},
        {983040, -1310720, 655360},
        {1048576, -1638400, 327680},
        {983040, -1638400, 655360},
        {223, 128},
        {192, 128},
        {223, 95},
        {192, 95},
        14
    },
    {
        {1048576, -1638400, 327680},
        {983040, -1638400, 655360},
        {1048576, -1966080, 327680},
        {983040, -1966080, 655360},
        {223, 96},
        {192, 96},
        {223, 63},
        {192, 63},
        14
    },
    {
        {-1114112, -4587520, -983040},
        {1114112, -4587520, -983040},
        {-1114112, -4587520, 983040},
        {1114112, -4587520, 983040},
        {240, 240},
        {15, 240},
        {240, 15},
        {15, 15},
        11
    },
    {
        {1048576, 0, -327680},
        {1048576, 0, -163840},
        {1048576, -163840, -327680},
        {1048576, -163840, -163840},
        {0, 255},
        {15, 255},
        {0, 240},
        {15, 240},
        16
    },
    {
        {1048576, -163840, -327680},
        {1048576, -163840, -163840},
        {1048576, -327680, -327680},
        {1048576, -327680, -163840},
        {0, 239},
        {15, 239},
        {0, 224},
        {15, 224},
        16
    },
    {
        {1048576, -163840, -163840},
        {1048576, -163840, 0},
        {1048576, -327680, -163840},
        {1048576, -327680, 0},
        {16, 239},
        {31, 239},
        {16, 224},
        {31, 224},
        16
    },
    {
        {1048576, 0, -163840},
        {1048576, 0, 0},
        {1048576, -163840, -163840},
        {1048576, -163840, 0},
        {16, 255},
        {31, 255},
        {16, 240},
        {31, 240},
        16
    },
    {
        {1048576, 0, 262144},
        {1048576, 0, 327680},
        {1048576, -65536, 262144},
        {1048576, -65536, 327680},
        {57, 255},
        {63, 255},
        {57, 249},
        {63, 249},
        16
    },
    {
        {1048576, 0, 196608},
        {1048576, 0, 262144},
        {1048576, -65536, 196608},
        {1048576, -65536, 262144},
        {51, 255},
        {57, 255},
        {51, 249},
        {57, 249},
        16
    },
    {
        {1048576, 0, 131072},
        {1048576, 0, 196608},
        {1048576, -65536, 131072},
        {1048576, -65536, 196608},
        {44, 255},
        {50, 255},
        {44, 249},
        {50, 249},
        16
    },
    {
        {1048576, 0, 65536},
        {1048576, 0, 131072},
        {1048576, -65536, 65536},
        {1048576, -65536, 131072},
        {38, 255},
        {44, 255},
        {38, 249},
        {44, 249},
        16
    },
    {
        {1048576, 0, 0},
        {1048576, 0, 65536},
        {1048576, -65536, 0},
        {1048576, -65536, 65536},
        {32, 255},
        {37, 255},
        {32, 249},
        {37, 249},
        16
    },
    {
        {1048576, -65536, 0},
        {1048576, -65536, 65536},
        {1048576, -131072, 0},
        {1048576, -131072, 65536},
        {32, 249},
        {37, 249},
        {32, 243},
        {37, 243},
        16
    },
    {
        {1048576, -65536, 131072},
        {1048576, -65536, 196608},
        {1048576, -131072, 131072},
        {1048576, -131072, 196608},
        {44, 249},
        {50, 249},
        {44, 243},
        {50, 243},
        16
    },
    {
        {1048576, -65536, 65536},
        {1048576, -65536, 131072},
        {1048576, -131072, 65536},
        {1048576, -131072, 131072},
        {38, 249},
        {44, 249},
        {38, 243},
        {44, 243},
        16
    },
    {
        {1048576, -65536, 196608},
        {1048576, -65536, 262144},
        {1048576, -131072, 196608},
        {1048576, -131072, 262144},
        {51, 249},
        {57, 249},
        {51, 243},
        {57, 243},
        16
    },
    {
        {1048576, -65536, 262144},
        {1048576, -65536, 327680},
        {1048576, -131072, 262144},
        {1048576, -131072, 327680},
        {57, 249},
        {63, 249},
        {57, 243},
        {63, 243},
        16
    },
    {
        {1048576, -131072, 0},
        {1048576, -131072, 65536},
        {1048576, -196608, 0},
        {1048576, -196608, 65536},
        {32, 242},
        {37, 242},
        {32, 236},
        {37, 236},
        16
    },
    {
        {1048576, -131072, 131072},
        {1048576, -131072, 196608},
        {1048576, -196608, 131072},
        {1048576, -196608, 196608},
        {44, 242},
        {50, 242},
        {44, 236},
        {50, 236},
        16
    },
    {
        {1048576, -131072, 65536},
        {1048576, -131072, 131072},
        {1048576, -196608, 65536},
        {1048576, -196608, 131072},
        {38, 242},
        {44, 242},
        {38, 236},
        {44, 236},
        16
    },
    {
        {1048576, -131072, 196608},
        {1048576, -131072, 262144},
        {1048576, -196608, 196608},
        {1048576, -196608, 262144},
        {51, 242},
        {57, 242},
        {51, 236},
        {57, 236},
        16
    },
    {
        {1048576, -131072, 262144},
        {1048576, -131072, 327680},
        {1048576, -196608, 262144},
        {1048576, -196608, 327680},
        {57, 242},
        {63, 242},
        {57, 236},
        {63, 236},
        16
    },
    {
        {1048576, -196608, 0},
        {1048576, -196608, 65536},
        {1048576, -262144, 0},
        {1048576, -262144, 65536},
        {32, 236},
        {37, 236},
        {32, 230},
        {37, 230},
        16
    },
    {
        {1048576, -196608, 131072},
        {1048576, -196608, 196608},
        {1048576, -262144, 131072},
        {1048576, -262144, 196608},
        {44, 236},
        {50, 236},
        {44, 230},
        {50, 230},
        16
    },
    {
        {1048576, -196608, 65536},
        {1048576, -196608, 131072},
        {1048576, -262144, 65536},
        {1048576, -262144, 131072},
        {38, 236},
        {44, 236},
        {38, 230},
        {44, 230},
        16
    },
    {
        {1048576, -196608, 196608},
        {1048576, -196608, 262144},
        {1048576, -262144, 196608},
        {1048576, -262144, 262144},
        {51, 236},
        {57, 236},
        {51, 230},
        {57, 230},
        16
    },
    {
        {1048576, -196608, 262144},
        {1048576, -196608, 327680},
        {1048576, -262144, 262144},
        {1048576, -262144, 327680},
        {57, 236},
        {63, 236},
        {57, 230},
        {63, 230},
        16
    },
    {
        {1048576, -262144, 0},
        {1048576, -262144, 65536},
        {1048576, -327680, 0},
        {1048576, -327680, 65536},
        {32, 229},
        {37, 229},
        {32, 224},
        {37, 224},
        16
    },
    {
        {1048576, -262144, 131072},
        {1048576, -262144, 196608},
        {1048576, -327680, 131072},
        {1048576, -327680, 196608},
        {44, 229},
        {50, 229},
        {44, 224},
        {50, 224},
        16
    },
    {
        {1048576, -262144, 65536},
        {1048576, -262144, 131072},
        {1048576, -327680, 65536},
        {1048576, -327680, 131072},
        {38, 229},
        {44, 229},
        {38, 224},
        {44, 224},
        16
    },
    {
        {1048576, -262144, 196608},
        {1048576, -262144, 262144},
        {1048576, -327680, 196608},
        {1048576, -327680, 262144},
        {51, 229},
        {57, 229},
        {51, 224},
        {57, 224},
        16
    },
    {
        {1048576, -262144, 262144},
        {1048576, -262144, 327680},
        {1048576, -327680, 262144},
        {1048576, -327680, 327680},
        {57, 229},
        {63, 229},
        {57, 224},
        {63, 224},
        16
    },
    {
        {-196608, 0, 1310720},
        {196608, 0, 1310720},
        {-196608, 0, 983040},
        {196608, 0, 983040},
        {252, 128},
        {34, 128},
        {252, 159},
        {34, 159},
        1
    },
    {
        {-196608, 0, 1638400},
        {196608, 0, 1638400},
        {-196608, 0, 1310720},
        {196608, 0, 1310720},
        {252, 96},
        {34, 96},
        {252, 127},
        {34, 127},
        1
    },
    {
        {-196608, 0, 1966080},
        {0, 0, 1966080},
        {-196608, 0, 1638400},
        {0, 0, 1638400},
        {191, 236},
        {191, 255},
        {160, 236},
        {160, 255},
        12
    },
    {
        {0, 0, 2162688},
        {327680, 0, 2162688},
        {0, 0, 1966080},
        {327680, 0, 1966080},
        {44, 255},
        {44, 224},
        {63, 255},
        {63, 224},
        12
    },
    {
        {-196608, 0, 2162688},
        {0, 0, 2162688},
        {-196608, 0, 1966080},
        {0, 0, 1966080},
        {236, 44},
        {255, 44},
        {236, 63},
        {255, 63},
        12
    },
    {
        {0, 0, 1966080},
        {327680, 0, 1966080},
        {0, 0, 1638400},
        {327680, 0, 1638400},
        {255, 192},
        {224, 192},
        {255, 159},
        {224, 159},
        12
    },
    {
        {-327680, -1015808, 1966080},
        {-327680, -1015808, 2293760},
        {-327680, -688128, 1966080},
        {-327680, -688128, 2293760},
        {96, 192},
        {96, 223},
        {65, 192},
        {65, 223},
        13
    },
    {
        {-327680, -1343488, 983040},
        {-327680, -1343488, 1310720},
        {-327680, -1015808, 983040},
        {-327680, -1015808, 1310720},
        {128, 96},
        {128, 127},
        {97, 96},
        {97, 127},
        13
    },
    {
        {-327680, -1343488, 1310720},
        {-327680, -1343488, 1638400},
        {-327680, -1015808, 1310720},
        {-327680, -1015808, 1638400},
        {128, 128},
        {128, 159},
        {97, 128},
        {97, 159},
        13
    },
    {
        {-327680, -1343488, 1638400},
        {-327680, -1343488, 1966080},
        {-327680, -1015808, 1638400},
        {-327680, -1015808, 1966080},
        {128, 160},
        {128, 191},
        {97, 160},
        {97, 191},
        13
    },
    {
        {-327680, -1343488, 1966080},
        {-327680, -1343488, 2293760},
        {-327680, -1015808, 1966080},
        {-327680, -1015808, 2293760},
        {128, 192},
        {128, 223},
        {97, 192},
        {97, 223},
        13
    },
    {
        {-327680, -1015808, 1310720},
        {-327680, -1015808, 1638400},
        {-327680, -688128, 1310720},
        {-327680, -688128, 1638400},
        {96, 128},
        {96, 159},
        {65, 128},
        {65, 159},
        13
    },
    {
        {-327680, -1015808, 983040},
        {-327680, -1015808, 1310720},
        {-327680, -688128, 983040},
        {-327680, -688128, 1310720},
        {96, 96},
        {96, 127},
        {65, 96},
        {65, 127},
        13
    },
    {
        {-327680, -1015808, 1638400},
        {-327680, -1015808, 1966080},
        {-327680, -688128, 1638400},
        {-327680, -688128, 1966080},
        {96, 160},
        {96, 191},
        {65, 160},
        {65, 191},
        13
    },
    {
        {-327680, -491520, 983040},
        {0, -491520, 983040},
        {-327680, -491520, 1310720},
        {0, -491520, 1310720},
        {224, 160},
        {255, 160},
        {224, 127},
        {255, 127},
        13
    },
    {
        {-327680, -688128, 1310720},
        {0, -688128, 1310720},
        {-327680, -688128, 983040},
        {0, -688128, 983040},
        {224, 128},
        {255, 128},
        {224, 159},
        {255, 159},
        13
    },
    {
        {0, -491520, 983040},
        {327680, -491520, 983040},
        {0, -491520, 1310720},
        {327680, -491520, 1310720},
        {0, 159},
        {31, 159},
        {0, 128},
        {31, 128},
        13
    },
    {
        {0, -688128, 1310720},
        {327680, -688128, 1310720},
        {0, -688128, 983040},
        {327680, -688128, 983040},
        {0, 128},
        {31, 128},
        {0, 159},
        {31, 159},
        13
    },
    {
        {0, -491520, 1310720},
        {327680, -491520, 1310720},
        {0, -491520, 1638400},
        {327680, -491520, 1638400},
        {0, 127},
        {31, 127},
        {0, 96},
        {31, 96},
        13
    },
    {
        {0, -688128, 1638400},
        {327680, -688128, 1638400},
        {0, -688128, 1310720},
        {327680, -688128, 1310720},
        {0, 96},
        {31, 96},
        {0, 127},
        {31, 127},
        13
    },
    {
        {-327680, -491520, 1310720},
        {0, -491520, 1310720},
        {-327680, -491520, 1638400},
        {0, -491520, 1638400},
        {224, 128},
        {255, 128},
        {224, 95},
        {255, 95},
        13
    },
    {
        {-327680, -688128, 1638400},
        {0, -688128, 1638400},
        {-327680, -688128, 1310720},
        {0, -688128, 1310720},
        {224, 96},
        {255, 96},
        {224, 127},
        {255, 127},
        13
    },
    {
        {-327680, -491520, 1638400},
        {0, -491520, 1638400},
        {-327680, -491520, 1966080},
        {0, -491520, 1966080},
        {224, 96},
        {255, 96},
        {224, 63},
        {255, 63},
        13
    },
    {
        {-327680, -688128, 1966080},
        {0, -688128, 1966080},
        {-327680, -688128, 1638400},
        {0, -688128, 1638400},
        {224, 64},
        {255, 64},
        {224, 95},
        {255, 95},
        13
    },
    {
        {0, -491520, 1638400},
        {327680, -491520, 1638400},
        {0, -491520, 1966080},
        {327680, -491520, 1966080},
        {0, 95},
        {31, 95},
        {0, 64},
        {31, 64},
        13
    },
    {
        {0, -688128, 1966080},
        {327680, -688128, 1966080},
        {0, -688128, 1638400},
        {327680, -688128, 1638400},
        {0, 64},
        {31, 64},
        {0, 95},
        {31, 95},
        13
    },
    {
        {0, -491520, 1966080},
        {327680, -491520, 1966080},
        {0, -491520, 2293760},
        {327680, -491520, 2293760},
        {0, 63},
        {31, 63},
        {0, 32},
        {31, 32},
        13
    },
    {
        {0, -688128, 2293760},
        {327680, -688128, 2293760},
        {0, -688128, 1966080},
        {327680, -688128, 1966080},
        {0, 32},
        {31, 32},
        {0, 63},
        {31, 63},
        13
    },
    {
        {-327680, -491520, 1966080},
        {0, -491520, 1966080},
        {-327680, -491520, 2293760},
        {0, -491520, 2293760},
        {224, 64},
        {255, 64},
        {224, 31},
        {255, 31},
        13
    },
    {
        {-327680, -688128, 2293760},
        {0, -688128, 2293760},
        {-327680, -688128, 1966080},
        {0, -688128, 1966080},
        {224, 32},
        {255, 32},
        {224, 63},
        {255, 63},
        13
    },
    {
        {327680, -1015808, 983040},
        {327680, -1015808, 1310720},
        {327680, -1343488, 983040},
        {327680, -1343488, 1310720},
        {96, 96},
        {96, 127},
        {127, 96},
        {127, 127},
        13
    },
    {
        {327680, -688128, 983040},
        {327680, -688128, 1310720},
        {327680, -1015808, 983040},
        {327680, -1015808, 1310720},
        {64, 96},
        {64, 127},
        {95, 96},
        {95, 127},
        13
    },
    {
        {327680, -688128, 1310720},
        {327680, -688128, 1638400},
        {327680, -1015808, 1310720},
        {327680, -1015808, 1638400},
        {64, 128},
        {64, 159},
        {95, 128},
        {95, 159},
        13
    },
    {
        {327680, -1015808, 1310720},
        {327680, -1015808, 1638400},
        {327680, -1343488, 1310720},
        {327680, -1343488, 1638400},
        {96, 128},
        {96, 159},
        {127, 128},
        {127, 159},
        13
    },
    {
        {327680, -1015808, 1638400},
        {327680, -1015808, 1966080},
        {327680, -1343488, 1638400},
        {327680, -1343488, 1966080},
        {96, 160},
        {96, 191},
        {127, 160},
        {127, 191},
        13
    },
    {
        {327680, -688128, 1638400},
        {327680, -688128, 1966080},
        {327680, -1015808, 1638400},
        {327680, -1015808, 1966080},
        {64, 160},
        {64, 191},
        {95, 160},
        {95, 191},
        13
    },
    {
        {327680, -688128, 1966080},
        {327680, -688128, 2293760},
        {327680, -1015808, 1966080},
        {327680, -1015808, 2293760},
        {64, 192},
        {64, 223},
        {95, 192},
        {95, 223},
        13
    },
    {
        {-196608, -1081344, 2293760},
        {196608, -1081344, 2293760},
        {-196608, -688128, 2293760},
        {196608, -688128, 2293760},
        {0, 64},
        {63, 64},
        {0, 127},
        {63, 127},
        8
    },
    {
        {-327680, -1310720, 1966080},
        {0, -1310720, 1966080},
        {-327680, -1310720, 2293760},
        {0, -1310720, 2293760},
        {224, 64},
        {255, 64},
        {224, 31},
        {255, 31},
        13
    },
    {
        {0, -1310720, 1966080},
        {327680, -1310720, 1966080},
        {0, -1310720, 2293760},
        {327680, -1310720, 2293760},
        {0, 63},
        {31, 63},
        {0, 32},
        {31, 32},
        13
    },
    {
        {0, -1310720, 1638400},
        {327680, -1310720, 1638400},
        {0, -1310720, 1966080},
        {327680, -1310720, 1966080},
        {0, 95},
        {31, 95},
        {0, 64},
        {31, 64},
        13
    },
    {
        {0, -1310720, 1310720},
        {327680, -1310720, 1310720},
        {0, -1310720, 1638400},
        {327680, -1310720, 1638400},
        {0, 127},
        {31, 127},
        {0, 96},
        {31, 96},
        10
    },
    {
        {0, -1310720, 983040},
        {327680, -1310720, 983040},
        {0, -1310720, 1310720},
        {327680, -1310720, 1310720},
        {0, 159},
        {31, 159},
        {0, 128},
        {31, 128},
        10
    },
    {
        {-327680, -1310720, 983040},
        {0, -1310720, 983040},
        {-327680, -1310720, 1310720},
        {0, -1310720, 1310720},
        {224, 160},
        {255, 160},
        {224, 127},
        {255, 127},
        10
    },
    {
        {-327680, -1310720, 1310720},
        {0, -1310720, 1310720},
        {-327680, -1310720, 1638400},
        {0, -1310720, 1638400},
        {224, 128},
        {255, 128},
        {224, 95},
        {255, 95},
        10
    },
    {
        {-327680, -1310720, 1638400},
        {0, -1310720, 1638400},
        {-327680, -1310720, 1966080},
        {0, -1310720, 1966080},
        {224, 96},
        {255, 96},
        {224, 63},
        {255, 63},
        13
    },
    {
        {327680, -1015808, 1966080},
        {327680, -1015808, 2293760},
        {327680, -1343488, 1966080},
        {327680, -1343488, 2293760},
        {96, 192},
        {96, 223},
        {127, 192},
        {127, 223},
        13
    },
    {
        {-294912, -491520, 1966080},
        {-294912, -491520, 2293760},
        {-294912, -98304, 1966080},
        {-294912, -98304, 2293760},
        {45, 192},
        {45, 223},
        {7, 192},
        {7, 223},
        13
    },
    {
        {196608, -688128, 2260992},
        {196608, -688128, 2293760},
        {196608, -1343488, 2260992},
        {196608, -1343488, 2293760},
        {40, 88},
        {47, 88},
        {40, 183},
        {47, 183},
        11
    },
    {
        {196608, -1343488, 2260992},
        {327680, -1343488, 2260992},
        {196608, -688128, 2260992},
        {327680, -688128, 2260992},
        {48, 184},
        {79, 184},
        {48, 87},
        {79, 87},
        11
    },
    {
        {-327680, -1343488, 2260992},
        {-196608, -1343488, 2260992},
        {-327680, -688128, 2260992},
        {-196608, -688128, 2260992},
        {176, 184},
        {207, 184},
        {176, 87},
        {207, 87},
        11
    },
    {
        {-196608, -1343488, 2260992},
        {-196608, -1343488, 2293760},
        {-196608, -688128, 2260992},
        {-196608, -688128, 2293760},
        {40, 184},
        {47, 184},
        {40, 87},
        {47, 87},
        11
    },
    {
        {-229376, -1310720, 2293760},
        {229376, -1310720, 2293760},
        {-229376, -1081344, 2293760},
        {229376, -1081344, 2293760},
        {249, 125},
        {37, 125},
        {249, 146},
        {37, 146},
        5
    },
    {
        {-294912, -491520, 1638400},
        {-294912, -491520, 1966080},
        {-294912, -98304, 1638400},
        {-294912, -98304, 1966080},
        {45, 160},
        {45, 191},
        {7, 160},
        {7, 191},
        13
    },
    {
        {-294912, -491520, 1310720},
        {-294912, -491520, 1638400},
        {-294912, -98304, 1310720},
        {-294912, -98304, 1638400},
        {45, 128},
        {45, 159},
        {7, 128},
        {7, 159},
        13
    },
    {
        {-294912, -491520, 983040},
        {-294912, -491520, 1310720},
        {-294912, -98304, 983040},
        {-294912, -98304, 1310720},
        {45, 96},
        {45, 127},
        {7, 96},
        {7, 127},
        13
    },
    {
        {655360, 0, 2162688},
        {983040, 0, 2162688},
        {655360, 0, 1769472},
        {983040, 0, 1769472},
        {60, 191},
        {60, 160},
        {98, 191},
        {98, 160},
        1
    },
    {
        {327680, 0, 2162688},
        {655360, 0, 2162688},
        {327680, 0, 1769472},
        {655360, 0, 1769472},
        {60, 223},
        {60, 192},
        {98, 223},
        {98, 192},
        1
    },
    {
        {294912, -98304, 1310720},
        {294912, -98304, 1671168},
        {294912, -491520, 1310720},
        {294912, -491520, 1671168},
        {249, 128},
        {249, 162},
        {31, 128},
        {31, 162},
        7
    },
    {
        {294912, -98304, 1671168},
        {327680, -98304, 1671168},
        {294912, -491520, 1671168},
        {327680, -491520, 1671168},
        {249, 28},
        {249, 31},
        {31, 28},
        {31, 31},
        7
    },
    {
        {294912, -98304, 983040},
        {294912, -98304, 1310720},
        {294912, -491520, 983040},
        {294912, -491520, 1310720},
        {7, 159},
        {7, 128},
        {45, 159},
        {45, 128},
        13
    },
    {
        {196608, 0, 1638400},
        {327680, 0, 1638400},
        {196608, 0, 1769472},
        {327680, 0, 1769472},
        {48, 111},
        {79, 111},
        {48, 80},
        {79, 80},
        11
    },
    {
        {327680, -98304, 1671168},
        {655360, -98304, 1671168},
        {327680, -491520, 1671168},
        {655360, -491520, 1671168},
        {249, 32},
        {249, 63},
        {31, 32},
        {31, 63},
        7
    },
    {
        {327680, -491520, 1966080},
        {655360, -491520, 1966080},
        {327680, -491520, 2260992},
        {655360, -491520, 2260992},
        {192, 32},
        {192, 63},
        {220, 32},
        {220, 63},
        13
    },
    {
        {327680, -491520, 1671168},
        {655360, -491520, 1671168},
        {327680, -491520, 1966080},
        {655360, -491520, 1966080},
        {163, 32},
        {163, 63},
        {191, 32},
        {191, 63},
        13
    },
    {
        {655360, -98304, 1671168},
        {983040, -98304, 1671168},
        {655360, -491520, 1671168},
        {983040, -491520, 1671168},
        {249, 64},
        {249, 95},
        {31, 64},
        {31, 95},
        7
    },
    {
        {-294912, -491520, 2260992},
        {32768, -491520, 2260992},
        {-294912, -98304, 2260992},
        {32768, -98304, 2260992},
        {45, 227},
        {45, 2},
        {7, 227},
        {7, 2},
        13
    },
    {
        {32768, -491520, 2260992},
        {360448, -491520, 2260992},
        {32768, -98304, 2260992},
        {360448, -98304, 2260992},
        {45, 3},
        {45, 34},
        {7, 3},
        {7, 34},
        13
    },
    {
        {360448, -491520, 2260992},
        {688128, -491520, 2260992},
        {360448, -98304, 2260992},
        {688128, -98304, 2260992},
        {45, 35},
        {45, 66},
        {7, 35},
        {7, 66},
        13
    },
    {
        {688128, -491520, 2260992},
        {983040, -491520, 2260992},
        {688128, -98304, 2260992},
        {983040, -98304, 2260992},
        {45, 67},
        {45, 95},
        {7, 67},
        {7, 95},
        13
    },
    {
        {655360, -491520, 1671168},
        {983040, -491520, 1671168},
        {655360, -491520, 1966080},
        {983040, -491520, 1966080},
        {163, 64},
        {163, 95},
        {191, 64},
        {191, 95},
        13
    },
    {
        {655360, -491520, 1966080},
        {983040, -491520, 1966080},
        {655360, -491520, 2260992},
        {983040, -491520, 2260992},
        {192, 64},
        {192, 95},
        {220, 64},
        {220, 95},
        13
    },
    {
        {983040, 0, 1671168},
        {983040, 0, 2260992},
        {983040, -491520, 1671168},
        {983040, -491520, 2260992},
        {152, 0},
        {39, 0},
        {152, 135},
        {39, 135},
        11
    },
    {
        {983040, -491520, 1671168},
        {1015808, -491520, 1671168},
        {983040, 0, 1671168},
        {1015808, 0, 1671168},
        {240, 136},
        {247, 136},
        {240, 255},
        {247, 255},
        11
    },
    {
        {983040, 0, 1671168},
        {1015808, 0, 1671168},
        {983040, 0, 2260992},
        {1015808, 0, 2260992},
        {240, 103},
        {247, 103},
        {240, 216},
        {247, 216},
        11
    },
    {
        {983040, -491520, 2260992},
        {1015808, -491520, 2260992},
        {983040, -491520, 1671168},
        {1015808, -491520, 1671168},
        {240, 216},
        {247, 216},
        {240, 103},
        {247, 103},
        11
    },
    {
        {983040, 0, 2260992},
        {1015808, 0, 2260992},
        {983040, -491520, 2260992},
        {1015808, -491520, 2260992},
        {240, 255},
        {247, 255},
        {240, 136},
        {247, 136},
        11
    },
    {
        {1015808, -491520, 1671168},
        {1015808, -491520, 2260992},
        {1015808, 0, 1671168},
        {1015808, 0, 2260992},
        {152, 136},
        {39, 136},
        {152, 255},
        {39, 255},
        11
    },
    {
        {0, -98304, 2260992},
        {327680, -98304, 2260992},
        {0, 0, 2162688},
        {327680, 0, 2162688},
        {32, 255},
        {32, 224},
        {63, 255},
        {63, 224},
        9
    },
    {
        {-262144, -98304, 2260992},
        {0, -98304, 2260992},
        {-262144, 0, 2162688},
        {0, 0, 2162688},
        {32, 25},
        {32, 255},
        {63, 25},
        {63, 255},
        15
    },
    {
        {-294912, -98304, 1966080},
        {-294912, -98304, 2228224},
        {-196608, 0, 1966080},
        {-196608, 0, 2228224},
        {160, 64},
        {160, 37},
        {191, 64},
        {191, 37},
        9
    },
    {
        {-294912, -98304, 1638400},
        {-294912, -98304, 1966080},
        {-196608, 0, 1638400},
        {-196608, 0, 1966080},
        {160, 96},
        {160, 63},
        {191, 96},
        {191, 63},
        15
    },
    {
        {-294912, 0, 2228224},
        {-294912, 0, 2260992},
        {-294912, -491520, 2228224},
        {-294912, -491520, 2260992},
        {32, 0},
        {39, 0},
        {32, 135},
        {39, 135},
        11
    },
    {
        {-294912, -491520, 2228224},
        {-262144, -491520, 2228224},
        {-294912, 0, 2228224},
        {-262144, 0, 2228224},
        {184, 136},
        {191, 136},
        {184, 255},
        {191, 255},
        11
    },
    {
        {-294912, 0, 2228224},
        {-262144, 0, 2228224},
        {-294912, 0, 2260992},
        {-262144, 0, 2260992},
        {184, 223},
        {191, 223},
        {184, 216},
        {191, 216},
        11
    },
    {
        {-294912, -491520, 2260992},
        {-262144, -491520, 2260992},
        {-294912, -491520, 2228224},
        {-262144, -491520, 2228224},
        {184, 216},
        {191, 216},
        {184, 223},
        {191, 223},
        11
    },
    {
        {-294912, 0, 2260992},
        {-262144, 0, 2260992},
        {-294912, -491520, 2260992},
        {-262144, -491520, 2260992},
        {184, 255},
        {191, 255},
        {184, 136},
        {191, 136},
        11
    },
    {
        {-262144, -491520, 2228224},
        {-262144, -491520, 2260992},
        {-262144, 0, 2228224},
        {-262144, 0, 2260992},
        {32, 136},
        {39, 136},
        {32, 255},
        {39, 255},
        11
    },
    {
        {-294912, -98304, 1310720},
        {-294912, -98304, 1638400},
        {-196608, 0, 1310720},
        {-196608, 0, 1638400},
        {160, 128},
        {160, 95},
        {191, 128},
        {191, 95},
        9
    },
    {
        {-294912, -98304, 983040},
        {-294912, -98304, 1310720},
        {-196608, 0, 983040},
        {-196608, 0, 1310720},
        {160, 160},
        {160, 127},
        {191, 160},
        {191, 127},
        15
    },
    {
        {196608, 0, 1310720},
        {294912, -98304, 1310720},
        {196608, 0, 983040},
        {294912, -98304, 983040},
        {191, 128},
        {160, 128},
        {191, 95},
        {160, 95},
        9
    },
    {
        {196608, 0, 1638400},
        {294912, -98304, 1638400},
        {196608, 0, 1310720},
        {294912, -98304, 1310720},
        {191, 159},
        {160, 159},
        {191, 128},
        {160, 128},
        15
    },
    {
        {655360, -98304, 2260992},
        {983040, -98304, 2260992},
        {655360, 0, 2162688},
        {983040, 0, 2162688},
        {32, 191},
        {32, 160},
        {63, 191},
        {63, 160},
        9
    },
    {
        {327680, -98304, 2260992},
        {655360, -98304, 2260992},
        {327680, 0, 2162688},
        {655360, 0, 2162688},
        {32, 223},
        {32, 192},
        {63, 223},
        {63, 192},
        15
    },
    {
        {327680, 0, 1769472},
        {655360, 0, 1769472},
        {327680, -98304, 1671168},
        {655360, -98304, 1671168},
        {63, 32},
        {63, 63},
        {32, 32},
        {32, 63},
        9
    },
    {
        {655360, 0, 1769472},
        {983040, 0, 1769472},
        {655360, -98304, 1671168},
        {983040, -98304, 1671168},
        {63, 64},
        {63, 95},
        {32, 64},
        {32, 95},
        15
    },
};
#pragma endregion