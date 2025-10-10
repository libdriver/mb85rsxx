[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MB85RSXX

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/mb85rsxx/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

MB85RSXX is a FeRAM (Ferroelectric Random Access Memory) chip, using the ferroelectric process and silicon gate CMOS process technologies for forming the nonvolatile memory cells. MB85RSXX adopts the Serial Peripheral Interface (SPI). The MB85RSXX is able to retain data without using a back-up battery, as is needed for SRAM. The memory cells used in the MB85RSXX can be used for 10^10 read/write operations, which is a significant improvement over the number of read and write operations supported by Flash memory and E2PROM. MB85RSXX does not take long time to write data like Flash memories or E2PROM, and MB85RSXX takes no wait time.

LibDriver MB85RSXX is a full-featured driver for MB85RSXX, launched by LibDriver. It provides writing, reading and additional features. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver MB85RSXX source files.

/interface includes LibDriver MB85RSXX SPI platform independent template.

/test includes LibDriver MB85RSXX driver test code and this code can test the chip necessary function simply.

/example includes LibDriver MB85RSXX sample code.

/doc includes LibDriver MB85RSXX offline document.

/datasheet includes MB85RSXX datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface SPI platform independent template and finish your platform SPI driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_mb85rsxx_basic.h"

uint8_t res;
uint8_t status;
uint8_t manufacturer_id;
uint8_t continuation_code;
uint8_t product_id1;
uint8_t product_id2;
uint8_t data = 0x00;
uint32_t reg = 0x0000;

/* basic init */
res = mb85rsxx_basic_init(MB85RS16);
if (res != 0)
{
    return 1;
}

...
    
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

...

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

...

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

...

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

...
    
/* deinit */
(void)mb85rsxx_basic_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/mb85rsxx/index.html](https://www.libdriver.com/docs/mb85rsxx/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.