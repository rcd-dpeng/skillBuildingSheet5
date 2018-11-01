/*******************************************************************************
* File Name: Rpi_mosi.h  
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

#if !defined(CY_PINS_Rpi_mosi_H) /* Pins Rpi_mosi_H */
#define CY_PINS_Rpi_mosi_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Rpi_mosi_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Rpi_mosi__PORT == 15 && ((Rpi_mosi__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Rpi_mosi_Write(uint8 value);
void    Rpi_mosi_SetDriveMode(uint8 mode);
uint8   Rpi_mosi_ReadDataReg(void);
uint8   Rpi_mosi_Read(void);
void    Rpi_mosi_SetInterruptMode(uint16 position, uint16 mode);
uint8   Rpi_mosi_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Rpi_mosi_SetDriveMode() function.
     *  @{
     */
        #define Rpi_mosi_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Rpi_mosi_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Rpi_mosi_DM_RES_UP          PIN_DM_RES_UP
        #define Rpi_mosi_DM_RES_DWN         PIN_DM_RES_DWN
        #define Rpi_mosi_DM_OD_LO           PIN_DM_OD_LO
        #define Rpi_mosi_DM_OD_HI           PIN_DM_OD_HI
        #define Rpi_mosi_DM_STRONG          PIN_DM_STRONG
        #define Rpi_mosi_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Rpi_mosi_MASK               Rpi_mosi__MASK
#define Rpi_mosi_SHIFT              Rpi_mosi__SHIFT
#define Rpi_mosi_WIDTH              1u

/* Interrupt constants */
#if defined(Rpi_mosi__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Rpi_mosi_SetInterruptMode() function.
     *  @{
     */
        #define Rpi_mosi_INTR_NONE      (uint16)(0x0000u)
        #define Rpi_mosi_INTR_RISING    (uint16)(0x0001u)
        #define Rpi_mosi_INTR_FALLING   (uint16)(0x0002u)
        #define Rpi_mosi_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Rpi_mosi_INTR_MASK      (0x01u) 
#endif /* (Rpi_mosi__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Rpi_mosi_PS                     (* (reg8 *) Rpi_mosi__PS)
/* Data Register */
#define Rpi_mosi_DR                     (* (reg8 *) Rpi_mosi__DR)
/* Port Number */
#define Rpi_mosi_PRT_NUM                (* (reg8 *) Rpi_mosi__PRT) 
/* Connect to Analog Globals */                                                  
#define Rpi_mosi_AG                     (* (reg8 *) Rpi_mosi__AG)                       
/* Analog MUX bux enable */
#define Rpi_mosi_AMUX                   (* (reg8 *) Rpi_mosi__AMUX) 
/* Bidirectional Enable */                                                        
#define Rpi_mosi_BIE                    (* (reg8 *) Rpi_mosi__BIE)
/* Bit-mask for Aliased Register Access */
#define Rpi_mosi_BIT_MASK               (* (reg8 *) Rpi_mosi__BIT_MASK)
/* Bypass Enable */
#define Rpi_mosi_BYP                    (* (reg8 *) Rpi_mosi__BYP)
/* Port wide control signals */                                                   
#define Rpi_mosi_CTL                    (* (reg8 *) Rpi_mosi__CTL)
/* Drive Modes */
#define Rpi_mosi_DM0                    (* (reg8 *) Rpi_mosi__DM0) 
#define Rpi_mosi_DM1                    (* (reg8 *) Rpi_mosi__DM1)
#define Rpi_mosi_DM2                    (* (reg8 *) Rpi_mosi__DM2) 
/* Input Buffer Disable Override */
#define Rpi_mosi_INP_DIS                (* (reg8 *) Rpi_mosi__INP_DIS)
/* LCD Common or Segment Drive */
#define Rpi_mosi_LCD_COM_SEG            (* (reg8 *) Rpi_mosi__LCD_COM_SEG)
/* Enable Segment LCD */
#define Rpi_mosi_LCD_EN                 (* (reg8 *) Rpi_mosi__LCD_EN)
/* Slew Rate Control */
#define Rpi_mosi_SLW                    (* (reg8 *) Rpi_mosi__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Rpi_mosi_PRTDSI__CAPS_SEL       (* (reg8 *) Rpi_mosi__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Rpi_mosi_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Rpi_mosi__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Rpi_mosi_PRTDSI__OE_SEL0        (* (reg8 *) Rpi_mosi__PRTDSI__OE_SEL0) 
#define Rpi_mosi_PRTDSI__OE_SEL1        (* (reg8 *) Rpi_mosi__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Rpi_mosi_PRTDSI__OUT_SEL0       (* (reg8 *) Rpi_mosi__PRTDSI__OUT_SEL0) 
#define Rpi_mosi_PRTDSI__OUT_SEL1       (* (reg8 *) Rpi_mosi__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Rpi_mosi_PRTDSI__SYNC_OUT       (* (reg8 *) Rpi_mosi__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Rpi_mosi__SIO_CFG)
    #define Rpi_mosi_SIO_HYST_EN        (* (reg8 *) Rpi_mosi__SIO_HYST_EN)
    #define Rpi_mosi_SIO_REG_HIFREQ     (* (reg8 *) Rpi_mosi__SIO_REG_HIFREQ)
    #define Rpi_mosi_SIO_CFG            (* (reg8 *) Rpi_mosi__SIO_CFG)
    #define Rpi_mosi_SIO_DIFF           (* (reg8 *) Rpi_mosi__SIO_DIFF)
#endif /* (Rpi_mosi__SIO_CFG) */

/* Interrupt Registers */
#if defined(Rpi_mosi__INTSTAT)
    #define Rpi_mosi_INTSTAT            (* (reg8 *) Rpi_mosi__INTSTAT)
    #define Rpi_mosi_SNAP               (* (reg8 *) Rpi_mosi__SNAP)
    
	#define Rpi_mosi_0_INTTYPE_REG 		(* (reg8 *) Rpi_mosi__0__INTTYPE)
#endif /* (Rpi_mosi__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Rpi_mosi_H */


/* [] END OF FILE */
