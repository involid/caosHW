#!/bin/bash

openssl enc -aes-256-cbc -md sha256 -salt -e -in text.txt -out text_encrypt.txt -pass pass:secret 2> /dev/null
