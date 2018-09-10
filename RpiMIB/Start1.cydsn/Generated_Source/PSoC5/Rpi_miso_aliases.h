/*******************************************************************************
* File Name: Rpi_miso.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Rpi_miso_ALIASES_H) /* Pins Rpi_miso_ALIASES_H */
#define CY_PINS_Rpi_miso_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define Rpi_miso_0			(Rpi_miso__0__PC)
#define Rpi_miso_0_INTR	((uint16)((uint16)0x0001u << Rpi_miso__0__SHIFT))

#define Rpi_miso_INTR_ALL	 ((uint16)(Rpi_miso_0_INTR))

#endif /* End Pins Rpi_miso_ALIASES_H */


/* [] END OF FILE */
