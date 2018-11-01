/*******************************************************************************
* File Name: enable_battery.h  
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

#if !defined(CY_PINS_enable_battery_ALIASES_H) /* Pins enable_battery_ALIASES_H */
#define CY_PINS_enable_battery_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define enable_battery_0			(enable_battery__0__PC)
#define enable_battery_0_INTR	((uint16)((uint16)0x0001u << enable_battery__0__SHIFT))

#define enable_battery_INTR_ALL	 ((uint16)(enable_battery_0_INTR))

#endif /* End Pins enable_battery_ALIASES_H */


/* [] END OF FILE */
