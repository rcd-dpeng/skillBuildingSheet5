/*******************************************************************************
* File Name: main.c
*
* Version: 1.10
*
* Description:
*  This is source code for forwarding data to and from the Raspberry Pi through the Cyprus, and monitoring battery connection.
*  Parameters used:
*   Mode                CPHA == 0, CPOL == 0                
*   Data lines          MOSI+MISO
*   Shift direction     MSB First
*   DataBits:           8 
*   Bit Rate            1 Mbps
*   Clock source        External  
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLI                                         ERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/
#include <project.h>

typedef enum {
    idle_state,
    listening_state,
    execution_state,
} state;

typedef enum {
    no_command,
    read_gpio,
    write_gpio,
    read_spi,
    write_spi,
    write_pwm,
    read_i2c,
    write_i2c,
    add_i2c_data,
    add_i2c_address,
    set_spi_trigger,
    read_encoder,
    set_trigger_radius,
    set_pinmode,
    write_firmware_date,
    read_firmware_date
} command;

uint16 ReadWriteSPIM1(uint8, uint8);
uint16 ReadWriteSPIM2(uint8, uint16);
uint16 ReadEncoder(uint8, uint8);
int abs(int x);
command InterpretCommand(uint16);
uint16 RPi_Command_Data;
uint16 RPi_Data;
uint8 i2c_address = 0;
uint8 i2c_data_to_write[8];
uint8 i2c_byte_count = 0;
uint16 spi_trigger_value[] = {0x800,0x800,0x800,0x800};
uint16 spi_trigger_radius[] = {25,25,25,25};
uint16 COMMAND_MASK = 0xFF00;
uint16 PORT_MASK = 0x00F0;
uint16 PARAMETER_MASK = 0x00F0;
uint16 CHANNEL_MASK = 0x000F;
uint16 DATA_MASK = 0x00F0;
uint8 READ_ENCODER = 0x10;
uint8 ENCODER_IDLE = 0xA5;
uint8 GPIO_MODE = 0;
uint8 TRIGGER_MODE = 1;
uint8 pinmode;
uint16 firmware_date[] = {13, 3, 2019};
uint16 ORDINAL_MASK = 0x000F;

state PSOC_state;
command RPi_Command;

CY_ISR(SS_Rise_Handler) {
    if (PSOC_state == idle_state) {
        RPi_Command_Data = SPIS_ReadRxData();
        RPi_Command = InterpretCommand(RPi_Command_Data);
        SPIS_ClearRxBuffer();
        if((RPi_Command == write_gpio) || (RPi_Command == write_spi) || (RPi_Command == write_pwm) || (RPi_Command == read_i2c) || (RPi_Command == add_i2c_data) || (RPi_Command == add_i2c_address) || (RPi_Command == set_spi_trigger) || (RPi_Command == set_trigger_radius) || (RPi_Command == set_pinmode) || (RPi_Command == write_firmware_date)) {
            PSOC_state = listening_state;
        } else {
            PSOC_state = execution_state;
        }
    } else if (PSOC_state == listening_state) {
        RPi_Data = SPIS_ReadRxData();
        PSOC_state = execution_state;
        SPIS_ClearRxBuffer();
    }
    
    SPIS_ReadRxStatus();
    SPIS_ClearRxBuffer();
    isr_SS_Rise_ClearPending();
}

/* The txBuffer size is equal (BUFFER_SIZE-1) because for SPI Mode where CPHA == 0 and
* CPOL == 0 one byte writes directly in SPI TX FIFO using SPIS_WriteTxDataZero() API.
*/

uint16 rxBuffer [4];
uint8 temp1;
uint8 temp2;
uint8 i;
uint16 shutdown_count;

/*Command Structure: 0x0CPQ --> execute command C with parameters P and Q
 *Some commands take no parameters, and are of the form 0x0C00
 */

