
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include "uds_filepath.h"
#include "yrx_logmodule.h"
static char *ngx_http_udsproxy(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static void *ngx_http_udsproxy_create_conf(ngx_conf_t *cf);
static char *ngx_http_udsproxy_merge_conf(ngx_conf_t *cf, void *parent, void *child);
static char *ngx_http_uds_host(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static char *ngx_http_uds_port(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static char *ngx_http_uds_uri(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);

ngx_int_t  init_module(ngx_cycle_t *cycle)
{
    u_char* p = NULL;
    u_char* ptmp = NULL;
    int n = 0;
    char szpath[260] = {0};
    ngx_str_t strsbin = ngx_string("sbin");
    ngx_str_t strconf = ngx_string("conf");
    ngx_str_t logconfName = ngx_string("log4cplus.Client_properties");
    p = ngx_pnalloc(cycle->pool, NGX_MAX_PATH);
    if (p == NULL) {
        return NGX_ERROR;
    }
#ifdef _WIN32
    GetModuleFileName(NULL,p, NGX_MAX_PATH);
    ptmp = (u_char*)ngx_strstr(p, (u_char*)"nginx.exe");
    ptmp = ngx_cpymem(ptmp,strconf.data, strconf.len);
    ptmp = ngx_cpymem(ptmp,"\\",1);
    ptmp = ngx_cpymem(ptmp,logconfName.data,logconfName.len);
    //p = strrchr(szpath,'\\');
    printf("szpath = %s\r\n",(char*)p);
#else
    n = readlink("/proc/self/exe",(char*)p,NGX_MAX_PATH);
    if (n >0 && n< NGX_MAX_PATH) 
    {
        ptmp = (u_char*)ngx_strstr(p,strsbin.data);
        printf("p=%s\n",p);
        ptmp = ngx_cpymem(ptmp,strconf.data, strconf.len);
        ptmp = ngx_cpymem(ptmp,"/",1);
        ptmp = ngx_cpymem(ptmp,logconfName.data,logconfName.len);
        //ptmp = ngx_cpystrn(p, strconf.data, strconf.len);
        //ptmp = ngx_cpystrn(p, logconfName.data, logconfName.len);
        //ngx_cpystrn(p,logconfName.data,logconfName.len);
        //len = ngx_strlen(p);
        //while(1)
        //{
        //    if(p[--len]=='/')
        //    {
        //        ++len;
        //        break;
        //    }
        //}
        //ngx_memcpy((u_char*)p+len, logconfName.data, logconfName.len); 
        printf("p=%s\n",p);
        printf("ptmp=%s\n",ptmp);
    }
#endif


    /*if (ngx_getcwd(p, NGX_MAX_PATH) == 0) {
        ngx_log_stderr(ngx_errno, "[emerg]: " ngx_getcwd_n " failed");
        return NGX_ERROR;
    }

    len = ngx_strlen(p);
    p[len++] = '/';
    ngx_memcpy((u_char*)p+len, logconfName.data, logconfName.len); */


    yrx_logInitLog4cplus( (char*)p ); 
    yrx_logInfo(__FILE__,__LINE__,"_yr_log_init");
    return NGX_OK;
}

typedef struct {
    ngx_str_t  uds_host;
    ngx_int_t  uds_port;
    ngx_str_t  uds_uri;
} ngx_http_udsproxy_conf_t;

static ngx_command_t  ngx_http_udsproxy_commands[] = {

    { ngx_string("udsproxy"),
      NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS,
      ngx_http_udsproxy,
      0,
      0,
      NULL },

    { ngx_string("uds_host"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_http_uds_host,
      NGX_HTTP_LOC_CONF_OFFSET,
      0,
      NULL },

    { ngx_string("uds_port"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_http_uds_port,
      NGX_HTTP_LOC_CONF_OFFSET,
      0,
      NULL },

    { ngx_string("uds_uri"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_http_uds_uri,
      NGX_HTTP_LOC_CONF_OFFSET,
      0,
      NULL },

      ngx_null_command
};


static ngx_http_module_t  ngx_http_udsproxy_module_ctx = {
    NULL,                          /* preconfiguration */
    NULL,                          /* postconfiguration */

    NULL,                          /* create main configuration */
    NULL,                          /* init main configuration */

    NULL,                          /* create server configuration */
    NULL,                          /* merge server configuration */

    ngx_http_udsproxy_create_conf,  /* create location configuration */
    ngx_http_udsproxy_merge_conf    /* merge location configuration */
};


ngx_module_t  ngx_http_udsproxy_module = {
    NGX_MODULE_V1,
    &ngx_http_udsproxy_module_ctx,      /* module context */
    ngx_http_udsproxy_commands,         /* module directives */
    NGX_HTTP_MODULE,               /* module type */
    NULL,                          /* init master */
    &init_module,                          /* init module */
    NULL,                          /* init process */
    NULL,                          /* init thread */
    NULL,                          /* exit thread */
    NULL,                          /* exit process */
    NULL,                          /* exit master */
    NGX_MODULE_V1_PADDING
};

ngx_int_t
_ngx_http_Error_handler(ngx_http_request_t *r, ngx_str_t  *errInfo);
ngx_int_t
_ngx_http_303_handler(ngx_http_request_t *r, ngx_str_t *p_path);


static ngx_int_t
ngx_http_udsproxy_handler(ngx_http_request_t *r)
{
    ngx_int_t                  rc;
    ngx_log_t                 *log;
    ngx_http_udsproxy_conf_t *ulcf;
    ngx_str_t url;
    int nRes;
    log = r->connection->log;

    ngx_log_error(NGX_LOG_ERR, log, 0, "==!!== uri: %V args: %V exten: %V request_line: %V unparsed_uri: %V.", &r->uri, &r->args, &r->exten, &r->request_line, &r->unparsed_uri);

    if (!(r->method & (NGX_HTTP_GET|NGX_HTTP_HEAD))) {
        return NGX_HTTP_NOT_ALLOWED;
    }


    if (r->uri.data[r->uri.len - 1] == '/') {
        return NGX_DECLINED;
    }

    rc = ngx_http_discard_request_body(r);

    if (rc != NGX_OK) {
        return rc;
    }

    ulcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

    ulcf = ngx_http_get_module_loc_conf(r, ngx_http_udsproxy_module);
    ngx_log_error(NGX_LOG_ERR, log, NGX_EACCES, "udsproxy local conf host: %V port: %d uri: %V", &ulcf->uds_host, ulcf->uds_port, &ulcf->uds_uri);

    nRes = get_flv_real_path(&ulcf->uds_host, ulcf->uds_port, &ulcf->uds_uri, &r->args, &url);
    /*rc = get_uds_file_url(r, &ulcf->uds_host, ulcf->uds_port, &ulcf->uds_uri, &r->args, &url);*/
    if ( nRes > 0 ) 
    {
        rc =_ngx_http_303_handler(r, &url);
    }
    else
    {
        rc = _ngx_http_Error_handler(r, &url);
    }
    return rc;
}

/* ******************************************************************* */

ngx_int_t _ngx_http_303_handler(ngx_http_request_t *r, ngx_str_t *p_path){

    ngx_str_t contentType;
    ngx_buf_t *b;
    ngx_chain_t                out;
    ngx_log_t *log = r->connection->log;

    ngx_str_t path = *p_path;
    ngx_log_error(NGX_LOG_ERR, log, NGX_EACCES, "==xx== Enter   _ngx_http_303_handler(), path:%V", &path);

    r->headers_out.status = NGX_HTTP_SEE_OTHER;
    /*r->headers_out.content_length_n = 0;*/

    ngx_str_set(&contentType, "text/html" );
    r->headers_out.content_type_len = contentType.len;
    r->headers_out.content_type = contentType;

    ngx_http_clear_location(r);
    r->headers_out.location = ngx_list_push(&r->headers_out.headers);
    r->headers_out.location->hash = 1;
    ngx_str_set(&r->headers_out.location->key, "Location");
    r->headers_out.location->value = path;

    ngx_http_send_header(r);
    /*if (rc == NGX_ERROR || rc > NGX_OK || r->header_only) {*/
        /*return rc;*/
    /*}*/
    
    b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));
    b->file_pos = 0;
    b->file_last = 0;

    b->in_file = 0;
    b->last_buf = 1;
    b->last_in_chain = 1;

    out.buf = b;
    out.next = NULL;

    ngx_log_error(NGX_LOG_ERR, log, NGX_EACCES, "==xx== Leave  _ngx_http_303_handler(), path:%V", &path);

    /*return NGX_OK;*/
    return ngx_http_output_filter(r, &out);
}

ngx_int_t
_ngx_http_Error_handler(ngx_http_request_t *r, ngx_str_t *errInfo)
{
    ngx_int_t     rc;  
    ngx_buf_t    *b;  
    ngx_chain_t   out;  

    ngx_str_t respbody = *errInfo;
//    ngx_str_t respbody = *errInfo;
    if (!(r->method & (NGX_HTTP_GET|NGX_HTTP_HEAD))) {  
        return NGX_HTTP_NOT_ALLOWED;  
    }  
    if (r->headers_in.if_modified_since) {  
        return NGX_HTTP_NOT_MODIFIED;  
    }  

    r->headers_out.content_type.len = sizeof("text/html;charset=utf-8") - 1;  
    r->headers_out.content_type.data = (u_char *) "text/html;charset=utf-8";  
    //r->headers_out.charset.len = sizeof("utf-8")-1;
    //r->headers_out.charset.data = (u_char*)("utf-8");

    r->headers_out.status = NGX_HTTP_OK;  
    r->headers_out.content_length_n = respbody.len;
    if (r->method == NGX_HTTP_HEAD) {  
        rc = ngx_http_send_header(r);  

        if (rc == NGX_ERROR || rc > NGX_OK || r->header_only) {  
            return rc;  
        }  
    }  

    b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));  
    if (b == NULL) {  
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "Failed to allocate response buffer.");  
        return NGX_HTTP_INTERNAL_SERVER_ERROR;  
    }  

    out.buf = b;  
    out.next = NULL;  


    b->pos = respbody.data; 
    b->last = respbody.data + respbody.len;

    b->memory = 1;  
    b->last_buf = 1;  
    rc = ngx_http_send_header(r);  

    if (rc == NGX_ERROR || rc > NGX_OK || r->header_only) {  
        return rc;  
    }  
    return ngx_http_output_filter(r, &out);  
}

static void *
ngx_http_udsproxy_create_conf(ngx_conf_t *cf)
{
    ngx_http_udsproxy_conf_t  *conf;

    conf = ngx_pcalloc(cf->pool, sizeof(ngx_http_udsproxy_conf_t));
    if (conf == NULL) {
        return NULL;
    }

    /*
     * set by ngx_pcalloc():
     *
     *     conf->uds_host = { 0, NULL };
     *     conf->uds_port = 0;
     *     conf->uds_uri = { 0, NULL };
     */

    return conf;
}


static char *
ngx_http_udsproxy_merge_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_udsproxy_conf_t *prev = parent;
    ngx_http_udsproxy_conf_t *conf = child;

    ngx_conf_merge_str_value(conf->uds_host, prev->uds_host, "localhost");
    if ( conf->uds_port == 0 ) {
        if ( prev->uds_port > 0 ) {
            conf->uds_port = prev->uds_port;
        }
    }
    ngx_conf_merge_str_value(conf->uds_uri, prev->uds_uri, "");

    return NGX_CONF_OK;
}

