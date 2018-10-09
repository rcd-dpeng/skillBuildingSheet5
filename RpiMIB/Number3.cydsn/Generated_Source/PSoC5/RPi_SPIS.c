/*******************************************************************************
* File Name: RPi_SPIS.c
* Version 2.70
*
* Description:
*  This file provides all API functionality of the SPI Slave component.
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

#if (RPi_SPIS_TX_SOFTWARE_BUF_ENABLED)

    volatile uint8 RPi_SPIS_txBuffer[RPi_SPIS_TX_BUFFER_SIZE];
    volatile uint8 RPi_SPIS_txBufferRead;
    volatile uint8 RPi_SPIS_txBufferWrite;
    volatile uint8 RPi_SPIS_txBufferFull;

#endif /* RPi_SPIS_TX_SOFTWARE_BUF_ENABLED*/

#if (RPi_SPIS_RX_SOFTWARE_BUF_ENABLED)

    volatile uint8 RPi_SPIS_rxBuffer[RPi_SPIS_RX_BUFFER_SIZE];
    volatile uint8 RPi_SPIS_rxBufferRead;
    volatile uint8 RPi_SPIS_rxBufferWrite;
    volatile uint8 RPi_SPIS_rxBufferFull;

#endif /* RPi_SPIS_RX_SOFTWARE_BUF_ENABLED */

uint8 RPi_SPIS_initVar = 0u;

volatile uint8 RPi_SPIS_swStatusTx;
volatile uint8 RPi_SPIS_swStatusRx;


/*******************************************************************************
* Function Name: RPi_SPIS_Init
********************************************************************************
*
* Summary:
*  Inits/Restores default SPIS configuration provided with customizer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  When this function is called it initializes all of the necessary parameters
*  for execution. i.e. setting the initial interrupt mask, configuring the
*  interrupt service routine, configuring the bit-counter parameters and
*  clearing the FIFO and Status Register.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void RPi_SPIS_Init(void) 
{
    /*Initialize the Bit counter */
    RPi_SPIS_COUNTER_PERIOD_REG = RPi_SPIS_BITCTR_INIT;

    /* ISR initialization */
    #if(RPi_SPIS_INTERNAL_TX_INT_ENABLED)

        CyIntDisable(RPi_SPIS_TX_ISR_NUMBER);

        /* Set the ISR to point to the RPi_SPIS_isr Interrupt. */
        (void)CyIntSetVector(RPi_SPIS_TX_ISR_NUMBER, &RPi_SPIS_TX_ISR);

        /* Set the priority. */
        CyIntSetPriority(RPi_SPIS_TX_ISR_NUMBER, RPi_SPIS_TX_ISR_PRIORITY);

    #endif /* RPi_SPIS_INTERNAL_TX_INT_ENABLED */

    #if(RPi_SPIS_INTERNAL_RX_INT_ENABLED)

        CyIntDisable(RPi_SPIS_RX_ISR_NUMBER);

        /* Set the ISR to point to the RPi_SPIS_isr Interrupt. */
        (void)CyIntSetVector(RPi_SPIS_RX_ISR_NUMBER, &RPi_SPIS_RX_ISR);

        /* Set the priority. */
        CyIntSetPriority(RPi_SPIS_RX_ISR_NUMBER, RPi_SPIS_RX_ISR_PRIORITY);

    #endif /* RPi_SPIS_INTERNAL_RX_INT_ENABLED */

    /* Clear any stray data from the RX and TX FIFO */
    RPi_SPIS_ClearFIFO();

    #if(RPi_SPIS_RX_SOFTWARE_BUF_ENABLED)
        RPi_SPIS_rxBufferFull = 0u;
        RPi_SPIS_rxBufferRead = 0u;
        RPi_SPIS_rxBufferWrite = 0u;
    #endif /* RPi_SPIS_RX_SOFTWARE_BUF_ENABLED */

    #if(RPi_SPIS_TX_SOFTWARE_BUF_ENABLED)
        RPi_SPIS_txBufferFull = 0u;
        RPi_SPIS_txBufferRead = 0u;
        RPi_SPIS_txBufferWrite = 0u;
    #endif /* RPi_SPIS_TX_SOFTWARE_BUF_ENABLED */

    (void) RPi_SPIS_ReadTxStatus(); /* Clear any pending status bits */
    (void) RPi_SPIS_ReadRxStatus(); /* Clear any pending status bits */


    /* Configure the Initial interrupt mask */
    #if (RPi_SPIS_TX_SOFTWARE_BUF_ENABLED)
        RPi_SPIS_TX_STATUS_MASK_REG  = (RPi_SPIS_TX_INIT_INTERRUPTS_MASK &
                                                (uint8)~RPi_SPIS_STS_TX_FIFO_NOT_FULL);
    #else /* RPi_SPIS_TX_SOFTWARE_BUF_ENABLED */
        RPi_SPIS_TX_STATUS_MASK_REG  = RPi_SPIS_TX_INIT_INTERRUPTS_MASK;
    #endif /* RPi_SPIS_TX_SOFTWARE_BUF_ENABLED */

    RPi_SPIS_RX_STATUS_MASK_REG  = RPi_SPIS_RX_INIT_INTERRUPTS_MASK;
}


