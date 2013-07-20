Egnix
=====

Nginx plugins especially for UDS.

Submodules
----------

flvplay(https://github.com/uukuguy/flvplay) - Play .flv .mp4 video using UDS access interface specification.

Downloaad
---------

    http://67.20.96.216/eginx-1.2.4.tar.gz

Install
-------

    $ git clone https://github.com/uukuguy/eginx.git
    $ cd eginx
    $ git submodule init
    $ git submodule update
    $ cd modules
    $ cd flvplay
    $ git pull origin master
    $ git checkout master
    $ cd ../rtmp
    $ git pull origin master
    $ git checkout master
    $ cd ../../

Run
---

    $ sudo eginx/bin/starteginx.sh
    $ tail -f eginx/logs/error.log

Stop
----

    $ sudo eginx/bin/stopeginx.sh


