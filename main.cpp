#include <iostream>
#include <vector>
#include <string>

#if (defined __clang) || (defined __GNUC__)
#include <bits/stdc++.h>
#endif //  (__clang__) || (__GNUC__)

using namespace std;
#if (defined _MSC_VER) && (defined _DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <cstdlib> 
#include <crtdbg.h>
#endif // (_MSC_VER && _DEBUG)

int main()
{
#if (defined _MSC_VER) && (defined _DEBUG) 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define DBG_NEW new
#endif // defined (_MSC_VER && _DEBUG)
	
	return 0;
}
