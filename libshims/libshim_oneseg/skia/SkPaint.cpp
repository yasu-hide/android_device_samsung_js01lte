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

#include "SkScalar.h"
#include "SkRect.h"
#include "SkTypeface.h"
#include "SkPaint.h"
#include "SkPaintOptionsAndroid.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * _ZN7SkPaint22setPaintOptionsAndroidERK21SkPaintOptionsAndroid
 * _ZN7SkPaint11setTypefaceEP10SkTypeface
 * _ZNK7SkPaint11measureTextEPKvjP6SkRectf
 * _ZN7SkPaint14setFilterLevelENS_11FilterLevelE
 */

// SkPaint::setPaintOptionsAndroid(SkPaintOptionsAndroid const&)
void _ZN7SkPaint22setPaintOptionsAndroidERK21SkPaintOptionsAndroid(const SkPaintOptionsAndroid& options) {}

// SkPaint::setTypeface(SkTypeface*)
SkTypeface* _ZN7SkPaint11setTypefaceEP10SkTypeface(SkTypeface* font) {
        return font;
}

extern SkScalar _ZNK7SkPaint11measureTextEPKvjP6SkRect(
    const void* textData, size_t length, SkRect* bounds);
// SkPaint::measureText(void const*, unsigned int, SkRect*, float) const
SkScalar _ZNK7SkPaint11measureTextEPKvjP6SkRectf(
    const void* textData, size_t length, SkRect* bounds, SkScalar zoom) {
        return _ZNK7SkPaint11measureTextEPKvjP6SkRect(textData, length, bounds);
}

enum FilterLevel {
    kNone_FilterLevel,
    kLow_FilterLevel,
    kMedium_FilterLevel,
    kHigh_FilterLevel
};
// SkPaint::setFilterLevel(SkPaint::FilterLevel)
void _ZN7SkPaint14setFilterLevelENS_11FilterLevelE(FilterLevel level) {}

#ifdef __cplusplus
}
#endif