/*******************************************************************************
* Function Name: RPi_SPIS_Enable
********************************************************************************
*
* Summary:
*  Enable SPIS component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void RPi_SPIS_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    RPi_SPIS_COUNTER_CONTROL_REG |= RPi_SPIS_CNTR_ENABLE;
    RPi_SPIS_TX_STATUS_ACTL_REG |= RPi_SPIS_INT_ENABLE;
    RPi_SPIS_RX_STATUS_ACTL_REG |= RPi_SPIS_INT_ENABLE;

    CyExitCriticalSection(enableInterrupts);

    #if(RPi_SPIS_INTERNAL_TX_INT_ENABLED)
        CyIntEnable(RPi_SPIS_TX_ISR_NUMBER);
    #endif /* RPi_SPIS_INTERNAL_TX_INT_ENABLED */

    #if(RPi_SPIS_INTERNAL_RX_INT_ENABLED)
        CyIntEnable(RPi_SPIS_RX_ISR_NUMBER);
    #endif /* RPi_SPIS_INTERNAL_RX_INT_ENABLED */
}


/*******************************************************************************
* Function Name: RPi_SPIS_Start
********************************************************************************
*
* Summary:
*  Initialize and Enable the SPI Slave component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  RPi_SPIS_initVar - used to check initial configuration, modified on
*  first function call.
*
* Theory:
*  Enable the clock input to enable operation.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void RPi_SPIS_Start(void) 
{
    if(RPi_SPIS_initVar == 0u)
    {
        RPi_SPIS_Init();
        RPi_SPIS_initVar = 1u;
    }

    RPi_SPIS_Enable();
}


/*******************************************************************************
* Function Name: RPi_SPIS_Stop
********************************************************************************
*
* Summary:
*  Disable the SPI Slave component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the internal interrupt if one is used.
*
*******************************************************************************/
void RPi_SPIS_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    RPi_SPIS_TX_STATUS_ACTL_REG &= (uint8)~RPi_SPIS_INT_ENABLE;
    RPi_SPIS_RX_STATUS_ACTL_REG &= (uint8)~RPi_SPIS_INT_ENABLE;

    CyExitCriticalSection(enableInterrupts);

    #if(RPi_SPIS_INTERNAL_TX_INT_ENABLED)
        CyIntDisable(RPi_SPIS_TX_ISR_NUMBER);
    #endif /* RPi_SPIS_INTERNAL_TX_INT_ENABLED */

    #if(RPi_SPIS_INTERNAL_RX_INT_ENABLED)
        CyIntDisable(RPi_SPIS_RX_ISR_NUMBER);
    #endif /* RPi_SPIS_INTERNAL_RX_INT_ENABLED */
}


/*******************************************************************************
* Function Name: RPi_SPIS_EnableTxInt
********************************************************************************
*
* Summary:
*  Enable internal Tx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Enable the internal Tx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void RPi_SPIS_EnableTxInt(void) 
{
    #if(RPi_SPIS_INTERNAL_TX_INT_ENABLED)
        CyIntEnable(RPi_SPIS_TX_ISR_NUMBER);
    #endif /* RPi_SPIS_INTERNAL_TX_INT_ENABLED */
}


/*******************************************************************************
* Function Name: RPi_SPIS_EnableRxInt
********************************************************************************
*
* Summary:
*  Enable internal Rx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Enable the internal Rx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void RPi_SPIS_EnableRxInt(void) 
{
    #if(RPi_SPIS_INTERNAL_RX_INT_ENABLED)
        CyIntEnable(RPi_SPIS_RX_ISR_NUMBER);
    #endif /* RPi_SPIS_INTERNAL_RX_INT_ENABLED */
}


