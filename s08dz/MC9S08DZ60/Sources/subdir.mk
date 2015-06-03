################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/adc.c" \
"../Sources/can.c" \
"../Sources/data.c" \
"../Sources/error.c" \
"../Sources/io.c" \
"../Sources/led.c" \
"../Sources/main.c" \
"../Sources/mcg.c" \
"../Sources/rprintf.c" \
"../Sources/rtc.c" \
"../Sources/serial.c" \
"../Sources/timer.c" \

C_SRCS += \
../Sources/adc.c \
../Sources/can.c \
../Sources/data.c \
../Sources/error.c \
../Sources/io.c \
../Sources/led.c \
../Sources/main.c \
../Sources/mcg.c \
../Sources/rprintf.c \
../Sources/rtc.c \
../Sources/serial.c \
../Sources/timer.c \

OBJS += \
./Sources/adc_c.obj \
./Sources/can_c.obj \
./Sources/data_c.obj \
./Sources/error_c.obj \
./Sources/io_c.obj \
./Sources/led_c.obj \
./Sources/main_c.obj \
./Sources/mcg_c.obj \
./Sources/rprintf_c.obj \
./Sources/rtc_c.obj \
./Sources/serial_c.obj \
./Sources/timer_c.obj \

OBJS_QUOTED += \
"./Sources/adc_c.obj" \
"./Sources/can_c.obj" \
"./Sources/data_c.obj" \
"./Sources/error_c.obj" \
"./Sources/io_c.obj" \
"./Sources/led_c.obj" \
"./Sources/main_c.obj" \
"./Sources/mcg_c.obj" \
"./Sources/rprintf_c.obj" \
"./Sources/rtc_c.obj" \
"./Sources/serial_c.obj" \
"./Sources/timer_c.obj" \

C_DEPS += \
./Sources/adc_c.d \
./Sources/can_c.d \
./Sources/data_c.d \
./Sources/error_c.d \
./Sources/io_c.d \
./Sources/led_c.d \
./Sources/main_c.d \
./Sources/mcg_c.d \
./Sources/rprintf_c.d \
./Sources/rtc_c.d \
./Sources/serial_c.d \
./Sources/timer_c.d \

C_DEPS_QUOTED += \
"./Sources/adc_c.d" \
"./Sources/can_c.d" \
"./Sources/data_c.d" \
"./Sources/error_c.d" \
"./Sources/io_c.d" \
"./Sources/led_c.d" \
"./Sources/main_c.d" \
"./Sources/mcg_c.d" \
"./Sources/rprintf_c.d" \
"./Sources/rtc_c.d" \
"./Sources/serial_c.d" \
"./Sources/timer_c.d" \

OBJS_OS_FORMAT += \
./Sources/adc_c.obj \
./Sources/can_c.obj \
./Sources/data_c.obj \
./Sources/error_c.obj \
./Sources/io_c.obj \
./Sources/led_c.obj \
./Sources/main_c.obj \
./Sources/mcg_c.obj \
./Sources/rprintf_c.obj \
./Sources/rtc_c.obj \
./Sources/serial_c.obj \
./Sources/timer_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/adc_c.obj: ../Sources/adc.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/adc.args" -ObjN="Sources/adc_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/can_c.obj: ../Sources/can.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/can.args" -ObjN="Sources/can_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/data_c.obj: ../Sources/data.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/data.args" -ObjN="Sources/data_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/error_c.obj: ../Sources/error.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/error.args" -ObjN="Sources/error_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/io_c.obj: ../Sources/io.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/io.args" -ObjN="Sources/io_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/led_c.obj: ../Sources/led.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/led.args" -ObjN="Sources/led_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/main.args" -ObjN="Sources/main_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/mcg_c.obj: ../Sources/mcg.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/mcg.args" -ObjN="Sources/mcg_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/rprintf_c.obj: ../Sources/rprintf.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/rprintf.args" -ObjN="Sources/rprintf_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/rtc_c.obj: ../Sources/rtc.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/rtc.args" -ObjN="Sources/rtc_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/serial_c.obj: ../Sources/serial.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/serial.args" -ObjN="Sources/serial_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/timer_c.obj: ../Sources/timer.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/timer.args" -ObjN="Sources/timer_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '


