ifeq ($(notdir $(CC)), clang)
  CFLAGS := -Weverything -Wno-vla
else ifeq ($(notdir $(CC)), suncc)
  CFLAGS := -errwarn -errtags
else ifeq ($(notdir $(CC)), cl6x)
  CFLAGS := --display_error_number
  C_OUTPUT_FILE := --output_file=
else ifeq ($(notdir $(CC)), pgcc)
  CFLAGS := -Minform=inform -c11
  C_OUTPUT_FILE := -o
else ifeq ($(notdir $(CC)), pgc++)
  CFLAGS := --display_error_number -Minform=inform --c++11
  C_OUTPUT_FILE := -o
else ifeq ($(notdir $(CC)), xlc)
  CFLAGS := -Weverything -Wno-vla
  C_OUTPUT_FILE := -o
else
  CFLAGS := -Wall -Wextra
endif

ifeq ($(notdir $(CXX)), clang)
  CXXFLAGS := -Weverything
else ifeq ($(notdir $(CXX)), sunCC)
  CXXFLAGS := -errwarn=%all -errtags=yes
else ifeq ($(notdir $(CXX)), pgc++)
  CXXFLAGS := -Minform=inform
  CXX_OUTPUT_FILE := -o
else ifeq ($(notdir $(CC)), cl6x)
  CXXFLAGS := --display_error_number
  CXX_OUTPUT_FILE := --output_file=
else ifeq ($(notdir $(CXX)), xlc++)
  CXXFLAGS := -Weverything
  CXX_OUTPUT_FILE := -o
else
  CXXFLAGS := -Wall -Wextra
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

%-cpp: %.c
	cp -a $(@:-cpp=.c) $(^:.c=.cpp)
	$(CXX) $(CXXFLAGS) $(CXX_OUTPUT_FILE)$@ $(^:.c=.cpp) || true

%: %.c
	$(CC) $(CFLAGS) $(C_OUTPUT_FILE)$@ $^ || true

.gitignore:
	rm -f $@
	@$(foreach file,$(CLEANFILES),echo "/$(file)" >> $@;)

clean:
	rm -f $(CLEANFILES)

.PHONY: clean all
