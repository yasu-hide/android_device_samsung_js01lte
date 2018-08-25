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

#include "SkTypeface.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * _ZN10SkTypeface14CreateFromFileEPKc
 * _ZN10SkTypeface14CreateFromNameEPKcNS_5StyleE
 * _ZN10SkTypeface18CreateFromTypefaceEPKS_NS_5StyleE
 */

// SkTypeface::CreateFromFile(char const*)
extern SkTypeface* _ZN10SkTypeface12MakeFromFileEPKci(const char path[], int index);
SkTypeface* _ZN10SkTypeface14CreateFromFileEPKc(const char path[]) {
	return _ZN10SkTypeface12MakeFromFileEPKci(path, 0);
}

// SkTypeface::CreateFromName(char const*, SkTypeface::Style)
extern SkTypeface* _ZN10SkTypeface12MakeFromNameEPKc11SkFontStyle(const char name[], SkFontStyle fontStyle);
SkTypeface* _ZN10SkTypeface14CreateFromNameEPKcNS_5StyleE(
    const char name[], SkTypeface::Style style) {
        return _ZN10SkTypeface12MakeFromNameEPKc11SkFontStyle(name, SkFontStyle::FromOldStyle(style));
}

// SkTypeface::CreateFromTypeface(SkTypeface const*, SkTypeface::Style)
extern SkTypeface* _ZN10SkTypeface16MakeFromTypefaceEPS_NS_5StyleE(const SkTypeface* family, SkTypeface::Style s);
SkTypeface* _ZN10SkTypeface18CreateFromTypefaceEPKS_NS_5StyleE(
    const SkTypeface* family, SkTypeface::Style s) {
        return _ZN10SkTypeface16MakeFromTypefaceEPS_NS_5StyleE(family, s);
}

#ifdef __cplusplus
}
#endif
