#include "package.h"

Package::Package(std::string_view info)
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
        {
            stream.str(stream.str().substr((int)stream.tellg()+token.length()));
            while (std::getline(stream,token,'&'))
                param[token.substr(0,token.find('='))] = token.substr(token.find('=')+1);
            return;
        }
        if (token.front()!='\n')
        {
            header["Prococol"] = token; continue;
        }
        else
        {
            token = token.substr(1);
            header[token.substr(0,token.find(' '))] = token.substr(token.find(' ')+1);
        }

    }
}

Package::Package(const Package &other)
{
    this->header = other.header;
    this->param = other.param;
}

Package::Package(Package &&other)
{
    this->header = std::move(other.header);
    this->param = std::move(other.param);
}

Package &Package::operator=(Package &&other)
{
    if (this == &other)
        return *this;
    this->header = std::move(other.header);
    this->param = std::move(other.param);
    return *this;
}
Package &Package::operator=(const Package &other)
{
    if (this == &other)
        return *this;
    this->header = other.header;
    this->param = other.param;
    return *this;
}


std::size_t Package::paramSize() const
{
    return param.size();
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
    return header.at("Prococol");
}

const Package::paramCont &Package::getParam() const
{
    return param;
}