/*******************************************************************************
* Function Name: RPi_SPIS_DisableTxInt
********************************************************************************
*
* Summary:
*  Disable internal Tx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the internal Tx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void RPi_SPIS_DisableTxInt(void) 
{
    #if(RPi_SPIS_INTERNAL_TX_INT_ENABLED)
        CyIntDisable(RPi_SPIS_TX_ISR_NUMBER);
    #endif /* RPi_SPIS_INTERNAL_TX_INT_ENABLED */
}


/*******************************************************************************
* Function Name: RPi_SPIS_DisableRxInt
********************************************************************************
*
* Summary:
*  Disable internal Rx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the internal Rx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void RPi_SPIS_DisableRxInt(void) 
{
    #if(RPi_SPIS_INTERNAL_RX_INT_ENABLED)
        CyIntDisable(RPi_SPIS_RX_ISR_NUMBER);
    #endif /* RPi_SPIS_INTERNAL_RX_INT_ENABLED */
}


/*******************************************************************************
* Function Name: RPi_SPIS_SetTxInterruptMode
********************************************************************************
*
* Summary:
*  Configure which status bits trigger an interrupt event.
*
* Parameters:
*  intSrc: An or'd combination of the desired status bit masks (defined in the
*  header file).
*
* Return:
*  None.
*
* Theory:
*  Enables the output of specific status bits to the interrupt controller.
*
*******************************************************************************/
void RPi_SPIS_SetTxInterruptMode(uint8 intSrc) 
{
    RPi_SPIS_TX_STATUS_MASK_REG  = intSrc;
}


/*******************************************************************************
* Function Name: RPi_SPIS_SetRxInterruptMode
********************************************************************************
*
* Summary:
*  Configure which status bits trigger an interrupt event.
*
* Parameters:
*  intSrc: An or'd combination of the desired status bit masks (defined in the
*  header file).
*
* Return:
*  None.
*
* Theory:
*  Enables the output of specific status bits to the interrupt controller.
*
*******************************************************************************/
void RPi_SPIS_SetRxInterruptMode(uint8 intSrc) 
{
    RPi_SPIS_RX_STATUS_MASK_REG  = intSrc;
}


/*******************************************************************************
* Function Name: RPi_SPIS_ReadTxStatus
********************************************************************************
*
* Summary:
*  Read the Tx status register for the component.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the Tx status register.
*
* Global variables:
*  RPi_SPIS_swStatusTx - used to store in software status register,
*  modified every function call - resets to zero.
*
* Theory:
*  Allows the user and the API to read the Tx status register for error
*  detection and flow control.
*
* Side Effects:
*  Clear Tx status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 RPi_SPIS_ReadTxStatus(void) 
{
    uint8 tmpStatus;

    #if (RPi_SPIS_TX_SOFTWARE_BUF_ENABLED)

        RPi_SPIS_DisableTxInt();

        tmpStatus = RPi_SPIS_GET_STATUS_TX(RPi_SPIS_swStatusTx);

        RPi_SPIS_swStatusTx = 0u;

        /* Enable Interrupts */
        RPi_SPIS_EnableTxInt();

    #else /* !RPi_SPIS_TX_SOFTWARE_BUF_ENABLED */

        tmpStatus = RPi_SPIS_TX_STATUS_REG;

    #endif /* RPi_SPIS_TX_SOFTWARE_BUF_ENABLED */

    return(tmpStatus);
}


/*******************************************************************************
* Function Name: RPi_SPIS_ReadRxStatus
********************************************************************************
*
* Summary:
*  Read the Rx status register for the component.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the Rx status register.
*
* Global variables:
*  RPi_SPIS_swStatusRx - used to store in software Rx status register,
*  modified every function call - resets to zero.
*
* Theory:
*  Allows the user and the API to read the Rx status register for error
*  detection and flow control.
*
* Side Effects:
*  Clear Rx status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 RPi_SPIS_ReadRxStatus(void) 
{
    uint8 tmpStatus;

    #if (RPi_SPIS_RX_SOFTWARE_BUF_ENABLED)

        RPi_SPIS_DisableRxInt();

        tmpStatus = RPi_SPIS_GET_STATUS_RX(RPi_SPIS_swStatusRx);

        RPi_SPIS_swStatusRx = 0u;

        /* Enable Interrupts */
        RPi_SPIS_EnableRxInt();

    #else /* !RPi_SPIS_RX_SOFTWARE_BUF_ENABLED */

        tmpStatus = RPi_SPIS_RX_STATUS_REG;

    #endif /* RPi_SPIS_RX_SOFTWARE_BUF_ENABLED */

    return(tmpStatus);
}


