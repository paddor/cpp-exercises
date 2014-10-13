################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Test.cpp 

OBJS += \
./src/Test.o 

CPP_DEPS += \
./src/Test.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/Users/paddor/Schule/HSR/14-15/Prog3/workspace/pocketcalculator_test/cute" -I"/Users/paddor/Schule/HSR/14-15/Prog3/workspace/pocketcalculator/src" -I"/Users/paddor/Schule/HSR/14-15/Prog3/workspace/sevensegment/src" -I"/Users/paddor/Schule/HSR/14-15/Prog3/workspace/calc/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


