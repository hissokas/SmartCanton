#include <bme680_bsec_support.h>
/**
 * @file    bme680_task.c
 * @author  Da Silva Andrade David
 * @version V1.0
 * @date    25-10-2017
 * @brief
 */

#include "bme680_task.h"
#include "dev_box_app_task.h"
#include "LED.h"
#include "Panic.h"

OSA_TASK_DEFINE(Bme680_Task, gBme680TaskPriority_c, 1, gBme680TaskStackSize_c, FALSE);
osaTaskId_t gBme680TaskId = 0;

static i2c_rtos_handle_t* master_rtos_handle;

struct bme680_dev bme680;

osaMsgQId_t gBme680NewMessageMeasureQ;

/*!
 * @brief           Handling of the ready outputs
 *
 * @param[in]       timestamp       time in nanoseconds
 * @param[in]       iaq             IAQ signal
 * @param[in]       iaq_accuracy    accuracy of IAQ signal
 * @param[in]       temperature     temperature signal
 * @param[in]       humidity        humidity signal
 * @param[in]       pressure        pressure signal
 * @param[in]       raw_temperature raw temperature signal
 * @param[in]       raw_humidity    raw humidity signal
 * @param[in]       gas             raw gas sensor signal
 * @param[in]       bsec_status     value returned by the bsec_do_steps() call
 *
 * @return          none
 */
void output_ready(int64_t timestamp, float iaq, uint8_t iaq_accuracy, float temperature, float humidity,
     float pressure, float raw_temperature, float raw_humidity, float gas, bsec_library_return_t bsec_status)
{
	// Data to be sent to the main task
	static bme680Data_t* bme680Data;

	bme680Data = pvPortMalloc(sizeof(bme680Data_t));

	bme680Data->iaq=iaq;
	bme680Data->iaq_accuracy=iaq_accuracy;
	bme680Data->temperature=temperature;
	bme680Data->humidity=humidity;
	bme680Data->pressure=pressure;
	bme680Data->raw_temperature=raw_temperature;
	bme680Data->raw_humidity=raw_humidity;
	bme680Data->gas=gas;

	OSA_MsgQPut(gBme680NewMessageMeasureQ, &bme680Data);
	/* Inform the DevBox Task that she can read the data available */
	OSA_EventSet(gDevBoxAppEvent, gDevBoxTaskEvtNewBME680Measure_c);
}


/**
 * Main BME680 task function
 */
void Bme680_Task(osaTaskParam_t argument)
{
	int8_t rslt = 0;
	(void)rslt;

	while (1)
	{
		bme680_bsec_kw41z_I2C_routines_init(&bme680, master_rtos_handle);

		/**
		 * Only quit when the Get MSEC is too small for the library
		 * After 1h, we restart the library with a clean configuration.
		 * TODO: Try to find a better way to do this. The ideal will be to
		 * have a Get MSEC in 64bits instead of 32 bits for now.
		 * See inside the function to have a peak where the calucul fails.
		 */
		bme680_bsec_kw41z_iot_loop(output_ready);
	}
}

osaStatus_t Bme680_TaskInit(i2c_rtos_handle_t* i2c_master_rtos_handle)
{
	if (gBme680TaskId)
	{
		return osaStatus_Error;
	}

	master_rtos_handle = i2c_master_rtos_handle;

	/* Create application Queue */
	gBme680NewMessageMeasureQ = OSA_MsgQCreate(BME680_MEASURE_QUEUE_SIZE);
	if ( NULL == gBme680NewMessageMeasureQ)
	{
		panic(0, 0, 0, 0);
		return osaStatus_Error;
	}

	/* Task creation */
	gBme680TaskId = OSA_TaskCreate(OSA_TASK(Bme680_Task), NULL);

	if ( NULL == gBme680TaskId)
	{
		panic(0, 0, 0, 0);
		return osaStatus_Error;
	}

	return osaStatus_Success;
}

