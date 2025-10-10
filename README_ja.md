[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MB85RSXX

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/mb85rsxx/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

MB85RSXXは、強誘電体プロセスとシリコンゲートCMOSプロセス技術を用いて不揮発性メモリセルを形成するFeRAM（強誘電体ランダムアクセスメモリ）チップです。MB85RSXXは、シリアルペリフェラルインターフェース（SPI）を採用しています。MB85RSXXは、SRAMに必要なバックアップバッテリーを使用せずにデータを保持できます。MB85RSXXに使用されているメモリセルは、10^10回の読み書きが可能で、これはフラッシュメモリやE2PROMがサポートする読み書き回数を大幅に上回っています。MB85RSXXは、フラッシュメモリやE2PROMのようにデータの書き込みに時間がかからず、待機時間も発生しません。

LibDriver MB85RSXXは、LibDriverによって起動されたMB85RSXXの全機能ドライバーです。 MB85RSXXは、書き込みおよび読み取り機能を提供します。LibDriverはMISRAに準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver MB85RSXXのソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver MB85RSXX用のプラットフォームに依存しないSPIバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver MB85RSXXドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver MB85RSXXプログラミング例が含まれています。

/ docディレクトリには、LibDriver MB85RSXXオフラインドキュメントが含まれています。

/ datasheetディレクトリには、MB85RSXXデータシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないSPIバステンプレートを参照して、指定したプラットフォームのSPIバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/mb85rsxx/index.html](https://www.libdriver.com/docs/mb85rsxx/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。