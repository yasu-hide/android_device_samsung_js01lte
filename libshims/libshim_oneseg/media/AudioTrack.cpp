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

#include <media/AudioTrack.h>

#ifdef __cplusplus
extern "C"
{
#endif

/*
android::AudioTrack::AudioTrack(audio_stream_type_t, unsigned int, audio_format_t, unsigned int, unsigned int, audio_output_flags_t, void (*)(int, void*, void*), void*, int, audio_session_t, android::AudioTrack::transfer_type, audio_offload_info_t const*, unsigned int, int, audio_attributes_t const*, bool, float)
*/
extern void _ZN7android10AudioTrackC1E19audio_stream_type_tj14audio_format_tjj20audio_output_flags_tPFviPvS4_ES4_i15audio_session_tNS0_13transfer_typeEPK20audio_offload_info_tjiPK18audio_attributes_tbf(
        void *self, audio_stream_type_t streamType, uint32_t sampleRate, audio_format_t format, audio_channel_mask_t channelMask, size_t frameCount, audio_output_flags_t flags, android::AudioTrack::callback_t cbf, void* user, unsigned int notificationFrames, audio_session_t sessionId, android::AudioTrack::transfer_type transferType, audio_offload_info_t const *offloadInfo, uid_t uid, pid_t pid, audio_attributes_t const *pAttributes, bool doNotReconnect, float maxRequiredSpeed);


/*
android::AudioTrack::AudioTrack(audio_stream_type_t, unsigned int, audio_format_t, unsigned int, unsigned int, audio_output_flags_t, void (*)(int, void*, void*), void*, unsigned int, int, android::AudioTrack::transfer_type, audio_offload_info_t const*, int, int, audio_attributes_t const*)
*/
void _ZN7android10AudioTrackC1E19audio_stream_type_tj14audio_format_tjj20audio_output_flags_tPFviPvS4_ES4_jiNS0_13transfer_typeEPK20audio_offload_info_tiiPK18audio_attributes_t(
        void *self, audio_stream_type_t streamType, uint32_t sampleRate, audio_format_t format, audio_channel_mask_t channelMask, size_t frameCount, audio_output_flags_t flags, android::AudioTrack::callback_t cbf, void* user, unsigned int notificationFrames, audio_session_t sessionId, android::AudioTrack::transfer_type transferType, audio_offload_info_t const *offloadInfo, uid_t uid, pid_t pid, audio_attributes_t const *pAttributes)
{
    _ZN7android10AudioTrackC1E19audio_stream_type_tj14audio_format_tjj20audio_output_flags_tPFviPvS4_ES4_i15audio_session_tNS0_13transfer_typeEPK20audio_offload_info_tjiPK18audio_attributes_tbf(
	self, streamType, sampleRate, format, channelMask, frameCount, flags, cbf, user, notificationFrames, sessionId, transferType, offloadInfo, uid, pid, pAttributes, false, 1.0f);
}

#ifdef __cplusplus
}
#endif
