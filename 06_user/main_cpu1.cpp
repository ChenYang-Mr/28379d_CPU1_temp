#include "Includes.h"

DRV8323_Obj drv8323;
DRV_SPI_8323_Vars_t drv8323_vars;
DRV_SPI_8323_Vars_t drv8323_vars_back;
//
// Globals
//
volatile uint16_t sData[2];         // Send data buffer
volatile uint16_t rData[2];         // Receive data buffer
volatile uint16_t rDataPoint = 0;   // To keep track of where we are in the
                                    // data stream to check received data

void configGPIOs(void);
void configGPIOs_slave(void);

void initSPIAMaster(void);
void initSPIBSlave(void);
void main(void)
 {
//确定运行模式
#ifdef _STANDALONE
#ifdef _FLASH

    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH);
#else

    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_RAM);
#endif
#endif

    //设备初始化
    Device_init();

    //GPIO初始化
    Device_initGPIO();

    Interrupt_initModule();
    Interrupt_initVectorTable();
    //开启总中断
    Interrupt_enableMaster();

    configGPIOs();

//    configGPIOs_slave();

    //
    // Set up SPI A as Master, initializing it for FIFO mode
    //
    initSPIAMaster();
#define DRV8323

#ifndef DRV8323
//    initSPIBSlave();

    sData[0] = 0;
    int RxFifoCnt = 0;
    int WaitTimeOut = 0;
    while(1)
    {
        SPI_resetRxFIFO(SPIB_BASE);
        sData[0] = sData[0] + 1;
        if(sData[0]>100)
            sData[0] = 0;
        
        // //  SPI_write(obj->spiHandle,ctrlWord);
         SPI_writeDataBlockingFIFO(SPIA_BASE, sData[0]);

         // wait for the response to populate the RX fifo, else a wait timeout will occur
         //  while((RxFifoCnt < SPI_FifoStatus_1_Word) && (WaitTimeOut < 0xffff))
         while((RxFifoCnt < SPI_FIFO_RX16) && (WaitTimeOut < 0xffff))
         {
             //    RxFifoCnt = SPI_getRxFifoStatus(obj->spiHandle);
                 RxFifoCnt = SPI_getRxFIFOStatus(SPIA_BASE);
             if(++WaitTimeOut > 0xfffe)
             {
                 while(1);
             }
         }
        rData[0] = SPI_readDataNonBlocking(SPIB_BASE);

        rData[1] = SPI_readDataBlockingFIFO(SPIB_BASE);
    }
#endif

#ifdef DRV8323

    DRV8323_Handle pdrv8323 = DRV8323_init(&drv8323,sizeof(DRV8323_Obj));
    DRV8323_setGpioNumber(pdrv8323,125);        //scs pin
    DRV8323_setSpiHandle(pdrv8323,SPIA_BASE);

    // turn on the DRV8301 if present
    while(1)
    {
        DRV8323_enable(&drv8323);
        DRV8323_setupSpi(&drv8323,&drv8323_vars);
        drv8323_vars.Ctrl_Reg_02.BRAKE = true;
        DRV8323_writeData(&drv8323,&drv8323_vars);
        DRV8323_readData(&drv8323,&drv8323_vars_back);
    }
#endif

    GPIO_setPinConfig(DEVICE_GPIO_CFG_LED1);
    GPIO_setMasterCore(DEVICE_GPIO_PIN_LED1, GPIO_CORE_CPU1);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);

    GPIO_setPinConfig(DEVICE_GPIO_CFG_LED2);
    GPIO_setMasterCore(DEVICE_GPIO_PIN_LED2, GPIO_CORE_CPU2);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED2, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED2, GPIO_DIR_MODE_OUT);


    while(1)
    {
        GPIO_togglePin(DEVICE_GPIO_PIN_LED1);
        delay_s(1);
    }
}



