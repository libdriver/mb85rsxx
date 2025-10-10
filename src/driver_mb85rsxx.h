/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_mb85rsxx.h
 * @brief     driver mb85rsxx header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2025-10-15
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2025/10/15  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_MB85RSXX_H
#define DRIVER_MB85RSXX_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup mb85rsxx_driver mb85rsxx driver function
 * @brief    mb85rsxx driver modules
 * @{
 */

/**
 * @addtogroup mb85rsxx_base_driver
 * @{
 */

/**
 * @brief mb85rsxx use device id definition
 */
#ifndef MB85RSXX_USE_DEVICE_ID
    #define MB85RSXX_USE_DEVICE_ID        1        /**< some types of chip can't use device id function and
                                                        set this definition to 0 to skip device id checking. 
                                                        default setting is enable */
#endif

/**
 * @brief mb85rsxx type enumeration definition
 */
typedef enum
{
    MB85RS16  = 2048,          /**< MB85RS16 type */
    MB85RS64  = 8192,          /**< MB85RS64 type */
    MB85RS128 = 16384,         /**< MB85RS128 type */
    MB85RS256 = 32768,         /**< MB85RS256 type */
    MB85RS512 = 65536,         /**< MB85RS512 type */
    MB85RS1M  = 131072,        /**< MB85RS1M type */
    MB85RS2M  = 262144,        /**< MB85RS2M type */
    MB85RS4M  = 524288,        /**< MB85RS4M type */
} mb85rsxx_t;

/**
 * @brief mb85rsxx status enumeration definition
 */
typedef enum
{
    MB85RSXX_STATUS_WPEN = (1 << 7),        /**< status register write protect */
    MB85RSXX_STATUS_BP1 = (1 << 3),         /**< block protect 1 */
    MB85RSXX_STATUS_BP0 = (1 << 2),         /**< block protect 0 */
    MB85RSXX_STATUS_WEL = (1 << 1),         /**< write enable latch */
} mb85rsxx_status_t;

/**
 * @brief mb85rsxx handle structure definition
 */
typedef struct mb85rsxx_handle_s
{
    uint8_t (*spi_init)(void);                                            /**< point to a spi_init function address */
    uint8_t (*spi_deinit)(void);                                          /**< point to a spi_deinit function address */
    uint8_t (*spi_read_write)(uint8_t *in_buf, uint32_t in_len, 
                              uint8_t *out_buf, uint32_t out_len);        /**< point to a spi_read_write function address */
    void (*delay_ms)(uint32_t ms);                                        /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                      /**< point to a debug_print function address */
    uint32_t id;                                                          /**< chip id */
    uint8_t inited;                                                       /**< inited flag */
    uint8_t buf[512 + 4];                                                 /**< inner buffer */
} mb85rsxx_handle_t;

/**
 * @brief mb85rsxx information structure definition
 */
typedef struct mb85rsxx_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} mb85rsxx_info_t;

/**
 * @}
 */

/**
 * @defgroup mb85rsxx_link_driver mb85rsxx link driver function
 * @brief    mb85rsxx link driver modules
 * @ingroup  mb85rsxx_driver
 * @{
 */

/**
 * @brief     initialize mb85rsxx_handle_t structure
 * @param[in] HANDLE pointer to a mb85rsxx handle structure
 * @param[in] STRUCTURE mb85rsxx_handle_t
 * @note      none
 */
#define DRIVER_MB85RSXX_LINK_INIT(HANDLE, STRUCTURE)           memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link spi_init function
 * @param[in] HANDLE pointer to a mb85rsxx handle structure
 * @param[in] FUC pointer to a spi_init function address
 * @note      none
 */
#define DRIVER_MB85RSXX_LINK_SPI_INIT(HANDLE, FUC)             (HANDLE)->spi_init = FUC

/**
 * @brief     link spi_deinit function
 * @param[in] HANDLE pointer to a mb85rsxx handle structure
 * @param[in] FUC pointer to a spi_deinit function address
 * @note      none
 */
