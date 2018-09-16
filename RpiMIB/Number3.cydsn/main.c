/*******************************************************************************
* File Name: main.c
*
* Version: 1.10
*
* Description:
*  This is source code for example project of the SPI Master component.
*  Parameters used:
*   Mode                CPHA == 0, CPOL == 0                
*   Data lines          MOSI+MISO
*   Shift direction     MSB First
*   DataBits:           8 
*   Bit Rate            1 Mbps
*   Clock source        External 
*
*  SPI communication test using DMA. 8 bytes are transmitted
*  between SPI Master and SPI Slave.
*  Received data are displayed on LCD. 
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/
#include <project.h>


uint16 WriteSignalGen(uint8, uint16);
uint16 ReadEncoderValue(uint8);
uint16  RPi_Command;
uint16  RPi_Data;
uint16 enc_a_Position;
uint16 enc_b_Position;
uint16 enc_c_Position;
uint16 pwm_a_command;
uint16 pwm_b_command;
uint16 pwm_a_new_command;
uint16 pwm_b_new_command;

#define idle_state            ((uint8) (0x00u))
#define read_encoder_state    ((uint8) (0x01u))
#define write_funcGen1_state  ((uint8) (0x02u))
#define write_funcGen2_state  ((uint8) (0x03u))
#define write_Amp_state       ((uint8) (0x04u))
#define write_pwm_a_state     ((uint8) (0x05u))
#define write_pwm_b_state     ((uint8) (0x06u))


uint8 read_counter;
uint8 PSOC_state = idle_state;
uint8 i2cAddress;
uint8 i2cData;

CY_ISR(SS_Fall_Handler)
{
    /*  load the encoder position data into the transmit data registers*/
    isr_SS_Fall_ClearPending();
    if (PSOC_state == idle_state) {
        SPIS_WriteTxDataZero(0x0001);
    } else if (PSOC_state == write_funcGen1_state) {
        SPIS_WriteTxDataZero(0x0020);
    } else if (PSOC_state == write_funcGen2_state) {
        SPIS_WriteTxDataZero(0x0040);
    }  else if (PSOC_state == write_Amp_state) {
        SPIS_WriteTxDataZero(0x0080);
    }    else if (PSOC_state == write_pwm_a_state) {
        SPIS_WriteTxDataZero(0x0100);
    } else if (PSOC_state == write_pwm_b_state) {
        SPIS_WriteTxDataZero(0x0200);
   }
}

CY_ISR(SS_Rise_Handler)
{
    if (PSOC_state == idle_state) {
        RPi_Command = SPIS_ReadRxData();
        read_counter = 0u;
    } else {
        RPi_Data = SPIS_ReadRxData();
    }
    
    /* Routine to write to sig gen over SPI or Power Amp Gain over I2C */
    
    if (PSOC_state == idle_state) {
        if (RPi_Command == 0x0010) {          
           PSOC_state = read_encoder_state;
           SPIS_WriteTxDataZero(enc_a_Position);
           SPIS_WriteTxData(enc_b_Position);
           SPIS_WriteTxData(enc_c_Position);
           read_counter = 0u; 
        } else if (RPi_Command == 0x0020) {
           PSOC_state = write_funcGen1_state;
        } else if (RPi_Command == 0x0040) {
           PSOC_state = write_funcGen2_state;
        }  else if (RPi_Command == 0x0080) {
           PSOC_state = write_Amp_state;
        }  else if (RPi_Command == 0x0100) {
           PSOC_state = write_pwm_a_state;
        }  else if (RPi_Command == 0x0200) {
           PSOC_state = write_pwm_b_state;
        }
    } else  if  ( PSOC_state == read_encoder_state) {      
        if (read_counter < 2u) {
            read_counter +=1;
        } else {
            PSOC_state = idle_state;
            read_counter = 0u;
        }
    } else if ( PSOC_state == write_funcGen1_state) {
        WriteSignalGen(0u, RPi_Data); 
        PSOC_state = idle_state;
    } else if ( PSOC_state == write_funcGen2_state) {
        WriteSignalGen(1u, RPi_Data); 
        PSOC_state = idle_state;
    } else if ( PSOC_state == write_Amp_state) {
        i2cAddress = ((uint8) (RPi_Data >> 8));
        i2cData = ((uint8) (RPi_Data & 0x00ff));
        I2C_1_MasterSendStart(i2cAddress, 0);
        I2C_1_MasterWriteByte(i2cData);
        I2C_1_MasterSendStop();
        PSOC_state = idle_state;       
     } else if ( PSOC_state == write_pwm_a_state) {
        pwm_a_new_command = RPi_Data;
        /* PWM_1_WriteCompare(pwm_a_command);  */
        PSOC_state = idle_state;  
    } else if ( PSOC_state == write_pwm_b_state) {
        pwm_b_new_command = RPi_Data;
        /* PWM_2_WriteCompare(pwm_b_command);   */
        PSOC_state = idle_state;         
    } else {
        PSOC_state = idle_state;
    }

    SPIS_ReadRxStatus();
    SPIS_ClearRxBuffer();
    isr_SS_Rise_ClearPending();
}

/* The txBuffer size is equal (BUFFER_SIZE-1) because for SPI Mode where CPHA == 0 and
* CPOL == 0 one byte writes directly in SPI TX FIFO using SPIS_WriteTxDataZero() API.
*/

uint16 rxBuffer[4];
uint8 temp1;
uint8 temp2;
uint8 i;
uint16 shutdown_count;

