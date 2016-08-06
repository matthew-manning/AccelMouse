#! /bin/bash
#build and link AccelRead

gcc -Wall i2c.c pseudomouse.c ws10dof.c MouseTest.c -o MouseTest
