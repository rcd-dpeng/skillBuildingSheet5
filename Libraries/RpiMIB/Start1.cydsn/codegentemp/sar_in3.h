/*******************************************************************************
* File Name: sar_in3.h  
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

#if !defined(CY_PINS_sar_in3_H) /* Pins sar_in3_H */
#define CY_PINS_sar_in3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "sar_in3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 sar_in3__PORT == 15 && ((sar_in3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    sar_in3_Write(uint8 value);
void    sar_in3_SetDriveMode(uint8 mode);
uint8   sar_in3_ReadDataReg(void);
uint8   sar_in3_Read(void);
void    sar_in3_SetInterruptMode(uint16 position, uint16 mode);
uint8   sar_in3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the sar_in3_SetDriveMode() function.
     *  @{
     */
        #define sar_in3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define sar_in3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define sar_in3_DM_RES_UP          PIN_DM_RES_UP
        #define sar_in3_DM_RES_DWN         PIN_DM_RES_DWN
        #define sar_in3_DM_OD_LO           PIN_DM_OD_LO
        #define sar_in3_DM_OD_HI           PIN_DM_OD_HI
        #define sar_in3_DM_STRONG          PIN_DM_STRONG
        #define sar_in3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define sar_in3_MASK               sar_in3__MASK
#define sar_in3_SHIFT              sar_in3__SHIFT
#define sar_in3_WIDTH              1u

/* Interrupt constants */
#if defined(sar_in3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in sar_in3_SetInterruptMode() function.
     *  @{
     */
        #define sar_in3_INTR_NONE      (uint16)(0x0000u)
        #define sar_in3_INTR_RISING    (uint16)(0x0001u)
        #define sar_in3_INTR_FALLING   (uint16)(0x0002u)
        #define sar_in3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define sar_in3_INTR_MASK      (0x01u) 
#endif /* (sar_in3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define sar_in3_PS                     (* (reg8 *) sar_in3__PS)
/* Data Register */
#define sar_in3_DR                     (* (reg8 *) sar_in3__DR)
/* Port Number */
#define sar_in3_PRT_NUM                (* (reg8 *) sar_in3__PRT) 
/* Connect to Analog Globals */                                                  
#define sar_in3_AG                     (* (reg8 *) sar_in3__AG)                       
/* Analog MUX bux enable */
#define sar_in3_AMUX                   (* (reg8 *) sar_in3__AMUX) 
/* Bidirectional Enable */                                                        
#define sar_in3_BIE                    (* (reg8 *) sar_in3__BIE)
/* Bit-mask for Aliased Register Access */
#define sar_in3_BIT_MASK               (* (reg8 *) sar_in3__BIT_MASK)
/* Bypass Enable */
#define sar_in3_BYP                    (* (reg8 *) sar_in3__BYP)
/* Port wide control signals */                                                   
#define sar_in3_CTL                    (* (reg8 *) sar_in3__CTL)
/* Drive Modes */
#define sar_in3_DM0                    (* (reg8 *) sar_in3__DM0) 
#define sar_in3_DM1                    (* (reg8 *) sar_in3__DM1)
#define sar_in3_DM2                    (* (reg8 *) sar_in3__DM2) 
/* Input Buffer Disable Override */
#define sar_in3_INP_DIS                (* (reg8 *) sar_in3__INP_DIS)
/* LCD Common or Segment Drive */
#define sar_in3_LCD_COM_SEG            (* (reg8 *) sar_in3__LCD_COM_SEG)
/* Enable Segment LCD */
#define sar_in3_LCD_EN                 (* (reg8 *) sar_in3__LCD_EN)
/* Slew Rate Control */
#define sar_in3_SLW                    (* (reg8 *) sar_in3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define sar_in3_PRTDSI__CAPS_SEL       (* (reg8 *) sar_in3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define sar_in3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) sar_in3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define sar_in3_PRTDSI__OE_SEL0        (* (reg8 *) sar_in3__PRTDSI__OE_SEL0) 
#define sar_in3_PRTDSI__OE_SEL1        (* (reg8 *) sar_in3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define sar_in3_PRTDSI__OUT_SEL0       (* (reg8 *) sar_in3__PRTDSI__OUT_SEL0) 
#define sar_in3_PRTDSI__OUT_SEL1       (* (reg8 *) sar_in3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define sar_in3_PRTDSI__SYNC_OUT       (* (reg8 *) sar_in3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(sar_in3__SIO_CFG)
    #define sar_in3_SIO_HYST_EN        (* (reg8 *) sar_in3__SIO_HYST_EN)
    #define sar_in3_SIO_REG_HIFREQ     (* (reg8 *) sar_in3__SIO_REG_HIFREQ)
    #define sar_in3_SIO_CFG            (* (reg8 *) sar_in3__SIO_CFG)
    #define sar_in3_SIO_DIFF           (* (reg8 *) sar_in3__SIO_DIFF)
#endif /* (sar_in3__SIO_CFG) */

/* Interrupt Registers */
#if defined(sar_in3__INTSTAT)
    #define sar_in3_INTSTAT            (* (reg8 *) sar_in3__INTSTAT)
    #define sar_in3_SNAP               (* (reg8 *) sar_in3__SNAP)
    
	#define sar_in3_0_INTTYPE_REG 		(* (reg8 *) sar_in3__0__INTTYPE)
#endif /* (sar_in3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_sar_in3_H */


/* [] END OF FILE */