/*******************************************************************************
* Function Name: RPi_SPIS_WriteTxData
********************************************************************************
*
* Summary:
*  Write a byte of data to be sent across the SPI.
*
* Parameters:
*  txDataByte: The data value to send across the SPI.
*
* Return:
*  None.
*
* Global variables:
*  RPi_SPIS_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer, modified every function
*  call if TX Software Buffer is used.
*  RPi_SPIS_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer.
*  RPi_SPIS_txBuffer[RPi_SPIS_TX_BUFFER_SIZE] - used to store
*  data to sending, modified every function call if TX Software Buffer is used.
*
* Theory:
*  Allows the user to transmit any byte of data in a single transfer.
*
* Side Effects:
*  If this function is called again before the previous byte is finished then
*  the next byte will be appended to the transfer with no time between
*  the byte transfers. Clear Tx status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void RPi_SPIS_WriteTxData(uint8 txData) 
{
    #if(RPi_SPIS_TX_SOFTWARE_BUF_ENABLED)

        uint8 tempStatus;
        uint8 tmpTxBufferRead;

        /* Block if buffer is full, so we don't overwrite. */
        do
        {
            tmpTxBufferRead = RPi_SPIS_txBufferRead;
            if (0u == tmpTxBufferRead)
            {
                tmpTxBufferRead = RPi_SPIS_TX_BUFFER_SIZE - 1u;
            }
            else
            {
                tmpTxBufferRead--;
            }

        }
        while(tmpTxBufferRead == RPi_SPIS_txBufferWrite);

        /* Disable Interrupt to protect variables that could change on interrupt. */
        RPi_SPIS_DisableTxInt();

        tempStatus = RPi_SPIS_GET_STATUS_TX(RPi_SPIS_swStatusTx);
        RPi_SPIS_swStatusTx = tempStatus;

        if((RPi_SPIS_txBufferRead == RPi_SPIS_txBufferWrite) &&
            (0u != (RPi_SPIS_swStatusTx & RPi_SPIS_STS_TX_FIFO_NOT_FULL)))
        {
            /* Put data element into the TX FIFO */
            CY_SET_REG8(RPi_SPIS_TXDATA_PTR, txData);
        }
        else
        {
            /* Put data element into the software buffer */
            RPi_SPIS_txBufferWrite++;
            if(RPi_SPIS_txBufferWrite >= RPi_SPIS_TX_BUFFER_SIZE)
            {
                RPi_SPIS_txBufferWrite = 0u;
            }

            if(RPi_SPIS_txBufferWrite == RPi_SPIS_txBufferRead)
            {
                RPi_SPIS_txBufferRead++;
                if(RPi_SPIS_txBufferRead >= RPi_SPIS_RX_BUFFER_SIZE)
                {
                    RPi_SPIS_txBufferRead = 0u;
                }
                RPi_SPIS_txBufferFull = 1u;
            }

            RPi_SPIS_txBuffer[RPi_SPIS_txBufferWrite] = txData;

            RPi_SPIS_TX_STATUS_MASK_REG |= RPi_SPIS_STS_TX_FIFO_NOT_FULL;
        }

        /* Enable Interrupt. */
        RPi_SPIS_EnableTxInt();

    #else /* !RPi_SPIS_TX_SOFTWARE_BUF_ENABLED */
        /* Wait until TX FIFO has a place */
        while(0u == (RPi_SPIS_TX_STATUS_REG & RPi_SPIS_STS_TX_FIFO_NOT_FULL))
        {
        }

        /* Put data element into the TX FIFO */
        CY_SET_REG8(RPi_SPIS_TXDATA_PTR, txData);
        
    #endif /* RPi_SPIS_TX_SOFTWARE_BUF_ENABLED */
}

#if(RPi_SPIS_MODE_USE_ZERO != 0u)

    /*******************************************************************************
    * Function Name: RPi_SPIS_WriteTxDataZero
    ********************************************************************************
    *
    * Summary:
    *  Write a byte zero of data to be sent across the SPI. This must be used in
    *  Mode 00 and 01 if the FIFO is empty and data is not being sent.
    *
    * Parameters:
    *  txDataByte: The data value to send across the SPI.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer. Clear
    *  status register of the component.
    *
    *******************************************************************************/
    void RPi_SPIS_WriteTxDataZero(uint8 txDataByte)
                                        
    {
        CY_SET_REG8(RPi_SPIS_TXDATA_ZERO_PTR, txDataByte);
    }

#endif /* (RPi_SPIS_MODE_USE_ZERO != 0u) */


