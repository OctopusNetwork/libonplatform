rootdir := $(shell pwd)/../../../..
project := ubuntu-base

include $(rootdir)/build/project/$(project).mk
include $(rootdir)/build/common/common.mk

####
##  Application targets
####
DEP_HEADERS += $(incdir)/libonplatform

apps = mt_udp_client mt_udp_server mt_tcp_sock_server mt_tcp_sock_client

mt_udp_client_SRCS = $(rootdir)/source/libonplatform/test/mt/udp_client_main.c
mt_udp_client_ARCHIVES = onplatform
mt_udp_client_LDLIBS =
mt_udp_client_DISTSOLIBS =

mt_udp_server_SRCS = $(rootdir)/source/libonplatform/test/mt/udp_server_main.c
mt_udp_server_ARCHIVES = onplatform
mt_udp_server_LDLIBS =
mt_udp_server_DISTSOLIBS =

mt_tcp_sock_server_SRCS = $(rootdir)/source/libonplatform/test/mt/tcp_sock_server_main.c
mt_tcp_sock_server_ARCHIVES = onplatform
mt_tcp_sock_server_LDLIBS =
mt_tcp_sock_server_DISTSOLIBS =

mt_tcp_sock_client_SRCS = $(rootdir)/source/libonplatform/test/mt/tcp_sock_client_main.c
mt_tcp_sock_client_ARCHIVES = onplatform
mt_tcp_sock_client_LDLIBS =
mt_tcp_sock_client_DISTSOLIBS =

include $(rootdir)/build/utils/app.mk
