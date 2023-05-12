#!/bin/bash

gcc encrypt.c -lcrypto -o encrypt
./encrypt secret
rm encrypt
