/*******************************************************************************
* File Name: delta_sig_in.h  
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

#if !defined(CY_PINS_delta_sig_in_H) /* Pins delta_sig_in_H */
#define CY_PINS_delta_sig_in_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "delta_sig_in_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 delta_sig_in__PORT == 15 && ((delta_sig_in__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    delta_sig_in_Write(uint8 value);
void    delta_sig_in_SetDriveMode(uint8 mode);
uint8   delta_sig_in_ReadDataReg(void);
uint8   delta_sig_in_Read(void);
void    delta_sig_in_SetInterruptMode(uint16 position, uint16 mode);
uint8   delta_sig_in_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the delta_sig_in_SetDriveMode() function.
     *  @{
     */
        #define delta_sig_in_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define delta_sig_in_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define delta_sig_in_DM_RES_UP          PIN_DM_RES_UP
        #define delta_sig_in_DM_RES_DWN         PIN_DM_RES_DWN
        #define delta_sig_in_DM_OD_LO           PIN_DM_OD_LO
        #define delta_sig_in_DM_OD_HI           PIN_DM_OD_HI
        #define delta_sig_in_DM_STRONG          PIN_DM_STRONG
        #define delta_sig_in_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define delta_sig_in_MASK               delta_sig_in__MASK
#define delta_sig_in_SHIFT              delta_sig_in__SHIFT
#define delta_sig_in_WIDTH              1u

/* Interrupt constants */
#if defined(delta_sig_in__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in delta_sig_in_SetInterruptMode() function.
     *  @{
     */
        #define delta_sig_in_INTR_NONE      (uint16)(0x0000u)
        #define delta_sig_in_INTR_RISING    (uint16)(0x0001u)
        #define delta_sig_in_INTR_FALLING   (uint16)(0x0002u)
        #define delta_sig_in_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define delta_sig_in_INTR_MASK      (0x01u) 
#endif /* (delta_sig_in__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define delta_sig_in_PS                     (* (reg8 *) delta_sig_in__PS)
/* Data Register */
#define delta_sig_in_DR                     (* (reg8 *) delta_sig_in__DR)
/* Port Number */
#define delta_sig_in_PRT_NUM                (* (reg8 *) delta_sig_in__PRT) 
/* Connect to Analog Globals */                                                  
#define delta_sig_in_AG                     (* (reg8 *) delta_sig_in__AG)                       
/* Analog MUX bux enable */
#define delta_sig_in_AMUX                   (* (reg8 *) delta_sig_in__AMUX) 
/* Bidirectional Enable */                                                        
#define delta_sig_in_BIE                    (* (reg8 *) delta_sig_in__BIE)
/* Bit-mask for Aliased Register Access */
#define delta_sig_in_BIT_MASK               (* (reg8 *) delta_sig_in__BIT_MASK)
/* Bypass Enable */
#define delta_sig_in_BYP                    (* (reg8 *) delta_sig_in__BYP)
/* Port wide control signals */                                                   
#define delta_sig_in_CTL                    (* (reg8 *) delta_sig_in__CTL)
/* Drive Modes */
#define delta_sig_in_DM0                    (* (reg8 *) delta_sig_in__DM0) 
#define delta_sig_in_DM1                    (* (reg8 *) delta_sig_in__DM1)
#define delta_sig_in_DM2                    (* (reg8 *) delta_sig_in__DM2) 
/* Input Buffer Disable Override */
#define delta_sig_in_INP_DIS                (* (reg8 *) delta_sig_in__INP_DIS)
/* LCD Common or Segment Drive */
#define delta_sig_in_LCD_COM_SEG            (* (reg8 *) delta_sig_in__LCD_COM_SEG)
/* Enable Segment LCD */
#define delta_sig_in_LCD_EN                 (* (reg8 *) delta_sig_in__LCD_EN)
/* Slew Rate Control */
#define delta_sig_in_SLW                    (* (reg8 *) delta_sig_in__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define delta_sig_in_PRTDSI__CAPS_SEL       (* (reg8 *) delta_sig_in__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define delta_sig_in_PRTDSI__DBL_SYNC_IN    (* (reg8 *) delta_sig_in__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define delta_sig_in_PRTDSI__OE_SEL0        (* (reg8 *) delta_sig_in__PRTDSI__OE_SEL0) 
#define delta_sig_in_PRTDSI__OE_SEL1        (* (reg8 *) delta_sig_in__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define delta_sig_in_PRTDSI__OUT_SEL0       (* (reg8 *) delta_sig_in__PRTDSI__OUT_SEL0) 
#define delta_sig_in_PRTDSI__OUT_SEL1       (* (reg8 *) delta_sig_in__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define delta_sig_in_PRTDSI__SYNC_OUT       (* (reg8 *) delta_sig_in__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(delta_sig_in__SIO_CFG)
    #define delta_sig_in_SIO_HYST_EN        (* (reg8 *) delta_sig_in__SIO_HYST_EN)
    #define delta_sig_in_SIO_REG_HIFREQ     (* (reg8 *) delta_sig_in__SIO_REG_HIFREQ)
    #define delta_sig_in_SIO_CFG            (* (reg8 *) delta_sig_in__SIO_CFG)
    #define delta_sig_in_SIO_DIFF           (* (reg8 *) delta_sig_in__SIO_DIFF)
#endif /* (delta_sig_in__SIO_CFG) */

/* Interrupt Registers */
#if defined(delta_sig_in__INTSTAT)
    #define delta_sig_in_INTSTAT            (* (reg8 *) delta_sig_in__INTSTAT)
    #define delta_sig_in_SNAP               (* (reg8 *) delta_sig_in__SNAP)
    
	#define delta_sig_in_0_INTTYPE_REG 		(* (reg8 *) delta_sig_in__0__INTTYPE)
#endif /* (delta_sig_in__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_delta_sig_in_H */


/* [] END OF FILE */
