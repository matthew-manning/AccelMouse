#! /bin/bash
#build and link AccelRead

gcc -Wall -Werror i2c.c pseudomouse.c ws10dof.c MouseTestServer.c -o MouseTest
