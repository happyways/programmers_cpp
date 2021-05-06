//https://programmers.co.kr/learn/courses/30/lessons/17681

#include <string>
#include <vector>
#include <sstream>

using namespace std;

string createSharpAndBlankStringFromBinary(int n, int value) {
    ostringstream oss;
    int cur_bit = 1 << (n-1);
    
    for ( int i = 0 ; i < n ; i++ ) {
        ( value & cur_bit ) ? (oss << "#") : (oss << " ");
        cur_bit >>= 1;
    }
    
    return oss.str();
}

vector<string> solution(int n, vector<int> arr1, vector<int> arr2) {
    //bit 연산자 or를 사용 
    for ( int i = 0 ; i < arr2.size() ; i++ ) {
        arr1[i] |= arr2[i];
    }
    
    //row별로 sharp, blank string 생성
    vector<string> answer;
    for ( int row : arr1 ) {
        answer.emplace_back(createSharpAndBlankStringFromBinary(n, row));
    }
    return answer;
}
