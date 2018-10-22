/*******************************************************************************
* File Name: RPi_SPIS.h
* Version 2.70
*
* Description:
*  Contains the function prototypes, constants and register definition
*  of the SPI Slave Component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SPIS_RPi_SPIS_H)
#define CY_SPIS_RPi_SPIS_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define RPi_SPIS_DATA_WIDTH                  (8u)
#define RPi_SPIS_INTERNAL_TX_INT_ENABLED     (0u)
#define RPi_SPIS_INTERNAL_RX_INT_ENABLED     (1u)
#define RPi_SPIS_MODE_USE_ZERO               (1u)
#define RPi_SPIS_BIDIRECTIONAL_MODE          (0u)
#define RPi_SPIS_MODE                        (0u)

#define RPi_SPIS_FIFO_SIZE                  (4u)
/* Internal interrupt handling */
#define RPi_SPIS_TX_BUFFER_SIZE             (4u)
#define RPi_SPIS_RX_BUFFER_SIZE             (4u)
#define RPi_SPIS_INTERNAL_TX_INT_ENABLED    (0u)
#define RPi_SPIS_INTERNAL_RX_INT_ENABLED    (1u)

#define RPi_SPIS_TX_SOFTWARE_BUF_ENABLED    ((0u != RPi_SPIS_INTERNAL_TX_INT_ENABLED) && \
                                                     (RPi_SPIS_TX_BUFFER_SIZE > RPi_SPIS_FIFO_SIZE))

#define RPi_SPIS_RX_SOFTWARE_BUF_ENABLED    ((0u != RPi_SPIS_INTERNAL_RX_INT_ENABLED) && \
                                                     (RPi_SPIS_RX_BUFFER_SIZE > RPi_SPIS_FIFO_SIZE))


/***************************************
*        Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
    uint8 cntrPeriod;
} RPi_SPIS_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  RPi_SPIS_Init(void) ;
void  RPi_SPIS_Enable(void) ;
void  RPi_SPIS_Start(void) ;
void  RPi_SPIS_Stop(void) ;
void  RPi_SPIS_EnableTxInt(void) ;
void  RPi_SPIS_EnableRxInt(void) ;
void  RPi_SPIS_DisableTxInt(void) ;
void  RPi_SPIS_DisableRxInt(void) ;
void  RPi_SPIS_SetTxInterruptMode(uint8 intSrc) ;
void  RPi_SPIS_SetRxInterruptMode(uint8 intSrc) ;
uint8 RPi_SPIS_ReadTxStatus(void) ;
uint8 RPi_SPIS_ReadRxStatus(void) ;
void  RPi_SPIS_WriteTxData(uint8 txData);

#if(RPi_SPIS_MODE_USE_ZERO != 0u)
    void  RPi_SPIS_WriteTxDataZero(uint8 txDataByte) \
                                              ;
#endif /* (RPi_SPIS_MODE_USE_ZERO != 0u) */

uint8 RPi_SPIS_ReadRxData(void) ;
uint8 RPi_SPIS_GetRxBufferSize(void) ;
uint8 RPi_SPIS_GetTxBufferSize(void) ;
void  RPi_SPIS_ClearRxBuffer(void) ;
void  RPi_SPIS_ClearTxBuffer(void) ;

#if (RPi_SPIS_BIDIRECTIONAL_MODE != 0u)
    void  RPi_SPIS_TxEnable(void) ;
    void  RPi_SPIS_TxDisable(void) ;
#endif /* RPi_SPIS_BIDIRECTIONAL_MODE != 0u */

void  RPi_SPIS_PutArray(const uint8 buffer[], uint8 byteCount) ;
void  RPi_SPIS_ClearFIFO(void) ;
void  RPi_SPIS_Sleep(void) ;
void  RPi_SPIS_Wakeup(void) ;
void  RPi_SPIS_SaveConfig(void) ;
void  RPi_SPIS_RestoreConfig(void) ;