/*******************************************************************************
* Function Name: RPi_SPIS_ReadRxData
********************************************************************************
*
* Summary:
*  Read the next byte of data received across the SPI.
*
* Parameters:
*  None.
*
* Return:
*  The next byte of data read from the FIFO.
*
* Global variables:
*  RPi_SPIS_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer.
*  RPi_SPIS_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified every function
*  call if RX Software Buffer is used.
*  RPi_SPIS_rxBuffer[RPi_SPIS_RX_BUFFER_SIZE] - used to store
*  received data.
*
* Theory:
*  Allows the user to read a byte of data received.
*
* Side Effects:
*  Will return invalid data if the FIFO is empty.  User should poll for FIFO
*  empty status before calling Read function.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 RPi_SPIS_ReadRxData(void) 
{
    uint8 rxData;

    #if(RPi_SPIS_RX_SOFTWARE_BUF_ENABLED)

        /* Disable Interrupt to protect variables that could change on interrupt. */
        RPi_SPIS_DisableRxInt();

        if(RPi_SPIS_rxBufferRead != RPi_SPIS_rxBufferWrite)
        {
            if(RPi_SPIS_rxBufferFull == 0u)
            {
                RPi_SPIS_rxBufferRead++;
                if(RPi_SPIS_rxBufferRead >= RPi_SPIS_RX_BUFFER_SIZE)
                {
                    RPi_SPIS_rxBufferRead = 0u;
                }
            }
            else
            {
                RPi_SPIS_rxBufferFull = 0u;
            }
        }

        rxData = RPi_SPIS_rxBuffer[RPi_SPIS_rxBufferRead];

        /* Enable Interrupt. */
        RPi_SPIS_EnableRxInt();

    #else /* !RPi_SPIS_RX_SOFTWARE_BUF_ENABLED */

        rxData = CY_GET_REG8(RPi_SPIS_RXDATA_PTR);

    #endif /* RPi_SPIS_RX_SOFTWARE_BUF_ENABLED */

    return (rxData);

}


/*******************************************************************************
* Function Name: RPi_SPIS_GetRxBufferSize
********************************************************************************
*
* Summary:
*  Returns the number of bytes/words of data currently held in the RX buffer.
*  If RX Software Buffer not used then function return 0 if FIFO empty or 1 if
*  FIFO not empty. In another case function return size of RX Software Buffer.
*
* Parameters:
*  None.
*
* Return:
*  Integer count of the number of bytes/words in the RX buffer.
*
* Global variables:
*  RPi_SPIS_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer.
*  RPi_SPIS_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer.
*
* Theory:
*  Allows the user to find out how full the RX Buffer is.
*
*******************************************************************************/
uint8 RPi_SPIS_GetRxBufferSize(void) 
{
    uint8 size;

    #if(RPi_SPIS_RX_SOFTWARE_BUF_ENABLED)

        /* Disable Interrupt to protect variables that could change on interrupt. */
        RPi_SPIS_DisableRxInt();

        if(RPi_SPIS_rxBufferRead == RPi_SPIS_rxBufferWrite)
        {
            size = 0u; /* No data in RX buffer */
        }
        else if(RPi_SPIS_rxBufferRead < RPi_SPIS_rxBufferWrite)
        {
            size = (RPi_SPIS_rxBufferWrite - RPi_SPIS_rxBufferRead);
        }
        else
        {
            size = (RPi_SPIS_RX_BUFFER_SIZE - RPi_SPIS_rxBufferRead) + RPi_SPIS_rxBufferWrite;
        }

        /* Enable interrupt. */
        RPi_SPIS_EnableRxInt();

    #else /* !RPi_SPIS_RX_SOFTWARE_BUF_ENABLED*/

        /* We can only know if there is data in the fifo. */
        size = ((RPi_SPIS_RX_STATUS_REG & RPi_SPIS_STS_RX_FIFO_NOT_EMPTY) != 0u) ? 1u : 0u;

    #endif /* RPi_SPIS_RX_SOFTWARE_BUF_ENABLED */

    return (size);
}


