#!/bin/bash

#sudo git clone https://github.com/root-project/jsroot.git
git submodule update --init --recursive
# (see https://git-scm.com/book/en/v2/Git-Tools-Submodules)

sudo npm install leaflet
sudo npm install jquery

# to update:
#sudo npm install -g npm