command InterpretCommand(uint16 data)
{
    command result = no_command;
    uint16 cmd = (data & COMMAND_MASK);
    
    switch(cmd) {  
        case 0x0100:
            result = read_gpio;
            break;
        case 0x0200:
            result = write_gpio;
            break;        
        case 0x0300:
            result = read_spi;
            break;        
        case 0x0400:
            result = write_spi;
            break;        
        case 0x0500:
            result = write_pwm;
            break;        
        case 0x0600:
            result = read_i2c;
            break;        
        case 0x0700:
            result = write_i2c;
            break;        
        case 0x0800:
            result = add_i2c_data;
            break;        
        case 0x0900:
            result = add_i2c_address;
            break;        
        case 0x0a00:
            result = set_spi_trigger;
            break;
        case 0x0b00:
            result = read_encoder;
            break;
        case 0x0c00:
            result = set_trigger_radius;
            break;
        case 0x0d00:
            result = set_pinmode;
            break;
        case 0x0e00:
            result = write_firmware_date;
            break;
        case 0x0f00:
            result = read_firmware_date;
            break;
        default:
            result = no_command;
            break;
    }
    
    return result;
}

int main() {
    RpiInterrupts_Write(3u);  // 9.25.18 - New location, trying to force the interrupts high as early as possible
    Comp_1_Start();
    CyDelay(2000u);
    
    /* Enable Battery Backup circuit and interface circuits between RPi and PSOC  */
    EnableBattery_Write(1u);
    Control_Reg_SS_1_Write(0u);
    
    //RpiInterrupts_Write(3u);     // 9.25.18 - Original location, moving this to the start of this function
    Clock_1_Start();
 
    SPIM_1_Start();
    SPIM_1_ClearFIFO();
    SPIM_1_ClearRxBuffer();
    SPIM_1_ClearTxBuffer();   
    
    SPIM_2_Start();
    SPIM_2_ClearFIFO();
    SPIM_2_ClearRxBuffer();
    SPIM_2_ClearTxBuffer();    

    SPIS_Start();
    SPIS_WriteTxDataZero(0x00u);
 
    PWM_1_Start();
    PWM_2_Start();
    PWM_1_SetCompareMode(PWM_1__B_PWM__LESS_THAN);
    PWM_2_SetCompareMode(PWM_1__B_PWM__LESS_THAN);
    
    I2C_1_Start();   
    
    PSOC_state = idle_state;
      
    CyGlobalIntEnable; 
    isr_SS_Rise_StartEx( SS_Rise_Handler );
 
    RPi_Command_Data = 0x000f;
    shutdown_count = 0;

    while (1)  { 
        // This code monitors the main power input.  A local backup batter supply prevents
        // power from being removed from the raspberry pi before it has been properly shutdown
        // Monitor the presence of the main power input. If power has been removed for more 
        // than 5000 times through this loop (about 20 seconds), interrupt the Raspberry Pi 
        // telling it to shut itself down allow 20 sec for the Pi to shut down then turn off 
        // back up power.
        CyDelayUs(1400u);   
        if (Status_Reg_1_Read() == 1u) {
            shutdown_count +=1;
            if (shutdown_count == 2000u) {   //9.25.18 - The while loop executes in about 2ms total.
                                             //          2ms * 2000 = 4 seconds, not 20 seconds as described above.
                                             //          Changing to 10000 to get 20 seconds.      
                CyGlobalIntDisable; 
                
                // tell Pi to shut down
                RpiInterrupts_Write(0u);
                CyDelay(20000u);
                
                // Wait 60 seconds then turn off back up power
                EnableBattery_Write(2u);
                CyDelay(2000u);
            }
        } else {
           shutdown_count = 0u;
        }
    
        // Writes correspondign GPIO high if encoder value is within specified range of trigger value
        if (pinmode == TRIGGER_MODE) {
            for (int i = 0; i < 4; i++) {
                int encoderValue;
            
                if (i == 3) {
                    encoderValue = (int)ReadEncoder(2, 0);
                } else {
                    encoderValue = (int)ReadEncoder(1, i);
                }
            
                if (abs(encoderValue - spi_trigger_value[i]) < spi_trigger_radius[i]) {
                    GPIO_Control_Reg_Write(GPIO_Status_Reg_Read() & (0xF-(1 << i)));
                    CyDelayUs(2000);
                    GPIO_Control_Reg_Write(GPIO_Status_Reg_Read() | (1 << i));
                    spi_trigger_value[i] = 0x8000;
                } else {
                    GPIO_Control_Reg_Write(GPIO_Status_Reg_Read() | (1 << i));
                } 
            }
        }
    
        if (PSOC_state == execution_state) {
            switch(RPi_Command) {      
                case read_gpio:
                    SPIS_WriteTxDataZero(GPIO_Status_Reg_Read());
                    break;
                    
                case write_gpio:
                    GPIO_Control_Reg_Write(RPi_Data);
                    break;
                    
                case read_spi:
                    if ((RPi_Command_Data & PORT_MASK) == 0x0010) {
                        SPIS_WriteTxDataZero(ReadWriteSPIM1(RPi_Command_Data & DATA_MASK, 0x0000));
                    } else if ((RPi_Command & PORT_MASK) == 0x0020){
                        SPIS_WriteTxDataZero(ReadWriteSPIM2(RPi_Command_Data & DATA_MASK, 0x0000)); 
                    }
                    break;
                
                case write_spi:
                    if ((RPi_Command_Data & PORT_MASK) == 0x0010) {
                        ReadWriteSPIM1(RPi_Command_Data & DATA_MASK, RPi_Data);
                    } else if ((RPi_Command_Data & PORT_MASK) == 0x0020) {
                        ReadWriteSPIM2(RPi_Command_Data & DATA_MASK, RPi_Data);
                    }
                    break;    
                
                case write_pwm:
                    if ((RPi_Command_Data & PARAMETER_MASK) == 0x0010) {
                        if ((RPi_Command_Data & CHANNEL_MASK) == 0x0000) {
                            PWM_1_SetCompareMode(RPi_Data);
                        } else if ((RPi_Command_Data & CHANNEL_MASK) == 0x0001) {
                            PWM_1_WritePeriod(RPi_Data);
                        } else if ((RPi_Command_Data & CHANNEL_MASK) == 0x0002) {
                            PWM_1_WriteCompare(RPi_Data);
                        }
                    } else if ((RPi_Command_Data & PARAMETER_MASK) == 0x0020) {
                        if ((RPi_Command_Data & CHANNEL_MASK) == 0x0000) {
                            PWM_2_SetCompareMode(RPi_Data);
                        } else if ((RPi_Command_Data & CHANNEL_MASK) == 0x0001) {
                            PWM_2_WritePeriod(RPi_Data);
                        } else if ((RPi_Command_Data & CHANNEL_MASK) == 0x0002) {
                            PWM_2_WriteCompare(RPi_Data);
                        }
                    }
                    break;
                    
                case read_i2c: {
                        uint8 i2c_data_read;
                        if ((RPi_Command_Data & DATA_MASK) == 1) {
                            I2C_1_MasterReadBuf(RPi_Data >> 8, &i2c_data_read, 1, I2C_1_MODE_COMPLETE_XFER);
                            SPIS_WriteTxDataZero(i2c_data_read);
                        } else if ((RPi_Command_Data & DATA_MASK) == 2) {
                            I2C_2_MasterReadBuf(RPi_Data >> 8, &i2c_data_read, 1, I2C_2_MODE_COMPLETE_XFER);
                            SPIS_WriteTxDataZero(i2c_data_read);
                        }  
                    }
                    break;       
                
                case write_i2c:
                    if ((RPi_Command_Data & DATA_MASK) == 1) {
                        I2C_1_MasterWriteBuf(i2c_address, i2c_data_to_write, i2c_byte_count,  I2C_1_MODE_COMPLETE_XFER);
                    } else if ((RPi_Command_Data & DATA_MASK) == 2) {
                        I2C_2_MasterWriteBuf(i2c_address, i2c_data_to_write,  i2c_byte_count + 1,  I2C_2_MODE_COMPLETE_XFER);
                    }
                
                    i2c_byte_count = 0;
                
                    break;     
                
                case add_i2c_data:
                    if (i2c_byte_count < 8) {
                        i2c_data_to_write[i2c_byte_count] = (uint8)(0x00FF & RPi_Data);
                        i2c_byte_count++;
                    }
                    break; 
                
                case add_i2c_address:
                    i2c_address = RPi_Data;
                    break; 
                
                case set_spi_trigger:
                    spi_trigger_value[RPi_Command_Data & CHANNEL_MASK] = RPi_Data;
                    break;
                
                case read_encoder: {
                    uint8 port = (RPi_Command_Data & PORT_MASK) >> 0x4;
                    uint8 channel = RPi_Command_Data & CHANNEL_MASK;
                    uint16 encoder = ReadEncoder(port, channel);
                    SPIS_WriteTxDataZero(encoder);
                    break;
                }
                
                case set_trigger_radius:
                    spi_trigger_radius[RPi_Command_Data & CHANNEL_MASK] = RPi_Data;
                    break;
                    
                case set_pinmode:
                    pinmode = RPi_Data;
                    break;
                    
                case write_firmware_date:
                    firmware_date[RPi_Command_Data & ORDINAL_MASK] = RPi_Data;
                    break;
                
                case read_firmware_date:
                    SPIS_WriteTxDataZero(firmware_date[RPi_Command_Data & ORDINAL_MASK]);
                    break;
                    
                case no_command:
                default:
                    break;
            }
        
            PSOC_state = idle_state;
            SPIS_ClearRxBuffer(); 
        }
    }
}

