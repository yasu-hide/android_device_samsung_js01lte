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

#include "SkCanvas.h"
#include "SkXfermode.h"
#include "SkRegion.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * _ZN8SkCanvas8drawARGBEjjjjN10SkXfermode4ModeE
 * _ZN8SkCanvas8clipRectERK6SkRectN8SkRegion2OpEb
 */

// SkCanvas::drawARGB(unsigned int, unsigned int, unsigned int, unsigned int, SkXfermode::Mode)
void _ZN8SkCanvas8drawARGBEjjjjN10SkXfermode4ModeE(SkCanvas *self, U8CPU a, U8CPU r, U8CPU g, U8CPU b, SkXfermode::Mode mode) {
    SkPaint paint;
    paint.setARGB(a, r, g, b);
    self->drawPaint(paint);
}

// SkCanvas::clipRect(SkRect const&, SkRegion::Op, bool)
void _ZN8SkCanvas8clipRectERK6SkRectN8SkRegion2OpEb(const SkRect& rect, SkRegion::Op op, bool doAA) {}


#ifdef __cplusplus
}
#endif
