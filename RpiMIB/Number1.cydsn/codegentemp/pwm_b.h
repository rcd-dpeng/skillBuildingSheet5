/*******************************************************************************
* File Name: pwm_b.h  
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

#if !defined(CY_PINS_pwm_b_H) /* Pins pwm_b_H */
#define CY_PINS_pwm_b_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pwm_b_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pwm_b__PORT == 15 && ((pwm_b__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pwm_b_Write(uint8 value);
void    pwm_b_SetDriveMode(uint8 mode);
uint8   pwm_b_ReadDataReg(void);
uint8   pwm_b_Read(void);
void    pwm_b_SetInterruptMode(uint16 position, uint16 mode);
uint8   pwm_b_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pwm_b_SetDriveMode() function.
     *  @{
     */
        #define pwm_b_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pwm_b_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pwm_b_DM_RES_UP          PIN_DM_RES_UP
        #define pwm_b_DM_RES_DWN         PIN_DM_RES_DWN
        #define pwm_b_DM_OD_LO           PIN_DM_OD_LO
        #define pwm_b_DM_OD_HI           PIN_DM_OD_HI
        #define pwm_b_DM_STRONG          PIN_DM_STRONG
        #define pwm_b_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pwm_b_MASK               pwm_b__MASK
#define pwm_b_SHIFT              pwm_b__SHIFT
#define pwm_b_WIDTH              1u

/* Interrupt constants */
#if defined(pwm_b__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pwm_b_SetInterruptMode() function.
     *  @{
     */
        #define pwm_b_INTR_NONE      (uint16)(0x0000u)
        #define pwm_b_INTR_RISING    (uint16)(0x0001u)
        #define pwm_b_INTR_FALLING   (uint16)(0x0002u)
        #define pwm_b_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pwm_b_INTR_MASK      (0x01u) 
#endif /* (pwm_b__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pwm_b_PS                     (* (reg8 *) pwm_b__PS)
/* Data Register */
#define pwm_b_DR                     (* (reg8 *) pwm_b__DR)
/* Port Number */
#define pwm_b_PRT_NUM                (* (reg8 *) pwm_b__PRT) 
/* Connect to Analog Globals */                                                  
#define pwm_b_AG                     (* (reg8 *) pwm_b__AG)                       
/* Analog MUX bux enable */
#define pwm_b_AMUX                   (* (reg8 *) pwm_b__AMUX) 
/* Bidirectional Enable */                                                        
#define pwm_b_BIE                    (* (reg8 *) pwm_b__BIE)
/* Bit-mask for Aliased Register Access */
#define pwm_b_BIT_MASK               (* (reg8 *) pwm_b__BIT_MASK)
/* Bypass Enable */
#define pwm_b_BYP                    (* (reg8 *) pwm_b__BYP)
/* Port wide control signals */                                                   
#define pwm_b_CTL                    (* (reg8 *) pwm_b__CTL)
/* Drive Modes */
#define pwm_b_DM0                    (* (reg8 *) pwm_b__DM0) 
#define pwm_b_DM1                    (* (reg8 *) pwm_b__DM1)
#define pwm_b_DM2                    (* (reg8 *) pwm_b__DM2) 
/* Input Buffer Disable Override */
#define pwm_b_INP_DIS                (* (reg8 *) pwm_b__INP_DIS)
/* LCD Common or Segment Drive */
#define pwm_b_LCD_COM_SEG            (* (reg8 *) pwm_b__LCD_COM_SEG)
/* Enable Segment LCD */
#define pwm_b_LCD_EN                 (* (reg8 *) pwm_b__LCD_EN)
/* Slew Rate Control */
#define pwm_b_SLW                    (* (reg8 *) pwm_b__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pwm_b_PRTDSI__CAPS_SEL       (* (reg8 *) pwm_b__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pwm_b_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pwm_b__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pwm_b_PRTDSI__OE_SEL0        (* (reg8 *) pwm_b__PRTDSI__OE_SEL0) 
#define pwm_b_PRTDSI__OE_SEL1        (* (reg8 *) pwm_b__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pwm_b_PRTDSI__OUT_SEL0       (* (reg8 *) pwm_b__PRTDSI__OUT_SEL0) 
#define pwm_b_PRTDSI__OUT_SEL1       (* (reg8 *) pwm_b__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pwm_b_PRTDSI__SYNC_OUT       (* (reg8 *) pwm_b__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pwm_b__SIO_CFG)
    #define pwm_b_SIO_HYST_EN        (* (reg8 *) pwm_b__SIO_HYST_EN)
    #define pwm_b_SIO_REG_HIFREQ     (* (reg8 *) pwm_b__SIO_REG_HIFREQ)
    #define pwm_b_SIO_CFG            (* (reg8 *) pwm_b__SIO_CFG)
    #define pwm_b_SIO_DIFF           (* (reg8 *) pwm_b__SIO_DIFF)
#endif /* (pwm_b__SIO_CFG) */

/* Interrupt Registers */
#if defined(pwm_b__INTSTAT)
    #define pwm_b_INTSTAT            (* (reg8 *) pwm_b__INTSTAT)
    #define pwm_b_SNAP               (* (reg8 *) pwm_b__SNAP)
    
	#define pwm_b_0_INTTYPE_REG 		(* (reg8 *) pwm_b__0__INTTYPE)
#endif /* (pwm_b__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pwm_b_H */


/* [] END OF FILE */
