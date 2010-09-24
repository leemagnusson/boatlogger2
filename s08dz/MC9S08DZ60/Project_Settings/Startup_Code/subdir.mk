################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Project_Settings/Startup_Code/start08.c" 

C_SRCS += \
../Project_Settings/Startup_Code/start08.c 

OBJS += \
./Project_Settings/Startup_Code/start08.obj 

OBJS_QUOTED += \
"./Project_Settings/Startup_Code/start08.obj" 

C_DEPS += \
./Project_Settings/Startup_Code/start08.d 

OBJS_OS_FORMAT += \
./Project_Settings/Startup_Code/start08.obj 


# Each subdirectory must supply rules for building sources it contributes
Project_Settings/Startup_Code/start08.obj: ../Project_Settings/Startup_Code/start08.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"C:\Program Files\Freescale\CW MCU v10.0\eclipse\../MCU/prog/chc08" -ArgFile"Project_Settings/Startup_Code/start08.args" -ObjN="Project_Settings/Startup_Code/start08.obj" "$<"
	"C:\Program Files\Freescale\CW MCU v10.0\eclipse\../MCU/prog/chc08" -ArgFile"Project_Settings/Startup_Code/start08.args" -ObjN="Project_Settings/Startup_Code/start08.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Project_Settings/Startup_Code/%.d: ../Project_Settings/Startup_Code/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


