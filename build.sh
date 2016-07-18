#! /bin/bash
#build and link AccelRead.c

arm-linux-gnueabi-gcc -Wall i2c.c pseudomouse.c ws10dof.c MouseTest.c -o MouseTest
