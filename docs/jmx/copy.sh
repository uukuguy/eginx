#!/bin/bash 
ROOT230=root@10.142.49.230
ROOT237=root@10.142.49.237
#scp nginx_http_download*.jmx root@10.142.49.230:/home/charles/nginx_test/

scp nginx_*.jmx ${ROOT230}:/home/charles/nginx_test/
scp nginx_*.jmx ${ROOT237}:/home/charles/nginx_test/

scp test230_3000port.jmx ${ROOT230}:/home/charles/nginx_test/
scp test230_3000port.jmx ${ROOT237}:/home/charles/nginx_test/



scp run.sh ${ROOT230}:/home/charles/nginx_test/
scp run.sh ${ROOT237}:/home/charles/nginx_test/
