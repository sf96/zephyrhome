#include "blinds.h"

static const struct device *blinds_device;
static uint8_t value_prev = 0;

void blinds_control_set(uint8_t value)
{
	if (value != value_prev) {
		int value_to_set = 0;
		for (int i = 0; i < 4; i++) {
			value_to_set = (BIT(i) & value) != 0 ? 1 : 0;
			int ret = gpio_pin_set(blinds_device, 8 + i, value_to_set);
			if (ret) {
				printf("[ERROR] blinds_set - GPIOB value on pin %d\n", i);
				printf("\tpin set fail");
				return;
			}
		}
		value_prev = value;
		printf("[NOTE] blinds_set - blinds are value is set to 0x%x\n", value);
	} else {
		return;
	}
}

void blinds_control_setup()
{
	blinds_device = device_get_binding("GPIOC");
	if (!blinds_device) {
		printf("[ERROR] blinds_setup - GPIOC device\n");
		printf("\tdevice_get_binding fail");
		return;
	}

	int ret = gpio_pin_configure(blinds_device, 8, GPIO_OUTPUT_ACTIVE);
	if (ret) {
		printf("[ERROR] blinds_setup - GPIOC pin 8");
		printf("\tconfiguration fail");
		return;
	}
	
	ret = gpio_pin_configure(blinds_device, 9, GPIO_OUTPUT_ACTIVE);
	if (ret) {
		printf("[ERROR] blinds_setup - GPIOC pin 9");
		printf("\tconfiguration fail");
		return;
	}

	ret = gpio_pin_configure(blinds_device, 10, GPIO_OUTPUT_ACTIVE);
	if (ret) {
		printf("[ERROR] blinds_setup - GPIOC pin 10");
		printf("\tconfiguration fail");
		return;
	}

	ret = gpio_pin_configure(blinds_device, 11, GPIO_OUTPUT_ACTIVE);
	if (ret) {
		printf("[ERROR] blinds_setup - GPIOC pin 11");
		printf("\tconfiguration fail");
		return;
	}

	printf("[NOTE] blinds_setup - initialization success\n");
}

