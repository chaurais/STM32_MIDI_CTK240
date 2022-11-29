################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Main/Sound/midiMessage.c \
../Main/Sound/usb_device.c \
../Main/Sound/usbd_conf.c \
../Main/Sound/usbd_core.c \
../Main/Sound/usbd_ctlreq.c \
../Main/Sound/usbd_desc.c \
../Main/Sound/usbd_ioreq.c \
../Main/Sound/usbd_midi.c \
../Main/Sound/usbd_midi_if.c 

OBJS += \
./Main/Sound/midiMessage.o \
./Main/Sound/usb_device.o \
./Main/Sound/usbd_conf.o \
./Main/Sound/usbd_core.o \
./Main/Sound/usbd_ctlreq.o \
./Main/Sound/usbd_desc.o \
./Main/Sound/usbd_ioreq.o \
./Main/Sound/usbd_midi.o \
./Main/Sound/usbd_midi_if.o 

C_DEPS += \
./Main/Sound/midiMessage.d \
./Main/Sound/usb_device.d \
./Main/Sound/usbd_conf.d \
./Main/Sound/usbd_core.d \
./Main/Sound/usbd_ctlreq.d \
./Main/Sound/usbd_desc.d \
./Main/Sound/usbd_ioreq.d \
./Main/Sound/usbd_midi.d \
./Main/Sound/usbd_midi_if.d 


# Each subdirectory must supply rules for building sources it contributes
Main/Sound/%.o Main/Sound/%.su: ../Main/Sound/%.c Main/Sound/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/STM32 MIDI/Firmware/Main" -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Main-2f-Sound

clean-Main-2f-Sound:
	-$(RM) ./Main/Sound/midiMessage.d ./Main/Sound/midiMessage.o ./Main/Sound/midiMessage.su ./Main/Sound/usb_device.d ./Main/Sound/usb_device.o ./Main/Sound/usb_device.su ./Main/Sound/usbd_conf.d ./Main/Sound/usbd_conf.o ./Main/Sound/usbd_conf.su ./Main/Sound/usbd_core.d ./Main/Sound/usbd_core.o ./Main/Sound/usbd_core.su ./Main/Sound/usbd_ctlreq.d ./Main/Sound/usbd_ctlreq.o ./Main/Sound/usbd_ctlreq.su ./Main/Sound/usbd_desc.d ./Main/Sound/usbd_desc.o ./Main/Sound/usbd_desc.su ./Main/Sound/usbd_ioreq.d ./Main/Sound/usbd_ioreq.o ./Main/Sound/usbd_ioreq.su ./Main/Sound/usbd_midi.d ./Main/Sound/usbd_midi.o ./Main/Sound/usbd_midi.su ./Main/Sound/usbd_midi_if.d ./Main/Sound/usbd_midi_if.o ./Main/Sound/usbd_midi_if.su

.PHONY: clean-Main-2f-Sound

