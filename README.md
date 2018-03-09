## Rootstealer
Program to detect when linux user opens terminal with root and inject intrusive commands with X11 lib

## Video of Proof of concept

The proposal of this video is use tool rootstealer to spy all gui windows interactions and inject commands only in root terminal. This approach is util when attacker need to send a malicious program to prove that user  is vulnerable  to social  engineering. Force root command in terminal with lib X11 is a exotic way to show the diversity of weak points.

https://www.youtube.com/watch?v=V8sZQq7nerw

## Install

```
# apt-get install libX11-dev libxtst-dev
# cd rootstealer/sendkeys; 
```
Config  CMD  that you need use to do injection, edit  value of variable CMD in /rootstealer/sendleys/src/sendkeys.c

Now you can takethat following:

```
# pip intall gi
or
# pip install gir
```
Run the python script to  spy all windows gui and  search  window with "@root" string in title.

```
$ python rootstealer.py &
```


## Tests

Tested in ubuntu 16.04
