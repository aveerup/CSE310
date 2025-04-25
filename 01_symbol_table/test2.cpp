#include<bits/stdc++.h>
using namespace std;

int main(){
    ifstream fin("input.txt");
    string line;
    long long num_buckets;
    fin >> num_buckets;
    cout<<num_buckets<<endl;
    while(getline(fin, line)){
        cout<<line<<endl;        
    }
}