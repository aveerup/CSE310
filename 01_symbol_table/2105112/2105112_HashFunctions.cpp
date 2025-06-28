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

unsigned int RSHash(const string &str, unsigned int bucketSize) {
    unsigned int b = 378551;
    unsigned long a = 63689;
    unsigned long hash = 0;

    for (char c : str) {
        hash = hash * a + c;
        a *= b;
    }
    return hash % bucketSize;
}

unsigned int BKDRHash(const string &str, unsigned int bucketSize) {
    unsigned long hash = 0;
    unsigned int seed = 131; // or 31, 131, 1313, 13131...
    for (char c : str) {
        hash = hash * seed + c;
    }
    return hash % bucketSize;
}


unsigned int Hash_function(string str, unsigned int num_buckets, string hash_name){
    
	if(hash_name == "BKDR")
		return BKDRHash(str, num_buckets);
	else if(hash_name == "RS")
		return RSHash(str, num_buckets);
	else
		return SDBMHash(str, num_buckets);

}

