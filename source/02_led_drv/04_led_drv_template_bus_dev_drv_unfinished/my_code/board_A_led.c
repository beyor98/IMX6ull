
#include "led_resource.h"

static struct led_resource board_A_led = {
	.pin = GROUP_PIN(3,1),
};

static struct resource resources[] = {
        {
                .start = GROUP_PIN(3,1),
                .flags = IORESOURCE_IRQ,
        },
        {
                .start =  GROUP_PIN(5,8),
                .flags = IORESOURCE_IRQ,
        },
}

struct led_resource *get_led_resouce(void)
{
	return &board_A_led;
}

struct led_resource get_led_resource(void)
{
	return board_A_led;
}

static struct platform_device board_A_led_dev = {
	.name = "100ask_led",
	.num_resources = ARRAY_SIZE(resources),
	.resource = &resource,
};

static int led_dev_init(void)
{
	int err;
	err = platform_device_register(&board_A_led_dev);

	return 0;
}

static int led_dev_exit(void)
{
	platform_device_register(&board_A_led_dev);
}

module_init(led_dev_init);
module_exit(led_dev_exit);
MODULE_LICENSE("GPL");


