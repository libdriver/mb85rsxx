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
 * @file      driver_mb85rsxx_basic.c
 * @brief     driver mb85rsxx basic source file
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

#include "driver_mb85rsxx_basic.h"

static mb85rsxx_handle_t gs_handle;        /**< mb85rsxx handle */

/**
 * @brief     basic example init
 * @param[in] type chip type
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t mb85rsxx_basic_init(mb85rsxx_t type)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_MB85RSXX_LINK_INIT(&gs_handle, mb85rsxx_handle_t);
    DRIVER_MB85RSXX_LINK_SPI_INIT(&gs_handle, mb85rsxx_interface_spi_init);
    DRIVER_MB85RSXX_LINK_SPI_DEINIT(&gs_handle, mb85rsxx_interface_spi_deinit);
    DRIVER_MB85RSXX_LINK_SPI_READ_WRITE(&gs_handle, mb85rsxx_interface_spi_read_write);
    DRIVER_MB85RSXX_LINK_DELAY_MS(&gs_handle, mb85rsxx_interface_delay_ms);
    DRIVER_MB85RSXX_LINK_DEBUG_PRINT(&gs_handle, mb85rsxx_interface_debug_print);
    
    /* set chip type */
    res = mb85rsxx_set_type(&gs_handle, type);
    if (res != 0)
    {
        mb85rsxx_interface_debug_print("mb85rsxx: set type failed.\n");
       
        return 1;
    }
    
    /* mb85rsxx init */
    res = mb85rsxx_init(&gs_handle);
    if (res != 0)
    {
        mb85rsxx_interface_debug_print("mb85rsxx: init failed.\n");
       
        return 1;
    }

    return 0;
}

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
uint8_t mb85rsxx_basic_read(uint32_t address, uint8_t *buf, uint16_t len)
{
    /* read data */
    if (mb85rsxx_read(&gs_handle, address, buf, len) != 0)
    {
        return 1;
    }
    
    return 0;
}

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
uint8_t mb85rsxx_basic_write(uint32_t address, uint8_t *buf, uint16_t len)
{
    /* write data */
    if (mb85rsxx_write(&gs_handle, address, buf, len) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t mb85rsxx_basic_deinit(void)
{
    /* mb85rsxx deinit */
    if (mb85rsxx_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example set status
 * @param[in] status set status
 * @return    status code
 *            - 0 success
 *            - 1 set status failed
 * @note      none
 */
uint8_t mb85rsxx_basic_set_status(uint8_t status)
{
    /* set status */
    if (mb85rsxx_set_status(&gs_handle, status) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example get status
 * @param[out] *status pointer to a status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get status failed
 * @note       none
 */
uint8_t mb85rsxx_basic_get_status(uint8_t *status)
{
    /* get status */
    if (mb85rsxx_get_status(&gs_handle, status) != 0)
    {
        return 1;
    }
    
    return 0;
}

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
                                uint8_t *product_id1, uint8_t *product_id2)
{
    /* get device id */
    if (mb85rsxx_get_device_id(&gs_handle, manufacturer_id, continuation_code,
                               product_id1, product_id2) != 0)
    {
        return 1;
    }
    
    return 0;
}
