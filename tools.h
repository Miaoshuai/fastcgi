/*======================================================
    > File Name: tools.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月17日 星期四 13时11分25秒
 =======================================================*/
#ifndef TOOLS_
#define TOOLS_

#include <string>

//从字符串中截取配置名字和配置内容
std::pair<std::string,std::string> intercept(const char *str);

//获取key字符串对应在配置文件中的value
std::string getMessageFromFile(const std::string &key);

#endif
