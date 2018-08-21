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

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

extern void _ZN7android6Parcel13writeString16EPKDsj(void **str16P, uint16_t const *str, unsigned int len);
void _ZN7android6Parcel13writeString16EPKtj(void **str16P, unsigned short const *str, unsigned int len) {
    _ZN7android6Parcel13writeString16EPKDsj(str16P, str, len);
}

#ifdef __cplusplus
}
#endif
