################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
buffer.obj: ../buffer.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/home/nick/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/bin/cl430" -vmspx -Ooff --opt_for_speed=0 --use_hw_mpy=none --include_path="/home/nick/ti/ccsv7/ccs_base/msp430/include" --include_path="/home/nick/workspace/eusci_a_uart_ex1_loopbackAdvanced" --include_path="/home/nick/workspace/eusci_a_uart_ex1_loopbackAdvanced/driverlib/MSP430FR2xx_4xx" --include_path="/home/nick/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/include" --advice:power="all" --advice:hw_config="all" --define=__MSP430FR4133__ --define=DEPRECATED -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="buffer.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

eusci_a_uart_ex1_loopbackAdvanced.obj: ../eusci_a_uart_ex1_loopbackAdvanced.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/home/nick/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/bin/cl430" -vmspx -Ooff --opt_for_speed=0 --use_hw_mpy=none --include_path="/home/nick/ti/ccsv7/ccs_base/msp430/include" --include_path="/home/nick/workspace/eusci_a_uart_ex1_loopbackAdvanced" --include_path="/home/nick/workspace/eusci_a_uart_ex1_loopbackAdvanced/driverlib/MSP430FR2xx_4xx" --include_path="/home/nick/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/include" --advice:power="all" --advice:hw_config="all" --define=__MSP430FR4133__ --define=DEPRECATED -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="eusci_a_uart_ex1_loopbackAdvanced.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

hardware.obj: ../hardware.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/home/nick/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/bin/cl430" -vmspx -Ooff --opt_for_speed=0 --use_hw_mpy=none --include_path="/home/nick/ti/ccsv7/ccs_base/msp430/include" --include_path="/home/nick/workspace/eusci_a_uart_ex1_loopbackAdvanced" --include_path="/home/nick/workspace/eusci_a_uart_ex1_loopbackAdvanced/driverlib/MSP430FR2xx_4xx" --include_path="/home/nick/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/include" --advice:power="all" --advice:hw_config="all" --define=__MSP430FR4133__ --define=DEPRECATED -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="hardware.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

interrupts.obj: ../interrupts.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/home/nick/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/bin/cl430" -vmspx -Ooff --opt_for_speed=0 --use_hw_mpy=none --include_path="/home/nick/ti/ccsv7/ccs_base/msp430/include" --include_path="/home/nick/workspace/eusci_a_uart_ex1_loopbackAdvanced" --include_path="/home/nick/workspace/eusci_a_uart_ex1_loopbackAdvanced/driverlib/MSP430FR2xx_4xx" --include_path="/home/nick/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/include" --advice:power="all" --advice:hw_config="all" --define=__MSP430FR4133__ --define=DEPRECATED -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="interrupts.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