/*******************************************************************************
* Function Name: RPi_SPIS_GetTxBufferSize
********************************************************************************
*
* Summary:
*  Returns the number of bytes/words of data currently held in the TX buffer.
*  If TX Software Buffer not used then function return 0 - if FIFO empty, 1 - if
*  FIFO not full, 4 - if FIFO full. In another case function return size of TX
*  Software Buffer.
*
* Parameters:
*  None.
*
* Return:
*  Integer count of the number of bytes/words in the TX buffer.
*
* Global variables:
*  RPi_SPIS_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer.
*  RPi_SPIS_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer.
*
* Theory:
*  Allows the user to find out how full the TX Buffer is.
*
* Side Effects:
*  Clear status register of the component.
*
*******************************************************************************/
uint8  RPi_SPIS_GetTxBufferSize(void) 
{
    uint8 size;

    #if(RPi_SPIS_TX_SOFTWARE_BUF_ENABLED)

        /* Disable Interrupt to protect variables that could change on interrupt. */
        RPi_SPIS_DisableTxInt();

        if(RPi_SPIS_txBufferRead == RPi_SPIS_txBufferWrite)
        {
            size = 0u;
        }
        else if(RPi_SPIS_txBufferRead < RPi_SPIS_txBufferWrite)
        {
            size = (RPi_SPIS_txBufferWrite - RPi_SPIS_txBufferRead);
        }
        else
        {
            size = (RPi_SPIS_TX_BUFFER_SIZE - RPi_SPIS_txBufferRead) + RPi_SPIS_txBufferWrite;
        }

        /* Enable Interrupt. */
        RPi_SPIS_EnableTxInt();

    #else /* !RPi_SPIS_TX_SOFTWARE_BUF_ENABLED */

        size = RPi_SPIS_TX_STATUS_REG;

        /* Is the fifo is full. */
        if((size & RPi_SPIS_STS_TX_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else if((size & RPi_SPIS_STS_TX_FIFO_NOT_FULL) != 0u)
        {
            size = 1u;
        }
        else
        {
            size = 4u;
        }

    #endif /* RPi_SPIS_TX_SOFTWARE_BUF_ENABLED */

    return (size);
}


/*******************************************************************************
* Function Name: RPi_SPIS_ClearRxBuffer
********************************************************************************
*
* Summary:
*  Clear the RX RAM buffer by setting the read and write pointers both to zero.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  RPi_SPIS_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer, modified every function
*  call - resets to zero.
*  RPi_SPIS_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified every function call -
*  resets to zero.
*
* Theory:
*  Setting the pointers to zero makes the system believe there is no data to
*  read and writing will resume at address 0 overwriting any data that may have
*  remained in the RAM.
*
* Side Effects:
*  Any received data not read from the RAM buffer will be lost when overwritten.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void RPi_SPIS_ClearRxBuffer(void) 
{
    /* Clear Hardware RX FIFO */
    while((RPi_SPIS_RX_STATUS_REG & RPi_SPIS_STS_RX_FIFO_NOT_EMPTY) != 0u)
    {
        CY_GET_REG8(RPi_SPIS_RXDATA_PTR);
    }

    #if(RPi_SPIS_RX_SOFTWARE_BUF_ENABLED)

        /* Disable interrupt to protect variables that could change on interrupt. */
        RPi_SPIS_DisableRxInt();

        RPi_SPIS_rxBufferRead  = 0u;
        RPi_SPIS_rxBufferWrite = 0u;
		RPi_SPIS_rxBufferFull  = 0u;
        /* Enable interrupt. */
        RPi_SPIS_EnableRxInt();

    #endif /* RPi_SPIS_RX_SOFTWARE_BUF_ENABLED */
}


/*******************************************************************************
* Function Name: RPi_SPIS_ClearTxBuffer
********************************************************************************
*
* Summary:
*  Clear the TX RAM buffer by setting the read and write pointers both to zero.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  RPi_SPIS_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer, modified every function
*  call - resets to zero.
*  RPi_SPIS_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer, modified every function call -
*  resets to zero.
*
* Theory:
*  Setting the pointers to zero makes the system believe there is no data to
*  read and writing will resume at address 0 overwriting any data that may have
*  remained in the RAM.
*
* Side Effects:
*  Any data not yet transmitted from the RAM buffer will be lost when
*  overwritten.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void RPi_SPIS_ClearTxBuffer(void) 
{
    uint8 enableInterrupts;

    /* Clear Hardware TX FIFO */
    enableInterrupts = CyEnterCriticalSection();

    #if(RPi_SPIS_DATA_WIDTH <= 8u)

        /* Clear TX FIFO */
        RPi_SPIS_TX_AUX_CONTROL_DP0_REG |= (uint8)RPi_SPIS_FIFO_CLR;
        RPi_SPIS_TX_AUX_CONTROL_DP0_REG &= (uint8)~RPi_SPIS_FIFO_CLR;

    #else

        /* Clear TX FIFO */
        RPi_SPIS_TX_AUX_CONTROL_DP0_REG |= (uint8)RPi_SPIS_FIFO_CLR;
        RPi_SPIS_TX_AUX_CONTROL_DP0_REG &= (uint8)~RPi_SPIS_FIFO_CLR;
        RPi_SPIS_TX_AUX_CONTROL_DP1_REG |= (uint8)RPi_SPIS_FIFO_CLR;
        RPi_SPIS_TX_AUX_CONTROL_DP1_REG &= (uint8)~RPi_SPIS_FIFO_CLR;

    #endif /* RPi_SPIS_DATA_WIDTH > 8u */

    CyExitCriticalSection(enableInterrupts);

    #if(RPi_SPIS_TX_SOFTWARE_BUF_ENABLED)

        /* Disable Interrupt to protect variables that could change on interrupt. */
        RPi_SPIS_DisableTxInt();

        RPi_SPIS_txBufferRead  = 0u;
        RPi_SPIS_txBufferWrite = 0u;
		RPi_SPIS_txBufferFull  = 0u;
		
        /* If Buffer is empty then disable TX FIFO status interrupt */
        RPi_SPIS_TX_STATUS_MASK_REG &= (uint8)~RPi_SPIS_STS_TX_FIFO_NOT_FULL;

        /* Enable Interrupt. */
        RPi_SPIS_EnableTxInt();

    #endif /* RPi_SPIS_TX_SOFTWARE_BUF_ENABLED */
}


