/*======================================================
    > File Name: tools.cpp
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月17日 星期四 13时14分46秒
 =======================================================*/

#include <string>
#include "tools.h"
#include <string.h>

//从字符串中截取配置名字和配置内容
std::pair<std::string,std::string> intercept(const char *str)
{
    int i=0;
    std::pair<std::string,std::string> option;    //保存每行的关键字和其对应的值

    while(1)
    {
        if(str[i] == ' ')
        {
            std::string s1(str,&str[i]);
            option.first = s1;
            std::string s2(&str[i] + 3);
            s2.resize(s2.size() - 1);
            option.second = s2;
            return option;   
        }
        else
        {
            i++;
        }
    }
}


//根据key在配置文件中获得对应的属性
std::string getMessageFromFile(const std::string &key)
{
    //打开配置文件
    FILE *fp = fopen("/home/shreck/Express_help/express_help.conf","r");
    if(!fp)
    {
        printf("打开配置文件失败!\n");
    }
    char buf[1024];
    std::pair<std::string,std::string> option;
    
    while(fgets(buf,sizeof(buf),fp) != NULL)
    {
        if(buf[0] == '#')
        {
            continue;
        }
        else
        {
            option = intercept(buf);
            if(option.first == key)
            {
                return option.second;
            }
        }
        bzero(&buf,sizeof(buf));
    }
    fclose(fp);
    return NULL;   
}


