

#define GPIO_OUTPUT_PIN(REG,BIT) ((REG) |=(1U<<(BIT)))
#define GPIO_INPUT_PIN(REG,BIT) ((REG) &=~(1U<<(BIT)))
#define GPIO_OUTPUT_PINS(REG,MASK) ((REG) |=(MASK))
#define GPIO_INPUT_PINS(REG,MASK) ((REG) &=~(MASK))

/* active high leds on and off*/
#define LED_AH_ON(PORT,BIT) (IOSET##PORT=(1U<<(BIT)))
#define LED_AH_OFF(PORT,BIT) (IOCLR##PORT=(1U<<(BIT)))

/*active low leds on and off*/
#define LED_AL_ON(PORT,BIT) (IOCLR##PORT=(1U<<(BIT)))
#define LED_AL_OFF(PORT,BIT) (IOSET##PORT=(1U<<(BIT)))

/*active low switch*/
#define AL_SW_PRESSED(PORT,BIT) (!(IOPIN##PORT&(1U<<(BIT))))

/*active high switch*/
#define AH_SW_PRESSED(PORT,BIT) (IOPIN##PORT&(1U<<(BIT)))
