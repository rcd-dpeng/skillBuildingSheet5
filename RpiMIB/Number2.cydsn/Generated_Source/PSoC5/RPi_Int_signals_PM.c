/*******************************************************************************
* File Name: RPi_Int_signals_PM.c
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

#include "RPi_Int_signals.h"

/* Check for removal by optimization */
#if !defined(RPi_Int_signals_Sync_ctrl_reg__REMOVED)

static RPi_Int_signals_BACKUP_STRUCT  RPi_Int_signals_backup = {0u};

    
/*******************************************************************************
* Function Name: RPi_Int_signals_SaveConfig
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
void RPi_Int_signals_SaveConfig(void) 
{
    RPi_Int_signals_backup.controlState = RPi_Int_signals_Control;
}


/*******************************************************************************
* Function Name: RPi_Int_signals_RestoreConfig
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
void RPi_Int_signals_RestoreConfig(void) 
{
     RPi_Int_signals_Control = RPi_Int_signals_backup.controlState;
}


/*******************************************************************************
* Function Name: RPi_Int_signals_Sleep
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
void RPi_Int_signals_Sleep(void) 
{
    RPi_Int_signals_SaveConfig();
}


/*******************************************************************************
* Function Name: RPi_Int_signals_Wakeup
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
void RPi_Int_signals_Wakeup(void)  
{
    RPi_Int_signals_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
