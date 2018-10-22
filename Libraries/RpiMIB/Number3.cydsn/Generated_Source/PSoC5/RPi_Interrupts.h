/*******************************************************************************
* File Name: RPi_Interrupts.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_RPi_Interrupts_H) /* CY_CONTROL_REG_RPi_Interrupts_H */
#define CY_CONTROL_REG_RPi_Interrupts_H

#include "cyfitter.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
     (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
     (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} RPi_Interrupts_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    RPi_Interrupts_Write(uint8 control) ;
uint8   RPi_Interrupts_Read(void) ;

void RPi_Interrupts_SaveConfig(void) ;
void RPi_Interrupts_RestoreConfig(void) ;
void RPi_Interrupts_Sleep(void) ; 
void RPi_Interrupts_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define RPi_Interrupts_Control        (* (reg8 *) RPi_Interrupts_Sync_ctrl_reg__CONTROL_REG )
#define RPi_Interrupts_Control_PTR    (  (reg8 *) RPi_Interrupts_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_RPi_Interrupts_H */


/* [] END OF FILE */
