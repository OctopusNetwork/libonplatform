rootdir := $(shell pwd)/../..
project ?= ubuntu-base

include $(rootdir)/build/project/$(project).mk
include $(rootdir)/build/common/common.mk

TARGET_ARCHIVE = libonplatform.a
MODULENAME = libonplatform
MODULEVERSION = 0.1.0

COMMON_INCLUDE_DIRS += $(rootdir)/source/$(MODULENAME)/include
COMMON_SRC_FILES := $(rootdir)/source/$(MODULENAME)/src/ocnet_malloc.c               \
                    $(rootdir)/source/$(MODULENAME)/src/ocnet_socket.c               \
                    $(rootdir)/source/$(MODULENAME)/src/ocnet_string.c               \
                    $(rootdir)/source/$(MODULENAME)/src/ocnet_thread.c               \
                    $(rootdir)/source/$(MODULENAME)/src/ocnet_time.c                 \
                    $(rootdir)/source/$(MODULENAME)/src/ocnet_iport.c
COMMON_INST_HEADER_DIRS += $(rootdir)/source/$(MODULENAME)/include

include $(rootdir)/build/utils/archive.mk

.PHONY : sync
