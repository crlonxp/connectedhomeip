/*******************************************************************************
 * @file  wfx_sl_ble_init.h
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 *    Copyright (c) 2022 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
#pragma once

// BLE include file to refer BLE APIs
#include "ble_config.h"
#include "cmsis_os2.h"
#include <stdbool.h>
#include <string.h>

extern "C" {
#include <rsi_ble.h>
#include <rsi_ble_apis.h>
#include <rsi_ble_common_config.h>
#include <rsi_bt_common.h>
#include <rsi_bt_common_apis.h>
#include <rsi_common_apis.h>
}

#define ATT_REC_IN_HOST (0)
#define WFX_QUEUE_SIZE 10

#define RSI_BT_CTRL_REMOTE_USER_TERMINATED (0x4E13)
#define RSI_BT_CTRL_REMOTE_DEVICE_TERMINATED_CONNECTION_DUE_TO_LOW_RESOURCES (0x4E14)
#define RSI_BT_CTRL_REMOTE_POWERING_OFF (0x4E15)
#define RSI_BT_CTRL_TERMINATED_MIC_FAILURE (0x4E3D)
#define RSI_BT_FAILED_TO_ESTABLISH_CONN (0x4E3E)
#define RSI_BT_INVALID_RANGE (0x4E60)

#define RSI_BLE_MATTER_CUSTOM_SERVICE_UUID (0)
#define RSI_BLE_MATTER_CUSTOM_SERVICE_SIZE (2)
#define RSI_BLE_MATTER_CUSTOM_SERVICE_VALUE_16 (0xFFF6)
#define RSI_BLE_MATTER_CUSTOM_SERVICE_DATA (0x00)

#define RSI_BLE_CUSTOM_CHARACTERISTIC_RX_SIZE (16)
#define RSI_BLE_CUSTOM_CHARACTERISTIC_RX_RESERVED 0x00, 0x00, 0x00
#define RSI_BLE_CUSTOM_CHARACTERISTIC_RX_VALUE_128_DATA_1 0x18EE2EF5
#define RSI_BLE_CUSTOM_CHARACTERISTIC_RX_VALUE_128_DATA_2 0x263D
#define RSI_BLE_CUSTOM_CHARACTERISTIC_RX_VALUE_128_DATA_3 0x4559
#define RSI_BLE_CUSTOM_CHARACTERISTIC_RX_VALUE_128_DATA_4 0x9F, 0x95, 0x9C, 0x4F, 0x11, 0x9D, 0x9F, 0x42
#define RSI_BLE_CHARACTERISTIC_RX_ATTRIBUTE_HANDLE_LOCATION (1)
#define RSI_BLE_CHARACTERISTIC_RX_VALUE_HANDLE_LOCATION (2)

#define RSI_BLE_CUSTOM_CHARACTERISTIC_TX_SIZE (16)
#define RSI_BLE_CUSTOM_CHARACTERISTIC_TX_RESERVED 0x00, 0x00, 0x00
#define RSI_BLE_CUSTOM_CHARACTERISTIC_TX_VALUE_128_DATA_1 0x18EE2EF5
#define RSI_BLE_CUSTOM_CHARACTERISTIC_TX_VALUE_128_DATA_2 0x263D
#define RSI_BLE_CUSTOM_CHARACTERISTIC_TX_VALUE_128_DATA_3 0x4559
#define RSI_BLE_CUSTOM_CHARACTERISTIC_TX_VALUE_128_DATA_4 0x9F, 0x95, 0x9C, 0x4F, 0x12, 0x9D, 0x9F, 0x42
#define RSI_BLE_CHARACTERISTIC_TX_ATTRIBUTE_HANDLE_LOCATION (3)
#define RSI_BLE_CHARACTERISTIC_TX_MEASUREMENT_HANDLE_LOCATION (4)
#define RSI_BLE_CHARACTERISTIC_TX_GATT_SERVER_CLIENT_HANDLE_LOCATION (5)

#ifdef CHIP_ENABLE_ADDITIONAL_DATA_ADVERTISING
#define RSI_BLE_CHAR_C3_UUID_SIZE (16)
#define RSI_BLE_CHAR_C3_RESERVED 0x00, 0x00, 0x00
#define RSI_BLE_CHAR_C3_UUID_1 0x64630238
#define RSI_BLE_CHAR_C3_UUID_2 0x8772
#define RSI_BLE_CHAR_C3_UUID_3 0x45f2
#define RSI_BLE_CHAR_C3_UUID_4 0x7D, 0xB8, 0x8A, 0x74, 0x04, 0x8F, 0x21, 0x83
#define RSI_BLE_CHAR_C3_ATTR_HANDLE_LOC (6)
#define RSI_BLE_CHAR_C3_MEASUREMENT_HANDLE_LOC (7)
#define RSI_BLE_CHAR_C3_GATT_SERVER_CLI_HANDLE_LOC (8)
#endif
namespace chip {
namespace DeviceLayer {
namespace Internal {

class SilabsBleWrapper
{
public:
    enum class BleEventType : uint8_t
    {
        RSI_BLE_CONN_EVENT,
        RSI_BLE_DISCONN_EVENT,
        RSI_BLE_GATT_WRITE_EVENT,
        RSI_BLE_MTU_EVENT,
        RSI_BLE_GATT_INDICATION_CONFIRMATION,
        RSI_BLE_RESP_ATT_VALUE,
        RSI_BLE_EVENT_GATT_RD
    };

    struct sl_wfx_msg_t
    {
        uint8_t connectionHandle;
        uint8_t bondingHandle;
        uint16_t reason;
        uint16_t event_id;
        uint16_t resp_status;
        rsi_ble_event_mtu_t rsi_ble_mtu;
        rsi_ble_event_write_t rsi_ble_write;
        rsi_ble_event_enhance_conn_status_t resp_enh_conn;
        rsi_ble_event_disconnect_t * resp_disconnect;
        rsi_ble_read_req_t * rsi_ble_read_req;
        rsi_ble_set_att_resp_t rsi_ble_event_set_att_rsp;
        uint16_t subscribed;
    };

    struct BleEvent_t
    {
        BleEventType eventType;
        sl_wfx_msg_t eventData;
    };

    // ALL Ble functions
    static void rsi_ble_on_connect_event(rsi_ble_event_conn_status_t * resp_conn);
    static void rsi_ble_on_disconnect_event(rsi_ble_event_disconnect_t * resp_disconnect, uint16_t reason);
    static void rsi_ble_on_enhance_conn_status_event(rsi_ble_event_enhance_conn_status_t * resp_enh_conn);
    static void rsi_ble_on_gatt_write_event(uint16_t event_id, rsi_ble_event_write_t * rsi_ble_write);
    static void rsi_ble_on_mtu_event(rsi_ble_event_mtu_t * rsi_ble_mtu);
    static void rsi_ble_on_event_indication_confirmation(uint16_t resp_status, rsi_ble_set_att_resp_t * rsi_ble_event_set_att_rsp);
    static void rsi_ble_on_read_req_event(uint16_t event_id, rsi_ble_read_req_t * rsi_ble_read_req);
    static void rsi_gatt_add_attribute_to_list(rsi_ble_t * p_val, uint16_t handle, uint16_t data_len, uint8_t * data, uuid_t uuid,
                                               uint8_t char_prop);
    static void rsi_ble_add_char_serv_att(void * serv_handler, uint16_t handle, uint8_t val_prop, uint16_t att_val_handle,
                                          uuid_t att_val_uuid);
    static void rsi_ble_add_char_val_att(void * serv_handler, uint16_t handle, uuid_t att_type_uuid, uint8_t val_prop,
                                         uint8_t * data, uint8_t data_len, uint8_t auth_read);
};

} // namespace Internal
} // namespace DeviceLayer
} // namespace chip
