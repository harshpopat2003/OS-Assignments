#!/bin/bash
cd /home/kern/build/kern1/linux-5.19.8 && make mrproper
cp /home/kern/build/linux-5.19.8/.config /home/kern/build/kern1/linux-5.19.8
cd /home/kern/build/kern1/linux-5.19.8
make