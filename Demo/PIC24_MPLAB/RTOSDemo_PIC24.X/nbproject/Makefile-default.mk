#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/RTOSDemo_PIC24.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/RTOSDemo_PIC24.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../App/ParTest/ParTest.c ../../App/serial/serial.c ../../App/CAT24C512.c ../../App/CheckData.c ../../App/Common.c ../../App/PC.c ../../App/PCF8583.c ../../App/SerialBuffer.c ../WCGDebug.c ../../BSP/timertest.c ../../BSP/Debug.c ../../BSP/I2C_S.c ../../BSP/INT.c ../../BSP/LCD.c ../../BSP/PPS.c ../../BSP/RS485.c ../../BSP/Sleep.c ../../BSP/TIM.c ../../BSP/UART2.c ../../BSP/UART3.c ../../../Source/portable/MPLAB/PIC24_dsPIC/port.c ../../../Source/portable/MPLAB/PIC24_dsPIC/portasm_PIC24.S ../../../Source/tasks.c ../../../Source/portable/MemMang/heap_4.c ../../../Source/list.c ../../../Source/queue.c ../../Common/Minimal/BlockQ.c ../../Common/Minimal/blocktim.c ../../Common/Minimal/comtest.c ../../Common/Minimal/integer.c ../main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/862485765/ParTest.o ${OBJECTDIR}/_ext/1875937438/serial.o ${OBJECTDIR}/_ext/1445226593/CAT24C512.o ${OBJECTDIR}/_ext/1445226593/CheckData.o ${OBJECTDIR}/_ext/1445226593/Common.o ${OBJECTDIR}/_ext/1445226593/PC.o ${OBJECTDIR}/_ext/1445226593/PCF8583.o ${OBJECTDIR}/_ext/1445226593/SerialBuffer.o ${OBJECTDIR}/_ext/1472/WCGDebug.o ${OBJECTDIR}/_ext/1445226623/timertest.o ${OBJECTDIR}/_ext/1445226623/Debug.o ${OBJECTDIR}/_ext/1445226623/I2C_S.o ${OBJECTDIR}/_ext/1445226623/INT.o ${OBJECTDIR}/_ext/1445226623/LCD.o ${OBJECTDIR}/_ext/1445226623/PPS.o ${OBJECTDIR}/_ext/1445226623/RS485.o ${OBJECTDIR}/_ext/1445226623/Sleep.o ${OBJECTDIR}/_ext/1445226623/TIM.o ${OBJECTDIR}/_ext/1445226623/UART2.o ${OBJECTDIR}/_ext/1445226623/UART3.o ${OBJECTDIR}/_ext/1343266892/port.o ${OBJECTDIR}/_ext/1343266892/portasm_PIC24.o ${OBJECTDIR}/_ext/449926602/tasks.o ${OBJECTDIR}/_ext/1884096877/heap_4.o ${OBJECTDIR}/_ext/449926602/list.o ${OBJECTDIR}/_ext/449926602/queue.o ${OBJECTDIR}/_ext/1163846883/BlockQ.o ${OBJECTDIR}/_ext/1163846883/blocktim.o ${OBJECTDIR}/_ext/1163846883/comtest.o ${OBJECTDIR}/_ext/1163846883/integer.o ${OBJECTDIR}/_ext/1472/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/862485765/ParTest.o.d ${OBJECTDIR}/_ext/1875937438/serial.o.d ${OBJECTDIR}/_ext/1445226593/CAT24C512.o.d ${OBJECTDIR}/_ext/1445226593/CheckData.o.d ${OBJECTDIR}/_ext/1445226593/Common.o.d ${OBJECTDIR}/_ext/1445226593/PC.o.d ${OBJECTDIR}/_ext/1445226593/PCF8583.o.d ${OBJECTDIR}/_ext/1445226593/SerialBuffer.o.d ${OBJECTDIR}/_ext/1472/WCGDebug.o.d ${OBJECTDIR}/_ext/1445226623/timertest.o.d ${OBJECTDIR}/_ext/1445226623/Debug.o.d ${OBJECTDIR}/_ext/1445226623/I2C_S.o.d ${OBJECTDIR}/_ext/1445226623/INT.o.d ${OBJECTDIR}/_ext/1445226623/LCD.o.d ${OBJECTDIR}/_ext/1445226623/PPS.o.d ${OBJECTDIR}/_ext/1445226623/RS485.o.d ${OBJECTDIR}/_ext/1445226623/Sleep.o.d ${OBJECTDIR}/_ext/1445226623/TIM.o.d ${OBJECTDIR}/_ext/1445226623/UART2.o.d ${OBJECTDIR}/_ext/1445226623/UART3.o.d ${OBJECTDIR}/_ext/1343266892/port.o.d ${OBJECTDIR}/_ext/1343266892/portasm_PIC24.o.d ${OBJECTDIR}/_ext/449926602/tasks.o.d ${OBJECTDIR}/_ext/1884096877/heap_4.o.d ${OBJECTDIR}/_ext/449926602/list.o.d ${OBJECTDIR}/_ext/449926602/queue.o.d ${OBJECTDIR}/_ext/1163846883/BlockQ.o.d ${OBJECTDIR}/_ext/1163846883/blocktim.o.d ${OBJECTDIR}/_ext/1163846883/comtest.o.d ${OBJECTDIR}/_ext/1163846883/integer.o.d ${OBJECTDIR}/_ext/1472/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/862485765/ParTest.o ${OBJECTDIR}/_ext/1875937438/serial.o ${OBJECTDIR}/_ext/1445226593/CAT24C512.o ${OBJECTDIR}/_ext/1445226593/CheckData.o ${OBJECTDIR}/_ext/1445226593/Common.o ${OBJECTDIR}/_ext/1445226593/PC.o ${OBJECTDIR}/_ext/1445226593/PCF8583.o ${OBJECTDIR}/_ext/1445226593/SerialBuffer.o ${OBJECTDIR}/_ext/1472/WCGDebug.o ${OBJECTDIR}/_ext/1445226623/timertest.o ${OBJECTDIR}/_ext/1445226623/Debug.o ${OBJECTDIR}/_ext/1445226623/I2C_S.o ${OBJECTDIR}/_ext/1445226623/INT.o ${OBJECTDIR}/_ext/1445226623/LCD.o ${OBJECTDIR}/_ext/1445226623/PPS.o ${OBJECTDIR}/_ext/1445226623/RS485.o ${OBJECTDIR}/_ext/1445226623/Sleep.o ${OBJECTDIR}/_ext/1445226623/TIM.o ${OBJECTDIR}/_ext/1445226623/UART2.o ${OBJECTDIR}/_ext/1445226623/UART3.o ${OBJECTDIR}/_ext/1343266892/port.o ${OBJECTDIR}/_ext/1343266892/portasm_PIC24.o ${OBJECTDIR}/_ext/449926602/tasks.o ${OBJECTDIR}/_ext/1884096877/heap_4.o ${OBJECTDIR}/_ext/449926602/list.o ${OBJECTDIR}/_ext/449926602/queue.o ${OBJECTDIR}/_ext/1163846883/BlockQ.o ${OBJECTDIR}/_ext/1163846883/blocktim.o ${OBJECTDIR}/_ext/1163846883/comtest.o ${OBJECTDIR}/_ext/1163846883/integer.o ${OBJECTDIR}/_ext/1472/main.o

