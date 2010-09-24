################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/adc.c" \
"../Sources/led.c" \
"../Sources/main.c" \
"../Sources/mcg.c" \
"../Sources/rprintf.c" \
"../Sources/rtc.c" \
"../Sources/serial.c" 

C_SRCS += \
../Sources/adc.c \
../Sources/led.c \
../Sources/main.c \
../Sources/mcg.c \
../Sources/rprintf.c \
../Sources/rtc.c \
../Sources/serial.c 

OBJS += \
./Sources/adc.obj \
./Sources/led.obj \
./Sources/main.obj \
./Sources/mcg.obj \
./Sources/rprintf.obj \
./Sources/rtc.obj \
./Sources/serial.obj 

OBJS_QUOTED += \
"./Sources/adc.obj" \
"./Sources/led.obj" \
"./Sources/main.obj" \
"./Sources/mcg.obj" \
"./Sources/rprintf.obj" \
"./Sources/rtc.obj" \
"./Sources/serial.obj" 

C_DEPS += \
./Sources/adc.d \
./Sources/led.d \
./Sources/main.d \
./Sources/mcg.d \
./Sources/rprintf.d \
./Sources/rtc.d \
./Sources/serial.d 

OBJS_OS_FORMAT += \
./Sources/adc.obj \
./Sources/led.obj \
./Sources/main.obj \
./Sources/mcg.obj \
./Sources/rprintf.obj \
./Sources/rtc.obj \
./Sources/serial.obj 


# Each subdirectory must supply rules for building sources it contributes
Sources/adc.obj: ../Sources/adc.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"C:\Program Files\Freescale\CW MCU v10.0\eclipse\../MCU/prog/chc08" -ArgFile"Sources/adc.args" -ObjN="Sources/adc.obj" "$<"
	"C:\Program Files\Freescale\CW MCU v10.0\eclipse\../MCU/prog/chc08" -ArgFile"Sources/adc.args" -ObjN="Sources/adc.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/led.obj: ../Sources/led.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"C:\Program Files\Freescale\CW MCU v10.0\eclipse\../MCU/prog/chc08" -ArgFile"Sources/led.args" -ObjN="Sources/led.obj" "$<"
	"C:\Program Files\Freescale\CW MCU v10.0\eclipse\../MCU/prog/chc08" -ArgFile"Sources/led.args" -ObjN="Sources/led.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"C:\Program Files\Freescale\CW MCU v10.0\eclipse\../MCU/prog/chc08" -ArgFile"Sources/main.args" -ObjN="Sources/main.obj" "$<"
	"C:\Program Files\Freescale\CW MCU v10.0\eclipse\../MCU/prog/chc08" -ArgFile"Sources/main.args" -ObjN="Sources/main.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/mcg.obj: ../Sources/mcg.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"C:\Program Files\Freescale\CW MCU v10.0\eclipse\../MCU/prog/chc08" -ArgFile"Sources/mcg.args" -ObjN="Sources/mcg.obj" "$<"
	"C:\Program Files\Freescale\CW MCU v10.0\eclipse\../MCU/prog/chc08" -ArgFile"Sources/mcg.args" -ObjN="Sources/mcg.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/rprintf.obj: ../Sources/rprintf.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"C:\Program Files\Freescale\CW MCU v10.0\eclipse\../MCU/prog/chc08" -ArgFile"Sources/rprintf.args" -ObjN="Sources/rprintf.obj" "$<"
	"C:\Program Files\Freescale\CW MCU v10.0\eclipse\../MCU/prog/chc08" -ArgFile"Sources/rprintf.args" -ObjN="Sources/rprintf.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/rtc.obj: ../Sources/rtc.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"C:\Program Files\Freescale\CW MCU v10.0\eclipse\../MCU/prog/chc08" -ArgFile"Sources/rtc.args" -ObjN="Sources/rtc.obj" "$<"
	"C:\Program Files\Freescale\CW MCU v10.0\eclipse\../MCU/prog/chc08" -ArgFile"Sources/rtc.args" -ObjN="Sources/rtc.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/serial.obj: ../Sources/serial.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"C:\Program Files\Freescale\CW MCU v10.0\eclipse\../MCU/prog/chc08" -ArgFile"Sources/serial.args" -ObjN="Sources/serial.obj" "$<"
	"C:\Program Files\Freescale\CW MCU v10.0\eclipse\../MCU/prog/chc08" -ArgFile"Sources/serial.args" -ObjN="Sources/serial.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '


