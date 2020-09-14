#ifdef _MSC_VER
#include <iostream>
#include <cassert>
#include <type_traits>
#else
#include <bits/stdc++.h>
#endif // _MSC_VER

// for memory leak detection
#if (defined _MSC_VER) && (defined _DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <cstdlib> 
#include <crtdbg.h>
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif // defined (_MSC_VER && _DEBUG)
using namespace std;

int main()
{
#ifdef _INC_CRTDBG
	_CrtDumpMemoryLeaks();
#endif 
 	return 0;
}

