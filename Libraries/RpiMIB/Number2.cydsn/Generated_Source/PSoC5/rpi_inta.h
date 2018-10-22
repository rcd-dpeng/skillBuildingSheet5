/*******************************************************************************
* File Name: rpi_inta.h  
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

#if !defined(CY_PINS_rpi_inta_H) /* Pins rpi_inta_H */
#define CY_PINS_rpi_inta_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "rpi_inta_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 rpi_inta__PORT == 15 && ((rpi_inta__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    rpi_inta_Write(uint8 value);
void    rpi_inta_SetDriveMode(uint8 mode);
uint8   rpi_inta_ReadDataReg(void);
uint8   rpi_inta_Read(void);
void    rpi_inta_SetInterruptMode(uint16 position, uint16 mode);
uint8   rpi_inta_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the rpi_inta_SetDriveMode() function.
     *  @{
     */
        #define rpi_inta_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define rpi_inta_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define rpi_inta_DM_RES_UP          PIN_DM_RES_UP
        #define rpi_inta_DM_RES_DWN         PIN_DM_RES_DWN
        #define rpi_inta_DM_OD_LO           PIN_DM_OD_LO
        #define rpi_inta_DM_OD_HI           PIN_DM_OD_HI
        #define rpi_inta_DM_STRONG          PIN_DM_STRONG
        #define rpi_inta_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define rpi_inta_MASK               rpi_inta__MASK
#define rpi_inta_SHIFT              rpi_inta__SHIFT
#define rpi_inta_WIDTH              1u

/* Interrupt constants */
#if defined(rpi_inta__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in rpi_inta_SetInterruptMode() function.
     *  @{
     */
        #define rpi_inta_INTR_NONE      (uint16)(0x0000u)
        #define rpi_inta_INTR_RISING    (uint16)(0x0001u)
        #define rpi_inta_INTR_FALLING   (uint16)(0x0002u)
        #define rpi_inta_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define rpi_inta_INTR_MASK      (0x01u) 
#endif /* (rpi_inta__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define rpi_inta_PS                     (* (reg8 *) rpi_inta__PS)
/* Data Register */
#define rpi_inta_DR                     (* (reg8 *) rpi_inta__DR)
/* Port Number */
#define rpi_inta_PRT_NUM                (* (reg8 *) rpi_inta__PRT) 
/* Connect to Analog Globals */                                                  
#define rpi_inta_AG                     (* (reg8 *) rpi_inta__AG)                       
/* Analog MUX bux enable */
#define rpi_inta_AMUX                   (* (reg8 *) rpi_inta__AMUX) 
/* Bidirectional Enable */                                                        
#define rpi_inta_BIE                    (* (reg8 *) rpi_inta__BIE)
/* Bit-mask for Aliased Register Access */
#define rpi_inta_BIT_MASK               (* (reg8 *) rpi_inta__BIT_MASK)
/* Bypass Enable */
#define rpi_inta_BYP                    (* (reg8 *) rpi_inta__BYP)
/* Port wide control signals */                                                   
#define rpi_inta_CTL                    (* (reg8 *) rpi_inta__CTL)
/* Drive Modes */
#define rpi_inta_DM0                    (* (reg8 *) rpi_inta__DM0) 
#define rpi_inta_DM1                    (* (reg8 *) rpi_inta__DM1)
#define rpi_inta_DM2                    (* (reg8 *) rpi_inta__DM2) 
/* Input Buffer Disable Override */
#define rpi_inta_INP_DIS                (* (reg8 *) rpi_inta__INP_DIS)
/* LCD Common or Segment Drive */
#define rpi_inta_LCD_COM_SEG            (* (reg8 *) rpi_inta__LCD_COM_SEG)
/* Enable Segment LCD */
#define rpi_inta_LCD_EN                 (* (reg8 *) rpi_inta__LCD_EN)
/* Slew Rate Control */
#define rpi_inta_SLW                    (* (reg8 *) rpi_inta__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define rpi_inta_PRTDSI__CAPS_SEL       (* (reg8 *) rpi_inta__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define rpi_inta_PRTDSI__DBL_SYNC_IN    (* (reg8 *) rpi_inta__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define rpi_inta_PRTDSI__OE_SEL0        (* (reg8 *) rpi_inta__PRTDSI__OE_SEL0) 
#define rpi_inta_PRTDSI__OE_SEL1        (* (reg8 *) rpi_inta__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define rpi_inta_PRTDSI__OUT_SEL0       (* (reg8 *) rpi_inta__PRTDSI__OUT_SEL0) 
#define rpi_inta_PRTDSI__OUT_SEL1       (* (reg8 *) rpi_inta__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define rpi_inta_PRTDSI__SYNC_OUT       (* (reg8 *) rpi_inta__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(rpi_inta__SIO_CFG)
    #define rpi_inta_SIO_HYST_EN        (* (reg8 *) rpi_inta__SIO_HYST_EN)
    #define rpi_inta_SIO_REG_HIFREQ     (* (reg8 *) rpi_inta__SIO_REG_HIFREQ)
    #define rpi_inta_SIO_CFG            (* (reg8 *) rpi_inta__SIO_CFG)
    #define rpi_inta_SIO_DIFF           (* (reg8 *) rpi_inta__SIO_DIFF)
#endif /* (rpi_inta__SIO_CFG) */

/* Interrupt Registers */
#if defined(rpi_inta__INTSTAT)
    #define rpi_inta_INTSTAT            (* (reg8 *) rpi_inta__INTSTAT)
    #define rpi_inta_SNAP               (* (reg8 *) rpi_inta__SNAP)
    
	#define rpi_inta_0_INTTYPE_REG 		(* (reg8 *) rpi_inta__0__INTTYPE)
#endif /* (rpi_inta__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_rpi_inta_H */


/* [] END OF FILE */