/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_RPi_SPIS) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    RPi_SPIS_CyBtldrCommStart(void) CYSMALL ;
    void    RPi_SPIS_CyBtldrCommStop(void) CYSMALL ;
    void    RPi_SPIS_CyBtldrCommReset(void) CYSMALL ;
    cystatus RPi_SPIS_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus RPi_SPIS_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_RPi_SPIS)
        #define CyBtldrCommStart    RPi_SPIS_CyBtldrCommStart
        #define CyBtldrCommStop     RPi_SPIS_CyBtldrCommStop
        #define CyBtldrCommReset    RPi_SPIS_CyBtldrCommReset
        #define CyBtldrCommWrite    RPi_SPIS_CyBtldrCommWrite
        #define CyBtldrCommRead     RPi_SPIS_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_RPi_SPIS) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define RPi_SPIS_BYTE2BYTE_TIME_OUT (1u)

#endif /* (CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_RPi_SPIS) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)) */


CY_ISR_PROTO(RPi_SPIS_TX_ISR);
CY_ISR_PROTO(RPi_SPIS_RX_ISR);

/* Macros for getting software status of SPIS Statusi Register */
#define RPi_SPIS_GET_STATUS_TX(swTxSts) ( (uint8)(RPi_SPIS_TX_STATUS_REG | \
                                                       ((swTxSts) & RPi_SPIS_STS_CLR_ON_RD_BYTES_MASK)) )
#define RPi_SPIS_GET_STATUS_RX(swRxSts) ( (uint8)(RPi_SPIS_RX_STATUS_REG | \
                                                       ((swRxSts) & RPi_SPIS_STS_CLR_ON_RD_BYTES_MASK)) )


/***************************************
*   Variable with external linkage
***************************************/

extern uint8 RPi_SPIS_initVar;


/***************************************
*           API Constants
***************************************/

#define RPi_SPIS_TX_ISR_NUMBER     ((uint8)RPi_SPIS_TxInternalInterrupt__INTC_NUMBER)
#define RPi_SPIS_RX_ISR_NUMBER     ((uint8)RPi_SPIS_RxInternalInterrupt__INTC_NUMBER)
#define RPi_SPIS_TX_ISR_PRIORITY   ((uint8)RPi_SPIS_TxInternalInterrupt__INTC_PRIOR_NUM)
#define RPi_SPIS_RX_ISR_PRIORITY   ((uint8)RPi_SPIS_RxInternalInterrupt__INTC_PRIOR_NUM)


/***************************************
*    Initial Parameter Constants
***************************************/

#define RPi_SPIS_INT_ON_SPI_DONE    (uint8)(0u << RPi_SPIS_STS_SPI_DONE_SHIFT)
#define RPi_SPIS_INT_ON_TX_EMPTY    (uint8)(0u << RPi_SPIS_STS_TX_FIFO_EMPTY_SHIFT)
#define RPi_SPIS_INT_ON_TX_NOT_FULL (uint8)(0u << RPi_SPIS_STS_TX_FIFO_NOT_FULL_SHIFT)
#define RPi_SPIS_INT_ON_BYTE_COMP   (uint8)(0u << RPi_SPIS_STS_BYTE_COMPLETE_SHIFT)

#define RPi_SPIS_TX_INIT_INTERRUPTS_MASK  (RPi_SPIS_INT_ON_SPI_DONE | \
                                            RPi_SPIS_INT_ON_TX_EMPTY | RPi_SPIS_INT_ON_TX_NOT_FULL | \
                                            RPi_SPIS_INT_ON_BYTE_COMP)

#define RPi_SPIS_INT_ON_RX_EMPTY     (uint8)(0u << RPi_SPIS_STS_RX_FIFO_EMPTY_SHIFT)
#define RPi_SPIS_INT_ON_RX_NOT_EMPTY (uint8)(0u << RPi_SPIS_STS_RX_FIFO_NOT_EMPTY_SHIFT)
#define RPi_SPIS_INT_ON_RX_OVER      (uint8)(0u << RPi_SPIS_STS_RX_FIFO_OVERRUN_SHIFT)
#define RPi_SPIS_INT_ON_RX_FULL      (uint8)(0u << RPi_SPIS_STS_RX_FIFO_FULL_SHIFT)

#define RPi_SPIS_RX_INIT_INTERRUPTS_MASK (RPi_SPIS_INT_ON_RX_EMPTY | \
                                            RPi_SPIS_INT_ON_RX_NOT_EMPTY | RPi_SPIS_INT_ON_RX_OVER | \
                                            RPi_SPIS_INT_ON_RX_FULL)

