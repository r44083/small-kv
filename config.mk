MODULES := src/proto_types \
	src \
	src/small-kv \
	src/third_party/protobuf \
	src/third_party/rax

ROOT := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

BUILDDIR := $(ROOT)/build
# Relative path to module object folder
OBJDIR := $(BUILDDIR)/obj$(patsubst $(abspath $(ROOT))%,%,$(CURDIR))
BINDIR := $(BUILDDIR)/bin

BIN := $(BINDIR)/$(notdir $(CURDIR))
MAP := $(BUILDDIR)/$(notdir $(CURDIR)).map

GLOBAL_INC := $(ROOT)/src \
	$(ROOT)/src/third_party/protobuf/src

GLOBAL_DEF :=
GLOBAL_C_CPP_FLAGS := -O0 -g3 -Wall
GLOBAL_CFLAGS := -std=c99
GLOBAL_CPPFLAGS := -std=c++17
GLOBAL_AFLAGS := -g3
LDFLAGS := -Wl,--Map="$(MAP)",--cref

CC := gcc
CPP := g++
AS := gcc -x assembler-with-cpp
LD := g++
GDB := gdb
SIZE := size
PROTOC := $(ROOT)/protoc/bin/protoc

ifeq ($(OS),Windows_NT)

define MKDIR
@if not exist "$(1)" mkdir "$(1)"
endef
define RMDIR
@if exist "$(1)" rmdir /s /q "$(1)"
endef
define RM
@del /q "$(1)" 2>nul
endef

else

define MKDIR
@mkdir -p "$(1)"
endef
define RMDIR
@rm -rf "$(1)"
endef
define RM
@rm -f "$(1)"
endef

endif
