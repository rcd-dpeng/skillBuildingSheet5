/*******************************************************************************
* File Name: Slush_I2C_interrupts.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware to read the value of a Status 
*  Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Slush_I2C_interrupts.h"

#if !defined(Slush_I2C_interrupts_sts_intr_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: Slush_I2C_interrupts_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The current value in the Status Register.
*
*******************************************************************************/
uint8 Slush_I2C_interrupts_Read(void) 
{ 
    return Slush_I2C_interrupts_Status;
}


/*******************************************************************************
* Function Name: Slush_I2C_interrupts_InterruptEnable
********************************************************************************
*
* Summary:
*  Enables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Slush_I2C_interrupts_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    Slush_I2C_interrupts_Status_Aux_Ctrl |= Slush_I2C_interrupts_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Slush_I2C_interrupts_InterruptDisable
********************************************************************************
*
* Summary:
*  Disables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Slush_I2C_interrupts_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    Slush_I2C_interrupts_Status_Aux_Ctrl &= (uint8)(~Slush_I2C_interrupts_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Slush_I2C_interrupts_WriteMask
********************************************************************************
*
* Summary:
*  Writes the current mask value assigned to the Status Register.
*
* Parameters:
*  mask:  Value to write into the mask register.
*
* Return:
*  None.
*
*******************************************************************************/
void Slush_I2C_interrupts_WriteMask(uint8 mask) 
{
    #if(Slush_I2C_interrupts_INPUTS < 8u)
    	mask &= ((uint8)(1u << Slush_I2C_interrupts_INPUTS) - 1u);
	#endif /* End Slush_I2C_interrupts_INPUTS < 8u */
    Slush_I2C_interrupts_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: Slush_I2C_interrupts_ReadMask
********************************************************************************
*
* Summary:
*  Reads the current interrupt mask assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The value of the interrupt mask of the Status Register.
*
*******************************************************************************/
uint8 Slush_I2C_interrupts_ReadMask(void) 
{
    return Slush_I2C_interrupts_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