#define RPi_SPIS_BITCTR_INIT           (RPi_SPIS_DATA_WIDTH - 1u)

#define RPi_SPIS__MODE_00 0
#define RPi_SPIS__MODE_01 1
#define RPi_SPIS__MODE_10 2
#define RPi_SPIS__MODE_11 3


#define RPi_SPIS_TX_BUFFER_SIZE         (4u)
#define RPi_SPIS_RX_BUFFER_SIZE         (4u)

/* Following definitions are for version Compatibility, they are obsolete.
*  Please do not use it in new projects
*/
#define RPi_SPIS_INIT_INTERRUPTS_MASK  (RPi_SPIS_INT_ON_SPI_DONE | RPi_SPIS_INT_ON_TX_EMPTY | \
                                            RPi_SPIS_INT_ON_TX_NOT_FULL | RPi_SPIS_INT_ON_RX_EMPTY | \
                                            RPi_SPIS_INT_ON_RX_NOT_EMPTY | RPi_SPIS_INT_ON_RX_OVER | \
                                            RPi_SPIS_INT_ON_BYTE_COMP)


/***************************************
*             Registers
***************************************/
#if(CY_PSOC3 || CY_PSOC5)
    #define RPi_SPIS_TXDATA_ZERO_REG          (* (reg8  *) \
            RPi_SPIS_BSPIS_sR8_Dp_u0__A0_REG)

    #define RPi_SPIS_TXDATA_ZERO_PTR           (  (reg8  *) \
            RPi_SPIS_BSPIS_sR8_Dp_u0__A0_REG)

    #define RPi_SPIS_RXDATA_ZERO_REG           (* (reg8  *) \
            RPi_SPIS_BSPIS_sR8_Dp_u0__A0_REG)

    #define RPi_SPIS_RXDATA_ZERO_PTR           (  (reg8  *) \
            RPi_SPIS_BSPIS_sR8_Dp_u0__A0_REG)

    #define RPi_SPIS_TXDATA_REG                (* (reg8  *) \
            RPi_SPIS_BSPIS_sR8_Dp_u0__F0_REG)

    #define RPi_SPIS_TXDATA_PTR                (  (reg8  *) \
            RPi_SPIS_BSPIS_sR8_Dp_u0__F0_REG)

    #define RPi_SPIS_RXDATA_REG                (* (reg8  *) \
            RPi_SPIS_BSPIS_sR8_Dp_u0__F1_REG)

    #define RPi_SPIS_RXDATA_PTR                (  (reg8  *) \
            RPi_SPIS_BSPIS_sR8_Dp_u0__F1_REG)
