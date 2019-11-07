#include <string>
#include <vector>
#include <list>
#include <tuple>
#include "print_ip.h"


int main()
{
	char c = -1;
	short sh = 0;
	int i = 2130706433;
	int64_t l = 8875824491850138409;
	std::string s = { "192.168.10.1" };
	std::vector<int> v1 = {213, 34, 0, 45};
	std::list<short> l1 = { 223, 123, 45, 67 };

	print_ip(c);
	print_ip(sh);
	print_ip(i);
	print_ip(l);
	print_ip(s);
	print_ip(v1);
	print_ip(l1);
	print_ip(std::make_tuple(123, 46, 78, 0));

	return 0;
}
