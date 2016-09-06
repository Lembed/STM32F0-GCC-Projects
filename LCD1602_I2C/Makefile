PROJ_NAME = LCD1602_I2C

SRCS = ./main.c  ./Src/stm32f0xx_it.c ./Src/system_stm32f0xx.c ./Src/lcd1602.c

COMMON = ../SDK/

STARTUP = $(COMMON)CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f030x6.s
LINKER_FILE = ./Linkscript/STM32F030F4_FLASH.ld

INCLUDE = -I./Inc
DEFINES =
#MCU Specific Stuff
MCU = STM32F030x6
DEFINES += -D$(MCU)
include $(COMMON)Makefile.common
