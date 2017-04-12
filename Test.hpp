#ifndef Test_hpp
#define Test_hpp
#include <string>

class Test
{
public:
	Test( void );
	Test( Test const & src );
	virtual ~Test( void );

	Test & operator=( Test const & rhs );

private:
	std::string yo;
	std::string const yoyo;
	int yo2;
	double const yo3;

	double yoyoyo;
};

#endif