#else
    #if(RPi_SPIS_DATA_WIDTH <= 8u) /* 8bit - SPIS */
        #define RPi_SPIS_TXDATA_ZERO_REG           (* (reg8 *) \
                RPi_SPIS_BSPIS_sR8_Dp_u0__A0_REG)

        #define RPi_SPIS_TXDATA_ZERO_PTR           (  (reg8  *) \
                RPi_SPIS_BSPIS_sR8_Dp_u0__A0_REG)

        #define RPi_SPIS_RXDATA_ZERO_REG           (* (reg8  *) \
                RPi_SPIS_BSPIS_sR8_Dp_u0__A0_REG)

        #define RPi_SPIS_RXDATA_ZERO_PTR           (  (reg8 *) \
                RPi_SPIS_BSPIS_sR8_Dp_u0__A0_REG)

        #define RPi_SPIS_TXDATA_REG                (* (reg8  *) \
                RPi_SPIS_BSPIS_sR8_Dp_u0__F0_REG)

        #define RPi_SPIS_TXDATA_PTR                (  (reg8  *) \
                RPi_SPIS_BSPIS_sR8_Dp_u0__F0_REG)

        #define RPi_SPIS_RXDATA_REG                (* (reg8  *) \
                RPi_SPIS_BSPIS_sR8_Dp_u0__F1_REG)

        #define RPi_SPIS_RXDATA_PTR                (  (reg8  *) \
                RPi_SPIS_BSPIS_sR8_Dp_u0__F1_REG)
    #else /* 16bit - SPIS */
        #define RPi_SPIS_TXDATA_ZERO_REG           (* (reg16  *) \
                RPi_SPIS_BSPIS_sR8_Dp_u0__16BIT_A0_REG)

        #define RPi_SPIS_TXDATA_ZERO_PTR           (  (reg16  *) \
                RPi_SPIS_BSPIS_sR8_Dp_u0__16BIT_A0_REG)

        #define RPi_SPIS_RXDATA_ZERO_REG           (* (reg16  *) \
                RPi_SPIS_BSPIS_sR8_Dp_u0__16BIT_A0_REG)

        #define RPi_SPIS_RXDATA_ZERO_PTR           (  (reg16  *) \
                RPi_SPIS_BSPIS_sR8_Dp_u0__16BIT_A0_REG)

        #define RPi_SPIS_TXDATA_REG                (* (reg16  *) \
                RPi_SPIS_BSPIS_sR8_Dp_u0__16BIT_F0_REG)

        #define RPi_SPIS_TXDATA_PTR                (  (reg16  *) \
                RPi_SPIS_BSPIS_sR8_Dp_u0__16BIT_F0_REG)

        #define RPi_SPIS_RXDATA_REG                (* (reg16  *) \
                RPi_SPIS_BSPIS_sR8_Dp_u0__16BIT_F1_REG)

        #define RPi_SPIS_RXDATA_PTR                (  (reg16 *) \
                RPi_SPIS_BSPIS_sR8_Dp_u0__16BIT_F1_REG)
    #endif /* (RPi_SPIS_DATA_WIDTH <= 8u) */
#endif     /* (CY_PSOC3 || CY_PSOC5) */

#define RPi_SPIS_TX_AUX_CONTROL_DP0_REG       (* (reg8 *) \
        RPi_SPIS_BSPIS_sR8_Dp_u0__DP_AUX_CTL_REG)
#define RPi_SPIS_TX_AUX_CONTROL_DP0_PTR       (  (reg8 *) \
        RPi_SPIS_BSPIS_sR8_Dp_u0__DP_AUX_CTL_REG)

#define RPi_SPIS_RX_AUX_CONTROL_DP0_REG       (* (reg8 *) \
        RPi_SPIS_BSPIS_sR8_Dp_u0__DP_AUX_CTL_REG)
#define RPi_SPIS_RX_AUX_CONTROL_DP0_PTR       (  (reg8 *) \
        RPi_SPIS_BSPIS_sR8_Dp_u0__DP_AUX_CTL_REG)

#if(RPi_SPIS_DATA_WIDTH > 8u)

    #define RPi_SPIS_TX_AUX_CONTROL_DP1_REG   (* (reg8 *) \
            RPi_SPIS_BSPIS_sR8_Dp_u1__DP_AUX_CTL_REG)
    #define RPi_SPIS_TX_AUX_CONTROL_DP1_PTR   (  (reg8 *) \
            RPi_SPIS_BSPIS_sR8_Dp_u1__DP_AUX_CTL_REG)

    #define RPi_SPIS_RX_AUX_CONTROL_DP1_REG   (* (reg8 *) \
            RPi_SPIS_BSPIS_sR8_Dp_u1__DP_AUX_CTL_REG)
    #define RPi_SPIS_RX_AUX_CONTROL_DP1_PTR   (  (reg8 *) \
            RPi_SPIS_BSPIS_sR8_Dp_u1__DP_AUX_CTL_REG)

#endif /* RPi_SPIS_DATA_WIDTH > 8u */


#define RPi_SPIS_COUNTER_PERIOD_REG    (* (reg8 *) \
        RPi_SPIS_BSPIS_BitCounter__PERIOD_REG)
#define RPi_SPIS_COUNTER_PERIOD_PTR    (  (reg8 *) \
        RPi_SPIS_BSPIS_BitCounter__PERIOD_REG)

#define RPi_SPIS_TX_STATUS_MASK_REG    (* (reg8 *) \
        RPi_SPIS_BSPIS_TxStsReg__MASK_REG)
#define RPi_SPIS_TX_STATUS_MASK_PTR    (  (reg8 *) \
        RPi_SPIS_BSPIS_TxStsReg__MASK_REG)

