/*******************************************************************************
* File Name: enable_battery.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_enable_battery_H) /* Pins enable_battery_H */
#define CY_PINS_enable_battery_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "enable_battery_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 enable_battery__PORT == 15 && ((enable_battery__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    enable_battery_Write(uint8 value);
void    enable_battery_SetDriveMode(uint8 mode);
uint8   enable_battery_ReadDataReg(void);
uint8   enable_battery_Read(void);
void    enable_battery_SetInterruptMode(uint16 position, uint16 mode);
uint8   enable_battery_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the enable_battery_SetDriveMode() function.
     *  @{
     */
        #define enable_battery_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define enable_battery_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define enable_battery_DM_RES_UP          PIN_DM_RES_UP
        #define enable_battery_DM_RES_DWN         PIN_DM_RES_DWN
        #define enable_battery_DM_OD_LO           PIN_DM_OD_LO
        #define enable_battery_DM_OD_HI           PIN_DM_OD_HI
        #define enable_battery_DM_STRONG          PIN_DM_STRONG
        #define enable_battery_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define enable_battery_MASK               enable_battery__MASK
#define enable_battery_SHIFT              enable_battery__SHIFT
#define enable_battery_WIDTH              1u

/* Interrupt constants */
#if defined(enable_battery__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in enable_battery_SetInterruptMode() function.
     *  @{
     */
        #define enable_battery_INTR_NONE      (uint16)(0x0000u)
        #define enable_battery_INTR_RISING    (uint16)(0x0001u)
        #define enable_battery_INTR_FALLING   (uint16)(0x0002u)
        #define enable_battery_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define enable_battery_INTR_MASK      (0x01u) 
#endif /* (enable_battery__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define enable_battery_PS                     (* (reg8 *) enable_battery__PS)
/* Data Register */
#define enable_battery_DR                     (* (reg8 *) enable_battery__DR)
/* Port Number */
#define enable_battery_PRT_NUM                (* (reg8 *) enable_battery__PRT) 
/* Connect to Analog Globals */                                                  
#define enable_battery_AG                     (* (reg8 *) enable_battery__AG)                       
/* Analog MUX bux enable */
#define enable_battery_AMUX                   (* (reg8 *) enable_battery__AMUX) 
/* Bidirectional Enable */                                                        
#define enable_battery_BIE                    (* (reg8 *) enable_battery__BIE)
/* Bit-mask for Aliased Register Access */
#define enable_battery_BIT_MASK               (* (reg8 *) enable_battery__BIT_MASK)
/* Bypass Enable */
#define enable_battery_BYP                    (* (reg8 *) enable_battery__BYP)
/* Port wide control signals */                                                   
#define enable_battery_CTL                    (* (reg8 *) enable_battery__CTL)
/* Drive Modes */
#define enable_battery_DM0                    (* (reg8 *) enable_battery__DM0) 
#define enable_battery_DM1                    (* (reg8 *) enable_battery__DM1)
#define enable_battery_DM2                    (* (reg8 *) enable_battery__DM2) 
/* Input Buffer Disable Override */
#define enable_battery_INP_DIS                (* (reg8 *) enable_battery__INP_DIS)
/* LCD Common or Segment Drive */
#define enable_battery_LCD_COM_SEG            (* (reg8 *) enable_battery__LCD_COM_SEG)
/* Enable Segment LCD */
#define enable_battery_LCD_EN                 (* (reg8 *) enable_battery__LCD_EN)
/* Slew Rate Control */
#define enable_battery_SLW                    (* (reg8 *) enable_battery__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define enable_battery_PRTDSI__CAPS_SEL       (* (reg8 *) enable_battery__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define enable_battery_PRTDSI__DBL_SYNC_IN    (* (reg8 *) enable_battery__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define enable_battery_PRTDSI__OE_SEL0        (* (reg8 *) enable_battery__PRTDSI__OE_SEL0) 
#define enable_battery_PRTDSI__OE_SEL1        (* (reg8 *) enable_battery__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define enable_battery_PRTDSI__OUT_SEL0       (* (reg8 *) enable_battery__PRTDSI__OUT_SEL0) 
#define enable_battery_PRTDSI__OUT_SEL1       (* (reg8 *) enable_battery__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define enable_battery_PRTDSI__SYNC_OUT       (* (reg8 *) enable_battery__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(enable_battery__SIO_CFG)
    #define enable_battery_SIO_HYST_EN        (* (reg8 *) enable_battery__SIO_HYST_EN)
    #define enable_battery_SIO_REG_HIFREQ     (* (reg8 *) enable_battery__SIO_REG_HIFREQ)
    #define enable_battery_SIO_CFG            (* (reg8 *) enable_battery__SIO_CFG)
    #define enable_battery_SIO_DIFF           (* (reg8 *) enable_battery__SIO_DIFF)
#endif /* (enable_battery__SIO_CFG) */

/* Interrupt Registers */
#if defined(enable_battery__INTSTAT)
    #define enable_battery_INTSTAT            (* (reg8 *) enable_battery__INTSTAT)
    #define enable_battery_SNAP               (* (reg8 *) enable_battery__SNAP)
    
	#define enable_battery_0_INTTYPE_REG 		(* (reg8 *) enable_battery__0__INTTYPE)
#endif /* (enable_battery__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_enable_battery_H */


/* [] END OF FILE */
