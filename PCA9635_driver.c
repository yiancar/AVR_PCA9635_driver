#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "PCA9635_driver.h"
#include "TWIlib.h"

// Create buffer to assemble I2C transmission
uint8_t twi_transfer_buffer[TXMAXBUFLEN];


void PCA9635_write_registers (uint8_t address, uint8_t reg, uint8_t data){
	twi_transfer_buffer[0] = (address << 1) | 0x00; //shift 7bit address left and add 0 to indicate write
	twi_transfer_buffer[1] = reg;
	twi_transfer_buffer[2] = data;
	
	TWIInfo.errorCode = TWI_NO_RELEVANT_INFO; //clear errors
	
	while (TWIInfo.errorCode != TWI_SUCCESS){
		TWITransmitData (twi_transfer_buffer, 3, 0); //buffer, its size, and dont repeatstart
	}
}

void PCA9635_write_all_pwm (uint8_t address, uint8_t *pwm_buffer){
	twi_transfer_buffer[0] = (address << 1) | 0x00; //shift 7bit address left and add 0 to indicate write
	twi_transfer_buffer[1] = PWM0 | 0x80; //go to register and enable auto incriment
	
	//copy pwm array to twm buffer
	for(uint8_t i = 0; i < PCA9635_ACTIVE_CHANNELS; i++ ){
		twi_transfer_buffer[2 + i] = pwm_buffer[i];
	}
	
	TWIInfo.errorCode = TWI_NO_RELEVANT_INFO; //clear errors
	
	while (TWIInfo.errorCode != TWI_SUCCESS){
		TWITransmitData (twi_transfer_buffer, 2 + PCA9635_ACTIVE_CHANNELS, 0); //buffer, its size, and dont repeatstart
	}
}

//initialize device and set modes, check datasheet
//(addres, bool sleep mode, bool allcall, bool dmblnk, bool invrt, bool och, bool outdrv, outne can 0-2)
void PCA9635_init (uint8_t address, uint8_t lpower, uint8_t allcall, uint8_t dmblnk, uint8_t invrt, uint8_t och, uint8_t outdrv, uint8_t outne){
	sei(); //enable interrupts
	TWIInit(); //initialize i2c
	
	twi_transfer_buffer[2] = 0x00; //clear buffers to enable bit manipulation
	twi_transfer_buffer[3] = 0x00;
	
	twi_transfer_buffer[0] = (address << 1) | 0x00; //shift 7bit address left and add 0 to indicate write
	twi_transfer_buffer[1] = MODE1 | 0x80; // go to register and enable auto incriment
	twi_transfer_buffer[2] |= (lpower << 4) | (allcall << 0); //set mode 1
	twi_transfer_buffer[3] |= (dmblnk << 5) | (invrt << 4) | (och << 3) | (outdrv << 2) | (outne << 0); //set mode 2
	
	TWIInfo.errorCode = TWI_NO_RELEVANT_INFO; //clear errors
	
	while (TWIInfo.errorCode != TWI_SUCCESS){
		TWITransmitData (twi_transfer_buffer, 4, 0); //buffer, its size, and dont repeatstart
	}
	
	//now set all leds to PWM and GRP PWM mode
	twi_transfer_buffer[0] = (address << 1) | 0x00; //shift 7bit address left and add 0 to indicate write
	twi_transfer_buffer[1] = LEDOUT0 | 0x80; //go to ledout0 and enable auto incriment
	twi_transfer_buffer[2] = 0xff;
	twi_transfer_buffer[3] = 0xff;
	twi_transfer_buffer[4] = 0xff;
	twi_transfer_buffer[5] = 0xff;
	
	TWIInfo.errorCode = TWI_NO_RELEVANT_INFO; //clear errors
	
	while (TWIInfo.errorCode != TWI_SUCCESS){
		TWITransmitData (twi_transfer_buffer, 6, 0); //buffer, its size, and dont repeatstart
	}
}

