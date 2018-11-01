/*******************************************************************************
* File Name: SPIM_SigGen_PM.c
* Version 2.50
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

#include "SPIM_SigGen_PVT.h"

static SPIM_SigGen_BACKUP_STRUCT SPIM_SigGen_backup =
{
    SPIM_SigGen_DISABLED,
    SPIM_SigGen_BITCTR_INIT,
};


/*******************************************************************************
* Function Name: SPIM_SigGen_SaveConfig
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
void SPIM_SigGen_SaveConfig(void) 
{

}


/*******************************************************************************
* Function Name: SPIM_SigGen_RestoreConfig
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
void SPIM_SigGen_RestoreConfig(void) 
{

}


/*******************************************************************************
* Function Name: SPIM_SigGen_Sleep
********************************************************************************
*
* Summary:
*  Prepare SPIM Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SPIM_SigGen_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPIM_SigGen_Sleep(void) 
{
    /* Save components enable state */
    SPIM_SigGen_backup.enableState = ((uint8) SPIM_SigGen_IS_ENABLED);

    SPIM_SigGen_Stop();
}


/*******************************************************************************
* Function Name: SPIM_SigGen_Wakeup
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
*  SPIM_SigGen_backup - used when non-retention registers are restored.
*  SPIM_SigGen_txBufferWrite - modified every function call - resets to
*  zero.
*  SPIM_SigGen_txBufferRead - modified every function call - resets to
*  zero.
*  SPIM_SigGen_rxBufferWrite - modified every function call - resets to
*  zero.
*  SPIM_SigGen_rxBufferRead - modified every function call - resets to
*  zero.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPIM_SigGen_Wakeup(void) 
{
    #if(SPIM_SigGen_RX_SOFTWARE_BUF_ENABLED)
        SPIM_SigGen_rxBufferFull  = 0u;
        SPIM_SigGen_rxBufferRead  = 0u;
        SPIM_SigGen_rxBufferWrite = 0u;
    #endif /* (SPIM_SigGen_RX_SOFTWARE_BUF_ENABLED) */

    #if(SPIM_SigGen_TX_SOFTWARE_BUF_ENABLED)
        SPIM_SigGen_txBufferFull  = 0u;
        SPIM_SigGen_txBufferRead  = 0u;
        SPIM_SigGen_txBufferWrite = 0u;
    #endif /* (SPIM_SigGen_TX_SOFTWARE_BUF_ENABLED) */

    /* Clear any data from the RX and TX FIFO */
    SPIM_SigGen_ClearFIFO();

    /* Restore components block enable state */
    if(0u != SPIM_SigGen_backup.enableState)
    {
        SPIM_SigGen_Enable();
    }
}


/* [] END OF FILE */
