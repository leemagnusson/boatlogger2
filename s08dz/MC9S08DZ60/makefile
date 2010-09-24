################################################################################
# Automatically-generated file. Do not edit!
################################################################################

first : all
-include ../makefile.init

RM := rm -f

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Sources/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include Project_Settings/Linker_Files/subdir.mk
-include Lib/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
test.abs \

EXECUTABLES_QUOTED += \
"test.abs" \

EXECUTABLES_OS_FORMAT += \
test.abs \

BURNER_OUTPUT_OUTPUTS += \
test.abs.s19 \

BURNER_OUTPUT_OUTPUTS_QUOTED += \
"test.abs.s19" \

BURNER_OUTPUT_OUTPUTS_OS_FORMAT += \
test.abs.s19 \


# All Target
call-burner := 0
ifneq ($(strip $(EXECUTABLES)),)
ifneq ($(strip $(BBL_SRCS_QUOTED)),)
call-burner := 1
endif
endif
ifeq ($(call-burner),1)
all: test.abs test.abs.s19
else
all: test.abs
endif

# Tool invocations
test.abs: $(OBJS) $(USER_OBJS) C:/Users/Lee/Documents/workspace5/test/Project_Settings/Linker_Files/Project.prm
	@echo 'Building target: $@'
	@echo 'Invoking: Linker'
	"C:\Program Files\Freescale\CW MCU v10.0\eclipse\../MCU/prog/linker" -ArgFile"test.args" -O"test.abs" -Add($(strip $(OBJS_QUOTED) $(USER_OBJS_QUOTED) $(LIBS)))
	@echo 'Finished building target: $@'
	@echo ' '

test.abs.s19: $(BBL_FILES) $(EXECUTABLES)
	@echo 'Invoking: Burner'
	"C:\Program Files\Freescale\CW MCU v10.0\eclipse\../MCU/prog/burner" -ViewHidden -f=$(strip $(BBL_SRCS_QUOTED)) -env"ABS_FILE=$(strip $(EXECUTABLES_OS_FORMAT))"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(EXECUTABLES_OS_FORMAT)$(CC_DEPS)$(OBJS_QUOTED)$(CPP_DEPS_QUOTED)$(CC_DEPS_QUOTED)$(BURNER_OUTPUT_OUTPUTS_OS_FORMAT)$(CPP_DEPS)$(EXECUTABLES)$(C++_DEPS_OS_FORMAT)$(CXX_DEPS_QUOTED)$(BURNER_OUTPUT_OUTPUTS)$(C_DEPS)$(CXX_DEPS_OS_FORMAT)$(C_UPPER_DEPS_OS_FORMAT)$(CC_DEPS_OS_FORMAT)$(BURNER_OUTPUT_OUTPUTS_QUOTED)$(CXX_DEPS)$(C++_DEPS)$(C_UPPER_DEPS_QUOTED)$(CPP_DEPS_OS_FORMAT)$(C++_DEPS_QUOTED)$(C_DEPS_OS_FORMAT)$(EXECUTABLES_QUOTED)$(C_UPPER_DEPS)$(C_DEPS_QUOTED)$(OBJS_OS_FORMAT) test.abs
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
