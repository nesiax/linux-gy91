#include <stdio.h>
#include <string.h>

#include "bmp280_defs.h"
#include "bmp280.h"
#include "bmp2xx.h"

#include "utils.h"


int bmp2xx_init(bmp280_dev_t *bmp, bmp280_delay_fptr_t delay, bmp280_com_fptr_t read, bmp280_com_fptr_t write)
{
    int8_t rslt;

    /* Map the delay function pointer with the function responsible for implementing the delay */
    bmp->delay_ms = delay;

    /* Assign device I2C address based on the status of SDO pin (GND for PRIMARY(0x76) & VDD for SECONDARY(0x77)) */
    bmp->dev_id = BMP280_I2C_ADDR_PRIM;

    /* Select the interface mode as I2C */
    bmp->intf = BMP280_I2C_INTF;

    /* Map the I2C read & write function pointer with the functions responsible for I2C bus transfer */
    bmp->read = read;
    bmp->write = write;

    rslt = bmp280_init(bmp);
    if (rslt != BMP280_OK)
        {
            print_rslt(" bmp280_init status", rslt);
            return rslt;
        }

    return rslt;
}


int bmp2xx_set_config(bmp280_config_t *conf, bmp280_dev_t *bmp)
{
    int8_t rslt;

    /* /\* Always read the current settings before writing, especially when */
    /*  * all the configuration is not modified */
    /*  *\/ */
    /* rslt = bmp280_get_config(conf, bmp); */
    /* if (rslt != BMP280_OK) */
    /*     { */
    /*         print_rslt(" bmp280_get_config status", rslt); */
    /*     } */

    /* configuring the temperature oversampling, filter coefficient and output data rate */
    /* Overwrite the desired settings */
    conf->filter = BMP280_FILTER_COEFF_2;

    /* Temperature oversampling set at 4x */
    //conf->os_temp = BMP280_OS_4X;

    /* Pressure over sampling none (disabling pressure measurement) */
    //conf->os_pres = BMP280_OS_NONE;

    /* Setting the output data rate as 1HZ(1000ms) */
    conf->odr = BMP280_ODR_1000_MS;

    rslt = bmp280_set_config(conf, bmp);
    if (rslt != BMP280_OK)
        {
            print_rslt(" bmp280_set_config status", rslt);
        }

    /* Always set the power mode after setting the configuration */
    rslt = bmp280_set_power_mode(BMP280_NORMAL_MODE, bmp);
    if (rslt != BMP280_OK)
        {
            print_rslt(" bmp280_set_power_mode status", rslt);
        }

    return rslt;

}

/* Local Variables:  */
/* mode: c           */
/* c-basic-offset: 4 */
/* End:              */
