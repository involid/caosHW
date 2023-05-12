#!/bin/bash

openssl enc -aes-256-cbc -md sha256 -salt -d -in text_encrypt.txt -out text_decrypt.txt -pass pass:secret 2> /dev/null