# Source Files
SOURCEFILES=../../App/ParTest/ParTest.c ../../App/serial/serial.c ../../App/CAT24C512.c ../../App/CheckData.c ../../App/Common.c ../../App/PC.c ../../App/PCF8583.c ../../App/SerialBuffer.c ../WCGDebug.c ../../BSP/timertest.c ../../BSP/Debug.c ../../BSP/I2C_S.c ../../BSP/INT.c ../../BSP/LCD.c ../../BSP/PPS.c ../../BSP/RS485.c ../../BSP/Sleep.c ../../BSP/TIM.c ../../BSP/UART2.c ../../BSP/UART3.c ../../../Source/portable/MPLAB/PIC24_dsPIC/port.c ../../../Source/portable/MPLAB/PIC24_dsPIC/portasm_PIC24.S ../../../Source/tasks.c ../../../Source/portable/MemMang/heap_4.c ../../../Source/list.c ../../../Source/queue.c ../../Common/Minimal/BlockQ.c ../../Common/Minimal/blocktim.c ../../Common/Minimal/comtest.c ../../Common/Minimal/integer.c ../main.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/RTOSDemo_PIC24.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ64GA306
MP_LINKER_FILE_OPTION=,--script="../p24FJ64GA306.gld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/862485765/ParTest.o: ../../App/ParTest/ParTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/862485765" 
	@${RM} ${OBJECTDIR}/_ext/862485765/ParTest.o.d 
	@${RM} ${OBJECTDIR}/_ext/862485765/ParTest.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../App/ParTest/ParTest.c  -o ${OBJECTDIR}/_ext/862485765/ParTest.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/862485765/ParTest.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/862485765/ParTest.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1875937438/serial.o: ../../App/serial/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1875937438" 
	@${RM} ${OBJECTDIR}/_ext/1875937438/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1875937438/serial.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../App/serial/serial.c  -o ${OBJECTDIR}/_ext/1875937438/serial.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1875937438/serial.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1875937438/serial.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226593/CAT24C512.o: ../../App/CAT24C512.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226593" 
	@${RM} ${OBJECTDIR}/_ext/1445226593/CAT24C512.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226593/CAT24C512.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../App/CAT24C512.c  -o ${OBJECTDIR}/_ext/1445226593/CAT24C512.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226593/CAT24C512.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226593/CAT24C512.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226593/CheckData.o: ../../App/CheckData.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226593" 
	@${RM} ${OBJECTDIR}/_ext/1445226593/CheckData.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226593/CheckData.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../App/CheckData.c  -o ${OBJECTDIR}/_ext/1445226593/CheckData.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226593/CheckData.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226593/CheckData.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226593/Common.o: ../../App/Common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226593" 
	@${RM} ${OBJECTDIR}/_ext/1445226593/Common.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226593/Common.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../App/Common.c  -o ${OBJECTDIR}/_ext/1445226593/Common.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226593/Common.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226593/Common.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226593/PC.o: ../../App/PC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226593" 
	@${RM} ${OBJECTDIR}/_ext/1445226593/PC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226593/PC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../App/PC.c  -o ${OBJECTDIR}/_ext/1445226593/PC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226593/PC.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226593/PC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226593/PCF8583.o: ../../App/PCF8583.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226593" 
	@${RM} ${OBJECTDIR}/_ext/1445226593/PCF8583.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226593/PCF8583.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../App/PCF8583.c  -o ${OBJECTDIR}/_ext/1445226593/PCF8583.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226593/PCF8583.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226593/PCF8583.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226593/SerialBuffer.o: ../../App/SerialBuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226593" 
	@${RM} ${OBJECTDIR}/_ext/1445226593/SerialBuffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226593/SerialBuffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../App/SerialBuffer.c  -o ${OBJECTDIR}/_ext/1445226593/SerialBuffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226593/SerialBuffer.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226593/SerialBuffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/WCGDebug.o: ../WCGDebug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/WCGDebug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/WCGDebug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../WCGDebug.c  -o ${OBJECTDIR}/_ext/1472/WCGDebug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/WCGDebug.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/WCGDebug.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226623/timertest.o: ../../BSP/timertest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226623" 
	@${RM} ${OBJECTDIR}/_ext/1445226623/timertest.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/timertest.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../BSP/timertest.c  -o ${OBJECTDIR}/_ext/1445226623/timertest.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/timertest.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/timertest.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226623/Debug.o: ../../BSP/Debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226623" 
	@${RM} ${OBJECTDIR}/_ext/1445226623/Debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/Debug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../BSP/Debug.c  -o ${OBJECTDIR}/_ext/1445226623/Debug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/Debug.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/Debug.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226623/I2C_S.o: ../../BSP/I2C_S.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226623" 
	@${RM} ${OBJECTDIR}/_ext/1445226623/I2C_S.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/I2C_S.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../BSP/I2C_S.c  -o ${OBJECTDIR}/_ext/1445226623/I2C_S.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/I2C_S.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/I2C_S.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226623/INT.o: ../../BSP/INT.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226623" 
	@${RM} ${OBJECTDIR}/_ext/1445226623/INT.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/INT.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../BSP/INT.c  -o ${OBJECTDIR}/_ext/1445226623/INT.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/INT.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/INT.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226623/LCD.o: ../../BSP/LCD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226623" 
	@${RM} ${OBJECTDIR}/_ext/1445226623/LCD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/LCD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../BSP/LCD.c  -o ${OBJECTDIR}/_ext/1445226623/LCD.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/LCD.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/LCD.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226623/PPS.o: ../../BSP/PPS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226623" 
	@${RM} ${OBJECTDIR}/_ext/1445226623/PPS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/PPS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../BSP/PPS.c  -o ${OBJECTDIR}/_ext/1445226623/PPS.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/PPS.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/PPS.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226623/RS485.o: ../../BSP/RS485.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226623" 
	@${RM} ${OBJECTDIR}/_ext/1445226623/RS485.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/RS485.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../BSP/RS485.c  -o ${OBJECTDIR}/_ext/1445226623/RS485.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/RS485.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/RS485.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226623/Sleep.o: ../../BSP/Sleep.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226623" 
	@${RM} ${OBJECTDIR}/_ext/1445226623/Sleep.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/Sleep.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../BSP/Sleep.c  -o ${OBJECTDIR}/_ext/1445226623/Sleep.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/Sleep.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/Sleep.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226623/TIM.o: ../../BSP/TIM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226623" 
	@${RM} ${OBJECTDIR}/_ext/1445226623/TIM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/TIM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../BSP/TIM.c  -o ${OBJECTDIR}/_ext/1445226623/TIM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/TIM.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/TIM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226623/UART2.o: ../../BSP/UART2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226623" 
	@${RM} ${OBJECTDIR}/_ext/1445226623/UART2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/UART2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../BSP/UART2.c  -o ${OBJECTDIR}/_ext/1445226623/UART2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/UART2.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/UART2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226623/UART3.o: ../../BSP/UART3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226623" 
	@${RM} ${OBJECTDIR}/_ext/1445226623/UART3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/UART3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../BSP/UART3.c  -o ${OBJECTDIR}/_ext/1445226623/UART3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/UART3.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/UART3.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1343266892/port.o: ../../../Source/portable/MPLAB/PIC24_dsPIC/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1343266892" 
	@${RM} ${OBJECTDIR}/_ext/1343266892/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1343266892/port.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../Source/portable/MPLAB/PIC24_dsPIC/port.c  -o ${OBJECTDIR}/_ext/1343266892/port.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1343266892/port.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1343266892/port.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/449926602/tasks.o: ../../../Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/449926602" 
	@${RM} ${OBJECTDIR}/_ext/449926602/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/449926602/tasks.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../Source/tasks.c  -o ${OBJECTDIR}/_ext/449926602/tasks.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/449926602/tasks.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/449926602/tasks.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1884096877/heap_4.o: ../../../Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1884096877" 
	@${RM} ${OBJECTDIR}/_ext/1884096877/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1884096877/heap_4.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../Source/portable/MemMang/heap_4.c  -o ${OBJECTDIR}/_ext/1884096877/heap_4.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1884096877/heap_4.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1884096877/heap_4.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/449926602/list.o: ../../../Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/449926602" 
	@${RM} ${OBJECTDIR}/_ext/449926602/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/449926602/list.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../Source/list.c  -o ${OBJECTDIR}/_ext/449926602/list.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/449926602/list.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/449926602/list.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/449926602/queue.o: ../../../Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/449926602" 
	@${RM} ${OBJECTDIR}/_ext/449926602/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/449926602/queue.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../Source/queue.c  -o ${OBJECTDIR}/_ext/449926602/queue.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/449926602/queue.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/449926602/queue.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1163846883/BlockQ.o: ../../Common/Minimal/BlockQ.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1163846883" 
	@${RM} ${OBJECTDIR}/_ext/1163846883/BlockQ.o.d 
	@${RM} ${OBJECTDIR}/_ext/1163846883/BlockQ.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../Common/Minimal/BlockQ.c  -o ${OBJECTDIR}/_ext/1163846883/BlockQ.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1163846883/BlockQ.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1163846883/BlockQ.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1163846883/blocktim.o: ../../Common/Minimal/blocktim.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1163846883" 
	@${RM} ${OBJECTDIR}/_ext/1163846883/blocktim.o.d 
	@${RM} ${OBJECTDIR}/_ext/1163846883/blocktim.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../Common/Minimal/blocktim.c  -o ${OBJECTDIR}/_ext/1163846883/blocktim.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1163846883/blocktim.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1163846883/blocktim.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1163846883/comtest.o: ../../Common/Minimal/comtest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1163846883" 
	@${RM} ${OBJECTDIR}/_ext/1163846883/comtest.o.d 
	@${RM} ${OBJECTDIR}/_ext/1163846883/comtest.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../Common/Minimal/comtest.c  -o ${OBJECTDIR}/_ext/1163846883/comtest.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1163846883/comtest.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1163846883/comtest.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1163846883/integer.o: ../../Common/Minimal/integer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1163846883" 
	@${RM} ${OBJECTDIR}/_ext/1163846883/integer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1163846883/integer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../Common/Minimal/integer.c  -o ${OBJECTDIR}/_ext/1163846883/integer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1163846883/integer.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1163846883/integer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../main.c  -o ${OBJECTDIR}/_ext/1472/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/862485765/ParTest.o: ../../App/ParTest/ParTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/862485765" 
	@${RM} ${OBJECTDIR}/_ext/862485765/ParTest.o.d 
	@${RM} ${OBJECTDIR}/_ext/862485765/ParTest.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../App/ParTest/ParTest.c  -o ${OBJECTDIR}/_ext/862485765/ParTest.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/862485765/ParTest.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/862485765/ParTest.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1875937438/serial.o: ../../App/serial/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1875937438" 
	@${RM} ${OBJECTDIR}/_ext/1875937438/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1875937438/serial.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../App/serial/serial.c  -o ${OBJECTDIR}/_ext/1875937438/serial.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1875937438/serial.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1875937438/serial.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226593/CAT24C512.o: ../../App/CAT24C512.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226593" 
	@${RM} ${OBJECTDIR}/_ext/1445226593/CAT24C512.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226593/CAT24C512.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../App/CAT24C512.c  -o ${OBJECTDIR}/_ext/1445226593/CAT24C512.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226593/CAT24C512.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226593/CAT24C512.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226593/CheckData.o: ../../App/CheckData.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226593" 
	@${RM} ${OBJECTDIR}/_ext/1445226593/CheckData.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226593/CheckData.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../App/CheckData.c  -o ${OBJECTDIR}/_ext/1445226593/CheckData.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226593/CheckData.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226593/CheckData.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226593/Common.o: ../../App/Common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226593" 
	@${RM} ${OBJECTDIR}/_ext/1445226593/Common.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226593/Common.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../App/Common.c  -o ${OBJECTDIR}/_ext/1445226593/Common.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226593/Common.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226593/Common.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226593/PC.o: ../../App/PC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226593" 
	@${RM} ${OBJECTDIR}/_ext/1445226593/PC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226593/PC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../App/PC.c  -o ${OBJECTDIR}/_ext/1445226593/PC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226593/PC.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226593/PC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226593/PCF8583.o: ../../App/PCF8583.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226593" 
	@${RM} ${OBJECTDIR}/_ext/1445226593/PCF8583.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226593/PCF8583.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../App/PCF8583.c  -o ${OBJECTDIR}/_ext/1445226593/PCF8583.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226593/PCF8583.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226593/PCF8583.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226593/SerialBuffer.o: ../../App/SerialBuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226593" 
	@${RM} ${OBJECTDIR}/_ext/1445226593/SerialBuffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226593/SerialBuffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../App/SerialBuffer.c  -o ${OBJECTDIR}/_ext/1445226593/SerialBuffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226593/SerialBuffer.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226593/SerialBuffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/WCGDebug.o: ../WCGDebug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/WCGDebug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/WCGDebug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../WCGDebug.c  -o ${OBJECTDIR}/_ext/1472/WCGDebug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/WCGDebug.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/WCGDebug.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226623/timertest.o: ../../BSP/timertest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226623" 
	@${RM} ${OBJECTDIR}/_ext/1445226623/timertest.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/timertest.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../BSP/timertest.c  -o ${OBJECTDIR}/_ext/1445226623/timertest.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/timertest.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/timertest.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226623/Debug.o: ../../BSP/Debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226623" 
	@${RM} ${OBJECTDIR}/_ext/1445226623/Debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/Debug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../BSP/Debug.c  -o ${OBJECTDIR}/_ext/1445226623/Debug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/Debug.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/Debug.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226623/I2C_S.o: ../../BSP/I2C_S.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226623" 
	@${RM} ${OBJECTDIR}/_ext/1445226623/I2C_S.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/I2C_S.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../BSP/I2C_S.c  -o ${OBJECTDIR}/_ext/1445226623/I2C_S.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/I2C_S.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/I2C_S.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226623/INT.o: ../../BSP/INT.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226623" 
	@${RM} ${OBJECTDIR}/_ext/1445226623/INT.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/INT.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../BSP/INT.c  -o ${OBJECTDIR}/_ext/1445226623/INT.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/INT.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/INT.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226623/LCD.o: ../../BSP/LCD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226623" 
	@${RM} ${OBJECTDIR}/_ext/1445226623/LCD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/LCD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../BSP/LCD.c  -o ${OBJECTDIR}/_ext/1445226623/LCD.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/LCD.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/LCD.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226623/PPS.o: ../../BSP/PPS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226623" 
	@${RM} ${OBJECTDIR}/_ext/1445226623/PPS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/PPS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../BSP/PPS.c  -o ${OBJECTDIR}/_ext/1445226623/PPS.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/PPS.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/PPS.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226623/RS485.o: ../../BSP/RS485.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226623" 
	@${RM} ${OBJECTDIR}/_ext/1445226623/RS485.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/RS485.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../BSP/RS485.c  -o ${OBJECTDIR}/_ext/1445226623/RS485.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/RS485.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/RS485.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226623/Sleep.o: ../../BSP/Sleep.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226623" 
	@${RM} ${OBJECTDIR}/_ext/1445226623/Sleep.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/Sleep.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../BSP/Sleep.c  -o ${OBJECTDIR}/_ext/1445226623/Sleep.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/Sleep.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/Sleep.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226623/TIM.o: ../../BSP/TIM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226623" 
	@${RM} ${OBJECTDIR}/_ext/1445226623/TIM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/TIM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../BSP/TIM.c  -o ${OBJECTDIR}/_ext/1445226623/TIM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/TIM.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/TIM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226623/UART2.o: ../../BSP/UART2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226623" 
	@${RM} ${OBJECTDIR}/_ext/1445226623/UART2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/UART2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../BSP/UART2.c  -o ${OBJECTDIR}/_ext/1445226623/UART2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/UART2.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/UART2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1445226623/UART3.o: ../../BSP/UART3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1445226623" 
	@${RM} ${OBJECTDIR}/_ext/1445226623/UART3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/UART3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../BSP/UART3.c  -o ${OBJECTDIR}/_ext/1445226623/UART3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/UART3.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/UART3.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1343266892/port.o: ../../../Source/portable/MPLAB/PIC24_dsPIC/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1343266892" 
	@${RM} ${OBJECTDIR}/_ext/1343266892/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1343266892/port.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../Source/portable/MPLAB/PIC24_dsPIC/port.c  -o ${OBJECTDIR}/_ext/1343266892/port.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1343266892/port.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1343266892/port.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/449926602/tasks.o: ../../../Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/449926602" 
	@${RM} ${OBJECTDIR}/_ext/449926602/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/449926602/tasks.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../Source/tasks.c  -o ${OBJECTDIR}/_ext/449926602/tasks.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/449926602/tasks.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/449926602/tasks.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1884096877/heap_4.o: ../../../Source/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1884096877" 
	@${RM} ${OBJECTDIR}/_ext/1884096877/heap_4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1884096877/heap_4.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../Source/portable/MemMang/heap_4.c  -o ${OBJECTDIR}/_ext/1884096877/heap_4.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1884096877/heap_4.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1884096877/heap_4.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/449926602/list.o: ../../../Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/449926602" 
	@${RM} ${OBJECTDIR}/_ext/449926602/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/449926602/list.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../Source/list.c  -o ${OBJECTDIR}/_ext/449926602/list.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/449926602/list.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/449926602/list.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/449926602/queue.o: ../../../Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/449926602" 
	@${RM} ${OBJECTDIR}/_ext/449926602/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/449926602/queue.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../Source/queue.c  -o ${OBJECTDIR}/_ext/449926602/queue.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/449926602/queue.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/449926602/queue.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1163846883/BlockQ.o: ../../Common/Minimal/BlockQ.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1163846883" 
	@${RM} ${OBJECTDIR}/_ext/1163846883/BlockQ.o.d 
	@${RM} ${OBJECTDIR}/_ext/1163846883/BlockQ.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../Common/Minimal/BlockQ.c  -o ${OBJECTDIR}/_ext/1163846883/BlockQ.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1163846883/BlockQ.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1163846883/BlockQ.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1163846883/blocktim.o: ../../Common/Minimal/blocktim.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1163846883" 
	@${RM} ${OBJECTDIR}/_ext/1163846883/blocktim.o.d 
	@${RM} ${OBJECTDIR}/_ext/1163846883/blocktim.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../Common/Minimal/blocktim.c  -o ${OBJECTDIR}/_ext/1163846883/blocktim.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1163846883/blocktim.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1163846883/blocktim.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1163846883/comtest.o: ../../Common/Minimal/comtest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1163846883" 
	@${RM} ${OBJECTDIR}/_ext/1163846883/comtest.o.d 
	@${RM} ${OBJECTDIR}/_ext/1163846883/comtest.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../Common/Minimal/comtest.c  -o ${OBJECTDIR}/_ext/1163846883/comtest.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1163846883/comtest.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1163846883/comtest.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1163846883/integer.o: ../../Common/Minimal/integer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1163846883" 
	@${RM} ${OBJECTDIR}/_ext/1163846883/integer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1163846883/integer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../Common/Minimal/integer.c  -o ${OBJECTDIR}/_ext/1163846883/integer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1163846883/integer.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1163846883/integer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../main.c  -o ${OBJECTDIR}/_ext/1472/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mlarge-code -O0 -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -DMPLAB_PIC24_PORT -msmart-io=1 -Wall -msfr-warn=off   -fno-schedule-insns -fno-schedule-insns2
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1343266892/portasm_PIC24.o: ../../../Source/portable/MPLAB/PIC24_dsPIC/portasm_PIC24.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1343266892" 
	@${RM} ${OBJECTDIR}/_ext/1343266892/portasm_PIC24.o.d 
	@${RM} ${OBJECTDIR}/_ext/1343266892/portasm_PIC24.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../../../Source/portable/MPLAB/PIC24_dsPIC/portasm_PIC24.S  -o ${OBJECTDIR}/_ext/1343266892/portasm_PIC24.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1343266892/portasm_PIC24.o.d"  -D__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -I".." -I"." -Wa,-MD,"${OBJECTDIR}/_ext/1343266892/portasm_PIC24.o.asm.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1343266892/portasm_PIC24.o.d" "${OBJECTDIR}/_ext/1343266892/portasm_PIC24.o.asm.d"  -t $(SILENT)  -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/1343266892/portasm_PIC24.o: ../../../Source/portable/MPLAB/PIC24_dsPIC/portasm_PIC24.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1343266892" 
	@${RM} ${OBJECTDIR}/_ext/1343266892/portasm_PIC24.o.d 
	@${RM} ${OBJECTDIR}/_ext/1343266892/portasm_PIC24.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../../../Source/portable/MPLAB/PIC24_dsPIC/portasm_PIC24.S  -o ${OBJECTDIR}/_ext/1343266892/portasm_PIC24.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1343266892/portasm_PIC24.o.d"  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  -I".." -I"../../../../../Demo/PIC24_MPLAB" -I"../../../../Demo/PIC24_MPLAB" -I"../../../../Source/include" -I"../../../../include" -I"../../../Common/include" -I"../../../Source/include" -I"../../../include" -I"../../Common/include" -I"../../Demo/PIC24_MPLAB" -I"../../include" -I"../FileSystem" -I"../include" -I"." -I"../../App" -I"../../BSP" -I".." -I"." -Wa,-MD,"${OBJECTDIR}/_ext/1343266892/portasm_PIC24.o.asm.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax,-g$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1343266892/portasm_PIC24.o.d" "${OBJECTDIR}/_ext/1343266892/portasm_PIC24.o.asm.d"  -t $(SILENT)  -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/RTOSDemo_PIC24.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../p24FJ64GA306.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/RTOSDemo_PIC24.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81B -mreserve=data@0x81C:0x81D -mreserve=data@0x81E:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x827 -mreserve=data@0x82A:0x84F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--heap=0,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library-path="..",--library-path=".",--no-force-link,--smart-io,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/RTOSDemo_PIC24.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../p24FJ64GA306.gld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/RTOSDemo_PIC24.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--heap=0,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library-path="..",--library-path=".",--no-force-link,--smart-io,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/RTOSDemo_PIC24.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
