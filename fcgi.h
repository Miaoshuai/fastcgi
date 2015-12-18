/*======================================================
    > File Name: fcgi.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月17日 星期四 01时14分57秒
 =======================================================*/
#ifndef FCGI_
#define FCGI_

#include "fast_cgi.h"

#include <string>

class FastCgi
{
    public:
        FastCgi();
        ~FastCgi();

        //设置套接字的值
        //void setSockfd(){sockfd_ = startConnect();}
        //设置请求Id
        void setRequestId(int requestId){requestId_ = requestId;}
        //生成头部
        FCGI_Header makeHeader(int type,int request,
                               int contentLength,int paddingLength);
        //生成发起请求的请求体
        FCGI_BeginRequestBody makeBeginRequestBody(int role,int keepConnection);
        
        //生成PARAMS的name-value body
        bool makeNameValueBody(std::string name,int nameLen,
                               std::string value,int valueLen,
                               unsigned char *bodyBuffPtr,int *bodyLen);

        //获取express_help.conf配置文件中的ip地址
        std::string getIpFromConf(void);
        
        //连接php-fpm，如果成功则返回对应的套接字描述符
        void startConnect(void);

        //发送开始请求记录
        bool sendStartRequestRecord(void);
        
        //向php-fpm发送name-value参数对
        bool sendParams(std::string name,std::string value);

        //发送结束请求记录
        bool sendEndRequestRecord(void);

        //只读php-fpm返回内容，读到的内容处理后期在添加
        bool readFromPhp(void);
    private:
        //从内容中提取html文件
        void getHtmlFromContent(char *content);
        //找到html开始处
        char *findStartHtml(char *content);

        int sockfd_;     //与php-fpm建立的sockfd
        int requestId_;  //record里的请求ID
        int flag_;        //用来标志当前读取内容是否为html内容
        
        static const int PARAMS_BUFF_LEN = 1024; //环境参数buffer的大小
        static const int CONTENT_BUFF_LEN = 1024;//内容buffer的大小
};

#endif
