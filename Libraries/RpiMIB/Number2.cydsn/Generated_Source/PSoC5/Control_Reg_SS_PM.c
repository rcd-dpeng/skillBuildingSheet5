/*******************************************************************************
* File Name: Control_Reg_SS_PM.c
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

#include "Control_Reg_SS.h"

/* Check for removal by optimization */
#if !defined(Control_Reg_SS_Sync_ctrl_reg__REMOVED)

static Control_Reg_SS_BACKUP_STRUCT  Control_Reg_SS_backup = {0u};

    
/*******************************************************************************
* Function Name: Control_Reg_SS_SaveConfig
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
void Control_Reg_SS_SaveConfig(void) 
{
    Control_Reg_SS_backup.controlState = Control_Reg_SS_Control;
}


/*******************************************************************************
* Function Name: Control_Reg_SS_RestoreConfig
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
void Control_Reg_SS_RestoreConfig(void) 
{
     Control_Reg_SS_Control = Control_Reg_SS_backup.controlState;
}


/*******************************************************************************
* Function Name: Control_Reg_SS_Sleep
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
void Control_Reg_SS_Sleep(void) 
{
    Control_Reg_SS_SaveConfig();
}


/*******************************************************************************
* Function Name: Control_Reg_SS_Wakeup
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
void Control_Reg_SS_Wakeup(void)  
{
    Control_Reg_SS_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
