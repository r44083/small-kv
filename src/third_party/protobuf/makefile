-include ../../../config.mk

SRC := src/google/protobuf/stubs/bytestream.cc \
	src/google/protobuf/stubs/bytestream.h \
	src/google/protobuf/stubs/common.cc \
	src/google/protobuf/stubs/hash.h \
	src/google/protobuf/stubs/int128.cc \
	src/google/protobuf/stubs/int128.h \
	src/google/protobuf/io/io_win32.cc \
	src/google/protobuf/stubs/map_util.h \
	src/google/protobuf/stubs/mathutil.h \
	src/google/protobuf/stubs/status.cc \
	src/google/protobuf/stubs/status.h \
	src/google/protobuf/stubs/status_macros.h \
	src/google/protobuf/stubs/statusor.cc \
	src/google/protobuf/stubs/statusor.h \
	src/google/protobuf/stubs/stringpiece.cc \
	src/google/protobuf/stubs/stringpiece.h \
	src/google/protobuf/stubs/stringprintf.cc \
	src/google/protobuf/stubs/stringprintf.h \
	src/google/protobuf/stubs/structurally_valid.cc \
	src/google/protobuf/stubs/strutil.cc \
	src/google/protobuf/stubs/time.cc \
	src/google/protobuf/stubs/time.h \
	src/google/protobuf/any_lite.cc \
	src/google/protobuf/arena.cc \
	src/google/protobuf/extension_set.cc \
	src/google/protobuf/generated_enum_util.cc \
	src/google/protobuf/generated_message_util.cc \
	src/google/protobuf/generated_message_table_driven_lite.h \
	src/google/protobuf/generated_message_table_driven_lite.cc \
	src/google/protobuf/implicit_weak_message.cc \
	src/google/protobuf/message_lite.cc \
	src/google/protobuf/parse_context.cc \
	src/google/protobuf/repeated_field.cc \
	src/google/protobuf/wire_format_lite.cc \
	src/google/protobuf/io/coded_stream.cc \
	src/google/protobuf/io/strtod.cc \
	src/google/protobuf/io/zero_copy_stream.cc \
	src/google/protobuf/io/zero_copy_stream_impl.cc \
	src/google/protobuf/io/zero_copy_stream_impl_lite.cc

INC := ./src
DEF :=
C_CPP_FLAGS :=
CFLAGS :=
CPPFLAGS :=

# Fix warning "comparison of integer expressions of different signedness: 'int' and 'long long unsigned int"
# for mingw-64
CPPFLAGS += -Wno-sign-compare

# Fix warning "unknown conversion type character 'l' in format" for mingw-64
$(OBJDIR)/src/google/protobuf/stubs/common.cc.o: CPPFLAGS += -Wno-format

AFLAGS :=

LIBDIR :=
LIB :=
LINKED_OBJ :=

# -------------------------

OBJ := $(patsubst %.c,$(OBJDIR)/%.c.o,$(filter %.c,$(SRC))) \
	$(patsubst %.cpp,$(OBJDIR)/%.cpp.o,$(filter %.cpp,$(SRC))) \
	$(patsubst %.cc,$(OBJDIR)/%.cc.o,$(filter %.cc,$(SRC))) \
	$(patsubst %.s,$(OBJDIR)/%.s.o,$(filter %.s,$(SRC))) \
	$(patsubst %.S,$(OBJDIR)/%.S.o,$(filter %.S,$(SRC)))

INC := $(addprefix -I,$(GLOBAL_INC) $(INC))
DEF := $(addprefix -D,$(GLOBAL_DEF) $(DEF))
C_CPP_FLAGS := $(strip $(GLOBAL_C_CPP_FLAGS) $(C_CPP_FLAGS))
CFLAGS := $(strip $(GLOBAL_CFLAGS) $(CFLAGS))
CPPFLAGS := $(strip $(GLOBAL_CPPFLAGS) $(CPPFLAGS))
AFLAGS := $(strip $(GLOBAL_AFLAGS) $(AFLAGS))

# Prevent including this part to main makefile
ifneq ($(ROOT),.)

all: $(OBJ)

clean:
	$(call RMDIR,$(OBJDIR))

.SECONDEXPANSION:
$(OBJDIR)/%.c.o: %.c | $$(@D)/.f
	$(CC) $(DEF) $(INC) $(C_CPP_FLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

$(OBJDIR)/%.cpp.o: %.cpp | $$(@D)/.f
	$(CPP) $(DEF) $(INC) $(C_CPP_FLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@

$(OBJDIR)/%.cc.o: %.cc | $$(@D)/.f
	$(CPP) $(DEF) $(INC) $(C_CPP_FLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@

$(OBJDIR)/%.s.o: %.s | $$(@D)/.f
	$(AS) $(DEF) $(INC) $(AFLAGS) -MMD -MP -c $< -o $@

$(OBJDIR)/%.S.o: %.S | $$(@D)/.f
	$(AS) $(DEF) $(INC) $(AFLAGS) -MMD -MP -c $< -o $@

%/.f:
	$(call MKDIR,$(dir $@))

-include $(patsubst %.o,%.d,$(OBJ))

endif