uint16 ReadWriteSPIM1(uint8 ChannelNumber, uint8 data) {
    Control_Reg_SS_1_Write(ChannelNumber);
    SPIM_1_ClearFIFO();
    SPIM_1_WriteTxData(data);
    
    while(!(SPIM_1_ReadTxStatus() & SPIM_1_STS_SPI_DONE));
    uint16 result = SPIM_1_ReadRxData();
    return(result);
}

uint16 ReadWriteSPIM2(uint8 ChannelNumber, uint16 data) {
    Control_Reg_SS_2_Write(ChannelNumber);
    SPIM_2_ClearFIFO();
    SPIM_2_WriteTxData(data);
    
    while(!(SPIM_2_ReadTxStatus() & SPIM_2_STS_SPI_DONE));
    uint16 result = SPIM_2_ReadRxData();
    return(result);
}

uint16 ReadEncoder(uint8 port, uint8 ChannelNumber) {
    uint16 MSB = 0xff;
    uint16 LSB = 0xff;

    if (port == 0x01) {
        ReadWriteSPIM1(ChannelNumber, READ_ENCODER);
        while (ReadWriteSPIM1(ChannelNumber, 0x00) == ENCODER_IDLE){}
        MSB = ReadWriteSPIM1(ChannelNumber, 0x00);
        CyDelayUs(2000);
        LSB = ReadWriteSPIM1(ChannelNumber, 0x00);
    } else if (port == 0x02) {
        ReadWriteSPIM2(ChannelNumber, READ_ENCODER);
        while (ReadWriteSPIM2(ChannelNumber, 0x00) == ENCODER_IDLE){}
        MSB = ReadWriteSPIM2(ChannelNumber, 0x00);
        CyDelayUs(2000);
        LSB = ReadWriteSPIM2(ChannelNumber, 0x00);
    }
    CyDelayUs(2000);
    return (uint16)(LSB + (MSB << 8));
}

/* QWJvbGlzaCB3YWdliGxhYm9yIG5vdyE= */
/* [] END OF FILE */
