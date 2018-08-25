
/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef SkXfermode_DEFINED
#define SkXfermode_DEFINED

#include "SkFlattenable.h"
class SK_API SkXfermode : public SkFlattenable {
public:
    enum Mode {
        kClear_Mode,    //!< [0, 0]
        kSrc_Mode,      //!< [Sa, Sc]
        kDst_Mode,      //!< [Da, Dc]
        kSrcOver_Mode,  //!< [Sa + Da - Sa*Da, Rc = Sc + (1 - Sa)*Dc]
        kDstOver_Mode,  //!< [Sa + Da - Sa*Da, Rc = Dc + (1 - Da)*Sc]
        kSrcIn_Mode,    //!< [Sa * Da, Sc * Da]
        kDstIn_Mode,    //!< [Sa * Da, Sa * Dc]
        kSrcOut_Mode,   //!< [Sa * (1 - Da), Sc * (1 - Da)]
        kDstOut_Mode,   //!< [Da * (1 - Sa), Dc * (1 - Sa)]
        kSrcATop_Mode,  //!< [Da, Sc * Da + (1 - Sa) * Dc]
        kDstATop_Mode,  //!< [Sa, Sa * Dc + Sc * (1 - Da)]
        kXor_Mode,      //!< [Sa + Da - 2 * Sa * Da, Sc * (1 - Da) + (1 - Sa) * Dc]
        kPlus_Mode,     //!< [Sa + Da, Sc + Dc]
        kModulate_Mode, // multiplies all components (= alpha and color)

        // Following blend modes are defined in the CSS Compositing standard:
        // https://dvcs.w3.org/hg/FXTF/rawfile/tip/compositing/index.html#blending
        kScreen_Mode,
        kLastCoeffMode = kScreen_Mode,

        kOverlay_Mode,
        kDarken_Mode,
        kLighten_Mode,
        kColorDodge_Mode,
        kColorBurn_Mode,
        kHardLight_Mode,
        kSoftLight_Mode,
        kDifference_Mode,
        kExclusion_Mode,
        kMultiply_Mode,
        kLastSeparableMode = kMultiply_Mode,

        kHue_Mode,
        kSaturation_Mode,
        kColor_Mode,
        kLuminosity_Mode,
        kLastMode = kLuminosity_Mode
    };

private:
    enum {
        kModeCount = kLastMode + 1
    };
};

#endif
