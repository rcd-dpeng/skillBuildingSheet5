/*******************************************************************************
* File Name: TimerCounter_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "TimerCounter.h"

static TimerCounter_backupStruct TimerCounter_backup;


/*******************************************************************************
* Function Name: TimerCounter_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  TimerCounter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void TimerCounter_SaveConfig(void) 
{
    #if (!TimerCounter_UsingFixedFunction)

        TimerCounter_backup.CounterUdb = TimerCounter_ReadCounter();

        #if(!TimerCounter_ControlRegRemoved)
            TimerCounter_backup.CounterControlRegister = TimerCounter_ReadControlRegister();
        #endif /* (!TimerCounter_ControlRegRemoved) */

    #endif /* (!TimerCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: TimerCounter_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  TimerCounter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void TimerCounter_RestoreConfig(void) 
{      
    #if (!TimerCounter_UsingFixedFunction)

       TimerCounter_WriteCounter(TimerCounter_backup.CounterUdb);

        #if(!TimerCounter_ControlRegRemoved)
            TimerCounter_WriteControlRegister(TimerCounter_backup.CounterControlRegister);
        #endif /* (!TimerCounter_ControlRegRemoved) */

    #endif /* (!TimerCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: TimerCounter_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  TimerCounter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void TimerCounter_Sleep(void) 
{
    #if(!TimerCounter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(TimerCounter_CTRL_ENABLE == (TimerCounter_CONTROL & TimerCounter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            TimerCounter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            TimerCounter_backup.CounterEnableState = 0u;
        }
    #else
        TimerCounter_backup.CounterEnableState = 1u;
        if(TimerCounter_backup.CounterEnableState != 0u)
        {
            TimerCounter_backup.CounterEnableState = 0u;
        }
    #endif /* (!TimerCounter_ControlRegRemoved) */
    
    TimerCounter_Stop();
    TimerCounter_SaveConfig();
}


/*******************************************************************************
* Function Name: TimerCounter_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  TimerCounter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void TimerCounter_Wakeup(void) 
{
    TimerCounter_RestoreConfig();
    #if(!TimerCounter_ControlRegRemoved)
        if(TimerCounter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            TimerCounter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!TimerCounter_ControlRegRemoved) */
    
}


/* [] END OF FILE */