#if (RPi_SPIS_BIDIRECTIONAL_MODE != 0u)

    /*******************************************************************************
    * Function Name: RPi_SPIS_TxEnable
    ********************************************************************************
    *
    * Summary:
    *  If the SPI Slave is configured to use a single bi-directional pin then this
    *  will set the bi-directional pin to transmit.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void RPi_SPIS_TxEnable(void) 
    {
            RPi_SPIS_CONTROL_REG |= RPi_SPIS_CTRL_TX_SIGNAL_EN;
    }


    /*******************************************************************************
    * Function Name: RPi_SPIS_TxDisable
    ********************************************************************************
    *
    * Summary:
    *  If the SPI Slave is configured to use a single bi-directional pin then this
    *  will set the bi-directional pin to receive.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void RPi_SPIS_TxDisable(void) 
    {
            RPi_SPIS_CONTROL_REG &= (uint8)~RPi_SPIS_CTRL_TX_SIGNAL_EN;
    }

#endif /* RPi_SPIS_BIDIRECTIONAL_MODE != 0u */


/*******************************************************************************
* Function Name: RPi_SPIS_PutArray
********************************************************************************
*
* Summary:
*  Write available data from RAM/ROM to the TX buffer while space is available
*  in the TX buffer. Keep trying until all data is passed to the TX buffer. If
*  used Mode 00 or 01 before PutArray() function should be called
*  WriteTxDataZero() function.
*
* Parameters:
*  *buffer: Pointer to the location in RAM containing the data to send
*  byteCount: The number of bytes to move to the transmit buffer.
*
* Return:
*  None.
*
* Side Effects:
*  Will stay in this routine until all data has been sent.  May get locked in
*  this loop if data is not being initiated by the master if there is not
*  enough room in the TX FIFO.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void RPi_SPIS_PutArray(const uint8 buffer[], uint8 byteCount)
                                                                    
{
    uint8 bufIndex;
    bufIndex = 0u;

    while(byteCount > 0u)
    {
        RPi_SPIS_WriteTxData(buffer[bufIndex]);
        bufIndex++;
        byteCount--;
    }
}


/*******************************************************************************
* Function Name: RPi_SPIS_ClearFIFO
********************************************************************************
*
* Summary:
*  Clear the RX and TX FIFO's of all data for a fresh start.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  Clear status register of the component.
*
*******************************************************************************/
void RPi_SPIS_ClearFIFO(void) 
{
    uint8 enableInterrupts;

    while((RPi_SPIS_RX_STATUS_REG & RPi_SPIS_STS_RX_FIFO_NOT_EMPTY) != 0u)
    {
        CY_GET_REG8(RPi_SPIS_RXDATA_PTR);
    }

    enableInterrupts = CyEnterCriticalSection();

    #if(RPi_SPIS_DATA_WIDTH <= 8u)

        /* Clear TX FIFO */
        RPi_SPIS_TX_AUX_CONTROL_DP0_REG |= (uint8)RPi_SPIS_FIFO_CLR;
        RPi_SPIS_TX_AUX_CONTROL_DP0_REG &= (uint8)~RPi_SPIS_FIFO_CLR;

    #else

        /* Clear TX FIFO */
        RPi_SPIS_TX_AUX_CONTROL_DP0_REG |= (uint8)RPi_SPIS_FIFO_CLR;
        RPi_SPIS_TX_AUX_CONTROL_DP0_REG &= (uint8)~RPi_SPIS_FIFO_CLR;
        RPi_SPIS_TX_AUX_CONTROL_DP1_REG |= (uint8)RPi_SPIS_FIFO_CLR;
        RPi_SPIS_TX_AUX_CONTROL_DP1_REG &= (uint8)~RPi_SPIS_FIFO_CLR;

    #endif /* RPi_SPIS_DATA_WIDTH <= 8u */

    CyExitCriticalSection(enableInterrupts);
}


