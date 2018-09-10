/*******************************************************************************
* File Name: RPi_SPIS_BOOT.c
* Version 2.70
*
* Description:
*  This file provides the source code of bootloader communication APIs for the
*  SPI component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "RPi_SPIS.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (0u != ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_RPi_SPIS) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)))


/*******************************************************************************
* Function Name: RPi_SPIS_CyBtldrCommStart
********************************************************************************
*
* Summary:
*  Starts the SPIS communication component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This component automatically enables global interrupt.
*
*******************************************************************************/
void RPi_SPIS_CyBtldrCommStart(void) CYSMALL 
{
    /* Start SPIS component and clear the Tx,Rx buffers */
    RPi_SPIS_Start();
    RPi_SPIS_ClearRxBuffer();
    RPi_SPIS_ClearTxBuffer();
}


/*******************************************************************************
* Function Name: RPi_SPIS_CyBtldrCommStop
********************************************************************************
*
* Summary:
*  Disables the communication component and disables the interrupt.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RPi_SPIS_CyBtldrCommStop(void) CYSMALL 
{
    /* Stop SPIS component */
    RPi_SPIS_Stop();
}


/*******************************************************************************
* Function Name: RPi_SPIS_CyBtldrCommReset
********************************************************************************
*
* Summary:
*  Resets the receive and transmit communication Buffers.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RPi_SPIS_CyBtldrCommReset(void) CYSMALL 
{
    /* Clear RX and TX buffers */
    RPi_SPIS_ClearRxBuffer();
    RPi_SPIS_ClearTxBuffer();
}


/*******************************************************************************
* Function Name: RPi_SPIS_CyBtldrCommWrite
********************************************************************************
*
* Summary:
*  Allows the caller to write data to the boot loader host. This function uses
* a blocking write function for writing data using SPIS communication component.
*
* Parameters:
*  pData:    A pointer to the block of data to send to the device
*  size:     The number of bytes to write.
*  count:    Pointer to an unsigned short variable to write the number of
*             bytes actually written.
*  timeOut:  Number of units to wait before returning because of a timeout.
*
* Return:
*   cystatus: This function will return CYRET_SUCCESS if data is sent
*             succesfully.
*
* Side Effects:
*  This function should be called after command was received .
*
*******************************************************************************/
cystatus RPi_SPIS_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
         
{
    cystatus status = CYRET_EMPTY;
    uint16 buf_index = 0u;
    uint16 timeoutMs;

    timeoutMs = 10u * (uint16) timeOut;

    /* Clear receive TX buffers status from previous transaction */
    (void) RPi_SPIS_ReadTxStatus();

    /* Write TX data using blocking function */
    #if(0u != RPi_SPIS_MODE_USE_ZERO)
        RPi_SPIS_WriteTxDataZero(pData[buf_index]);
        buf_index++;
    #endif /* (RPi_SPIS_MODE_USE_ZERO == 1u) */

    /* Write TX data using blocking function */
    do
    {
        RPi_SPIS_WriteTxData(pData[buf_index]);
        buf_index++;
    }while(buf_index < size);

    while(0u != timeoutMs)
    {
        if(0u != (RPi_SPIS_ReadTxStatus() & RPi_SPIS_STS_SPI_DONE))
        {
            /* Return success code */
            *count = size;
            status = CYRET_SUCCESS;
            break;
         }
        CyDelay(1u);
        timeoutMs--;
    }

    RPi_SPIS_ClearRxBuffer();

    return (status);
}


/*******************************************************************************
* Function Name: RPi_SPIS_CyBtldrCommRead
********************************************************************************
*
* Summary:
*  Receives the command.
*
* Parameters:
*  pData:    A pointer to the area to store the block of data received
*             from the device.
*  size:     Maximum size of the read buffer
*  count:    Pointer to an unsigned short variable to write the number
*             of bytes actually read.
*  timeOut:  Number of units to wait before returning because of a timeOut.
*            Timeout is measured in 10s of ms.
*
* Return:
*  cystatus: This function will return CYRET_SUCCESS if atleast one byte is
*            received succesfully within the timeout interval .If no data
*            is received  this function will return CYRET_EMPTY.
*
*  BYTE2BYTE_TIME_OUT is used for detecting timeout marking end of block
*  data from host. This has to be set to a value which is greater than
*  the expected maximum delay between two bytes during a block/packet
*  transmission from the host.
*******************************************************************************/
cystatus RPi_SPIS_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
         
{
    uint16 iCntr;
    uint16 dataIndexCntr;
    uint16 tempCount;
    uint16 oldDataCount;

    cystatus status = CYRET_EMPTY;

    /* Check whether data is received within the timeout period.
    *  Timeout period is in units of 10ms.
    *  If atleast one byte is received within the timeout interval, wait for more data */
    for (iCntr = 0u; iCntr < (10u * (uint16) timeOut); iCntr++)
    {
        /* If atleast one byte is received within the timeout interval
         * enter the next loop
         * waiting for more data reception
        */
        if(0u != RPi_SPIS_GetRxBufferSize())
        {
            /* Wait for more data until 1ms byte to byte time out interval.
            * If no data is received during the last 1 ms(BYTE2BYTE_TIME_OUT)
            * then it is considered as end of transmitted data block(packet)
            * from the host and the program execution will break from the
            * data awaiting loop with status=CYRET_SUCCESS
            */
            do
            {
                oldDataCount = RPi_SPIS_GetRxBufferSize();
                CyDelay(RPi_SPIS_BYTE2BYTE_TIME_OUT);
            }while(RPi_SPIS_GetRxBufferSize() > oldDataCount);
            status = CYRET_SUCCESS;
            break;
        }
        /* If not data is received , give a delay of 1ms and check again until the Timeout specified in .cydwr. */
        else
        {
            CyDelay(1u);
        }
    }

    /* Initialize the data read indexes and Count value*/
    *count = 0u;
    dataIndexCntr = 0u;

    /* If GetRxBufferSize()>0 , move the received data to the pData buffer */
    while(RPi_SPIS_GetRxBufferSize() > 0u)
    {
        tempCount = RPi_SPIS_GetRxBufferSize();
        *count  =(*count) + tempCount;

        /* Check if buffer overflow will occur before moving the data */
        if(*count < size)
        {
            for (iCntr = 0u; iCntr < tempCount; iCntr++)
            {
                /* Read the data and move it to the pData buffer */
                pData[dataIndexCntr] = RPi_SPIS_ReadRxData();
                dataIndexCntr++;
            }

            /* Check if the last data received is End of packet(0x17)
            *  If not wait for additional 5ms
            */
            if(pData[dataIndexCntr - 1u] != 0x17u)
            {
                CyDelay(1u);
            }
        }
        /* If there is no space to move data, break from the loop */
        else
        {
            *count = (*count) - tempCount;
            break;
        }
    }

    return (status);
}

#endif /* if defined(CYDEV_BOOTLOADER_IO_COMP) && (0u != ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_RPi_SPIS) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)) */


/* [] END OF FILE */
