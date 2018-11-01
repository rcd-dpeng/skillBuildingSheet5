/*******************************************************************************
* File Name: RPi_SPIS_INT.c
* Version 2.70
*
* Description:
*  This file provides all Interrupt Service Routine (ISR) for the SPI Slave
*  component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "RPi_SPIS_PVT.h"
#include "cyapicallbacks.h"

/* User code required at start of ISR */
/* `#START RPi_SPIS_ISR_START_DEF` */

/* `#END` */


/*******************************************************************************
* Function Name: RPi_SPIS_TX_ISR
*
* Summary:
*  Interrupt Service Routine for TX portion of the SPI Slave.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  RPi_SPIS_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer.
*  RPi_SPIS_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer, modified when exist data to
*  sending and FIFO Not Full.
*  RPi_SPIS_txBuffer[RPi_SPIS_TX_BUFFER_SIZE] - used to store
*  data to sending.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(RPi_SPIS_TX_ISR)
{

    #if(RPi_SPIS_TX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
    #endif /* (RPi_SPIS_TX_SOFTWARE_BUF_ENABLED) */

    #ifdef RPi_SPIS_TX_ISR_ENTRY_CALLBACK
        RPi_SPIS_TX_ISR_EntryCallback();
    #endif /* RPi_SPIS_TX_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START RPi_SPIS_ISR_TX_START` */

    /* `#END` */

    #if(RPi_SPIS_TX_SOFTWARE_BUF_ENABLED)
        /* Component interrupt service code */

        /* See if TX data buffer is not empty and there is space in TX FIFO */
        while(RPi_SPIS_txBufferRead != RPi_SPIS_txBufferWrite)
        {
            tmpStatus = RPi_SPIS_GET_STATUS_TX(RPi_SPIS_swStatusTx);
            RPi_SPIS_swStatusTx = tmpStatus;

            if ((RPi_SPIS_swStatusTx & RPi_SPIS_STS_TX_FIFO_NOT_FULL) != 0u)
            {
                if(RPi_SPIS_txBufferFull == 0u)
                {
                   RPi_SPIS_txBufferRead++;

                    if(RPi_SPIS_txBufferRead >= RPi_SPIS_TX_BUFFER_SIZE)
                    {
                        RPi_SPIS_txBufferRead = 0u;
                    }
                }
                else
                {
                    RPi_SPIS_txBufferFull = 0u;
                }

                /* Put data element into the TX FIFO */
                CY_SET_REG8(RPi_SPIS_TXDATA_PTR, 
                                             RPi_SPIS_txBuffer[RPi_SPIS_txBufferRead]);
            }
            else
            {
                break;
            }
        }

        /* If Buffer is empty then disable TX FIFO status interrupt until there is data in the buffer */
        if(RPi_SPIS_txBufferRead == RPi_SPIS_txBufferWrite)
        {
            RPi_SPIS_TX_STATUS_MASK_REG &= ((uint8)~RPi_SPIS_STS_TX_FIFO_NOT_FULL);
        }

    #endif /* RPi_SPIS_TX_SOFTWARE_BUF_ENABLED */

    /* User code required at end of ISR (Optional) */
    /* `#START RPi_SPIS_ISR_TX_END` */

    /* `#END` */
    
    #ifdef RPi_SPIS_TX_ISR_EXIT_CALLBACK
        RPi_SPIS_TX_ISR_ExitCallback();
    #endif /* RPi_SPIS_TX_ISR_EXIT_CALLBACK */
   }


/*******************************************************************************
* Function Name: RPi_SPIS_RX_ISR
*
* Summary:
*  Interrupt Service Routine for RX portion of the SPI Slave.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  RPi_SPIS_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer modified when FIFO contains
*  new data.
*  RPi_SPIS_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified when overflow occurred.
*  RPi_SPIS_rxBuffer[RPi_SPIS_RX_BUFFER_SIZE] - used to store
*  received data, modified when FIFO contains new data.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(RPi_SPIS_RX_ISR)
{
    #if(RPi_SPIS_RX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
        uint8 rxData;
    #endif /* (RPi_SPIS_TX_SOFTWARE_BUF_ENABLED) */

    #ifdef RPi_SPIS_RX_ISR_ENTRY_CALLBACK
        RPi_SPIS_RX_ISR_EntryCallback();
    #endif /* RPi_SPIS_RX_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START RPi_SPIS_RX_ISR_START` */

    /* `#END` */
    
    #if(RPi_SPIS_RX_SOFTWARE_BUF_ENABLED)
        tmpStatus = RPi_SPIS_GET_STATUS_RX(RPi_SPIS_swStatusRx);
        RPi_SPIS_swStatusRx = tmpStatus;
        /* See if RX data FIFO has some data and if it can be moved to the RX Buffer */
        while((RPi_SPIS_swStatusRx & RPi_SPIS_STS_RX_FIFO_NOT_EMPTY) != 0u)
        {
            rxData = CY_GET_REG8(RPi_SPIS_RXDATA_PTR);

            /* Set next pointer. */
            RPi_SPIS_rxBufferWrite++;
            if(RPi_SPIS_rxBufferWrite >= RPi_SPIS_RX_BUFFER_SIZE)
            {
                RPi_SPIS_rxBufferWrite = 0u;
            }

            if(RPi_SPIS_rxBufferWrite == RPi_SPIS_rxBufferRead)
            {
                RPi_SPIS_rxBufferRead++;
                if(RPi_SPIS_rxBufferRead >= RPi_SPIS_RX_BUFFER_SIZE)
                {
                    RPi_SPIS_rxBufferRead = 0u;
                }
                RPi_SPIS_rxBufferFull = 1u;
            }

            /* Move data from the FIFO to the Buffer */
            RPi_SPIS_rxBuffer[RPi_SPIS_rxBufferWrite] = rxData;

            tmpStatus = RPi_SPIS_GET_STATUS_RX(RPi_SPIS_swStatusRx);
            RPi_SPIS_swStatusRx = tmpStatus;
        }
    #endif /* RPi_SPIS_RX_SOFTWARE_BUF_ENABLED */

    /* User code required at end of ISR (Optional) */
    /* `#START RPi_SPIS_RX_ISR_END` */

    /* `#END` */

    #ifdef RPi_SPIS_RX_ISR_EXIT_CALLBACK
        RPi_SPIS_RX_ISR_ExitCallback();
    #endif /* RPi_SPIS_RX_ISR_EXIT_CALLBACK */
}

/* [] END OF FILE */
