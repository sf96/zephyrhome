#include <stdio.h>
#include <drivers/gpio.h>
#include "light_sensor.h"

static const struct device *light_device;
static uint8_t value_prev = 0;

void light_control_set(uint8_t value)
{
	if (value != value_prev) {
		int value_to_set = 0;
		for (int i = 0; i < 4; i++) {
			value_to_set = (BIT(i) & value) != 0 ? 1 : 0;
			int ret = gpio_pin_set(light_device, 4 + i, value_to_set);
			if (ret) {
				printf("[ERROR] light_control_set - GPIOB value on pin %d\n", i);
				printf("\tpin set fail");
				return;
			}
		}
		value_prev = value;
		printf("[NOTE] light_control_set - light value is set to 0x%x\n", value);
	} else {
		return;
	}
}

void light_control_setup()
{
	light_device = device_get_binding("GPIOB");
	if (!light_device) {
		printf("[ERROR] light_control_setup - GPIOB device\n");
		printf("\tdevice_get_binding fail");
		return;
	}

	int ret = gpio_pin_configure(light_device, 4, GPIO_OUTPUT_ACTIVE);
	if (ret) {
		printf("[ERROR] light_control_setup - GPIOB pin 4");
		printf("\tconfiguration fail");
		return;
	}
	
	ret = gpio_pin_configure(light_device, 5, GPIO_OUTPUT_ACTIVE);
	if (ret) {
		printf("[ERROR] light_control_setup - GPIOB pin 5");
		printf("\tconfiguration fail");
		return;
	}
	
	ret = gpio_pin_configure(light_device, 6, GPIO_OUTPUT_ACTIVE);
	if (ret) {
		printf("[ERROR] light_control_setup - GPIOB pin 6");
		printf("\tconfiguration fail");
		return;
	}

	ret = gpio_pin_configure(light_device, 7, GPIO_OUTPUT_ACTIVE);
	if (ret) {
		printf("[ERROR] light_control_setup - GPIOB pin 7");
		printf("\tconfiguration fail");
		return;
	}

	printf("[NOTE] light_control_setup - initialization success\n");
}
