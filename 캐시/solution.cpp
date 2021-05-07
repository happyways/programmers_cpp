#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(int cacheSize, vector<string> cities) {
    //begin쪽이 사용한지 가장 오래된 값
    //end쪽이 가장 최근에 사용한 값
    list<string> cache;
    
    int total_running_time = 0;
    for ( auto& city : cities ) {
        //대소문자를 구분하지 않기 때문에 소문자로 통일
        transform(city.begin(), city.end(), city.begin(), ::tolower);
        
        //이미 cache에 있는지 확인
        auto find_iter = find(cache.begin(), cache.end(), city);
        if ( find_iter != cache.end() ) {
            total_running_time += 1;
            cache.erase(find_iter);
        }
        else {
            total_running_time += 5;
        }
        cache.emplace_back(city);
        
        //cache사이즈를 초과했으면, 가장 오래된 값 삭제
        if ( cache.size() > cacheSize ) {
            cache.erase(cache.begin());
        }
        
    }
    
    return total_running_time;
}
