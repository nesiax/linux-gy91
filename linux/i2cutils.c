/*!
 *  @brief Example shows basic setup of sensor which includes following
 *      Initialization of the interface.
 *      performing the sensor initialization.
 */

#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
#include <time.h>

#include "i2cbusses.h"

static int check_funcs(int file, int size, int daddress)
{
    unsigned long funcs;

    /* check adapter functionality */
    if (ioctl(file, I2C_FUNCS, &funcs) < 0) {
        fprintf(stderr, "Error: Could not get the adapter "
                "functionality matrix: %s\n", strerror(errno));
        return -1;
    }

    if (!(funcs & I2C_FUNC_SMBUS_READ_BYTE_DATA)) {
        fprintf(stderr, MISSING_FUNC_FMT, "SMBus read byte");
        return -1;
    }

    return 0;
}

/*!
 *  @brief Function that creates a mandatory delay required in some of the APIs such as "bmg250_soft_reset",
 *      "bmg250_set_foc", "bmg250_perform_self_test"  and so on.
 *
 *  @param[in] period_ms  : the required wait time in milliseconds.
 *  @return void.
 *
 */
void bmp2xx_delay_ms(uint32_t period_ms)
{
    struct timespec ts;

    ts.tv_sec = period_ms / 1000;
    ts.tv_nsec = (period_ms % 1000) * 1000000;

    nanosleep(&ts, NULL);
}

/*!
 *  @brief Function for writing the sensor's registers through I2C bus.
 *
 *  @param[in] i2c_addr : sensor I2C address.
 *  @param[in] reg_addr : Register address.
 *  @param[in] reg_data : Pointer to the data buffer whose value is to be written.
 *  @param[in] length   : No of bytes to write.
 *
 *  @return Status of execution
 *  @retval 0 -> Success
 *  @retval >0 -> Failure Info
 *
 */
int8_t i2c_reg_write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length)
{

    /* Implement the I2C write routine according to the target machine. */
    int i2cbus, size, file;

    char filename[20];
    int force = 0;
    int res = 0;

#ifdef I2C_DEBUG
    fprintf(stderr, "in write\n");
    fprintf(stderr, "i2c_addr 0x%.8X, reg_addr 0x%.8X, reg_dat 0x%.8X, lenght 0x%.8X\n",
            i2c_addr, reg_addr, *reg_data, length );
#endif

    i2cbus = 1;

    size = I2C_SMBUS_BYTE_DATA;

    if (reg_addr < 0 || reg_addr > 0xff) {
        fprintf(stderr, "Error: Data address invalid!\n");
        return -1;
    }

    file = open_i2c_dev(i2cbus, filename, sizeof(filename), 0);
    if (file < 0
        || check_funcs(file, size, reg_addr)
        || set_slave_addr(file, i2c_addr, force)) {
        fprintf(stderr, "Error: No pass checks!\n");
        return -2;
    }

    /* I2C_SMBUS_BYTE_DATA */

    for (int i = 0 ; i< length ; i++)
        {
            res = i2c_smbus_write_byte_data(file, reg_addr, *reg_data);

            if (res < 0) {
                fprintf(stderr, "Error: Read failed\n");
                return -3;
            }
            reg_addr++;
            reg_data++;
        }

    close(file);

    return 0;


}

/*!
 *  @brief Function for reading the sensor's registers through I2C bus.
 *
 *  @param[in] i2c_addr : Sensor I2C address.
 *  @param[in] reg_addr : Register address.
 *  @param[out] reg_data    : Pointer to the data buffer to store the read data.
 *  @param[in] length   : No of bytes to read.
 *
 *  @return Status of execution
 *  @retval 0 -> Success
 *  @retval >0 -> Failure Info
 *
 */
int8_t i2c_reg_read(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length)
{

    /* Implement the I2C read routine according to the target machine. */

    /* i2cget -y 1 0x76 0x81 = 0x74 */

    int i2cbus, size, file;

    char filename[20];
    int force = 0;


#ifdef I2C_DEBUG
    fprintf(stderr, "in read\n");
    fprintf(stderr, "i2c_addr 0x%.8X, reg_addr 0x%.8X, reg_dat 0x%.8X, lenght 0x%.8X\n",
            i2c_addr, reg_addr, *reg_data, length );
#endif

    i2cbus = 1;

    size = I2C_SMBUS_BYTE_DATA;

    if (reg_addr < 0 || reg_addr > 0xff) {
        fprintf(stderr, "Error: Data address invalid!\n");
        return -1;
    }

    file = open_i2c_dev(i2cbus, filename, sizeof(filename), 0);
    if (file < 0
        || check_funcs(file, size, reg_addr)
        || set_slave_addr(file, i2c_addr, force)) {
        fprintf(stderr, "Error: No pass checks!\n");
        return -2;
    }
    /* I2C_SMBUS_BYTE_DATA */

    for (int i = 0 ; i< length ; i++)
        {
            *reg_data = i2c_smbus_read_byte_data(file, reg_addr + i);
            if (*reg_data < 0) {
                fprintf(stderr, "Error: Read failed\n");
                return -3;
            }
            reg_data++;
        }

    close(file);

#ifdef I2C_DEBUG
    fprintf(stderr, "DEBUG: returning 0\n");
#endif

    return 0;

}
