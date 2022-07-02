################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
07_driver/drv8323/%.obj: ../07_driver/drv8323/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/SOFTWARE/ti/ccs1011/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O2 --fp_mode=strict --include_path="C:/Users/Administrator/Desktop/28379d_CPU1_temp" --include_path="D:/SOFTWARE/ti/ccs1011/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --include_path="C:/Users/Administrator/Desktop/28379d_CPU1_temp/03_device/include" --include_path="C:/Users/Administrator/Desktop/28379d_CPU1_temp/04_common/include" --include_path="C:/Users/Administrator/Desktop/28379d_CPU1_temp/05_headers/include" --include_path="C:/Users/Administrator/Desktop/28379d_CPU1_temp/06_user" --include_path="C:/Users/Administrator/Desktop/28379d_CPU1_temp/07_driver/drv8323" --advice:performance=all --define=CPU1 --define=_LAUNCHXL_F28379D --define=_FLASH --define=_STANDALONE --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="07_driver/drv8323/$(basename $(<F)).d_raw" --obj_directory="07_driver/drv8323" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


