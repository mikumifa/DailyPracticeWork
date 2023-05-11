#!/bin/bash


xterm -T "secure_server" -e './secure_server/secure_server 1235;$SHELL' &
sleep 2s 
xterm -T "secure_client" -e './secure_client/secure_client localhost 1235; $SHELL' &