/* Following functions are for version Compatibility, they are obsolete.
*  Please do not use it in new projects.
*/


/*******************************************************************************
* Function Name: RPi_SPIS_EnableInt
********************************************************************************
*
* Summary:
*  Enable internal interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Enable the internal interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void RPi_SPIS_EnableInt(void) 
{
    #if(RPi_SPIS_INTERNAL_TX_INT_ENABLED)
        CyIntEnable(RPi_SPIS_TX_ISR_NUMBER);
    #endif /* RPi_SPIS_INTERNAL_TX_INT_ENABLED */

    #if(RPi_SPIS_INTERNAL_RX_INT_ENABLED)
        CyIntEnable(RPi_SPIS_RX_ISR_NUMBER);
    #endif /* RPi_SPIS_INTERNAL_RX_INT_ENABLED */
}


/*******************************************************************************
* Function Name: RPi_SPIS_DisableInt
********************************************************************************
*
* Summary:
*  Disable internal interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the internal interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void RPi_SPIS_DisableInt(void) 
{
    #if(RPi_SPIS_INTERNAL_TX_INT_ENABLED)
        CyIntDisable(RPi_SPIS_TX_ISR_NUMBER);
    #endif /* RPi_SPIS_INTERNAL_TX_INT_ENABLED */

    #if(RPi_SPIS_INTERNAL_RX_INT_ENABLED)
        CyIntDisable(RPi_SPIS_RX_ISR_NUMBER);
    #endif /* RPi_SPIS_INTERNAL_RX_INT_ENABLED */
}


/*******************************************************************************
* Function Name: RPi_SPIS_SetInterruptMode
********************************************************************************
*
* Summary:
*  Configure which status bits trigger an interrupt event.
*
* Parameters:
*  intSrc: An or'd combination of the desired status bit masks (defined in the
*  header file).
*
* Return:
*  None.
*
* Theory:
*  Enables the output of specific status bits to the interrupt controller.
*
*******************************************************************************/
void RPi_SPIS_SetInterruptMode(uint8 intSrc) 
{
    RPi_SPIS_TX_STATUS_MASK_REG  = intSrc;
    RPi_SPIS_RX_STATUS_MASK_REG  = intSrc;
}


/*******************************************************************************
* Function Name: RPi_SPIS_ReadStatus
********************************************************************************
*
* Summary:
*  Read the status register for the component.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the status register.
*
* Global variables:
*  RPi_SPIS_swStatus - used to store in software status register,
*  modified every function call - resets to zero.
*
* Theory:
*  Allows the user and the API to read the status register for error detection
*  and flow control.
*
* Side Effects:
*  Clear status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 RPi_SPIS_ReadStatus(void) 
{
    uint8 tmpStatus;

    #if ((RPi_SPIS_TX_SOFTWARE_BUF_ENABLED) || (RPi_SPIS_RX_SOFTWARE_BUF_ENABLED))

        RPi_SPIS_DisableInt();

        tmpStatus = RPi_SPIS_GET_STATUS_TX(RPi_SPIS_swStatusTx) |
              (RPi_SPIS_GET_STATUS_RX(RPi_SPIS_swStatusRx) & (uint8)~RPi_SPIS_STS_RX_FIFO_FULL);

        RPi_SPIS_swStatusTx = 0u;
        RPi_SPIS_swStatusRx = 0u;

        /* Enable Interrupts */
        RPi_SPIS_EnableInt();

    #else /* !((RPi_SPIS_TX_SOFTWARE_BUF_ENABLED) || (RPi_SPIS_RX_SOFTWARE_BUF_ENABLED)) */

        tmpStatus = RPi_SPIS_TX_STATUS_REG | (RPi_SPIS_RX_STATUS_REG &
                                                      (uint8)~RPi_SPIS_STS_RX_FIFO_FULL);

    #endif /* (RPi_SPIS_TX_SOFTWARE_BUF_ENABLED) || (RPi_SPIS_RX_SOFTWARE_BUF_ENABLED) */

    return(tmpStatus);
}


/* [] END OF FILE */
