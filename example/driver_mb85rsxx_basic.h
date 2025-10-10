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
 * @file      driver_mb85rsxx_basic.h
 * @brief     driver mb85rsxx basic header file
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

#ifndef DRIVER_MB85RSXX_BASIC_H
#define DRIVER_MB85RSXX_BASIC_H

#include "driver_mb85rsxx_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup mb85rsxx_example_driver mb85rsxx example driver function
 * @brief    mb85rsxx example driver modules
 * @ingroup  mb85rsxx_driver
 * @{
 */

/**
 * @brief     basic example init
 * @param[in] type chip type
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t mb85rsxx_basic_init(mb85rsxx_t type);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t mb85rsxx_basic_deinit(void);

/**
 * @brief      basic example read
 * @param[in]  address register address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read data failed
 * @note       none
 */
uint8_t mb85rsxx_basic_read(uint32_t address, uint8_t *buf, uint16_t len);

/**
 * @brief     basic example write
 * @param[in] address register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write data failed
 * @note      none
 */
uint8_t mb85rsxx_basic_write(uint32_t address, uint8_t *buf, uint16_t len);

/**
 * @brief     basic example set status
 * @param[in] status set status
 * @return    status code
 *            - 0 success
 *            - 1 set status failed
 * @note      none
 */
uint8_t mb85rsxx_basic_set_status(uint8_t status);

/**
 * @brief      basic example get status
 * @param[out] *status pointer to a status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get status failed
 * @note       none
 */
uint8_t mb85rsxx_basic_get_status(uint8_t *status);

/**
 * @brief      basic example get device info
 * @param[out] *manufacturer_id pointer to a manufacturer id buffer
 * @param[out] *continuation_code pointer to a continuation code buffer
 * @param[out] *product_id1 pointer to a product id1 buffer
 * @param[out] *product_id2 pointer to a product id2 buffer
 * @return     status code
 *             - 0 success
 *             - 1 get device info failed
 * @note       none
 */
uint8_t mb85rsxx_basic_get_info(uint8_t *manufacturer_id, uint8_t *continuation_code,
                                uint8_t *product_id1, uint8_t *product_id2);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
