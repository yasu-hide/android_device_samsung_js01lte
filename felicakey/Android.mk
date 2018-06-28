LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := felicakey.c
LOCAL_MODULE := felicakey
LOCAL_CFLAGS += -Wno-unused-parameter
LOCAL_SHARED_LIBRARIES += liblog libcutils
LOCAL_VENDOR_MODULE := true
include $(BUILD_EXECUTABLE)
