# Operationg System for x86 architecture

## Using tools
* gcc
* qemu

## Usage
```
make
make run
```

## Structure

### Memory Map

|Address|Data|
|:-|-:|
|0x8000|FDD image of sector 0|
|0x8200|FDD image of sector 1|
|0x8400|FDD image of sector 2|
|  :   |continue...|
|End|of Memory|

