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
 * @file      main.c
 * @brief     main source file
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
#include "driver_mb85rsxx_basic.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "getopt.h"
#include <math.h>
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
volatile uint16_t g_len;   /**< uart buffer length */

/**
 * @brief     mb85rsxx full function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t mb85rsxx(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"data", required_argument, NULL, 1},
        {"reg", required_argument, NULL, 2},
        {"type", required_argument, NULL, 3},
        {NULL, 0, NULL, 0},
    };
    char type[32] = "unknown";
    uint8_t data = rand() % 0xFF;
    uint32_t reg = 0x0000;
    mb85rsxx_t chip_type = MB85RS16;

    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }

    /* init 0 */
    optind = 0;

    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);

        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 32);
                snprintf(type, 32, "h");

                break;
            }

            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 32);
                snprintf(type, 32, "i");

                break;
            }

            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 32);
                snprintf(type, 32, "p");

                break;
            }

            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 32);
                snprintf(type, 32, "e_%s", optarg);

                break;
            }

            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 32);
                snprintf(type, 32, "t_%s", optarg);

                break;
            }
            
            /* data */
            case 1 :
            {
                char *p;
                uint16_t l;
                uint16_t i;
                uint64_t hex_data;

                /* set the data */
                l = strlen(optarg);

                /* check the header */
                if (l >= 2)
                {
                    if (strncmp(optarg, "0x", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else if (strncmp(optarg, "0X", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else
                    {
                        p = optarg;
                    }
                }
                else
                {
                    p = optarg;
                }
                
                /* init 0 */
                hex_data = 0;

                /* loop */
                for (i = 0; i < l; i++)
                {
                    if ((p[i] <= '9') && (p[i] >= '0'))
                    {
                        hex_data += (p[i] - '0') * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'F') && (p[i] >= 'A'))
                    {
                        hex_data += ((p[i] - 'A') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'f') && (p[i] >= 'a'))
                    {
                        hex_data += ((p[i] - 'a') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else
                    {
                        return 5;
                    }
                }
                
                /* set the data */
                data = hex_data & 0xFF;
                
                break;
            }

            /* register */
            case 2 :
            {
                char *p;
                uint16_t l;
                uint16_t i;
                uint64_t hex_data;

                /* set the data */
                l = strlen(optarg);

                /* check the header */
                if (l >= 2)
                {
                    if (strncmp(optarg, "0x", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else if (strncmp(optarg, "0X", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else
                    {
                        p = optarg;
                    }
                }
                else
                {
                    p = optarg;
                }
                
                /* init 0 */
                hex_data = 0;

                /* loop */
                for (i = 0; i < l; i++)
                {
                    if ((p[i] <= '9') && (p[i] >= '0'))
                    {
                        hex_data += (p[i] - '0') * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'F') && (p[i] >= 'A'))
                    {
                        hex_data += ((p[i] - 'A') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'f') && (p[i] >= 'a'))
                    {
                        hex_data += ((p[i] - 'a') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else
                    {
                        return 5;
                    }
                }
                
                /* set the data */
                reg = hex_data & 0xFFFF;

                break;
            }

            /* type */
            case 3 :
            {
                if (strcmp("MB85RS16", optarg) == 0)
                {
                    chip_type = MB85RS16;
                }
                else if (strcmp("MB85RS64", optarg) == 0)
                {
                    chip_type = MB85RS64;
                }
                else if (strcmp("MB85RS128", optarg) == 0)
                {
                    chip_type = MB85RS128;
                }
                else if (strcmp("MB85RS256", optarg) == 0)
                {
                    chip_type = MB85RS256;
                }
                else if (strcmp("MB85RS512", optarg) == 0)
                {
                    chip_type = MB85RS512;
                }
                else if (strcmp("MB85RS1M", optarg) == 0)
                {
                    chip_type = MB85RS1M;
                }
                else if (strcmp("MB85RS2M", optarg) == 0)
                {
                    chip_type = MB85RS2M;
                }
                else if (strcmp("MB85RS4M", optarg) == 0)
                {
                    chip_type = MB85RS4M;
                }
                else
                {
                    return 5;
                }

                break;
            }

            /* the end */
            case -1 :
            {
                break;
            }

            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_read", type) == 0)
    {
        /* run the read test */
        if (mb85rsxx_read_test(chip_type) != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;

        /* basic init */
        res = mb85rsxx_basic_init(chip_type);
        if (res != 0)
        {
            return 1;
        }

        /* read data */
        res = mb85rsxx_basic_read(reg, (uint8_t *)&data, 1);
        if (res != 0)
        {
            (void)mb85rsxx_basic_deinit();

            return 1;
        }
        else
        {
            mb85rsxx_interface_debug_print("mb85rsxx: read 0x%04x is 0x%02X.\n", reg, data);
        }

        /* deinit */
        (void)mb85rsxx_basic_deinit();

        return 0;
    }
    else if (strcmp("e_write", type) == 0)
    {
        uint8_t res;

        /* basic init */
        res = mb85rsxx_basic_init(chip_type);
        if (res != 0)
        {
            return 1;
        }

        /* write data */
        res = mb85rsxx_basic_write(reg, (uint8_t *)&data, 1);
        if (res != 0)
        {
            (void)mb85rsxx_basic_deinit();

            return 1;
        }
        else
        {
            mb85rsxx_interface_debug_print("mb85rsxx: write 0x%04x is 0x%02X.\n", reg, data);
        }

        /* deinit */
        (void)mb85rsxx_basic_deinit();

        return 0;
    }
    else if (strcmp("e_status", type) == 0)
    {
        uint8_t res;
        uint8_t status;

        /* basic init */
        res = mb85rsxx_basic_init(chip_type);
        if (res != 0)
        {
            return 1;
        }

        /* get status */
        res = mb85rsxx_basic_get_status(&status);
        if (res != 0)
        {
            (void)mb85rsxx_basic_deinit();

            return 1;
        }
        else
        {
            mb85rsxx_interface_debug_print("mb85rsxx: status is 0x%02X.\n", status);
        }

        /* deinit */
        (void)mb85rsxx_basic_deinit();

        return 0;
    }
    else if (strcmp("e_info", type) == 0)
    {
        uint8_t res;
        uint8_t manufacturer_id;
        uint8_t continuation_code;
        uint8_t product_id1;
        uint8_t product_id2;

        /* basic init */
        res = mb85rsxx_basic_init(chip_type);
        if (res != 0)
        {
            return 1;
        }

        /* get info */
        res = mb85rsxx_basic_get_info(&manufacturer_id, &continuation_code, &product_id1, &product_id2);
        if (res != 0)
        {
            (void)mb85rsxx_basic_deinit();

            return 1;
        }
        else
        {
            mb85rsxx_interface_debug_print("mb85rsxx: manufacturer id is 0x%02X.\n", manufacturer_id);
            mb85rsxx_interface_debug_print("mb85rsxx: continuation code is 0x%02X.\n", continuation_code);
            mb85rsxx_interface_debug_print("mb85rsxx: product id1 is 0x%02X.\n", product_id1);
            mb85rsxx_interface_debug_print("mb85rsxx: product id2 is 0x%02X.\n", product_id2);
        }

        /* deinit */
        (void)mb85rsxx_basic_deinit();

        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        mb85rsxx_interface_debug_print("Usage:\n");
        mb85rsxx_interface_debug_print("  mb85rsxx (-i | --information)\n");
        mb85rsxx_interface_debug_print("  mb85rsxx (-h | --help)\n");
        mb85rsxx_interface_debug_print("  mb85rsxx (-p | --port)\n");
        mb85rsxx_interface_debug_print("  mb85rsxx (-t read | --test=read) [--type=<MB85RS16 | MB85RS64 | MB85RS128 | MB85RS256 |\n");
        mb85rsxx_interface_debug_print("                                            MB85RS512 | MB85RS1M | MB85RS2M | MB85RS4M>]\n");
        mb85rsxx_interface_debug_print("  mb85rsxx (-e read | --example=read) [--type=<MB85RS16 | MB85RS64 | MB85RS128 | MB85RS256 |\n");
        mb85rsxx_interface_debug_print("                                               MB85RS512 | MB85RS1M | MB85RS2M | MB85RS4M>]\n");
        mb85rsxx_interface_debug_print("                                      [--reg=<address>]\n");
        mb85rsxx_interface_debug_print("  mb85rsxx (-e write | --example=write) [--type=<MB85RS16 | MB85RS64 | MB85RS128 | MB85RS256 |\n");
        mb85rsxx_interface_debug_print("                                                 MB85RS512 | MB85RS1M | MB85RS2M | MB85RS4M>]\n");
        mb85rsxx_interface_debug_print("                                        [--reg=<address>] [--data=<value>]\n");
        mb85rsxx_interface_debug_print("  mb85rsxx (-e status | --example=status) [--type=<MB85RS16 | MB85RS64 | MB85RS128 | MB85RS256 |\n");
        mb85rsxx_interface_debug_print("                                                   MB85RS512 | MB85RS1M | MB85RS2M | MB85RS4M>]\n");
        mb85rsxx_interface_debug_print("  mb85rsxx (-e info | --example=info) [--type=<MB85RS16 | MB85RS64 | MB85RS128 | MB85RS256 |\n");
        mb85rsxx_interface_debug_print("                                               MB85RS512 | MB85RS1M | MB85RS2M | MB85RS4M>]\n");
        mb85rsxx_interface_debug_print("\n");
        mb85rsxx_interface_debug_print("Options:\n");
        mb85rsxx_interface_debug_print("      --data=<value>                            Set the sent data and it is hexadecimal.([default: random])\n");
        mb85rsxx_interface_debug_print("  -e <read>, --example=<read>                   Run the driver example.\n");
        mb85rsxx_interface_debug_print("  -h, --help                                    Show the help.\n");
        mb85rsxx_interface_debug_print("  -i, --information                             Show the chip information.\n");
        mb85rsxx_interface_debug_print("  -p, --port                                    Display the pin connections of the current board.\n");
        mb85rsxx_interface_debug_print("      --reg=<address>                           Set the register address and it is hexadecimal.([default: 0x0000])\n");
        mb85rsxx_interface_debug_print("  -t <read | write>, --test=<read | write>      Run the driver test.\n");
        mb85rsxx_interface_debug_print("      --type=<MB85RS16 | MB85RS64 | MB85RS128 | MB85RS256 |\n");
        mb85rsxx_interface_debug_print("              MB85RS512 | MB85RS1M | MB85RS2M | MB85RS4M>\n");
        mb85rsxx_interface_debug_print("                                                Set the chip type.([default: MB85RS16])\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        mb85rsxx_info_t info;

        /* print mb85rsxx info */
        mb85rsxx_info(&info);
        mb85rsxx_interface_debug_print("mb85rsxx: chip is %s.\n", info.chip_name);
        mb85rsxx_interface_debug_print("mb85rsxx: manufacturer is %s.\n", info.manufacturer_name);
        mb85rsxx_interface_debug_print("mb85rsxx: interface is %s.\n", info.interface);
        mb85rsxx_interface_debug_print("mb85rsxx: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        mb85rsxx_interface_debug_print("mb85rsxx: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        mb85rsxx_interface_debug_print("mb85rsxx: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        mb85rsxx_interface_debug_print("mb85rsxx: max current is %0.2fmA.\n", info.max_current_ma);
        mb85rsxx_interface_debug_print("mb85rsxx: max temperature is %0.1fC.\n", info.temperature_max);
        mb85rsxx_interface_debug_print("mb85rsxx: min temperature is %0.1fC.\n", info.temperature_min);

        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        mb85rsxx_interface_debug_print("mb85rsxx: SPI interface SCK connected to GPIOA PIN5.\n");
        mb85rsxx_interface_debug_print("mb85rsxx: SPI interface MISO connected to GPIOA PIN6.\n");
        mb85rsxx_interface_debug_print("mb85rsxx: SPI interface MOSI connected to GPIOA PIN7.\n");
        mb85rsxx_interface_debug_print("mb85rsxx: SPI interface CS connected to GPIOA PIN4.\n");

        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;

    /* stm32f407 clock init and hal init */
    clock_init();

    /* delay init */
    delay_init();

    /* uart init */
    uart_init(115200);

    /* shell init && register mb85rsxx function */
    shell_init();
    shell_register("mb85rsxx", mb85rsxx);
    uart_print("mb85rsxx: welcome to libdriver mb85rsxx.\n");

    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("mb85rsxx: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("mb85rsxx: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("mb85rsxx: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("mb85rsxx: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("mb85rsxx: param is invalid.\n");
            }
            else
            {
                uart_print("mb85rsxx: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
