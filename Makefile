INSTALL_ROOT=/usr/local

export OSTYPE="`uname -s`"

ZLIB_SRC=zlib-1.2.7
PCRE_SRC=pcre-8.31
OPENSSL_SRC=openssl-1.0.1c
NGINX_SRC=nginx-1.2.4

all: _configure_nginx 
	${MAKE} -C src/nginx -s

_configure_nginx: src/nginx/Makefile

src/nginx/Makefile:
	cd src && tar zxvf ${ZLIB_SRC}.tar.gz
	cd src && tar zxvf ${PCRE_SRC}.tar.gz
	cd src && tar zxvf ${OPENSSL_SRC}.tar.gz
	cd src && tar zxvf ${NGINX_SRC}.tar.gz
	if [ $(OSTYPE) = "Darwin" ] ; \
	then \
	cd src/nginx && \
	./configure --prefix=${INSTALL_ROOT}/${NGINX_SRC} \
		--with-ld-opt="" \
		--with-http_ssl_module \
		--with-openssl=../openssl \
		--with-pcre=../pcre \
		--with-zlib=../zlib \
		--add-module=../../modules/flvplay/src/ngx_http_flvplay \
		; \
	else \
	cd src/nginx && \
	./configure --prefix=${INSTALL_ROOT}/${NGINX_SRC} \
		--with-ld-opt="-static" \
		--with-http_ssl_module \
		--with-openssl=../openssl \
		--with-pcre=../pcre \
		--with-zlib=../zlib \
		--add-module=../../modules/flvplay/src/ngx_http_flvplay \
		; \
	fi


clean:
	rm -fr src/${ZLIB_SRC}
	rm -fr src/${PCRE_SRC}
	rm -fr src/${OPENSSL_SRC}
	rm -fr src/${NGINX_SRC}

install:
	${MAKE} -C src/nginx install
	test -d ${INSTALL_ROOT}/nginx || ln -sf ${NGINX_SRC} ${INSTALL_ROOT}/nginx
	cp -Rf conf html ${INSTALL_ROOT}/nginx/
	if [ $(OSTYPE) = "Darwin" ] ; \
	then \
		cp -f conf/nginx.conf.macos ${INSTALL_ROOT}/nginx/conf/nginx.conf ;\
	fi


