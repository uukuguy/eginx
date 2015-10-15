#-*- coding:utf-8 -*-

import os

filename='200M.flv'
filesize=200*1024*1024 #200M

with open(filename, "w") as f:
        f.write(os.urandom(filesize))


#with open("20M.flv", "w") as f:
        #f.write(os.urandom(1024*1024*20))


#with open("200M.flv", "w") as f:
        #f.write(os.urandom(1024*1024*200))
