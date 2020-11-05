#include <chaiscript/chaiscript.hpp>
#include <string>
#include <functional>

std::string helloWorld(const std::string& t_name)
{
	return "Hello " + t_name + " - 'e's not the Messiah!";
}

class MyClass
{
public:
	int sum(int const N)
	{
		int s = 0;
		for (int i = 1; i <= N; ++i)
		{
			s += i;
		}
		return s;
	}
};

int main()
{
	chaiscript::ChaiScript chai;
	chai.add(chaiscript::fun(&helloWorld), "helloWorld");
	chai.eval_file("Test.chai");
	auto enableSkynet = chai.eval<std::function<void()>>("enableSkyNet");
	enableSkynet();
	auto sum = chai.eval<std::function<void(int)>>("sumUpTo");
	std::wcout << L"sumUpTo:\n";
	sum(100);

	std::wcout << L"returnSum:\n";
	auto retSum = chai.eval<std::function<int(int)>>("returnSum");
	int amount = retSum(100);
	std::wcout << amount << std::endl;

	std::wcout << L"MyClass::sum:\n";
	chai.add(chaiscript::user_type<MyClass>(), "MyClass");
	chai.add(chaiscript::fun(&MyClass::sum), "sum");
	auto retMemberSum = chai.eval<std::function<int(MyClass*, int)>>("callMemberFunc");
	MyClass obj;
	int res = retMemberSum(&obj, 100);
	std::wcout << res << std::endl;
	return 0;
}