/*******************************************************************************
* Function Name: main
********************************************************************************
*******************************************************************************/
int main()
{
    Comp_1_Start();
    CyDelay(2000u);
    /* Enable Battery Backup circuit and interface circuits between RPi and PSOC  */
    EnableBattery_Write(1u);
    Control_Reg_SS_Write(0u);
    Control_Reg_LED_Write(0u);
    RpiInterrupts_Write(3u);     
    Clock_1_Start();
 
    SPIM_1_Start();
    SPIM_1_ClearFIFO();
    SPIM_1_ClearRxBuffer();
    SPIM_1_ClearTxBuffer();   
    
    SPIM_SigGen_Start();
    SPIM_SigGen_ClearFIFO();
    SPIM_SigGen_ClearRxBuffer();
    SPIM_SigGen_ClearTxBuffer();    

    SPIS_Start();
    SPIS_WriteTxDataZero(0x00u);
 
    PWM_1_Start();
    PWM_2_Start();
    
    I2C_1_Start();   
    
    PSOC_state = idle_state;
     read_counter = 0u;
      
    CyGlobalIntEnable; 
    isr_SS_Fall_StartEx(SS_Fall_Handler);
    isr_SS_Rise_StartEx(SS_Rise_Handler);
 
    RPi_Command = 0x000f;
  
    shutdown_count = 0;

    while (1) {
        /* read the encoder values  */     
        enc_a_Position = ReadEncoderValue(0u);    
        enc_b_Position = ReadEncoderValue(1u);        
        enc_c_Position = ReadEncoderValue(2u);
      
        /* This code monitors the main power input.  A local backup batter supply prevents  */
        /* power from being removed from the raspberry pi before it has been properly shutdown   */
        /* Monitor the presence of the main power input */    
        /*  If power has been removed for more than 5000 times through this loop -  -  about 20 seconds */
        /*  Interrupt the Raspberry Pi telling it to shut itself down  */
        /*  allow 20 sec for the Pi to shut down then turn off back up power. */
        CyDelayUs(1400u);

        /* implenemt slew rate for changes in servo position*/
        if (pwm_a_new_command > pwm_a_command) {
            if ((pwm_a_new_command - pwm_a_command) > 50) {
                pwm_a_command +=50;
            } else {
                pwm_a_command = pwm_a_new_command;
            }
        } else {
            if ((pwm_a_command - pwm_a_new_command) > 50)  {
                pwm_a_command -=50;
            } else {
                pwm_a_command = pwm_a_new_command;
            }
        }

        if (pwm_b_new_command > pwm_b_command) {
            if ((pwm_b_new_command - pwm_b_command) > 50) {
                pwm_b_command +=50;
            } else {
                pwm_b_command = pwm_b_new_command;
            }
        } else {
            if ((pwm_b_command - pwm_b_new_command) > 50)  {
                pwm_b_command -=50;
            } else {
                 pwm_b_command = pwm_b_new_command;
            }
        }
    
        PWM_1_WriteCompare(pwm_a_command);
        PWM_2_WriteCompare(pwm_b_command);
    
        if (Status_Reg_1_Read() == 1u) {
            shutdown_count += 1;
            if (shutdown_count == 2000u) {      
                CyGlobalIntDisable; 
                Control_Reg_LED_Write(1u);
                /* tell Pi to shut down */ 
                RpiInterrupts_Write(0u);
                CyDelay(20000u);
                /* Wait 60 seconds then turn off back up power */
                EnableBattery_Write(2u);
                CyDelay(2000u);
            }
        } else {
            shutdown_count = 0u;
        }
    }
}

uint16 WriteSignalGen(uint8 ChannelNumber, uint16 CommandWord){
    uint16 result;
    Control_Reg_SS_SigGen_Write(ChannelNumber);
    SPIM_SigGen_ClearFIFO();
    SPIM_SigGen_WriteTxData(CommandWord);
    while (!(SPIM_SigGen_STS_SPI_DONE));
    result = 0u;
    return(result);
}


uint16 ReadEncoderValue(uint8 encoderNumber)
{
    uint16 result;
    uint8 ii;
       
      Control_Reg_SS_Write(encoderNumber);
      SPIM_1_ClearFIFO();
      SPIM_1_WriteTxData(0x10);       
      /*  wait for transmit of first data is finished  */
      while(!(SPIM_1_ReadTxStatus() & SPIM_1_STS_SPI_DONE));   
      CyDelayUs(20u);
      ii=0;
      while ((SPIM_1_ReadByte() != 0x10) & (ii<6)) {
          CyDelayUs(20u);
          SPIM_1_WriteTxData(0x00);  
          while(!(SPIM_1_ReadTxStatus() & SPIM_1_STS_SPI_DONE));
          ii+=1;
      }  
     /*  if ii > 6  means encoder did not respond -- possibly not hooked up*/
      if (ii<6) {
         CyDelayUs(20u);
         SPIM_1_WriteTxData(0x00);  
         while(!(SPIM_1_ReadTxStatus() & SPIM_1_STS_SPI_DONE));
         result = SPIM_1_ReadByte()*256;    
         CyDelayUs(20u);
         SPIM_1_WriteTxData(0x00);  
         while(!(SPIM_1_ReadTxStatus() & SPIM_1_STS_SPI_DONE));
         result += SPIM_1_ReadByte();          
         CyDelayUs(40u);
      } else {
         /*  note encoder word is 12 bits long.  0xF000 represents an invalid code  */
         result = 0xF000;
        CyDelayUs(40u);
      }    
    return(result);
}

/* [] END OF FILE */
