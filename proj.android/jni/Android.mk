LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

CLASSES_FILES   := $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)
CHAR_FILES   := $(wildcard $(LOCAL_PATH)/../../Classes/Character/*.cpp)
OMOK_FILES   := $(wildcard $(LOCAL_PATH)/../../Classes/omok/*.cpp)
STONE_FILES   := $(wildcard $(LOCAL_PATH)/../../Classes/Stone/*.cpp)

LOCAL_SRC_FILES := hellocpp/main.cpp \
       $(CLASSES_FILES:$(LOCAL_PATH)/%=%) \
	   $(CHAR_FILES:$(LOCAL_PATH)/%=%) \
	   $(OMOK_FILES:$(LOCAL_PATH)/%=%) \
	   $(STONE_FILES:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
