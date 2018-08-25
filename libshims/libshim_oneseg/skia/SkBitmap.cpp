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
#include "SkColorTable.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * _ZN8SkBitmap9setPixelsEPvP12SkColorTable
 * _ZN8SkBitmap11allocPixelsEPNS_9AllocatorEP12SkColorTable
 * _ZNK8SkBitmap6copyToEPS_11SkColorTypePNS_9AllocatorE
 */

extern void _ZN8SkBitmap9setPixelsEPv(void* p);
void _ZN8SkBitmap9setPixelsEPvP12SkColorTable(void* p, SkColorTable* ctable) {
        _ZN8SkBitmap9setPixelsEPv(p);
}

// SkBitmap::allocPixels(SkBitmap::Allocator*, SkColorTable*)
bool _ZN8SkBitmap11allocPixelsEPNS_9AllocatorEP12SkColorTable(
    SkBitmap *self, SkBitmap::Allocator* allocator, SkColorTable* ctable) {
        SkBitmap::HeapAllocator stdalloc;
        if(NULL == allocator) {
            allocator = &stdalloc;
        }
        return allocator->allocPixelRef(self);
}

// SkBitmap::copyTo(SkBitmap*, SkColorType, SkBitmap::Allocator*) const
bool _ZNK8SkBitmap6copyToEPS_11SkColorTypePNS_9AllocatorE(
    SkBitmap* dst, SkColorType dstColorType, SkBitmap::Allocator* alloc) {
        return false;
}


#ifdef __cplusplus
}
#endif
