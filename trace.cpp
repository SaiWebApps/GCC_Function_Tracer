#include <iostream>
#include <list>
#include <stdio.h>
#include <dlfcn.h>
#include <cxxabi.h>
#include <string.h>

using namespace std;

list<string> function_stack;

extern "C" 
{
	//Get the name of the function located at the specified address.
	char *get_function_name(void *func_ptr)
	{
		Dl_info i;
		int status = 0;
		char *func_name = NULL;

		//Get mangled function name.
		dladdr(func_ptr, &i);
		//Demangle mangled-name to get actual function name.
		func_name = abi::__cxa_demangle(i.dli_sname, 0, 0, &status);

		//If the function name is NULL, then it's main().
		if (func_name == NULL) {
			func_name = "main()";
		}
		return func_name;
	}

	void print_function_stack()
	{
		string result("");
		while (!function_stack.empty()) {
			result = result + function_stack.front();
			function_stack.pop_front();
			//Add arrow after function name as long as it isn't the last one.
			if (!function_stack.empty()) {
				result = result + " -> ";
			}
		}
		//Print out the list of functions that we've gone through.
		cout << result << endl;
	}

	//Triggered whenever we enter a function dest from function src
	void __cyg_profile_func_enter(void *dest, void *src)
	{
		char *func_name = get_function_name(dest);
		function_stack.push_back(string(func_name));
	}

	//Triggered whenever we exit function dest
	void __cyg_profile_func_exit(void *dest, void *src)
	{
		const char *func_name = get_function_name(dest);
		const char *prev_func = function_stack.back().c_str();

		if (prev_func != NULL && strcmp(func_name, prev_func) != 0) {
			function_stack.push_back(func_name);
		}

		//If we are exiting the main function, then program is over, so print out stack.
		if (strcmp(func_name, "main()") == 0) {
			print_function_stack();
		}
	}
}
