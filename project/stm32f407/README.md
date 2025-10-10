### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

SPI Pin: SCK/MISO/MOSI/CS PA5/PA6/PA7/PA4.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. MB85RSXX

#### 3.1 Command Instruction

1. Show mb85rsxx chip and driver information.

   ```shell
   mb85rsxx (-i | --information)
   ```

2. Show mb85rsxx help.

   ```shell
   mb85rsxx (-h | --help)
   ```

3. Show mb85rsxx pin connections of the current board.

   ```shell
   mb85rsxx (-p | --port)
   ```

4. Run mb85rsxx read test.

   ```shell
   mb85rsxx (-e read | --example=read) [--type=<MB85RS16 | MB85RS64 | MB85RS128 | MB85RS256 | MB85RS512 | MB85RS1M | MB85RS2M | MB85RS4M>]
   ```

5. Run mb85rsxx read function, reg is the register address and it is hexadecimal.

   ```shell
   mb85rsxx (-e read | --example=read) [--type=<MB85RS16 | MB85RS64 | MB85RS128 | MB85RS256 | MB85RS512 | MB85RS1M | MB85RS2M | MB85RS4M>] [--reg=<address>]
   ```

6. Run mb85rsxx write function, reg is the register address and data is the set value, both are hexadecimal.

   ```shell
   mb85rsxx (-e write | --example=write) [--type=<MB85RS16 | MB85RS64 | MB85RS128 | MB85RS256 | MB85RS512 | MB85RS1M | MB85RS2M | MB85RS4M>] [--reg=<address>] [--data=<value>]
   ```

7. Run mb85rsxx status function.

   ```shell
   mb85rsxx (-e status | --example=status) [--type=<MB85RS16 | MB85RS64 | MB85RS128 | MB85RS256 | MB85RS512 | MB85RS1M | MB85RS2M | MB85RS4M>]
   ```
   
8. Run mb85rsxx info function.

   ```shell
   mb85rsxx (-e info | --example=info) [--type=<MB85RS16 | MB85RS64 | MB85RS128 | MB85RS256 | MB85RS512 | MB85RS1M | MB85RS2M | MB85RS4M>]
   ```
   
#### 3.2 Command Example

```shell
mb85rsxx -i

mb85rsxx: chip is RAMXEED MB85RSXX.
mb85rsxx: manufacturer is RAMXEED.
mb85rsxx: interface is SPI.
mb85rsxx: driver version is 1.0.
mb85rsxx: min supply voltage is 1.8V.
mb85rsxx: max supply voltage is 5.5V.
mb85rsxx: max current is 2.60mA.
mb85rsxx: max temperature is 85.0C.
mb85rsxx: min temperature is -40.0C.
```

```shell
mb85rsxx -p

mb85rsxx: SPI interface SCK connected to GPIOA PIN5.
mb85rsxx: SPI interface MISO connected to GPIOA PIN6.
mb85rsxx: SPI interface MOSI connected to GPIOA PIN7.
mb85rsxx: SPI interface CS connected to GPIOA PIN4.
```

```shell
mb85rsxx -t read --type=MB85RS64

mb85rsxx: chip is RAMXEED MB85RSXX.
mb85rsxx: manufacturer is RAMXEED.
mb85rsxx: interface is SPI.
mb85rsxx: driver version is 1.0.
mb85rsxx: min supply voltage is 1.8V.
mb85rsxx: max supply voltage is 5.5V.
mb85rsxx: max current is 2.60mA.
mb85rsxx: max temperature is 85.0C.
mb85rsxx: min temperature is -40.0C.
mb85rsxx: manufacturer id is 0x04.
mb85rsxx: continuation code is 0x7F.
mb85rsxx: product id1 is 0x03.
mb85rsxx: product id2 is 0x02.
mb85rsxx: status 0x00.
mb85rsxx: start read test.
mb85rsxx: 0x0000 read write test passed.
mb85rsxx: 0x0400 read write test passed.
mb85rsxx: 0x0800 read write test passed.
mb85rsxx: 0x0C00 read write test passed.
mb85rsxx: 0x1000 read write test passed.
mb85rsxx: 0x1400 read write test passed.
mb85rsxx: 0x1800 read write test passed.
mb85rsxx: 0x1C00 read write test passed.
mb85rsxx: finish read test.
```

```shell
mb85rsxx -e read --type=MB85RS64 --reg=0x0001

mb85rsxx: read 0x0001 is 0x15.
```

```shell
mb85rsxx -e write --type=MB85RS64 --reg=0x0001 --data=0x15

mb85rsxx: write 0x0001 is 0x15.
```

```shell
mb85rsxx -e status --type=MB85RS64

mb85rsxx: status is 0x00.
```

```shell
mb85rsxx -e info --type=MB85RS64

mb85rsxx: manufacturer id is 0x04.
mb85rsxx: continuation code is 0x7F.
mb85rsxx: product id1 is 0x03.
mb85rsxx: product id2 is 0x02.
```

```shell
mb85rsxx -h

Usage:
  mb85rsxx (-i | --information)
  mb85rsxx (-h | --help)
  mb85rsxx (-p | --port)
  mb85rsxx (-t read | --test=read) [--type=<MB85RS16 | MB85RS64 | MB85RS128 | MB85RS256 |
                                            MB85RS512 | MB85RS1M | MB85RS2M | MB85RS4M>]
  mb85rsxx (-e read | --example=read) [--type=<MB85RS16 | MB85RS64 | MB85RS128 | MB85RS256 |
                                               MB85RS512 | MB85RS1M | MB85RS2M | MB85RS4M>]
                                      [--reg=<address>]
  mb85rsxx (-e write | --example=write) [--type=<MB85RS16 | MB85RS64 | MB85RS128 | MB85RS256 |
                                                 MB85RS512 | MB85RS1M | MB85RS2M | MB85RS4M>]
                                        [--reg=<address>] [--data=<value>]
  mb85rsxx (-e status | --example=status) [--type=<MB85RS16 | MB85RS64 | MB85RS128 | MB85RS256 |
                                                   MB85RS512 | MB85RS1M | MB85RS2M | MB85RS4M>]
  mb85rsxx (-e info | --example=info) [--type=<MB85RS16 | MB85RS64 | MB85RS128 | MB85RS256 |
                                               MB85RS512 | MB85RS1M | MB85RS2M | MB85RS4M>]

Options:
      --data=<value>                            Set the sent data and it is hexadecimal.([default: random])
  -e <read>, --example=<read>                   Run the driver example.
  -h, --help                                    Show the help.
  -i, --information                             Show the chip information.
  -p, --port                                    Display the pin connections of the current board.
      --reg=<address>                           Set the register address and it is hexadecimal.([default: 0x0000])
  -t <read | write>, --test=<read | write>      Run the driver test.
      --type=<MB85RS16 | MB85RS64 | MB85RS128 | MB85RS256 |
              MB85RS512 | MB85RS1M | MB85RS2M | MB85RS4M>
                                                Set the chip type.([default: MB85RS16])
```

