/*======================================================
    > File Name: fast_cgi.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月16日 星期三 23时20分45秒
 =======================================================*/

#ifndef FASTCGI_H
#define FASTCGI_H

//监听sock
#define FCGI_LISTENSOCK_FILENO 0

typedef struct 
{
    unsigned char version;              //版本
    unsigned char type;                 //操作类型
    unsigned char requestIdB1;          //请求id
    unsigned char requestIdB0;          
    unsigned char contentLengthB1;      //内容长度
    unsigned char contentLengthB0;
    unsigned char paddingLength;        //填充字节的长度
    unsigned char reserved;             //保留字节
}FCGI_Header;

//允许传送的最大数据65536
#define FCGI_MAX_LENGTH 0xffff

//上述FCGI_HEADER长度
#define FCGI_HEADER_LEN  8


//FCGI的版本
#define FCGI_VERSION_1           1

//上述FCGI_Header中type的具体值
#define FCGI_BEGIN_REQUEST       1      //开始请求
#define FCGI_ABORT_REQUEST       2      //异常终止请求
#define FCGI_END_REQUEST         3      //正常终止请求
#define FCGI_PARAMS              4      //传递参数
#define FCGI_STDIN               5      //POST内容传递
#define FCGI_STDOUT              6      //正常响应内容
#define FCGI_STDERR              7      //错误输出
#define FCGI_DATA                8
#define FCGI_GET_VALUES          9
#define FCGI_GET_VALUES_RESULT  10
#define FCGI_UNKNOWN_TYPE       11      //通知webserver所请求type非正常类型
#define FCGI_MAXTYPE (FCGI_UNKNOWN_TYPE)


//空的请求ID
#define FCGI_NULL_REQUEST_ID     0

typedef struct 
{
    unsigned char roleB1;       //web服务器所期望php-fpm扮演的角色，具体取值下面有
    unsigned char roleB0;
    unsigned char flags;        //确定php-fpm处理完一次请求之后是否关闭
    unsigned char reserved[5];  //保留字段
}FCGI_BeginRequestBody;

typedef struct 
{
    FCGI_Header header;         //webserver请求php-fpm的请求头
    FCGI_BeginRequestBody body;//请求体

}FCGI_BeginRequestRecord;


//webserver期望应用扮演的角色
#define FCGI_KEEP_CONN  1       //如果为0则处理完请求应用就关闭，否则不关闭
#define FCGI_RESPONDER  1       //接受http关联的所有信息,并产生http响应，接受来自webserver的PARAMS环境变量
#define FCGI_AUTHORIZER 2       //对于认证的会关联其http请求,未认证的则关闭请求
#define FCGI_FILTER     3       //过滤web服务器中的额外数据流，并产生过滤后的http响应

typedef struct 
{
    unsigned char appStatusB3;      //结束状态，0为正常
    unsigned char appStatusB2;
    unsigned char appStatusB1;
    unsigned char appStatusB0;
    unsigned char protocolStatus;   //协议状态
    unsigned char reserved[3];
}FCGI_EndRequestBody;

typedef struct 
{
    FCGI_Header header;         //结束头
    FCGI_EndRequestBody body;   //结束体
}FCGI_EndRequestRecord;


//几种结束状态
#define FCGI_REQUEST_COMPLETE 0     //正常结束
#define FCGI_CANT_MPX_CONN    1     //拒绝新请求，单线程
#define FCGI_OVERLOADED       2     //拒绝新请求，应用负载了
#define FCGI_UNKNOWN_ROLE     3     //webserver指定了一个应用不能识别的角色



#define FCGI_MAX_CONNS  "FCGI_MAX_CONNS"    //可接受的并发传输线路的最大值

#define FCGI_MAX_REQS   "FCGI_MAX_REQS"     //可接受并发请求的最大值

#define FCGI_MPXS_CONNS "FCGI_MPXS_CONNS"   //是否多路复用，其状态值也不同

typedef struct 
{
    unsigned char type;     
    unsigned char reserved[7];
}FCGI_UnknownTypeBody;

typedef struct 
{
    FCGI_Header header;
    FCGI_UnknownTypeBody body;
}FCGI_UnknownTypeRecord;

#endif
