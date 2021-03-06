/**
 * @file    smartcanton_devbox_bno055_service.c
 * @author  Da Silva Andrade David
 * @version V1.0
 * @date    02-01-2018
 * @brief	Define the interface to manage the bno055 service of the SmartCanton
 * 			DevBox. Contain function to start, stop, subscribe and unsubscribe from 
 *  		the service. Data can be written to the ble database or/and generate 
 * 			notifications.
 */

/************************************************************************************
 *************************************************************************************
 * Include
 *************************************************************************************
 ************************************************************************************/
#include "smartcanton_devbox_bno055_interface.h"
#include "gatt_uuid_decl_x.h"
#include "stdio.h"
#include "string_utils.h"

/************************************************************************************
 *************************************************************************************
 * Private constants & macros
 *************************************************************************************
 ************************************************************************************/

/************************************************************************************
 *************************************************************************************
 * Private type definitions
 *************************************************************************************
 ************************************************************************************/

/************************************************************************************
 *************************************************************************************
 * Private memory declarations
 *************************************************************************************
 ************************************************************************************/

/*! Smart Canton Dev Box GPS Service - Subscribed Client*/
static deviceId_t mScDbBno055_SubscribedClientId;

/************************************************************************************
 *************************************************************************************
 * Private functions prototypes
 *************************************************************************************
 ************************************************************************************/

bleResult_t ScDbBno055_SendInstantValueNotifications(bleUuid_t* pCharacteristicUuid,
		uint16_t *serviceHandle, uint8_t* value, uint16_t valueLength);

/************************************************************************************
 *************************************************************************************
 * Public functions
 *************************************************************************************
 ************************************************************************************/
bleResult_t ScDbBno055_Start(scdbBno055Config_t *pServiceConfig)
{
	bleResult_t result;

	/* Clear subscribed client ID (if any) */
	mScDbBno055_SubscribedClientId = gInvalidDeviceId_c;

	result = gBleSuccess_c;
	return result;
}

bleResult_t ScDbBno055_Stop(scdbBno055Config_t *pServiceConfig)
{
	/* Unsubscribe current client */
	return ScDbBno055_Unsubscribe();
}

bleResult_t ScDbBno055_Subscribe(deviceId_t deviceId)
{
	/* Subscribe a new client to this service */
	mScDbBno055_SubscribedClientId = deviceId;

	return gBleSuccess_c;
}

bleResult_t ScDbBno055_Unsubscribe()
{
	/* Clear current subscribed client ID */
	mScDbBno055_SubscribedClientId = gInvalidDeviceId_c;
	return gBleSuccess_c;
}

bleResult_t ScDbBno055_InstantValueNotificationAccel(uint16_t serviceHandle, struct bno055_accel_float_t* accel){

	return ScDbBno055_SendInstantValueNotifications((bleUuid_t*) uuid_bno055_accelerometer,
			&serviceHandle, (uint8_t*)accel, sizeof(struct bno055_accel_float_t));
}

bleResult_t ScDbBno055_InstantValueNotificationGyro(uint16_t serviceHandle, struct bno055_gyro_float_t* gyro){

	return ScDbBno055_SendInstantValueNotifications((bleUuid_t*) uuid_bno055_gyroscope,
			&serviceHandle, (uint8_t*)gyro, sizeof(struct bno055_gyro_float_t));
}

bleResult_t ScDbBno055_InstantValueNotificationMag(uint16_t serviceHandle, struct bno055_mag_float_t* mag){

	return ScDbBno055_SendInstantValueNotifications((bleUuid_t*) uuid_bno055_magnetometer,
			&serviceHandle, (uint8_t*)mag, sizeof(struct bno055_mag_float_t));
}

bleResult_t ScDbBno055_RecordValueMeasureInterval(uint16_t serviceHandle, uint32_t interval){

    uint16_t  handle;

   	bleResult_t result = GattDb_FindCharValueHandleInService(serviceHandle,
   		gBleUuidType128_c, (bleUuid_t*) uuid_bno055_measure_interval, &handle);

   	if (result != gBleSuccess_c)
   		return result;

   	/* Update characteristic value */
   	result = GattDb_WriteAttribute(handle, sizeof(uint32_t), (uint8_t*)&interval);
   	return result;
}

bleResult_t ScDbBno055_InstantValueNotificationAll(uint16_t serviceHandle, bno055Data_t* bno055Data){
	bleResult_t result;

	result = ScDbBno055_InstantValueNotificationAccel(serviceHandle, &bno055Data->accel_xyz);
	if(result != gBleSuccess_c)
		return result;

	result = ScDbBno055_InstantValueNotificationGyro(serviceHandle, &bno055Data->gyro_xyz);
	if(result != gBleSuccess_c)
		return result;

	result = ScDbBno055_InstantValueNotificationMag(serviceHandle, &bno055Data->mag_xyz);

	return result;
}

/************************************************************************************
 *************************************************************************************
 * Private functions
 *************************************************************************************
 ************************************************************************************/

bleResult_t ScDbBno055_SendInstantValueNotifications(bleUuid_t* pCharacteristicUuid,
		uint16_t *serviceHandle, uint8_t* value, uint16_t valueLength)
{
	uint16_t cccdHandle;
	bool_t isNotifActive;
	uint16_t handle;
	bleResult_t result;

	/* Get handle of GPS latitude characteristic */
	result = GattDb_FindCharValueHandleInService(*serviceHandle, gBleUuidType128_c,
			(bleUuid_t*) pCharacteristicUuid, &handle);

	if (result != gBleSuccess_c)
		return result;

	/* Get handle of the handle CCCD */
	result = GattDb_FindCccdHandleForCharValueHandle(handle, &cccdHandle);

	if (result != gBleSuccess_c)
		return result;

	if (mScDbBno055_SubscribedClientId == gInvalidDeviceId_c)
		return gBleUnexpectedError_c;

	if (gBleSuccess_c == Gap_CheckNotificationStatus(mScDbBno055_SubscribedClientId,
			cccdHandle, &isNotifActive) && TRUE == isNotifActive)
	{
		result = GattServer_SendInstantValueNotification(mScDbBno055_SubscribedClientId,
				handle, valueLength, value);
	}

	return result;
}

/*! *********************************************************************************
 * @}
 ********************************************************************************** */
