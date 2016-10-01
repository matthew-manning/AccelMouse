#! /bin/bash
#build and link AccelRead

gcc -Wall -Werror i2c.c pseudomouse.c ws10dof.c transferLib.c MouseServer.c -o MouseServer
