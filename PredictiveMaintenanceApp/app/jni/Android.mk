# Copyright (C) 2009 The Android Open Source Project
# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE            := pca_native

LOCAL_SRC_FILES         := 	pca_native.cpp \
							os\Semaphore.cpp \
							os\CriticalSectionLock.cpp \
							os\Thread.cpp \
							debug\Logger.cpp \
							pca\PCA.cpp \
							pca\PCA_Scores.cpp \
							pca\pca_impl\PCA_Impl
#
#LOCAL_MODULE            := pca_impl
#LOCAL_SRC_FILES         := 	pca\pca_impl\PCA_Impl

LOCAL_CPPFLAGS += -fexceptions  -std=c++11

LOCAL_C_INCLUDES := $(LOCAL_PATH)

LOCAL_LDLIBS :=  -llog

include $(BUILD_SHARED_LIBRARY)
