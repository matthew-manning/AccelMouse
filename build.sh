#! /bin/bash
#build and link AccelRead.c

 arm-linux-gnueabi-gcc -Wall AccelRead.c i2c.c -o AccelRead
