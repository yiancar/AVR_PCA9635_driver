## Synopsis

A simple AVR driver for the PCA9635 using I2C interrupts.
http://docs-europe.electrocomponents.com/webdocs/14ac/0900766b814ac9c9.pdf

## References

Uses the TWIlib ( http://www.chrisherring.net/all/tutorial-interrupt-driven-twi-interface-for-avr-part1/ )

## Example

Define the I2C slave address and the number of channels used in the header file.

PCA9635_init 
...Initializes the I2C bus the global interrupt registers SEI and send the initialization data to the chip.
...Inputs 	- I2C slave address of chip
......- Sleep register (bool), puts chip in sleep mode 
			- Allcall register (bool), responds to calls for all other PCA9635 on the bus
			- Dmblk register (bool), selects either dimming or blinking function
			- Invrt register (bool), inverts output | used with external drivers
			- Och register (bool), change outputs on I2C ACK
			- Outdrv register (bool), enables internal totem-pole output driver
			- Outne register (0-2), changes the behavior of the OE pin

PCA9635_write_register
	Writes to a single register of the chip
	Inputs	- I2C slave address of chip
			- Register to write to
			- Value to write (0x00 - 0xFF)

PCA9635_write_register
	Writes to all pwm registers
	Inputs	- I2C slave address of chip
			- Array with pwm values (0x00 - 0xFF) Size of array should equal number of active channels

## Improvements

Read is not implimented as reading a value to check if you should change it is slower that changing it anyway

## License

This project is licensed under the MIT License