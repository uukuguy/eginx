INSTALL_ROOT=/usr/local
APP=eginx
EGINX_SRC=eginx-1.2.4

export OSTYPE="`uname -s`"

ZLIB_SRC=zlib-1.2.7
PCRE_SRC=pcre-8.31
OPENSSL_SRC=openssl-1.0.1c
NGINX_SRC=nginx-1.2.4

NGX_DEPS=--with-openssl=../openssl \
		--with-pcre=../pcre \
		--with-zlib=../zlib \

#if [ $(OSTYPE) = "Darwin" ] ; \
	#then \
	#NGX_DEPS= \
	#; \
#else \
#NGX_DEPS=--with-openssl=../openssl \
		#--with-pcre=../pcre \
		#--with-zlib=../zlib \
		#;\
#fi


NGX_MODULES=--with-http_ssl_module \
		--with-http_flv_module 
		#--with-http_mp4_module 

NGX_ADD_MODULES=--add-module=../../modules/udsproxy/src/ngx_http_udsproxy \
				--add-module=../../modules/miniuds/src/ngx_http_miniuds 
				
#--add-module=../../modules/rtmp
#--add-module=../../modules/flvplay/src/ngx_http_flvplay 

#CFLAGS=-I/usr/include/jsoncpp/json
#JSONLIB=-ljsoncpp
JSONLIB=-ljson
LOG4CPLUS=-llog4cplus
LOG4CPLUS_Wrapper_Folder=${PWD}/YRXCore/linux/log4cplus
LOG4CPLUS_WrapperLIBS=-llog4cplusWrapper
all: _configure_nginx 
	${MAKE} -C src/nginx 

_configure_nginx: src/nginx/Makefile

src/nginx/Makefile:
	cd src && tar zxvf ${ZLIB_SRC}.tar.gz
	cd src && tar zxvf ${PCRE_SRC}.tar.gz
	cd src && tar zxvf ${OPENSSL_SRC}.tar.gz
	cd src && tar zxvf ${NGINX_SRC}.tar.gz
	${MAKE} -C ${LOG4CPLUS_Wrapper_Folder}
	if [ $(OSTYPE) = "Darwin" ] ; \
	then \
	cd src/nginx && \
	./configure --prefix=${INSTALL_ROOT}/${EGINX_SRC} \
		--with-cc-opt="-I/opt/local/include" \
		--with-ld-opt="-L/opt/local/lib -lboost_system-mt ${JSONLIB} ${LOG4CPLUS} ${LOG4CPLUS_WrapperLIBS} -lstdc++.6" \
		${NGX_DEPS} \
		${NGX_MODULES} \
		${NGX_ADD_MODULES} \
		; \
	else \
	cd src/nginx && \
	./configure --prefix=${INSTALL_ROOT}/${EGINX_SRC} \
		--with-cc-opt="-I${LOG4CPLUS_Wrapper_Folder}" \
		--with-ld-opt="-L. -L${LOG4CPLUS_Wrapper_Folder} -static -llog4cplusWrapper  ${JSONLIB} ${LOG4CPLUS}  -lboost_system -lstdc++ -lrt" \
		${NGX_DEPS} \
		${NGX_MODULES} \
		${NGX_ADD_MODULES} \
		; \
	fi


clean:
	rm -fr src/${ZLIB_SRC}
	rm -fr src/${PCRE_SRC}
	rm -fr src/${OPENSSL_SRC}
	rm -fr src/${NGINX_SRC}

install:
	${MAKE} -C src/nginx install
	test -d ${INSTALL_ROOT}/${APP} || ln -sf ${EGINX_SRC} ${INSTALL_ROOT}/${APP}
	cp -Rf bin conf html ${INSTALL_ROOT}/${APP}/
	if [ $(OSTYPE) = "Darwin" ] ; \
	then \
		cp -f conf/nginx.conf.macos ${INSTALL_ROOT}/${APP}/conf/nginx.conf ;\
	fi


