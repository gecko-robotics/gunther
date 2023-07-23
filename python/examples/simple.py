#!/usr/bin/env python3

from gunther import Beacon
from gunther import Ascii, Json, Raw
from gunther import AF_INET, AF_INET6
import time
import sys
from colorama import Fore

def func(d):
    # for k,v in d.items():
    #     print(f"{Fore.BLUE}{k}:{Fore.RESET} {v}", end=" ")
    # print(" ")
    print(d)


if len(sys.argv) != 2 or sys.argv[1] not in ['b','l','s']:
    print("apple.py b|l")

b = Beacon(handler=Ascii, family=AF_INET)

try:
    if sys.argv[1] == 'l':
        msgs = b.listen(3)
        if len(msgs) > 0:
            for d in msgs:
                print(d)
    elif sys.argv[1] == 'b':
        msgs = [
            {"host":"1.2.3.4:1234","topic":"bob","size":1024},
            {"host":"11.12.13.14:1234","topic":"alice","size":512},
            {"host":"12.22.32.42:1234","topic":"tom","size":128},
        ]
        b.broadcast(msgs,0.5)
    else:
        b.stream(func)

except KeyboardInterrupt:
    print("ctl-c ...")