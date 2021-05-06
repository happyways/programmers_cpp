//https://programmers.co.kr/learn/courses/30/lessons/17682

#include <string>
#include <vector>
#include <cmath>   //pow
#include <numeric> //accumulate

using namespace std;

//s,d,t : 1,2,3제곱
//* : 지금 & 바로 전 점수 2배, # : 해당 점수 -1배
//점수는 0~10 : 10일 경우 2자리 일 수 있음
int solution(string dartResult) {
    vector<int> points;
    for ( int i = 0 ; i < dartResult.size() ; i++ ) {
        switch ( dartResult[i] ) {
            case 'S':
                //1제곱임으로 값이 바뀌지 않음
                //do nothing
                break;
                
            case 'D':
                //2제곱
                points.back() = pow(points.back(), 2);
                break;
                
            case 'T':
                //3제곱
                points.back() = pow(points.back(), 3);
                break;
                
            case '*':
                points.back() *= 2;
                if ( points.size() >= 2 ) {
                    //끝에서 2번째 값에 2 곱하기
                    *prev(points.end(), 2) *= 2;
                }
                break;
                
            case '#':
                points.back() *= -1;
                break;
                
            //이외의 숫자 값일 경우
            default:
                //숫자가 10일 경우 2글자 임으로 예외 처리
                if ( dartResult.compare(i, 2, "10") == 0 ) {
                    points.emplace_back(10);
                    i++;
                }
                else {
                    points.emplace_back(dartResult[i] - '0');
                }
                break;
        }
    }
    
    //accumulate : points 값 전부 더하기
    return accumulate(points.begin(), points.end(), 0);
}