#define RPi_SPIS_RX_STATUS_MASK_REG    (* (reg8 *) \
        RPi_SPIS_BSPIS_RxStsReg__MASK_REG)
#define RPi_SPIS_RX_STATUS_MASK_PTR    (  (reg8 *) \
        RPi_SPIS_BSPIS_RxStsReg__MASK_REG)

#define RPi_SPIS_ONE_REG               (* (reg8 *) \
        RPi_SPIS_BSPIS_SPISlave_dpCounter_u0__D1_REG)
#define RPi_SPIS_ONE_PTR               (  (reg8 *) \
        RPi_SPIS_BSPIS_dpCounter_u0__D1_REG)

#define RPi_SPIS_TX_STATUS_REG         (* (reg8 *) \
        RPi_SPIS_BSPIS_TxStsReg__STATUS_REG)
#define RPi_SPIS_TX_STATUS_PTR         (  (reg8 *) \
        RPi_SPIS_BSPIS__TxStsReg__STATUS_REG)

#define RPi_SPIS_RX_STATUS_REG         (* (reg8 *) \
        RPi_SPIS_BSPIS_RxStsReg__STATUS_REG)
#define RPi_SPIS_RX_STATUS_PTR         (  (reg8 *) \
        RPi_SPIS_BSPIS_RxStsReg__STATUS_REG)

#define RPi_SPIS_COUNTER_CONTROL_REG   (* (reg8 *) \
        RPi_SPIS_BSPIS_BitCounter__CONTROL_AUX_CTL_REG)
#define RPi_SPIS_COUNTER_CONTROL_PTR   (  (reg8 *) \
        RPi_SPIS_BSPIS_BitCounter__CONTROL_AUX_CTL_REG)

#define RPi_SPIS_TX_STATUS_ACTL_REG    (* (reg8 *) \
        RPi_SPIS_BSPIS_TxStsReg__STATUS_AUX_CTL_REG)
#define RPi_SPIS_TX_STATUS_ACTL_PTR    (  (reg8 *) \
        RPi_SPIS_TX_BSPIS_TxStsReg__STATUS_AUX_CTL_REG)

#define RPi_SPIS_RX_STATUS_ACTL_REG    (* (reg8 *) \
        RPi_SPIS_BSPIS_RxStsReg__STATUS_AUX_CTL_REG)
#define RPi_SPIS_RX_STATUS_ACTL_PTR    (  (reg8 *) \
        RPi_SPIS_RX_BSPIS_RxStsReg__STATUS_AUX_CTL_REG)

#if(RPi_SPIS_BIDIRECTIONAL_MODE)

    #define RPi_SPIS_CONTROL_REG       (* (reg8 *) \
   RPi_SPIS_BSPIS_SyncCtl_CtrlReg__CONTROL_REG)
    #define RPi_SPIS_CONTROL_PTR       (  (reg8 *) \
   RPi_SPIS_BSPIS_SyncCtl_CtrlReg__CONTROL_REG)

#endif /* RPi_SPIS_BIDIRECTIONAL_MODE */


/***************************************
*       Register Constants
***************************************/

/* Status Register Definitions */
#define RPi_SPIS_STS_SPI_DONE_SHIFT             (0x00u)
#define RPi_SPIS_STS_TX_FIFO_NOT_FULL_SHIFT     (0x01u)
#define RPi_SPIS_STS_TX_FIFO_EMPTY_SHIFT        (0x02u)
#define RPi_SPIS_STS_RX_FIFO_NOT_EMPTY_SHIFT    (0x03u)
#define RPi_SPIS_STS_RX_FIFO_EMPTY_SHIFT        (0x04u)
#define RPi_SPIS_STS_RX_FIFO_OVERRUN_SHIFT      (0x05u)
#define RPi_SPIS_STS_RX_FIFO_FULL_SHIFT         (0x06u)
#define RPi_SPIS_STS_BYTE_COMPLETE_SHIFT        (0x06u)

