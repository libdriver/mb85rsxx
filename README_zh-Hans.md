[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MB85RSXX

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/mb85rsxx/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

MB85RSXX是一款铁电随机存取存储器（FeRAM）芯片，采用铁电工艺和硅栅CMOS工艺技术形成非易失性存储单元。MB85RSXX采用串行外设接口（SPI）。MB85RSXX能够在不使用SRAM所需的备用电池的情况下保留数据。MB85RSXX中使用的存储单元可用于10^10次读/写操作，这比闪存和E2PROM的读写操作数量有了显著提高。MB85RS4X不像闪存或E2PROM那样需要很长时间来写入数据，MB85RSXXX也不需要等待时间。

LibDriver MB85RSXX是LibDriver推出的MB85RSXX全功能驱动，该驱动提供写入和读取功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver MB85RSXX的源文件。

/interface目录包含了LibDriver MB85RSXX与平台无关的SPI总线模板。

/test目录包含了LibDriver MB85RSXX驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver MB85RSXX编程范例。

/doc目录包含了LibDriver MB85RSXX离线文档。

/datasheet目录包含了MB85RSXX数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的SPI总线模板，完成指定平台的SPI总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

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

### 文档

在线文档: [https://www.libdriver.com/docs/mb85rsxx/index.html](https://www.libdriver.com/docs/mb85rsxx/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。