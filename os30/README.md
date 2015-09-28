# Operationg System for x86 architecture

![image](https://raw.github.com/wiki/SatoshiShimada/os/images/os1.png)

## Using tools
* gcc
* qemu

## Usage
```shell
make
make run
```

## Structure

### Memory Map

|Address|Data|
|:------|---------:|
|~ 0x79ff | Stack |
|0x8000 |FDD image of sector 0|
|0x8200 |FDD image of sector 1|
|0x8400 |FDD image of sector 2|
|0x26f800 ~ 0x26f8ff | IDT |
|0x270000 | 0x27ffff | GDT |
|  :    |continue...|
|End    |of Memory|

