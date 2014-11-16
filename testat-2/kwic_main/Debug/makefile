################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: kwic_main

dependents:
	-cd /Users/paddor/Schule/HSR/14-15/Prog3/workspace/testat-2/kwic/Debug && $(MAKE) clean all
	-cd /Users/paddor/Schule/HSR/14-15/Prog3/workspace/testat-2/word/Debug && $(MAKE) clean all

# Tool invocations
kwic_main: $(OBJS) $(USER_OBJS) /Users/paddor/Schule/HSR/14-15/Prog3/workspace/testat-2/kwic/Debug/libkwic.dylib /Users/paddor/Schule/HSR/14-15/Prog3/workspace/testat-2/word/Debug/libword.dylib
	@echo 'Building target: $@'
	@echo 'Invoking: MacOS X C++ Linker'
	g++ -L"/Users/paddor/Schule/HSR/14-15/Prog3/workspace/testat-2/word/Debug" -L"/Users/paddor/Schule/HSR/14-15/Prog3/workspace/testat-2/kwic/Debug" -o "kwic_main" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(CPP_DEPS)$(C_DEPS) kwic_main
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
/Users/paddor/Schule/HSR/14-15/Prog3/workspace/testat-2/kwic/Debug/libkwic.dylib:
/Users/paddor/Schule/HSR/14-15/Prog3/workspace/testat-2/word/Debug/libword.dylib:

-include ../makefile.targets