#define RPi_SPIS_STS_SPI_DONE                   ((uint8)(0x01u << RPi_SPIS_STS_SPI_DONE_SHIFT))
#define RPi_SPIS_STS_TX_FIFO_EMPTY              ((uint8)(0x01u << RPi_SPIS_STS_TX_FIFO_EMPTY_SHIFT))
#define RPi_SPIS_STS_TX_FIFO_NOT_FULL           ((uint8)(0x01u << RPi_SPIS_STS_TX_FIFO_NOT_FULL_SHIFT))
#define RPi_SPIS_STS_RX_FIFO_EMPTY              ((uint8)(0x01u << RPi_SPIS_STS_RX_FIFO_EMPTY_SHIFT))
#define RPi_SPIS_STS_RX_FIFO_NOT_EMPTY          ((uint8)(0x01u << RPi_SPIS_STS_RX_FIFO_NOT_EMPTY_SHIFT))
#define RPi_SPIS_STS_RX_FIFO_OVERRUN            ((uint8)(0x01u << RPi_SPIS_STS_RX_FIFO_OVERRUN_SHIFT))
#define RPi_SPIS_STS_RX_FIFO_FULL               ((uint8)(0x01u << RPi_SPIS_STS_RX_FIFO_FULL_SHIFT))
#define RPi_SPIS_STS_BYTE_COMPLETE              ((uint8)(0x01u << RPi_SPIS_STS_BYTE_COMPLETE_SHIFT))

#define RPi_SPIS_STS_CLR_ON_RD_BYTES_MASK       (0x61u)

/* StatusI Register Interrupt Enable Control Bits */
/* As defined by the Register map for the AUX Control Register */
#define RPi_SPIS_INT_ENABLE                     (0x10u)
#define RPi_SPIS_TX_FIFO_CLR    (0x01u) /* F0 - TX FIFO */
#define RPi_SPIS_RX_FIFO_CLR    (0x02u) /* F1 - RX FIFO */
#define RPi_SPIS_FIFO_CLR       (RPi_SPIS_TX_FIFO_CLR | RPi_SPIS_RX_FIFO_CLR)

/* Bit Counter (7-bit) Control Register Bit Definitions */
/* As defined by the Register map for the AUX Control Register */
#define RPi_SPIS_CNTR_ENABLE                    (0x20u)

/* Bi-Directional mode control bit */
#define RPi_SPIS_CTRL_TX_SIGNAL_EN              (0x01u)

/* Datapath Auxillary Control Register definitions */
#define RPi_SPIS_AUX_CTRL_FIFO0_CLR             (0x00u)
#define RPi_SPIS_AUX_CTRL_FIFO1_CLR             (0x00u)
#define RPi_SPIS_AUX_CTRL_FIFO0_LVL             (0x00u)
#define RPi_SPIS_AUX_CTRL_FIFO1_LVL             (0x00u)
#define RPi_SPIS_STATUS_ACTL_INT_EN_MASK        (0x10u)

/* Component disabled */
#define RPi_SPIS_DISABLED   (0u)

/***************************************
* The following code is DEPRECATED and 
* should not be used in new projects.
***************************************/

#define RPi_SPIS_TXDATA_ZERO               (RPi_SPIS_TXDATA_ZERO_REG)
#define RPi_SPIS_TXDATA                    (RPi_SPIS_TXDATA_REG)
#define RPi_SPIS_RXDATA                    (RPi_SPIS_RXDATA_REG)
#define RPi_SPIS_MISO_AUX_CONTROLDP0       (RPi_SPIS_MISO_AUX_CTRL_DP0_REG)
#define RPi_SPIS_MOSI_AUX_CONTROLDP0       (RPi_SPIS_MOSI_AUX_CTRL_DP0_REG)
#define RPi_SPIS_TXBUFFERREAD              (RPi_SPIS_txBufferRead)
#define RPi_SPIS_TXBUFFERWRITE             (RPi_SPIS_txBufferWrite)
#define RPi_SPIS_RXBUFFERREAD              (RPi_SPIS_rxBufferRead)
#define RPi_SPIS_RXBUFFERWRITE             (RPi_SPIS_rxBufferWrite)

#if(RPi_SPIS_DATA_WIDTH > 8u)

    #define RPi_SPIS_MISO_AUX_CONTROLDP1   (RPi_SPIS_MISO_AUX_CTRL_DP1_REG)
    #define RPi_SPIS_MOSI_AUX_CONTROLDP1   (RPi_SPIS_MOSI_AUX_CTRL_DP0_REG)

