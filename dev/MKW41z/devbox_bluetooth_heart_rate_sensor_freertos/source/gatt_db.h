PRIMARY_SERVICE(service_device_information, gBleSig_DeviceInformationService_d)
    CHARACTERISTIC(char_manufacturer_name_string, gBleSig_ManufacturerNameString_d, (gGattCharPropRead_c))
        VALUE_VARLEN(value_manufacturer_name_string, gBleSig_ManufacturerNameString_d, (gPermissionFlagReadable_c), 23, 3, "NXP")
    CHARACTERISTIC(char_model_number_string, gBleSig_ModelNumberString_d, (gGattCharPropRead_c))
        VALUE_VARLEN(value_model_number_string, gBleSig_ModelNumberString_d, (gPermissionFlagReadable_c), 23, 3, "NXP")
    CHARACTERISTIC(char_serial_number_string, gBleSig_SerialNumberString_d, (gGattCharPropRead_c))
        VALUE_VARLEN(value_serial_number_string, gBleSig_SerialNumberString_d, (gPermissionFlagReadable_c), 23, 3, "NXP")
    CHARACTERISTIC(char_hardware_revision_string, gBleSig_HardwareRevisionString_d, (gGattCharPropRead_c))
        VALUE_VARLEN(value_hardware_revision_string, gBleSig_HardwareRevisionString_d, (gPermissionFlagReadable_c), 23, 3, "NXP")
    CHARACTERISTIC(char_firmware_revision_string, gBleSig_FirmwareRevisionString_d, (gGattCharPropRead_c))
        VALUE_VARLEN(value_firmware_revision_string, gBleSig_FirmwareRevisionString_d, (gPermissionFlagReadable_c), 23, 3, "NXP")
    CHARACTERISTIC(char_software_revision_string, gBleSig_SoftwareRevisionString_d, (gGattCharPropRead_c))
        VALUE_VARLEN(value_software_revision_string, gBleSig_SoftwareRevisionString_d, (gPermissionFlagReadable_c), 23, 3, "NXP")
    CHARACTERISTIC(char_system_id, gBleSig_SystemId_d, (gGattCharPropRead_c))
        VALUE(value_system_id, gBleSig_SystemId_d, (gPermissionFlagReadable_c), 8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
    CHARACTERISTIC(char_ieee_1107320601_regulatory_certification_data_list, gBleSig_IeeeRcdl_d, (gGattCharPropRead_c))
        VALUE_VARLEN(value_ieee_1107320601_regulatory_certification_data_list, gBleSig_IeeeRcdl_d, (gPermissionFlagReadable_c), 23, 3, "NXP")
    CHARACTERISTIC(char_pnp_id, gBleSig_PnpId_d, (gGattCharPropRead_c))
        VALUE(value_pnp_id, gBleSig_PnpId_d, (gPermissionFlagReadable_c), 7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)

PRIMARY_SERVICE(service_battery, gBleSig_BatteryService_d)
    CHARACTERISTIC(char_battery_level, gBleSig_BatteryLevel_d, (gGattCharPropNotify_c | gGattCharPropRead_c))
        VALUE(value_battery_level, gBleSig_BatteryLevel_d, (gPermissionFlagReadable_c), 1, 0x00)
        DESCRIPTOR(descriptor_battery_level, gBleSig_CharPresFormatDescriptor_d, (gPermissionFlagReadable_c), 7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
        CCCD(cccd_battery_level)

PRIMARY_SERVICE(service_generic_attribute, gBleSig_GenericAttributeProfile_d)
    CHARACTERISTIC(char_service_changed, gBleSig_GattServiceChanged_d, (gGattCharPropIndicate_c))
        VALUE(value_service_changed, gBleSig_GattServiceChanged_d, (gPermissionNone_c), 4, 0x00, 0x00, 0x00, 0x00)
        CCCD(cccd_service_changed)

PRIMARY_SERVICE(service_generic_access, gBleSig_GenericAccessProfile_d)
    CHARACTERISTIC(char_device_name, gBleSig_GapDeviceName_d, (gGattCharPropRead_c | gGattCharPropWrite_c))
        VALUE_VARLEN(value_device_name, gBleSig_GapDeviceName_d, (gPermissionFlagReadable_c | gPermissionFlagWritable_c), 23, 17, "SmartCantonDevBox")
    CHARACTERISTIC(char_appearance, gBleSig_GapAppearance_d, (gGattCharPropRead_c))
        VALUE(value_appearance, gBleSig_GapAppearance_d, (gPermissionFlagReadable_c), 2, UuidArray(gUnknown_c))
    CHARACTERISTIC(char_peripheral_preferred_connection_parameters, gBleSig_GapPpcp_d, (gGattCharPropRead_c))
        VALUE(value_peripheral_preferred_connection_parameters, gBleSig_GapPpcp_d, (gPermissionFlagReadable_c), 8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)

PRIMARY_SERVICE_UUID128(service_smartcanton_devbox, uuid_service_smartcanton_devbox)
	CHARACTERISTIC_UUID128(char_lora_app_eui, uuid_lora_app_eui, (gGattCharPropRead_c | gGattCharPropWrite_c))
		VALUE_UUID128_VARLEN(value_lora_app_eui, uuid_lora_app_eui, (gPermissionFlagReadable_c | gPermissionFlagWritable_c), 8, 8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
		DESCRIPTOR(descriptor_lora_app_eui, 0x2901, (gPermissionFlagReadable_c), 24, "LoRaWAN Application EUI")
	CHARACTERISTIC_UUID128(char_lora_app_key, uuid_lora_app_key, (gGattCharPropRead_c | gGattCharPropWrite_c))
		VALUE_UUID128_VARLEN(value_lora_app_key, uuid_lora_app_key, (gPermissionFlagReadable_c | gPermissionFlagWritable_c), 16, 16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
		DESCRIPTOR(descriptor_lora_app_key, 0x2901, (gPermissionFlagReadable_c), 24, "LoRaWAN Application Key")
	CHARACTERISTIC_UUID128(char_lora_device_eui, uuid_lora_device_eui, (gGattCharPropRead_c))
		VALUE_UUID128_VARLEN(value_lora_device_eui, uuid_lora_device_eui, (gPermissionFlagReadable_c), 8, 8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
		DESCRIPTOR(descriptor_lora_device_eui, 0x2901, (gPermissionFlagReadable_c), 19, "LoRaWAN Device EUI")
	CHARACTERISTIC_UUID128(char_lora_confirm_mode, uuid_lora_confirm_mode, (gGattCharPropRead_c | gGattCharPropWrite_c))
		VALUE_UUID128(value_lora_confirm_mode, uuid_lora_confirm_mode, (gPermissionFlagReadable_c | gPermissionFlagWritable_c), 1, 0x00)
		DESCRIPTOR(descriptor_lora_confirm_mode, 0x2901, (gPermissionFlagReadable_c), 26, "LoRaWAN Confirmation Mode")
	CHARACTERISTIC_UUID128(char_lora_network_join_status, uuid_lora_network_join_status, (gGattCharPropRead_c))
		VALUE_UUID128(value_lora_network_join_status, uuid_lora_network_join_status, (gPermissionFlagReadable_c), 1, 0x00)
		DESCRIPTOR(descriptor_lora_network_join_status, 0x2901, (gPermissionFlagReadable_c), 28, "LoRaWAN Network Join Status")
	CHARACTERISTIC_UUID128(char_lora_device_address, uuid_lora_device_address, (gGattCharPropRead_c))
		VALUE_UUID128_VARLEN(value_lora_device_address, uuid_lora_device_address, (gPermissionFlagReadable_c), 4, 4, 0x00, 0x00, 0x00, 0x00)
		DESCRIPTOR(descriptor_lora_device_address, 0x2901, (gPermissionFlagReadable_c), 23, "LoRaWAN Device Address")
	CHARACTERISTIC_UUID128(char_lora_network_session_key, uuid_lora_network_session_key, (gGattCharPropRead_c))
		VALUE_UUID128_VARLEN(value_lora_network_session_key, uuid_lora_network_session_key, (gPermissionFlagReadable_c), 16, 16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
		DESCRIPTOR(descriptor_lora_network_session_key, 0x2901, (gPermissionFlagReadable_c), 28, "LoRaWAN Network Session Key")
	CHARACTERISTIC_UUID128(char_lora_app_session_key, uuid_lora_app_session_key, (gGattCharPropRead_c))
		VALUE_UUID128_VARLEN(value_lora_app_session_key, uuid_lora_app_session_key, (gPermissionFlagReadable_c), 16, 16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
		DESCRIPTOR(descriptor_lora_app_session_key, 0x2901, (gPermissionFlagReadable_c), 24, "LoRaWAN App Session Key")
	CHARACTERISTIC_UUID128(char_lora_validate_new_configuration, uuid_lora_validate_new_configuration, (gGattCharPropWrite_c))
		VALUE_UUID128(value_lora_validate_new_configuration, uuid_lora_validate_new_configuration, (gPermissionFlagWritable_c), 1, 0x00)
		DESCRIPTOR(descriptor_lora_validate_new_configuration, 0x2901, (gPermissionFlagReadable_c), 35, "LoRaWAN Validate New Configuration")
