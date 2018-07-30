/*
 * Copyright (C) 2017 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "SkBitmap.h"
#include "SkImageInfo.h"

#ifdef __cplusplus
extern "C"
{
#endif

enum Config {
    kNo_Config,         //!< bitmap has not been configured
    kA8_Config,         //!< 8-bits per pixel, with only alpha specified (0 is transparent, 0xFF is opaque)
    kIndex8_Config,     //!< 8-bits per pixel, using SkColorTable to specify the colors
    kRGB_565_Config,    //!< 16-bits per pixel, (see SkColorPriv.h for packing)
    kARGB_4444_Config,  //!< 16-bits per pixel, (see SkColorPriv.h for packing)
    kARGB_8888_Config,  //!< 32-bits per pixel, (see SkColorPriv.h for packing)
};

/*
 * _Z25SkBitmapConfigToColorTypeN8SkBitmap6ConfigE
 */
SkColorType _Z25SkBitmapConfigToColorTypeN8SkBitmap6ConfigE(
    Config config) {
        static const SkColorType gCT[] = {
            kUnknown_SkColorType,   // kNo_Config
            kAlpha_8_SkColorType,   // kA8_Config
            kRGB_565_SkColorType,   // kRGB_565_Config
            kARGB_4444_SkColorType, // kARGB_4444_Config
            kN32_SkColorType,   // kARGB_8888_Config
        };
        SkASSERT((unsigned)config < SK_ARRAY_COUNT(gCT));
        return gCT[config];
}

#ifdef __cplusplus
}
#endif

