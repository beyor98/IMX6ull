#include "led_resource.h"

static struct led_resource board_A_led = {
	.pin = (3<<16)|(1);
}

struct led_resource get_led_resource(void)
{
	return board_A_led;
}