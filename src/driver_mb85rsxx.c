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
 * @file      driver_mb85rsxx.c
 * @brief     driver mb85rsxx source file
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

#include "driver_mb85rsxx.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "RAMXEED MB85RSXX"        /**< chip name */
#define MANUFACTURER_NAME         "RAMXEED"                 /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        1.8f                      /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.5f                      /**< chip max supply voltage */
#define MAX_CURRENT               2.6f                      /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                    /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                     /**< chip max operating temperature */
#define DRIVER_VERSION            1000                      /**< driver version */

/**
 * @brief chip command definition
 */
#define MB85RSXX_COMMAND_WREN         0x06        /**< set write enable latch command */
#define MB85RSXX_COMMAND_WRDI         0x04        /**< reset write enable latch command */
#define MB85RSXX_COMMAND_RDSR         0x05        /**< read status register command */
#define MB85RSXX_COMMAND_WRSR         0x01        /**< write status register command */
#define MB85RSXX_COMMAND_READ         0x03        /**< read memory code command */
#define MB85RSXX_COMMAND_WRITE        0x02        /**< write memory code command */
#define MB85RSXX_COMMAND_RDID         0x9F        /**< read device id command */

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
uint8_t mb85rsxx_enable_write(mb85rsxx_handle_t *handle)
{
    uint8_t res;
    uint8_t buf[1];
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    buf[0] = MB85RSXX_COMMAND_WREN;                                     /* set command */
    res = handle->spi_read_write(buf, 1, NULL, 0);                      /* write command */
    if (res != 0)                                                       /* check the result */
    {
        handle->debug_print("mb85rsxx: enable write failed.\n");        /* enable write failed */
       
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t mb85rsxx_disable_write(mb85rsxx_handle_t *handle)
{
    uint8_t res;
    uint8_t buf[1];
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    buf[0] = MB85RSXX_COMMAND_WRDI;                                     /* set command */
    res = handle->spi_read_write(buf, 1, NULL, 0);                      /* write command */
    if (res != 0)                                                       /* check the result */
    {
        handle->debug_print("mb85rsxx: disable write failed.\n");       /* disable write failed */
       
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

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
uint8_t mb85rsxx_get_status(mb85rsxx_handle_t *handle, uint8_t *status)
{
    uint8_t res;
    uint8_t buf[1];
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    buf[0] = MB85RSXX_COMMAND_RDSR;                                   /* set command */
    res = handle->spi_read_write(buf, 1, status, 1);                  /* write command */
    if (res != 0)                                                     /* check the result */
    {
        handle->debug_print("mb85rsxx: get status failed.\n");        /* get status failed */
       
        return 1;                                                     /* return error */
    }
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t mb85rsxx_set_status(mb85rsxx_handle_t *handle, uint8_t status)
{
    uint8_t res;
    uint8_t buf[2];
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    buf[0] = MB85RSXX_COMMAND_WREN;                                   /* set command */
    res = handle->spi_read_write(buf, 1, NULL, 0);                    /* write command */
    if (res != 0)                                                     /* check the result */
    {
        handle->debug_print("mb85rsxx: enable write failed.\n");      /* enable write failed */
       
        return 1;                                                     /* return error */
    }
    
    buf[0] = MB85RSXX_COMMAND_WRSR;                                   /* set command */
    buf[1] = status;                                                  /* set status */
    res = handle->spi_read_write(buf, 2, NULL, 0);                    /* write command */
    if (res != 0)                                                     /* check the result */
    {
        handle->debug_print("mb85rsxx: set status failed.\n");        /* set status failed */
       
        return 1;                                                     /* return error */
    }
    
    buf[0] = MB85RSXX_COMMAND_WRDI;                                   /* set command */
    res = handle->spi_read_write(buf, 1, NULL, 0);                    /* write command */
    if (res != 0)                                                     /* check the result */
    {
        handle->debug_print("mb85rsxx: disable write failed.\n");     /* disable write failed */
       
        return 1;                                                     /* return error */
    }
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t mb85rsxx_init(mb85rsxx_handle_t *handle)
{
    uint8_t res;
    uint8_t ind;
    uint8_t buf[1];
    uint8_t number[4];
    const uint32_t density[] = {1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288};
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->debug_print == NULL)                                           /* check debug_print */
    {
        return 3;                                                              /* return error */
    }
    if (handle->spi_init == NULL)                                              /* check spi_init */
    {
        handle->debug_print("mb85rsxx: spi_init is null.\n");                  /* spi_init is null */
       
        return 3;                                                              /* return error */
    }
    if (handle->spi_deinit == NULL)                                            /* check spi_deinit */
    {
        handle->debug_print("mb85rsxx: spi_deinit is null.\n");                /* spi_deinit is null */
       
        return 3;                                                              /* return error */
    }
    if (handle->spi_read_write == NULL)                                        /* check spi_read_write */
    {
        handle->debug_print("mb85rsxx: spi_read_write is null.\n");            /* spi_read_write is null */
       
        return 3;                                                              /* return error */
    }
    if (handle->delay_ms == NULL)                                              /* check delay_ms */
    {
        handle->debug_print("mb85rsxx: delay_ms is null.\n");                  /* delay_ms is null */
       
        return 3;                                                              /* return error */
    }

    if (handle->spi_init() != 0)                                               /* spi init */
    {
        handle->debug_print("mb85rsxx: spi init failed.\n");                   /* spi init failed */
       
        return 1;                                                              /* return error */
    }
#if (MB85RSXX_USE_DEVICE_ID != 0)
    buf[0] = MB85RSXX_COMMAND_RDID;                                            /* set command */
    res = handle->spi_read_write(buf, 1, number, 4);                           /* write command */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("mb85rsxx: get id failed.\n");                     /* get id failed */
        (void)handle->spi_deinit();                                            /* spi deinit */
        
        return 4;                                                              /* return error */
    }
    if ((number[0] != 0x04) || (number[1] != 0x7F))                            /* check id */
    {
        handle->debug_print("mb85rsxx: id is invalid.\n");                     /* id is invalid */
        (void)handle->spi_deinit();                                            /* spi deinit */
        
        return 4;                                                              /* return error */
    }
    ind = number[2] & 0x1F;                                                    /* set index */
    if (ind > 9)                                                               /* check index range */
    {
        handle->debug_print("mb85rsxx: id is invalid.\n");                     /* id is invalid */
        (void)handle->spi_deinit();                                            /* spi deinit */
        
        return 4;                                                              /* return error */
    }
    if (density[ind] != handle->id)                                            /* check density */
    {
        handle->debug_print("mb85rsxx: id is invalid.\n");                     /* id is invalid */
        (void)handle->spi_deinit();                                            /* spi deinit */
        
        return 4;                                                              /* return error */
    }
#endif
    handle->inited = 1;                                                        /* flag finish initialization */

    return 0;                                                                  /* success return 0 */
}

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
uint8_t mb85rsxx_deinit(mb85rsxx_handle_t *handle)
{
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (handle->spi_deinit() != 0)                                   /* spi deinit */
    {
        handle->debug_print("mb85rsxx: spi deinit failed.\n");       /* spi deinit failed */
        
        return 1;                                                    /* return error */
    }   
    handle->inited = 0;                                              /* flag close */
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief     set the chip type
 * @param[in] *handle pointer to a mb85rsxx handle structure
 * @param[in] type chip type
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t mb85rsxx_set_type(mb85rsxx_handle_t *handle, mb85rsxx_t type)
{
    if (handle == NULL)                 /* check handle */
    {
        return 2;                       /* return error */
    }

    handle->id = (uint32_t)type;        /* set id */
    
    return 0;                           /* success return 0 */
}

/**
 * @brief      get the chip type
 * @param[in]  *handle pointer to a mb85rsxx handle structure
 * @param[out] *type pointer to a chip type buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t mb85rsxx_get_type(mb85rsxx_handle_t *handle, mb85rsxx_t *type)
{
    if (handle == NULL)                     /* check handle */
    {
        return 2;                           /* return error */
    }

    *type = (mb85rsxx_t)(handle->id);       /* get id */
    
    return 0;                               /* success return 0 */
}

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
uint8_t mb85rsxx_read(mb85rsxx_handle_t *handle, uint32_t address, uint8_t *buf, uint16_t len)
{
    uint8_t res;
    uint8_t reg[4];
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    if ((address + len) > handle->id)                                 /* check length */
    {
        handle->debug_print("mb85rsxx: read out of range.\n");        /* read out of range */
       
        return 4;                                                     /* return error */
    }

    if (handle->id > (uint32_t)MB85RS512)                             /* choose id to set different address */
    {
        reg[0] = MB85RSXX_COMMAND_READ;                               /* set command */
        reg[1] = (address >> 16) & 0xFF;                              /* address msb */
        reg[2] = (address >> 8) & 0xFF;                               /* address mmsb */
        reg[3] = (address >> 0) & 0xFF;                               /* address lsb */
        res = handle->spi_read_write(reg, 4, buf, len);               /* read data */
        if (res != 0)                                                 /* check the result */
        {
            handle->debug_print("mb85rsxx: read failed.\n");          /* read failed */
           
            return 1;                                                 /* return error */
        }
    }
    else
    {
        reg[0] = MB85RSXX_COMMAND_READ;                               /* set command */
        reg[1] = (address >> 8) & 0xFF;                               /* address msb */
        reg[2] = (address >> 0) & 0xFF;                               /* address lsb */
        res = handle->spi_read_write(reg, 3, buf, len);               /* read data */
        if (res != 0)                                                 /* check the result */
        {
            handle->debug_print("mb85rsxx: read failed.\n");          /* read failed */
           
            return 1;                                                 /* return error */
        }
    }
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t mb85rsxx_write(mb85rsxx_handle_t *handle, uint32_t address, uint8_t *buf, uint16_t len)
{
    uint8_t res;
    uint8_t reg[1];
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    if ((address + len) > handle->id)                                         /* check length */
    {
        handle->debug_print("mb85rsxx: write out of range.\n");               /* write out of range */
       
        return 4;                                                             /* return error */
    }
    if (len > 512)                                                            /* check length */
    {
        handle->debug_print("mb85rsxx: len > 512.\n");                        /* len > 512 */
       
        return 5;                                                             /* return error */
    }

    reg[0] = MB85RSXX_COMMAND_WREN;                                           /* set command */
    res = handle->spi_read_write(reg, 1, NULL, 0);                            /* write command */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mb85rsxx: enable write failed.\n");              /* enable write failed */
       
        return 1;                                                             /* return error */
    }
    
    if (handle->id > (uint32_t)MB85RS512)                                     /* choose id to set different address */
    {
        handle->buf[0] = MB85RSXX_COMMAND_WRITE;                              /* set command */
        handle->buf[1] = (address >> 16) & 0xFF;                              /* address msb */
        handle->buf[2] = (address >> 8) & 0xFF;                               /* address mmsb */
        handle->buf[3] = (address >> 0) & 0xFF;                               /* address lsb */
        memcpy((uint8_t *)(handle->buf + 4), (uint8_t *)buf, len);            /* copy data */
        res = handle->spi_read_write(handle->buf, 4 + len, NULL, 0);          /* write data */
        if (res != 0)                                                         /* check the result */
        {
            handle->debug_print("mb85rsxx: write failed.\n");                 /* write failed */
           
            return 1;                                                         /* return error */
        }
    }
    else
    {
        handle->buf[0] = MB85RSXX_COMMAND_WRITE;                              /* set command */
        handle->buf[1] = (address >> 8) & 0xFF;                               /* address msb */
        handle->buf[2] = (address >> 0) & 0xFF;                               /* address lsb */
        memcpy((uint8_t *)(handle->buf + 3), (uint8_t *)buf, len);            /* copy data */
        res = handle->spi_read_write(handle->buf, 3 + len, NULL, 0);          /* write data */
        if (res != 0)                                                         /* check the result */
        {
            handle->debug_print("mb85rsxx: write failed.\n");                 /* write failed */
           
            return 1;                                                         /* return error */
        }
    }
    
    reg[0] = MB85RSXX_COMMAND_WRDI;                                           /* set command */
    res = handle->spi_read_write(reg, 1, NULL, 0);                            /* write command */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mb85rsxx: disable write failed.\n");             /* disable write failed */
       
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
                               uint8_t *product_id1, uint8_t *product_id2)
{
#if (MB85RSXX_USE_DEVICE_ID != 0)
    uint8_t res;
    uint8_t buf[1];
    uint8_t number[4];
    
    if (handle == NULL)                                           /* check handle */
    {
        return 2;                                                 /* return error */
    }
    if (handle->inited != 1)                                      /* check handle initialization */
    {
        return 3;                                                 /* return error */
    }
    
    buf[0] = MB85RSXX_COMMAND_RDID;                               /* set command */
    res = handle->spi_read_write(buf, 1, number, 4);              /* write command */
    if (res != 0)                                                 /* check the result */
    {
        handle->debug_print("mb85rsxx: get id failed.\n");        /* get id failed */
       
        return 1;                                                 /* return error */
    }
    *manufacturer_id = number[0];                                 /* set manufacturer id */
    *continuation_code = number[1];                               /* set continuation code */
    *product_id1 = number[2];                                     /* set product id1 */
    *product_id2 = number[3];                                     /* set product id2 */
    
    return 0;                                                     /* success return 0 */
#else
    if (handle == NULL)                                           /* check handle */
    {
        return 2;                                                 /* return error */
    }
    if (handle->inited != 1)                                      /* check handle initialization */
    {
        return 3;                                                 /* return error */
    }
    
    handle->debug_print("mb85rsxx: this function is disable.\n"); /* this function is disable */
    
    return 1;                                                     /* return error */
#endif
}

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a mb85rsxx info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t mb85rsxx_info(mb85rsxx_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(mb85rsxx_info_t));                       /* initialize mb85rsxx info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "SPI", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