#endif /* RPi_SPIS_DATA_WIDTH > 8u */

#define RPi_SPIS_COUNTER_PERIOD            (RPi_SPIS_COUNTER_PERIOD_REG)
#define RPi_SPIS_COUNTER_CONTROL           (RPi_SPIS_COUNTER_CONTROL_REG)
#define RPi_SPIS_ONE                       (RPi_SPIS_ONE_REG)
#define RPi_SPIS_STATUS                    (RPi_SPIS_TX_STATUS_REG)
#define RPi_SPIS_STATUS_MASK               (RPi_SPIS_TX_STATUS_MASK_REG)
#define RPi_SPIS_STATUS_ACTL               (RPi_SPIS_TX_STATUS_ACTL_REG)

#define RPi_SPIS_WriteByte      (RPi_SPIS_WriteTxData)
#define RPi_SPIS_ReadByte       (RPi_SPIS_ReadRxData)
#define RPi_SPIS_WriteByteZero  (RPi_SPIS_WriteTxDataZero)
void  RPi_SPIS_SetInterruptMode(uint8 intSrc) ;
uint8 RPi_SPIS_ReadStatus(void) ;
void  RPi_SPIS_EnableInt(void) ;
void  RPi_SPIS_DisableInt(void) ;

#define RPi_SPIS_STS_TX_BUF_NOT_FULL_SHIFT      (0x01u)
#define RPi_SPIS_STS_TX_BUF_FULL_SHIFT          (0x02u)
#define RPi_SPIS_STS_RX_BUF_NOT_EMPTY_SHIFT     (0x03u)
#define RPi_SPIS_STS_RX_BUF_EMPTY_SHIFT         (0x04u)
#define RPi_SPIS_STS_RX_BUF_OVERRUN_SHIFT       (0x05u)

#define RPi_SPIS_STS_TX_BUF_NOT_FULL            ((uint8)(0x01u << RPi_SPIS_STS_TX_BUF_NOT_FULL_SHIFT))
#define RPi_SPIS_STS_TX_BUF_FULL                ((uint8)(0x01u << RPi_SPIS_STS_TX_BUF_FULL_SHIFT))
#define RPi_SPIS_STS_RX_BUF_NOT_EMPTY           ((uint8)(0x01u << RPi_SPIS_STS_RX_BUF_NOT_EMPTY_SHIFT))
#define RPi_SPIS_STS_RX_BUF_EMPTY               ((uint8)(0x01u << RPi_SPIS_STS_RX_BUF_EMPTY_SHIFT))
#define RPi_SPIS_STS_RX_BUF_OVERRUN             ((uint8)(0x01u << RPi_SPIS_STS_RX_BUF_OVERRUN_SHIFT))

#define RPi_SPIS_DataWidth                  (RPi_SPIS_DATA_WIDTH)
#define RPi_SPIS_InternalClockUsed          (RPi_SPIS_INTERNAL_CLOCK)
#define RPi_SPIS_InternalTxInterruptEnabled (RPi_SPIS_INTERNAL_TX_INT_ENABLED)
#define RPi_SPIS_InternalRxInterruptEnabled (RPi_SPIS_INTERNAL_RX_INT_ENABLED)
#define RPi_SPIS_ModeUseZero                (RPi_SPIS_MODE_USE_ZERO)
#define RPi_SPIS_BidirectionalMode          (RPi_SPIS_BIDIRECTIONAL_MODE)
#define RPi_SPIS_Mode                       (RPi_SPIS_MODE)
#define RPi_SPIS_DATAWIDHT                  (RPi_SPIS_DATA_WIDTH)
#define RPi_SPIS_InternalInterruptEnabled   (0u)

#define RPi_SPIS_TXBUFFERSIZE   (RPi_SPIS_TX_BUFFER_SIZE)
#define RPi_SPIS_RXBUFFERSIZE   (RPi_SPIS_RX_BUFFER_SIZE)

#define RPi_SPIS_TXBUFFER       RPi_SPIS_txBuffer
#define RPi_SPIS_RXBUFFER       RPi_SPIS_rxBuffer

#endif  /* CY_SPIS_RPi_SPIS_H */

/* [] END OF FILE */
