#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <sys/printk.h>
#include "irq_handler.h"
#include "light_sensor.h"
#include "i2c_sensor.h"
#include "blinds.h"

int state_flag = 1;
int fire_alarm_flag = 0;

void main(void)
{
	printk("*********************************\n");
	printk("*           WELCOME  IN         *\n");
	printk("*           ZEPHYR HOME         *\n");
	printk("*           id:  131010         *\n");
	printk("*********************************\n");

	int light_level_curr = 0;
	int light_level_prev = -1;
	int status_variable_curr = 0;
	int status_variable_prev = -1;

	gpio_setup();
	i2c_sensor_setup();
	light_control_setup();
	blinds_control_setup();

	while (true) {
		if (state_flag == 1) {
			printf("\n");
			light_level_curr = i2c_sensor_read();
			if (light_level_prev != light_level_curr) {
				light_level_prev = light_level_curr;
				printf("[STATUS] light - value: %u\n", light_level_curr);
			}

			status_variable_curr = (light_level_curr * 15)/100;
			if (status_variable_prev != status_variable_curr) {
				status_variable_prev = status_variable_curr;
				printf("[STATUS] status_variable - value: %u\n", status_variable_curr);
				blinds_control_set(status_variable_curr);
				light_control_set(status_variable_curr);
			}
		}
		k_msleep(2500);
	}
}