#define DRIVER_MB85RSXX_LINK_SPI_DEINIT(HANDLE, FUC)           (HANDLE)->spi_deinit = FUC

/**
 * @brief     link spi_read_write function
 * @param[in] HANDLE pointer to a mb85rsxx handle structure
 * @param[in] FUC pointer to a spi_read_write function address
 * @note      none
 */
#define DRIVER_MB85RSXX_LINK_SPI_READ_WRITE(HANDLE, FUC)       (HANDLE)->spi_read_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to a mb85rsxx handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_MB85RSXX_LINK_DELAY_MS(HANDLE, FUC)             (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to a mb85rsxx handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_MB85RSXX_LINK_DEBUG_PRINT(HANDLE, FUC)          (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup mb85rsxx_base_driver mb85rsxx base driver function
 * @brief    mb85rsxx base driver modules
 * @ingroup  mb85rsxx_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a mb85rsxx info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t mb85rsxx_info(mb85rsxx_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to a mb85rsxx handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 id is invalid
 * @note      none
 */
uint8_t mb85rsxx_init(mb85rsxx_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle pointer to a mb85rsxx handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mb85rsxx_deinit(mb85rsxx_handle_t *handle);

/**
 * @brief     set the chip type
 * @param[in] *handle pointer to a mb85rsxx handle structure
 * @param[in] type chip type
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t mb85rsxx_set_type(mb85rsxx_handle_t *handle, mb85rsxx_t type);

/**
 * @brief      get the chip type
 * @param[in]  *handle pointer to a mb85rsxx handle structure
 * @param[out] *type pointer to a chip type buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t mb85rsxx_get_type(mb85rsxx_handle_t *handle, mb85rsxx_t *type);

/**
 * @brief      read bytes from the chip
 * @param[in]  *handle pointer to a mb85rsxx handle structure
 * @param[in]  address register address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read data failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 end address is over the max address
 * @note       none
 */
uint8_t mb85rsxx_read(mb85rsxx_handle_t *handle, uint32_t address, uint8_t *buf, uint16_t len);

/**
 * @brief     write bytes to the chip
 * @param[in] *handle pointer to a mb85rsxx handle structure
 * @param[in] address register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write data failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 end address is over the max address
 *            - 5 len > 512
 * @note      none
 */
uint8_t mb85rsxx_write(mb85rsxx_handle_t *handle, uint32_t address, uint8_t *buf, uint16_t len);

/**
 * @brief     enable write
 * @param[in] *handle pointer to a mb85rsxx handle structure
 * @return    status code
 *            - 0 success
 *            - 1 enable write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mb85rsxx_enable_write(mb85rsxx_handle_t *handle);

/**
 * @brief     disable write
 * @param[in] *handle pointer to a mb85rsxx handle structure
 * @return    status code
 *            - 0 success
 *            - 1 disable write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mb85rsxx_disable_write(mb85rsxx_handle_t *handle);

/**
 * @brief     set status
 * @param[in] *handle pointer to a mb85rsxx handle structure
 * @param[in] status set status
 * @return    status code
 *            - 0 success
 *            - 1 set status failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mb85rsxx_set_status(mb85rsxx_handle_t *handle, uint8_t status);

/**
 * @brief      get status
 * @param[in]  *handle pointer to a mb85rsxx handle structure
 * @param[out] *status pointer to a status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mb85rsxx_get_status(mb85rsxx_handle_t *handle, uint8_t *status);

/**
 * @brief      get device id
 * @param[in]  *handle pointer to a mb85rsxx handle structure
 * @param[out] *manufacturer_id pointer to a manufacturer id buffer
 * @param[out] *continuation_code pointer to a continuation code buffer
 * @param[out] *product_id1 pointer to a product id1 buffer
 * @param[out] *product_id2 pointer to a product id2 buffer
 * @return     status code
 *             - 0 success
 *             - 1 get device id failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mb85rsxx_get_device_id(mb85rsxx_handle_t *handle, uint8_t *manufacturer_id, uint8_t *continuation_code,
                               uint8_t *product_id1, uint8_t *product_id2);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
