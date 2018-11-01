/*******************************************************************************
* File Name: Rpi_miso.h  
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

#if !defined(CY_PINS_Rpi_miso_H) /* Pins Rpi_miso_H */
#define CY_PINS_Rpi_miso_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Rpi_miso_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Rpi_miso__PORT == 15 && ((Rpi_miso__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Rpi_miso_Write(uint8 value);
void    Rpi_miso_SetDriveMode(uint8 mode);
uint8   Rpi_miso_ReadDataReg(void);
uint8   Rpi_miso_Read(void);
void    Rpi_miso_SetInterruptMode(uint16 position, uint16 mode);
uint8   Rpi_miso_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Rpi_miso_SetDriveMode() function.
     *  @{
     */
        #define Rpi_miso_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Rpi_miso_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Rpi_miso_DM_RES_UP          PIN_DM_RES_UP
        #define Rpi_miso_DM_RES_DWN         PIN_DM_RES_DWN
        #define Rpi_miso_DM_OD_LO           PIN_DM_OD_LO
        #define Rpi_miso_DM_OD_HI           PIN_DM_OD_HI
        #define Rpi_miso_DM_STRONG          PIN_DM_STRONG
        #define Rpi_miso_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Rpi_miso_MASK               Rpi_miso__MASK
#define Rpi_miso_SHIFT              Rpi_miso__SHIFT
#define Rpi_miso_WIDTH              1u

/* Interrupt constants */
#if defined(Rpi_miso__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Rpi_miso_SetInterruptMode() function.
     *  @{
     */
        #define Rpi_miso_INTR_NONE      (uint16)(0x0000u)
        #define Rpi_miso_INTR_RISING    (uint16)(0x0001u)
        #define Rpi_miso_INTR_FALLING   (uint16)(0x0002u)
        #define Rpi_miso_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Rpi_miso_INTR_MASK      (0x01u) 
#endif /* (Rpi_miso__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Rpi_miso_PS                     (* (reg8 *) Rpi_miso__PS)
/* Data Register */
#define Rpi_miso_DR                     (* (reg8 *) Rpi_miso__DR)
/* Port Number */
#define Rpi_miso_PRT_NUM                (* (reg8 *) Rpi_miso__PRT) 
/* Connect to Analog Globals */                                                  
#define Rpi_miso_AG                     (* (reg8 *) Rpi_miso__AG)                       
/* Analog MUX bux enable */
#define Rpi_miso_AMUX                   (* (reg8 *) Rpi_miso__AMUX) 
/* Bidirectional Enable */                                                        
#define Rpi_miso_BIE                    (* (reg8 *) Rpi_miso__BIE)
/* Bit-mask for Aliased Register Access */
#define Rpi_miso_BIT_MASK               (* (reg8 *) Rpi_miso__BIT_MASK)
/* Bypass Enable */
#define Rpi_miso_BYP                    (* (reg8 *) Rpi_miso__BYP)
/* Port wide control signals */                                                   
#define Rpi_miso_CTL                    (* (reg8 *) Rpi_miso__CTL)
/* Drive Modes */
#define Rpi_miso_DM0                    (* (reg8 *) Rpi_miso__DM0) 
#define Rpi_miso_DM1                    (* (reg8 *) Rpi_miso__DM1)
#define Rpi_miso_DM2                    (* (reg8 *) Rpi_miso__DM2) 
/* Input Buffer Disable Override */
#define Rpi_miso_INP_DIS                (* (reg8 *) Rpi_miso__INP_DIS)
/* LCD Common or Segment Drive */
#define Rpi_miso_LCD_COM_SEG            (* (reg8 *) Rpi_miso__LCD_COM_SEG)
/* Enable Segment LCD */
#define Rpi_miso_LCD_EN                 (* (reg8 *) Rpi_miso__LCD_EN)
/* Slew Rate Control */
#define Rpi_miso_SLW                    (* (reg8 *) Rpi_miso__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Rpi_miso_PRTDSI__CAPS_SEL       (* (reg8 *) Rpi_miso__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Rpi_miso_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Rpi_miso__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Rpi_miso_PRTDSI__OE_SEL0        (* (reg8 *) Rpi_miso__PRTDSI__OE_SEL0) 
#define Rpi_miso_PRTDSI__OE_SEL1        (* (reg8 *) Rpi_miso__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Rpi_miso_PRTDSI__OUT_SEL0       (* (reg8 *) Rpi_miso__PRTDSI__OUT_SEL0) 
#define Rpi_miso_PRTDSI__OUT_SEL1       (* (reg8 *) Rpi_miso__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Rpi_miso_PRTDSI__SYNC_OUT       (* (reg8 *) Rpi_miso__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Rpi_miso__SIO_CFG)
    #define Rpi_miso_SIO_HYST_EN        (* (reg8 *) Rpi_miso__SIO_HYST_EN)
    #define Rpi_miso_SIO_REG_HIFREQ     (* (reg8 *) Rpi_miso__SIO_REG_HIFREQ)
    #define Rpi_miso_SIO_CFG            (* (reg8 *) Rpi_miso__SIO_CFG)
    #define Rpi_miso_SIO_DIFF           (* (reg8 *) Rpi_miso__SIO_DIFF)
#endif /* (Rpi_miso__SIO_CFG) */

/* Interrupt Registers */
#if defined(Rpi_miso__INTSTAT)
    #define Rpi_miso_INTSTAT            (* (reg8 *) Rpi_miso__INTSTAT)
    #define Rpi_miso_SNAP               (* (reg8 *) Rpi_miso__SNAP)
    
	#define Rpi_miso_0_INTTYPE_REG 		(* (reg8 *) Rpi_miso__0__INTTYPE)
#endif /* (Rpi_miso__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Rpi_miso_H */


/* [] END OF FILE */
