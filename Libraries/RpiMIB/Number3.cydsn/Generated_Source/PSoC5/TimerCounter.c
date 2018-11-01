/*******************************************************************************
* File Name: TimerCounter.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "TimerCounter.h"

uint8 TimerCounter_initVar = 0u;


/*******************************************************************************
* Function Name: TimerCounter_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void TimerCounter_Init(void) 
{
        #if (!TimerCounter_UsingFixedFunction && !TimerCounter_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!TimerCounter_UsingFixedFunction && !TimerCounter_ControlRegRemoved) */
        
        #if(!TimerCounter_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 TimerCounter_interruptState;
        #endif /* (!TimerCounter_UsingFixedFunction) */
        
        #if (TimerCounter_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            TimerCounter_CONTROL &= TimerCounter_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                TimerCounter_CONTROL2 &= ((uint8)(~TimerCounter_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                TimerCounter_CONTROL3 &= ((uint8)(~TimerCounter_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (TimerCounter_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                TimerCounter_CONTROL |= TimerCounter_ONESHOT;
            #endif /* (TimerCounter_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            TimerCounter_CONTROL2 |= TimerCounter_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            TimerCounter_RT1 &= ((uint8)(~TimerCounter_RT1_MASK));
            TimerCounter_RT1 |= TimerCounter_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            TimerCounter_RT1 &= ((uint8)(~TimerCounter_SYNCDSI_MASK));
            TimerCounter_RT1 |= TimerCounter_SYNCDSI_EN;

        #else
            #if(!TimerCounter_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = TimerCounter_CONTROL & ((uint8)(~TimerCounter_CTRL_CMPMODE_MASK));
            TimerCounter_CONTROL = ctrl | TimerCounter_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = TimerCounter_CONTROL & ((uint8)(~TimerCounter_CTRL_CAPMODE_MASK));
            
            #if( 0 != TimerCounter_CAPTURE_MODE_CONF)
                TimerCounter_CONTROL = ctrl | TimerCounter_DEFAULT_CAPTURE_MODE;
            #else
                TimerCounter_CONTROL = ctrl;
            #endif /* 0 != TimerCounter_CAPTURE_MODE */ 
            
            #endif /* (!TimerCounter_ControlRegRemoved) */
        #endif /* (TimerCounter_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!TimerCounter_UsingFixedFunction)
            TimerCounter_ClearFIFO();
        #endif /* (!TimerCounter_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        TimerCounter_WritePeriod(TimerCounter_INIT_PERIOD_VALUE);
        #if (!(TimerCounter_UsingFixedFunction && (CY_PSOC5A)))
            TimerCounter_WriteCounter(TimerCounter_INIT_COUNTER_VALUE);
        #endif /* (!(TimerCounter_UsingFixedFunction && (CY_PSOC5A))) */
        TimerCounter_SetInterruptMode(TimerCounter_INIT_INTERRUPTS_MASK);
        
        #if (!TimerCounter_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)TimerCounter_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            TimerCounter_WriteCompare(TimerCounter_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            TimerCounter_interruptState = CyEnterCriticalSection();
            
            TimerCounter_STATUS_AUX_CTRL |= TimerCounter_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(TimerCounter_interruptState);
            
        #endif /* (!TimerCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: TimerCounter_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void TimerCounter_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (TimerCounter_UsingFixedFunction)
        TimerCounter_GLOBAL_ENABLE |= TimerCounter_BLOCK_EN_MASK;
        TimerCounter_GLOBAL_STBY_ENABLE |= TimerCounter_BLOCK_STBY_EN_MASK;
    #endif /* (TimerCounter_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!TimerCounter_ControlRegRemoved || TimerCounter_UsingFixedFunction)
        TimerCounter_CONTROL |= TimerCounter_CTRL_ENABLE;                
    #endif /* (!TimerCounter_ControlRegRemoved || TimerCounter_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: TimerCounter_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  TimerCounter_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void TimerCounter_Start(void) 
{
    if(TimerCounter_initVar == 0u)
    {
        TimerCounter_Init();
        
        TimerCounter_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    TimerCounter_Enable();        
}


/*******************************************************************************
* Function Name: TimerCounter_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void TimerCounter_Stop(void) 
{
    /* Disable Counter */
    #if(!TimerCounter_ControlRegRemoved || TimerCounter_UsingFixedFunction)
        TimerCounter_CONTROL &= ((uint8)(~TimerCounter_CTRL_ENABLE));        
    #endif /* (!TimerCounter_ControlRegRemoved || TimerCounter_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (TimerCounter_UsingFixedFunction)
        TimerCounter_GLOBAL_ENABLE &= ((uint8)(~TimerCounter_BLOCK_EN_MASK));
        TimerCounter_GLOBAL_STBY_ENABLE &= ((uint8)(~TimerCounter_BLOCK_STBY_EN_MASK));
    #endif /* (TimerCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: TimerCounter_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void TimerCounter_SetInterruptMode(uint8 interruptsMask) 
{
    TimerCounter_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: TimerCounter_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   TimerCounter_ReadStatusRegister(void) 
{
    return TimerCounter_STATUS;
}


#if(!TimerCounter_ControlRegRemoved)
/*******************************************************************************
* Function Name: TimerCounter_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   TimerCounter_ReadControlRegister(void) 
{
    return TimerCounter_CONTROL;
}


/*******************************************************************************
* Function Name: TimerCounter_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    TimerCounter_WriteControlRegister(uint8 control) 
{
    TimerCounter_CONTROL = control;
}

#endif  /* (!TimerCounter_ControlRegRemoved) */


#if (!(TimerCounter_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: TimerCounter_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void TimerCounter_WriteCounter(uint16 counter) \
                                   
{
    #if(TimerCounter_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (TimerCounter_GLOBAL_ENABLE & TimerCounter_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        TimerCounter_GLOBAL_ENABLE |= TimerCounter_BLOCK_EN_MASK;
        CY_SET_REG16(TimerCounter_COUNTER_LSB_PTR, (uint16)counter);
        TimerCounter_GLOBAL_ENABLE &= ((uint8)(~TimerCounter_BLOCK_EN_MASK));
    #else
        CY_SET_REG16(TimerCounter_COUNTER_LSB_PTR, counter);
    #endif /* (TimerCounter_UsingFixedFunction) */
}
#endif /* (!(TimerCounter_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: TimerCounter_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) The present value of the counter.
*
*******************************************************************************/
uint16 TimerCounter_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(TimerCounter_UsingFixedFunction)
		(void)CY_GET_REG16(TimerCounter_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(TimerCounter_COUNTER_LSB_PTR_8BIT);
	#endif/* (TimerCounter_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(TimerCounter_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(TimerCounter_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(TimerCounter_STATICCOUNT_LSB_PTR));
    #endif /* (TimerCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: TimerCounter_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint16) Present Capture value.
*
*******************************************************************************/
uint16 TimerCounter_ReadCapture(void) 
{
    #if(TimerCounter_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(TimerCounter_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(TimerCounter_STATICCOUNT_LSB_PTR));
    #endif /* (TimerCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: TimerCounter_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint16) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void TimerCounter_WritePeriod(uint16 period) 
{
    #if(TimerCounter_UsingFixedFunction)
        CY_SET_REG16(TimerCounter_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG16(TimerCounter_PERIOD_LSB_PTR, period);
    #endif /* (TimerCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: TimerCounter_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) Present period value.
*
*******************************************************************************/
uint16 TimerCounter_ReadPeriod(void) 
{
    #if(TimerCounter_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(TimerCounter_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(TimerCounter_PERIOD_LSB_PTR));
    #endif /* (TimerCounter_UsingFixedFunction) */
}


#if (!TimerCounter_UsingFixedFunction)
/*******************************************************************************
* Function Name: TimerCounter_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void TimerCounter_WriteCompare(uint16 compare) \
                                   
{
    #if(TimerCounter_UsingFixedFunction)
        CY_SET_REG16(TimerCounter_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(TimerCounter_COMPARE_LSB_PTR, compare);
    #endif /* (TimerCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: TimerCounter_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint16) Present compare value.
*
*******************************************************************************/
uint16 TimerCounter_ReadCompare(void) 
{
    return (CY_GET_REG16(TimerCounter_COMPARE_LSB_PTR));
}


#if (TimerCounter_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: TimerCounter_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void TimerCounter_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    TimerCounter_CONTROL &= ((uint8)(~TimerCounter_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    TimerCounter_CONTROL |= compareMode;
}
#endif  /* (TimerCounter_COMPARE_MODE_SOFTWARE) */


#if (TimerCounter_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: TimerCounter_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void TimerCounter_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    TimerCounter_CONTROL &= ((uint8)(~TimerCounter_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    TimerCounter_CONTROL |= ((uint8)((uint8)captureMode << TimerCounter_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (TimerCounter_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: TimerCounter_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void TimerCounter_ClearFIFO(void) 
{

    while(0u != (TimerCounter_ReadStatusRegister() & TimerCounter_STATUS_FIFONEMP))
    {
        (void)TimerCounter_ReadCapture();
    }

}
#endif  /* (!TimerCounter_UsingFixedFunction) */


/* [] END OF FILE */

