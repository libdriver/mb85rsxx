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
 * @file      driver_mb85rsxx_read_test.c
 * @brief     driver mb85rsxx read test source file
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
 
#include "driver_mb85rsxx_read_test.h"
#include <stdlib.h>

static mb85rsxx_handle_t gs_handle;        /**< mb85rsxx handle */

/**
 * @brief     read test
 * @param[in] type chip type
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t mb85rsxx_read_test(mb85rsxx_t type)
{
    uint8_t res, i, j;
    uint8_t status;
    uint8_t manufacturer_id;
    uint8_t continuation_code;
    uint8_t product_id1;
    uint8_t product_id2;
    uint8_t buf[12];
    uint8_t buf_check[12];
    uint32_t inc;
    mb85rsxx_info_t info;
    
    /* link interface function */
    DRIVER_MB85RSXX_LINK_INIT(&gs_handle, mb85rsxx_handle_t);
    DRIVER_MB85RSXX_LINK_SPI_INIT(&gs_handle, mb85rsxx_interface_spi_init);
    DRIVER_MB85RSXX_LINK_SPI_DEINIT(&gs_handle, mb85rsxx_interface_spi_deinit);
    DRIVER_MB85RSXX_LINK_SPI_READ_WRITE(&gs_handle, mb85rsxx_interface_spi_read_write);
    DRIVER_MB85RSXX_LINK_DELAY_MS(&gs_handle, mb85rsxx_interface_delay_ms);
    DRIVER_MB85RSXX_LINK_DEBUG_PRINT(&gs_handle, mb85rsxx_interface_debug_print);
    
    /* get information */
    res = mb85rsxx_info(&info);
    if (res != 0)
    {
        mb85rsxx_interface_debug_print("mb85rsxx: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        mb85rsxx_interface_debug_print("mb85rsxx: chip is %s.\n", info.chip_name);
        mb85rsxx_interface_debug_print("mb85rsxx: manufacturer is %s.\n", info.manufacturer_name);
        mb85rsxx_interface_debug_print("mb85rsxx: interface is %s.\n", info.interface);
        mb85rsxx_interface_debug_print("mb85rsxx: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        mb85rsxx_interface_debug_print("mb85rsxx: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        mb85rsxx_interface_debug_print("mb85rsxx: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        mb85rsxx_interface_debug_print("mb85rsxx: max current is %0.2fmA.\n", info.max_current_ma);
        mb85rsxx_interface_debug_print("mb85rsxx: max temperature is %0.1fC.\n", info.temperature_max);
        mb85rsxx_interface_debug_print("mb85rsxx: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
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
    
#if (MB85RSXX_USE_DEVICE_ID != 0)
    /* get device id */
    res = mb85rsxx_get_device_id(&gs_handle, &manufacturer_id, &continuation_code, &product_id1, &product_id2);
    if (res != 0)
    {
        mb85rsxx_interface_debug_print("mb85rsxx: get device id failed.\n");
        (void)mb85rsxx_deinit(&gs_handle);
        
        return 1;
    }
    mb85rsxx_interface_debug_print("mb85rsxx: manufacturer id is 0x%02X.\n", manufacturer_id);
    mb85rsxx_interface_debug_print("mb85rsxx: continuation code is 0x%02X.\n", continuation_code);
    mb85rsxx_interface_debug_print("mb85rsxx: product id1 is 0x%02X.\n", product_id1);
    mb85rsxx_interface_debug_print("mb85rsxx: product id2 is 0x%02X.\n", product_id2);
#endif
    
    /* get status */
    res = mb85rsxx_get_status(&gs_handle, &status);
    if (res != 0)
    {
        mb85rsxx_interface_debug_print("mb85rsxx: get status failed.\n");
        (void)mb85rsxx_deinit(&gs_handle);
        
        return 1;
    }
    mb85rsxx_interface_debug_print("mb85rsxx: status 0x%02X.\n", status);
    
    /* start read test */
    mb85rsxx_interface_debug_print("mb85rsxx: start read test.\n");
    inc = (uint32_t)type / 8;
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 12; j++)
        {
            buf[j] = (uint8_t)(rand() % 256);
        }
    
        /* write data */
        res = mb85rsxx_write(&gs_handle, i * inc, (uint8_t *)buf, 12);
        if (res != 0)
        {
            mb85rsxx_interface_debug_print("mb85rsxx: write failed.\n");
            (void)mb85rsxx_deinit(&gs_handle);
            
            return 1;
        }

        /* read data */
        res = mb85rsxx_read(&gs_handle, i * inc, (uint8_t *)buf_check, 12);
        if (res != 0)
        {
            mb85rsxx_interface_debug_print("mb85rsxx: read failed.\n");
            (void)mb85rsxx_deinit(&gs_handle);
            
            return 1;
        }
        for (j = 0; j < 12; j++)
        {
            /* check data */
            if (buf[j] != buf_check[j])
            {
                mb85rsxx_interface_debug_print("mb85rsxx: check error.\n");
                (void)mb85rsxx_deinit(&gs_handle);
                
                return 1;
            }
        }
        mb85rsxx_interface_debug_print("mb85rsxx: 0x%04X read write test passed.\n", i * inc);
    }

    /* finish read test */
    mb85rsxx_interface_debug_print("mb85rsxx: finish read test.\n");
    (void)mb85rsxx_deinit(&gs_handle);
    
    return 0;
}
