#ifndef _LED_RESOURCE_H
#define _LED_RESOURCE_H

#define GROUP(X) (X>>16)
#define PIN(X) (X&0xFFFF)
#define GROUP_PIN(G ,P) ((g<<16)|(P))

struct led_resource {
	int pin;
};

struct led_resource *get_led_resource(void);


#endif