//
// Configure GPIOs for external loopback.
//
void configGPIOs(void)
{
    //
    // This test is designed for an external loopback between SPIA
    //
    // SPISIMOA.
    //
    GPIO_setMasterCore(58, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_58_SPISIMOA);
    GPIO_setPadConfig(58, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(58, GPIO_QUAL_ASYNC);

    //
    // SPISOMIA.
    //
    GPIO_setMasterCore(59, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_59_SPISOMIA);
    GPIO_setPadConfig(59, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(59, GPIO_QUAL_ASYNC);

    //
    // SPICLKA.
    //
    GPIO_setMasterCore(60, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_60_SPICLKA);
    GPIO_setPadConfig(60, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(60, GPIO_QUAL_ASYNC);

    //
    // SPISTEA.
    //
    GPIO_setMasterCore(125, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_125_GPIO125);
    GPIO_setPadConfig(125, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(125, GPIO_QUAL_ASYNC);
    GPIO_setDirectionMode(125, GPIO_DIR_MODE_OUT);

    //DRV8323 ENABLE
    GPIO_setPinConfig(GPIO_67_GPIO67);
    GPIO_setMasterCore(67, GPIO_CORE_CPU1);
    GPIO_setPadConfig(67, GPIO_PIN_TYPE_PULLUP);
    GPIO_setDirectionMode(67, GPIO_DIR_MODE_OUT);
    GPIO_setQualificationMode(67, GPIO_QUAL_ASYNC);
    GPIO_writePin(67, 1);

}

//
// Configure GPIOs for external loopback.
//
void configGPIOs_slave(void)
{
    //
    // This test is designed for an external loopback between SPIA
    //
    // SPISIMOA.
    //
    GPIO_setMasterCore(63, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_63_SPISIMOB);
    GPIO_setPadConfig(63, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(63, GPIO_QUAL_ASYNC);

    //
    // SPISOMIA.
    //
    GPIO_setMasterCore(64, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_64_SPISOMIB);
    GPIO_setPadConfig(64, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(64, GPIO_QUAL_ASYNC);

    //
    // SPICLKA.
    //
    GPIO_setMasterCore(65, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_65_SPICLKB);
    GPIO_setPadConfig(65, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(65, GPIO_QUAL_ASYNC);

    //
    // SPISTEA.
    //
    GPIO_setMasterCore(66, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_66_SPISTEB);
    GPIO_setPadConfig(66, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(66, GPIO_QUAL_ASYNC);

}

//
// Function to configure SPI A as master with FIFO enabled.
//
void initSPIAMaster(void)
{
    //
    // Must put SPI into reset before configuring it
    //
    SPI_disableModule(SPIA_BASE);

    //
    // SPI configuration. Use a 500kHz SPICLK and 16-bit word size.
    //
    SPI_setConfig(SPIA_BASE, DEVICE_LSPCLK_FREQ, SPI_PROT_POL0PHA0,
                  SPI_MODE_MASTER, 500000, 16);
    SPI_disableLoopback(SPIA_BASE);
    SPI_setEmulationMode(SPIA_BASE, SPI_EMULATION_FREE_RUN);

    //
    // FIFO and interrupt configuration
    //
    SPI_enableFIFO(SPIA_BASE);
//    SPI_clearInterruptStatus(SPIA_BASE, SPI_INT_RXFF);
//    SPI_setFIFOInterruptLevel(SPIA_BASE, SPI_FIFO_TX2, SPI_FIFO_RX2);
//    SPI_enableInterrupt(SPIA_BASE, SPI_INT_RXFF);

    //
    // Configuration complete. Enable the module.
    //
    SPI_enableModule(SPIA_BASE);
}

//
// Function to configure SPI A as master with FIFO enabled.
//
void initSPIBSlave(void)
{
    //
    // Must put SPI into reset before configuring it
    //
    SPI_disableModule(SPIB_BASE);

    //
    // SPI configuration. Use a 500kHz SPICLK and 16-bit word size.
    //
    SPI_setConfig(SPIB_BASE, DEVICE_LSPCLK_FREQ, SPI_PROT_POL0PHA0,
                  SPI_MODE_SLAVE, 500000, 16);
    SPI_disableLoopback(SPIB_BASE);
    SPI_setEmulationMode(SPIB_BASE, SPI_EMULATION_FREE_RUN);

    //
    // FIFO and interrupt configuration
    //
    SPI_enableFIFO(SPIB_BASE);
//    SPI_clearInterruptStatus(SPIA_BASE, SPI_INT_RXFF);
//    SPI_setFIFOInterruptLevel(SPIA_BASE, SPI_FIFO_TX2, SPI_FIFO_RX2);
//    SPI_enableInterrupt(SPIA_BASE, SPI_INT_RXFF);

    //
    // Configuration complete. Enable the module.
    //
    SPI_enableModule(SPIB_BASE);
}
