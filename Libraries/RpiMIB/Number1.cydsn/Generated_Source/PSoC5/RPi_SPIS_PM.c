/*******************************************************************************
* File Name: RPi_SPIS_PM.c
* Version 2.70
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "RPi_SPIS_PVT.h"

static RPi_SPIS_BACKUP_STRUCT RPi_SPIS_backup = 
{
    RPi_SPIS_DISABLED,
    RPi_SPIS_BITCTR_INIT,
};


/*******************************************************************************
* Function Name: RPi_SPIS_SaveConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void RPi_SPIS_SaveConfig(void) 
{

}


/*******************************************************************************
* Function Name: RPi_SPIS_RestoreConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void RPi_SPIS_RestoreConfig(void) 
{

}


/*******************************************************************************
* Function Name: RPi_SPIS_Sleep
********************************************************************************
*
* Summary:
*  Prepare SPI Slave Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  RPi_SPIS_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void RPi_SPIS_Sleep(void) 
{
    /* Save components enable state */
    if ((RPi_SPIS_TX_STATUS_ACTL_REG & RPi_SPIS_INT_ENABLE) != 0u)
    {
        RPi_SPIS_backup.enableState = 1u;
    }
    else /* Components block is disabled */
    {
        RPi_SPIS_backup.enableState = 0u;
    }

    RPi_SPIS_Stop();

}


/*******************************************************************************
* Function Name: RPi_SPIS_Wakeup
********************************************************************************
*
* Summary:
*  Prepare SPIM Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  RPi_SPIS_backup - used when non-retention registers are restored.
*  RPi_SPIS_txBufferWrite - modified every function call - resets to
*  zero.
*  RPi_SPIS_txBufferRead - modified every function call - resets to
*  zero.
*  RPi_SPIS_rxBufferWrite - modified every function call - resets to
*  zero.
*  RPi_SPIS_rxBufferRead - modified every function call - resets to
*  zero.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void RPi_SPIS_Wakeup(void) 
{
    #if (RPi_SPIS_TX_SOFTWARE_BUF_ENABLED)
        RPi_SPIS_txBufferFull = 0u;
        RPi_SPIS_txBufferRead = 0u;
        RPi_SPIS_txBufferWrite = 0u;
    #endif /* RPi_SPIS_TX_SOFTWARE_BUF_ENABLED */

    #if (RPi_SPIS_RX_SOFTWARE_BUF_ENABLED)
        RPi_SPIS_rxBufferFull = 0u;
        RPi_SPIS_rxBufferRead = 0u;
        RPi_SPIS_rxBufferWrite = 0u;
    #endif /* RPi_SPIS_RX_SOFTWARE_BUF_ENABLED */

    RPi_SPIS_ClearFIFO();

    /* Restore components block enable state */
    if (RPi_SPIS_backup.enableState != 0u)
    {
         /* Components block was enabled */
         RPi_SPIS_Enable();
    } /* Do nothing if components block was disabled */
}


/* [] END OF FILE */
