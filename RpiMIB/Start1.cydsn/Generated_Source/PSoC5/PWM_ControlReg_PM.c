/*******************************************************************************
* File Name: PWM_ControlReg_PM.c
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

#include "PWM_ControlReg.h"

/* Check for removal by optimization */
#if !defined(PWM_ControlReg_Sync_ctrl_reg__REMOVED)

static PWM_ControlReg_BACKUP_STRUCT  PWM_ControlReg_backup = {0u};

    
/*******************************************************************************
* Function Name: PWM_ControlReg_SaveConfig
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
void PWM_ControlReg_SaveConfig(void) 
{
    PWM_ControlReg_backup.controlState = PWM_ControlReg_Control;
}


/*******************************************************************************
* Function Name: PWM_ControlReg_RestoreConfig
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
void PWM_ControlReg_RestoreConfig(void) 
{
     PWM_ControlReg_Control = PWM_ControlReg_backup.controlState;
}


/*******************************************************************************
* Function Name: PWM_ControlReg_Sleep
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
void PWM_ControlReg_Sleep(void) 
{
    PWM_ControlReg_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_ControlReg_Wakeup
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
void PWM_ControlReg_Wakeup(void)  
{
    PWM_ControlReg_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
