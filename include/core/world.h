#pragma once
#include "bsp.h"


///////////////////////////////////////////////
// BSP Tree Definition and Shape Definitions //
///////////////////////////////////////////////
#pragma region BSPTree
int numTextures = 19;
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
    {
        "01F9.TIM;1",
        {
            0, 0,
            0, 0,
            0, 0
        }
    },
    {
        "01L5.TIM;1",
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

#pragma endregion

#pragma region Object Data

int numTris = 26;
Tri3 tris[] = {
	{{397312, 45056, -131072}, {430080, 45056, -131072}, {397312, 45056, -262144}},
	{{397312, 45056, 131072}, {397312, 45056, 262144}, {430080, 45056, 131072}},
	{{266240, 45056, -262144}, {397312, 45056, -262144}, {266240, 45056, -393216}},
	{{266240, 45056, 262144}, {266240, 45056, 393216}, {397312, 45056, 262144}},
	{{-389120, 45056, 262144}, {-258048, 45056, 393216}, {-258048, 45056, 262144}},
	{{-421888, 45056, 131072}, {-389120, 45056, 262144}, {-389120, 45056, 131072}},
	{{-421888, 45056, -131072}, {-389120, 45056, -131072}, {-389120, 45056, -262144}},
	{{-389120, 45056, -262144}, {-258048, 45056, -262144}, {-258048, 45056, -393216}},
	{{-389120, -1789952, 262144}, {-258048, -1789952, 262144}, {-258048, -1789952, 393216}},
	{{-389120, -1822720, 262144}, {-258048, -1822720, 393216}, {-258048, -1822720, 262144}},
	{{266240, -1789952, 262144}, {397312, -1789952, 262144}, {266240, -1789952, 393216}},
	{{266240, -1822720, 262144}, {266240, -1822720, 393216}, {397312, -1822720, 262144}},
	{{-421888, -1789952, 131072}, {-389120, -1789952, 131072}, {-389120, -1789952, 262144}},
	{{-421888, -1822720, 131072}, {-389120, -1822720, 262144}, {-389120, -1822720, 131072}},
	{{-421888, -1789952, -131072}, {-389120, -1789952, -262144}, {-389120, -1789952, -131072}},
	{{-421888, -1822720, -131072}, {-389120, -1822720, -131072}, {-389120, -1822720, -262144}},
	{{-389120, -1789952, -262144}, {-258048, -1789952, -393216}, {-258048, -1789952, -262144}},
	{{-389120, -1822720, -262144}, {-258048, -1822720, -262144}, {-258048, -1822720, -393216}},
	{{266240, -1789952, -262144}, {266240, -1789952, -393216}, {397312, -1789952, -262144}},
	{{266240, -1822720, -262144}, {397312, -1822720, -262144}, {266240, -1822720, -393216}},
	{{397312, -1789952, -131072}, {397312, -1789952, -262144}, {430080, -1789952, -131072}},
	{{397312, -1822720, -131072}, {430080, -1822720, -131072}, {397312, -1822720, -262144}},
	{{397312, -1789952, 131072}, {430080, -1789952, 131072}, {397312, -1789952, 262144}},
	{{397312, -1822720, 131072}, {397312, -1822720, 262144}, {430080, -1822720, 131072}},
	{{-61440, -135168, 671744}, {-61440, -118784, 737280}, {-61440, -135168, 737280}},
	{{69632, -118784, 737280}, {69632, -135168, 671744}, {69632, -135168, 737280}},
};
int numQuads = 1077;
Quad3 quads[] = {
	{{-126976, 45056, 131072}, {4096, 45056, 131072}, {-126976, 45056, 0}, {4096, 45056, 0}, },
	{{-126976, 45056, 0}, {4096, 45056, 0}, {-126976, 45056, -131072}, {4096, 45056, -131072}, },
	{{-258048, 45056, 262144}, {-126976, 45056, 262144}, {-258048, 45056, 131072}, {-126976, 45056, 131072}, },
	{{-389120, 45056, 262144}, {-258048, 45056, 262144}, {-389120, 45056, 131072}, {-258048, 45056, 131072}, },
	{{135168, 45056, 393216}, {266240, 45056, 393216}, {135168, 45056, 262144}, {266240, 45056, 262144}, },
	{{135168, 45056, 262144}, {266240, 45056, 262144}, {135168, 45056, 131072}, {266240, 45056, 131072}, },
	{{266240, 45056, 262144}, {397312, 45056, 262144}, {266240, 45056, 131072}, {397312, 45056, 131072}, },
	{{4096, 45056, -131072}, {135168, 45056, -131072}, {4096, 45056, -262144}, {135168, 45056, -262144}, },
	{{4096, 45056, 131072}, {135168, 45056, 131072}, {4096, 45056, 0}, {135168, 45056, 0}, },
	{{-126976, 45056, -262144}, {4096, 45056, -262144}, {-126976, 45056, -393216}, {4096, 45056, -393216}, },
	{{4096, 45056, -262144}, {135168, 45056, -262144}, {4096, 45056, -393216}, {135168, 45056, -393216}, },
	{{-126976, 45056, -131072}, {4096, 45056, -131072}, {-126976, 45056, -262144}, {4096, 45056, -262144}, },
	{{4096, 45056, 393216}, {135168, 45056, 393216}, {4096, 45056, 262144}, {135168, 45056, 262144}, },
	{{-126976, 45056, 393216}, {4096, 45056, 393216}, {-126976, 45056, 262144}, {4096, 45056, 262144}, },
	{{4096, 45056, 262144}, {135168, 45056, 262144}, {4096, 45056, 131072}, {135168, 45056, 131072}, },
	{{-126976, 45056, 262144}, {4096, 45056, 262144}, {-126976, 45056, 131072}, {4096, 45056, 131072}, },
	{{-389120, 45056, 0}, {-258048, 45056, 0}, {-389120, 45056, -131072}, {-258048, 45056, -131072}, },
	{{-258048, 45056, 0}, {-126976, 45056, 0}, {-258048, 45056, -131072}, {-126976, 45056, -131072}, },
	{{266240, 45056, 131072}, {397312, 45056, 131072}, {266240, 45056, 0}, {397312, 45056, 0}, },
	{{266240, 45056, 0}, {397312, 45056, 0}, {266240, 45056, -131072}, {397312, 45056, -131072}, },
	{{135168, 45056, 0}, {266240, 45056, 0}, {135168, 45056, -131072}, {266240, 45056, -131072}, },
	{{135168, 45056, 131072}, {266240, 45056, 131072}, {135168, 45056, 0}, {266240, 45056, 0}, },
	{{-258048, 45056, 131072}, {-126976, 45056, 131072}, {-258048, 45056, 0}, {-126976, 45056, 0}, },
	{{-389120, 45056, 131072}, {-258048, 45056, 131072}, {-389120, 45056, 0}, {-258048, 45056, 0}, },
	{{-258048, 45056, 393216}, {-126976, 45056, 393216}, {-258048, 45056, 262144}, {-126976, 45056, 262144}, },
	{{-389120, 45056, -131072}, {-258048, 45056, -131072}, {-389120, 45056, -262144}, {-258048, 45056, -262144}, },
	{{-258048, 45056, -131072}, {-126976, 45056, -131072}, {-258048, 45056, -262144}, {-126976, 45056, -262144}, },
	{{-258048, 45056, -262144}, {-126976, 45056, -262144}, {-258048, 45056, -393216}, {-126976, 45056, -393216}, },
	{{4096, 45056, 0}, {135168, 45056, 0}, {4096, 45056, -131072}, {135168, 45056, -131072}, },
	{{266240, 45056, -131072}, {397312, 45056, -131072}, {266240, 45056, -262144}, {397312, 45056, -262144}, },
	{{135168, 45056, -262144}, {266240, 45056, -262144}, {135168, 45056, -393216}, {266240, 45056, -393216}, },
	{{135168, 45056, -131072}, {266240, 45056, -131072}, {135168, 45056, -262144}, {266240, 45056, -262144}, },
	{{-126976, 45056, -393216}, {4096, 45056, -393216}, {-126976, -86016, -393216}, {4096, -86016, -393216}, },
	{{4096, 45056, -393216}, {135168, 45056, -393216}, {4096, -86016, -393216}, {135168, -86016, -393216}, },
	{{4096, -86016, -393216}, {135168, -86016, -393216}, {4096, -217088, -393216}, {135168, -217088, -393216}, },
	{{-126976, -86016, -393216}, {4096, -86016, -393216}, {-126976, -217088, -393216}, {4096, -217088, -393216}, },
	{{4096, -217088, -393216}, {135168, -217088, -393216}, {4096, -348160, -393216}, {135168, -348160, -393216}, },
	{{-126976, -217088, -393216}, {4096, -217088, -393216}, {-126976, -348160, -393216}, {4096, -348160, -393216}, },
	{{4096, -348160, -393216}, {135168, -348160, -393216}, {4096, -479232, -393216}, {135168, -479232, -393216}, },
	{{-126976, -348160, -393216}, {4096, -348160, -393216}, {-126976, -479232, -393216}, {4096, -479232, -393216}, },
	{{-126976, -479232, -393216}, {4096, -479232, -393216}, {-126976, -610304, -393216}, {4096, -610304, -393216}, },
	{{4096, -479232, -393216}, {135168, -479232, -393216}, {4096, -610304, -393216}, {135168, -610304, -393216}, },
	{{-126976, -610304, -393216}, {4096, -610304, -393216}, {-126976, -741376, -393216}, {4096, -741376, -393216}, },
	{{4096, -610304, -393216}, {135168, -610304, -393216}, {4096, -741376, -393216}, {135168, -741376, -393216}, },
	{{4096, -741376, -393216}, {135168, -741376, -393216}, {4096, -872448, -393216}, {135168, -872448, -393216}, },
	{{-126976, -741376, -393216}, {4096, -741376, -393216}, {-126976, -872448, -393216}, {4096, -872448, -393216}, },
	{{-126976, -872448, -393216}, {4096, -872448, -393216}, {-126976, -1003520, -393216}, {4096, -1003520, -393216}, },
	{{4096, -872448, -393216}, {135168, -872448, -393216}, {4096, -1003520, -393216}, {135168, -1003520, -393216}, },
	{{-126976, -1003520, -393216}, {4096, -1003520, -393216}, {-126976, -1134592, -393216}, {4096, -1134592, -393216}, },
	{{4096, -1003520, -393216}, {135168, -1003520, -393216}, {4096, -1134592, -393216}, {135168, -1134592, -393216}, },
	{{4096, -1134592, -393216}, {135168, -1134592, -393216}, {4096, -1265664, -393216}, {135168, -1265664, -393216}, },
	{{-126976, -1134592, -393216}, {4096, -1134592, -393216}, {-126976, -1265664, -393216}, {4096, -1265664, -393216}, },
	{{-126976, -1265664, -393216}, {4096, -1265664, -393216}, {-126976, -1396736, -393216}, {4096, -1396736, -393216}, },
	{{4096, -1265664, -393216}, {135168, -1265664, -393216}, {4096, -1396736, -393216}, {135168, -1396736, -393216}, },
	{{4096, -1396736, -393216}, {135168, -1396736, -393216}, {4096, -1527808, -393216}, {135168, -1527808, -393216}, },
	{{-126976, -1396736, -393216}, {4096, -1396736, -393216}, {-126976, -1527808, -393216}, {4096, -1527808, -393216}, },
	{{-126976, -1527808, -393216}, {4096, -1527808, -393216}, {-126976, -1658880, -393216}, {4096, -1658880, -393216}, },
	{{4096, -1527808, -393216}, {135168, -1527808, -393216}, {4096, -1658880, -393216}, {135168, -1658880, -393216}, },
	{{4096, -1658880, -393216}, {135168, -1658880, -393216}, {4096, -1789952, -393216}, {135168, -1789952, -393216}, },
	{{-126976, -1658880, -393216}, {4096, -1658880, -393216}, {-126976, -1789952, -393216}, {4096, -1789952, -393216}, },
	{{266240, 45056, -393216}, {397312, 45056, -262144}, {266240, -86016, -393216}, {397312, -86016, -262144}, },
	{{397312, 45056, 0}, {430080, 45056, 0}, {397312, 45056, -131072}, {430080, 45056, -131072}, },
	{{397312, 45056, -262144}, {430080, 45056, -131072}, {397312, -86016, -262144}, {430080, -86016, -131072}, },
	{{430080, 45056, 131072}, {397312, 45056, 262144}, {430080, -86016, 131072}, {397312, -86016, 262144}, },
	{{430080, 45056, -131072}, {430080, 45056, 0}, {430080, -86016, -131072}, {430080, -86016, 0}, },
	{{266240, -86016, 393216}, {397312, -86016, 262144}, {266240, 45056, 393216}, {397312, 45056, 262144}, },
	{{430080, 45056, 0}, {430080, 45056, 131072}, {430080, -86016, 0}, {430080, -86016, 131072}, },
	{{397312, 45056, 131072}, {430080, 45056, 131072}, {397312, 45056, 0}, {430080, 45056, 0}, },
	{{-389120, 45056, -262144}, {-258048, 45056, -393216}, {-389120, -86016, -262144}, {-258048, -86016, -393216}, },
	{{-389120, -86016, -262144}, {-421888, -86016, -131072}, {-389120, 45056, -262144}, {-421888, 45056, -131072}, },
	{{-421888, -86016, -131072}, {-421888, -86016, 0}, {-421888, 45056, -131072}, {-421888, 45056, 0}, },
	{{-421888, -86016, 0}, {-421888, -86016, 131072}, {-421888, 45056, 0}, {-421888, 45056, 131072}, },
	{{-421888, -86016, 131072}, {-389120, -86016, 262144}, {-421888, 45056, 131072}, {-389120, 45056, 262144}, },
	{{-389120, 45056, 262144}, {-389120, -86016, 262144}, {-258048, 45056, 393216}, {-258048, -86016, 393216}, },
	{{-421888, 45056, 0}, {-389120, 45056, 0}, {-421888, 45056, -131072}, {-389120, 45056, -131072}, },
	{{-421888, 45056, 131072}, {-389120, 45056, 131072}, {-421888, 45056, 0}, {-389120, 45056, 0}, },
	{{-290816, 45056, -393216}, {-258048, 45056, -368640}, {-290816, -86016, -393216}, {-258048, -86016, -368640}, },
	{{-258048, 45056, -368640}, {-126976, 45056, -368640}, {-258048, -86016, -368640}, {-126976, -86016, -368640}, },
	{{-126976, -86016, -393216}, {-126976, -86016, -368640}, {-126976, 45056, -393216}, {-126976, 45056, -368640}, },
	{{135168, 45056, -393216}, {135168, 45056, -368640}, {135168, -86016, -393216}, {135168, -86016, -368640}, },
	{{135168, 45056, -368640}, {266240, 45056, -368640}, {135168, -86016, -368640}, {266240, -86016, -368640}, },
	{{299008, -86016, -393216}, {266240, -86016, -368640}, {299008, 45056, -393216}, {266240, 45056, -368640}, },
	{{-258048, 45056, 368640}, {-290816, 45056, 393216}, {-258048, -86016, 368640}, {-290816, -86016, 393216}, },
	{{-258048, -86016, 368640}, {-126976, -86016, 368640}, {-258048, 45056, 368640}, {-126976, 45056, 368640}, },
	{{-126976, -86016, 393216}, {-126976, 45056, 393216}, {-126976, -86016, 368640}, {-126976, 45056, 368640}, },
	{{135168, 45056, 368640}, {135168, 45056, 393216}, {135168, -86016, 368640}, {135168, -86016, 393216}, },
	{{135168, -86016, 368640}, {266240, -86016, 368640}, {135168, 45056, 368640}, {266240, 45056, 368640}, },
	{{266240, -86016, 368640}, {299008, -86016, 393216}, {266240, 45056, 368640}, {299008, 45056, 393216}, },
	{{135168, -86016, -393216}, {135168, -86016, -368640}, {135168, -217088, -393216}, {135168, -217088, -368640}, },
	{{135168, -86016, -368640}, {266240, -86016, -368640}, {135168, -217088, -368640}, {266240, -217088, -368640}, },
	{{299008, -217088, -393216}, {266240, -217088, -368640}, {299008, -86016, -393216}, {266240, -86016, -368640}, },
	{{266240, -86016, -393216}, {397312, -86016, -262144}, {266240, -217088, -393216}, {397312, -217088, -262144}, },
	{{397312, -86016, -262144}, {430080, -86016, -131072}, {397312, -217088, -262144}, {430080, -217088, -131072}, },
	{{430080, -86016, -131072}, {430080, -86016, 0}, {430080, -217088, -131072}, {430080, -217088, 0}, },
	{{430080, -86016, 0}, {430080, -86016, 131072}, {430080, -217088, 0}, {430080, -217088, 131072}, },
	{{430080, -86016, 131072}, {397312, -86016, 262144}, {430080, -217088, 131072}, {397312, -217088, 262144}, },
	{{266240, -217088, 393216}, {397312, -217088, 262144}, {266240, -86016, 393216}, {397312, -86016, 262144}, },
	{{135168, -86016, 368640}, {135168, -86016, 393216}, {135168, -217088, 368640}, {135168, -217088, 393216}, },
	{{135168, -217088, 368640}, {266240, -217088, 368640}, {135168, -86016, 368640}, {266240, -86016, 368640}, },
	{{266240, -217088, 368640}, {299008, -217088, 393216}, {266240, -86016, 368640}, {299008, -86016, 393216}, },
	{{-258048, -86016, 368640}, {-290816, -86016, 393216}, {-258048, -217088, 368640}, {-290816, -217088, 393216}, },
	{{-258048, -217088, 368640}, {-126976, -217088, 368640}, {-258048, -86016, 368640}, {-126976, -86016, 368640}, },
	{{-126976, -217088, 393216}, {-126976, -86016, 393216}, {-126976, -217088, 368640}, {-126976, -86016, 368640}, },
	{{-389120, -86016, 262144}, {-389120, -217088, 262144}, {-258048, -86016, 393216}, {-258048, -217088, 393216}, },
	{{-421888, -217088, 131072}, {-389120, -217088, 262144}, {-421888, -86016, 131072}, {-389120, -86016, 262144}, },
	{{-421888, -217088, 0}, {-421888, -217088, 131072}, {-421888, -86016, 0}, {-421888, -86016, 131072}, },
	{{-421888, -217088, -131072}, {-421888, -217088, 0}, {-421888, -86016, -131072}, {-421888, -86016, 0}, },
	{{-389120, -217088, -262144}, {-421888, -217088, -131072}, {-389120, -86016, -262144}, {-421888, -86016, -131072}, },
	{{-389120, -86016, -262144}, {-258048, -86016, -393216}, {-389120, -217088, -262144}, {-258048, -217088, -393216}, },
	{{-290816, -86016, -393216}, {-258048, -86016, -368640}, {-290816, -217088, -393216}, {-258048, -217088, -368640}, },
	{{-258048, -86016, -368640}, {-126976, -86016, -368640}, {-258048, -217088, -368640}, {-126976, -217088, -368640}, },
	{{-126976, -217088, -393216}, {-126976, -217088, -368640}, {-126976, -86016, -393216}, {-126976, -86016, -368640}, },
	{{135168, -217088, -393216}, {135168, -217088, -368640}, {135168, -348160, -393216}, {135168, -348160, -368640}, },
	{{135168, -217088, -368640}, {266240, -217088, -368640}, {135168, -348160, -368640}, {266240, -348160, -368640}, },
	{{299008, -348160, -393216}, {266240, -348160, -368640}, {299008, -217088, -393216}, {266240, -217088, -368640}, },
	{{266240, -217088, -393216}, {397312, -217088, -262144}, {266240, -348160, -393216}, {397312, -348160, -262144}, },
	{{397312, -217088, -262144}, {430080, -217088, -131072}, {397312, -348160, -262144}, {430080, -348160, -131072}, },
	{{430080, -217088, -131072}, {430080, -217088, 0}, {430080, -348160, -131072}, {430080, -348160, 0}, },
	{{430080, -217088, 0}, {430080, -217088, 131072}, {430080, -348160, 0}, {430080, -348160, 131072}, },
	{{430080, -217088, 131072}, {397312, -217088, 262144}, {430080, -348160, 131072}, {397312, -348160, 262144}, },
	{{266240, -348160, 393216}, {397312, -348160, 262144}, {266240, -217088, 393216}, {397312, -217088, 262144}, },
	{{135168, -217088, 368640}, {135168, -217088, 393216}, {135168, -348160, 368640}, {135168, -348160, 393216}, },
	{{135168, -348160, 368640}, {266240, -348160, 368640}, {135168, -217088, 368640}, {266240, -217088, 368640}, },
	{{266240, -348160, 368640}, {299008, -348160, 393216}, {266240, -217088, 368640}, {299008, -217088, 393216}, },
	{{-258048, -217088, 368640}, {-290816, -217088, 393216}, {-258048, -348160, 368640}, {-290816, -348160, 393216}, },
	{{-258048, -348160, 368640}, {-126976, -348160, 368640}, {-258048, -217088, 368640}, {-126976, -217088, 368640}, },
	{{-126976, -348160, 393216}, {-126976, -217088, 393216}, {-126976, -348160, 368640}, {-126976, -217088, 368640}, },
	{{-389120, -217088, 262144}, {-389120, -348160, 262144}, {-258048, -217088, 393216}, {-258048, -348160, 393216}, },
	{{-421888, -348160, 131072}, {-389120, -348160, 262144}, {-421888, -217088, 131072}, {-389120, -217088, 262144}, },
	{{-421888, -348160, 0}, {-421888, -348160, 131072}, {-421888, -217088, 0}, {-421888, -217088, 131072}, },
	{{-421888, -348160, -131072}, {-421888, -348160, 0}, {-421888, -217088, -131072}, {-421888, -217088, 0}, },
	{{-389120, -348160, -262144}, {-421888, -348160, -131072}, {-389120, -217088, -262144}, {-421888, -217088, -131072}, },
	{{-389120, -217088, -262144}, {-258048, -217088, -393216}, {-389120, -348160, -262144}, {-258048, -348160, -393216}, },
	{{-290816, -217088, -393216}, {-258048, -217088, -368640}, {-290816, -348160, -393216}, {-258048, -348160, -368640}, },
	{{-258048, -217088, -368640}, {-126976, -217088, -368640}, {-258048, -348160, -368640}, {-126976, -348160, -368640}, },
	{{-126976, -348160, -393216}, {-126976, -348160, -368640}, {-126976, -217088, -393216}, {-126976, -217088, -368640}, },
	{{135168, -348160, -393216}, {135168, -348160, -368640}, {135168, -479232, -393216}, {135168, -479232, -368640}, },
	{{135168, -348160, -368640}, {266240, -348160, -368640}, {135168, -479232, -368640}, {266240, -479232, -368640}, },
	{{299008, -479232, -393216}, {266240, -479232, -368640}, {299008, -348160, -393216}, {266240, -348160, -368640}, },
	{{266240, -348160, -393216}, {397312, -348160, -262144}, {266240, -479232, -393216}, {397312, -479232, -262144}, },
	{{397312, -348160, -262144}, {430080, -348160, -131072}, {397312, -479232, -262144}, {430080, -479232, -131072}, },
	{{430080, -348160, -131072}, {430080, -348160, 0}, {430080, -479232, -131072}, {430080, -479232, 0}, },
	{{430080, -348160, 0}, {430080, -348160, 131072}, {430080, -479232, 0}, {430080, -479232, 131072}, },
	{{430080, -348160, 131072}, {397312, -348160, 262144}, {430080, -479232, 131072}, {397312, -479232, 262144}, },
	{{266240, -479232, 393216}, {397312, -479232, 262144}, {266240, -348160, 393216}, {397312, -348160, 262144}, },
	{{135168, -348160, 368640}, {135168, -348160, 393216}, {135168, -479232, 368640}, {135168, -479232, 393216}, },
	{{135168, -479232, 368640}, {266240, -479232, 368640}, {135168, -348160, 368640}, {266240, -348160, 368640}, },
	{{266240, -479232, 368640}, {299008, -479232, 393216}, {266240, -348160, 368640}, {299008, -348160, 393216}, },
	{{-258048, -348160, 368640}, {-290816, -348160, 393216}, {-258048, -479232, 368640}, {-290816, -479232, 393216}, },
	{{-258048, -479232, 368640}, {-126976, -479232, 368640}, {-258048, -348160, 368640}, {-126976, -348160, 368640}, },
	{{-126976, -479232, 393216}, {-126976, -348160, 393216}, {-126976, -479232, 368640}, {-126976, -348160, 368640}, },
	{{-389120, -348160, 262144}, {-389120, -479232, 262144}, {-258048, -348160, 393216}, {-258048, -479232, 393216}, },
	{{-421888, -479232, 131072}, {-389120, -479232, 262144}, {-421888, -348160, 131072}, {-389120, -348160, 262144}, },
	{{-421888, -479232, 0}, {-421888, -479232, 131072}, {-421888, -348160, 0}, {-421888, -348160, 131072}, },
	{{-421888, -479232, -131072}, {-421888, -479232, 0}, {-421888, -348160, -131072}, {-421888, -348160, 0}, },
	{{-389120, -479232, -262144}, {-421888, -479232, -131072}, {-389120, -348160, -262144}, {-421888, -348160, -131072}, },
	{{-389120, -348160, -262144}, {-258048, -348160, -393216}, {-389120, -479232, -262144}, {-258048, -479232, -393216}, },
	{{-290816, -348160, -393216}, {-258048, -348160, -368640}, {-290816, -479232, -393216}, {-258048, -479232, -368640}, },
	{{-258048, -348160, -368640}, {-126976, -348160, -368640}, {-258048, -479232, -368640}, {-126976, -479232, -368640}, },
	{{-126976, -479232, -393216}, {-126976, -479232, -368640}, {-126976, -348160, -393216}, {-126976, -348160, -368640}, },
	{{135168, -479232, -393216}, {135168, -479232, -368640}, {135168, -610304, -393216}, {135168, -610304, -368640}, },
	{{135168, -479232, -368640}, {266240, -479232, -368640}, {135168, -610304, -368640}, {266240, -610304, -368640}, },
	{{299008, -610304, -393216}, {266240, -610304, -368640}, {299008, -479232, -393216}, {266240, -479232, -368640}, },
	{{266240, -479232, -393216}, {397312, -479232, -262144}, {266240, -610304, -393216}, {397312, -610304, -262144}, },
	{{397312, -479232, -262144}, {430080, -479232, -131072}, {397312, -610304, -262144}, {430080, -610304, -131072}, },
	{{430080, -479232, -131072}, {430080, -479232, 0}, {430080, -610304, -131072}, {430080, -610304, 0}, },
	{{430080, -479232, 0}, {430080, -479232, 131072}, {430080, -610304, 0}, {430080, -610304, 131072}, },
	{{430080, -479232, 131072}, {397312, -479232, 262144}, {430080, -610304, 131072}, {397312, -610304, 262144}, },
	{{266240, -610304, 393216}, {397312, -610304, 262144}, {266240, -479232, 393216}, {397312, -479232, 262144}, },
	{{135168, -479232, 368640}, {135168, -479232, 393216}, {135168, -610304, 368640}, {135168, -610304, 393216}, },
	{{135168, -610304, 368640}, {266240, -610304, 368640}, {135168, -479232, 368640}, {266240, -479232, 368640}, },
	{{266240, -610304, 368640}, {299008, -610304, 393216}, {266240, -479232, 368640}, {299008, -479232, 393216}, },
	{{-258048, -479232, 368640}, {-290816, -479232, 393216}, {-258048, -610304, 368640}, {-290816, -610304, 393216}, },
	{{-258048, -610304, 368640}, {-126976, -610304, 368640}, {-258048, -479232, 368640}, {-126976, -479232, 368640}, },
	{{-126976, -610304, 393216}, {-126976, -479232, 393216}, {-126976, -610304, 368640}, {-126976, -479232, 368640}, },
	{{-389120, -479232, 262144}, {-389120, -610304, 262144}, {-258048, -479232, 393216}, {-258048, -610304, 393216}, },
	{{-421888, -610304, 131072}, {-389120, -610304, 262144}, {-421888, -479232, 131072}, {-389120, -479232, 262144}, },
	{{-421888, -610304, 0}, {-421888, -610304, 131072}, {-421888, -479232, 0}, {-421888, -479232, 131072}, },
	{{-421888, -610304, -131072}, {-421888, -610304, 0}, {-421888, -479232, -131072}, {-421888, -479232, 0}, },
	{{-389120, -610304, -262144}, {-421888, -610304, -131072}, {-389120, -479232, -262144}, {-421888, -479232, -131072}, },
	{{-389120, -479232, -262144}, {-258048, -479232, -393216}, {-389120, -610304, -262144}, {-258048, -610304, -393216}, },
	{{-290816, -479232, -393216}, {-258048, -479232, -368640}, {-290816, -610304, -393216}, {-258048, -610304, -368640}, },
	{{-258048, -479232, -368640}, {-126976, -479232, -368640}, {-258048, -610304, -368640}, {-126976, -610304, -368640}, },
	{{-126976, -610304, -393216}, {-126976, -610304, -368640}, {-126976, -479232, -393216}, {-126976, -479232, -368640}, },
	{{135168, -610304, -393216}, {135168, -610304, -368640}, {135168, -741376, -393216}, {135168, -741376, -368640}, },
	{{135168, -610304, -368640}, {266240, -610304, -368640}, {135168, -741376, -368640}, {266240, -741376, -368640}, },
	{{299008, -741376, -393216}, {266240, -741376, -368640}, {299008, -610304, -393216}, {266240, -610304, -368640}, },
	{{266240, -610304, -393216}, {397312, -610304, -262144}, {266240, -741376, -393216}, {397312, -741376, -262144}, },
	{{397312, -610304, -262144}, {430080, -610304, -131072}, {397312, -741376, -262144}, {430080, -741376, -131072}, },
	{{430080, -610304, -131072}, {430080, -610304, 0}, {430080, -741376, -131072}, {430080, -741376, 0}, },
	{{430080, -610304, 0}, {430080, -610304, 131072}, {430080, -741376, 0}, {430080, -741376, 131072}, },
	{{430080, -610304, 131072}, {397312, -610304, 262144}, {430080, -741376, 131072}, {397312, -741376, 262144}, },
	{{266240, -741376, 393216}, {397312, -741376, 262144}, {266240, -610304, 393216}, {397312, -610304, 262144}, },
	{{135168, -610304, 368640}, {135168, -610304, 393216}, {135168, -741376, 368640}, {135168, -741376, 393216}, },
	{{135168, -741376, 368640}, {266240, -741376, 368640}, {135168, -610304, 368640}, {266240, -610304, 368640}, },
	{{266240, -741376, 368640}, {299008, -741376, 393216}, {266240, -610304, 368640}, {299008, -610304, 393216}, },
	{{-258048, -610304, 368640}, {-290816, -610304, 393216}, {-258048, -741376, 368640}, {-290816, -741376, 393216}, },
	{{-258048, -741376, 368640}, {-126976, -741376, 368640}, {-258048, -610304, 368640}, {-126976, -610304, 368640}, },
	{{-126976, -741376, 393216}, {-126976, -610304, 393216}, {-126976, -741376, 368640}, {-126976, -610304, 368640}, },
	{{-389120, -610304, 262144}, {-389120, -741376, 262144}, {-258048, -610304, 393216}, {-258048, -741376, 393216}, },
	{{-421888, -741376, 131072}, {-389120, -741376, 262144}, {-421888, -610304, 131072}, {-389120, -610304, 262144}, },
	{{-421888, -741376, 0}, {-421888, -741376, 131072}, {-421888, -610304, 0}, {-421888, -610304, 131072}, },
	{{-421888, -741376, -131072}, {-421888, -741376, 0}, {-421888, -610304, -131072}, {-421888, -610304, 0}, },
	{{-389120, -741376, -262144}, {-421888, -741376, -131072}, {-389120, -610304, -262144}, {-421888, -610304, -131072}, },
	{{-389120, -610304, -262144}, {-258048, -610304, -393216}, {-389120, -741376, -262144}, {-258048, -741376, -393216}, },
	{{-290816, -610304, -393216}, {-258048, -610304, -368640}, {-290816, -741376, -393216}, {-258048, -741376, -368640}, },
	{{-258048, -610304, -368640}, {-126976, -610304, -368640}, {-258048, -741376, -368640}, {-126976, -741376, -368640}, },
	{{-126976, -741376, -393216}, {-126976, -741376, -368640}, {-126976, -610304, -393216}, {-126976, -610304, -368640}, },
	{{135168, -741376, -393216}, {135168, -741376, -368640}, {135168, -872448, -393216}, {135168, -872448, -368640}, },
	{{135168, -741376, -368640}, {266240, -741376, -368640}, {135168, -872448, -368640}, {266240, -872448, -368640}, },
	{{299008, -872448, -393216}, {266240, -872448, -368640}, {299008, -741376, -393216}, {266240, -741376, -368640}, },
	{{266240, -741376, -393216}, {397312, -741376, -262144}, {266240, -872448, -393216}, {397312, -872448, -262144}, },
	{{397312, -741376, -262144}, {430080, -741376, -131072}, {397312, -872448, -262144}, {430080, -872448, -131072}, },
	{{430080, -741376, -131072}, {430080, -741376, 0}, {430080, -872448, -131072}, {430080, -872448, 0}, },
	{{430080, -741376, 0}, {430080, -741376, 131072}, {430080, -872448, 0}, {430080, -872448, 131072}, },
	{{430080, -741376, 131072}, {397312, -741376, 262144}, {430080, -872448, 131072}, {397312, -872448, 262144}, },
	{{266240, -872448, 393216}, {397312, -872448, 262144}, {266240, -741376, 393216}, {397312, -741376, 262144}, },
	{{135168, -741376, 368640}, {135168, -741376, 393216}, {135168, -872448, 368640}, {135168, -872448, 393216}, },
	{{135168, -872448, 368640}, {266240, -872448, 368640}, {135168, -741376, 368640}, {266240, -741376, 368640}, },
	{{266240, -872448, 368640}, {299008, -872448, 393216}, {266240, -741376, 368640}, {299008, -741376, 393216}, },
	{{-258048, -741376, 368640}, {-290816, -741376, 393216}, {-258048, -872448, 368640}, {-290816, -872448, 393216}, },
	{{-258048, -872448, 368640}, {-126976, -872448, 368640}, {-258048, -741376, 368640}, {-126976, -741376, 368640}, },
	{{-126976, -872448, 393216}, {-126976, -741376, 393216}, {-126976, -872448, 368640}, {-126976, -741376, 368640}, },
	{{-389120, -741376, 262144}, {-389120, -872448, 262144}, {-258048, -741376, 393216}, {-258048, -872448, 393216}, },
	{{-421888, -872448, 131072}, {-389120, -872448, 262144}, {-421888, -741376, 131072}, {-389120, -741376, 262144}, },
	{{-421888, -872448, 0}, {-421888, -872448, 131072}, {-421888, -741376, 0}, {-421888, -741376, 131072}, },
	{{-421888, -872448, -131072}, {-421888, -872448, 0}, {-421888, -741376, -131072}, {-421888, -741376, 0}, },
	{{-389120, -872448, -262144}, {-421888, -872448, -131072}, {-389120, -741376, -262144}, {-421888, -741376, -131072}, },
	{{-389120, -741376, -262144}, {-258048, -741376, -393216}, {-389120, -872448, -262144}, {-258048, -872448, -393216}, },
	{{-290816, -741376, -393216}, {-258048, -741376, -368640}, {-290816, -872448, -393216}, {-258048, -872448, -368640}, },
	{{-258048, -741376, -368640}, {-126976, -741376, -368640}, {-258048, -872448, -368640}, {-126976, -872448, -368640}, },
	{{-126976, -872448, -393216}, {-126976, -872448, -368640}, {-126976, -741376, -393216}, {-126976, -741376, -368640}, },
	{{135168, -872448, -393216}, {135168, -872448, -368640}, {135168, -1003520, -393216}, {135168, -1003520, -368640}, },
	{{135168, -872448, -368640}, {266240, -872448, -368640}, {135168, -1003520, -368640}, {266240, -1003520, -368640}, },
	{{299008, -1003520, -393216}, {266240, -1003520, -368640}, {299008, -872448, -393216}, {266240, -872448, -368640}, },
	{{266240, -872448, -393216}, {397312, -872448, -262144}, {266240, -1003520, -393216}, {397312, -1003520, -262144}, },
	{{397312, -872448, -262144}, {430080, -872448, -131072}, {397312, -1003520, -262144}, {430080, -1003520, -131072}, },
	{{430080, -872448, -131072}, {430080, -872448, 0}, {430080, -1003520, -131072}, {430080, -1003520, 0}, },
	{{430080, -872448, 0}, {430080, -872448, 131072}, {430080, -1003520, 0}, {430080, -1003520, 131072}, },
	{{430080, -872448, 131072}, {397312, -872448, 262144}, {430080, -1003520, 131072}, {397312, -1003520, 262144}, },
	{{266240, -1003520, 393216}, {397312, -1003520, 262144}, {266240, -872448, 393216}, {397312, -872448, 262144}, },
	{{135168, -872448, 368640}, {135168, -872448, 393216}, {135168, -1003520, 368640}, {135168, -1003520, 393216}, },
	{{135168, -1003520, 368640}, {266240, -1003520, 368640}, {135168, -872448, 368640}, {266240, -872448, 368640}, },
	{{266240, -1003520, 368640}, {299008, -1003520, 393216}, {266240, -872448, 368640}, {299008, -872448, 393216}, },
	{{-258048, -872448, 368640}, {-290816, -872448, 393216}, {-258048, -1003520, 368640}, {-290816, -1003520, 393216}, },
	{{-258048, -1003520, 368640}, {-126976, -1003520, 368640}, {-258048, -872448, 368640}, {-126976, -872448, 368640}, },
	{{-126976, -1003520, 393216}, {-126976, -872448, 393216}, {-126976, -1003520, 368640}, {-126976, -872448, 368640}, },
	{{-389120, -872448, 262144}, {-389120, -1003520, 262144}, {-258048, -872448, 393216}, {-258048, -1003520, 393216}, },
	{{-421888, -1003520, 131072}, {-389120, -1003520, 262144}, {-421888, -872448, 131072}, {-389120, -872448, 262144}, },
	{{-421888, -1003520, 0}, {-421888, -1003520, 131072}, {-421888, -872448, 0}, {-421888, -872448, 131072}, },
	{{-421888, -1003520, -131072}, {-421888, -1003520, 0}, {-421888, -872448, -131072}, {-421888, -872448, 0}, },
	{{-389120, -1003520, -262144}, {-421888, -1003520, -131072}, {-389120, -872448, -262144}, {-421888, -872448, -131072}, },
	{{-389120, -872448, -262144}, {-258048, -872448, -393216}, {-389120, -1003520, -262144}, {-258048, -1003520, -393216}, },
	{{-290816, -872448, -393216}, {-258048, -872448, -368640}, {-290816, -1003520, -393216}, {-258048, -1003520, -368640}, },
	{{-258048, -872448, -368640}, {-126976, -872448, -368640}, {-258048, -1003520, -368640}, {-126976, -1003520, -368640}, },
	{{-126976, -1003520, -393216}, {-126976, -1003520, -368640}, {-126976, -872448, -393216}, {-126976, -872448, -368640}, },
	{{135168, -1003520, -393216}, {135168, -1003520, -368640}, {135168, -1134592, -393216}, {135168, -1134592, -368640}, },
	{{135168, -1003520, -368640}, {266240, -1003520, -368640}, {135168, -1134592, -368640}, {266240, -1134592, -368640}, },
	{{299008, -1134592, -393216}, {266240, -1134592, -368640}, {299008, -1003520, -393216}, {266240, -1003520, -368640}, },
	{{266240, -1003520, -393216}, {397312, -1003520, -262144}, {266240, -1134592, -393216}, {397312, -1134592, -262144}, },
	{{397312, -1003520, -262144}, {430080, -1003520, -131072}, {397312, -1134592, -262144}, {430080, -1134592, -131072}, },
	{{430080, -1003520, -131072}, {430080, -1003520, 0}, {430080, -1134592, -131072}, {430080, -1134592, 0}, },
	{{430080, -1003520, 0}, {430080, -1003520, 131072}, {430080, -1134592, 0}, {430080, -1134592, 131072}, },
	{{430080, -1003520, 131072}, {397312, -1003520, 262144}, {430080, -1134592, 131072}, {397312, -1134592, 262144}, },
	{{266240, -1134592, 393216}, {397312, -1134592, 262144}, {266240, -1003520, 393216}, {397312, -1003520, 262144}, },
	{{135168, -1003520, 368640}, {135168, -1003520, 393216}, {135168, -1134592, 368640}, {135168, -1134592, 393216}, },
	{{135168, -1134592, 368640}, {266240, -1134592, 368640}, {135168, -1003520, 368640}, {266240, -1003520, 368640}, },
	{{266240, -1134592, 368640}, {299008, -1134592, 393216}, {266240, -1003520, 368640}, {299008, -1003520, 393216}, },
	{{-258048, -1003520, 368640}, {-290816, -1003520, 393216}, {-258048, -1134592, 368640}, {-290816, -1134592, 393216}, },
	{{-258048, -1134592, 368640}, {-126976, -1134592, 368640}, {-258048, -1003520, 368640}, {-126976, -1003520, 368640}, },
	{{-126976, -1134592, 393216}, {-126976, -1003520, 393216}, {-126976, -1134592, 368640}, {-126976, -1003520, 368640}, },
	{{-389120, -1003520, 262144}, {-389120, -1134592, 262144}, {-258048, -1003520, 393216}, {-258048, -1134592, 393216}, },
	{{-421888, -1134592, 131072}, {-389120, -1134592, 262144}, {-421888, -1003520, 131072}, {-389120, -1003520, 262144}, },
	{{-421888, -1134592, 0}, {-421888, -1134592, 131072}, {-421888, -1003520, 0}, {-421888, -1003520, 131072}, },
	{{-421888, -1134592, -131072}, {-421888, -1134592, 0}, {-421888, -1003520, -131072}, {-421888, -1003520, 0}, },
	{{-389120, -1134592, -262144}, {-421888, -1134592, -131072}, {-389120, -1003520, -262144}, {-421888, -1003520, -131072}, },
	{{-389120, -1003520, -262144}, {-258048, -1003520, -393216}, {-389120, -1134592, -262144}, {-258048, -1134592, -393216}, },
	{{-290816, -1003520, -393216}, {-258048, -1003520, -368640}, {-290816, -1134592, -393216}, {-258048, -1134592, -368640}, },
	{{-258048, -1003520, -368640}, {-126976, -1003520, -368640}, {-258048, -1134592, -368640}, {-126976, -1134592, -368640}, },
	{{-126976, -1134592, -393216}, {-126976, -1134592, -368640}, {-126976, -1003520, -393216}, {-126976, -1003520, -368640}, },
	{{135168, -1134592, -393216}, {135168, -1134592, -368640}, {135168, -1265664, -393216}, {135168, -1265664, -368640}, },
	{{135168, -1134592, -368640}, {266240, -1134592, -368640}, {135168, -1265664, -368640}, {266240, -1265664, -368640}, },
	{{299008, -1265664, -393216}, {266240, -1265664, -368640}, {299008, -1134592, -393216}, {266240, -1134592, -368640}, },
	{{266240, -1134592, -393216}, {397312, -1134592, -262144}, {266240, -1265664, -393216}, {397312, -1265664, -262144}, },
	{{397312, -1134592, -262144}, {430080, -1134592, -131072}, {397312, -1265664, -262144}, {430080, -1265664, -131072}, },
	{{430080, -1134592, -131072}, {430080, -1134592, 0}, {430080, -1265664, -131072}, {430080, -1265664, 0}, },
	{{430080, -1134592, 0}, {430080, -1134592, 131072}, {430080, -1265664, 0}, {430080, -1265664, 131072}, },
	{{430080, -1134592, 131072}, {397312, -1134592, 262144}, {430080, -1265664, 131072}, {397312, -1265664, 262144}, },
	{{266240, -1265664, 393216}, {397312, -1265664, 262144}, {266240, -1134592, 393216}, {397312, -1134592, 262144}, },
	{{135168, -1134592, 368640}, {135168, -1134592, 393216}, {135168, -1265664, 368640}, {135168, -1265664, 393216}, },
	{{135168, -1265664, 368640}, {266240, -1265664, 368640}, {135168, -1134592, 368640}, {266240, -1134592, 368640}, },
	{{266240, -1265664, 368640}, {299008, -1265664, 393216}, {266240, -1134592, 368640}, {299008, -1134592, 393216}, },
	{{-258048, -1134592, 368640}, {-290816, -1134592, 393216}, {-258048, -1265664, 368640}, {-290816, -1265664, 393216}, },
	{{-258048, -1265664, 368640}, {-126976, -1265664, 368640}, {-258048, -1134592, 368640}, {-126976, -1134592, 368640}, },
	{{-126976, -1265664, 393216}, {-126976, -1134592, 393216}, {-126976, -1265664, 368640}, {-126976, -1134592, 368640}, },
	{{-389120, -1134592, 262144}, {-389120, -1265664, 262144}, {-258048, -1134592, 393216}, {-258048, -1265664, 393216}, },
	{{-421888, -1265664, 131072}, {-389120, -1265664, 262144}, {-421888, -1134592, 131072}, {-389120, -1134592, 262144}, },
	{{-421888, -1265664, 0}, {-421888, -1265664, 131072}, {-421888, -1134592, 0}, {-421888, -1134592, 131072}, },
	{{-421888, -1265664, -131072}, {-421888, -1265664, 0}, {-421888, -1134592, -131072}, {-421888, -1134592, 0}, },
	{{-389120, -1265664, -262144}, {-421888, -1265664, -131072}, {-389120, -1134592, -262144}, {-421888, -1134592, -131072}, },
	{{-389120, -1134592, -262144}, {-258048, -1134592, -393216}, {-389120, -1265664, -262144}, {-258048, -1265664, -393216}, },
	{{-290816, -1134592, -393216}, {-258048, -1134592, -368640}, {-290816, -1265664, -393216}, {-258048, -1265664, -368640}, },
	{{-258048, -1134592, -368640}, {-126976, -1134592, -368640}, {-258048, -1265664, -368640}, {-126976, -1265664, -368640}, },
	{{-126976, -1265664, -393216}, {-126976, -1265664, -368640}, {-126976, -1134592, -393216}, {-126976, -1134592, -368640}, },
	{{135168, -1265664, -393216}, {135168, -1265664, -368640}, {135168, -1396736, -393216}, {135168, -1396736, -368640}, },
	{{135168, -1265664, -368640}, {266240, -1265664, -368640}, {135168, -1396736, -368640}, {266240, -1396736, -368640}, },
	{{299008, -1396736, -393216}, {266240, -1396736, -368640}, {299008, -1265664, -393216}, {266240, -1265664, -368640}, },
	{{266240, -1265664, -393216}, {397312, -1265664, -262144}, {266240, -1396736, -393216}, {397312, -1396736, -262144}, },
	{{397312, -1265664, -262144}, {430080, -1265664, -131072}, {397312, -1396736, -262144}, {430080, -1396736, -131072}, },
	{{430080, -1265664, -131072}, {430080, -1265664, 0}, {430080, -1396736, -131072}, {430080, -1396736, 0}, },
	{{430080, -1265664, 0}, {430080, -1265664, 131072}, {430080, -1396736, 0}, {430080, -1396736, 131072}, },
	{{430080, -1265664, 131072}, {397312, -1265664, 262144}, {430080, -1396736, 131072}, {397312, -1396736, 262144}, },
	{{266240, -1396736, 393216}, {397312, -1396736, 262144}, {266240, -1265664, 393216}, {397312, -1265664, 262144}, },
	{{135168, -1265664, 368640}, {135168, -1265664, 393216}, {135168, -1396736, 368640}, {135168, -1396736, 393216}, },
	{{135168, -1396736, 368640}, {266240, -1396736, 368640}, {135168, -1265664, 368640}, {266240, -1265664, 368640}, },
	{{266240, -1396736, 368640}, {299008, -1396736, 393216}, {266240, -1265664, 368640}, {299008, -1265664, 393216}, },
	{{-258048, -1265664, 368640}, {-290816, -1265664, 393216}, {-258048, -1396736, 368640}, {-290816, -1396736, 393216}, },
	{{-258048, -1396736, 368640}, {-126976, -1396736, 368640}, {-258048, -1265664, 368640}, {-126976, -1265664, 368640}, },
	{{-126976, -1396736, 393216}, {-126976, -1265664, 393216}, {-126976, -1396736, 368640}, {-126976, -1265664, 368640}, },
	{{-389120, -1265664, 262144}, {-389120, -1396736, 262144}, {-258048, -1265664, 393216}, {-258048, -1396736, 393216}, },
	{{-421888, -1396736, 131072}, {-389120, -1396736, 262144}, {-421888, -1265664, 131072}, {-389120, -1265664, 262144}, },
	{{-421888, -1396736, 0}, {-421888, -1396736, 131072}, {-421888, -1265664, 0}, {-421888, -1265664, 131072}, },
	{{-421888, -1396736, -131072}, {-421888, -1396736, 0}, {-421888, -1265664, -131072}, {-421888, -1265664, 0}, },
	{{-389120, -1396736, -262144}, {-421888, -1396736, -131072}, {-389120, -1265664, -262144}, {-421888, -1265664, -131072}, },
	{{-389120, -1265664, -262144}, {-258048, -1265664, -393216}, {-389120, -1396736, -262144}, {-258048, -1396736, -393216}, },
	{{-290816, -1265664, -393216}, {-258048, -1265664, -368640}, {-290816, -1396736, -393216}, {-258048, -1396736, -368640}, },
	{{-258048, -1265664, -368640}, {-126976, -1265664, -368640}, {-258048, -1396736, -368640}, {-126976, -1396736, -368640}, },
	{{-126976, -1396736, -393216}, {-126976, -1396736, -368640}, {-126976, -1265664, -393216}, {-126976, -1265664, -368640}, },
	{{135168, -1396736, -393216}, {135168, -1396736, -368640}, {135168, -1527808, -393216}, {135168, -1527808, -368640}, },
	{{135168, -1396736, -368640}, {266240, -1396736, -368640}, {135168, -1527808, -368640}, {266240, -1527808, -368640}, },
	{{299008, -1527808, -393216}, {266240, -1527808, -368640}, {299008, -1396736, -393216}, {266240, -1396736, -368640}, },
	{{266240, -1396736, -393216}, {397312, -1396736, -262144}, {266240, -1527808, -393216}, {397312, -1527808, -262144}, },
	{{397312, -1396736, -262144}, {430080, -1396736, -131072}, {397312, -1527808, -262144}, {430080, -1527808, -131072}, },
	{{430080, -1396736, -131072}, {430080, -1396736, 0}, {430080, -1527808, -131072}, {430080, -1527808, 0}, },
	{{430080, -1396736, 0}, {430080, -1396736, 131072}, {430080, -1527808, 0}, {430080, -1527808, 131072}, },
	{{430080, -1396736, 131072}, {397312, -1396736, 262144}, {430080, -1527808, 131072}, {397312, -1527808, 262144}, },
	{{266240, -1527808, 393216}, {397312, -1527808, 262144}, {266240, -1396736, 393216}, {397312, -1396736, 262144}, },
	{{135168, -1396736, 368640}, {135168, -1396736, 393216}, {135168, -1527808, 368640}, {135168, -1527808, 393216}, },
	{{135168, -1527808, 368640}, {266240, -1527808, 368640}, {135168, -1396736, 368640}, {266240, -1396736, 368640}, },
	{{266240, -1527808, 368640}, {299008, -1527808, 393216}, {266240, -1396736, 368640}, {299008, -1396736, 393216}, },
	{{-258048, -1396736, 368640}, {-290816, -1396736, 393216}, {-258048, -1527808, 368640}, {-290816, -1527808, 393216}, },
	{{-258048, -1527808, 368640}, {-126976, -1527808, 368640}, {-258048, -1396736, 368640}, {-126976, -1396736, 368640}, },
	{{-126976, -1527808, 393216}, {-126976, -1396736, 393216}, {-126976, -1527808, 368640}, {-126976, -1396736, 368640}, },
	{{-389120, -1396736, 262144}, {-389120, -1527808, 262144}, {-258048, -1396736, 393216}, {-258048, -1527808, 393216}, },
	{{-421888, -1527808, 131072}, {-389120, -1527808, 262144}, {-421888, -1396736, 131072}, {-389120, -1396736, 262144}, },
	{{-421888, -1527808, 0}, {-421888, -1527808, 131072}, {-421888, -1396736, 0}, {-421888, -1396736, 131072}, },
	{{-421888, -1527808, -131072}, {-421888, -1527808, 0}, {-421888, -1396736, -131072}, {-421888, -1396736, 0}, },
	{{-389120, -1527808, -262144}, {-421888, -1527808, -131072}, {-389120, -1396736, -262144}, {-421888, -1396736, -131072}, },
	{{-389120, -1396736, -262144}, {-258048, -1396736, -393216}, {-389120, -1527808, -262144}, {-258048, -1527808, -393216}, },
	{{-290816, -1396736, -393216}, {-258048, -1396736, -368640}, {-290816, -1527808, -393216}, {-258048, -1527808, -368640}, },
	{{-258048, -1396736, -368640}, {-126976, -1396736, -368640}, {-258048, -1527808, -368640}, {-126976, -1527808, -368640}, },
	{{-126976, -1527808, -393216}, {-126976, -1527808, -368640}, {-126976, -1396736, -393216}, {-126976, -1396736, -368640}, },
	{{135168, -1527808, -393216}, {135168, -1527808, -368640}, {135168, -1658880, -393216}, {135168, -1658880, -368640}, },
	{{135168, -1527808, -368640}, {266240, -1527808, -368640}, {135168, -1658880, -368640}, {266240, -1658880, -368640}, },
	{{299008, -1658880, -393216}, {266240, -1658880, -368640}, {299008, -1527808, -393216}, {266240, -1527808, -368640}, },
	{{266240, -1527808, -393216}, {397312, -1527808, -262144}, {266240, -1658880, -393216}, {397312, -1658880, -262144}, },
	{{397312, -1527808, -262144}, {430080, -1527808, -131072}, {397312, -1658880, -262144}, {430080, -1658880, -131072}, },
	{{430080, -1527808, -131072}, {430080, -1527808, 0}, {430080, -1658880, -131072}, {430080, -1658880, 0}, },
	{{430080, -1527808, 0}, {430080, -1527808, 131072}, {430080, -1658880, 0}, {430080, -1658880, 131072}, },
	{{430080, -1527808, 131072}, {397312, -1527808, 262144}, {430080, -1658880, 131072}, {397312, -1658880, 262144}, },
	{{266240, -1658880, 393216}, {397312, -1658880, 262144}, {266240, -1527808, 393216}, {397312, -1527808, 262144}, },
	{{135168, -1527808, 368640}, {135168, -1527808, 393216}, {135168, -1658880, 368640}, {135168, -1658880, 393216}, },
	{{135168, -1658880, 368640}, {266240, -1658880, 368640}, {135168, -1527808, 368640}, {266240, -1527808, 368640}, },
	{{266240, -1658880, 368640}, {299008, -1658880, 393216}, {266240, -1527808, 368640}, {299008, -1527808, 393216}, },
	{{-258048, -1527808, 368640}, {-290816, -1527808, 393216}, {-258048, -1658880, 368640}, {-290816, -1658880, 393216}, },
	{{-258048, -1658880, 368640}, {-126976, -1658880, 368640}, {-258048, -1527808, 368640}, {-126976, -1527808, 368640}, },
	{{-126976, -1658880, 393216}, {-126976, -1527808, 393216}, {-126976, -1658880, 368640}, {-126976, -1527808, 368640}, },
	{{-389120, -1527808, 262144}, {-389120, -1658880, 262144}, {-258048, -1527808, 393216}, {-258048, -1658880, 393216}, },
	{{-421888, -1658880, 131072}, {-389120, -1658880, 262144}, {-421888, -1527808, 131072}, {-389120, -1527808, 262144}, },
	{{-421888, -1658880, 0}, {-421888, -1658880, 131072}, {-421888, -1527808, 0}, {-421888, -1527808, 131072}, },
	{{-421888, -1658880, -131072}, {-421888, -1658880, 0}, {-421888, -1527808, -131072}, {-421888, -1527808, 0}, },
	{{-389120, -1658880, -262144}, {-421888, -1658880, -131072}, {-389120, -1527808, -262144}, {-421888, -1527808, -131072}, },
	{{-389120, -1527808, -262144}, {-258048, -1527808, -393216}, {-389120, -1658880, -262144}, {-258048, -1658880, -393216}, },
	{{-290816, -1527808, -393216}, {-258048, -1527808, -368640}, {-290816, -1658880, -393216}, {-258048, -1658880, -368640}, },
	{{-258048, -1527808, -368640}, {-126976, -1527808, -368640}, {-258048, -1658880, -368640}, {-126976, -1658880, -368640}, },
	{{-126976, -1658880, -393216}, {-126976, -1658880, -368640}, {-126976, -1527808, -393216}, {-126976, -1527808, -368640}, },
	{{135168, -1658880, -393216}, {135168, -1658880, -368640}, {135168, -1789952, -393216}, {135168, -1789952, -368640}, },
	{{135168, -1658880, -368640}, {266240, -1658880, -368640}, {135168, -1789952, -368640}, {266240, -1789952, -368640}, },
	{{299008, -1789952, -393216}, {266240, -1789952, -368640}, {299008, -1658880, -393216}, {266240, -1658880, -368640}, },
	{{266240, -1658880, -393216}, {397312, -1658880, -262144}, {266240, -1789952, -393216}, {397312, -1789952, -262144}, },
	{{397312, -1658880, -262144}, {430080, -1658880, -131072}, {397312, -1789952, -262144}, {430080, -1789952, -131072}, },
	{{430080, -1658880, -131072}, {430080, -1658880, 0}, {430080, -1789952, -131072}, {430080, -1789952, 0}, },
	{{430080, -1658880, 0}, {430080, -1658880, 131072}, {430080, -1789952, 0}, {430080, -1789952, 131072}, },
	{{430080, -1658880, 131072}, {397312, -1658880, 262144}, {430080, -1789952, 131072}, {397312, -1789952, 262144}, },
	{{266240, -1789952, 393216}, {397312, -1789952, 262144}, {266240, -1658880, 393216}, {397312, -1658880, 262144}, },
	{{135168, -1658880, 368640}, {135168, -1658880, 393216}, {135168, -1789952, 368640}, {135168, -1789952, 393216}, },
	{{135168, -1789952, 368640}, {266240, -1789952, 368640}, {135168, -1658880, 368640}, {266240, -1658880, 368640}, },
	{{266240, -1789952, 368640}, {299008, -1789952, 393216}, {266240, -1658880, 368640}, {299008, -1658880, 393216}, },
	{{-258048, -1658880, 368640}, {-290816, -1658880, 393216}, {-258048, -1789952, 368640}, {-290816, -1789952, 393216}, },
	{{-258048, -1789952, 368640}, {-126976, -1789952, 368640}, {-258048, -1658880, 368640}, {-126976, -1658880, 368640}, },
	{{-126976, -1789952, 393216}, {-126976, -1658880, 393216}, {-126976, -1789952, 368640}, {-126976, -1658880, 368640}, },
	{{-389120, -1658880, 262144}, {-389120, -1789952, 262144}, {-258048, -1658880, 393216}, {-258048, -1789952, 393216}, },
	{{-421888, -1789952, 131072}, {-389120, -1789952, 262144}, {-421888, -1658880, 131072}, {-389120, -1658880, 262144}, },
	{{-421888, -1789952, 0}, {-421888, -1789952, 131072}, {-421888, -1658880, 0}, {-421888, -1658880, 131072}, },
	{{-421888, -1789952, -131072}, {-421888, -1789952, 0}, {-421888, -1658880, -131072}, {-421888, -1658880, 0}, },
	{{-389120, -1789952, -262144}, {-421888, -1789952, -131072}, {-389120, -1658880, -262144}, {-421888, -1658880, -131072}, },
	{{-389120, -1658880, -262144}, {-258048, -1658880, -393216}, {-389120, -1789952, -262144}, {-258048, -1789952, -393216}, },
	{{-290816, -1658880, -393216}, {-258048, -1658880, -368640}, {-290816, -1789952, -393216}, {-258048, -1789952, -368640}, },
	{{-258048, -1658880, -368640}, {-126976, -1658880, -368640}, {-258048, -1789952, -368640}, {-126976, -1789952, -368640}, },
	{{-126976, -1789952, -393216}, {-126976, -1789952, -368640}, {-126976, -1658880, -393216}, {-126976, -1658880, -368640}, },
	{{-126976, -610304, 393216}, {4096, -610304, 393216}, {-126976, -479232, 393216}, {4096, -479232, 393216}, },
	{{-126976, -479232, 393216}, {4096, -479232, 393216}, {-126976, -479232, 409600}, {4096, -479232, 409600}, },
	{{4096, -610304, 393216}, {135168, -610304, 393216}, {4096, -479232, 393216}, {135168, -479232, 393216}, },
	{{4096, -479232, 393216}, {135168, -479232, 393216}, {4096, -479232, 409600}, {135168, -479232, 409600}, },
	{{-126976, -741376, 393216}, {4096, -741376, 393216}, {-126976, -610304, 393216}, {4096, -610304, 393216}, },
	{{4096, -741376, 393216}, {135168, -741376, 393216}, {4096, -610304, 393216}, {135168, -610304, 393216}, },
	{{4096, -872448, 393216}, {135168, -872448, 393216}, {4096, -741376, 393216}, {135168, -741376, 393216}, },
	{{-126976, -872448, 393216}, {4096, -872448, 393216}, {-126976, -741376, 393216}, {4096, -741376, 393216}, },
	{{-126976, -1003520, 393216}, {4096, -1003520, 393216}, {-126976, -872448, 393216}, {4096, -872448, 393216}, },
	{{4096, -1003520, 393216}, {135168, -1003520, 393216}, {4096, -872448, 393216}, {135168, -872448, 393216}, },
	{{4096, -1134592, 393216}, {135168, -1134592, 393216}, {4096, -1003520, 393216}, {135168, -1003520, 393216}, },
	{{-126976, -1134592, 393216}, {4096, -1134592, 393216}, {-126976, -1003520, 393216}, {4096, -1003520, 393216}, },
	{{-126976, -1265664, 393216}, {4096, -1265664, 393216}, {-126976, -1134592, 393216}, {4096, -1134592, 393216}, },
	{{4096, -1265664, 393216}, {135168, -1265664, 393216}, {4096, -1134592, 393216}, {135168, -1134592, 393216}, },
	{{4096, -1396736, 393216}, {135168, -1396736, 393216}, {4096, -1265664, 393216}, {135168, -1265664, 393216}, },
	{{-126976, -1396736, 393216}, {4096, -1396736, 393216}, {-126976, -1265664, 393216}, {4096, -1265664, 393216}, },
	{{-126976, -1527808, 393216}, {4096, -1527808, 393216}, {-126976, -1396736, 393216}, {4096, -1396736, 393216}, },
	{{4096, -1527808, 393216}, {135168, -1527808, 393216}, {4096, -1396736, 393216}, {135168, -1396736, 393216}, },
	{{4096, -1658880, 393216}, {135168, -1658880, 393216}, {4096, -1527808, 393216}, {135168, -1527808, 393216}, },
	{{-126976, -1658880, 393216}, {4096, -1658880, 393216}, {-126976, -1527808, 393216}, {4096, -1527808, 393216}, },
	{{-126976, -1789952, 393216}, {4096, -1789952, 393216}, {-126976, -1658880, 393216}, {4096, -1658880, 393216}, },
	{{4096, -1789952, 393216}, {135168, -1789952, 393216}, {4096, -1658880, 393216}, {135168, -1658880, 393216}, },
	{{-73728, 45056, 409600}, {81920, 45056, 409600}, {-73728, 45056, 393216}, {81920, 45056, 393216}, },
	{{-61440, 45056, 540672}, {4096, 45056, 540672}, {-61440, 45056, 409600}, {4096, 45056, 409600}, },
	{{4096, 45056, 540672}, {86016, 45056, 540672}, {4096, 45056, 409600}, {86016, 45056, 409600}, },
	{{-61440, 45056, 671744}, {4096, 45056, 671744}, {-61440, 45056, 540672}, {4096, 45056, 540672}, },
	{{4096, 45056, 671744}, {86016, 45056, 671744}, {4096, 45056, 540672}, {86016, 45056, 540672}, },
	{{-61440, 45056, 729088}, {4096, 45056, 729088}, {-61440, 45056, 671744}, {4096, 45056, 671744}, },
	{{4096, 45056, 729088}, {77824, 45056, 729088}, {4096, 45056, 671744}, {77824, 45056, 671744}, },
	{{-61440, 45056, 884736}, {4096, 45056, 884736}, {-61440, 45056, 802816}, {4096, 45056, 802816}, },
	{{4096, 45056, 884736}, {77824, 45056, 884736}, {4096, 45056, 802816}, {77824, 45056, 802816}, },
	{{135168, 45056, 802816}, {266240, 45056, 802816}, {135168, 45056, 720896}, {266240, 45056, 720896}, },
	{{135168, 45056, 884736}, {266240, 45056, 884736}, {135168, 45056, 802816}, {266240, 45056, 802816}, },
	{{266240, 45056, 802816}, {397312, 45056, 802816}, {266240, 45056, 720896}, {397312, 45056, 720896}, },
	{{266240, 45056, 884736}, {397312, 45056, 884736}, {266240, 45056, 802816}, {397312, 45056, 802816}, },
	{{446464, 45056, 1064960}, {528384, 45056, 1064960}, {446464, 45056, 933888}, {528384, 45056, 933888}, },
	{{528384, 45056, 1064960}, {614400, 45056, 1064960}, {528384, 45056, 933888}, {614400, 45056, 933888}, },
	{{446464, 45056, 1196032}, {528384, 45056, 1196032}, {446464, 45056, 1064960}, {528384, 45056, 1064960}, },
	{{528384, 45056, 1196032}, {614400, 45056, 1196032}, {528384, 45056, 1064960}, {614400, 45056, 1064960}, },
	{{446464, 45056, 1327104}, {528384, 45056, 1327104}, {446464, 45056, 1196032}, {528384, 45056, 1196032}, },
	{{528384, 45056, 1327104}, {614400, 45056, 1327104}, {528384, 45056, 1196032}, {614400, 45056, 1196032}, },
	{{446464, 45056, 1458176}, {528384, 45056, 1458176}, {446464, 45056, 1327104}, {528384, 45056, 1327104}, },
	{{528384, 45056, 1458176}, {614400, 45056, 1458176}, {528384, 45056, 1327104}, {614400, 45056, 1327104}, },
	{{266240, 45056, 1589248}, {397312, 45056, 1589248}, {266240, 45056, 1507328}, {397312, 45056, 1507328}, },
	{{135168, 45056, 1589248}, {266240, 45056, 1589248}, {135168, 45056, 1507328}, {266240, 45056, 1507328}, },
	{{135168, 45056, 1675264}, {266240, 45056, 1675264}, {135168, 45056, 1589248}, {266240, 45056, 1589248}, },
	{{266240, 45056, 1675264}, {397312, 45056, 1675264}, {266240, 45056, 1589248}, {397312, 45056, 1589248}, },
	{{-77824, 45056, 1982464}, {4096, 45056, 1982464}, {-77824, 45056, 1851392}, {4096, 45056, 1851392}, },
	{{-77824, 45056, 1851392}, {4096, 45056, 1851392}, {-77824, 45056, 1720320}, {4096, 45056, 1720320}, },
	{{4096, 45056, 1851392}, {86016, 45056, 1851392}, {4096, 45056, 1720320}, {86016, 45056, 1720320}, },
	{{4096, 45056, 1982464}, {86016, 45056, 1982464}, {4096, 45056, 1851392}, {86016, 45056, 1851392}, },
	{{-389120, -1789952, 262144}, {-258048, -1789952, 393216}, {-389120, -1822720, 262144}, {-258048, -1822720, 393216}, },
	{{-389120, -1822720, 262144}, {-258048, -1822720, 262144}, {-389120, -1789952, 262144}, {-258048, -1789952, 262144}, },
	{{-258048, -1789952, 393216}, {-258048, -1789952, 262144}, {-258048, -1822720, 393216}, {-258048, -1822720, 262144}, },
	{{-389120, -1789952, 131072}, {-389120, -1789952, 262144}, {-389120, -1822720, 131072}, {-389120, -1822720, 262144}, },
	{{-389120, -1822720, 131072}, {-258048, -1822720, 131072}, {-389120, -1789952, 131072}, {-258048, -1789952, 131072}, },
	{{-389120, -1789952, 131072}, {-258048, -1789952, 131072}, {-389120, -1789952, 262144}, {-258048, -1789952, 262144}, },
	{{-389120, -1822720, 262144}, {-258048, -1822720, 262144}, {-389120, -1822720, 131072}, {-258048, -1822720, 131072}, },
	{{-389120, -1789952, 262144}, {-258048, -1789952, 262144}, {-389120, -1822720, 262144}, {-258048, -1822720, 262144}, },
	{{-258048, -1822720, 131072}, {-258048, -1822720, 262144}, {-258048, -1789952, 131072}, {-258048, -1789952, 262144}, },
	{{-389120, -1789952, 0}, {-389120, -1789952, 131072}, {-389120, -1822720, 0}, {-389120, -1822720, 131072}, },
	{{-389120, -1822720, 0}, {-258048, -1822720, 0}, {-389120, -1789952, 0}, {-258048, -1789952, 0}, },
	{{-389120, -1789952, 0}, {-258048, -1789952, 0}, {-389120, -1789952, 131072}, {-258048, -1789952, 131072}, },
	{{-389120, -1822720, 131072}, {-258048, -1822720, 131072}, {-389120, -1822720, 0}, {-258048, -1822720, 0}, },
	{{-389120, -1789952, 131072}, {-258048, -1789952, 131072}, {-389120, -1822720, 131072}, {-258048, -1822720, 131072}, },
	{{-258048, -1822720, 0}, {-258048, -1822720, 131072}, {-258048, -1789952, 0}, {-258048, -1789952, 131072}, },
	{{-389120, -1789952, -131072}, {-389120, -1789952, 0}, {-389120, -1822720, -131072}, {-389120, -1822720, 0}, },
	{{-389120, -1822720, -131072}, {-258048, -1822720, -131072}, {-389120, -1789952, -131072}, {-258048, -1789952, -131072}, },
	{{-389120, -1789952, -131072}, {-258048, -1789952, -131072}, {-389120, -1789952, 0}, {-258048, -1789952, 0}, },
	{{-389120, -1822720, 0}, {-258048, -1822720, 0}, {-389120, -1822720, -131072}, {-258048, -1822720, -131072}, },
	{{-389120, -1789952, 0}, {-258048, -1789952, 0}, {-389120, -1822720, 0}, {-258048, -1822720, 0}, },
	{{-258048, -1822720, -131072}, {-258048, -1822720, 0}, {-258048, -1789952, -131072}, {-258048, -1789952, 0}, },
	{{-389120, -1789952, -262144}, {-389120, -1789952, -131072}, {-389120, -1822720, -262144}, {-389120, -1822720, -131072}, },
	{{-389120, -1822720, -262144}, {-258048, -1822720, -262144}, {-389120, -1789952, -262144}, {-258048, -1789952, -262144}, },
	{{-389120, -1789952, -262144}, {-258048, -1789952, -262144}, {-389120, -1789952, -131072}, {-258048, -1789952, -131072}, },
	{{-389120, -1822720, -131072}, {-258048, -1822720, -131072}, {-389120, -1822720, -262144}, {-258048, -1822720, -262144}, },
	{{-389120, -1789952, -131072}, {-258048, -1789952, -131072}, {-389120, -1822720, -131072}, {-258048, -1822720, -131072}, },
	{{-258048, -1822720, -262144}, {-258048, -1822720, -131072}, {-258048, -1789952, -262144}, {-258048, -1789952, -131072}, },
	{{-258048, -1789952, -262144}, {-258048, -1789952, -131072}, {-258048, -1822720, -262144}, {-258048, -1822720, -131072}, },
	{{-258048, -1822720, -262144}, {-126976, -1822720, -262144}, {-258048, -1789952, -262144}, {-126976, -1789952, -262144}, },
	{{-258048, -1789952, -262144}, {-126976, -1789952, -262144}, {-258048, -1789952, -131072}, {-126976, -1789952, -131072}, },
	{{-258048, -1822720, -131072}, {-126976, -1822720, -131072}, {-258048, -1822720, -262144}, {-126976, -1822720, -262144}, },
	{{-258048, -1789952, -131072}, {-126976, -1789952, -131072}, {-258048, -1822720, -131072}, {-126976, -1822720, -131072}, },
	{{-126976, -1822720, -262144}, {-126976, -1822720, -131072}, {-126976, -1789952, -262144}, {-126976, -1789952, -131072}, },
	{{-126976, -1789952, -262144}, {-126976, -1789952, -131072}, {-126976, -1822720, -262144}, {-126976, -1822720, -131072}, },
	{{-126976, -1822720, -262144}, {4096, -1822720, -262144}, {-126976, -1789952, -262144}, {4096, -1789952, -262144}, },
	{{-126976, -1789952, -262144}, {4096, -1789952, -262144}, {-126976, -1789952, -131072}, {4096, -1789952, -131072}, },
	{{-126976, -1822720, -131072}, {4096, -1822720, -131072}, {-126976, -1822720, -262144}, {4096, -1822720, -262144}, },
	{{-126976, -1789952, -131072}, {4096, -1789952, -131072}, {-126976, -1822720, -131072}, {4096, -1822720, -131072}, },
	{{4096, -1822720, -262144}, {4096, -1822720, -131072}, {4096, -1789952, -262144}, {4096, -1789952, -131072}, },
	{{4096, -1789952, -262144}, {4096, -1789952, -131072}, {4096, -1822720, -262144}, {4096, -1822720, -131072}, },
	{{4096, -1822720, -262144}, {135168, -1822720, -262144}, {4096, -1789952, -262144}, {135168, -1789952, -262144}, },
	{{4096, -1789952, -262144}, {135168, -1789952, -262144}, {4096, -1789952, -131072}, {135168, -1789952, -131072}, },
	{{4096, -1822720, -131072}, {135168, -1822720, -131072}, {4096, -1822720, -262144}, {135168, -1822720, -262144}, },
	{{4096, -1789952, -131072}, {135168, -1789952, -131072}, {4096, -1822720, -131072}, {135168, -1822720, -131072}, },
	{{135168, -1822720, -262144}, {135168, -1822720, -131072}, {135168, -1789952, -262144}, {135168, -1789952, -131072}, },
	{{135168, -1789952, -262144}, {135168, -1789952, -131072}, {135168, -1822720, -262144}, {135168, -1822720, -131072}, },
	{{135168, -1822720, -262144}, {266240, -1822720, -262144}, {135168, -1789952, -262144}, {266240, -1789952, -262144}, },
	{{135168, -1789952, -262144}, {266240, -1789952, -262144}, {135168, -1789952, -131072}, {266240, -1789952, -131072}, },
	{{135168, -1822720, -131072}, {266240, -1822720, -131072}, {135168, -1822720, -262144}, {266240, -1822720, -262144}, },
	{{135168, -1789952, -131072}, {266240, -1789952, -131072}, {135168, -1822720, -131072}, {266240, -1822720, -131072}, },
	{{266240, -1822720, -262144}, {266240, -1822720, -131072}, {266240, -1789952, -262144}, {266240, -1789952, -131072}, },
	{{266240, -1789952, -262144}, {266240, -1789952, -131072}, {266240, -1822720, -262144}, {266240, -1822720, -131072}, },
	{{266240, -1822720, -262144}, {397312, -1822720, -262144}, {266240, -1789952, -262144}, {397312, -1789952, -262144}, },
	{{266240, -1789952, -262144}, {397312, -1789952, -262144}, {266240, -1789952, -131072}, {397312, -1789952, -131072}, },
	{{266240, -1822720, -131072}, {397312, -1822720, -131072}, {266240, -1822720, -262144}, {397312, -1822720, -262144}, },
	{{266240, -1789952, -131072}, {397312, -1789952, -131072}, {266240, -1822720, -131072}, {397312, -1822720, -131072}, },
	{{397312, -1822720, -262144}, {397312, -1822720, -131072}, {397312, -1789952, -262144}, {397312, -1789952, -131072}, },
	{{266240, -1789952, -131072}, {266240, -1789952, 0}, {266240, -1822720, -131072}, {266240, -1822720, 0}, },
	{{266240, -1822720, -131072}, {397312, -1822720, -131072}, {266240, -1789952, -131072}, {397312, -1789952, -131072}, },
	{{266240, -1789952, -131072}, {397312, -1789952, -131072}, {266240, -1789952, 0}, {397312, -1789952, 0}, },
	{{266240, -1822720, 0}, {397312, -1822720, 0}, {266240, -1822720, -131072}, {397312, -1822720, -131072}, },
	{{266240, -1789952, 0}, {397312, -1789952, 0}, {266240, -1822720, 0}, {397312, -1822720, 0}, },
	{{397312, -1822720, -131072}, {397312, -1822720, 0}, {397312, -1789952, -131072}, {397312, -1789952, 0}, },
	{{266240, -1789952, 0}, {266240, -1789952, 131072}, {266240, -1822720, 0}, {266240, -1822720, 131072}, },
	{{266240, -1822720, 0}, {397312, -1822720, 0}, {266240, -1789952, 0}, {397312, -1789952, 0}, },
	{{266240, -1789952, 0}, {397312, -1789952, 0}, {266240, -1789952, 131072}, {397312, -1789952, 131072}, },
	{{266240, -1822720, 131072}, {397312, -1822720, 131072}, {266240, -1822720, 0}, {397312, -1822720, 0}, },
	{{266240, -1789952, 131072}, {397312, -1789952, 131072}, {266240, -1822720, 131072}, {397312, -1822720, 131072}, },
	{{397312, -1822720, 0}, {397312, -1822720, 131072}, {397312, -1789952, 0}, {397312, -1789952, 131072}, },
	{{266240, -1789952, 131072}, {266240, -1789952, 262144}, {266240, -1822720, 131072}, {266240, -1822720, 262144}, },
	{{266240, -1822720, 131072}, {397312, -1822720, 131072}, {266240, -1789952, 131072}, {397312, -1789952, 131072}, },
	{{266240, -1789952, 131072}, {397312, -1789952, 131072}, {266240, -1789952, 262144}, {397312, -1789952, 262144}, },
	{{266240, -1822720, 262144}, {397312, -1822720, 262144}, {266240, -1822720, 131072}, {397312, -1822720, 131072}, },
	{{266240, -1789952, 262144}, {397312, -1789952, 262144}, {266240, -1822720, 262144}, {397312, -1822720, 262144}, },
	{{397312, -1822720, 131072}, {397312, -1822720, 262144}, {397312, -1789952, 131072}, {397312, -1789952, 262144}, },
	{{266240, -1789952, 262144}, {266240, -1789952, 393216}, {266240, -1822720, 262144}, {266240, -1822720, 393216}, },
	{{266240, -1822720, 262144}, {397312, -1822720, 262144}, {266240, -1789952, 262144}, {397312, -1789952, 262144}, },
	{{266240, -1789952, 393216}, {397312, -1789952, 262144}, {266240, -1822720, 393216}, {397312, -1822720, 262144}, },
	{{135168, -1789952, 262144}, {135168, -1789952, 393216}, {135168, -1822720, 262144}, {135168, -1822720, 393216}, },
	{{135168, -1822720, 262144}, {266240, -1822720, 262144}, {135168, -1789952, 262144}, {266240, -1789952, 262144}, },
	{{135168, -1789952, 262144}, {266240, -1789952, 262144}, {135168, -1789952, 393216}, {266240, -1789952, 393216}, },
	{{135168, -1822720, 393216}, {266240, -1822720, 393216}, {135168, -1822720, 262144}, {266240, -1822720, 262144}, },
	{{135168, -1789952, 393216}, {266240, -1789952, 393216}, {135168, -1822720, 393216}, {266240, -1822720, 393216}, },
	{{266240, -1822720, 262144}, {266240, -1822720, 393216}, {266240, -1789952, 262144}, {266240, -1789952, 393216}, },
	{{4096, -1789952, 262144}, {4096, -1789952, 393216}, {4096, -1822720, 262144}, {4096, -1822720, 393216}, },
	{{4096, -1822720, 262144}, {135168, -1822720, 262144}, {4096, -1789952, 262144}, {135168, -1789952, 262144}, },
	{{4096, -1789952, 262144}, {135168, -1789952, 262144}, {4096, -1789952, 393216}, {135168, -1789952, 393216}, },
	{{4096, -1822720, 393216}, {135168, -1822720, 393216}, {4096, -1822720, 262144}, {135168, -1822720, 262144}, },
	{{4096, -1789952, 393216}, {135168, -1789952, 393216}, {4096, -1822720, 393216}, {135168, -1822720, 393216}, },
	{{135168, -1822720, 262144}, {135168, -1822720, 393216}, {135168, -1789952, 262144}, {135168, -1789952, 393216}, },
	{{-126976, -1789952, 262144}, {-126976, -1789952, 393216}, {-126976, -1822720, 262144}, {-126976, -1822720, 393216}, },
	{{-126976, -1822720, 262144}, {4096, -1822720, 262144}, {-126976, -1789952, 262144}, {4096, -1789952, 262144}, },
	{{-126976, -1789952, 262144}, {4096, -1789952, 262144}, {-126976, -1789952, 393216}, {4096, -1789952, 393216}, },
	{{-126976, -1822720, 393216}, {4096, -1822720, 393216}, {-126976, -1822720, 262144}, {4096, -1822720, 262144}, },
	{{-126976, -1789952, 393216}, {4096, -1789952, 393216}, {-126976, -1822720, 393216}, {4096, -1822720, 393216}, },
	{{4096, -1822720, 262144}, {4096, -1822720, 393216}, {4096, -1789952, 262144}, {4096, -1789952, 393216}, },
	{{-258048, -1789952, 262144}, {-258048, -1789952, 393216}, {-258048, -1822720, 262144}, {-258048, -1822720, 393216}, },
	{{-258048, -1822720, 262144}, {-126976, -1822720, 262144}, {-258048, -1789952, 262144}, {-126976, -1789952, 262144}, },
	{{-258048, -1789952, 262144}, {-126976, -1789952, 262144}, {-258048, -1789952, 393216}, {-126976, -1789952, 393216}, },
	{{-258048, -1822720, 393216}, {-126976, -1822720, 393216}, {-258048, -1822720, 262144}, {-126976, -1822720, 262144}, },
	{{-258048, -1789952, 393216}, {-126976, -1789952, 393216}, {-258048, -1822720, 393216}, {-126976, -1822720, 393216}, },
	{{-126976, -1822720, 262144}, {-126976, -1822720, 393216}, {-126976, -1789952, 262144}, {-126976, -1789952, 393216}, },
	{{-258048, -1789952, 131072}, {-258048, -1789952, 262144}, {-258048, -1822720, 131072}, {-258048, -1822720, 262144}, },
	{{-258048, -1822720, 131072}, {-126976, -1822720, 131072}, {-258048, -1789952, 131072}, {-126976, -1789952, 131072}, },
	{{-258048, -1789952, 131072}, {-126976, -1789952, 131072}, {-258048, -1789952, 262144}, {-126976, -1789952, 262144}, },
	{{-258048, -1822720, 262144}, {-126976, -1822720, 262144}, {-258048, -1822720, 131072}, {-126976, -1822720, 131072}, },
	{{-258048, -1789952, 262144}, {-126976, -1789952, 262144}, {-258048, -1822720, 262144}, {-126976, -1822720, 262144}, },
	{{-126976, -1822720, 131072}, {-126976, -1822720, 262144}, {-126976, -1789952, 131072}, {-126976, -1789952, 262144}, },
	{{-258048, -1789952, 0}, {-258048, -1789952, 131072}, {-258048, -1822720, 0}, {-258048, -1822720, 131072}, },
	{{-258048, -1822720, 0}, {-126976, -1822720, 0}, {-258048, -1789952, 0}, {-126976, -1789952, 0}, },
	{{-258048, -1789952, 0}, {-126976, -1789952, 0}, {-258048, -1789952, 131072}, {-126976, -1789952, 131072}, },
	{{-258048, -1822720, 131072}, {-126976, -1822720, 131072}, {-258048, -1822720, 0}, {-126976, -1822720, 0}, },
	{{-258048, -1789952, 131072}, {-126976, -1789952, 131072}, {-258048, -1822720, 131072}, {-126976, -1822720, 131072}, },
	{{-126976, -1822720, 0}, {-126976, -1822720, 131072}, {-126976, -1789952, 0}, {-126976, -1789952, 131072}, },
	{{-258048, -1789952, -131072}, {-258048, -1789952, 0}, {-258048, -1822720, -131072}, {-258048, -1822720, 0}, },
	{{-258048, -1822720, -131072}, {-126976, -1822720, -131072}, {-258048, -1789952, -131072}, {-126976, -1789952, -131072}, },
	{{-258048, -1789952, -131072}, {-126976, -1789952, -131072}, {-258048, -1789952, 0}, {-126976, -1789952, 0}, },
	{{-258048, -1822720, 0}, {-126976, -1822720, 0}, {-258048, -1822720, -131072}, {-126976, -1822720, -131072}, },
	{{-258048, -1789952, 0}, {-126976, -1789952, 0}, {-258048, -1822720, 0}, {-126976, -1822720, 0}, },
	{{-126976, -1822720, -131072}, {-126976, -1822720, 0}, {-126976, -1789952, -131072}, {-126976, -1789952, 0}, },
	{{-126976, -1789952, -131072}, {-126976, -1789952, 0}, {-126976, -1822720, -131072}, {-126976, -1822720, 0}, },
	{{-126976, -1822720, -131072}, {4096, -1822720, -131072}, {-126976, -1789952, -131072}, {4096, -1789952, -131072}, },
	{{-126976, -1789952, -131072}, {4096, -1789952, -131072}, {-126976, -1789952, 0}, {4096, -1789952, 0}, },
	{{-126976, -1822720, 0}, {4096, -1822720, 0}, {-126976, -1822720, -131072}, {4096, -1822720, -131072}, },
	{{-126976, -1789952, 0}, {4096, -1789952, 0}, {-126976, -1822720, 0}, {4096, -1822720, 0}, },
	{{4096, -1822720, -131072}, {4096, -1822720, 0}, {4096, -1789952, -131072}, {4096, -1789952, 0}, },
	{{4096, -1789952, -131072}, {4096, -1789952, 0}, {4096, -1822720, -131072}, {4096, -1822720, 0}, },
	{{4096, -1822720, -131072}, {135168, -1822720, -131072}, {4096, -1789952, -131072}, {135168, -1789952, -131072}, },
	{{4096, -1789952, -131072}, {135168, -1789952, -131072}, {4096, -1789952, 0}, {135168, -1789952, 0}, },
	{{4096, -1822720, 0}, {135168, -1822720, 0}, {4096, -1822720, -131072}, {135168, -1822720, -131072}, },
	{{4096, -1789952, 0}, {135168, -1789952, 0}, {4096, -1822720, 0}, {135168, -1822720, 0}, },
	{{135168, -1822720, -131072}, {135168, -1822720, 0}, {135168, -1789952, -131072}, {135168, -1789952, 0}, },
	{{135168, -1789952, -131072}, {135168, -1789952, 0}, {135168, -1822720, -131072}, {135168, -1822720, 0}, },
	{{135168, -1822720, -131072}, {266240, -1822720, -131072}, {135168, -1789952, -131072}, {266240, -1789952, -131072}, },
	{{135168, -1789952, -131072}, {266240, -1789952, -131072}, {135168, -1789952, 0}, {266240, -1789952, 0}, },
	{{135168, -1822720, 0}, {266240, -1822720, 0}, {135168, -1822720, -131072}, {266240, -1822720, -131072}, },
	{{135168, -1789952, 0}, {266240, -1789952, 0}, {135168, -1822720, 0}, {266240, -1822720, 0}, },
	{{266240, -1822720, -131072}, {266240, -1822720, 0}, {266240, -1789952, -131072}, {266240, -1789952, 0}, },
	{{135168, -1789952, 0}, {135168, -1789952, 131072}, {135168, -1822720, 0}, {135168, -1822720, 131072}, },
	{{135168, -1822720, 0}, {266240, -1822720, 0}, {135168, -1789952, 0}, {266240, -1789952, 0}, },
	{{135168, -1789952, 0}, {266240, -1789952, 0}, {135168, -1789952, 131072}, {266240, -1789952, 131072}, },
	{{135168, -1822720, 131072}, {266240, -1822720, 131072}, {135168, -1822720, 0}, {266240, -1822720, 0}, },
	{{135168, -1789952, 131072}, {266240, -1789952, 131072}, {135168, -1822720, 131072}, {266240, -1822720, 131072}, },
	{{266240, -1822720, 0}, {266240, -1822720, 131072}, {266240, -1789952, 0}, {266240, -1789952, 131072}, },
	{{135168, -1789952, 131072}, {135168, -1789952, 262144}, {135168, -1822720, 131072}, {135168, -1822720, 262144}, },
	{{135168, -1822720, 131072}, {266240, -1822720, 131072}, {135168, -1789952, 131072}, {266240, -1789952, 131072}, },
	{{135168, -1789952, 131072}, {266240, -1789952, 131072}, {135168, -1789952, 262144}, {266240, -1789952, 262144}, },
	{{135168, -1822720, 262144}, {266240, -1822720, 262144}, {135168, -1822720, 131072}, {266240, -1822720, 131072}, },
	{{135168, -1789952, 262144}, {266240, -1789952, 262144}, {135168, -1822720, 262144}, {266240, -1822720, 262144}, },
	{{266240, -1822720, 131072}, {266240, -1822720, 262144}, {266240, -1789952, 131072}, {266240, -1789952, 262144}, },
	{{4096, -1789952, 131072}, {4096, -1789952, 262144}, {4096, -1822720, 131072}, {4096, -1822720, 262144}, },
	{{4096, -1822720, 131072}, {135168, -1822720, 131072}, {4096, -1789952, 131072}, {135168, -1789952, 131072}, },
	{{4096, -1789952, 131072}, {135168, -1789952, 131072}, {4096, -1789952, 262144}, {135168, -1789952, 262144}, },
	{{4096, -1822720, 262144}, {135168, -1822720, 262144}, {4096, -1822720, 131072}, {135168, -1822720, 131072}, },
	{{4096, -1789952, 262144}, {135168, -1789952, 262144}, {4096, -1822720, 262144}, {135168, -1822720, 262144}, },
	{{135168, -1822720, 131072}, {135168, -1822720, 262144}, {135168, -1789952, 131072}, {135168, -1789952, 262144}, },
	{{-126976, -1789952, 131072}, {-126976, -1789952, 262144}, {-126976, -1822720, 131072}, {-126976, -1822720, 262144}, },
	{{-126976, -1822720, 131072}, {4096, -1822720, 131072}, {-126976, -1789952, 131072}, {4096, -1789952, 131072}, },
	{{-126976, -1789952, 131072}, {4096, -1789952, 131072}, {-126976, -1789952, 262144}, {4096, -1789952, 262144}, },
	{{-126976, -1822720, 262144}, {4096, -1822720, 262144}, {-126976, -1822720, 131072}, {4096, -1822720, 131072}, },
	{{-126976, -1789952, 262144}, {4096, -1789952, 262144}, {-126976, -1822720, 262144}, {4096, -1822720, 262144}, },
	{{4096, -1822720, 131072}, {4096, -1822720, 262144}, {4096, -1789952, 131072}, {4096, -1789952, 262144}, },
	{{-126976, -1789952, 0}, {-126976, -1789952, 131072}, {-126976, -1822720, 0}, {-126976, -1822720, 131072}, },
	{{-126976, -1822720, 0}, {4096, -1822720, 0}, {-126976, -1789952, 0}, {4096, -1789952, 0}, },
	{{-126976, -1789952, 0}, {4096, -1789952, 0}, {-126976, -1789952, 131072}, {4096, -1789952, 131072}, },
	{{-126976, -1822720, 131072}, {4096, -1822720, 131072}, {-126976, -1822720, 0}, {4096, -1822720, 0}, },
	{{-126976, -1789952, 131072}, {4096, -1789952, 131072}, {-126976, -1822720, 131072}, {4096, -1822720, 131072}, },
	{{4096, -1822720, 0}, {4096, -1822720, 131072}, {4096, -1789952, 0}, {4096, -1789952, 131072}, },
	{{4096, -1789952, 0}, {4096, -1789952, 131072}, {4096, -1822720, 0}, {4096, -1822720, 131072}, },
	{{4096, -1822720, 0}, {135168, -1822720, 0}, {4096, -1789952, 0}, {135168, -1789952, 0}, },
	{{4096, -1789952, 0}, {135168, -1789952, 0}, {4096, -1789952, 131072}, {135168, -1789952, 131072}, },
	{{4096, -1822720, 131072}, {135168, -1822720, 131072}, {4096, -1822720, 0}, {135168, -1822720, 0}, },
	{{4096, -1789952, 131072}, {135168, -1789952, 131072}, {4096, -1822720, 131072}, {135168, -1822720, 131072}, },
	{{135168, -1822720, 0}, {135168, -1822720, 131072}, {135168, -1789952, 0}, {135168, -1789952, 131072}, },
	{{-421888, -1789952, 0}, {-421888, -1789952, 131072}, {-421888, -1822720, 0}, {-421888, -1822720, 131072}, },
	{{-421888, -1822720, 0}, {-389120, -1822720, 0}, {-421888, -1789952, 0}, {-389120, -1789952, 0}, },
	{{-421888, -1789952, 0}, {-389120, -1789952, 0}, {-421888, -1789952, 131072}, {-389120, -1789952, 131072}, },
	{{-421888, -1822720, 131072}, {-389120, -1822720, 131072}, {-421888, -1822720, 0}, {-389120, -1822720, 0}, },
	{{-421888, -1789952, 131072}, {-389120, -1789952, 131072}, {-421888, -1822720, 131072}, {-389120, -1822720, 131072}, },
	{{-389120, -1822720, 0}, {-389120, -1822720, 131072}, {-389120, -1789952, 0}, {-389120, -1789952, 131072}, },
	{{-421888, -1789952, 131072}, {-389120, -1789952, 262144}, {-421888, -1822720, 131072}, {-389120, -1822720, 262144}, },
	{{-421888, -1822720, 131072}, {-389120, -1822720, 131072}, {-421888, -1789952, 131072}, {-389120, -1789952, 131072}, },
	{{-389120, -1789952, 262144}, {-389120, -1789952, 131072}, {-389120, -1822720, 262144}, {-389120, -1822720, 131072}, },
	{{-421888, -1822720, -131072}, {-389120, -1822720, -262144}, {-421888, -1789952, -131072}, {-389120, -1789952, -262144}, },
	{{-421888, -1789952, -131072}, {-389120, -1789952, -131072}, {-421888, -1822720, -131072}, {-389120, -1822720, -131072}, },
	{{-389120, -1789952, -262144}, {-389120, -1822720, -262144}, {-389120, -1789952, -131072}, {-389120, -1822720, -131072}, },
	{{-421888, -1789952, -131072}, {-421888, -1789952, 0}, {-421888, -1822720, -131072}, {-421888, -1822720, 0}, },
	{{-421888, -1822720, -131072}, {-389120, -1822720, -131072}, {-421888, -1789952, -131072}, {-389120, -1789952, -131072}, },
	{{-421888, -1789952, -131072}, {-389120, -1789952, -131072}, {-421888, -1789952, 0}, {-389120, -1789952, 0}, },
	{{-421888, -1822720, 0}, {-389120, -1822720, 0}, {-421888, -1822720, -131072}, {-389120, -1822720, -131072}, },
	{{-421888, -1789952, 0}, {-389120, -1789952, 0}, {-421888, -1822720, 0}, {-389120, -1822720, 0}, },
	{{-389120, -1822720, -131072}, {-389120, -1822720, 0}, {-389120, -1789952, -131072}, {-389120, -1789952, 0}, },
	{{-389120, -1822720, -262144}, {-258048, -1822720, -393216}, {-389120, -1789952, -262144}, {-258048, -1789952, -393216}, },
	{{-389120, -1789952, -262144}, {-258048, -1789952, -262144}, {-389120, -1822720, -262144}, {-258048, -1822720, -262144}, },
	{{-258048, -1822720, -262144}, {-258048, -1789952, -262144}, {-258048, -1822720, -393216}, {-258048, -1789952, -393216}, },
	{{-258048, -1789952, -393216}, {-258048, -1789952, -262144}, {-258048, -1822720, -393216}, {-258048, -1822720, -262144}, },
	{{-258048, -1822720, -393216}, {-126976, -1822720, -393216}, {-258048, -1789952, -393216}, {-126976, -1789952, -393216}, },
	{{-258048, -1789952, -393216}, {-126976, -1789952, -393216}, {-258048, -1789952, -262144}, {-126976, -1789952, -262144}, },
	{{-258048, -1822720, -262144}, {-126976, -1822720, -262144}, {-258048, -1822720, -393216}, {-126976, -1822720, -393216}, },
	{{-258048, -1789952, -262144}, {-126976, -1789952, -262144}, {-258048, -1822720, -262144}, {-126976, -1822720, -262144}, },
	{{-126976, -1822720, -393216}, {-126976, -1822720, -262144}, {-126976, -1789952, -393216}, {-126976, -1789952, -262144}, },
	{{-126976, -1789952, -393216}, {-126976, -1789952, -262144}, {-126976, -1822720, -393216}, {-126976, -1822720, -262144}, },
	{{-126976, -1822720, -393216}, {4096, -1822720, -393216}, {-126976, -1789952, -393216}, {4096, -1789952, -393216}, },
	{{-126976, -1789952, -393216}, {4096, -1789952, -393216}, {-126976, -1789952, -262144}, {4096, -1789952, -262144}, },
	{{-126976, -1822720, -262144}, {4096, -1822720, -262144}, {-126976, -1822720, -393216}, {4096, -1822720, -393216}, },
	{{-126976, -1789952, -262144}, {4096, -1789952, -262144}, {-126976, -1822720, -262144}, {4096, -1822720, -262144}, },
	{{4096, -1822720, -393216}, {4096, -1822720, -262144}, {4096, -1789952, -393216}, {4096, -1789952, -262144}, },
	{{4096, -1789952, -393216}, {4096, -1789952, -262144}, {4096, -1822720, -393216}, {4096, -1822720, -262144}, },
	{{4096, -1822720, -393216}, {135168, -1822720, -393216}, {4096, -1789952, -393216}, {135168, -1789952, -393216}, },
	{{4096, -1789952, -393216}, {135168, -1789952, -393216}, {4096, -1789952, -262144}, {135168, -1789952, -262144}, },
	{{4096, -1822720, -262144}, {135168, -1822720, -262144}, {4096, -1822720, -393216}, {135168, -1822720, -393216}, },
	{{4096, -1789952, -262144}, {135168, -1789952, -262144}, {4096, -1822720, -262144}, {135168, -1822720, -262144}, },
	{{135168, -1822720, -393216}, {135168, -1822720, -262144}, {135168, -1789952, -393216}, {135168, -1789952, -262144}, },
	{{135168, -1789952, -393216}, {135168, -1789952, -262144}, {135168, -1822720, -393216}, {135168, -1822720, -262144}, },
	{{135168, -1822720, -393216}, {266240, -1822720, -393216}, {135168, -1789952, -393216}, {266240, -1789952, -393216}, },
	{{135168, -1789952, -393216}, {266240, -1789952, -393216}, {135168, -1789952, -262144}, {266240, -1789952, -262144}, },
	{{135168, -1822720, -262144}, {266240, -1822720, -262144}, {135168, -1822720, -393216}, {266240, -1822720, -393216}, },
	{{135168, -1789952, -262144}, {266240, -1789952, -262144}, {135168, -1822720, -262144}, {266240, -1822720, -262144}, },
	{{266240, -1822720, -393216}, {266240, -1822720, -262144}, {266240, -1789952, -393216}, {266240, -1789952, -262144}, },
	{{266240, -1822720, -262144}, {266240, -1822720, -393216}, {266240, -1789952, -262144}, {266240, -1789952, -393216}, },
	{{266240, -1789952, -262144}, {397312, -1789952, -262144}, {266240, -1822720, -262144}, {397312, -1822720, -262144}, },
	{{266240, -1789952, -393216}, {266240, -1822720, -393216}, {397312, -1789952, -262144}, {397312, -1822720, -262144}, },
	{{397312, -1822720, -131072}, {397312, -1822720, -262144}, {397312, -1789952, -131072}, {397312, -1789952, -262144}, },
	{{397312, -1789952, -131072}, {430080, -1789952, -131072}, {397312, -1822720, -131072}, {430080, -1822720, -131072}, },
	{{397312, -1789952, -262144}, {397312, -1822720, -262144}, {430080, -1789952, -131072}, {430080, -1822720, -131072}, },
	{{397312, -1789952, 0}, {397312, -1789952, 131072}, {397312, -1822720, 0}, {397312, -1822720, 131072}, },
	{{397312, -1822720, 0}, {430080, -1822720, 0}, {397312, -1789952, 0}, {430080, -1789952, 0}, },
	{{397312, -1789952, 0}, {430080, -1789952, 0}, {397312, -1789952, 131072}, {430080, -1789952, 131072}, },
	{{397312, -1822720, 131072}, {430080, -1822720, 131072}, {397312, -1822720, 0}, {430080, -1822720, 0}, },
	{{397312, -1789952, 131072}, {430080, -1789952, 131072}, {397312, -1822720, 131072}, {430080, -1822720, 131072}, },
	{{430080, -1822720, 0}, {430080, -1822720, 131072}, {430080, -1789952, 0}, {430080, -1789952, 131072}, },
	{{397312, -1789952, 131072}, {397312, -1789952, 262144}, {397312, -1822720, 131072}, {397312, -1822720, 262144}, },
	{{397312, -1822720, 131072}, {430080, -1822720, 131072}, {397312, -1789952, 131072}, {430080, -1789952, 131072}, },
	{{397312, -1789952, 262144}, {430080, -1789952, 131072}, {397312, -1822720, 262144}, {430080, -1822720, 131072}, },
	{{397312, -1789952, -131072}, {397312, -1789952, 0}, {397312, -1822720, -131072}, {397312, -1822720, 0}, },
	{{397312, -1822720, -131072}, {430080, -1822720, -131072}, {397312, -1789952, -131072}, {430080, -1789952, -131072}, },
	{{397312, -1789952, -131072}, {430080, -1789952, -131072}, {397312, -1789952, 0}, {430080, -1789952, 0}, },
	{{397312, -1822720, 0}, {430080, -1822720, 0}, {397312, -1822720, -131072}, {430080, -1822720, -131072}, },
	{{397312, -1789952, 0}, {430080, -1789952, 0}, {397312, -1822720, 0}, {430080, -1822720, 0}, },
	{{430080, -1822720, -131072}, {430080, -1822720, 0}, {430080, -1789952, -131072}, {430080, -1789952, 0}, },
	{{-126976, -135168, 409600}, {4096, -135168, 409600}, {-126976, -135168, 540672}, {4096, -135168, 540672}, },
	{{-126976, -217088, 540672}, {4096, -217088, 540672}, {-126976, -217088, 409600}, {4096, -217088, 409600}, },
	{{-126976, -135168, 540672}, {4096, -135168, 540672}, {-126976, -217088, 540672}, {4096, -217088, 540672}, },
	{{86016, 45056, 417792}, {86016, -135168, 417792}, {81920, 45056, 409600}, {81920, -135168, 409600}, },
	{{86016, 45056, 417792}, {106496, 45056, 421888}, {86016, -135168, 417792}, {106496, -135168, 421888}, },
	{{106496, 45056, 421888}, {131072, 45056, 417792}, {106496, -135168, 421888}, {131072, -135168, 417792}, },
	{{131072, -135168, 417792}, {131072, 45056, 417792}, {135168, -135168, 409600}, {135168, 45056, 409600}, },
	{{86016, 45056, 385024}, {81920, 45056, 393216}, {86016, -86016, 385024}, {81920, -86016, 393216}, },
	{{86016, -86016, 385024}, {106496, -86016, 380928}, {86016, 45056, 385024}, {106496, 45056, 380928}, },
	{{106496, -86016, 380928}, {131072, -86016, 385024}, {106496, 45056, 380928}, {131072, 45056, 385024}, },
	{{131072, 45056, 385024}, {131072, -86016, 385024}, {135168, 45056, 393216}, {135168, -86016, 393216}, },
	{{-122880, 45056, 417792}, {-122880, -135168, 417792}, {-126976, 45056, 409600}, {-126976, -135168, 409600}, },
	{{-122880, 45056, 417792}, {-98304, 45056, 421888}, {-122880, -135168, 417792}, {-98304, -135168, 421888}, },
	{{-98304, 45056, 421888}, {-77824, 45056, 417792}, {-98304, -135168, 421888}, {-77824, -135168, 417792}, },
	{{-77824, -135168, 417792}, {-77824, 45056, 417792}, {-73728, -135168, 409600}, {-73728, 45056, 409600}, },
	{{-122880, 45056, 385024}, {-126976, 45056, 393216}, {-122880, -86016, 385024}, {-126976, -86016, 393216}, },
	{{-122880, -86016, 385024}, {-98304, -86016, 380928}, {-122880, 45056, 385024}, {-98304, 45056, 380928}, },
	{{-98304, -86016, 380928}, {-77824, -86016, 385024}, {-98304, 45056, 380928}, {-77824, 45056, 385024}, },
	{{-77824, 45056, 385024}, {-77824, -86016, 385024}, {-73728, 45056, 393216}, {-73728, -86016, 393216}, },
	{{-73728, -217088, 393216}, {81920, -217088, 393216}, {-73728, -110592, 393216}, {81920, -110592, 393216}, },
	{{-73728, -217088, 409600}, {81920, -217088, 409600}, {-73728, -217088, 393216}, {81920, -217088, 393216}, },
	{{-73728, -110592, 409600}, {81920, -110592, 409600}, {-73728, -217088, 409600}, {81920, -217088, 409600}, },
	{{-73728, 45056, 393216}, {-73728, 45056, 409600}, {-73728, -110592, 393216}, {-73728, -110592, 409600}, },
	{{-73728, -110592, 393216}, {81920, -110592, 393216}, {-73728, 45056, 393216}, {81920, 45056, 393216}, },
	{{-73728, 45056, 393216}, {81920, 45056, 393216}, {-73728, 45056, 409600}, {81920, 45056, 409600}, },
	{{-73728, -110592, 409600}, {81920, -110592, 409600}, {-73728, -110592, 393216}, {81920, -110592, 393216}, },
	{{-73728, 45056, 409600}, {81920, 45056, 409600}, {-73728, -110592, 409600}, {81920, -110592, 409600}, },
	{{81920, -110592, 393216}, {81920, -110592, 409600}, {81920, 45056, 393216}, {81920, 45056, 409600}, },
	{{4096, -135168, 409600}, {135168, -135168, 409600}, {4096, -135168, 540672}, {135168, -135168, 540672}, },
	{{4096, -217088, 540672}, {135168, -217088, 540672}, {4096, -217088, 409600}, {135168, -217088, 409600}, },
	{{4096, -135168, 540672}, {135168, -135168, 540672}, {4096, -217088, 540672}, {135168, -217088, 540672}, },
	{{-126976, -135168, 540672}, {-61440, -135168, 540672}, {-126976, -135168, 671744}, {-61440, -135168, 671744}, },
	{{-126976, -217088, 671744}, {-61440, -217088, 671744}, {-126976, -217088, 540672}, {-61440, -217088, 540672}, },
	{{-61440, -217088, 540672}, {-61440, -217088, 671744}, {-61440, -135168, 540672}, {-61440, -135168, 671744}, },
	{{69632, -135168, 540672}, {69632, -135168, 671744}, {69632, -217088, 540672}, {69632, -217088, 671744}, },
	{{69632, -135168, 540672}, {135168, -135168, 540672}, {69632, -135168, 671744}, {135168, -135168, 671744}, },
	{{69632, -217088, 671744}, {135168, -217088, 671744}, {69632, -217088, 540672}, {135168, -217088, 540672}, },
	{{69632, -135168, 868352}, {135168, -135168, 868352}, {69632, -135168, 933888}, {135168, -135168, 933888}, },
	{{69632, -217088, 933888}, {135168, -217088, 933888}, {69632, -217088, 868352}, {135168, -217088, 868352}, },
	{{69632, -217088, 671744}, {135168, -217088, 671744}, {69632, -135168, 671744}, {135168, -135168, 671744}, },
	{{69632, -135168, 671744}, {135168, -135168, 671744}, {69632, -135168, 737280}, {135168, -135168, 737280}, },
	{{69632, -217088, 737280}, {135168, -217088, 737280}, {69632, -217088, 671744}, {135168, -217088, 671744}, },
	{{-126976, -217088, 671744}, {-61440, -217088, 671744}, {-126976, -135168, 671744}, {-61440, -135168, 671744}, },
	{{-126976, -135168, 671744}, {-61440, -135168, 671744}, {-126976, -135168, 802816}, {-61440, -135168, 802816}, },
	{{-126976, -217088, 802816}, {-61440, -217088, 802816}, {-126976, -217088, 671744}, {-61440, -217088, 671744}, },
	{{-126976, -135168, 802816}, {-61440, -135168, 802816}, {-126976, -135168, 933888}, {-61440, -135168, 933888}, },
	{{-126976, -217088, 933888}, {-61440, -217088, 933888}, {-126976, -217088, 802816}, {-61440, -217088, 802816}, },
	{{-126976, -348160, 409600}, {-126976, -348160, 540672}, {-126976, -217088, 409600}, {-126976, -217088, 540672}, },
	{{-126976, -348160, 540672}, {-126976, -348160, 671744}, {-126976, -217088, 540672}, {-126976, -217088, 671744}, },
	{{-126976, -479232, 409600}, {-126976, -479232, 540672}, {-126976, -348160, 409600}, {-126976, -348160, 540672}, },
	{{-126976, -479232, 540672}, {-126976, -479232, 671744}, {-126976, -348160, 540672}, {-126976, -348160, 671744}, },
	{{-126976, -479232, 671744}, {-126976, -479232, 802816}, {-126976, -348160, 671744}, {-126976, -348160, 802816}, },
	{{-126976, -479232, 802816}, {-126976, -479232, 933888}, {-126976, -348160, 802816}, {-126976, -348160, 933888}, },
	{{-126976, -348160, 671744}, {-126976, -348160, 802816}, {-126976, -217088, 671744}, {-126976, -217088, 802816}, },
	{{-126976, -348160, 802816}, {-126976, -348160, 933888}, {-126976, -217088, 802816}, {-126976, -217088, 933888}, },
	{{135168, -217088, 409600}, {135168, -217088, 540672}, {135168, -348160, 409600}, {135168, -348160, 540672}, },
	{{135168, -348160, 409600}, {135168, -348160, 540672}, {135168, -479232, 409600}, {135168, -479232, 540672}, },
	{{135168, -348160, 540672}, {135168, -348160, 671744}, {135168, -479232, 540672}, {135168, -479232, 671744}, },
	{{135168, -217088, 540672}, {135168, -217088, 671744}, {135168, -348160, 540672}, {135168, -348160, 671744}, },
	{{135168, -217088, 671744}, {135168, -217088, 802816}, {135168, -348160, 671744}, {135168, -348160, 802816}, },
	{{135168, -348160, 671744}, {135168, -348160, 802816}, {135168, -479232, 671744}, {135168, -479232, 802816}, },
	{{135168, -348160, 802816}, {135168, -348160, 933888}, {135168, -479232, 802816}, {135168, -479232, 933888}, },
	{{135168, -217088, 802816}, {135168, -217088, 933888}, {135168, -348160, 802816}, {135168, -348160, 933888}, },
	{{4096, -479232, 409600}, {135168, -479232, 409600}, {4096, -479232, 540672}, {135168, -479232, 540672}, },
	{{-126976, -479232, 409600}, {4096, -479232, 409600}, {-126976, -479232, 540672}, {4096, -479232, 540672}, },
	{{-126976, -479232, 540672}, {4096, -479232, 540672}, {-126976, -479232, 671744}, {4096, -479232, 671744}, },
	{{4096, -479232, 540672}, {135168, -479232, 540672}, {4096, -479232, 671744}, {135168, -479232, 671744}, },
	{{-126976, -479232, 802816}, {4096, -479232, 802816}, {-126976, -479232, 933888}, {4096, -479232, 933888}, },
	{{4096, -479232, 802816}, {135168, -479232, 802816}, {4096, -479232, 933888}, {135168, -479232, 933888}, },
	{{4096, -479232, 671744}, {135168, -479232, 671744}, {4096, -479232, 802816}, {135168, -479232, 802816}, },
	{{-126976, -479232, 671744}, {4096, -479232, 671744}, {-126976, -479232, 802816}, {4096, -479232, 802816}, },
	{{135168, -348160, 393216}, {135168, -348160, 409600}, {135168, -479232, 393216}, {135168, -479232, 409600}, },
	{{135168, -217088, 393216}, {135168, -217088, 409600}, {135168, -348160, 393216}, {135168, -348160, 409600}, },
	{{81920, -217088, 409600}, {135168, -217088, 409600}, {81920, -217088, 393216}, {135168, -217088, 393216}, },
	{{-126976, -217088, 409600}, {-73728, -217088, 409600}, {-126976, -217088, 393216}, {-73728, -217088, 393216}, },
	{{-126976, -348160, 393216}, {-126976, -348160, 409600}, {-126976, -217088, 393216}, {-126976, -217088, 409600}, },
	{{-126976, -479232, 393216}, {-126976, -479232, 409600}, {-126976, -348160, 393216}, {-126976, -348160, 409600}, },
	{{-122880, -217088, 925696}, {-126976, -217088, 933888}, {-122880, -380928, 925696}, {-126976, -380928, 933888}, },
	{{-122880, -380928, 925696}, {-98304, -380928, 921600}, {-122880, -217088, 925696}, {-98304, -217088, 921600}, },
	{{-98304, -380928, 921600}, {-77824, -380928, 925696}, {-98304, -217088, 921600}, {-77824, -217088, 925696}, },
	{{-77824, -217088, 925696}, {-77824, -380928, 925696}, {-73728, -217088, 933888}, {-73728, -380928, 933888}, },
	{{86016, -217088, 925696}, {81920, -217088, 933888}, {86016, -380928, 925696}, {81920, -380928, 933888}, },
	{{86016, -380928, 925696}, {106496, -380928, 921600}, {86016, -217088, 925696}, {106496, -217088, 921600}, },
	{{106496, -380928, 921600}, {131072, -380928, 925696}, {106496, -217088, 921600}, {131072, -217088, 925696}, },
	{{131072, -217088, 925696}, {131072, -380928, 925696}, {135168, -217088, 933888}, {135168, -380928, 933888}, },
	{{-73728, -372736, 933888}, {81920, -372736, 933888}, {-73728, -217088, 933888}, {81920, -217088, 933888}, },
	{{-73728, -479232, 933888}, {81920, -479232, 933888}, {-73728, -372736, 933888}, {81920, -372736, 933888}, },
	{{-122880, -86016, 385024}, {-126976, -86016, 393216}, {-122880, -217088, 385024}, {-126976, -217088, 393216}, },
	{{-122880, -217088, 385024}, {-98304, -217088, 380928}, {-122880, -86016, 385024}, {-98304, -86016, 380928}, },
	{{-98304, -217088, 380928}, {-77824, -217088, 385024}, {-98304, -86016, 380928}, {-77824, -86016, 385024}, },
	{{-77824, -86016, 385024}, {-77824, -217088, 385024}, {-73728, -86016, 393216}, {-73728, -217088, 393216}, },
	{{86016, -86016, 385024}, {81920, -86016, 393216}, {86016, -217088, 385024}, {81920, -217088, 393216}, },
	{{86016, -217088, 385024}, {106496, -217088, 380928}, {86016, -86016, 385024}, {106496, -86016, 380928}, },
	{{106496, -217088, 380928}, {131072, -217088, 385024}, {106496, -86016, 380928}, {131072, -86016, 385024}, },
	{{131072, -86016, 385024}, {131072, -217088, 385024}, {135168, -86016, 393216}, {135168, -217088, 393216}, },
	{{-122880, -380928, 925696}, {-126976, -380928, 933888}, {-122880, -479232, 925696}, {-126976, -479232, 933888}, },
	{{-122880, -479232, 925696}, {-98304, -479232, 921600}, {-122880, -380928, 925696}, {-98304, -380928, 921600}, },
	{{-98304, -479232, 921600}, {-77824, -479232, 925696}, {-98304, -380928, 921600}, {-77824, -380928, 925696}, },
	{{-77824, -380928, 925696}, {-77824, -479232, 925696}, {-73728, -380928, 933888}, {-73728, -479232, 933888}, },
	{{86016, -380928, 925696}, {81920, -380928, 933888}, {86016, -479232, 925696}, {81920, -479232, 933888}, },
	{{86016, -479232, 925696}, {106496, -479232, 921600}, {86016, -380928, 925696}, {106496, -380928, 921600}, },
	{{106496, -479232, 921600}, {131072, -479232, 925696}, {106496, -380928, 921600}, {131072, -380928, 925696}, },
	{{131072, -380928, 925696}, {131072, -479232, 925696}, {135168, -380928, 933888}, {135168, -479232, 933888}, },
	{{135168, -4096, 409600}, {135168, -4096, 540672}, {135168, -135168, 409600}, {135168, -135168, 540672}, },
	{{135168, -4096, 540672}, {135168, -4096, 671744}, {135168, -135168, 540672}, {135168, -135168, 671744}, },
	{{135168, -4096, 671744}, {151552, -4096, 671744}, {135168, -135168, 671744}, {151552, -135168, 671744}, },
	{{-110592, -135168, 409600}, {-110592, -135168, 540672}, {-110592, -4096, 409600}, {-110592, -4096, 540672}, },
	{{-110592, -135168, 540672}, {-110592, -135168, 671744}, {-110592, -4096, 540672}, {-110592, -4096, 671744}, },
	{{-110592, -135168, 671744}, {-110592, -135168, 802816}, {-110592, -4096, 671744}, {-110592, -4096, 802816}, },
	{{-110592, -135168, 802816}, {-110592, -135168, 933888}, {-110592, -4096, 802816}, {-110592, -4096, 933888}, },
	{{659456, -4096, 671744}, {659456, -4096, 802816}, {659456, -135168, 671744}, {659456, -135168, 802816}, },
	{{659456, -4096, 802816}, {659456, -4096, 933888}, {659456, -135168, 802816}, {659456, -135168, 933888}, },
	{{659456, -4096, 933888}, {659456, -4096, 1064960}, {659456, -135168, 933888}, {659456, -135168, 1064960}, },
	{{659456, -4096, 1064960}, {659456, -4096, 1196032}, {659456, -135168, 1064960}, {659456, -135168, 1196032}, },
	{{659456, -4096, 1196032}, {659456, -4096, 1327104}, {659456, -135168, 1196032}, {659456, -135168, 1327104}, },
	{{659456, -4096, 1327104}, {659456, -4096, 1458176}, {659456, -135168, 1327104}, {659456, -135168, 1458176}, },
	{{659456, -4096, 1458176}, {659456, -4096, 1589248}, {659456, -135168, 1458176}, {659456, -135168, 1589248}, },
	{{659456, -4096, 1589248}, {659456, -4096, 1720320}, {659456, -135168, 1589248}, {659456, -135168, 1720320}, },
	{{135168, -4096, 1720320}, {135168, -4096, 1851392}, {135168, -135168, 1720320}, {135168, -135168, 1851392}, },
	{{135168, -135168, 1720320}, {151552, -135168, 1720320}, {135168, -4096, 1720320}, {151552, -4096, 1720320}, },
	{{135168, -4096, 1851392}, {135168, -4096, 1982464}, {135168, -135168, 1851392}, {135168, -135168, 1982464}, },
	{{-126976, -135168, 1458176}, {-126976, -135168, 1589248}, {-126976, -4096, 1458176}, {-126976, -4096, 1589248}, },
	{{-126976, -135168, 1589248}, {-126976, -135168, 1720320}, {-126976, -4096, 1589248}, {-126976, -4096, 1720320}, },
	{{-126976, -135168, 1720320}, {-126976, -135168, 1851392}, {-126976, -4096, 1720320}, {-126976, -4096, 1851392}, },
	{{-126976, -135168, 1851392}, {-126976, -135168, 1982464}, {-126976, -4096, 1851392}, {-126976, -4096, 1982464}, },
	{{380928, -135168, 933888}, {397312, -135168, 933888}, {380928, -4096, 933888}, {397312, -4096, 933888}, },
	{{397312, -135168, 933888}, {397312, -135168, 1064960}, {397312, -4096, 933888}, {397312, -4096, 1064960}, },
	{{397312, -135168, 1064960}, {397312, -135168, 1196032}, {397312, -4096, 1064960}, {397312, -4096, 1196032}, },
	{{397312, -135168, 1196032}, {397312, -135168, 1327104}, {397312, -4096, 1196032}, {397312, -4096, 1327104}, },
	{{380928, -4096, 1458176}, {397312, -4096, 1458176}, {380928, -135168, 1458176}, {397312, -135168, 1458176}, },
	{{397312, -135168, 1327104}, {397312, -135168, 1458176}, {397312, -4096, 1327104}, {397312, -4096, 1458176}, },
	{{528384, -4096, 671744}, {659456, -4096, 671744}, {528384, -135168, 671744}, {659456, -135168, 671744}, },
	{{397312, -4096, 671744}, {528384, -4096, 671744}, {397312, -135168, 671744}, {528384, -135168, 671744}, },
	{{266240, -4096, 671744}, {397312, -4096, 671744}, {266240, -135168, 671744}, {397312, -135168, 671744}, },
	{{151552, -4096, 671744}, {266240, -4096, 671744}, {151552, -135168, 671744}, {266240, -135168, 671744}, },
	{{-110592, -135168, 933888}, {20480, -135168, 933888}, {-110592, -4096, 933888}, {20480, -4096, 933888}, },
	{{20480, -135168, 933888}, {151552, -135168, 933888}, {20480, -4096, 933888}, {151552, -4096, 933888}, },
	{{151552, -135168, 933888}, {282624, -135168, 933888}, {151552, -4096, 933888}, {282624, -4096, 933888}, },
	{{282624, -135168, 933888}, {380928, -135168, 933888}, {282624, -4096, 933888}, {380928, -4096, 933888}, },
	{{151552, -135168, 1720320}, {266240, -135168, 1720320}, {151552, -4096, 1720320}, {266240, -4096, 1720320}, },
	{{266240, -135168, 1720320}, {397312, -135168, 1720320}, {266240, -4096, 1720320}, {397312, -4096, 1720320}, },
	{{397312, -135168, 1720320}, {528384, -135168, 1720320}, {397312, -4096, 1720320}, {528384, -4096, 1720320}, },
	{{528384, -135168, 1720320}, {659456, -135168, 1720320}, {528384, -4096, 1720320}, {659456, -4096, 1720320}, },
	{{266240, -4096, 1458176}, {380928, -4096, 1458176}, {266240, -135168, 1458176}, {380928, -135168, 1458176}, },
	{{135168, -4096, 1458176}, {266240, -4096, 1458176}, {135168, -135168, 1458176}, {266240, -135168, 1458176}, },
	{{4096, -4096, 1458176}, {135168, -4096, 1458176}, {4096, -135168, 1458176}, {135168, -135168, 1458176}, },
	{{-126976, -4096, 1458176}, {4096, -4096, 1458176}, {-126976, -135168, 1458176}, {4096, -135168, 1458176}, },
	{{69632, -135168, 1916928}, {135168, -135168, 1916928}, {69632, -135168, 1982464}, {135168, -135168, 1982464}, },
	{{-122880, 45056, 1974272}, {-126976, 45056, 1982464}, {-122880, -135168, 1974272}, {-126976, -135168, 1982464}, },
	{{-122880, -135168, 1974272}, {-98304, -135168, 1970176}, {-122880, 45056, 1974272}, {-98304, 45056, 1970176}, },
	{{-98304, -135168, 1970176}, {-77824, -135168, 1974272}, {-98304, 45056, 1970176}, {-77824, 45056, 1974272}, },
	{{-77824, 45056, 1974272}, {-77824, -135168, 1974272}, {-73728, 45056, 1982464}, {-73728, -135168, 1982464}, },
	{{-73728, -151552, 1982464}, {81920, -151552, 1982464}, {-73728, -110592, 1982464}, {81920, -110592, 1982464}, },
	{{86016, 45056, 1974272}, {81920, 45056, 1982464}, {86016, -135168, 1974272}, {81920, -135168, 1982464}, },
	{{86016, -135168, 1974272}, {106496, -135168, 1970176}, {86016, 45056, 1974272}, {106496, 45056, 1970176}, },
	{{106496, -135168, 1970176}, {131072, -135168, 1974272}, {106496, 45056, 1970176}, {131072, 45056, 1974272}, },
	{{131072, 45056, 1974272}, {131072, -135168, 1974272}, {135168, 45056, 1982464}, {135168, -135168, 1982464}, },
	{{-73728, -110592, 1982464}, {81920, -110592, 1982464}, {-73728, 45056, 1982464}, {81920, 45056, 1982464}, },
	{{-110592, -4096, 409600}, {-110592, -4096, 540672}, {-61440, 45056, 409600}, {-61440, 45056, 540672}, },
	{{-110592, -4096, 540672}, {-110592, -4096, 671744}, {-61440, 45056, 540672}, {-61440, 45056, 671744}, },
	{{-110592, -4096, 671744}, {-110592, -4096, 802816}, {-61440, 45056, 671744}, {-61440, 45056, 802816}, },
	{{-110592, -4096, 802816}, {-110592, -4096, 933888}, {-61440, 45056, 802816}, {-61440, 45056, 884736}, },
	{{397312, -4096, 933888}, {397312, -4096, 1064960}, {446464, 45056, 933888}, {446464, 45056, 1064960}, },
	{{397312, -4096, 1064960}, {397312, -4096, 1196032}, {446464, 45056, 1064960}, {446464, 45056, 1196032}, },
	{{397312, -4096, 1196032}, {397312, -4096, 1327104}, {446464, 45056, 1196032}, {446464, 45056, 1327104}, },
	{{397312, -4096, 1327104}, {397312, -4096, 1458176}, {446464, 45056, 1327104}, {446464, 45056, 1458176}, },
	{{-77824, 45056, 1589248}, {-77824, 45056, 1507328}, {-126976, -4096, 1589248}, {-126976, -4096, 1458176}, },
	{{-126976, -4096, 1589248}, {-126976, -4096, 1720320}, {-77824, 45056, 1589248}, {-77824, 45056, 1720320}, },
	{{-126976, -4096, 1720320}, {-126976, -4096, 1851392}, {-77824, 45056, 1720320}, {-77824, 45056, 1851392}, },
	{{-126976, -4096, 1851392}, {-126976, -4096, 1982464}, {-77824, 45056, 1851392}, {-77824, 45056, 1982464}, },
	{{86016, 45056, 1851392}, {135168, -4096, 1851392}, {86016, 45056, 1720320}, {135168, -4096, 1720320}, },
	{{86016, 45056, 1982464}, {135168, -4096, 1982464}, {86016, 45056, 1851392}, {135168, -4096, 1851392}, },
	{{610304, 45056, 1589248}, {659456, -4096, 1589248}, {610304, 45056, 1458176}, {659456, -4096, 1458176}, },
	{{610304, 45056, 1671168}, {659456, -4096, 1720320}, {610304, 45056, 1589248}, {659456, -4096, 1589248}, },
	{{610304, 45056, 1064960}, {659456, -4096, 1064960}, {610304, 45056, 933888}, {659456, -4096, 933888}, },
	{{610304, 45056, 1196032}, {659456, -4096, 1196032}, {610304, 45056, 1064960}, {659456, -4096, 1064960}, },
	{{610304, 45056, 1327104}, {659456, -4096, 1327104}, {610304, 45056, 1196032}, {659456, -4096, 1196032}, },
	{{610304, 45056, 1458176}, {659456, -4096, 1458176}, {610304, 45056, 1327104}, {659456, -4096, 1327104}, },
	{{610304, 45056, 933888}, {659456, -4096, 933888}, {610304, 45056, 802816}, {659456, -4096, 802816}, },
	{{4096, -4096, 933888}, {135168, -4096, 933888}, {4096, 45056, 884736}, {135168, 45056, 884736}, },
	{{266240, -4096, 933888}, {397312, -4096, 933888}, {266240, 45056, 884736}, {397312, 45056, 884736}, },
	{{135168, -4096, 933888}, {266240, -4096, 933888}, {135168, 45056, 884736}, {266240, 45056, 884736}, },
	{{528384, -4096, 1720320}, {659456, -4096, 1720320}, {528384, 45056, 1671168}, {610304, 45056, 1671168}, },
	{{397312, -4096, 1720320}, {528384, -4096, 1720320}, {397312, 45056, 1671168}, {528384, 45056, 1671168}, },
	{{266240, -4096, 1720320}, {397312, -4096, 1720320}, {266240, 45056, 1671168}, {397312, 45056, 1671168}, },
	{{135168, -4096, 1720320}, {266240, -4096, 1720320}, {135168, 45056, 1671168}, {266240, 45056, 1671168}, },
	{{86016, 45056, 671744}, {135168, -4096, 671744}, {86016, 45056, 540672}, {135168, -4096, 540672}, },
	{{86016, 45056, 540672}, {135168, -4096, 540672}, {86016, 45056, 409600}, {135168, -4096, 409600}, },
	{{397312, 45056, 720896}, {528384, 45056, 720896}, {397312, -4096, 671744}, {528384, -4096, 671744}, },
	{{135168, 45056, 720896}, {266240, 45056, 720896}, {135168, -4096, 671744}, {266240, -4096, 671744}, },
	{{266240, 45056, 720896}, {397312, 45056, 720896}, {266240, -4096, 671744}, {397312, -4096, 671744}, },
	{{135168, 45056, 1507328}, {266240, 45056, 1507328}, {135168, -4096, 1458176}, {266240, -4096, 1458176}, },
	{{266240, 45056, 1507328}, {397312, 45056, 1507328}, {266240, -4096, 1458176}, {397312, -4096, 1458176}, },
	{{-77824, 45056, 1507328}, {4096, 45056, 1507328}, {-126976, -4096, 1458176}, {4096, -4096, 1458176}, },
	{{4096, 45056, 1507328}, {135168, 45056, 1507328}, {4096, -4096, 1458176}, {135168, -4096, 1458176}, },
	{{389120, -4096, 1449984}, {389120, -4096, 1466368}, {389120, -135168, 1449984}, {389120, -135168, 1466368}, },
	{{389120, -135168, 1449984}, {405504, -135168, 1449984}, {389120, -4096, 1449984}, {405504, -4096, 1449984}, },
	{{389120, -4096, 1449984}, {405504, -4096, 1449984}, {389120, -4096, 1466368}, {405504, -4096, 1466368}, },
	{{389120, -135168, 1466368}, {405504, -135168, 1466368}, {389120, -135168, 1449984}, {405504, -135168, 1449984}, },
	{{389120, -4096, 1466368}, {405504, -4096, 1466368}, {389120, -135168, 1466368}, {405504, -135168, 1466368}, },
	{{405504, -135168, 1449984}, {405504, -135168, 1466368}, {405504, -4096, 1449984}, {405504, -4096, 1466368}, },
	{{389120, 45056, 1449984}, {389120, 45056, 1515520}, {389120, -4096, 1449984}, {389120, -4096, 1466368}, },
	{{389120, -4096, 1449984}, {405504, -4096, 1449984}, {389120, 45056, 1449984}, {454656, 45056, 1449984}, },
	{{389120, 45056, 1449984}, {454656, 45056, 1449984}, {389120, 45056, 1515520}, {454656, 45056, 1515520}, },
	{{389120, -4096, 1466368}, {405504, -4096, 1466368}, {389120, -4096, 1449984}, {405504, -4096, 1449984}, },
	{{389120, 45056, 1515520}, {454656, 45056, 1515520}, {389120, -4096, 1466368}, {405504, -4096, 1466368}, },
	{{405504, -4096, 1449984}, {405504, -4096, 1466368}, {454656, 45056, 1449984}, {454656, 45056, 1515520}, },
	{{389120, 45056, 876544}, {389120, 45056, 942080}, {389120, -4096, 925696}, {389120, -4096, 942080}, },
	{{389120, -4096, 925696}, {405504, -4096, 925696}, {389120, 45056, 876544}, {454656, 45056, 876544}, },
	{{389120, 45056, 876544}, {454656, 45056, 876544}, {389120, 45056, 942080}, {454656, 45056, 942080}, },
	{{389120, 45056, 942080}, {454656, 45056, 942080}, {389120, -4096, 942080}, {405504, -4096, 942080}, },
	{{405504, -4096, 925696}, {405504, -4096, 942080}, {454656, 45056, 876544}, {454656, 45056, 942080}, },
	{{389120, -4096, 925696}, {389120, -4096, 942080}, {389120, -135168, 925696}, {389120, -135168, 942080}, },
	{{389120, -135168, 925696}, {405504, -135168, 925696}, {389120, -4096, 925696}, {405504, -4096, 925696}, },
	{{389120, -4096, 942080}, {405504, -4096, 942080}, {389120, -135168, 942080}, {405504, -135168, 942080}, },
	{{405504, -135168, 925696}, {405504, -135168, 942080}, {405504, -4096, 925696}, {405504, -4096, 942080}, },
	{{77824, 45056, 663552}, {77824, 45056, 729088}, {126976, -4096, 663552}, {126976, -4096, 679936}, },
	{{126976, -4096, 663552}, {143360, -4096, 663552}, {77824, 45056, 663552}, {143360, 45056, 663552}, },
	{{77824, 45056, 663552}, {143360, 45056, 663552}, {77824, 45056, 729088}, {143360, 45056, 729088}, },
	{{126976, -4096, 679936}, {143360, -4096, 679936}, {126976, -4096, 663552}, {143360, -4096, 663552}, },
	{{77824, 45056, 729088}, {143360, 45056, 729088}, {126976, -4096, 679936}, {143360, -4096, 679936}, },
	{{143360, -4096, 663552}, {143360, -4096, 679936}, {143360, 45056, 663552}, {143360, 45056, 729088}, },
	{{77824, 45056, 1662976}, {77824, 45056, 1728512}, {126976, -4096, 1712128}, {126976, -4096, 1728512}, },
	{{126976, -4096, 1712128}, {143360, -4096, 1712128}, {77824, 45056, 1662976}, {143360, 45056, 1662976}, },
	{{77824, 45056, 1662976}, {143360, 45056, 1662976}, {77824, 45056, 1728512}, {143360, 45056, 1728512}, },
	{{126976, -4096, 1728512}, {143360, -4096, 1728512}, {126976, -4096, 1712128}, {143360, -4096, 1712128}, },
	{{77824, 45056, 1728512}, {143360, 45056, 1728512}, {126976, -4096, 1728512}, {143360, -4096, 1728512}, },
	{{143360, -4096, 1712128}, {143360, -4096, 1728512}, {143360, 45056, 1662976}, {143360, 45056, 1728512}, },
	{{528384, 45056, 720896}, {610304, 45056, 720896}, {528384, -4096, 671744}, {659456, -4096, 671744}, },
	{{610304, 45056, 802816}, {659456, -4096, 802816}, {610304, 45056, 720896}, {659456, -4096, 671744}, },
	{{-61440, -118784, 737280}, {-61440, -118784, 868352}, {-61440, -135168, 737280}, {-61440, -135168, 868352}, },
	{{-61440, -118784, 737280}, {69632, -118784, 737280}, {-61440, -118784, 868352}, {69632, -118784, 868352}, },
	{{-61440, -118784, 868352}, {69632, -118784, 868352}, {-61440, -135168, 868352}, {69632, -135168, 868352}, },
	{{200704, -135168, 737280}, {331776, -135168, 737280}, {200704, -118784, 737280}, {331776, -118784, 737280}, },
	{{200704, -118784, 737280}, {331776, -118784, 737280}, {200704, -118784, 868352}, {331776, -118784, 868352}, },
	{{200704, -118784, 868352}, {331776, -118784, 868352}, {200704, -135168, 868352}, {331776, -135168, 868352}, },
	{{397312, -135168, 737280}, {462848, -135168, 737280}, {397312, -118784, 737280}, {462848, -118784, 737280}, },
	{{397312, -118784, 737280}, {462848, -118784, 737280}, {397312, -118784, 868352}, {462848, -118784, 868352}, },
	{{397312, -118784, 868352}, {462848, -118784, 868352}, {397312, -135168, 868352}, {462848, -135168, 868352}, },
	{{462848, -135168, 737280}, {593920, -135168, 737280}, {462848, -118784, 737280}, {593920, -118784, 737280}, },
	{{462848, -118784, 737280}, {593920, -118784, 737280}, {462848, -118784, 868352}, {593920, -118784, 868352}, },
	{{593920, -135168, 737280}, {593920, -135168, 868352}, {593920, -118784, 737280}, {593920, -118784, 868352}, },
	{{462848, -118784, 933888}, {462848, -118784, 999424}, {462848, -135168, 933888}, {462848, -135168, 999424}, },
	{{462848, -118784, 933888}, {593920, -118784, 933888}, {462848, -118784, 999424}, {593920, -118784, 999424}, },
	{{593920, -135168, 933888}, {593920, -135168, 999424}, {593920, -118784, 933888}, {593920, -118784, 999424}, },
	{{462848, -118784, 999424}, {462848, -118784, 1130496}, {462848, -135168, 999424}, {462848, -135168, 1130496}, },
	{{462848, -118784, 999424}, {593920, -118784, 999424}, {462848, -118784, 1130496}, {593920, -118784, 1130496}, },
	{{593920, -135168, 999424}, {593920, -135168, 1130496}, {593920, -118784, 999424}, {593920, -118784, 1130496}, },
	{{462848, -118784, 1130496}, {462848, -118784, 1261568}, {462848, -135168, 1130496}, {462848, -135168, 1261568}, },
	{{462848, -118784, 1130496}, {593920, -118784, 1130496}, {462848, -118784, 1261568}, {593920, -118784, 1261568}, },
	{{593920, -135168, 1130496}, {593920, -135168, 1261568}, {593920, -118784, 1130496}, {593920, -118784, 1261568}, },
	{{462848, -118784, 1261568}, {462848, -118784, 1392640}, {462848, -135168, 1261568}, {462848, -135168, 1392640}, },
	{{462848, -118784, 1261568}, {593920, -118784, 1261568}, {462848, -118784, 1392640}, {593920, -118784, 1392640}, },
	{{593920, -135168, 1261568}, {593920, -135168, 1392640}, {593920, -118784, 1261568}, {593920, -118784, 1392640}, },
	{{462848, -118784, 1458176}, {462848, -118784, 1523712}, {462848, -135168, 1458176}, {462848, -135168, 1523712}, },
	{{462848, -118784, 1458176}, {593920, -118784, 1458176}, {462848, -118784, 1523712}, {593920, -118784, 1523712}, },
	{{593920, -135168, 1458176}, {593920, -135168, 1523712}, {593920, -118784, 1458176}, {593920, -118784, 1523712}, },
	{{462848, -118784, 1523712}, {593920, -118784, 1523712}, {462848, -118784, 1654784}, {593920, -118784, 1654784}, },
	{{462848, -118784, 1654784}, {593920, -118784, 1654784}, {462848, -135168, 1654784}, {593920, -135168, 1654784}, },
	{{593920, -135168, 1523712}, {593920, -135168, 1654784}, {593920, -118784, 1523712}, {593920, -118784, 1654784}, },
	{{331776, -135168, 1523712}, {397312, -135168, 1523712}, {331776, -118784, 1523712}, {397312, -118784, 1523712}, },
	{{331776, -118784, 1523712}, {397312, -118784, 1523712}, {331776, -118784, 1654784}, {397312, -118784, 1654784}, },
	{{331776, -118784, 1654784}, {397312, -118784, 1654784}, {331776, -135168, 1654784}, {397312, -135168, 1654784}, },
	{{200704, -135168, 1523712}, {331776, -135168, 1523712}, {200704, -118784, 1523712}, {331776, -118784, 1523712}, },
	{{200704, -118784, 1523712}, {331776, -118784, 1523712}, {200704, -118784, 1654784}, {331776, -118784, 1654784}, },
	{{200704, -118784, 1654784}, {331776, -118784, 1654784}, {200704, -135168, 1654784}, {331776, -135168, 1654784}, },
	{{135168, -135168, 1523712}, {200704, -135168, 1523712}, {135168, -118784, 1523712}, {200704, -118784, 1523712}, },
	{{135168, -118784, 1523712}, {200704, -118784, 1523712}, {135168, -118784, 1654784}, {200704, -118784, 1654784}, },
	{{135168, -118784, 1654784}, {200704, -118784, 1654784}, {135168, -135168, 1654784}, {200704, -135168, 1654784}, },
	{{-61440, -118784, 1654784}, {-61440, -118784, 1720320}, {-61440, -135168, 1654784}, {-61440, -135168, 1720320}, },
	{{-61440, -118784, 1654784}, {69632, -118784, 1654784}, {-61440, -118784, 1720320}, {69632, -118784, 1720320}, },
	{{69632, -135168, 1654784}, {69632, -135168, 1720320}, {69632, -118784, 1654784}, {69632, -118784, 1720320}, },
	{{-61440, -118784, 1785856}, {-61440, -118784, 1916928}, {-61440, -135168, 1785856}, {-61440, -135168, 1916928}, },
	{{-61440, -118784, 1785856}, {69632, -118784, 1785856}, {-61440, -118784, 1916928}, {69632, -118784, 1916928}, },
	{{-61440, -118784, 1916928}, {69632, -118784, 1916928}, {-61440, -135168, 1916928}, {69632, -135168, 1916928}, },
	{{69632, -135168, 1785856}, {69632, -135168, 1916928}, {69632, -118784, 1785856}, {69632, -118784, 1916928}, },
	{{-61440, -135168, 671744}, {69632, -135168, 671744}, {-61440, -118784, 737280}, {69632, -118784, 737280}, },
	{{-110592, -4096, 933888}, {4096, -4096, 933888}, {-61440, 45056, 884736}, {4096, 45056, 884736}, },
	{{77824, 45056, 884736}, {135168, 45056, 884736}, {77824, 45056, 802816}, {135168, 45056, 802816}, },
	{{77824, 45056, 802816}, {135168, 45056, 802816}, {77824, 45056, 729088}, {135168, 45056, 729088}, },
	{{4096, 45056, 802816}, {77824, 45056, 802816}, {4096, 45056, 729088}, {77824, 45056, 729088}, },
	{{-61440, 45056, 802816}, {4096, 45056, 802816}, {-61440, 45056, 729088}, {4096, 45056, 729088}, },
	{{397312, 45056, 802816}, {454656, 45056, 802816}, {397312, 45056, 720896}, {454656, 45056, 720896}, },
	{{397312, 45056, 876544}, {454656, 45056, 876544}, {397312, 45056, 802816}, {454656, 45056, 802816}, },
	{{454656, 45056, 933888}, {528384, 45056, 933888}, {454656, 45056, 876544}, {528384, 45056, 876544}, },
	{{454656, 45056, 876544}, {528384, 45056, 876544}, {454656, 45056, 802816}, {528384, 45056, 802816}, },
	{{454656, 45056, 802816}, {528384, 45056, 802816}, {454656, 45056, 720896}, {528384, 45056, 720896}, },
	{{528384, 45056, 802816}, {610304, 45056, 802816}, {528384, 45056, 720896}, {610304, 45056, 720896}, },
	{{528384, 45056, 876544}, {610304, 45056, 876544}, {528384, 45056, 802816}, {610304, 45056, 802816}, },
	{{528384, 45056, 933888}, {610304, 45056, 933888}, {528384, 45056, 876544}, {610304, 45056, 876544}, },
	{{528384, 45056, 1515520}, {610304, 45056, 1515520}, {528384, 45056, 1458176}, {610304, 45056, 1458176}, },
	{{454656, 45056, 1515520}, {528384, 45056, 1515520}, {454656, 45056, 1458176}, {528384, 45056, 1458176}, },
	{{454656, 45056, 1589248}, {528384, 45056, 1589248}, {454656, 45056, 1515520}, {528384, 45056, 1515520}, },
	{{528384, 45056, 1589248}, {610304, 45056, 1589248}, {528384, 45056, 1515520}, {610304, 45056, 1515520}, },
	{{528384, 45056, 1671168}, {610304, 45056, 1671168}, {528384, 45056, 1589248}, {610304, 45056, 1589248}, },
	{{454656, 45056, 1671168}, {528384, 45056, 1671168}, {454656, 45056, 1589248}, {528384, 45056, 1589248}, },
	{{397312, 45056, 1589248}, {454656, 45056, 1589248}, {397312, 45056, 1515520}, {454656, 45056, 1515520}, },
	{{397312, 45056, 1671168}, {454656, 45056, 1671168}, {397312, 45056, 1589248}, {454656, 45056, 1589248}, },
	{{-77824, 45056, 1720320}, {4096, 45056, 1720320}, {-77824, 45056, 1662976}, {4096, 45056, 1662976}, },
	{{4096, 45056, 1720320}, {77824, 45056, 1720320}, {4096, 45056, 1662976}, {77824, 45056, 1662976}, },
	{{4096, 45056, 1662976}, {77824, 45056, 1662976}, {4096, 45056, 1589248}, {77824, 45056, 1589248}, },
	{{-77824, 45056, 1662976}, {4096, 45056, 1662976}, {-77824, 45056, 1589248}, {4096, 45056, 1589248}, },
	{{-77824, 45056, 1589248}, {4096, 45056, 1589248}, {-77824, 45056, 1507328}, {4096, 45056, 1507328}, },
	{{4096, 45056, 1589248}, {77824, 45056, 1589248}, {4096, 45056, 1507328}, {77824, 45056, 1507328}, },
	{{77824, 45056, 1662976}, {135168, 45056, 1662976}, {77824, 45056, 1589248}, {135168, 45056, 1589248}, },
	{{77824, 45056, 1589248}, {135168, 45056, 1589248}, {77824, 45056, 1507328}, {135168, 45056, 1507328}, },
	{{-126976, -135168, 1916928}, {-61440, -135168, 1916928}, {-126976, -135168, 1982464}, {-61440, -135168, 1982464}, },
	{{69632, -135168, 1785856}, {135168, -135168, 1785856}, {69632, -135168, 1916928}, {135168, -135168, 1916928}, },
	{{-126976, -135168, 1458176}, {-61440, -135168, 1458176}, {-126976, -135168, 1523712}, {-61440, -135168, 1523712}, },
	{{-61440, -135168, 1458176}, {69632, -135168, 1458176}, {-61440, -135168, 1523712}, {69632, -135168, 1523712}, },
	{{69632, -135168, 1458176}, {135168, -135168, 1458176}, {69632, -135168, 1523712}, {135168, -135168, 1523712}, },
	{{200704, -135168, 1458176}, {331776, -135168, 1458176}, {200704, -135168, 1523712}, {331776, -135168, 1523712}, },
	{{331776, -135168, 1458176}, {397312, -135168, 1458176}, {331776, -135168, 1523712}, {397312, -135168, 1523712}, },
	{{397312, -135168, 1458176}, {462848, -135168, 1458176}, {397312, -135168, 1523712}, {462848, -135168, 1523712}, },
	{{-61440, -135168, 1916928}, {69632, -135168, 1916928}, {-61440, -135168, 1982464}, {69632, -135168, 1982464}, },
	{{397312, -135168, 1523712}, {462848, -135168, 1523712}, {397312, -118784, 1523712}, {462848, -118784, 1523712}, },
	{{397312, -118784, 1523712}, {462848, -118784, 1523712}, {397312, -118784, 1654784}, {462848, -118784, 1654784}, },
	{{397312, -118784, 1654784}, {462848, -118784, 1654784}, {397312, -135168, 1654784}, {462848, -135168, 1654784}, },
	{{462848, -118784, 1392640}, {462848, -118784, 1458176}, {462848, -135168, 1392640}, {462848, -135168, 1458176}, },
	{{462848, -118784, 1392640}, {593920, -118784, 1392640}, {462848, -118784, 1458176}, {593920, -118784, 1458176}, },
	{{593920, -135168, 1392640}, {593920, -135168, 1458176}, {593920, -118784, 1392640}, {593920, -118784, 1458176}, },
	{{397312, -135168, 1392640}, {462848, -135168, 1392640}, {397312, -135168, 1458176}, {462848, -135168, 1458176}, },
	{{69632, -135168, 1720320}, {135168, -135168, 1720320}, {69632, -135168, 1785856}, {135168, -135168, 1785856}, },
	{{135168, -135168, 1654784}, {200704, -135168, 1654784}, {135168, -135168, 1720320}, {200704, -135168, 1720320}, },
	{{200704, -135168, 1654784}, {331776, -135168, 1654784}, {200704, -135168, 1720320}, {331776, -135168, 1720320}, },
	{{462848, -135168, 1654784}, {593920, -135168, 1654784}, {462848, -135168, 1720320}, {593920, -135168, 1720320}, },
	{{593920, -135168, 1654784}, {659456, -135168, 1654784}, {593920, -135168, 1720320}, {659456, -135168, 1720320}, },
	{{593920, -135168, 1523712}, {659456, -135168, 1523712}, {593920, -135168, 1654784}, {659456, -135168, 1654784}, },
	{{593920, -135168, 1458176}, {659456, -135168, 1458176}, {593920, -135168, 1523712}, {659456, -135168, 1523712}, },
	{{593920, -135168, 1392640}, {659456, -135168, 1392640}, {593920, -135168, 1458176}, {659456, -135168, 1458176}, },
	{{593920, -135168, 1261568}, {659456, -135168, 1261568}, {593920, -135168, 1392640}, {659456, -135168, 1392640}, },
	{{593920, -135168, 1130496}, {659456, -135168, 1130496}, {593920, -135168, 1261568}, {659456, -135168, 1261568}, },
	{{593920, -135168, 999424}, {659456, -135168, 999424}, {593920, -135168, 1130496}, {659456, -135168, 1130496}, },
	{{593920, -135168, 737280}, {659456, -135168, 737280}, {593920, -135168, 868352}, {659456, -135168, 868352}, },
	{{397312, -135168, 1261568}, {462848, -135168, 1261568}, {397312, -135168, 1392640}, {462848, -135168, 1392640}, },
	{{397312, -135168, 1130496}, {462848, -135168, 1130496}, {397312, -135168, 1261568}, {462848, -135168, 1261568}, },
	{{397312, -135168, 999424}, {462848, -135168, 999424}, {397312, -135168, 1130496}, {462848, -135168, 1130496}, },
	{{397312, -135168, 933888}, {462848, -135168, 933888}, {397312, -135168, 999424}, {462848, -135168, 999424}, },
	{{397312, -135168, 868352}, {462848, -135168, 868352}, {397312, -135168, 933888}, {462848, -135168, 933888}, },
	{{331776, -135168, 868352}, {397312, -135168, 868352}, {331776, -135168, 933888}, {397312, -135168, 933888}, },
	{{200704, -135168, 868352}, {331776, -135168, 868352}, {200704, -135168, 933888}, {331776, -135168, 933888}, },
	{{135168, -135168, 868352}, {200704, -135168, 868352}, {135168, -135168, 933888}, {200704, -135168, 933888}, },
	{{69632, -135168, 737280}, {135168, -135168, 737280}, {69632, -118784, 737280}, {135168, -118784, 737280}, },
	{{69632, -118784, 737280}, {135168, -118784, 737280}, {69632, -118784, 868352}, {135168, -118784, 868352}, },
	{{69632, -118784, 868352}, {135168, -118784, 868352}, {69632, -135168, 868352}, {135168, -135168, 868352}, },
	{{135168, -135168, 737280}, {200704, -135168, 737280}, {135168, -118784, 737280}, {200704, -118784, 737280}, },
	{{135168, -118784, 737280}, {200704, -118784, 737280}, {135168, -118784, 868352}, {200704, -118784, 868352}, },
	{{135168, -118784, 868352}, {200704, -118784, 868352}, {135168, -135168, 868352}, {200704, -135168, 868352}, },
	{{593920, -135168, 671744}, {659456, -135168, 671744}, {593920, -135168, 737280}, {659456, -135168, 737280}, },
	{{462848, -135168, 671744}, {593920, -135168, 671744}, {462848, -135168, 737280}, {593920, -135168, 737280}, },
	{{331776, -135168, 737280}, {397312, -135168, 737280}, {331776, -118784, 737280}, {397312, -118784, 737280}, },
	{{331776, -118784, 737280}, {397312, -118784, 737280}, {331776, -118784, 868352}, {397312, -118784, 868352}, },
	{{331776, -118784, 868352}, {397312, -118784, 868352}, {331776, -135168, 868352}, {397312, -135168, 868352}, },
	{{397312, -135168, 671744}, {462848, -135168, 671744}, {397312, -135168, 737280}, {462848, -135168, 737280}, },
	{{331776, -135168, 671744}, {397312, -135168, 671744}, {331776, -135168, 737280}, {397312, -135168, 737280}, },
	{{200704, -135168, 671744}, {331776, -135168, 671744}, {200704, -135168, 737280}, {331776, -135168, 737280}, },
	{{135168, -135168, 671744}, {200704, -135168, 671744}, {135168, -135168, 737280}, {200704, -135168, 737280}, },
	{{593920, -135168, 933888}, {659456, -135168, 933888}, {593920, -135168, 999424}, {659456, -135168, 999424}, },
	{{593920, -135168, 868352}, {659456, -135168, 868352}, {593920, -135168, 933888}, {659456, -135168, 933888}, },
	{{462848, -118784, 868352}, {462848, -118784, 933888}, {462848, -135168, 868352}, {462848, -135168, 933888}, },
	{{462848, -118784, 868352}, {593920, -118784, 868352}, {462848, -118784, 933888}, {593920, -118784, 933888}, },
	{{593920, -135168, 868352}, {593920, -135168, 933888}, {593920, -118784, 868352}, {593920, -118784, 933888}, },
	{{331776, -135168, 1654784}, {397312, -135168, 1654784}, {331776, -135168, 1720320}, {397312, -135168, 1720320}, },
	{{-61440, -118784, 1720320}, {-61440, -118784, 1785856}, {-61440, -135168, 1720320}, {-61440, -135168, 1785856}, },
	{{-61440, -118784, 1720320}, {69632, -118784, 1720320}, {-61440, -118784, 1785856}, {69632, -118784, 1785856}, },
	{{69632, -135168, 1720320}, {69632, -135168, 1785856}, {69632, -118784, 1720320}, {69632, -118784, 1785856}, },
	{{-126976, -135168, 1785856}, {-61440, -135168, 1785856}, {-126976, -135168, 1916928}, {-61440, -135168, 1916928}, },
	{{-126976, -135168, 1720320}, {-61440, -135168, 1720320}, {-126976, -135168, 1785856}, {-61440, -135168, 1785856}, },
	{{-126976, -135168, 1654784}, {-61440, -135168, 1654784}, {-126976, -135168, 1720320}, {-61440, -135168, 1720320}, },
	{{-126976, -135168, 1523712}, {-61440, -135168, 1523712}, {-126976, -135168, 1654784}, {-61440, -135168, 1654784}, },
	{{-61440, -118784, 1523712}, {-61440, -118784, 1654784}, {-61440, -135168, 1523712}, {-61440, -135168, 1654784}, },
	{{-61440, -135168, 1523712}, {69632, -135168, 1523712}, {-61440, -118784, 1523712}, {69632, -118784, 1523712}, },
	{{-61440, -118784, 1523712}, {69632, -118784, 1523712}, {-61440, -118784, 1654784}, {69632, -118784, 1654784}, },
	{{-61440, -217088, 671744}, {69632, -217088, 671744}, {-61440, -135168, 671744}, {69632, -135168, 671744}, },
	{{-61440, -217088, 737280}, {69632, -217088, 737280}, {-61440, -217088, 671744}, {69632, -217088, 671744}, },
	{{-61440, -135168, 868352}, {69632, -135168, 868352}, {-61440, -135168, 933888}, {69632, -135168, 933888}, },
	{{-61440, -217088, 933888}, {69632, -217088, 933888}, {-61440, -217088, 868352}, {69632, -217088, 868352}, },
	{{397312, -135168, 1654784}, {462848, -135168, 1654784}, {397312, -135168, 1720320}, {462848, -135168, 1720320}, },
	{{69632, -135168, 1523712}, {135168, -135168, 1523712}, {69632, -118784, 1523712}, {135168, -118784, 1523712}, },
	{{69632, -118784, 1523712}, {135168, -118784, 1523712}, {69632, -118784, 1654784}, {135168, -118784, 1654784}, },
	{{69632, -118784, 1654784}, {135168, -118784, 1654784}, {69632, -135168, 1654784}, {135168, -135168, 1654784}, },
	{{69632, -135168, 1654784}, {135168, -135168, 1654784}, {69632, -135168, 1720320}, {135168, -135168, 1720320}, },
	{{135168, -135168, 1458176}, {200704, -135168, 1458176}, {135168, -135168, 1523712}, {200704, -135168, 1523712}, },
	{{-61440, -217088, 737280}, {69632, -217088, 737280}, {-61440, -135168, 737280}, {69632, -135168, 737280}, },
	{{-61440, -217088, 868352}, {69632, -217088, 868352}, {-61440, -217088, 737280}, {69632, -217088, 737280}, },
	{{69632, -217088, 868352}, {135168, -217088, 868352}, {69632, -217088, 737280}, {135168, -217088, 737280}, },
};
uint32_t triPrims[2][234] = {
	{
		0x00000000, 0xe202539c, 0x25808080, 0x00000000, 0x3c162020, 0x00000000, 0x00052027, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202539c, 0x25808080, 0x00000000, 0x3c163f20, 0x00000000, 0x00052020, 0x00000000, 0x00003f27, 
		0x00000000, 0xe202539c, 0x25808080, 0x00000000, 0x3c162020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202539c, 0x25808080, 0x00000000, 0x3c163f20, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202539c, 0x25808080, 0x00000000, 0x3c16203f, 0x00000000, 0x00053f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe202539c, 0x25808080, 0x00000000, 0x3c162027, 0x00000000, 0x00053f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe202539c, 0x25808080, 0x00000000, 0x3c163f27, 0x00000000, 0x00053f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe202539c, 0x25808080, 0x00000000, 0x3c163f3f, 0x00000000, 0x00053f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c953f20, 0x00000000, 0x0005203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c953f18, 0x00000000, 0x00053f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c953f18, 0x00000000, 0x00052020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c952018, 0x00000000, 0x00053f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c952018, 0x00000000, 0x00052020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c952020, 0x00000000, 0x00053f3f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c952020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c952020, 0x00000000, 0x00053f20, 0x00000000, 0x00002027, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c952020, 0x00000000, 0x00052027, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f27, 0x00000000, 0x00002020, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00052020, 0x00000000, 0x00003f27, 
		0x00000000, 0xe200739c, 0x25808080, 0x00000000, 0x3c942336, 0x00000000, 0x00053332, 0x00000000, 0x00003336, 
		0x00000000, 0xe200739c, 0x25808080, 0x00000000, 0x3c94332d, 0x00000000, 0x00052331, 0x00000000, 0x00003331, 
},
{
		0x00000000, 0xe202539c, 0x25808080, 0x00000000, 0x3c162020, 0x00000000, 0x00052027, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202539c, 0x25808080, 0x00000000, 0x3c163f20, 0x00000000, 0x00052020, 0x00000000, 0x00003f27, 
		0x00000000, 0xe202539c, 0x25808080, 0x00000000, 0x3c162020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202539c, 0x25808080, 0x00000000, 0x3c163f20, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202539c, 0x25808080, 0x00000000, 0x3c16203f, 0x00000000, 0x00053f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe202539c, 0x25808080, 0x00000000, 0x3c162027, 0x00000000, 0x00053f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe202539c, 0x25808080, 0x00000000, 0x3c163f27, 0x00000000, 0x00053f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe202539c, 0x25808080, 0x00000000, 0x3c163f3f, 0x00000000, 0x00053f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c953f20, 0x00000000, 0x0005203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c953f18, 0x00000000, 0x00053f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c953f18, 0x00000000, 0x00052020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c952018, 0x00000000, 0x00053f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c952018, 0x00000000, 0x00052020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c952020, 0x00000000, 0x00053f3f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c952020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c952020, 0x00000000, 0x00053f20, 0x00000000, 0x00002027, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c952020, 0x00000000, 0x00052027, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f27, 0x00000000, 0x00002020, 
		0x00000000, 0xe200039c, 0x25808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00052020, 0x00000000, 0x00003f27, 
		0x00000000, 0xe200739c, 0x25808080, 0x00000000, 0x3c942336, 0x00000000, 0x00053332, 0x00000000, 0x00003336, 
		0x00000000, 0xe200739c, 0x25808080, 0x00000000, 0x3c94332d, 0x00000000, 0x00052331, 0x00000000, 0x00003331, 
},
};
uint32_t quadPrims[2][11847] = {
	{
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c14203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c152020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c143f20, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c152020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c152020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c152020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c152020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c152020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c152020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c152020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f20, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f20, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f20, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f20, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f20, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f20, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f20, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f20, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c143f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202039c, 0x2d808080, 0x00000000, 0x3c573f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202039c, 0x2d808080, 0x00000000, 0x3c573f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202039c, 0x2d808080, 0x00000000, 0x3c573f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202039c, 0x2d808080, 0x00000000, 0x3c573f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15203f, 0x00000000, 0x0005273f, 0x00000000, 0x00002020, 0x00000000, 0x00002720, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c54303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c542f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15203f, 0x00000000, 0x0005273f, 0x00000000, 0x00002020, 0x00000000, 0x00002720, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c544e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c17203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c17203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c544f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c152720, 0x00000000, 0x00052020, 0x00000000, 0x0000273f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c152720, 0x00000000, 0x00052020, 0x00000000, 0x0000273f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd5203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c54303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c542f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd4203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd42020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c544f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd5203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd5203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c544e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c54303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c542f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd4203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd42020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c544f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd4203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd4203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c544e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c54303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c542f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c97203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c544f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd4203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd4203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c544e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd63f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c54303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c542f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c544f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd4203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd4203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c544e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd63f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd63f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c54303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c542f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c544f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c97203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c97203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c544e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd63f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd5203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd61013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd4203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd61013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd42020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd4203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd61013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd42020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c97203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd61013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd63f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd61013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd63f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd63f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd61013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd63f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd63f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd61013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd63f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd63f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd61013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd63f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202039c, 0x2d808080, 0x00000000, 0x3c572020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe202039c, 0x2d808080, 0x00000000, 0x3c572020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951c01, 0x00000000, 0x00051c3e, 0x00000000, 0x00002001, 0x00000000, 0x0000203e, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c152020, 0x00000000, 0x0005202f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f2f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15202f, 0x00000000, 0x00052042, 0x00000000, 0x00003f2f, 0x00000000, 0x00003f42, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c152020, 0x00000000, 0x0005202f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f2f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15202f, 0x00000000, 0x00052042, 0x00000000, 0x00003f2f, 0x00000000, 0x00003f42, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142f2d, 0x00000000, 0x00053f2d, 0x00000000, 0x00002f20, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142d20, 0x00000000, 0x00052d0e, 0x00000000, 0x00002020, 0x00000000, 0x0000200e, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c140c10, 0x00000000, 0x00050c20, 0x00000000, 0x00002010, 0x00000000, 0x00002020, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c143f0c, 0x00000000, 0x00052d0c, 0x00000000, 0x00003f20, 0x00000000, 0x00002d20, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f10, 0x00000000, 0x00052010, 0x00000000, 0x00003f23, 0x00000000, 0x00002023, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f1c, 0x00000000, 0x0005201c, 0x00000000, 0x00003f2f, 0x00000000, 0x0000202f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f10, 0x00000000, 0x00052010, 0x00000000, 0x00003f23, 0x00000000, 0x00002023, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f1c, 0x00000000, 0x0005201c, 0x00000000, 0x00003f2f, 0x00000000, 0x0000202f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15203b, 0x00000000, 0x0005204e, 0x00000000, 0x00003f3b, 0x00000000, 0x00003f4e, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15202f, 0x00000000, 0x00052043, 0x00000000, 0x00003f2f, 0x00000000, 0x00003f43, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15203b, 0x00000000, 0x0005204e, 0x00000000, 0x00003f3b, 0x00000000, 0x00003f4e, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15202f, 0x00000000, 0x00052043, 0x00000000, 0x00003f2f, 0x00000000, 0x00003f43, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15203b, 0x00000000, 0x0005204e, 0x00000000, 0x00003f3b, 0x00000000, 0x00003f4e, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15202f, 0x00000000, 0x00052043, 0x00000000, 0x00003f2f, 0x00000000, 0x00003f43, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15203b, 0x00000000, 0x0005204e, 0x00000000, 0x00003f3b, 0x00000000, 0x00003f4e, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15202f, 0x00000000, 0x00052043, 0x00000000, 0x00003f2f, 0x00000000, 0x00003f43, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f10, 0x00000000, 0x00052010, 0x00000000, 0x00003f23, 0x00000000, 0x00002023, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f10, 0x00000000, 0x00052010, 0x00000000, 0x00003f23, 0x00000000, 0x00002023, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f1b, 0x00000000, 0x0005201b, 0x00000000, 0x00003f2f, 0x00000000, 0x0000202f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f1b, 0x00000000, 0x0005201b, 0x00000000, 0x00003f2f, 0x00000000, 0x0000202f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15201c, 0x00000000, 0x0005202f, 0x00000000, 0x00003f1c, 0x00000000, 0x00003f2f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15201c, 0x00000000, 0x0005202f, 0x00000000, 0x00003f1c, 0x00000000, 0x00003f2f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15202f, 0x00000000, 0x00052042, 0x00000000, 0x00003f2f, 0x00000000, 0x00003f42, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15202f, 0x00000000, 0x00052042, 0x00000000, 0x00003f2f, 0x00000000, 0x00003f42, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c95103f, 0x00000000, 0x00051020, 0x00000000, 0x0000083f, 0x00000000, 0x00000820, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c95103f, 0x00000000, 0x00051020, 0x00000000, 0x0000083f, 0x00000000, 0x00000820, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950818, 0x00000000, 0x00050820, 0x00000000, 0x00001018, 0x00000000, 0x00001020, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f18, 0x00000000, 0x00053f20, 0x00000000, 0x00002018, 0x00000000, 0x00002020, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952018, 0x00000000, 0x00052020, 0x00000000, 0x00003f18, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951018, 0x00000000, 0x00051020, 0x00000000, 0x00000818, 0x00000000, 0x00000820, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950818, 0x00000000, 0x00050820, 0x00000000, 0x00001018, 0x00000000, 0x00001020, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c95103f, 0x00000000, 0x00051020, 0x00000000, 0x0000083f, 0x00000000, 0x00000820, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c95083f, 0x00000000, 0x00050820, 0x00000000, 0x0000103f, 0x00000000, 0x00001020, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951018, 0x00000000, 0x00051020, 0x00000000, 0x00000818, 0x00000000, 0x00000820, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x00050820, 0x00000000, 0x0000103f, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950818, 0x00000000, 0x00050820, 0x00000000, 0x00001018, 0x00000000, 0x00001020, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f18, 0x00000000, 0x00053f20, 0x00000000, 0x00002018, 0x00000000, 0x00002020, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952018, 0x00000000, 0x00052020, 0x00000000, 0x00003f18, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951018, 0x00000000, 0x00051020, 0x00000000, 0x00000818, 0x00000000, 0x00000820, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c95083f, 0x00000000, 0x00050820, 0x00000000, 0x0000103f, 0x00000000, 0x00001020, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c95083f, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x00001020, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c95083f, 0x00000000, 0x00050820, 0x00000000, 0x0000103f, 0x00000000, 0x00001020, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x00050820, 0x00000000, 0x0000103f, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c95083f, 0x00000000, 0x00050820, 0x00000000, 0x0000103f, 0x00000000, 0x00001020, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x00051027, 0x00000000, 0x00000820, 0x00000000, 0x00000827, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x00050820, 0x00000000, 0x0000103f, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x00050827, 0x00000000, 0x00001020, 0x00000000, 0x00001027, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f27, 0x00000000, 0x00002020, 0x00000000, 0x00002027, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x00052027, 0x00000000, 0x00003f20, 0x00000000, 0x00003f27, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x00051027, 0x00000000, 0x00000820, 0x00000000, 0x00000827, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x00050827, 0x00000000, 0x00001020, 0x00000000, 0x00001027, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c95103f, 0x00000000, 0x00051020, 0x00000000, 0x0000083f, 0x00000000, 0x00000820, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x00050827, 0x00000000, 0x00001020, 0x00000000, 0x00001027, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f27, 0x00000000, 0x00002020, 0x00000000, 0x00002027, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x00052027, 0x00000000, 0x00003f20, 0x00000000, 0x00003f27, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x00051027, 0x00000000, 0x00000820, 0x00000000, 0x00000827, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943b04, 0x00000000, 0x00053b23, 0x00000000, 0x00001c04, 0x00000000, 0x00001c23, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c20, 0x00000000, 0x00051c3f, 0x00000000, 0x00003b20, 0x00000000, 0x00003b3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942320, 0x00000000, 0x0005233f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f08, 0x00000000, 0x00050408, 0x00000000, 0x00002f0a, 0x00000000, 0x0000040a, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f2a, 0x00000000, 0x00052f2f, 0x00000000, 0x0000042a, 0x00000000, 0x0000042f, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f2f, 0x00000000, 0x00052f34, 0x00000000, 0x0000042f, 0x00000000, 0x00000434, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d150408, 0x00000000, 0x00052f08, 0x00000000, 0x0000040a, 0x00000000, 0x00002f0a, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f27, 0x00000000, 0x00052f29, 0x00000000, 0x00001027, 0x00000000, 0x00001029, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15102a, 0x00000000, 0x0005102f, 0x00000000, 0x00002f2a, 0x00000000, 0x00002f2f, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15102f, 0x00000000, 0x00051034, 0x00000000, 0x00002f2f, 0x00000000, 0x00002f34, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f27, 0x00000000, 0x00051027, 0x00000000, 0x00002f29, 0x00000000, 0x00001029, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f08, 0x00000000, 0x00050408, 0x00000000, 0x00002f0a, 0x00000000, 0x0000040a, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f0b, 0x00000000, 0x00052f10, 0x00000000, 0x0000040b, 0x00000000, 0x00000410, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f10, 0x00000000, 0x00052f15, 0x00000000, 0x00000410, 0x00000000, 0x00000415, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d150408, 0x00000000, 0x00052f08, 0x00000000, 0x0000040a, 0x00000000, 0x00002f0a, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f27, 0x00000000, 0x00052f29, 0x00000000, 0x00001027, 0x00000000, 0x00001029, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15100b, 0x00000000, 0x00051010, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f10, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d151010, 0x00000000, 0x00051015, 0x00000000, 0x00002f10, 0x00000000, 0x00002f15, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f27, 0x00000000, 0x00051027, 0x00000000, 0x00002f29, 0x00000000, 0x00001029, 
		0x00000000, 0xe200639c, 0x2d808080, 0x00000000, 0x3cd71c20, 0x00000000, 0x00051c3e, 0x00000000, 0x00003520, 0x00000000, 0x0000353e, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951b0d, 0x00000000, 0x00051b32, 0x00000000, 0x00001f0d, 0x00000000, 0x00001f32, 
		0x00000000, 0xe200639c, 0x2d808080, 0x00000000, 0x3cd73520, 0x00000000, 0x0005353e, 0x00000000, 0x00001c20, 0x00000000, 0x00001c3e, 
		0x00000000, 0xe2080318, 0x2d808080, 0x00000000, 0x3c967d40, 0x00000000, 0x00057d46, 0x00000000, 0x00003f40, 0x00000000, 0x00003f46, 
		0x00000000, 0xe2080318, 0x2d808080, 0x00000000, 0x3c963f40, 0x00000000, 0x00053f7e, 0x00000000, 0x00007d40, 0x00000000, 0x00007d7e, 
		0x00000000, 0xe2080318, 0x2d808080, 0x00000000, 0x3c963940, 0x00000000, 0x0005397e, 0x00000000, 0x00003340, 0x00000000, 0x0000337e, 
		0x00000000, 0xe2080318, 0x2d808080, 0x00000000, 0x3c963340, 0x00000000, 0x0005337e, 0x00000000, 0x00003940, 0x00000000, 0x0000397e, 
		0x00000000, 0xe2080318, 0x2d808080, 0x00000000, 0x3c967d40, 0x00000000, 0x00057d7e, 0x00000000, 0x00003f40, 0x00000000, 0x00003f7e, 
		0x00000000, 0xe2080318, 0x2d808080, 0x00000000, 0x3c963f40, 0x00000000, 0x00053f46, 0x00000000, 0x00007d40, 0x00000000, 0x00007d46, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943b23, 0x00000000, 0x00053b42, 0x00000000, 0x00001c23, 0x00000000, 0x00001c42, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c20, 0x00000000, 0x00051c3f, 0x00000000, 0x00003b20, 0x00000000, 0x00003b3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942320, 0x00000000, 0x0005233f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943b04, 0x00000000, 0x00053b14, 0x00000000, 0x00001c04, 0x00000000, 0x00001c14, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c20, 0x00000000, 0x00051c2f, 0x00000000, 0x00003b20, 0x00000000, 0x00003b2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94103f, 0x00000000, 0x00051020, 0x00000000, 0x0000233f, 0x00000000, 0x00002320, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94233f, 0x00000000, 0x00052320, 0x00000000, 0x0000103f, 0x00000000, 0x00001020, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943b33, 0x00000000, 0x00053b42, 0x00000000, 0x00001c33, 0x00000000, 0x00001c42, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c2f, 0x00000000, 0x00051c3f, 0x00000000, 0x00003b2f, 0x00000000, 0x00003b3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b33, 0x00000000, 0x00052b42, 0x00000000, 0x00001c33, 0x00000000, 0x00001c42, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c2f, 0x00000000, 0x00051c3f, 0x00000000, 0x00002b2f, 0x00000000, 0x00002b3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94102f, 0x00000000, 0x0005103f, 0x00000000, 0x0000232f, 0x00000000, 0x0000233f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c33, 0x00000000, 0x00051c42, 0x00000000, 0x00000c33, 0x00000000, 0x00000c42, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c940c2f, 0x00000000, 0x00050c3f, 0x00000000, 0x00001c2f, 0x00000000, 0x00001c3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941020, 0x00000000, 0x0005102f, 0x00000000, 0x00002320, 0x00000000, 0x0000232f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943b04, 0x00000000, 0x00053b14, 0x00000000, 0x00001c04, 0x00000000, 0x00001c14, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c20, 0x00000000, 0x00051c2f, 0x00000000, 0x00003b20, 0x00000000, 0x00003b2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943b04, 0x00000000, 0x00053b14, 0x00000000, 0x00001c04, 0x00000000, 0x00001c14, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c20, 0x00000000, 0x00051c2f, 0x00000000, 0x00003b20, 0x00000000, 0x00003b2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94234e, 0x00000000, 0x0005424e, 0x00000000, 0x0000232f, 0x00000000, 0x0000422f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94234e, 0x00000000, 0x0005424e, 0x00000000, 0x0000232f, 0x00000000, 0x0000422f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94234e, 0x00000000, 0x0005424e, 0x00000000, 0x0000232f, 0x00000000, 0x0000422f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94234e, 0x00000000, 0x0005424e, 0x00000000, 0x0000232f, 0x00000000, 0x0000422f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94234e, 0x00000000, 0x0005424e, 0x00000000, 0x0000232f, 0x00000000, 0x0000422f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94234e, 0x00000000, 0x0005424e, 0x00000000, 0x0000232f, 0x00000000, 0x0000422f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94234e, 0x00000000, 0x0005424e, 0x00000000, 0x0000232f, 0x00000000, 0x0000422f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94234e, 0x00000000, 0x0005424e, 0x00000000, 0x0000232f, 0x00000000, 0x0000422f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94232f, 0x00000000, 0x0005422f, 0x00000000, 0x0000234e, 0x00000000, 0x0000424e, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94232f, 0x00000000, 0x0005422f, 0x00000000, 0x0000234e, 0x00000000, 0x0000424e, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94232f, 0x00000000, 0x0005422f, 0x00000000, 0x0000234e, 0x00000000, 0x0000424e, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94232f, 0x00000000, 0x0005422f, 0x00000000, 0x0000234e, 0x00000000, 0x0000424e, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94232f, 0x00000000, 0x0005422f, 0x00000000, 0x0000234e, 0x00000000, 0x0000424e, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94232f, 0x00000000, 0x0005422f, 0x00000000, 0x0000234e, 0x00000000, 0x0000424e, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94232f, 0x00000000, 0x0005422f, 0x00000000, 0x0000234e, 0x00000000, 0x0000424e, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94232f, 0x00000000, 0x0005422f, 0x00000000, 0x0000234e, 0x00000000, 0x0000424e, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c163b20, 0x00000000, 0x00053b3f, 0x00000000, 0x00001c20, 0x00000000, 0x00001c3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c163b20, 0x00000000, 0x00053b3f, 0x00000000, 0x00001c20, 0x00000000, 0x00001c3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c163b20, 0x00000000, 0x00053b3f, 0x00000000, 0x00001c20, 0x00000000, 0x00001c3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c163b20, 0x00000000, 0x00053b3f, 0x00000000, 0x00001c20, 0x00000000, 0x00001c3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c163b20, 0x00000000, 0x00053b3f, 0x00000000, 0x00001c20, 0x00000000, 0x00001c3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c163b20, 0x00000000, 0x00053b3f, 0x00000000, 0x00001c20, 0x00000000, 0x00001c3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c163b20, 0x00000000, 0x00053b3f, 0x00000000, 0x00001c20, 0x00000000, 0x00001c3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c163b20, 0x00000000, 0x00053b3f, 0x00000000, 0x00001c20, 0x00000000, 0x00001c3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952f20, 0x00000000, 0x00052f23, 0x00000000, 0x00001020, 0x00000000, 0x00001023, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952f20, 0x00000000, 0x00052f23, 0x00000000, 0x00001020, 0x00000000, 0x00001023, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951c32, 0x00000000, 0x00051c3f, 0x00000000, 0x00002032, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951c20, 0x00000000, 0x00051c2c, 0x00000000, 0x00002020, 0x00000000, 0x0000202c, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x00051023, 0x00000000, 0x00002f20, 0x00000000, 0x00002f23, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x00051023, 0x00000000, 0x00002f20, 0x00000000, 0x00002f23, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f2b, 0x00000000, 0x00052f2d, 0x00000000, 0x0000082b, 0x00000000, 0x0000082d, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15080b, 0x00000000, 0x00050810, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f10, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d150810, 0x00000000, 0x00050815, 0x00000000, 0x00002f10, 0x00000000, 0x00002f15, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f2b, 0x00000000, 0x0005082b, 0x00000000, 0x00002f2d, 0x00000000, 0x0000082d, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f2b, 0x00000000, 0x00052f2d, 0x00000000, 0x0000082b, 0x00000000, 0x0000082d, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15082a, 0x00000000, 0x0005082f, 0x00000000, 0x00002f2a, 0x00000000, 0x00002f2f, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15082f, 0x00000000, 0x00050834, 0x00000000, 0x00002f2f, 0x00000000, 0x00002f34, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f2b, 0x00000000, 0x0005082b, 0x00000000, 0x00002f2d, 0x00000000, 0x0000082d, 
		0x00000000, 0xe2080318, 0x2d808080, 0x00000000, 0x3c960140, 0x00000000, 0x0005017e, 0x00000000, 0x00003f40, 0x00000000, 0x00003f7e, 
		0x00000000, 0xe200639c, 0x2d808080, 0x00000000, 0x3cd71c20, 0x00000000, 0x00051c3e, 0x00000000, 0x00003520, 0x00000000, 0x0000353e, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f27, 0x00000000, 0x00052f29, 0x00000000, 0x00001027, 0x00000000, 0x00001029, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15100b, 0x00000000, 0x00051010, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f10, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d151010, 0x00000000, 0x00051015, 0x00000000, 0x00002f10, 0x00000000, 0x00002f15, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f27, 0x00000000, 0x00051027, 0x00000000, 0x00002f29, 0x00000000, 0x00001029, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f27, 0x00000000, 0x00052f29, 0x00000000, 0x00001027, 0x00000000, 0x00001029, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15102a, 0x00000000, 0x0005102f, 0x00000000, 0x00002f2a, 0x00000000, 0x00002f2f, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15102f, 0x00000000, 0x00051034, 0x00000000, 0x00002f2f, 0x00000000, 0x00002f34, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f27, 0x00000000, 0x00051027, 0x00000000, 0x00002f29, 0x00000000, 0x00001029, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15272b, 0x00000000, 0x0005272d, 0x00000000, 0x0000102b, 0x00000000, 0x0000102d, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15100b, 0x00000000, 0x00051010, 0x00000000, 0x0000270b, 0x00000000, 0x00002710, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d151010, 0x00000000, 0x00051015, 0x00000000, 0x00002710, 0x00000000, 0x00002715, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15272b, 0x00000000, 0x0005102b, 0x00000000, 0x0000272d, 0x00000000, 0x0000102d, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15272b, 0x00000000, 0x0005272d, 0x00000000, 0x0000102b, 0x00000000, 0x0000102d, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15102a, 0x00000000, 0x0005102f, 0x00000000, 0x0000272a, 0x00000000, 0x0000272f, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15102f, 0x00000000, 0x00051034, 0x00000000, 0x0000272f, 0x00000000, 0x00002734, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15272b, 0x00000000, 0x0005102b, 0x00000000, 0x0000272d, 0x00000000, 0x0000102d, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563b20, 0x00000000, 0x00053f20, 0x00000000, 0x00003b3f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563b3f, 0x00000000, 0x00053f3f, 0x00000000, 0x00003b20, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56373f, 0x00000000, 0x00053b3f, 0x00000000, 0x00003720, 0x00000000, 0x00003b20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563720, 0x00000000, 0x00053b20, 0x00000000, 0x0000373f, 0x00000000, 0x00003b3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563b20, 0x00000000, 0x00055a20, 0x00000000, 0x00003b3f, 0x00000000, 0x00005a3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563b20, 0x00000000, 0x00055a20, 0x00000000, 0x00003b3f, 0x00000000, 0x00005a3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563b20, 0x00000000, 0x00055a20, 0x00000000, 0x00003b3f, 0x00000000, 0x00005a3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053b20, 0x00000000, 0x0000203f, 0x00000000, 0x00003b3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x0005373f, 0x00000000, 0x00002020, 0x00000000, 0x00003720, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053b3f, 0x00000000, 0x00002020, 0x00000000, 0x00003b20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563b3f, 0x00000000, 0x00055a3f, 0x00000000, 0x00003b20, 0x00000000, 0x00005a20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563b3f, 0x00000000, 0x00055a3f, 0x00000000, 0x00003b20, 0x00000000, 0x00005a20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563b3f, 0x00000000, 0x00055a3f, 0x00000000, 0x00003b20, 0x00000000, 0x00005a20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563b20, 0x00000000, 0x00055620, 0x00000000, 0x00003b3f, 0x00000000, 0x0000563f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563b20, 0x00000000, 0x00055a20, 0x00000000, 0x00003b3f, 0x00000000, 0x00005a3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563b20, 0x00000000, 0x00055a20, 0x00000000, 0x00003b3f, 0x00000000, 0x00005a3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c561c20, 0x00000000, 0x00053b20, 0x00000000, 0x00001c3f, 0x00000000, 0x00003b3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b2f, 0x00000000, 0x00052b3f, 0x00000000, 0x00001c2f, 0x00000000, 0x00001c3f, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f2b, 0x00000000, 0x00052f2d, 0x00000000, 0x0000042b, 0x00000000, 0x0000042d, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15040b, 0x00000000, 0x00050410, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f10, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d150410, 0x00000000, 0x00050415, 0x00000000, 0x00002f10, 0x00000000, 0x00002f15, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f2b, 0x00000000, 0x0005042b, 0x00000000, 0x00002f2d, 0x00000000, 0x0000042d, 
		0x00000000, 0xe200639c, 0x2d808080, 0x00000000, 0x3cd70c20, 0x00000000, 0x00050c3e, 0x00000000, 0x00001620, 0x00000000, 0x0000163e, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f2b, 0x00000000, 0x00052f2d, 0x00000000, 0x0000042b, 0x00000000, 0x0000042d, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15042a, 0x00000000, 0x0005042f, 0x00000000, 0x00002f2a, 0x00000000, 0x00002f2f, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15042f, 0x00000000, 0x00050434, 0x00000000, 0x00002f2f, 0x00000000, 0x00002f34, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f2b, 0x00000000, 0x0005042b, 0x00000000, 0x00002f2d, 0x00000000, 0x0000042d, 
		0x00000000, 0xe2080318, 0x2d808080, 0x00000000, 0x3c963f40, 0x00000000, 0x00053f7e, 0x00000000, 0x00007d40, 0x00000000, 0x00007d7e, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002b21, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f21, 0x00000000, 0x00052021, 0x00000000, 0x00003f40, 0x00000000, 0x00002040, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f21, 0x00000000, 0x00052021, 0x00000000, 0x00003f40, 0x00000000, 0x00002040, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f21, 0x00000000, 0x00052021, 0x00000000, 0x00003f40, 0x00000000, 0x00002040, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f21, 0x00000000, 0x00052021, 0x00000000, 0x00003f40, 0x00000000, 0x00002040, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52021, 0x00000000, 0x00053321, 0x00000000, 0x00002002, 0x00000000, 0x00003f02, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52021, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00003f02, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972021, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00003f02, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52021, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00003f02, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972b21, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00003f02, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52021, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00003f02, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972021, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00003f02, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52021, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00003f02, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972021, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00003f02, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972021, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00003f02, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002b21, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972021, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00003f02, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52021, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00003f02, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f40, 0x00000000, 0x00052040, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f40, 0x00000000, 0x00052040, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f40, 0x00000000, 0x00052040, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f40, 0x00000000, 0x00052040, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f40, 0x00000000, 0x00052040, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53340, 0x00000000, 0x00052040, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f40, 0x00000000, 0x00052040, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943f29, 0x00000000, 0x00053f2d, 0x00000000, 0x00002029, 0x00000000, 0x0000202d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942021, 0x00000000, 0x00052025, 0x00000000, 0x00003f21, 0x00000000, 0x00003f25, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c3d, 0x00000000, 0x00051c40, 0x00000000, 0x0000183d, 0x00000000, 0x00001840, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94183d, 0x00000000, 0x00051840, 0x00000000, 0x00001c3d, 0x00000000, 0x00001c40, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943f3a, 0x00000000, 0x00053f3e, 0x00000000, 0x0000203a, 0x00000000, 0x0000203e, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942021, 0x00000000, 0x00052025, 0x00000000, 0x00003f21, 0x00000000, 0x00003f25, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f23, 0x00000000, 0x00052f33, 0x00000000, 0x00002323, 0x00000000, 0x00002327, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162320, 0x00000000, 0x00052323, 0x00000000, 0x00002f20, 0x00000000, 0x00002f2f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c161c20, 0x00000000, 0x00051c2f, 0x00000000, 0x00000c20, 0x00000000, 0x00000c2f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c161820, 0x00000000, 0x00051823, 0x00000000, 0x00001c20, 0x00000000, 0x00001c23, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c16202f, 0x00000000, 0x0005203f, 0x00000000, 0x00002b2f, 0x00000000, 0x00002b33, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f33, 0x00000000, 0x00052b33, 0x00000000, 0x00002f3f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f14, 0x00000000, 0x00052f04, 0x00000000, 0x00002308, 0x00000000, 0x00002304, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162b2f, 0x00000000, 0x00052b33, 0x00000000, 0x0000202f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162b20, 0x00000000, 0x00052b2f, 0x00000000, 0x00003b20, 0x00000000, 0x00003b2f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f20, 0x00000000, 0x00052f2f, 0x00000000, 0x00002320, 0x00000000, 0x00002323, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162b33, 0x00000000, 0x00052f33, 0x00000000, 0x0000203f, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943f0e, 0x00000000, 0x00053f0a, 0x00000000, 0x0000200e, 0x00000000, 0x0000200a, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94203a, 0x00000000, 0x0005203e, 0x00000000, 0x00003f3a, 0x00000000, 0x00003f3e, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943f21, 0x00000000, 0x00053f25, 0x00000000, 0x00002021, 0x00000000, 0x00002025, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942006, 0x00000000, 0x00052002, 0x00000000, 0x00003f06, 0x00000000, 0x00003f02, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f20, 0x00000000, 0x00052020, 0x00000000, 0x00002f14, 0x00000000, 0x00002b14, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162323, 0x00000000, 0x00052320, 0x00000000, 0x00002f2f, 0x00000000, 0x00002f20, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c161c2f, 0x00000000, 0x00051c20, 0x00000000, 0x00000c2f, 0x00000000, 0x00000c20, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c161823, 0x00000000, 0x00051820, 0x00000000, 0x00001c23, 0x00000000, 0x00001c20, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x00052010, 0x00000000, 0x00002b14, 0x00000000, 0x00002b10, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162323, 0x00000000, 0x00052327, 0x00000000, 0x00002f23, 0x00000000, 0x00002f33, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x00052f20, 0x00000000, 0x00002b14, 0x00000000, 0x00002f14, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162b14, 0x00000000, 0x00052b10, 0x00000000, 0x00002020, 0x00000000, 0x00002010, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162b2f, 0x00000000, 0x00052b20, 0x00000000, 0x00003b2f, 0x00000000, 0x00003b20, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c163b23, 0x00000000, 0x00053b20, 0x00000000, 0x00003723, 0x00000000, 0x00003720, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f2f, 0x00000000, 0x00052f20, 0x00000000, 0x00002323, 0x00000000, 0x00002320, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162308, 0x00000000, 0x00052304, 0x00000000, 0x00002f14, 0x00000000, 0x00002f04, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f40, 0x00000000, 0x00052b40, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52021, 0x00000000, 0x00052002, 0x00000000, 0x00003321, 0x00000000, 0x00003f02, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94332d, 0x00000000, 0x0005522d, 0x00000000, 0x00003331, 0x00000000, 0x00005231, 
		0x00000000, 0xe204139c, 0x2d808080, 0x00000000, 0x3d163f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f2d, 0x00000000, 0x00054e2d, 0x00000000, 0x00002f31, 0x00000000, 0x00004e31, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f31, 0x00000000, 0x00054e31, 0x00000000, 0x00002f2d, 0x00000000, 0x00004e2d, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd42020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f2d, 0x00000000, 0x00054e2d, 0x00000000, 0x00002f31, 0x00000000, 0x00004e31, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942031, 0x00000000, 0x00052f31, 0x00000000, 0x0000202d, 0x00000000, 0x00002f2d, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52f20, 0x00000000, 0x00053f20, 0x00000000, 0x00002f3f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94202d, 0x00000000, 0x00052f2d, 0x00000000, 0x00002031, 0x00000000, 0x00002f31, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f31, 0x00000000, 0x00054e31, 0x00000000, 0x00002f2d, 0x00000000, 0x00004e2d, 
		0x00000000, 0xe204139c, 0x2d808080, 0x00000000, 0x3d163f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943331, 0x00000000, 0x00055231, 0x00000000, 0x0000332d, 0x00000000, 0x0000522d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94232d, 0x00000000, 0x0005332d, 0x00000000, 0x00002331, 0x00000000, 0x00003331, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52f20, 0x00000000, 0x00052f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942331, 0x00000000, 0x00053331, 0x00000000, 0x0000232d, 0x00000000, 0x0000332d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94332d, 0x00000000, 0x0005522d, 0x00000000, 0x00003331, 0x00000000, 0x00005231, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943331, 0x00000000, 0x00055231, 0x00000000, 0x0000332d, 0x00000000, 0x0000522d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94332d, 0x00000000, 0x0005522d, 0x00000000, 0x00003331, 0x00000000, 0x00005231, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943331, 0x00000000, 0x00055231, 0x00000000, 0x0000332d, 0x00000000, 0x0000522d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94332d, 0x00000000, 0x0005522d, 0x00000000, 0x00003331, 0x00000000, 0x00005231, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943331, 0x00000000, 0x00055231, 0x00000000, 0x0000332d, 0x00000000, 0x0000522d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94232d, 0x00000000, 0x0005332d, 0x00000000, 0x00002331, 0x00000000, 0x00003331, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972f20, 0x00000000, 0x00052f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942331, 0x00000000, 0x00053331, 0x00000000, 0x0000232d, 0x00000000, 0x0000332d, 
		0x00000000, 0xe204139c, 0x2d808080, 0x00000000, 0x3d163f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f2d, 0x00000000, 0x00054e2d, 0x00000000, 0x00002f31, 0x00000000, 0x00004e31, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943331, 0x00000000, 0x00055231, 0x00000000, 0x0000332d, 0x00000000, 0x0000522d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f31, 0x00000000, 0x00053f31, 0x00000000, 0x00002f2d, 0x00000000, 0x00003f2d, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52020, 0x00000000, 0x00052f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f2d, 0x00000000, 0x00053f2d, 0x00000000, 0x00002f31, 0x00000000, 0x00003f31, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f31, 0x00000000, 0x00054e31, 0x00000000, 0x00002f2d, 0x00000000, 0x00004e2d, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd42020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f2d, 0x00000000, 0x00054e2d, 0x00000000, 0x00002f31, 0x00000000, 0x00004e31, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942031, 0x00000000, 0x00052f31, 0x00000000, 0x0000202d, 0x00000000, 0x00002f2d, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972f20, 0x00000000, 0x00053f20, 0x00000000, 0x00002f3f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94202d, 0x00000000, 0x00052f2d, 0x00000000, 0x00002031, 0x00000000, 0x00002f31, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94332d, 0x00000000, 0x0005422d, 0x00000000, 0x00003331, 0x00000000, 0x00004231, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52020, 0x00000000, 0x0005203f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943331, 0x00000000, 0x00054231, 0x00000000, 0x0000332d, 0x00000000, 0x0000422d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94332d, 0x00000000, 0x0005522d, 0x00000000, 0x00003331, 0x00000000, 0x00005231, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f2d, 0x00000000, 0x00054e2d, 0x00000000, 0x00002f31, 0x00000000, 0x00004e31, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943331, 0x00000000, 0x00055231, 0x00000000, 0x0000332d, 0x00000000, 0x0000522d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f3e, 0x00000000, 0x00054e3e, 0x00000000, 0x00002f4d, 0x00000000, 0x00004e4d, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53c02, 0x00000000, 0x00052002, 0x00000000, 0x00003021, 0x00000000, 0x00002021, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142d0c, 0x00000000, 0x0005200c, 0x00000000, 0x00002d20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c143f2d, 0x00000000, 0x00053f20, 0x00000000, 0x00002d2d, 0x00000000, 0x00002d20, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c143f20, 0x00000000, 0x00053f0e, 0x00000000, 0x00002d20, 0x00000000, 0x00002d0e, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142f3f, 0x00000000, 0x00053e3f, 0x00000000, 0x00002f2d, 0x00000000, 0x00003e2d, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c14203f, 0x00000000, 0x00052d3f, 0x00000000, 0x0000202b, 0x00000000, 0x00002d2b, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c140e20, 0x00000000, 0x00050e2d, 0x00000000, 0x00002020, 0x00000000, 0x0000202d, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c14202d, 0x00000000, 0x0005203f, 0x00000000, 0x00002d2d, 0x00000000, 0x00002d3f, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c140e2d, 0x00000000, 0x00050e3f, 0x00000000, 0x0000202d, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142d3f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002d2b, 0x00000000, 0x00003f2b, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c143f20, 0x00000000, 0x00053f0c, 0x00000000, 0x00002b20, 0x00000000, 0x00002b0c, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c14200e, 0x00000000, 0x00050c0e, 0x00000000, 0x00002020, 0x00000000, 0x00000c20, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x00050c20, 0x00000000, 0x0000202d, 0x00000000, 0x00000c2d, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c14202d, 0x00000000, 0x00050c2d, 0x00000000, 0x00002020, 0x00000000, 0x00000c20, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142d2d, 0x00000000, 0x00052d3f, 0x00000000, 0x0000202d, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c143f2d, 0x00000000, 0x00053f3f, 0x00000000, 0x00002d2d, 0x00000000, 0x00002d3f, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c14203f, 0x00000000, 0x00050c3f, 0x00000000, 0x0000202d, 0x00000000, 0x00000c2d, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c140c20, 0x00000000, 0x00050c0c, 0x00000000, 0x00002020, 0x00000000, 0x0000200c, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142d0c, 0x00000000, 0x00053f0c, 0x00000000, 0x00002d20, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c143f20, 0x00000000, 0x00053f2d, 0x00000000, 0x00002d20, 0x00000000, 0x00002d2d, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c14200c, 0x00000000, 0x00052d0c, 0x00000000, 0x00002020, 0x00000000, 0x00002d20, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142b20, 0x00000000, 0x00053f20, 0x00000000, 0x00002b2d, 0x00000000, 0x00003f2d, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005200e, 0x00000000, 0x00002d20, 0x00000000, 0x00002d0e, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c140e20, 0x00000000, 0x00050e0e, 0x00000000, 0x00002020, 0x00000000, 0x0000200e, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142b0e, 0x00000000, 0x00053f0e, 0x00000000, 0x00002b20, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c143f0c, 0x00000000, 0x00053f20, 0x00000000, 0x00002b0c, 0x00000000, 0x00002b20, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c143f3f, 0x00000000, 0x00052d3f, 0x00000000, 0x00003f2b, 0x00000000, 0x00002d2b, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c140e2d, 0x00000000, 0x00050e20, 0x00000000, 0x0000202d, 0x00000000, 0x00002020, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142d3f, 0x00000000, 0x0005203f, 0x00000000, 0x00002d2b, 0x00000000, 0x0000202b, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b20, 0x00000000, 0x00052b2f, 0x00000000, 0x00001c20, 0x00000000, 0x00001c2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b2f, 0x00000000, 0x00052b3f, 0x00000000, 0x00000c2f, 0x00000000, 0x00000c3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x00052f20, 0x00000000, 0x0000202f, 0x00000000, 0x00002f2f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f20, 0x00000000, 0x00054e20, 0x00000000, 0x00002f2f, 0x00000000, 0x00004e2f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f20, 0x00000000, 0x00053f20, 0x00000000, 0x00002f2f, 0x00000000, 0x00003f2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f23, 0x00000000, 0x00054e23, 0x00000000, 0x00002f33, 0x00000000, 0x00004e33, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f23, 0x00000000, 0x00053f23, 0x00000000, 0x00002f33, 0x00000000, 0x00003f33, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c16203e, 0x00000000, 0x00052f3e, 0x00000000, 0x0000204d, 0x00000000, 0x00002f4d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b10, 0x00000000, 0x00052b2f, 0x00000000, 0x00001c10, 0x00000000, 0x00001c2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942031, 0x00000000, 0x00052f31, 0x00000000, 0x0000202d, 0x00000000, 0x00002f2d, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52f20, 0x00000000, 0x00053f20, 0x00000000, 0x00002f3f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94202d, 0x00000000, 0x00052f2d, 0x00000000, 0x00002031, 0x00000000, 0x00002f31, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94332d, 0x00000000, 0x0005422d, 0x00000000, 0x00003331, 0x00000000, 0x00004231, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972020, 0x00000000, 0x0005203f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943331, 0x00000000, 0x00054231, 0x00000000, 0x0000332d, 0x00000000, 0x0000422d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b20, 0x00000000, 0x00052b2f, 0x00000000, 0x00001c20, 0x00000000, 0x00001c2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c2f, 0x00000000, 0x00051c3f, 0x00000000, 0x00000c2f, 0x00000000, 0x00000c3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942033, 0x00000000, 0x00052f33, 0x00000000, 0x00002042, 0x00000000, 0x00002f42, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f33, 0x00000000, 0x00054e33, 0x00000000, 0x00002f42, 0x00000000, 0x00004e42, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f2e, 0x00000000, 0x00054e2e, 0x00000000, 0x00002f3e, 0x00000000, 0x00004e3e, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f2e, 0x00000000, 0x00053f2e, 0x00000000, 0x00002f3e, 0x00000000, 0x00003f3e, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f2e, 0x00000000, 0x00053f2e, 0x00000000, 0x00002f4d, 0x00000000, 0x00003f4d, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f3e, 0x00000000, 0x00053f3e, 0x00000000, 0x00002f4d, 0x00000000, 0x00003f4d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b2f, 0x00000000, 0x00052b3f, 0x00000000, 0x00001c2f, 0x00000000, 0x00001c3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b2f, 0x00000000, 0x00052b3f, 0x00000000, 0x00000c2f, 0x00000000, 0x00000c3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b2f, 0x00000000, 0x00052b3f, 0x00000000, 0x00000c2f, 0x00000000, 0x00000c3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b2f, 0x00000000, 0x00052b3f, 0x00000000, 0x00000c2f, 0x00000000, 0x00000c3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f30, 0x00000000, 0x00053f30, 0x00000000, 0x00002f4f, 0x00000000, 0x00003f4f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b20, 0x00000000, 0x00052b2f, 0x00000000, 0x00000c20, 0x00000000, 0x00000c2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b20, 0x00000000, 0x00052b2f, 0x00000000, 0x00000c20, 0x00000000, 0x00000c2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b20, 0x00000000, 0x00052b2f, 0x00000000, 0x00000c20, 0x00000000, 0x00000c2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c20, 0x00000000, 0x00051c2f, 0x00000000, 0x00000c20, 0x00000000, 0x00000c2f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162030, 0x00000000, 0x00052f30, 0x00000000, 0x0000203f, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f33, 0x00000000, 0x00053f33, 0x00000000, 0x00002f42, 0x00000000, 0x00003f42, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f33, 0x00000000, 0x00054e33, 0x00000000, 0x00002f42, 0x00000000, 0x00004e42, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942033, 0x00000000, 0x00052f33, 0x00000000, 0x00002042, 0x00000000, 0x00002f42, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f31, 0x00000000, 0x00053f31, 0x00000000, 0x00002f2d, 0x00000000, 0x00003f2d, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972020, 0x00000000, 0x00052f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f2d, 0x00000000, 0x00053f2d, 0x00000000, 0x00002f31, 0x00000000, 0x00003f31, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942031, 0x00000000, 0x00052f31, 0x00000000, 0x0000202d, 0x00000000, 0x00002f2d, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972f20, 0x00000000, 0x00053f20, 0x00000000, 0x00002f3f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94202d, 0x00000000, 0x00052f2d, 0x00000000, 0x00002031, 0x00000000, 0x00002f31, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f20, 0x00000000, 0x00053f20, 0x00000000, 0x00002f30, 0x00000000, 0x00003f30, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f20, 0x00000000, 0x00054e20, 0x00000000, 0x00002f30, 0x00000000, 0x00004e30, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f31, 0x00000000, 0x00053f31, 0x00000000, 0x00002f2d, 0x00000000, 0x00003f2d, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52020, 0x00000000, 0x00052f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f2d, 0x00000000, 0x00053f2d, 0x00000000, 0x00002f31, 0x00000000, 0x00003f31, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x00052f20, 0x00000000, 0x00002030, 0x00000000, 0x00002f30, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f23, 0x00000000, 0x00053f23, 0x00000000, 0x00002f33, 0x00000000, 0x00003f33, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f23, 0x00000000, 0x00054e23, 0x00000000, 0x00002f33, 0x00000000, 0x00004e33, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942023, 0x00000000, 0x00052f23, 0x00000000, 0x00002033, 0x00000000, 0x00002f33, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c2f, 0x00000000, 0x00051c3f, 0x00000000, 0x00000c2f, 0x00000000, 0x00000c3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f30, 0x00000000, 0x00053f30, 0x00000000, 0x00002f3f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94332d, 0x00000000, 0x0005422d, 0x00000000, 0x00003331, 0x00000000, 0x00004231, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52020, 0x00000000, 0x0005203f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943331, 0x00000000, 0x00054231, 0x00000000, 0x0000332d, 0x00000000, 0x0000422d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f33, 0x00000000, 0x00053f33, 0x00000000, 0x00002f42, 0x00000000, 0x00003f42, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94232d, 0x00000000, 0x0005332d, 0x00000000, 0x00002331, 0x00000000, 0x00003331, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52f20, 0x00000000, 0x00052f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942331, 0x00000000, 0x00053331, 0x00000000, 0x0000232d, 0x00000000, 0x0000332d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b20, 0x00000000, 0x00052b2f, 0x00000000, 0x00000c20, 0x00000000, 0x00000c2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c20, 0x00000000, 0x00051c2f, 0x00000000, 0x00000c20, 0x00000000, 0x00000c2f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c16202f, 0x00000000, 0x00052f2f, 0x00000000, 0x0000203f, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c16202f, 0x00000000, 0x00052f2f, 0x00000000, 0x0000204e, 0x00000000, 0x00002f4e, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94332d, 0x00000000, 0x0005522d, 0x00000000, 0x00003331, 0x00000000, 0x00005231, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f31, 0x00000000, 0x00054e31, 0x00000000, 0x00002f2d, 0x00000000, 0x00004e2d, 
		0x00000000, 0xe204139c, 0x2d808080, 0x00000000, 0x3d163f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941010, 0x00000000, 0x0005102f, 0x00000000, 0x00002310, 0x00000000, 0x0000232f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c940c10, 0x00000000, 0x00050c2f, 0x00000000, 0x00001c10, 0x00000000, 0x00001c2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b10, 0x00000000, 0x00052b2f, 0x00000000, 0x00001c10, 0x00000000, 0x00001c2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c10, 0x00000000, 0x00051c2f, 0x00000000, 0x00002b10, 0x00000000, 0x00002b2f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c16202e, 0x00000000, 0x00052f2e, 0x00000000, 0x0000203e, 0x00000000, 0x00002f3e, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f31, 0x00000000, 0x00053f31, 0x00000000, 0x00002f2d, 0x00000000, 0x00003f2d, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972020, 0x00000000, 0x00052f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f2d, 0x00000000, 0x00053f2d, 0x00000000, 0x00002f31, 0x00000000, 0x00003f31, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f2f, 0x00000000, 0x00053f2f, 0x00000000, 0x00002f3f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942023, 0x00000000, 0x00052f23, 0x00000000, 0x00002033, 0x00000000, 0x00002f33, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941010, 0x00000000, 0x0005102f, 0x00000000, 0x00002310, 0x00000000, 0x0000232f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c940c10, 0x00000000, 0x00050c2f, 0x00000000, 0x00002b10, 0x00000000, 0x00002b2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c940c2f, 0x00000000, 0x00050c3f, 0x00000000, 0x00002b2f, 0x00000000, 0x00002b3f, 
},
{
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c14203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c152020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c143f20, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c152020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c152020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c152020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c152020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c152020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c152020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c152020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f20, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f20, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f20, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f20, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f20, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f20, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f20, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f20, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c143f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202039c, 0x2d808080, 0x00000000, 0x3c573f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202039c, 0x2d808080, 0x00000000, 0x3c573f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202039c, 0x2d808080, 0x00000000, 0x3c573f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202039c, 0x2d808080, 0x00000000, 0x3c573f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c553f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15203f, 0x00000000, 0x0005273f, 0x00000000, 0x00002020, 0x00000000, 0x00002720, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c54303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c542f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15203f, 0x00000000, 0x0005273f, 0x00000000, 0x00002020, 0x00000000, 0x00002720, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c544e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c17203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c17203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c544f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c152720, 0x00000000, 0x00052020, 0x00000000, 0x0000273f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c152720, 0x00000000, 0x00052020, 0x00000000, 0x0000273f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd5203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c54303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c542f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd4203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd42020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c544f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd5203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd5203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c544e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c54303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c542f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd4203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd42020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c544f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd4203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd4203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c544e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c54303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c542f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c97203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c544f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd4203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd4203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c544e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd63f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c54303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c542f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c544f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd4203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd4203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c544e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd63f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd63f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c54303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c542f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c544f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c97203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c97203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202139c, 0x2d808080, 0x00000000, 0x3c544e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd63f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd5203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd61013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd4203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd61013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd42020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd4203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd61013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd42020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c97203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd61013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd63f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd61013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd63f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd63f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd61013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd63f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd63f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd61013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd63f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0d, 0x00000000, 0x00052f13, 0x00000000, 0x0000100d, 0x00000000, 0x00001013, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd63f3f, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100b, 0x00000000, 0x00051013, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56303f, 0x00000000, 0x00053020, 0x00000000, 0x00004f3f, 0x00000000, 0x00004f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562f3f, 0x00000000, 0x00052f20, 0x00000000, 0x00004e3f, 0x00000000, 0x00004e20, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f3f, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x0000100d, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd61013, 0x00000000, 0x0005100b, 0x00000000, 0x00002f13, 0x00000000, 0x00002f0b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f13, 0x00000000, 0x00052f0b, 0x00000000, 0x00001013, 0x00000000, 0x0000100b, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00052f0d, 0x00000000, 0x00001013, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c173f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564f20, 0x00000000, 0x00054f3f, 0x00000000, 0x00003020, 0x00000000, 0x0000303f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00052020, 0x00000000, 0x00003f3f, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c564e20, 0x00000000, 0x00054e3f, 0x00000000, 0x00002f20, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd62f0b, 0x00000000, 0x00052f13, 0x00000000, 0x0000100b, 0x00000000, 0x00001013, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd63f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200239c, 0x2d808080, 0x00000000, 0x3cd6100d, 0x00000000, 0x00051013, 0x00000000, 0x00002f0d, 0x00000000, 0x00002f13, 
		0x00000000, 0xe202039c, 0x2d808080, 0x00000000, 0x3c572020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe202039c, 0x2d808080, 0x00000000, 0x3c572020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202439c, 0x2d808080, 0x00000000, 0x3c172020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202339c, 0x2d808080, 0x00000000, 0x3c552020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951c01, 0x00000000, 0x00051c3e, 0x00000000, 0x00002001, 0x00000000, 0x0000203e, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c152020, 0x00000000, 0x0005202f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f2f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15202f, 0x00000000, 0x00052042, 0x00000000, 0x00003f2f, 0x00000000, 0x00003f42, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c152020, 0x00000000, 0x0005202f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f2f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15202f, 0x00000000, 0x00052042, 0x00000000, 0x00003f2f, 0x00000000, 0x00003f42, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142f2d, 0x00000000, 0x00053f2d, 0x00000000, 0x00002f20, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142d20, 0x00000000, 0x00052d0e, 0x00000000, 0x00002020, 0x00000000, 0x0000200e, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c140c10, 0x00000000, 0x00050c20, 0x00000000, 0x00002010, 0x00000000, 0x00002020, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c143f0c, 0x00000000, 0x00052d0c, 0x00000000, 0x00003f20, 0x00000000, 0x00002d20, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f10, 0x00000000, 0x00052010, 0x00000000, 0x00003f23, 0x00000000, 0x00002023, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f1c, 0x00000000, 0x0005201c, 0x00000000, 0x00003f2f, 0x00000000, 0x0000202f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f10, 0x00000000, 0x00052010, 0x00000000, 0x00003f23, 0x00000000, 0x00002023, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f1c, 0x00000000, 0x0005201c, 0x00000000, 0x00003f2f, 0x00000000, 0x0000202f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15203b, 0x00000000, 0x0005204e, 0x00000000, 0x00003f3b, 0x00000000, 0x00003f4e, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15202f, 0x00000000, 0x00052043, 0x00000000, 0x00003f2f, 0x00000000, 0x00003f43, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15203b, 0x00000000, 0x0005204e, 0x00000000, 0x00003f3b, 0x00000000, 0x00003f4e, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15202f, 0x00000000, 0x00052043, 0x00000000, 0x00003f2f, 0x00000000, 0x00003f43, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15203b, 0x00000000, 0x0005204e, 0x00000000, 0x00003f3b, 0x00000000, 0x00003f4e, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15202f, 0x00000000, 0x00052043, 0x00000000, 0x00003f2f, 0x00000000, 0x00003f43, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15203b, 0x00000000, 0x0005204e, 0x00000000, 0x00003f3b, 0x00000000, 0x00003f4e, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15202f, 0x00000000, 0x00052043, 0x00000000, 0x00003f2f, 0x00000000, 0x00003f43, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f10, 0x00000000, 0x00052010, 0x00000000, 0x00003f23, 0x00000000, 0x00002023, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f10, 0x00000000, 0x00052010, 0x00000000, 0x00003f23, 0x00000000, 0x00002023, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f1b, 0x00000000, 0x0005201b, 0x00000000, 0x00003f2f, 0x00000000, 0x0000202f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c153f1b, 0x00000000, 0x0005201b, 0x00000000, 0x00003f2f, 0x00000000, 0x0000202f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15201c, 0x00000000, 0x0005202f, 0x00000000, 0x00003f1c, 0x00000000, 0x00003f2f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15201c, 0x00000000, 0x0005202f, 0x00000000, 0x00003f1c, 0x00000000, 0x00003f2f, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15202f, 0x00000000, 0x00052042, 0x00000000, 0x00003f2f, 0x00000000, 0x00003f42, 
		0x00000000, 0xe202639c, 0x2d808080, 0x00000000, 0x3c15202f, 0x00000000, 0x00052042, 0x00000000, 0x00003f2f, 0x00000000, 0x00003f42, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c95103f, 0x00000000, 0x00051020, 0x00000000, 0x0000083f, 0x00000000, 0x00000820, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c95103f, 0x00000000, 0x00051020, 0x00000000, 0x0000083f, 0x00000000, 0x00000820, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950818, 0x00000000, 0x00050820, 0x00000000, 0x00001018, 0x00000000, 0x00001020, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f18, 0x00000000, 0x00053f20, 0x00000000, 0x00002018, 0x00000000, 0x00002020, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952018, 0x00000000, 0x00052020, 0x00000000, 0x00003f18, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951018, 0x00000000, 0x00051020, 0x00000000, 0x00000818, 0x00000000, 0x00000820, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950818, 0x00000000, 0x00050820, 0x00000000, 0x00001018, 0x00000000, 0x00001020, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c95103f, 0x00000000, 0x00051020, 0x00000000, 0x0000083f, 0x00000000, 0x00000820, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c95083f, 0x00000000, 0x00050820, 0x00000000, 0x0000103f, 0x00000000, 0x00001020, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951018, 0x00000000, 0x00051020, 0x00000000, 0x00000818, 0x00000000, 0x00000820, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x00050820, 0x00000000, 0x0000103f, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950818, 0x00000000, 0x00050820, 0x00000000, 0x00001018, 0x00000000, 0x00001020, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f18, 0x00000000, 0x00053f20, 0x00000000, 0x00002018, 0x00000000, 0x00002020, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952018, 0x00000000, 0x00052020, 0x00000000, 0x00003f18, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951018, 0x00000000, 0x00051020, 0x00000000, 0x00000818, 0x00000000, 0x00000820, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c95083f, 0x00000000, 0x00050820, 0x00000000, 0x0000103f, 0x00000000, 0x00001020, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c95083f, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x00001020, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c95083f, 0x00000000, 0x00050820, 0x00000000, 0x0000103f, 0x00000000, 0x00001020, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x00050820, 0x00000000, 0x0000103f, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c95083f, 0x00000000, 0x00050820, 0x00000000, 0x0000103f, 0x00000000, 0x00001020, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x00051027, 0x00000000, 0x00000820, 0x00000000, 0x00000827, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x00050820, 0x00000000, 0x0000103f, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x00050827, 0x00000000, 0x00001020, 0x00000000, 0x00001027, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f27, 0x00000000, 0x00002020, 0x00000000, 0x00002027, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x00052027, 0x00000000, 0x00003f20, 0x00000000, 0x00003f27, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x00051027, 0x00000000, 0x00000820, 0x00000000, 0x00000827, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x00050827, 0x00000000, 0x00001020, 0x00000000, 0x00001027, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c95103f, 0x00000000, 0x00051020, 0x00000000, 0x0000083f, 0x00000000, 0x00000820, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x0005103f, 0x00000000, 0x00000820, 0x00000000, 0x0000083f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x00050827, 0x00000000, 0x00001020, 0x00000000, 0x00001027, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c953f20, 0x00000000, 0x00053f27, 0x00000000, 0x00002020, 0x00000000, 0x00002027, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952020, 0x00000000, 0x00052027, 0x00000000, 0x00003f20, 0x00000000, 0x00003f27, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x00051027, 0x00000000, 0x00000820, 0x00000000, 0x00000827, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c950820, 0x00000000, 0x0005083f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943b04, 0x00000000, 0x00053b23, 0x00000000, 0x00001c04, 0x00000000, 0x00001c23, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c20, 0x00000000, 0x00051c3f, 0x00000000, 0x00003b20, 0x00000000, 0x00003b3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942320, 0x00000000, 0x0005233f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f08, 0x00000000, 0x00050408, 0x00000000, 0x00002f0a, 0x00000000, 0x0000040a, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f2a, 0x00000000, 0x00052f2f, 0x00000000, 0x0000042a, 0x00000000, 0x0000042f, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f2f, 0x00000000, 0x00052f34, 0x00000000, 0x0000042f, 0x00000000, 0x00000434, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d150408, 0x00000000, 0x00052f08, 0x00000000, 0x0000040a, 0x00000000, 0x00002f0a, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f27, 0x00000000, 0x00052f29, 0x00000000, 0x00001027, 0x00000000, 0x00001029, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15102a, 0x00000000, 0x0005102f, 0x00000000, 0x00002f2a, 0x00000000, 0x00002f2f, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15102f, 0x00000000, 0x00051034, 0x00000000, 0x00002f2f, 0x00000000, 0x00002f34, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f27, 0x00000000, 0x00051027, 0x00000000, 0x00002f29, 0x00000000, 0x00001029, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f08, 0x00000000, 0x00050408, 0x00000000, 0x00002f0a, 0x00000000, 0x0000040a, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f0b, 0x00000000, 0x00052f10, 0x00000000, 0x0000040b, 0x00000000, 0x00000410, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f10, 0x00000000, 0x00052f15, 0x00000000, 0x00000410, 0x00000000, 0x00000415, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d150408, 0x00000000, 0x00052f08, 0x00000000, 0x0000040a, 0x00000000, 0x00002f0a, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f27, 0x00000000, 0x00052f29, 0x00000000, 0x00001027, 0x00000000, 0x00001029, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15100b, 0x00000000, 0x00051010, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f10, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d151010, 0x00000000, 0x00051015, 0x00000000, 0x00002f10, 0x00000000, 0x00002f15, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f27, 0x00000000, 0x00051027, 0x00000000, 0x00002f29, 0x00000000, 0x00001029, 
		0x00000000, 0xe200639c, 0x2d808080, 0x00000000, 0x3cd71c20, 0x00000000, 0x00051c3e, 0x00000000, 0x00003520, 0x00000000, 0x0000353e, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951b0d, 0x00000000, 0x00051b32, 0x00000000, 0x00001f0d, 0x00000000, 0x00001f32, 
		0x00000000, 0xe200639c, 0x2d808080, 0x00000000, 0x3cd73520, 0x00000000, 0x0005353e, 0x00000000, 0x00001c20, 0x00000000, 0x00001c3e, 
		0x00000000, 0xe2080318, 0x2d808080, 0x00000000, 0x3c967d40, 0x00000000, 0x00057d46, 0x00000000, 0x00003f40, 0x00000000, 0x00003f46, 
		0x00000000, 0xe2080318, 0x2d808080, 0x00000000, 0x3c963f40, 0x00000000, 0x00053f7e, 0x00000000, 0x00007d40, 0x00000000, 0x00007d7e, 
		0x00000000, 0xe2080318, 0x2d808080, 0x00000000, 0x3c963940, 0x00000000, 0x0005397e, 0x00000000, 0x00003340, 0x00000000, 0x0000337e, 
		0x00000000, 0xe2080318, 0x2d808080, 0x00000000, 0x3c963340, 0x00000000, 0x0005337e, 0x00000000, 0x00003940, 0x00000000, 0x0000397e, 
		0x00000000, 0xe2080318, 0x2d808080, 0x00000000, 0x3c967d40, 0x00000000, 0x00057d7e, 0x00000000, 0x00003f40, 0x00000000, 0x00003f7e, 
		0x00000000, 0xe2080318, 0x2d808080, 0x00000000, 0x3c963f40, 0x00000000, 0x00053f46, 0x00000000, 0x00007d40, 0x00000000, 0x00007d46, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943b23, 0x00000000, 0x00053b42, 0x00000000, 0x00001c23, 0x00000000, 0x00001c42, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c20, 0x00000000, 0x00051c3f, 0x00000000, 0x00003b20, 0x00000000, 0x00003b3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942320, 0x00000000, 0x0005233f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943b04, 0x00000000, 0x00053b14, 0x00000000, 0x00001c04, 0x00000000, 0x00001c14, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c20, 0x00000000, 0x00051c2f, 0x00000000, 0x00003b20, 0x00000000, 0x00003b2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94103f, 0x00000000, 0x00051020, 0x00000000, 0x0000233f, 0x00000000, 0x00002320, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94233f, 0x00000000, 0x00052320, 0x00000000, 0x0000103f, 0x00000000, 0x00001020, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943b33, 0x00000000, 0x00053b42, 0x00000000, 0x00001c33, 0x00000000, 0x00001c42, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c2f, 0x00000000, 0x00051c3f, 0x00000000, 0x00003b2f, 0x00000000, 0x00003b3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b33, 0x00000000, 0x00052b42, 0x00000000, 0x00001c33, 0x00000000, 0x00001c42, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c2f, 0x00000000, 0x00051c3f, 0x00000000, 0x00002b2f, 0x00000000, 0x00002b3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94102f, 0x00000000, 0x0005103f, 0x00000000, 0x0000232f, 0x00000000, 0x0000233f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c33, 0x00000000, 0x00051c42, 0x00000000, 0x00000c33, 0x00000000, 0x00000c42, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c940c2f, 0x00000000, 0x00050c3f, 0x00000000, 0x00001c2f, 0x00000000, 0x00001c3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941020, 0x00000000, 0x0005102f, 0x00000000, 0x00002320, 0x00000000, 0x0000232f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943b04, 0x00000000, 0x00053b14, 0x00000000, 0x00001c04, 0x00000000, 0x00001c14, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c20, 0x00000000, 0x00051c2f, 0x00000000, 0x00003b20, 0x00000000, 0x00003b2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943b04, 0x00000000, 0x00053b14, 0x00000000, 0x00001c04, 0x00000000, 0x00001c14, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c20, 0x00000000, 0x00051c2f, 0x00000000, 0x00003b20, 0x00000000, 0x00003b2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94234e, 0x00000000, 0x0005424e, 0x00000000, 0x0000232f, 0x00000000, 0x0000422f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94234e, 0x00000000, 0x0005424e, 0x00000000, 0x0000232f, 0x00000000, 0x0000422f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94234e, 0x00000000, 0x0005424e, 0x00000000, 0x0000232f, 0x00000000, 0x0000422f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94234e, 0x00000000, 0x0005424e, 0x00000000, 0x0000232f, 0x00000000, 0x0000422f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94234e, 0x00000000, 0x0005424e, 0x00000000, 0x0000232f, 0x00000000, 0x0000422f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94234e, 0x00000000, 0x0005424e, 0x00000000, 0x0000232f, 0x00000000, 0x0000422f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94234e, 0x00000000, 0x0005424e, 0x00000000, 0x0000232f, 0x00000000, 0x0000422f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94234e, 0x00000000, 0x0005424e, 0x00000000, 0x0000232f, 0x00000000, 0x0000422f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94232f, 0x00000000, 0x0005422f, 0x00000000, 0x0000234e, 0x00000000, 0x0000424e, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94232f, 0x00000000, 0x0005422f, 0x00000000, 0x0000234e, 0x00000000, 0x0000424e, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94232f, 0x00000000, 0x0005422f, 0x00000000, 0x0000234e, 0x00000000, 0x0000424e, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94232f, 0x00000000, 0x0005422f, 0x00000000, 0x0000234e, 0x00000000, 0x0000424e, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94232f, 0x00000000, 0x0005422f, 0x00000000, 0x0000234e, 0x00000000, 0x0000424e, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94232f, 0x00000000, 0x0005422f, 0x00000000, 0x0000234e, 0x00000000, 0x0000424e, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94232f, 0x00000000, 0x0005422f, 0x00000000, 0x0000234e, 0x00000000, 0x0000424e, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94232f, 0x00000000, 0x0005422f, 0x00000000, 0x0000234e, 0x00000000, 0x0000424e, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c163b20, 0x00000000, 0x00053b3f, 0x00000000, 0x00001c20, 0x00000000, 0x00001c3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c163b20, 0x00000000, 0x00053b3f, 0x00000000, 0x00001c20, 0x00000000, 0x00001c3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c163b20, 0x00000000, 0x00053b3f, 0x00000000, 0x00001c20, 0x00000000, 0x00001c3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c163b20, 0x00000000, 0x00053b3f, 0x00000000, 0x00001c20, 0x00000000, 0x00001c3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c163b20, 0x00000000, 0x00053b3f, 0x00000000, 0x00001c20, 0x00000000, 0x00001c3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c163b20, 0x00000000, 0x00053b3f, 0x00000000, 0x00001c20, 0x00000000, 0x00001c3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c163b20, 0x00000000, 0x00053b3f, 0x00000000, 0x00001c20, 0x00000000, 0x00001c3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c163b20, 0x00000000, 0x00053b3f, 0x00000000, 0x00001c20, 0x00000000, 0x00001c3f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952f20, 0x00000000, 0x00052f23, 0x00000000, 0x00001020, 0x00000000, 0x00001023, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c952f20, 0x00000000, 0x00052f23, 0x00000000, 0x00001020, 0x00000000, 0x00001023, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951c32, 0x00000000, 0x00051c3f, 0x00000000, 0x00002032, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951c20, 0x00000000, 0x00051c2c, 0x00000000, 0x00002020, 0x00000000, 0x0000202c, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x00051023, 0x00000000, 0x00002f20, 0x00000000, 0x00002f23, 
		0x00000000, 0xe200039c, 0x2d808080, 0x00000000, 0x3c951020, 0x00000000, 0x00051023, 0x00000000, 0x00002f20, 0x00000000, 0x00002f23, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f2b, 0x00000000, 0x00052f2d, 0x00000000, 0x0000082b, 0x00000000, 0x0000082d, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15080b, 0x00000000, 0x00050810, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f10, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d150810, 0x00000000, 0x00050815, 0x00000000, 0x00002f10, 0x00000000, 0x00002f15, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f2b, 0x00000000, 0x0005082b, 0x00000000, 0x00002f2d, 0x00000000, 0x0000082d, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f2b, 0x00000000, 0x00052f2d, 0x00000000, 0x0000082b, 0x00000000, 0x0000082d, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15082a, 0x00000000, 0x0005082f, 0x00000000, 0x00002f2a, 0x00000000, 0x00002f2f, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15082f, 0x00000000, 0x00050834, 0x00000000, 0x00002f2f, 0x00000000, 0x00002f34, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f2b, 0x00000000, 0x0005082b, 0x00000000, 0x00002f2d, 0x00000000, 0x0000082d, 
		0x00000000, 0xe2080318, 0x2d808080, 0x00000000, 0x3c960140, 0x00000000, 0x0005017e, 0x00000000, 0x00003f40, 0x00000000, 0x00003f7e, 
		0x00000000, 0xe200639c, 0x2d808080, 0x00000000, 0x3cd71c20, 0x00000000, 0x00051c3e, 0x00000000, 0x00003520, 0x00000000, 0x0000353e, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f27, 0x00000000, 0x00052f29, 0x00000000, 0x00001027, 0x00000000, 0x00001029, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15100b, 0x00000000, 0x00051010, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f10, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d151010, 0x00000000, 0x00051015, 0x00000000, 0x00002f10, 0x00000000, 0x00002f15, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f27, 0x00000000, 0x00051027, 0x00000000, 0x00002f29, 0x00000000, 0x00001029, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f27, 0x00000000, 0x00052f29, 0x00000000, 0x00001027, 0x00000000, 0x00001029, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15102a, 0x00000000, 0x0005102f, 0x00000000, 0x00002f2a, 0x00000000, 0x00002f2f, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15102f, 0x00000000, 0x00051034, 0x00000000, 0x00002f2f, 0x00000000, 0x00002f34, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f27, 0x00000000, 0x00051027, 0x00000000, 0x00002f29, 0x00000000, 0x00001029, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15272b, 0x00000000, 0x0005272d, 0x00000000, 0x0000102b, 0x00000000, 0x0000102d, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15100b, 0x00000000, 0x00051010, 0x00000000, 0x0000270b, 0x00000000, 0x00002710, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d151010, 0x00000000, 0x00051015, 0x00000000, 0x00002710, 0x00000000, 0x00002715, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15272b, 0x00000000, 0x0005102b, 0x00000000, 0x0000272d, 0x00000000, 0x0000102d, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15272b, 0x00000000, 0x0005272d, 0x00000000, 0x0000102b, 0x00000000, 0x0000102d, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15102a, 0x00000000, 0x0005102f, 0x00000000, 0x0000272a, 0x00000000, 0x0000272f, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15102f, 0x00000000, 0x00051034, 0x00000000, 0x0000272f, 0x00000000, 0x00002734, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15272b, 0x00000000, 0x0005102b, 0x00000000, 0x0000272d, 0x00000000, 0x0000102d, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563b20, 0x00000000, 0x00053f20, 0x00000000, 0x00003b3f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563b3f, 0x00000000, 0x00053f3f, 0x00000000, 0x00003b20, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56373f, 0x00000000, 0x00053b3f, 0x00000000, 0x00003720, 0x00000000, 0x00003b20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563720, 0x00000000, 0x00053b20, 0x00000000, 0x0000373f, 0x00000000, 0x00003b3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563b20, 0x00000000, 0x00055a20, 0x00000000, 0x00003b3f, 0x00000000, 0x00005a3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563b20, 0x00000000, 0x00055a20, 0x00000000, 0x00003b3f, 0x00000000, 0x00005a3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563b20, 0x00000000, 0x00055a20, 0x00000000, 0x00003b3f, 0x00000000, 0x00005a3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c562020, 0x00000000, 0x00053b20, 0x00000000, 0x0000203f, 0x00000000, 0x00003b3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x00003f20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x0005373f, 0x00000000, 0x00002020, 0x00000000, 0x00003720, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c56203f, 0x00000000, 0x00053b3f, 0x00000000, 0x00002020, 0x00000000, 0x00003b20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563b3f, 0x00000000, 0x00055a3f, 0x00000000, 0x00003b20, 0x00000000, 0x00005a20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563b3f, 0x00000000, 0x00055a3f, 0x00000000, 0x00003b20, 0x00000000, 0x00005a20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563b3f, 0x00000000, 0x00055a3f, 0x00000000, 0x00003b20, 0x00000000, 0x00005a20, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563b20, 0x00000000, 0x00055620, 0x00000000, 0x00003b3f, 0x00000000, 0x0000563f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563b20, 0x00000000, 0x00055a20, 0x00000000, 0x00003b3f, 0x00000000, 0x00005a3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c563b20, 0x00000000, 0x00055a20, 0x00000000, 0x00003b3f, 0x00000000, 0x00005a3f, 
		0x00000000, 0xe202239c, 0x2d808080, 0x00000000, 0x3c561c20, 0x00000000, 0x00053b20, 0x00000000, 0x00001c3f, 0x00000000, 0x00003b3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b2f, 0x00000000, 0x00052b3f, 0x00000000, 0x00001c2f, 0x00000000, 0x00001c3f, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f2b, 0x00000000, 0x00052f2d, 0x00000000, 0x0000042b, 0x00000000, 0x0000042d, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15040b, 0x00000000, 0x00050410, 0x00000000, 0x00002f0b, 0x00000000, 0x00002f10, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d150410, 0x00000000, 0x00050415, 0x00000000, 0x00002f10, 0x00000000, 0x00002f15, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f2b, 0x00000000, 0x0005042b, 0x00000000, 0x00002f2d, 0x00000000, 0x0000042d, 
		0x00000000, 0xe200639c, 0x2d808080, 0x00000000, 0x3cd70c20, 0x00000000, 0x00050c3e, 0x00000000, 0x00001620, 0x00000000, 0x0000163e, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f2b, 0x00000000, 0x00052f2d, 0x00000000, 0x0000042b, 0x00000000, 0x0000042d, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15042a, 0x00000000, 0x0005042f, 0x00000000, 0x00002f2a, 0x00000000, 0x00002f2f, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d15042f, 0x00000000, 0x00050434, 0x00000000, 0x00002f2f, 0x00000000, 0x00002f34, 
		0x00000000, 0xe204039c, 0x2d808080, 0x00000000, 0x3d152f2b, 0x00000000, 0x0005042b, 0x00000000, 0x00002f2d, 0x00000000, 0x0000042d, 
		0x00000000, 0xe2080318, 0x2d808080, 0x00000000, 0x3c963f40, 0x00000000, 0x00053f7e, 0x00000000, 0x00007d40, 0x00000000, 0x00007d7e, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002b21, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f21, 0x00000000, 0x00052021, 0x00000000, 0x00003f40, 0x00000000, 0x00002040, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f21, 0x00000000, 0x00052021, 0x00000000, 0x00003f40, 0x00000000, 0x00002040, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f21, 0x00000000, 0x00052021, 0x00000000, 0x00003f40, 0x00000000, 0x00002040, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f21, 0x00000000, 0x00052021, 0x00000000, 0x00003f40, 0x00000000, 0x00002040, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52021, 0x00000000, 0x00053321, 0x00000000, 0x00002002, 0x00000000, 0x00003f02, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52021, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00003f02, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972021, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00003f02, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52021, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00003f02, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972b21, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00003f02, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52021, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00003f02, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972021, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00003f02, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52021, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00003f02, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972021, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00003f02, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972021, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00003f02, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002b21, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f02, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972021, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00003f02, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52021, 0x00000000, 0x00052002, 0x00000000, 0x00003f21, 0x00000000, 0x00003f02, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f40, 0x00000000, 0x00052040, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f40, 0x00000000, 0x00052040, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f40, 0x00000000, 0x00052040, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53f40, 0x00000000, 0x00052040, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f40, 0x00000000, 0x00052040, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53340, 0x00000000, 0x00052040, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f40, 0x00000000, 0x00052040, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943f29, 0x00000000, 0x00053f2d, 0x00000000, 0x00002029, 0x00000000, 0x0000202d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942021, 0x00000000, 0x00052025, 0x00000000, 0x00003f21, 0x00000000, 0x00003f25, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c3d, 0x00000000, 0x00051c40, 0x00000000, 0x0000183d, 0x00000000, 0x00001840, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94183d, 0x00000000, 0x00051840, 0x00000000, 0x00001c3d, 0x00000000, 0x00001c40, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943f3a, 0x00000000, 0x00053f3e, 0x00000000, 0x0000203a, 0x00000000, 0x0000203e, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942021, 0x00000000, 0x00052025, 0x00000000, 0x00003f21, 0x00000000, 0x00003f25, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f23, 0x00000000, 0x00052f33, 0x00000000, 0x00002323, 0x00000000, 0x00002327, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162320, 0x00000000, 0x00052323, 0x00000000, 0x00002f20, 0x00000000, 0x00002f2f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c161c20, 0x00000000, 0x00051c2f, 0x00000000, 0x00000c20, 0x00000000, 0x00000c2f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c161820, 0x00000000, 0x00051823, 0x00000000, 0x00001c20, 0x00000000, 0x00001c23, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c16202f, 0x00000000, 0x0005203f, 0x00000000, 0x00002b2f, 0x00000000, 0x00002b33, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f33, 0x00000000, 0x00052b33, 0x00000000, 0x00002f3f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f14, 0x00000000, 0x00052f04, 0x00000000, 0x00002308, 0x00000000, 0x00002304, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162b2f, 0x00000000, 0x00052b33, 0x00000000, 0x0000202f, 0x00000000, 0x0000203f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162b20, 0x00000000, 0x00052b2f, 0x00000000, 0x00003b20, 0x00000000, 0x00003b2f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f20, 0x00000000, 0x00052f2f, 0x00000000, 0x00002320, 0x00000000, 0x00002323, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162b33, 0x00000000, 0x00052f33, 0x00000000, 0x0000203f, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943f0e, 0x00000000, 0x00053f0a, 0x00000000, 0x0000200e, 0x00000000, 0x0000200a, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94203a, 0x00000000, 0x0005203e, 0x00000000, 0x00003f3a, 0x00000000, 0x00003f3e, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943f21, 0x00000000, 0x00053f25, 0x00000000, 0x00002021, 0x00000000, 0x00002025, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942006, 0x00000000, 0x00052002, 0x00000000, 0x00003f06, 0x00000000, 0x00003f02, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f20, 0x00000000, 0x00052020, 0x00000000, 0x00002f14, 0x00000000, 0x00002b14, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162323, 0x00000000, 0x00052320, 0x00000000, 0x00002f2f, 0x00000000, 0x00002f20, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c161c2f, 0x00000000, 0x00051c20, 0x00000000, 0x00000c2f, 0x00000000, 0x00000c20, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c161823, 0x00000000, 0x00051820, 0x00000000, 0x00001c23, 0x00000000, 0x00001c20, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x00052010, 0x00000000, 0x00002b14, 0x00000000, 0x00002b10, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162323, 0x00000000, 0x00052327, 0x00000000, 0x00002f23, 0x00000000, 0x00002f33, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x00052f20, 0x00000000, 0x00002b14, 0x00000000, 0x00002f14, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162b14, 0x00000000, 0x00052b10, 0x00000000, 0x00002020, 0x00000000, 0x00002010, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162b2f, 0x00000000, 0x00052b20, 0x00000000, 0x00003b2f, 0x00000000, 0x00003b20, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c163b23, 0x00000000, 0x00053b20, 0x00000000, 0x00003723, 0x00000000, 0x00003720, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f2f, 0x00000000, 0x00052f20, 0x00000000, 0x00002323, 0x00000000, 0x00002320, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162308, 0x00000000, 0x00052304, 0x00000000, 0x00002f14, 0x00000000, 0x00002f04, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f40, 0x00000000, 0x00052b40, 0x00000000, 0x00003f21, 0x00000000, 0x00002021, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52021, 0x00000000, 0x00052002, 0x00000000, 0x00003321, 0x00000000, 0x00003f02, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94332d, 0x00000000, 0x0005522d, 0x00000000, 0x00003331, 0x00000000, 0x00005231, 
		0x00000000, 0xe204139c, 0x2d808080, 0x00000000, 0x3d163f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f2d, 0x00000000, 0x00054e2d, 0x00000000, 0x00002f31, 0x00000000, 0x00004e31, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f31, 0x00000000, 0x00054e31, 0x00000000, 0x00002f2d, 0x00000000, 0x00004e2d, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd42020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f2d, 0x00000000, 0x00054e2d, 0x00000000, 0x00002f31, 0x00000000, 0x00004e31, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942031, 0x00000000, 0x00052f31, 0x00000000, 0x0000202d, 0x00000000, 0x00002f2d, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52f20, 0x00000000, 0x00053f20, 0x00000000, 0x00002f3f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94202d, 0x00000000, 0x00052f2d, 0x00000000, 0x00002031, 0x00000000, 0x00002f31, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f31, 0x00000000, 0x00054e31, 0x00000000, 0x00002f2d, 0x00000000, 0x00004e2d, 
		0x00000000, 0xe204139c, 0x2d808080, 0x00000000, 0x3d163f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943331, 0x00000000, 0x00055231, 0x00000000, 0x0000332d, 0x00000000, 0x0000522d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94232d, 0x00000000, 0x0005332d, 0x00000000, 0x00002331, 0x00000000, 0x00003331, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52f20, 0x00000000, 0x00052f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942331, 0x00000000, 0x00053331, 0x00000000, 0x0000232d, 0x00000000, 0x0000332d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94332d, 0x00000000, 0x0005522d, 0x00000000, 0x00003331, 0x00000000, 0x00005231, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943331, 0x00000000, 0x00055231, 0x00000000, 0x0000332d, 0x00000000, 0x0000522d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94332d, 0x00000000, 0x0005522d, 0x00000000, 0x00003331, 0x00000000, 0x00005231, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943331, 0x00000000, 0x00055231, 0x00000000, 0x0000332d, 0x00000000, 0x0000522d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94332d, 0x00000000, 0x0005522d, 0x00000000, 0x00003331, 0x00000000, 0x00005231, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd43f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943331, 0x00000000, 0x00055231, 0x00000000, 0x0000332d, 0x00000000, 0x0000522d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94232d, 0x00000000, 0x0005332d, 0x00000000, 0x00002331, 0x00000000, 0x00003331, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972f20, 0x00000000, 0x00052f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942331, 0x00000000, 0x00053331, 0x00000000, 0x0000232d, 0x00000000, 0x0000332d, 
		0x00000000, 0xe204139c, 0x2d808080, 0x00000000, 0x3d163f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f2d, 0x00000000, 0x00054e2d, 0x00000000, 0x00002f31, 0x00000000, 0x00004e31, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943331, 0x00000000, 0x00055231, 0x00000000, 0x0000332d, 0x00000000, 0x0000522d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f31, 0x00000000, 0x00053f31, 0x00000000, 0x00002f2d, 0x00000000, 0x00003f2d, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52020, 0x00000000, 0x00052f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f2d, 0x00000000, 0x00053f2d, 0x00000000, 0x00002f31, 0x00000000, 0x00003f31, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f31, 0x00000000, 0x00054e31, 0x00000000, 0x00002f2d, 0x00000000, 0x00004e2d, 
		0x00000000, 0xe200439c, 0x2d808080, 0x00000000, 0x3cd42020, 0x00000000, 0x00053f20, 0x00000000, 0x0000203f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f2d, 0x00000000, 0x00054e2d, 0x00000000, 0x00002f31, 0x00000000, 0x00004e31, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942031, 0x00000000, 0x00052f31, 0x00000000, 0x0000202d, 0x00000000, 0x00002f2d, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972f20, 0x00000000, 0x00053f20, 0x00000000, 0x00002f3f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94202d, 0x00000000, 0x00052f2d, 0x00000000, 0x00002031, 0x00000000, 0x00002f31, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94332d, 0x00000000, 0x0005422d, 0x00000000, 0x00003331, 0x00000000, 0x00004231, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52020, 0x00000000, 0x0005203f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943331, 0x00000000, 0x00054231, 0x00000000, 0x0000332d, 0x00000000, 0x0000422d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94332d, 0x00000000, 0x0005522d, 0x00000000, 0x00003331, 0x00000000, 0x00005231, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c973f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f2d, 0x00000000, 0x00054e2d, 0x00000000, 0x00002f31, 0x00000000, 0x00004e31, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943331, 0x00000000, 0x00055231, 0x00000000, 0x0000332d, 0x00000000, 0x0000522d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f3e, 0x00000000, 0x00054e3e, 0x00000000, 0x00002f4d, 0x00000000, 0x00004e4d, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd53c02, 0x00000000, 0x00052002, 0x00000000, 0x00003021, 0x00000000, 0x00002021, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142d0c, 0x00000000, 0x0005200c, 0x00000000, 0x00002d20, 0x00000000, 0x00002020, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c143f2d, 0x00000000, 0x00053f20, 0x00000000, 0x00002d2d, 0x00000000, 0x00002d20, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c143f20, 0x00000000, 0x00053f0e, 0x00000000, 0x00002d20, 0x00000000, 0x00002d0e, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142f3f, 0x00000000, 0x00053e3f, 0x00000000, 0x00002f2d, 0x00000000, 0x00003e2d, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c14203f, 0x00000000, 0x00052d3f, 0x00000000, 0x0000202b, 0x00000000, 0x00002d2b, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c140e20, 0x00000000, 0x00050e2d, 0x00000000, 0x00002020, 0x00000000, 0x0000202d, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c14202d, 0x00000000, 0x0005203f, 0x00000000, 0x00002d2d, 0x00000000, 0x00002d3f, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c140e2d, 0x00000000, 0x00050e3f, 0x00000000, 0x0000202d, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142d3f, 0x00000000, 0x00053f3f, 0x00000000, 0x00002d2b, 0x00000000, 0x00003f2b, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c143f20, 0x00000000, 0x00053f0c, 0x00000000, 0x00002b20, 0x00000000, 0x00002b0c, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c14200e, 0x00000000, 0x00050c0e, 0x00000000, 0x00002020, 0x00000000, 0x00000c20, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x00050c20, 0x00000000, 0x0000202d, 0x00000000, 0x00000c2d, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c14202d, 0x00000000, 0x00050c2d, 0x00000000, 0x00002020, 0x00000000, 0x00000c20, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142d2d, 0x00000000, 0x00052d3f, 0x00000000, 0x0000202d, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c143f2d, 0x00000000, 0x00053f3f, 0x00000000, 0x00002d2d, 0x00000000, 0x00002d3f, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c14203f, 0x00000000, 0x00050c3f, 0x00000000, 0x0000202d, 0x00000000, 0x00000c2d, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c140c20, 0x00000000, 0x00050c0c, 0x00000000, 0x00002020, 0x00000000, 0x0000200c, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142d0c, 0x00000000, 0x00053f0c, 0x00000000, 0x00002d20, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c143f20, 0x00000000, 0x00053f2d, 0x00000000, 0x00002d20, 0x00000000, 0x00002d2d, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c14200c, 0x00000000, 0x00052d0c, 0x00000000, 0x00002020, 0x00000000, 0x00002d20, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142b20, 0x00000000, 0x00053f20, 0x00000000, 0x00002b2d, 0x00000000, 0x00003f2d, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005200e, 0x00000000, 0x00002d20, 0x00000000, 0x00002d0e, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c140e20, 0x00000000, 0x00050e0e, 0x00000000, 0x00002020, 0x00000000, 0x0000200e, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142b0e, 0x00000000, 0x00053f0e, 0x00000000, 0x00002b20, 0x00000000, 0x00003f20, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c143f0c, 0x00000000, 0x00053f20, 0x00000000, 0x00002b0c, 0x00000000, 0x00002b20, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c143f3f, 0x00000000, 0x00052d3f, 0x00000000, 0x00003f2b, 0x00000000, 0x00002d2b, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c140e2d, 0x00000000, 0x00050e20, 0x00000000, 0x0000202d, 0x00000000, 0x00002020, 
		0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142d3f, 0x00000000, 0x0005203f, 0x00000000, 0x00002d2b, 0x00000000, 0x0000202b, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b20, 0x00000000, 0x00052b2f, 0x00000000, 0x00001c20, 0x00000000, 0x00001c2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b2f, 0x00000000, 0x00052b3f, 0x00000000, 0x00000c2f, 0x00000000, 0x00000c3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x00052f20, 0x00000000, 0x0000202f, 0x00000000, 0x00002f2f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f20, 0x00000000, 0x00054e20, 0x00000000, 0x00002f2f, 0x00000000, 0x00004e2f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f20, 0x00000000, 0x00053f20, 0x00000000, 0x00002f2f, 0x00000000, 0x00003f2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f23, 0x00000000, 0x00054e23, 0x00000000, 0x00002f33, 0x00000000, 0x00004e33, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f23, 0x00000000, 0x00053f23, 0x00000000, 0x00002f33, 0x00000000, 0x00003f33, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c16203e, 0x00000000, 0x00052f3e, 0x00000000, 0x0000204d, 0x00000000, 0x00002f4d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b10, 0x00000000, 0x00052b2f, 0x00000000, 0x00001c10, 0x00000000, 0x00001c2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942031, 0x00000000, 0x00052f31, 0x00000000, 0x0000202d, 0x00000000, 0x00002f2d, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52f20, 0x00000000, 0x00053f20, 0x00000000, 0x00002f3f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94202d, 0x00000000, 0x00052f2d, 0x00000000, 0x00002031, 0x00000000, 0x00002f31, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94332d, 0x00000000, 0x0005422d, 0x00000000, 0x00003331, 0x00000000, 0x00004231, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972020, 0x00000000, 0x0005203f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943331, 0x00000000, 0x00054231, 0x00000000, 0x0000332d, 0x00000000, 0x0000422d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b20, 0x00000000, 0x00052b2f, 0x00000000, 0x00001c20, 0x00000000, 0x00001c2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c2f, 0x00000000, 0x00051c3f, 0x00000000, 0x00000c2f, 0x00000000, 0x00000c3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942033, 0x00000000, 0x00052f33, 0x00000000, 0x00002042, 0x00000000, 0x00002f42, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f33, 0x00000000, 0x00054e33, 0x00000000, 0x00002f42, 0x00000000, 0x00004e42, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f2e, 0x00000000, 0x00054e2e, 0x00000000, 0x00002f3e, 0x00000000, 0x00004e3e, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f2e, 0x00000000, 0x00053f2e, 0x00000000, 0x00002f3e, 0x00000000, 0x00003f3e, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f2e, 0x00000000, 0x00053f2e, 0x00000000, 0x00002f4d, 0x00000000, 0x00003f4d, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f3e, 0x00000000, 0x00053f3e, 0x00000000, 0x00002f4d, 0x00000000, 0x00003f4d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b2f, 0x00000000, 0x00052b3f, 0x00000000, 0x00001c2f, 0x00000000, 0x00001c3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b2f, 0x00000000, 0x00052b3f, 0x00000000, 0x00000c2f, 0x00000000, 0x00000c3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b2f, 0x00000000, 0x00052b3f, 0x00000000, 0x00000c2f, 0x00000000, 0x00000c3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b2f, 0x00000000, 0x00052b3f, 0x00000000, 0x00000c2f, 0x00000000, 0x00000c3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f30, 0x00000000, 0x00053f30, 0x00000000, 0x00002f4f, 0x00000000, 0x00003f4f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b20, 0x00000000, 0x00052b2f, 0x00000000, 0x00000c20, 0x00000000, 0x00000c2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b20, 0x00000000, 0x00052b2f, 0x00000000, 0x00000c20, 0x00000000, 0x00000c2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b20, 0x00000000, 0x00052b2f, 0x00000000, 0x00000c20, 0x00000000, 0x00000c2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c20, 0x00000000, 0x00051c2f, 0x00000000, 0x00000c20, 0x00000000, 0x00000c2f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162030, 0x00000000, 0x00052f30, 0x00000000, 0x0000203f, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f33, 0x00000000, 0x00053f33, 0x00000000, 0x00002f42, 0x00000000, 0x00003f42, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f33, 0x00000000, 0x00054e33, 0x00000000, 0x00002f42, 0x00000000, 0x00004e42, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942033, 0x00000000, 0x00052f33, 0x00000000, 0x00002042, 0x00000000, 0x00002f42, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f31, 0x00000000, 0x00053f31, 0x00000000, 0x00002f2d, 0x00000000, 0x00003f2d, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972020, 0x00000000, 0x00052f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f2d, 0x00000000, 0x00053f2d, 0x00000000, 0x00002f31, 0x00000000, 0x00003f31, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942031, 0x00000000, 0x00052f31, 0x00000000, 0x0000202d, 0x00000000, 0x00002f2d, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972f20, 0x00000000, 0x00053f20, 0x00000000, 0x00002f3f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94202d, 0x00000000, 0x00052f2d, 0x00000000, 0x00002031, 0x00000000, 0x00002f31, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f20, 0x00000000, 0x00053f20, 0x00000000, 0x00002f30, 0x00000000, 0x00003f30, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f20, 0x00000000, 0x00054e20, 0x00000000, 0x00002f30, 0x00000000, 0x00004e30, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f31, 0x00000000, 0x00053f31, 0x00000000, 0x00002f2d, 0x00000000, 0x00003f2d, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52020, 0x00000000, 0x00052f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f2d, 0x00000000, 0x00053f2d, 0x00000000, 0x00002f31, 0x00000000, 0x00003f31, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162020, 0x00000000, 0x00052f20, 0x00000000, 0x00002030, 0x00000000, 0x00002f30, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f23, 0x00000000, 0x00053f23, 0x00000000, 0x00002f33, 0x00000000, 0x00003f33, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f23, 0x00000000, 0x00054e23, 0x00000000, 0x00002f33, 0x00000000, 0x00004e33, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942023, 0x00000000, 0x00052f23, 0x00000000, 0x00002033, 0x00000000, 0x00002f33, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c2f, 0x00000000, 0x00051c3f, 0x00000000, 0x00000c2f, 0x00000000, 0x00000c3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f30, 0x00000000, 0x00053f30, 0x00000000, 0x00002f3f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94332d, 0x00000000, 0x0005422d, 0x00000000, 0x00003331, 0x00000000, 0x00004231, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52020, 0x00000000, 0x0005203f, 0x00000000, 0x00001020, 0x00000000, 0x0000103f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c943331, 0x00000000, 0x00054231, 0x00000000, 0x0000332d, 0x00000000, 0x0000422d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f33, 0x00000000, 0x00053f33, 0x00000000, 0x00002f42, 0x00000000, 0x00003f42, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94232d, 0x00000000, 0x0005332d, 0x00000000, 0x00002331, 0x00000000, 0x00003331, 
		0x00000000, 0xe200339c, 0x2d808080, 0x00000000, 0x3cd52f20, 0x00000000, 0x00052f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942331, 0x00000000, 0x00053331, 0x00000000, 0x0000232d, 0x00000000, 0x0000332d, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b20, 0x00000000, 0x00052b2f, 0x00000000, 0x00000c20, 0x00000000, 0x00000c2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c20, 0x00000000, 0x00051c2f, 0x00000000, 0x00000c20, 0x00000000, 0x00000c2f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c16202f, 0x00000000, 0x00052f2f, 0x00000000, 0x0000203f, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c16202f, 0x00000000, 0x00052f2f, 0x00000000, 0x0000204e, 0x00000000, 0x00002f4e, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c94332d, 0x00000000, 0x0005522d, 0x00000000, 0x00003331, 0x00000000, 0x00005231, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f31, 0x00000000, 0x00054e31, 0x00000000, 0x00002f2d, 0x00000000, 0x00004e2d, 
		0x00000000, 0xe204139c, 0x2d808080, 0x00000000, 0x3d163f20, 0x00000000, 0x00053f3f, 0x00000000, 0x00002020, 0x00000000, 0x0000203f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941010, 0x00000000, 0x0005102f, 0x00000000, 0x00002310, 0x00000000, 0x0000232f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c940c10, 0x00000000, 0x00050c2f, 0x00000000, 0x00001c10, 0x00000000, 0x00001c2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942b10, 0x00000000, 0x00052b2f, 0x00000000, 0x00001c10, 0x00000000, 0x00001c2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941c10, 0x00000000, 0x00051c2f, 0x00000000, 0x00002b10, 0x00000000, 0x00002b2f, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c16202e, 0x00000000, 0x00052f2e, 0x00000000, 0x0000203e, 0x00000000, 0x00002f3e, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f31, 0x00000000, 0x00053f31, 0x00000000, 0x00002f2d, 0x00000000, 0x00003f2d, 
		0x00000000, 0xe200539c, 0x2d808080, 0x00000000, 0x3c972020, 0x00000000, 0x00052f20, 0x00000000, 0x0000203f, 0x00000000, 0x00002f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942f2d, 0x00000000, 0x00053f2d, 0x00000000, 0x00002f31, 0x00000000, 0x00003f31, 
		0x00000000, 0xe202539c, 0x2d808080, 0x00000000, 0x3c162f2f, 0x00000000, 0x00053f2f, 0x00000000, 0x00002f3f, 0x00000000, 0x00003f3f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c942023, 0x00000000, 0x00052f23, 0x00000000, 0x00002033, 0x00000000, 0x00002f33, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c941010, 0x00000000, 0x0005102f, 0x00000000, 0x00002310, 0x00000000, 0x0000232f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c940c10, 0x00000000, 0x00050c2f, 0x00000000, 0x00002b10, 0x00000000, 0x00002b2f, 
		0x00000000, 0xe200739c, 0x2d808080, 0x00000000, 0x3c940c2f, 0x00000000, 0x00050c3f, 0x00000000, 0x00002b2f, 0x00000000, 0x00002b3f, 
},
};

uint32_t *nextQuadSub;
uint32_t quadSubs[2][2750] = {
    {
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
    },
        {
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
        0x00000000, 0xe200139c, 0x2d808080, 0x00000000, 0x3c142020, 0x00000000, 0x0005203f, 0x00000000, 0x00003f20, 0x00000000, 0x00003f3f,
    }
};

#pragma endregion