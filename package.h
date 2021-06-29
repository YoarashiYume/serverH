#ifndef PACKAGE_H
#define PACKAGE_H
/*
 *Strores all info from the incommong socket
 **/
#include <unordered_map>
#include <algorithm>
#include <sstream>

class Package
{
public:
    using parameterContainer = std::unordered_map<std::string,std::string>;
private:
    parameterContainer parameterList;
    parameterContainer header;
public:
    Package() = default;
    Package(std::string_view info);//Parses incoming info
    Package(const Package& other);
    Package(Package&& other);
    Package& operator=(const Package& other);
    Package &operator=(Package&& other);
    std::size_t paramCount() const;
    std::string getUri() const;
    std::string getMethod() const;
    std::string getProtocol() const;
    const parameterContainer& getParam() const;
};

#endif // PACKAGE_H
