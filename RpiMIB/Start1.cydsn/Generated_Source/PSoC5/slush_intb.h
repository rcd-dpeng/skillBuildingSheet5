/*******************************************************************************
* File Name: slush_intb.h  
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

#if !defined(CY_PINS_slush_intb_H) /* Pins slush_intb_H */
#define CY_PINS_slush_intb_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "slush_intb_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 slush_intb__PORT == 15 && ((slush_intb__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    slush_intb_Write(uint8 value);
void    slush_intb_SetDriveMode(uint8 mode);
uint8   slush_intb_ReadDataReg(void);
uint8   slush_intb_Read(void);
void    slush_intb_SetInterruptMode(uint16 position, uint16 mode);
uint8   slush_intb_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the slush_intb_SetDriveMode() function.
     *  @{
     */
        #define slush_intb_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define slush_intb_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define slush_intb_DM_RES_UP          PIN_DM_RES_UP
        #define slush_intb_DM_RES_DWN         PIN_DM_RES_DWN
        #define slush_intb_DM_OD_LO           PIN_DM_OD_LO
        #define slush_intb_DM_OD_HI           PIN_DM_OD_HI
        #define slush_intb_DM_STRONG          PIN_DM_STRONG
        #define slush_intb_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define slush_intb_MASK               slush_intb__MASK
#define slush_intb_SHIFT              slush_intb__SHIFT
#define slush_intb_WIDTH              1u

/* Interrupt constants */
#if defined(slush_intb__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in slush_intb_SetInterruptMode() function.
     *  @{
     */
        #define slush_intb_INTR_NONE      (uint16)(0x0000u)
        #define slush_intb_INTR_RISING    (uint16)(0x0001u)
        #define slush_intb_INTR_FALLING   (uint16)(0x0002u)
        #define slush_intb_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define slush_intb_INTR_MASK      (0x01u) 
#endif /* (slush_intb__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define slush_intb_PS                     (* (reg8 *) slush_intb__PS)
/* Data Register */
#define slush_intb_DR                     (* (reg8 *) slush_intb__DR)
/* Port Number */
#define slush_intb_PRT_NUM                (* (reg8 *) slush_intb__PRT) 
/* Connect to Analog Globals */                                                  
#define slush_intb_AG                     (* (reg8 *) slush_intb__AG)                       
/* Analog MUX bux enable */
#define slush_intb_AMUX                   (* (reg8 *) slush_intb__AMUX) 
/* Bidirectional Enable */                                                        
#define slush_intb_BIE                    (* (reg8 *) slush_intb__BIE)
/* Bit-mask for Aliased Register Access */
#define slush_intb_BIT_MASK               (* (reg8 *) slush_intb__BIT_MASK)
/* Bypass Enable */
#define slush_intb_BYP                    (* (reg8 *) slush_intb__BYP)
/* Port wide control signals */                                                   
#define slush_intb_CTL                    (* (reg8 *) slush_intb__CTL)
/* Drive Modes */
#define slush_intb_DM0                    (* (reg8 *) slush_intb__DM0) 
#define slush_intb_DM1                    (* (reg8 *) slush_intb__DM1)
#define slush_intb_DM2                    (* (reg8 *) slush_intb__DM2) 
/* Input Buffer Disable Override */
#define slush_intb_INP_DIS                (* (reg8 *) slush_intb__INP_DIS)
/* LCD Common or Segment Drive */
#define slush_intb_LCD_COM_SEG            (* (reg8 *) slush_intb__LCD_COM_SEG)
/* Enable Segment LCD */
#define slush_intb_LCD_EN                 (* (reg8 *) slush_intb__LCD_EN)
/* Slew Rate Control */
#define slush_intb_SLW                    (* (reg8 *) slush_intb__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define slush_intb_PRTDSI__CAPS_SEL       (* (reg8 *) slush_intb__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define slush_intb_PRTDSI__DBL_SYNC_IN    (* (reg8 *) slush_intb__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define slush_intb_PRTDSI__OE_SEL0        (* (reg8 *) slush_intb__PRTDSI__OE_SEL0) 
#define slush_intb_PRTDSI__OE_SEL1        (* (reg8 *) slush_intb__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define slush_intb_PRTDSI__OUT_SEL0       (* (reg8 *) slush_intb__PRTDSI__OUT_SEL0) 
#define slush_intb_PRTDSI__OUT_SEL1       (* (reg8 *) slush_intb__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define slush_intb_PRTDSI__SYNC_OUT       (* (reg8 *) slush_intb__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(slush_intb__SIO_CFG)
    #define slush_intb_SIO_HYST_EN        (* (reg8 *) slush_intb__SIO_HYST_EN)
    #define slush_intb_SIO_REG_HIFREQ     (* (reg8 *) slush_intb__SIO_REG_HIFREQ)
    #define slush_intb_SIO_CFG            (* (reg8 *) slush_intb__SIO_CFG)
    #define slush_intb_SIO_DIFF           (* (reg8 *) slush_intb__SIO_DIFF)
#endif /* (slush_intb__SIO_CFG) */

/* Interrupt Registers */
#if defined(slush_intb__INTSTAT)
    #define slush_intb_INTSTAT            (* (reg8 *) slush_intb__INTSTAT)
    #define slush_intb_SNAP               (* (reg8 *) slush_intb__SNAP)
    
	#define slush_intb_0_INTTYPE_REG 		(* (reg8 *) slush_intb__0__INTTYPE)
#endif /* (slush_intb__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_slush_intb_H */


/* [] END OF FILE */
