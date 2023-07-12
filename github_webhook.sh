#!/bin/bash
cd ~/oai-cn5g-fed
if git pull | grep -q "Already up to date."; then echo "hello"; else bash ~/script.sh > ~/Console.output ; fi
