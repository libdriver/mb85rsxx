[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MB85RSXX

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/mb85rsxx/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

MB85RSXX는 비휘발성 메모리 셀을 형성하기 위해 강유전체 공정과 실리콘 게이트 CMOS 공정 기술을 사용하는 FeRAM(강유전체 랜덤 액세스 메모리) 칩입니다. MB85RSXX는 SPI(Serial Peripheral Interface)를 채택하여 SRAM처럼 백업 배터리를 사용하지 않고도 데이터를 보존할 수 있습니다. MB85RSXX에 사용된 메모리 셀은 10^10회의 읽기/쓰기 연산에 사용될 수 있으며, 이는 플래시 메모리나 E2PROM이 지원하는 읽기 및 쓰기 연산 횟수보다 크게 향상되었습니다. MB85RSXX는 플래시 메모리나 E2PROM처럼 데이터 쓰기에 오랜 시간이 걸리지 않으며, 대기 시간도 없습니다.

LibDriver MB85RSXX는 LibDriver에서 출시한 MB85RSXX의 전체 기능 드라이버입니다. MB85RSXX는 쓰기 및 읽기 기능을 제공합니다. LibDriver는 MISRA를 준수합니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example basic](#example-basic)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver MB85RSXX의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver MB85RSXX용 플랫폼 독립적인 SPI버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver MB85RSXX드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver MB85RSXX프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver MB85RSXX오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 MB85RSXX데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

/misra 에는 LibDriver misra 코드 검색 결과가 포함됩니다.

### 설치

/interface 디렉토리에서 플랫폼 독립적인 SPI버스 템플릿을 참조하여 지정된 플랫폼에 대한 SPI버스 드라이버를 완성하십시오.

/src 디렉터리, 플랫폼용 인터페이스 드라이버 및 자체 드라이버를 프로젝트에 추가합니다. 기본 예제 드라이버를 사용하려면 /example 디렉터리를 프로젝트에 추가합니다.

### 사용

/example 디렉터리의 예제를 참조하여 자신만의 드라이버를 완성할 수 있습니다. 기본 프로그래밍 예제를 사용하려는 경우 사용 방법은 다음과 같습니다.

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

### 문서

온라인 문서: [https://www.libdriver.com/docs/mb85rsxx/index.html](https://www.libdriver.com/docs/mb85rsxx/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.