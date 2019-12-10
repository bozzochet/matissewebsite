# Matisse Web site (+ Server services)

We need JSRoot:
```
#sudo git clone https://github.com/root-project/jsroot.git
git submodule update --init --recursive
# (see https://git-scm.com/book/en/v2/Git-Tools-Submodules)
```

and some node modules (for the ISS map with OpenNotify):
```
sudo npm install leaflet
sudo npm install jquery
```

to update:
```
sudo npm install -g npm
```
