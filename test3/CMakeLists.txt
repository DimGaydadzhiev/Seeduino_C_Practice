 
    # Target a recent cmake
    cmake_minimum_required(VERSION 3.5)

    # Project name
    project("blink")

    # Product filename
    set(PRODUCT_NAME blinkTest)

    include_directories("src")

    ## AVR Chip Configuration
    set(F_CPU 16000000UL)


  
    # CPU, you can find the list here:
    # https://gcc.gnu.org/onlinedocs/gcc/AVR-Options.html
    set(MCU atmega328p)

    # Default Baudrate for UART, read avr include/util/setbaud.h for usage
    set(BAUD 9600)

    # The programmer to use, read avrdude manual for list
    set(PROG_TYPE arduino)
    set(PROG_PORT /dev/ttyUSB0)

    # AVR Fuses, must be in concordance with your hardware and F_CPU
    # http://eleccelerator.com/fusecalc/fusecalc.php?chip=atmega328p
    set(E_FUSE 0xfd)
    set(H_FUSE 0xda)
    set(L_FUSE 0xfd)
    set(LOCK_BIT 0xff)

    # Use AVR GCC toolchain
    set(CMAKE_SYSTEM_NAME Generic)
    set(CMAKE_CXX_COMPILER avr-g++)
    set(CMAKE_C_COMPILER avr-gcc)
    set(CMAKE_ASM_COMPILER avr-gcc)

    # Pass defines to compiler
    add_definitions(
        -DF_CPU=${F_CPU}
        -DBAUD=${BAUD}
    )

    # Set linker commands including mcu type and generating map file:
    set(CMAKE_EXE_LINKER_FLAGS "-mmcu=${MCU} -Wl,--relax,--gc-sections,-u,vfprintf -lprintf_flt -lm" )

    if (RUN_TEST_SUITE)
      add_compile_options(
        -DCOMPILE_RUN_TEST_SUITE
      )
    endif (RUN_TEST_SUITE)

    add_compile_options(
        -mmcu=${MCU} # MCU
        -std=gnu99 # C99 standard
        -Os # optimize
        -Wall # enable warnings
        -Wno-main
        -Wno-unused-function
        -Wundef
        -pedantic
        -Wstrict-prototypes
        -Werror
        -Wfatal-errors
        -g
        -gdwarf-2
        -funsigned-char # a few optimizations
        -funsigned-bitfields
        -fpack-struct
        -fshort-enums
        -ffunction-sections
        -fdata-sections
        -fno-split-wide-types
        -fno-tree-scev-cprop
    )

    file(GLOB_RECURSE SRC_FILES "src/*.c") # Load all files in src folder

    # Create one target
    add_executable(${PRODUCT_NAME} ${SRC_FILES})

    # Rename the output to .elf as we will create multiple files
    set_target_properties(${PRODUCT_NAME} PROPERTIES OUTPUT_NAME ${PRODUCT_NAME}.elf)

    # Make listing
    add_custom_target(listing ALL avr-objdump -h -S -z ${PRODUCT_NAME}.elf > ${PRODUCT_NAME}.lss DEPENDS ${PRODUCT_NAME})

    # Strip binary for upload
    add_custom_target(strip ALL avr-strip ${PRODUCT_NAME}.elf DEPENDS listing)

    # Show size at this point
    add_custom_target(size ALL avr-size -C --mcu=${MCU} ${PRODUCT_NAME}.elf DEPENDS strip)

    # Transform binary into hex file, we ignore the eeprom segments in the step
    add_custom_target(hex ALL avr-objcopy -R .eeprom -O ihex ${PRODUCT_NAME}.elf ${PRODUCT_NAME}.hex DEPENDS size)

    # Transform binary into hex file, this is the eeprom part (empty if you don't
    # use eeprom static variables)
    add_custom_target(eeprom avr-objcopy -j .eeprom  --set-section-flags=.eeprom="alloc,load"  --change-section-lma .eeprom=0 -O ihex ${PRODUCT_NAME}.elf ${PRODUCT_NAME}.eep DEPENDS strip)

    # Upload the firmware with avrdude
    add_custom_target(upload avrdude  -c ${PROG_TYPE} -P ${PROG_PORT} -p ${MCU} -U flash:w:${PRODUCT_NAME}.hex DEPENDS hex)

    # Upload the eeprom with avrdude
    add_custom_target(upload_eeprom avrdude -c ${PROG_TYPE} -P ${PROG_PORT} -p ${MCU}  -U eeprom:w:${PRODUCT_NAME}.eep DEPENDS eeprom)

    # Burn fuses
    add_custom_target(fuses avrdude -c ${PROG_TYPE} -p ${MCU}  -U lfuse:w:${L_FUSE}:m -U hfuse:w:${H_FUSE}:m -U efuse:w:${E_FUSE}:m -U lock:w:${LOCK_BIT}:m )

    # Clean extra files
    set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${PRODUCT_NAME}.hex;${PRODUCT_NAME}.eeprom;${PRODUCT_NAME}.lst")


