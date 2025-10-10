[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MB85RSXX
[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/mb85rsxx/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

MB85RSXX ist ein FeRAM-Chip (Ferroelectric Random Access Memory), der die Ferroelektrizitäts- und Silizium-Gate-CMOS-Prozesstechnologie zur Bildung der nichtflüchtigen Speicherzellen nutzt. MB85RSXX nutzt die Serial Peripheral Interface (SPI). Der MB85RSXX kann Daten ohne Pufferbatterie speichern, wie dies bei SRAM erforderlich ist. Die im MB85RSXX verwendeten Speicherzellen ermöglichen 10^10 Lese-/Schreibvorgänge, was eine deutliche Verbesserung gegenüber der Anzahl der von Flash-Speichern und E2PROM unterstützten Lese- und Schreibvorgänge darstellt. MB85RSXX benötigt im Gegensatz zu Flash-Speichern oder E2PROM nicht lange zum Schreiben von Daten und verursacht keine Wartezeiten.

LibDriver MB85RSXX ist der voll funktionsfähige Treiber von MB85RSXX, der von LibDriver gestartet wurde. MB85RSXX bietet Schreib- und Lesefunktionen. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver MB85RSXX-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver MB85RSXX SPI.

/test enthält den Testcode des LibDriver MB85RSXX-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver MB85RSXX-Beispielcode.

/doc enthält das LibDriver MB85RSXX-Offlinedokument.

/Datenblatt enthält MB85RSXX-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige SPI-Schnittstellenvorlage und stellen Sie Ihren Plattform-SPI-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/mb85rsxx/index.html](https://www.libdriver.com/docs/mb85rsxx/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.