#include <stdio.h>

#include "bmp280_defs.h"
#include "utils.h"

/*!
 *  @brief Prints the execution status of the APIs.
 *
 *  @param[in] api_name : name of the API whose execution status has to be printed.
 *  @param[in] rslt     : error code returned by the API whose execution status has to be printed.
 *
 *  @return void.
 */
void print_rslt(const char api_name[], int8_t rslt)
{
    if (rslt != BMP280_OK)
        {
            printf("%s\t", api_name);
            if (rslt == BMP280_E_NULL_PTR)
                {
                    printf("Error [%d] : Null pointer error\r\n", rslt);
                }
            else if (rslt == BMP280_E_COMM_FAIL)
                {
                    printf("Error [%d] : Bus communication failed\r\n", rslt);
                }
            else if (rslt == BMP280_E_IMPLAUS_TEMP)
                {
                    printf("Error [%d] : Invalid Temperature\r\n", rslt);
                }
            else if (rslt == BMP280_E_DEV_NOT_FOUND)
                {
                    printf("Error [%d] : Device not found\r\n", rslt);
                }
            else
                {
                    /* For more error codes refer "*_defs.h" */
                    printf("Error [%d] : Unknown error code\r\n", rslt);
                }
        }
}

/* Local Variables:  */
/* mode: c           */
/* c-basic-offset: 4 */
/* End:              */
