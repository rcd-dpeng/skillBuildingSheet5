/*******************************************************************************
* File Name: Control_Reg_SS_SigGen_PM.c
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

#include "Control_Reg_SS_SigGen.h"

/* Check for removal by optimization */
#if !defined(Control_Reg_SS_SigGen_Sync_ctrl_reg__REMOVED)

static Control_Reg_SS_SigGen_BACKUP_STRUCT  Control_Reg_SS_SigGen_backup = {0u};

    
/*******************************************************************************
* Function Name: Control_Reg_SS_SigGen_SaveConfig
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
void Control_Reg_SS_SigGen_SaveConfig(void) 
{
    Control_Reg_SS_SigGen_backup.controlState = Control_Reg_SS_SigGen_Control;
}


/*******************************************************************************
* Function Name: Control_Reg_SS_SigGen_RestoreConfig
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
void Control_Reg_SS_SigGen_RestoreConfig(void) 
{
     Control_Reg_SS_SigGen_Control = Control_Reg_SS_SigGen_backup.controlState;
}


/*******************************************************************************
* Function Name: Control_Reg_SS_SigGen_Sleep
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
void Control_Reg_SS_SigGen_Sleep(void) 
{
    Control_Reg_SS_SigGen_SaveConfig();
}


/*******************************************************************************
* Function Name: Control_Reg_SS_SigGen_Wakeup
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
void Control_Reg_SS_SigGen_Wakeup(void)  
{
    Control_Reg_SS_SigGen_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */