/*******************************************************************************
* File Name: .h
* Version 2.50
*
* Description:
*  This private header file contains internal definitions for the SPIM
*  component. Do not use these definitions directly in your application.
*
* Note:
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SPIM_PVT_SPIM_SigGen_H)
#define CY_SPIM_PVT_SPIM_SigGen_H

#include "SPIM_SigGen.h"


/**********************************
*   Functions with external linkage
**********************************/


/**********************************
*   Variables with external linkage
**********************************/

extern volatile uint8 SPIM_SigGen_swStatusTx;
extern volatile uint8 SPIM_SigGen_swStatusRx;

#if(SPIM_SigGen_TX_SOFTWARE_BUF_ENABLED)
    extern volatile uint16 SPIM_SigGen_txBuffer[SPIM_SigGen_TX_BUFFER_SIZE];
    extern volatile uint8 SPIM_SigGen_txBufferRead;
    extern volatile uint8 SPIM_SigGen_txBufferWrite;
    extern volatile uint8 SPIM_SigGen_txBufferFull;
#endif /* (SPIM_SigGen_TX_SOFTWARE_BUF_ENABLED) */

#if(SPIM_SigGen_RX_SOFTWARE_BUF_ENABLED)
    extern volatile uint16 SPIM_SigGen_rxBuffer[SPIM_SigGen_RX_BUFFER_SIZE];
    extern volatile uint8 SPIM_SigGen_rxBufferRead;
    extern volatile uint8 SPIM_SigGen_rxBufferWrite;
    extern volatile uint8 SPIM_SigGen_rxBufferFull;
#endif /* (SPIM_SigGen_RX_SOFTWARE_BUF_ENABLED) */

#endif /* CY_SPIM_PVT_SPIM_SigGen_H */


/* [] END OF FILE */
