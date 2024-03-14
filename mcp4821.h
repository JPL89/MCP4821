// @File		MCP4821.H		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		BRAZIL
// @Date		14/03/24
//
//
// Copyright (C) 2024 JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//

#ifndef MCP4821_H
#define MCP4821_H

#define MCP4821_CLK PORTCbits.RC0
#define MCP4821_DIN PORTCbits.RC1
#define MCP4821_DOUT PORTCbits.RC2
#define MCP4821_CS PORTCbits.RC3

#define MCP4821_CLK_TRIS TRISCbits.RC0
#define MCP4821_DIN_TRIS TRISCbits.RC1
#define MCP4821_DOUT_TRIS TRISCbits.RC2
#define MCP4821_CS_TRIS TRISCbits.RC3 

static const void SPI_transfer(unsigned int data)
{     
    for(unsigned int mask = 0x8000; mask; mask >>= 1)
    {
        if(data & mask) MCP4821_DIN = 1; else MCP4821_DIN = 0;
            
         __asm__ __volatile__("nop");
         MCP4821_CLK = 1;
         __asm__ __volatile__("nop");
         MCP4821_CLK = 0;
         __asm__ __volatile__("nop");    
    }
}

void MCP4821_Write(unsigned int data)
{
    data |= (1 << 12); // SHDN
    
    MCP4821_CS = 0;
    SPI_transfer(data);
    MCP4821_CS = 1;   
}

void MCP4821_Init(void)
{
    MCP4821_CLK_TRIS = 0;
    MCP4821_DIN_TRIS = 0;
    MCP4821_DOUT_TRIS = 1;
    MCP4821_CS_TRIS = 0;
    
    MCP4821_CS = 1;
}

#endif 
