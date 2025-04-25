#include <string>
using namespace std;

unsigned int SDBMHash ( string str , unsigned int num_buckets ) {
	unsigned int hash = 0;
	unsigned int len = str . length () ;

	for ( unsigned int i = 0; i < len ; i ++)
	{
		hash = (( str [ i ]) + ( hash << 6) + ( hash << 16) - hash ) % num_buckets ;
	}

		return hash ;
	}

unsigned int Hash_function(string str, unsigned int num_buckets){
    return SDBMHash(str, num_buckets);
}

