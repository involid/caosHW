#!/bin/bash

gcc decrypt.c -lcrypto -o decrypt
cat text_encrypt.txt | ./decrypt secret > text_decrypt.txt
rm decrypt
