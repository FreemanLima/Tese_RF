
#ifndef _REGISTERS_H
#define _REGISTERS_H

//this file will make life easier by declutering the main .c file
//all CC1101 register adresses are defined here
//maybe some notes about the registers aswell


#define Write 0x00
#define Read 0x80
#define Burst 0x40




#define IOCFG2 0x00
#define IOCFG1 0x01
#define IOCFG0 0x02
#define FIFOTHR 0x03
#define SYNC1 0x04
#define SYNC0 0x05
#define PKTLEN 0x06
#define PKTCTRL1 0x07
#define PKTCTRL0 0x08
#define ADDR 0x09
#define CHANNR 0x0A
#define FSCTRL1 0x0B
#define FSCTRL0 0x0C
#define FREQ2 0x0D
#define FREQ1 0x0E
#define FREQ0 0x0F
#define MDMCFG4 0x10
#define MDMCFG3 0x11
#define MDMCFG2 0x12
#define MDMCFG1 0x13
#define MDMCFG0 0x14
#define DEVIATN 0x15
#define MCSM2 0x16
#define MCSM1 0x17
#define MCSM0 0x18
#define FOCCFG 0x19
#define BSCFG 0x1A
#define AGCCTRL2 0x1B
#define AGCCTRL1 0x1C
#define AGCCTRL0 0x1D
#define WOREVT1 0x1E
#define WOREVT0 0x1F
#define WORCTRL 0x20
#define FREND1 0x21
#define FREND0 0x22
#define FSCAL3 0x23
#define FSCAL2 0x24
#define FSCAL1 0x25
#define FSCAL0 0x26
#define RCCTRL1 0x27
#define RCCTRL0 0x28
#define FSTEST 0x29
#define PTEST 0x2A
#define AGCTEST 0x2B
#define TEST2 0x2C
#define TEST1 0x2D
#define TEST0 0x2E

// from here the burst wont burst, but it will to select command strobes? whatever that means
//se b & Read cuidado, só dá para ler os registos alternativos byte a byte
#define SRES 0x30 // Reset chip
// se b - PARTNUM (part number do cc1101 inutil)
#define SFSTXON 0x31 // Enable and calibrate frequency synthesizer (if MCSM0.FS_AUTOCAL=1). If in RX (with CCA): Go to a wait state where only the synthesizer is running (for quick RX / TX turnaround).
// se b - VERSION (version number do cc1101 inutil)

#define SXOFF 0x32 // Turn off crystal oscillator
// se b - FREQEST (frequency offset estimate)

#define SCAL 0x33 // Calibrate frequency synthesizer and turn it off
// se b - LQI (Demodulator estimate for link quality)

#define SRX 0x34 // Enable RX. Perform calibration first if coming from IDLE and MCSM0.FS_AUTOCAL=1
// se b - RSSI (Received signal strength indication)

#define STX 0x35 //In IDLE state: Enable TX. Perform calibration first if MCSM0.FS_AUTOCAL=1.If in RX state and CCA is enabled: Only go to TX if channel is clear
// se b - MARCSTATE (Control state machine state)

#define SIDLE 0x36 // Exit RX / TX, turn off frequency synthesizer and exit Wake-On-Radio mode if applicable
// se b - WORTIME1 (High Byte of WOR timer)

#define WT0 0x37 //
// se b - WORTIME0 (Low Byte of WOR timer)

#define SWOR 0x38 // Start automatic RX polling sequence (Wake-on-Radio) as described in Section 19.5 if WORCTRL.RC_PD=0
// se b - PKTSTATUS (GDOx status and packet status)

#define SPWD 0x39 // Enter power down mode when CSn goes high
// se b - VCO_VC_DAC (Current setting from PLL calibration module)

#define SFRX 0x3A // Flush the RX FIFO buffer. Only issue SFRX in IDLE or RXFIFO_OVERFLOW
// se b - TXBYTES Underflow e bytes em TX FIFO

#define SFTX 0x3B // Flush the TX FIFO buffer. Only issue SFTX in IDLE or TXFIFO_UNDERFLOW
// se b - RXBYTES Overflow e bytes em RX FIFO

#define SWORRST 0x3C // Reset real time clock to Event1 value
// se b - RCCTRL1_STATUS (last RC oscillator calibration result)

#define SNOP 0x3D //no op, good for filler and requesting status byte :)
// se b -  RCCTRL0_STATUS (last RC oscillator calibration result)

#define PATABLE 0x3E

#define FIFO 0x3F









#endif