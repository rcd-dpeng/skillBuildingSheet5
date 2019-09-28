/*******************************************************************************
* File Name: RpiInterrupts_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "RpiInterrupts.h"

/* Check for removal by optimization */
#if !defined(RpiInterrupts_Sync_ctrl_reg__REMOVED)

static RpiInterrupts_BACKUP_STRUCT  RpiInterrupts_backup = {0u};

    
/*******************************************************************************
* Function Name: RpiInterrupts_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RpiInterrupts_SaveConfig(void) 
{
    RpiInterrupts_backup.controlState = RpiInterrupts_Control;
}


/*******************************************************************************
* Function Name: RpiInterrupts_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void RpiInterrupts_RestoreConfig(void) 
{
     RpiInterrupts_Control = RpiInterrupts_backup.controlState;
}


/*******************************************************************************
* Function Name: RpiInterrupts_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RpiInterrupts_Sleep(void) 
{
    RpiInterrupts_SaveConfig();
}


/*******************************************************************************
* Function Name: RpiInterrupts_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RpiInterrupts_Wakeup(void)  
{
    RpiInterrupts_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
