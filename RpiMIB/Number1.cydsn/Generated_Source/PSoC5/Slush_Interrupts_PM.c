/*******************************************************************************
* File Name: Slush_Interrupts_PM.c
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

#include "Slush_Interrupts.h"

/* Check for removal by optimization */
#if !defined(Slush_Interrupts_Sync_ctrl_reg__REMOVED)

static Slush_Interrupts_BACKUP_STRUCT  Slush_Interrupts_backup = {0u};

    
/*******************************************************************************
* Function Name: Slush_Interrupts_SaveConfig
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
void Slush_Interrupts_SaveConfig(void) 
{
    Slush_Interrupts_backup.controlState = Slush_Interrupts_Control;
}


/*******************************************************************************
* Function Name: Slush_Interrupts_RestoreConfig
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
void Slush_Interrupts_RestoreConfig(void) 
{
     Slush_Interrupts_Control = Slush_Interrupts_backup.controlState;
}


/*******************************************************************************
* Function Name: Slush_Interrupts_Sleep
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
void Slush_Interrupts_Sleep(void) 
{
    Slush_Interrupts_SaveConfig();
}


/*******************************************************************************
* Function Name: Slush_Interrupts_Wakeup
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
void Slush_Interrupts_Wakeup(void)  
{
    Slush_Interrupts_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
