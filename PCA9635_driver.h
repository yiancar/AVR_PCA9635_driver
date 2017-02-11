#ifndef PCA9635_DRIVER_H
#define PCA9635_DRIVER_H

//set I2C address
#define	PCA9635_addr	0x15
//set number of active leds (1-16)
#define PCA9635_ACTIVE_CHANNELS 14
//addresses for shortcut
#define MODE1	0x00
#define MODE2	0x01
#define PWM0	0x02
#define PWM1	0x03
#define PWM2	0x04
#define PWM3	0x05
#define PWM4	0x06
#define PWM5	0x07
#define PWM6	0x08
#define PWM7	0x09
#define PWM8	0x0A
#define PWM9	0x0B
#define PWM10	0x0C
#define PWM11	0x0D
#define PWM12	0x0E
#define PWM13	0x0F
#define PWM14	0x10
#define PWM15	0x11
#define GRPPWM	0x12
#define GRPFREQ	0x13
#define LEDOUT0	0x14
#define LEDOUT1	0x15
#define LEDOUT2	0x16
#define LEDOUT3	0x17
#define SUBADR1	0x18
#define SUBADR2	0x19
#define SUBADR3	0x1A
#define ALLCALLADR	0x2B

void PCA9635_init (uint8_t address, uint8_t lpower, uint8_t allcall, uint8_t dmblnk, uint8_t invrt, uint8_t och, uint8_t outdrv, uint8_t outne);
void PCA9635_write_registers (uint8_t address, uint8_t reg, uint8_t data);
void PCA9635_write_all_pwm (uint8_t address, uint8_t *pwm_buffer);

#endif //PCA9635_DRIVER_H