#include "package.h"

Package::Package(const std::string_view info)
{
    std::istringstream stream{info.data()};
    std::string token;
    while (std::getline(stream,token,' '))
    {
        if (token.front() == 47)
        {
            header["Request"] = token;
            break;
        }
        header["Method"] = token;
    }
    while (std::getline(stream,token,'\r'))
    {
        if (header.contains("Content-Type:"))
        {//Parses simple data
            stream.str(stream.str().substr((int)stream.tellg()+token.length()));
            while (std::getline(stream,token,'&'))
                parameterList[token.substr(0,token.find('='))] = token.substr(token.find('=')+1);
            return;
        }
        if (token.front()!='\n')
        {
            header["Protocol"] = token;
            continue;
        }
        else
        {
            token = token.substr(1);
            header[token.substr(0,token.find(' '))] = token.substr(token.find(' ')+1);
        }

    }
}


std::size_t Package::paramCount() const
{
    return parameterList.size();
}

std::string Package::getUri() const
{
    return header.at("Request");
}

std::string Package::getMethod() const
{
    return header.at("Method");
}

std::string Package::getProtocol() const
{
    return header.at("Protocol");
}

const Package::parameterContainer &Package::getParam() const
{
    return parameterList;
}
