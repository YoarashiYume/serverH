#ifndef PACKAGE_H
#define PACKAGE_H

#include <unordered_map>
#include <string_view>
#include <sstream>

/**
 \brief Strores all info from the incommong socket
 */
class Package final
{
public:
    using parameterContainer = std::unordered_map<std::string,std::string>;
private:
    parameterContainer parameterList;///< parameters passed by REST request
    parameterContainer header;///< information about the REST request
public:
	/**
	\brief Constructor
	Automatically reads the received information
	\param info request received
	*/
    Package(const std::string_view info);//Parses incoming info
	/**
	\brief Method returns the number of parameters in the request
	\return parameterList.size()
	*/
    std::size_t paramCount() const;
	/**
	\brief Method returns request type
	\return REST-request type
	*/
    std::string getUri() const;
	/**
	\brief Method returns request method
	\return REST-request method
	*/
    std::string getMethod() const;
	/**
	\brief Method returns request protocol
	\return REST-request protocol
	*/
    std::string getProtocol() const;
    const parameterContainer& getParam() const;
};

#endif // PACKAGE_H
