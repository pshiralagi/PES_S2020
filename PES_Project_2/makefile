#	@file : makefile
#	@author : Pavan Shiralagi and Antara Prakash
#	@date : 02/09/2020
#	@description : Makefile to build project for four different configurations, two configrations
#					run on the board and two on the PC
#	@references : https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html	\
				  https://github.com/ErichStyger/mcuoneclipse/tree/master/Examples/MCUXpresso/FRDM-KL25Z/MyMakeProject

# Command for removing files
RM := rm -rf


# Include files for FB versions
BOARD_INCLUDE := \
	-I"CMSIS" \
	-I"source" \
	-I"board" \
	-I"drivers" \
	-I"utilities"

# Include for PC versions
#PC_INCLUDE := \
#	-I"C:\MinGW\include"
	

# Compiler for FB versions (arm compiler)
CC := arm-none-eabi-gcc

# Linker for FB versions (arm linker)
LL := arm-none-eabi-gcc

# Executable to build for FB versions (.axf)
EXE := \
  ./debug/PES_Project_2.axf

# List of object files for FB versions
OBJS := \
	./debug/PES_Project_2.o \
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
	
# List of dependency files 
C_DEPS = \
	$(wildcard ./debug/*.d)
 
# Include generated dependency files, if target is not clean
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Compiler options for FB versions
C_OPTIONS := \
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

# Linker Options for FB versions
L_OPTIONS := -nostdlib -Xlinker -Map="debug/MyMakeProject.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m0plus -mthumb -T linkerfile.ld -o $(EXE)

# Building correct version (FB_RUN | FB_DEBUG | PC_RUN | PC_DEBUG)
######
#FB_RUN version
ifeq ($(VERSION), FB_RUN)
./debug/%.o: ./source/%.c   
	@echo 'Building file: $<'
	$(CC) $(C_OPTIONS) $(B_OPTIONS) -DFB_RUN $(BOARD_INCLUDE) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<" 
	@echo 'Finished building: FB_RUN $<'
	@echo ' '

#FB_DEBUG version
else ifeq ($(VERSION), FB_DEBUG)
./debug/%.o: ./source/%.c   
	@echo 'Building file: $<'
	$(CC) $(C_OPTIONS) $(B_OPTIONS) -DFB_DEBUG $(BOARD_INCLUDE) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<" 
	@echo 'Finished building: FB_DEBUG $<'
	@echo ' '

#PC_RUN version
else ifeq ($(VERSION), PC_RUN)
CC := gcc						#Linux gcc compiler
EXE := \
  ./debug/PES_Project_2.exe
OBJS := ./debug/PES_Project_2.o
LL := gcc
L_OPTIONS := -g -o $(EXE)		#Flags for converting an object file into executable file
./debug/PES_Project_2.o: ./source/PES_Project_2.c ./source/led.c ./source/time.c 
	@echo 'Building file: $<'
	$(CC) -c -std=gnu99 -DPC_RUN -Isource/time.h -Isource/led.h -Isource/general.h -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<" 
	@echo 'Finished building: PC_RUN $<'
	@echo ' '
	
#PC_DEBUG version
else ifeq ($(VERSION), PC_DEBUG)
CC := gcc
EXE := \
  ./debug/PES_Project_2.exe
OBJS := ./debug/PES_Project_2.o
LL := gcc
L_OPTIONS := -g -o $(EXE)
./debug/PES_Project_2.o: ./source/PES_Project_2.c ./source/led.c ./source/time.c   
	@echo 'Building file: $<'
	$(CC) -c -std=gnu99 -DPC_DEBUG -Isource/time.h -Isource/led.h -Isource/general.h -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<" 
	@echo 'Finished building: PC_DEBUG $<'
	@echo ' '
	
endif

# Main (all) target
all: $(EXE)
	@echo "*** Building completed ***"

# Clean target
clean:
	-$(RM) $(EXECUTABLES) $(OBJS) $(EXE) $(C_DEPS)
	-$(RM) ./debug/*.map
	@echo "*******Clean completed*******"

# Rule to link executable
$(EXE): $(OBJS) linkerfile.ld
	@echo 'Building target: $@'
	@echo 'Invoking: Linker'
	$(LL) $(L_OPTIONS) $(OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Rule to build the files in the CMSIS folder
./debug/%.o: ./CMSIS/%.c
	@echo 'Building file: $<'
	$(CC) $(C_OPTIONS) $(B_OPTIONS) $(BOARD_INCLUDE) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Building completed: $<'
	@echo ' '

# Rule to build files in board folder
./debug/%.o: ./board/%.c
	@echo 'Building file: $<'
	$(CC) $(C_OPTIONS) $(B_OPTIONS) $(BOARD_INCLUDE) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Building completed: $<'
	@echo ' '
	
# Rule to build files in drivers folder
./debug/%.o: ./drivers/%.c
	@echo 'Building file: $<'
	$(CC) $(C_OPTIONS) $(B_OPTIONS) $(BOARD_INCLUDE) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Building completed: $<'
	@echo ' '

# Rule to build files in utilities folder
./debug/%.o: ./utilities/%.c
	@echo 'Building file: $<'
	$(CC) $(C_OPTIONS) $(B_OPTIONS) $(BOARD_INCLUDE) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Building completed: $<'
	@echo ' '

# Rule to build files in startup folder
./debug/%.o: ./startup/%.c
	@echo 'Building file: $<'
	$(CC) $(C_OPTIONS) $(B_OPTIONS) $(BOARD_INCLUDE) -o $@ $<
	@echo 'Building completed: $<'
	@echo ' '
