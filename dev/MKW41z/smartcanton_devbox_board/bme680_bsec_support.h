/**
 * @file    bme680_support.h
 * @author  Da Silva Andrade David
 * @version V1.0
 * @date    25-10-2017
 * @brief   Functions to support the bno055 driver libraries on a Freescale KW41z processor
 */

#ifndef _BME680_SUPPORT_H_
#define _BME680_SUPPORT_H_
#include "BME680_driver/bme680.h"
#include "fsl_i2c_freertos.h"
#include "BME680_BSEC/bsec_integration.h"

return_values_init bme680_bsec_kw41z_I2C_routines_init(struct bme680_dev *bme680,
		i2c_rtos_handle_t* i2c_master_rtos_handle);

void bme680_bsec_kw41z_iot_loop(output_ready_fct output_ready);

#endif /* _BME680_SUPPORT_H_ */