static char *
ngx_http_uds_host(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_udsproxy_conf_t *ulcf = conf;

    ngx_str_t        *value;

    if (ulcf->uds_host.data != NULL) {
        return "uds_host is duplicate";
    }

    value = cf->args->elts;

    if (value[1].len == 0) {
        ulcf->uds_host.len = 0;
        ulcf->uds_host.data = (u_char*)0;
    } else 
        ulcf->uds_host = value[1];

    return NGX_CONF_OK;
}


static char *
ngx_http_uds_port(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_udsproxy_conf_t *ulcf = conf;

    ngx_str_t        *value;

    value = cf->args->elts;

    if (value[1].len == 0) {
        ulcf->uds_port = 80;
    } else
        ulcf->uds_port = atoi((const char*)value[1].data);

    return NGX_CONF_OK;
}

static char *
ngx_http_uds_uri(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_udsproxy_conf_t *ulcf = conf;

    ngx_str_t        *value;

    if (ulcf->uds_uri.data != NULL) {
        return "uds_uri is duplicate";
    }

    value = cf->args->elts;

    if (value[1].len == 0) {
        ulcf->uds_uri.len = 0;
        ulcf->uds_uri.data = (u_char*)0;
    } else
        ulcf->uds_uri = value[1];
    

    return NGX_CONF_OK;
}

static char *
ngx_http_udsproxy(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_core_loc_conf_t  *clcf;

    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_udsproxy_handler;

    return NGX_CONF_OK;
}

