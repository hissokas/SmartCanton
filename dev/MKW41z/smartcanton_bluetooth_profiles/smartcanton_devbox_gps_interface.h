/*! *********************************************************************************
 * \addtogroup Potentiometer Profile
 * @{
 ********************************************************************************** */
/*!
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * \file
 *
 * This file is the interface file for the Heart Rate Service
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _SMARTCANTON_DEVBOX_GPS_INTERFACE_H_
#define _SMARTCANTON_DEVBOX_GPS_INTERFACE_H_

/************************************************************************************
 *************************************************************************************
 * Include
 *************************************************************************************
 ************************************************************************************/

#include "FunctionLib.h"

#include "ble_general.h"
#include "gatt_db_app_interface.h"
#include "gatt_server_interface.h"
#include "gap_interface.h"
#include "lorawan_controller.h"
#include "minmea/minmea.h"

/**
 * This include is only used to be able to use the structure utf8s_t.
 * TODO: Maybe we can implement a ifndef with on both file to define structure in both
 * files.
 */
#include "device_info_interface.h"

/************************************************************************************
 *************************************************************************************
 * Public constants & macros
 *************************************************************************************
 ************************************************************************************/

/************************************************************************************
 *************************************************************************************
 * Public type definitions
 *************************************************************************************
 ************************************************************************************/

/*! Smart Canton Dev Box Service - Configuration */
typedef struct scdbGPSConfig_tag {
	uint16_t serviceHandle;
} scdbGPSConfig_t;

/************************************************************************************
 *************************************************************************************
 * Public memory declarations
 *************************************************************************************
 ************************************************************************************/

/************************************************************************************
 *************************************************************************************
 * Public prototypes
 *************************************************************************************
 ************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*!**********************************************************************************
 * \brief        Starts Smart Canton Dev Box Service functionality
 *
 * \param[in]    pServiceConfig  Pointer to structure that contains server
 *                               configuration information.
 * \param[in]    pServiceConfig  Pointer to structure that contains server
 *                               configuration information.
 *
 * \return       gBleSuccess_c or error.
 ************************************************************************************/
bleResult_t ScDbGPS_Start(scdbGPSConfig_t *pServiceConfig);

/*!**********************************************************************************
 * \brief        Stops Smart Canton Dev Box Service functionality
 *
 * \param[in]    pServiceConfig  Pointer to structure that contains server
 *                               configuration information.
 *
 * \return       gBleSuccess_c or error.
 ************************************************************************************/
bleResult_t ScDbGPS_Stop(scdbGPSConfig_t *pServiceConfig);

/*!**********************************************************************************
 * \brief        Subscribes a GATT client to the Smart Canton Dev Box service
 *
 * \param[in]    clientDeviceId  Client Id in Device DB.
 *
 * \return       gBleSuccess_c or error.
 ************************************************************************************/
bleResult_t ScDbGPS_Subscribe(deviceId_t clientDeviceId);

/*!**********************************************************************************
 * \brief        Unsubscribes a GATT client from the Smart Canton Dev Box service
 *
 * \return       gBleSuccess_c or error.
 ************************************************************************************/
bleResult_t ScDbGPS_Unsubscribe();

/*!**********************************************************************************
 * \brief        Record a new GPS position the GATT database and send a notification
 * \param[in]	 serviceHandle Handle to the Smart Canton Dev Box GPS service
 * \param[in]	 latitude New Latitude value
 * \param[in]	 longitude New Longitude value
 *
 * \return       gBleSuccess_c or error.
 ************************************************************************************/
bleResult_t ScDbGPS_RecordGPSPosition(uint16_t serviceHandle, float* latitude,
		float* longitude);

/*!**********************************************************************************
 * \brief        Record a new GPS speed the GATT database and send a notification
 * \param[in]	 serviceHandle Handle to the Smart Canton Dev Box GPS service
 * \param[in]	 speed New GPS speed
 *
 * \return       gBleSuccess_c or error.
 ************************************************************************************/
bleResult_t ScDbGPS_RecordGPSSpeed(uint16_t serviceHandle, float* speed);

/*!**********************************************************************************
 * \brief        Record a new GPS course the GATT database and send a notification
 * \param[in]	 serviceHandle Handle to the Smart Canton Dev Box GPS service
 * \param[in]	 course New GPS course
 *
 * \return       gBleSuccess_c or error.
 ************************************************************************************/
bleResult_t ScDbGPS_RecordGPSCourse(uint16_t serviceHandle, float* course);

/*!**********************************************************************************
 * \brief        Record a new GPS Time the GATT database and send a notification
 * \param[in]	 serviceHandle Handle to the Smart Canton Dev Box GPS service
 * \param[in]	 course New GPS time
 *
 * \return       gBleSuccess_c or error.
 ************************************************************************************/
bleResult_t ScDbGPS_RecordGPSTime(uint16_t serviceHandle, struct minmea_time *time);

/*!**********************************************************************************
 * \brief        Record a new GPS Date the GATT database and send a notification
 * \param[in]	 serviceHandle Handle to the Smart Canton Dev Box GPS service
 * \param[in]	 course New GPS Date
 *
 * \return       gBleSuccess_c or error.
 ************************************************************************************/
bleResult_t ScDbGPS_RecordGPSDate(uint16_t serviceHandle,
		struct minmea_date *date);


#ifdef __cplusplus
}
#endif

#endif /* _SMARTCANTON_DEVBOX_GPS_INTERFACE_H_ */

/*! **********************************************************************************
 * @}
 ************************************************************************************/