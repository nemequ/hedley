CLANG_C_FLAGS = -Weverything -Wno-vla -Wno-covered-switch-default -Werror
GCC_C_FLAGS = -Wall -Wextra -Werror

ifeq ($(notdir $(CC)), clang)
  CFLAGS ?= $(CLANG_C_FLAGS)
else ifeq ($(notdir $(CC)), suncc)
  CFLAGS ?= -errwarn -errtags
  C_OUTPUT_FILE := -o
else ifeq ($(notdir $(CC)), cl6x)
  CFLAGS ?= --display_error_number --emit_warnings_as_errors --issue_remarks
  C_OUTPUT_FILE := --output_file=
else ifeq ($(notdir $(CC)), pgcc)
  CFLAGS ?= -Minform=inform -c11
  C_OUTPUT_FILE := -o
else ifeq ($(notdir $(CC)), pgc++)
  CFLAGS ?= --display_error_number -Minform=inform -Werror
  C_OUTPUT_FILE := -o
else ifeq ($(notdir $(CC)), xlc)
  CFLAGS ?= $(CLANG_C_FLAGS)
  C_OUTPUT_FILE := -o
else ifeq ($(notdir $(CC)), icc)
  CFLAGS ?= $(GCC_C_FLAGS)
  C_OUTPUT_FILE := -o
else
  CFLAGS ?= $(filter-out -Werror,$(GCC_C_FLAGS))
endif

CLANG_CXX_FLAGS = -Weverything -Werror
GCC_CXX_FLAGS = -Wall -Wextra -Werror

ifeq ($(notdir $(CXX)), clang)
  CXXFLAGS ?= $(CLANG_CXX_FLAGS)
else ifeq ($(notdir $(CXX)), sunCC)
  CXXFLAGS ?= -errwarn=%all -errtags=yes
  CXX_OUTPUT_FILE := -o
else ifeq ($(notdir $(CXX)), pgc++)
  CXXFLAGS ?= --display_error_number -Minform=inform -Werror
  CXX_OUTPUT_FILE := -o
else ifeq ($(notdir $(CC)), cl6x)
  CXXFLAGS ?= --display_error_number --emit_warnings_as_errors --issue_remarks
  CXX_OUTPUT_FILE := --output_file=
else ifeq ($(notdir $(CXX)), xlc++)
  CXXFLAGS ?= $(CLANG_CXX_FLAGS)
  CXX_OUTPUT_FILE := -o
else ifeq ($(notdir $(CXX)), icpc)
  CXXFLAGS ?= $(GCC_CXX_FLAGS)
  CXX_OUTPUT_FILE := -o
else
  CXXFLAGS ?= $(filter-out -Werror,$(GCC_CXX_FLAGS))
endif

C_OUTPUT_FILE ?= --output=
CXX_OUTPUT_FILE ?= --output=

NULL =

TESTS = \
	array-param \
	const \
	deprecated \
	likely \
	message \
	noinline \
	no-return \
	pure \
	restrict \
	sentinel \
	static-assert \
	stringify \
	unknown-pragmas \
	unavailable \
	unreachable \
	visibility \
	warn \
	warn-unused-result \
	$(NULL)

CLEANFILES = \
	$(TESTS) \
	$(TESTS:=-cpp) \
	$(TESTS:=.cpp)

all: $(TESTS) $(TESTS:=-cpp) .gitignore

%.cpp: %.c
	cp -a $^ $@

%-cpp: %.cpp
	$(CXX) $(CXXFLAGS) $(CXX_OUTPUT_FILE)$@ $(^:.c=.cpp)

%: %.c
	$(CC) $(CFLAGS) $(C_OUTPUT_FILE)$@ $^

define GEN_GCC_C_WARNINGS
$(1): $(1:=.c)
	$(CC) $(filter-out -Werror,$(CFLAGS)) $(C_OUTPUT_FILE)$(1) $(1:=.c)
endef

define GEN_GCC_CXX_WARNINGS
$(1)-cpp: $(1:=.cpp)
	$(CXX) $(filter-out -Werror,$(CXXFLAGS)) $(CXX_OUTPUT_FILE)$(1) $(1:=.cpp)
endef

.gitignore:
	rm -f $@
	@$(foreach file,$(CLEANFILES),echo "/$(file)" >> $@;)
	echo "/.gitignore" >> $@

clean:
	rm -f $(CLEANFILES)

.PHONY: clean all

ifeq ($(notdir $(CC)), gcc)
$(foreach tgt,unavailable warn unknown-pragmas,$(eval $(call GEN_GCC_C_WARNINGS,$(tgt))))
endif

ifeq ($(notdir $(CXX)), g++)
$(foreach tgt,unavailable warn unknown-pragmas,$(eval $(call GEN_GCC_CXX_WARNINGS,$(tgt))))
endif
