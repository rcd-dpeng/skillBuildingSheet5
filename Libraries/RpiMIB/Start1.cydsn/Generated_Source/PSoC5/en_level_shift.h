/*******************************************************************************
* File Name: en_level_shift.h  
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

#if !defined(CY_PINS_en_level_shift_H) /* Pins en_level_shift_H */
#define CY_PINS_en_level_shift_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "en_level_shift_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 en_level_shift__PORT == 15 && ((en_level_shift__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    en_level_shift_Write(uint8 value);
void    en_level_shift_SetDriveMode(uint8 mode);
uint8   en_level_shift_ReadDataReg(void);
uint8   en_level_shift_Read(void);
void    en_level_shift_SetInterruptMode(uint16 position, uint16 mode);
uint8   en_level_shift_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the en_level_shift_SetDriveMode() function.
     *  @{
     */
        #define en_level_shift_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define en_level_shift_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define en_level_shift_DM_RES_UP          PIN_DM_RES_UP
        #define en_level_shift_DM_RES_DWN         PIN_DM_RES_DWN
        #define en_level_shift_DM_OD_LO           PIN_DM_OD_LO
        #define en_level_shift_DM_OD_HI           PIN_DM_OD_HI
        #define en_level_shift_DM_STRONG          PIN_DM_STRONG
        #define en_level_shift_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define en_level_shift_MASK               en_level_shift__MASK
#define en_level_shift_SHIFT              en_level_shift__SHIFT
#define en_level_shift_WIDTH              1u

/* Interrupt constants */
#if defined(en_level_shift__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in en_level_shift_SetInterruptMode() function.
     *  @{
     */
        #define en_level_shift_INTR_NONE      (uint16)(0x0000u)
        #define en_level_shift_INTR_RISING    (uint16)(0x0001u)
        #define en_level_shift_INTR_FALLING   (uint16)(0x0002u)
        #define en_level_shift_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define en_level_shift_INTR_MASK      (0x01u) 
#endif /* (en_level_shift__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define en_level_shift_PS                     (* (reg8 *) en_level_shift__PS)
/* Data Register */
#define en_level_shift_DR                     (* (reg8 *) en_level_shift__DR)
/* Port Number */
#define en_level_shift_PRT_NUM                (* (reg8 *) en_level_shift__PRT) 
/* Connect to Analog Globals */                                                  
#define en_level_shift_AG                     (* (reg8 *) en_level_shift__AG)                       
/* Analog MUX bux enable */
#define en_level_shift_AMUX                   (* (reg8 *) en_level_shift__AMUX) 
/* Bidirectional Enable */                                                        
#define en_level_shift_BIE                    (* (reg8 *) en_level_shift__BIE)
/* Bit-mask for Aliased Register Access */
#define en_level_shift_BIT_MASK               (* (reg8 *) en_level_shift__BIT_MASK)
/* Bypass Enable */
#define en_level_shift_BYP                    (* (reg8 *) en_level_shift__BYP)
/* Port wide control signals */                                                   
#define en_level_shift_CTL                    (* (reg8 *) en_level_shift__CTL)
/* Drive Modes */
#define en_level_shift_DM0                    (* (reg8 *) en_level_shift__DM0) 
#define en_level_shift_DM1                    (* (reg8 *) en_level_shift__DM1)
#define en_level_shift_DM2                    (* (reg8 *) en_level_shift__DM2) 
/* Input Buffer Disable Override */
#define en_level_shift_INP_DIS                (* (reg8 *) en_level_shift__INP_DIS)
/* LCD Common or Segment Drive */
#define en_level_shift_LCD_COM_SEG            (* (reg8 *) en_level_shift__LCD_COM_SEG)
/* Enable Segment LCD */
#define en_level_shift_LCD_EN                 (* (reg8 *) en_level_shift__LCD_EN)
/* Slew Rate Control */
#define en_level_shift_SLW                    (* (reg8 *) en_level_shift__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define en_level_shift_PRTDSI__CAPS_SEL       (* (reg8 *) en_level_shift__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define en_level_shift_PRTDSI__DBL_SYNC_IN    (* (reg8 *) en_level_shift__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define en_level_shift_PRTDSI__OE_SEL0        (* (reg8 *) en_level_shift__PRTDSI__OE_SEL0) 
#define en_level_shift_PRTDSI__OE_SEL1        (* (reg8 *) en_level_shift__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define en_level_shift_PRTDSI__OUT_SEL0       (* (reg8 *) en_level_shift__PRTDSI__OUT_SEL0) 
#define en_level_shift_PRTDSI__OUT_SEL1       (* (reg8 *) en_level_shift__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define en_level_shift_PRTDSI__SYNC_OUT       (* (reg8 *) en_level_shift__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(en_level_shift__SIO_CFG)
    #define en_level_shift_SIO_HYST_EN        (* (reg8 *) en_level_shift__SIO_HYST_EN)
    #define en_level_shift_SIO_REG_HIFREQ     (* (reg8 *) en_level_shift__SIO_REG_HIFREQ)
    #define en_level_shift_SIO_CFG            (* (reg8 *) en_level_shift__SIO_CFG)
    #define en_level_shift_SIO_DIFF           (* (reg8 *) en_level_shift__SIO_DIFF)
#endif /* (en_level_shift__SIO_CFG) */

/* Interrupt Registers */
#if defined(en_level_shift__INTSTAT)
    #define en_level_shift_INTSTAT            (* (reg8 *) en_level_shift__INTSTAT)
    #define en_level_shift_SNAP               (* (reg8 *) en_level_shift__SNAP)
    
	#define en_level_shift_0_INTTYPE_REG 		(* (reg8 *) en_level_shift__0__INTTYPE)
#endif /* (en_level_shift__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_en_level_shift_H */


/* [] END OF FILE */
