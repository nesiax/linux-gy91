#ifndef BMP2XX_H
#define BMP2XX_H

typedef struct bmp280_dev bmp280_dev_t;
typedef struct bmp280_config bmp280_config_t;

int bmp2xx_init(bmp280_dev_t *bmp, bmp280_delay_fptr_t delay, bmp280_com_fptr_t read, bmp280_com_fptr_t write);
int bmp2xx_set_config(bmp280_config_t *conf, bmp280_dev_t *bmp);

#endif /* BMP2XX_H */


/* Local Variables:  */
/* mode: c           */
/* c-basic-offset: 4 */
/* End:              */
