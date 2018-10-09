/*******************************************************************************
* File Name: Supply_monitor.h  
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

#if !defined(CY_PINS_Supply_monitor_H) /* Pins Supply_monitor_H */
#define CY_PINS_Supply_monitor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Supply_monitor_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Supply_monitor__PORT == 15 && ((Supply_monitor__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Supply_monitor_Write(uint8 value);
void    Supply_monitor_SetDriveMode(uint8 mode);
uint8   Supply_monitor_ReadDataReg(void);
uint8   Supply_monitor_Read(void);
void    Supply_monitor_SetInterruptMode(uint16 position, uint16 mode);
uint8   Supply_monitor_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Supply_monitor_SetDriveMode() function.
     *  @{
     */
        #define Supply_monitor_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Supply_monitor_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Supply_monitor_DM_RES_UP          PIN_DM_RES_UP
        #define Supply_monitor_DM_RES_DWN         PIN_DM_RES_DWN
        #define Supply_monitor_DM_OD_LO           PIN_DM_OD_LO
        #define Supply_monitor_DM_OD_HI           PIN_DM_OD_HI
        #define Supply_monitor_DM_STRONG          PIN_DM_STRONG
        #define Supply_monitor_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Supply_monitor_MASK               Supply_monitor__MASK
#define Supply_monitor_SHIFT              Supply_monitor__SHIFT
#define Supply_monitor_WIDTH              1u

/* Interrupt constants */
#if defined(Supply_monitor__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Supply_monitor_SetInterruptMode() function.
     *  @{
     */
        #define Supply_monitor_INTR_NONE      (uint16)(0x0000u)
        #define Supply_monitor_INTR_RISING    (uint16)(0x0001u)
        #define Supply_monitor_INTR_FALLING   (uint16)(0x0002u)
        #define Supply_monitor_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Supply_monitor_INTR_MASK      (0x01u) 
#endif /* (Supply_monitor__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Supply_monitor_PS                     (* (reg8 *) Supply_monitor__PS)
/* Data Register */
#define Supply_monitor_DR                     (* (reg8 *) Supply_monitor__DR)
/* Port Number */
#define Supply_monitor_PRT_NUM                (* (reg8 *) Supply_monitor__PRT) 
/* Connect to Analog Globals */                                                  
#define Supply_monitor_AG                     (* (reg8 *) Supply_monitor__AG)                       
/* Analog MUX bux enable */
#define Supply_monitor_AMUX                   (* (reg8 *) Supply_monitor__AMUX) 
/* Bidirectional Enable */                                                        
#define Supply_monitor_BIE                    (* (reg8 *) Supply_monitor__BIE)
/* Bit-mask for Aliased Register Access */
#define Supply_monitor_BIT_MASK               (* (reg8 *) Supply_monitor__BIT_MASK)
/* Bypass Enable */
#define Supply_monitor_BYP                    (* (reg8 *) Supply_monitor__BYP)
/* Port wide control signals */                                                   
#define Supply_monitor_CTL                    (* (reg8 *) Supply_monitor__CTL)
/* Drive Modes */
#define Supply_monitor_DM0                    (* (reg8 *) Supply_monitor__DM0) 
#define Supply_monitor_DM1                    (* (reg8 *) Supply_monitor__DM1)
#define Supply_monitor_DM2                    (* (reg8 *) Supply_monitor__DM2) 
/* Input Buffer Disable Override */
#define Supply_monitor_INP_DIS                (* (reg8 *) Supply_monitor__INP_DIS)
/* LCD Common or Segment Drive */
#define Supply_monitor_LCD_COM_SEG            (* (reg8 *) Supply_monitor__LCD_COM_SEG)
/* Enable Segment LCD */
#define Supply_monitor_LCD_EN                 (* (reg8 *) Supply_monitor__LCD_EN)
/* Slew Rate Control */
#define Supply_monitor_SLW                    (* (reg8 *) Supply_monitor__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Supply_monitor_PRTDSI__CAPS_SEL       (* (reg8 *) Supply_monitor__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Supply_monitor_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Supply_monitor__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Supply_monitor_PRTDSI__OE_SEL0        (* (reg8 *) Supply_monitor__PRTDSI__OE_SEL0) 
#define Supply_monitor_PRTDSI__OE_SEL1        (* (reg8 *) Supply_monitor__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Supply_monitor_PRTDSI__OUT_SEL0       (* (reg8 *) Supply_monitor__PRTDSI__OUT_SEL0) 
#define Supply_monitor_PRTDSI__OUT_SEL1       (* (reg8 *) Supply_monitor__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Supply_monitor_PRTDSI__SYNC_OUT       (* (reg8 *) Supply_monitor__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Supply_monitor__SIO_CFG)
    #define Supply_monitor_SIO_HYST_EN        (* (reg8 *) Supply_monitor__SIO_HYST_EN)
    #define Supply_monitor_SIO_REG_HIFREQ     (* (reg8 *) Supply_monitor__SIO_REG_HIFREQ)
    #define Supply_monitor_SIO_CFG            (* (reg8 *) Supply_monitor__SIO_CFG)
    #define Supply_monitor_SIO_DIFF           (* (reg8 *) Supply_monitor__SIO_DIFF)
#endif /* (Supply_monitor__SIO_CFG) */

/* Interrupt Registers */
#if defined(Supply_monitor__INTSTAT)
    #define Supply_monitor_INTSTAT            (* (reg8 *) Supply_monitor__INTSTAT)
    #define Supply_monitor_SNAP               (* (reg8 *) Supply_monitor__SNAP)
    
	#define Supply_monitor_0_INTTYPE_REG 		(* (reg8 *) Supply_monitor__0__INTTYPE)
#endif /* (Supply_monitor__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Supply_monitor_H */


/* [] END OF FILE */
