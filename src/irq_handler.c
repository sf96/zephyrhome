#include <stdio.h>
#include <device.h>
#include <drivers/gpio.h>

extern int fire_alarm_flag;
extern int state_flag;

static const struct device *gpio_device;
static struct gpio_callback irq_data;

int fire_alarm_pin = 3;

void power_alarm_handler(const struct device *dev, struct gpio_callback *data, gpio_port_pins_t pins)
{
	if (pins & 0x1) {
		if (state_flag == 0) {
			state_flag = 1;
			printf("* Starting\n");
		} else {
			state_flag = 0;
			printf("* Turning off ...\n");
		}
	} else if (pins & 0x2) {
		fire_alarm_flag = 1;
		gpio_pin_set(dev, fire_alarm_pin, 1);
		printf("\n");
		printf("XXXXXXXXXXXXXXXXXXXXXXXXXX\n");
		printf("!!!                    !!!\n");
		printf("!!! FIRE ALARM STARTED !!!\n");
		printf("!!!    DO NOT PANIC    !!!\n");
		printf("!!!                    !!!\n");
		printf("XXXXXXXXXXXXXXXXXXXXXXXXXX\n");
		printf("\n");
	} else if (pins & 0x4) {
		if (fire_alarm_flag == 1) {
			fire_alarm_flag = 0;
			gpio_pin_set(dev, fire_alarm_pin, 0);
			printf("UUUUUUUUUUUUUUUUUUUUUUUUUUUUU\n");
			printf("///                       ///\n");
			printf("/// Fire alarm turned off ///\n");
			printf("///      SUCCESS :D       ///\n");
			printf("///                       ///\n");
			printf("UUUUUUUUUUUUUUUUUUUUUUUUUUUUU\n");
		}
	}
}

void gpio_setup()
{
	int ret;

	gpio_device = device_get_binding("GPIOA");
	if (!gpio_device) {
		printf("[ERROR] gpio_setup - GPIO A device_get_binding\n");
		return;
	}
	
	ret = gpio_pin_configure(gpio_device, 0, GPIO_INPUT);
	if (ret) {
		printf("[ERROR] gpio_setup - GPIO.A pin 0 as input\n");
		printf("\tconfiguration fail");
		return;
	}

	ret = gpio_pin_configure(gpio_device, 1, GPIO_INPUT);
	if (ret) {
		printf("[ERROR] gpio_setup - GPIO.A pin 1 as input\n");
		printf("\tconfiguration fail");
		return;
	}

	ret = gpio_pin_configure(gpio_device, 2, GPIO_INPUT);
	if (ret) {
		printf("[ERROR] gpio_setup - GPIO.A pin 2 as input\n");
		printf("\tconfiguration fail");
		return;
	}

	ret = gpio_pin_configure(gpio_device, fire_alarm_pin, GPIO_OUTPUT_INACTIVE);
	if (ret) {
		printf("[ERROR] gpio_setup - GPIO.A pin %d as output\n", fire_alarm_pin);
		printf("\tconfiguration fail");
		return;
	}

	ret = gpio_pin_interrupt_configure(gpio_device, 0, GPIO_INT_EDGE_TO_ACTIVE);
	if (ret) {
		printf("[ERROR] gpio_setup - IRQ on GPIO.A pin 0\n");
		printf("\tinterrupt configuration fail");
		return;
	}

	ret = gpio_pin_interrupt_configure(gpio_device, 1, GPIO_INT_EDGE_TO_ACTIVE);
	if (ret) {
		printf("[ERROR] gpio_setup - IRQ on GPIO.A pin 1\n");
		printf("\tinterrupt configuration fail");
		return;
	}

	ret = gpio_pin_interrupt_configure(gpio_device, 2, GPIO_INT_EDGE_TO_ACTIVE);
	if (ret) {
		printf("[ERROR] gpio_setup - IRQ on GPIO.A pin 2\n");
		printf("\tinterrupt configuration fail");
		return;
	}

	gpio_init_callback(&irq_data, power_alarm_handler, (gpio_port_pins_t)0x7);
	gpio_add_callback(gpio_device, &irq_data);
	printf("[NOTE]  gpio_setup - initialization success");

}
