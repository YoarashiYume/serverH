#ifndef PACKAGE_H
#define PACKAGE_H

#include <unordered_map>
#include <vector>
#include <algorithm>
#include <sstream>

class Package
{
public:
    using paramCont = std::unordered_map<std::string,std::string>;
private:
    paramCont param;
    paramCont header;
public:
    Package() = default;
    Package(std::string_view info);
    Package(const Package& other);
    Package(Package&& other);
    Package& operator=(const Package& other);
    Package &operator=(Package&& other);
    std::size_t paramSize() const;
    std::string getUri() const;
    std::string getMethod() const;
    std::string getProtocol() const;
    const paramCont& getParam() const;
};

#endif // PACKAGE_H
