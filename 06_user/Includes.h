#ifndef INCLUDES_H_
#define INCLUDES_H_

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

#define u16 unsigned int
#define u32 unsigned long
#define u64 unsigned long long

#define s16 signed int
#define s32 signed long
#define s64 signed long long

/************************************************************************************/
/*********************************		延时函数		*********************************/
#define delay_s(x) SysCtl_delay(((((long double)(x)) / (1.0L /  \
                              (long double)DEVICE_SYSCLK_FREQ)) - 9.0L) / 5.0L)

#define delay_ms(x) SysCtl_delay(((((long double)(x)) / (1000.0L /  \
                              (long double)DEVICE_SYSCLK_FREQ)) - 9.0L) / 5.0L)

#define delay_us(x) SysCtl_delay(((((long double)(x)) / (1000000.0L /  \
                              (long double)DEVICE_SYSCLK_FREQ)) - 9.0L) / 5.0L)

#define delay_ns(x) SysCtl_delay(((((long double)(x)) / (1000000000.0L /  \
                              (long double)DEVICE_SYSCLK_FREQ)) - 9.0L) / 5.0L)
/************************************************************************************/
/*********************************		头文件		*********************************/
#include "F2837xD_Ipc_drivers.h"

#include "driverlib.h"
#include "device.h"
#include "drv8323.h"

//#include "Data_Flow.h"

//#include "..\6.my_driver\Interrupt_function\Interrupt_function.h"
//#include "..\6.my_driver\my_SCI\my_SCI.h"
//#include "..\6.my_driver\my_SCI\micro_printf.h"
//#include "..\6.my_driver\my_SCI\NiMing.h"
//#include "..\6.my_driver\my_ePWM\my_ePWM.h"
//#include "..\6.my_driver\my_IIC\my_IIC.h"
//#include "..\6.my_driver\my_SPI\my_SPI.h"
//#include "..\6.my_driver\my_TIMER\my_TIMER.h"

//#include "..\7.my_device\1.IMU\BMI088.h"
//#include "..\7.my_device\1.IMU\IST8310.h"
//#include "..\7.my_device\1.IMU\my_IMU.h"
/************************************************************************************/

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif
