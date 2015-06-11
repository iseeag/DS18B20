DS18B20 RaspberryPi demo 
======
this c++ code can be used with up to 8 sensors in a single bus, but I have no idea how slow it would be


The setup script does the following: 
add modules through command lines: 
sudo modprobe w1-gpio
sudo modprobe w1-therm 
Try overlay if /sys/bus/w1/devices couldn't be found by adding 'dtoverlay=w1-gpio' (without the quotes) to /boot/config.txt 
more details: https://github.com/raspberrypi/firmware/tree/master/boot/overlays

~~~
//some advanced stuff: 
Customise kernel to have multiple 1-wire bus on Pi. 
Example: 

#if defined(CONFIG_W1_MASTER_GPIO) || defined(CONFIG_W1_MASTER_GPIO_MODULE)
static struct w1_gpio_platform_data w1_gpio_pdata = {
            .pin = W1_GPIO,
                    .is_open_drain = 0,
};

static struct platform_device w1_device = {
            .name = "w1-gpio",
                    .id = 0,
                            .dev.platform_data = &w1_gpio_pdata,
};
static struct w1_gpio_platform_data w1_gpio_pdata1 = {
            .pin = 22,
                    .is_open_drain = 0,
};

static struct platform_device w1_device1 = {
            .name = "w1-gpio",
                    .id = 1,
                            .dev.platform_data = &w1_gpio_pdata1,
};
static struct w1_gpio_platform_data w1_gpio_pdata2 = {
            .pin = 23,
                    .is_open_drain = 0,
};

static struct platform_device w1_device2 = {
            .name = "w1-gpio",
                    .id = 2,
                            .dev.platform_data = &w1_gpio_pdata2,
};
static struct w1_gpio_platform_data w1_gpio_pdata3 = {
            .pin = 24,
                    .is_open_drain = 0,
};

static struct platform_device w1_device3 = {
            .name = "w1-gpio",
                    .id = 3,
                            .dev.platform_data = &w1_gpio_pdata3,
};
#endif
~~~
