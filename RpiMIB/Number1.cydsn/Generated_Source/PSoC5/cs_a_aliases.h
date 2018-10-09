/*******************************************************************************
* File Name: cs_a.h  
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

#if !defined(CY_PINS_cs_a_ALIASES_H) /* Pins cs_a_ALIASES_H */
#define CY_PINS_cs_a_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define cs_a_0			(cs_a__0__PC)
#define cs_a_0_INTR	((uint16)((uint16)0x0001u << cs_a__0__SHIFT))

#define cs_a_INTR_ALL	 ((uint16)(cs_a_0_INTR))

#endif /* End Pins cs_a_ALIASES_H */


/* [] END OF FILE */
