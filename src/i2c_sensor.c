#include "i2c_sensor.h"

static const struct device *i2c_sensor_device;

#define ADDRESS 0x40
#define REGISTER 0xe5

int i2c_sensor_read()
{
	int value = 0;
	uint8_t sensor_data[2];

	if (!i2c_burst_read(i2c_sensor_device, ADDRESS, REGISTER, sensor_data, sizeof(sensor_data))) {
		value = ((sensor_data[0] << 8 | sensor_data[1]) * 125 >> 16) - 5;
		printf("[NOTE] i2c_sensor_read - read success\n");
	} else {
		value = -1;
		printf("[ERROR] i2c_sensor_read\n");
		printf("\tunable to read data");
	}

	return value;
}

void i2c_sensor_setup()
{
	i2c_sensor_device = device_get_binding("I2C_1");
	if (!i2c_sensor_device) {
		printf("[ERROR] i2c_sensor_setup\n");
		printf("\tdevice_get_binding I2C_1 unsuccesful");
		return;
	} else {
		printf("[NOTE] i2c_sensor_device - initialization success\n");
	}
}

