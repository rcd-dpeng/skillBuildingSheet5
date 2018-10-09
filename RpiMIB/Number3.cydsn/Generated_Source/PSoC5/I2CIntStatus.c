/*******************************************************************************
* File Name: I2CIntStatus.c  
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

#include "I2CIntStatus.h"

#if !defined(I2CIntStatus_sts_intr_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: I2CIntStatus_Read
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
uint8 I2CIntStatus_Read(void) 
{ 
    return I2CIntStatus_Status;
}


/*******************************************************************************
* Function Name: I2CIntStatus_InterruptEnable
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
void I2CIntStatus_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    I2CIntStatus_Status_Aux_Ctrl |= I2CIntStatus_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: I2CIntStatus_InterruptDisable
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
void I2CIntStatus_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    I2CIntStatus_Status_Aux_Ctrl &= (uint8)(~I2CIntStatus_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: I2CIntStatus_WriteMask
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
void I2CIntStatus_WriteMask(uint8 mask) 
{
    #if(I2CIntStatus_INPUTS < 8u)
    	mask &= ((uint8)(1u << I2CIntStatus_INPUTS) - 1u);
	#endif /* End I2CIntStatus_INPUTS < 8u */
    I2CIntStatus_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: I2CIntStatus_ReadMask
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
uint8 I2CIntStatus_ReadMask(void) 
{
    return I2CIntStatus_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
