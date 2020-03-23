#!/bin/sh

LIST_OF_APPS="python pip" 

apt-get update  # To get the latest package lists
apt-get install -y $LIST_OF_APPS

pip install notebook # download jupyter notebook

jupyter notebook # launch notebook

