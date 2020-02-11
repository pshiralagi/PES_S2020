#############################
# Command for removing files
RM := rm -rf

#############################
# Include files
INCLUDES := \
	-I"CMSIS" \
	-I"source" \
	-I"board" \
	-I"drivers" \
	-I"utilities"
	
PC_INCLUDES := \
	-I"C:\MinGW\include"
############################
# Compiler for FB versions
CC := arm-none-eabi-gcc

############################
# Linker for FB versions
LL := arm-none-eabi-gcc

###########################################
# Executable to build for FB versions
EXE := \
  ./debug/PES_Project_2.axf

#######################################
# List of object files for FB versions
OBJS := ./debug/PES_Project_2.o \
	./debug/led.o \
	./debug/cap_touch.o \
	./debug/time.o \
	./debug/startup_mkl25z4.o \
	./debug/system_MKL25Z4.o	\
	./debug/board.o \
	./debug/clock_config.o \
	./debug/peripherals.o \
	./debug/pin_mux.o \
	./debug/fsl_clock.o \
	./debug/fsl_common.o \
	./debug/fsl_flash.o \
	./debug/fsl_gpio.o \
	./debug/fsl_lpsci.o \
	./debug/fsl_smc.o \
	./debug/fsl_uart.o \
	./debug/fsl_debug_console.o
	
############################
# List of dependency files 
C_DEPS = \
	./debug/PES_Project_2.d \
	./debug/led.d \
	./debug/cap_touch.d \
	./debug/time.d \
	./debug/general.d \
	./debug/startup_mkl25z4.d \
	./debug/system_MKL25Z4.d \
	./debug/board.d \
	./debug/clock_config.d \
	./debug/peripherals.d \
	./debug/pin_mux.d \
	./debug/fsl_clock.d \
	./debug/fsl_common.d \
	./debug/fsl_flash.d \
	./debug/fsl_gpio.d \
	./debug/fsl_lpsci.d \
	./debug/fsl_smc.d \
	./debug/fsl_uart.d \
	./debug/fsl_debug_console.d
 
##############################################################
# Include generated dependency files (only if not clean target)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

##################################
# Compiler options for FB versions
CC_OPTIONS := \
	-c \
	-std=gnu99 \
	-O0 \
	-g3 \
	-ffunction-sections \
	-fmessage-length=0\
	-fno-common \
	-fdata-sections \
	-fno-builtin \
	-mcpu=cortex-m0plus \
	-mthumb \
	-Wall \
	-Werror

################################
# Build options for FB versions
B_OPTIONS := \
	-D__REDLIB__ \
	-DCPU_MKL25Z128VLK4 \
	-DCPU_MKL25Z128VLK4_cm0plus \
	-DSDK_OS_BAREMETAL \
	-DFSL_RTOS_BM \
	-DSDK_DEBUGCONSOLE=1 \
	-DCR_INTEGER_PRINTF \
	-DPRINTF_FLOAT_ENABLE=0 \
	-DSCANF_FLOAT_ENABLE=0 \
	-DPRINTF_ADVANCED_ENABLE=0 \
	-DSCANF_ADVANCED_ENABLE=0 \
	-D__MCUXPRESSO \
	-D__USE_CMSIS \
	-DDEBUG \
	-DFRDM_KL25Z \
	-DFREEDOM \
	-specs=redlib.specs \

################################
# Linker Options for FB versions
LL_OPTIONS := -nostdlib -Xlinker -Map="debug/MyMakeProject.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m0plus -mthumb -T linkerfile.ld -o $(EXE)

###########################################################
# Checking different versions and enabling necessary macros
ifeq ($(VERSION), FB_RUN)
./debug/%.o: ./source/%.c   
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) $(B_OPTIONS) -DFB_RUN $(INCLUDES) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<" 
	@echo 'Finished building: FB_RUN $<'
	@echo ' '

else ifeq ($(VERSION), FB_DEBUG)
./debug/%.o: ./source/%.c   
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) $(B_OPTIONS) -DFB_DEBUG $(INCLUDES) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<" 
	@echo 'Finished building: FB_DEBUG $<'
	@echo ' '

else ifeq ($(VERSION), PC_RUN)
CC := gcc						#MinGW gcc compiler [1]
EXE := \
  ./debug/PES_Project_2.exe
OBJS := ./debug/PES_Project_2.o
LL := gcc
LL_OPTIONS := -g -o $(EXE)		#Flags for converting an object file into executable file [1] 
./debug/PES_Project_2.o: ./source/PES_Project_2.c   
	@echo 'Building file: $<'
	$(CC) -c -std=gnu99 -DPC_RUN $(PC_INCLUDES) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<" 
	@echo 'Finished building: PC_RUN $<'
	@echo ' '
	
else ifeq ($(VERSION), PC_DEBUG)
CC := gcc
EXE := \
  ./debug/PES_Project_2.exe
OBJS := ./debug/PES_Project_2.o
LL := gcc
LL_OPTIONS := -g -o $(EXE)
./debug/PES_Project_2.o: ./source/PES_Project_2.c   
	@echo 'Building file: $<'
	$(CC) -c -std=gnu99 -DPC_DEBUG $(PC_INCLUDES) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<" 
	@echo 'Finished building: PC_DEBUG $<'
	@echo ' '
	
endif

############################
# Main (all) target
all: $(EXE)
	@echo "*** finished building ***"

############################
# Clean target
clean:
	-$(RM) $(EXECUTABLES) $(OBJS) $(EXE) 
	-$(RM) ./debug/*.map
	@echo "*******Cleaned!*******"

############################
# Rule to link the executable
$(EXE): $(OBJS) linkerfile.ld
	@echo 'Building target: $@'
	@echo 'Invoking: Linker'
	$(LL) $(LL_OPTIONS) $(OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

#############################################
# Rule to build the files in the CMSIS folder
./debug/%.o: ./CMSIS/%.c
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) $(B_OPTIONS) $(INCLUDES) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

#############################################
# Rule to build the files in the board folder
./debug/%.o: ./board/%.c
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) $(B_OPTIONS) $(INCLUDES) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
	
###############################################
# Rule to build the files in the drivers folder
./debug/%.o: ./drivers/%.c
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) $(B_OPTIONS) $(INCLUDES) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

################################################
# Rule to build the files in the utilities folder
./debug/%.o: ./utilities/%.c
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) $(B_OPTIONS) $(INCLUDES) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

###############################################
# Rule to build the files in the startup folder
./debug/%.o: ./startup/%.c
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) $(B_OPTIONS) $(INCLUDES) -o $@ $<
	@echo 'Finished building: $<'
	@echo ' '

############################ References ################################
# [1] https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html
########################################################################