/*******************************************************************************
* File Name: slush_inta.h  
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

#if !defined(CY_PINS_slush_inta_H) /* Pins slush_inta_H */
#define CY_PINS_slush_inta_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "slush_inta_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 slush_inta__PORT == 15 && ((slush_inta__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    slush_inta_Write(uint8 value);
void    slush_inta_SetDriveMode(uint8 mode);
uint8   slush_inta_ReadDataReg(void);
uint8   slush_inta_Read(void);
void    slush_inta_SetInterruptMode(uint16 position, uint16 mode);
uint8   slush_inta_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the slush_inta_SetDriveMode() function.
     *  @{
     */
        #define slush_inta_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define slush_inta_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define slush_inta_DM_RES_UP          PIN_DM_RES_UP
        #define slush_inta_DM_RES_DWN         PIN_DM_RES_DWN
        #define slush_inta_DM_OD_LO           PIN_DM_OD_LO
        #define slush_inta_DM_OD_HI           PIN_DM_OD_HI
        #define slush_inta_DM_STRONG          PIN_DM_STRONG
        #define slush_inta_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define slush_inta_MASK               slush_inta__MASK
#define slush_inta_SHIFT              slush_inta__SHIFT
#define slush_inta_WIDTH              1u

/* Interrupt constants */
#if defined(slush_inta__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in slush_inta_SetInterruptMode() function.
     *  @{
     */
        #define slush_inta_INTR_NONE      (uint16)(0x0000u)
        #define slush_inta_INTR_RISING    (uint16)(0x0001u)
        #define slush_inta_INTR_FALLING   (uint16)(0x0002u)
        #define slush_inta_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define slush_inta_INTR_MASK      (0x01u) 
#endif /* (slush_inta__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define slush_inta_PS                     (* (reg8 *) slush_inta__PS)
/* Data Register */
#define slush_inta_DR                     (* (reg8 *) slush_inta__DR)
/* Port Number */
#define slush_inta_PRT_NUM                (* (reg8 *) slush_inta__PRT) 
/* Connect to Analog Globals */                                                  
#define slush_inta_AG                     (* (reg8 *) slush_inta__AG)                       
/* Analog MUX bux enable */
#define slush_inta_AMUX                   (* (reg8 *) slush_inta__AMUX) 
/* Bidirectional Enable */                                                        
#define slush_inta_BIE                    (* (reg8 *) slush_inta__BIE)
/* Bit-mask for Aliased Register Access */
#define slush_inta_BIT_MASK               (* (reg8 *) slush_inta__BIT_MASK)
/* Bypass Enable */
#define slush_inta_BYP                    (* (reg8 *) slush_inta__BYP)
/* Port wide control signals */                                                   
#define slush_inta_CTL                    (* (reg8 *) slush_inta__CTL)
/* Drive Modes */
#define slush_inta_DM0                    (* (reg8 *) slush_inta__DM0) 
#define slush_inta_DM1                    (* (reg8 *) slush_inta__DM1)
#define slush_inta_DM2                    (* (reg8 *) slush_inta__DM2) 
/* Input Buffer Disable Override */
#define slush_inta_INP_DIS                (* (reg8 *) slush_inta__INP_DIS)
/* LCD Common or Segment Drive */
#define slush_inta_LCD_COM_SEG            (* (reg8 *) slush_inta__LCD_COM_SEG)
/* Enable Segment LCD */
#define slush_inta_LCD_EN                 (* (reg8 *) slush_inta__LCD_EN)
/* Slew Rate Control */
#define slush_inta_SLW                    (* (reg8 *) slush_inta__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define slush_inta_PRTDSI__CAPS_SEL       (* (reg8 *) slush_inta__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define slush_inta_PRTDSI__DBL_SYNC_IN    (* (reg8 *) slush_inta__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define slush_inta_PRTDSI__OE_SEL0        (* (reg8 *) slush_inta__PRTDSI__OE_SEL0) 
#define slush_inta_PRTDSI__OE_SEL1        (* (reg8 *) slush_inta__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define slush_inta_PRTDSI__OUT_SEL0       (* (reg8 *) slush_inta__PRTDSI__OUT_SEL0) 
#define slush_inta_PRTDSI__OUT_SEL1       (* (reg8 *) slush_inta__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define slush_inta_PRTDSI__SYNC_OUT       (* (reg8 *) slush_inta__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(slush_inta__SIO_CFG)
    #define slush_inta_SIO_HYST_EN        (* (reg8 *) slush_inta__SIO_HYST_EN)
    #define slush_inta_SIO_REG_HIFREQ     (* (reg8 *) slush_inta__SIO_REG_HIFREQ)
    #define slush_inta_SIO_CFG            (* (reg8 *) slush_inta__SIO_CFG)
    #define slush_inta_SIO_DIFF           (* (reg8 *) slush_inta__SIO_DIFF)
#endif /* (slush_inta__SIO_CFG) */

/* Interrupt Registers */
#if defined(slush_inta__INTSTAT)
    #define slush_inta_INTSTAT            (* (reg8 *) slush_inta__INTSTAT)
    #define slush_inta_SNAP               (* (reg8 *) slush_inta__SNAP)
    
	#define slush_inta_0_INTTYPE_REG 		(* (reg8 *) slush_inta__0__INTTYPE)
#endif /* (slush_inta__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_slush_inta_H */


/* [] END OF FILE */
