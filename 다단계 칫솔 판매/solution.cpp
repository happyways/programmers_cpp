#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct Node {
    Node() : total_earned_money(0), parent(nullptr) {} 
    
    int total_earned_money;
    Node* parent;
};

//재귀로 돌면서 번 돈을 배분
void sellToothBrush(Node* node, int earned_money) {
    if ( node == nullptr ) {
        return;
    }
    
    //parent node에게 줄 10%를 제외하고, 총 번돈에 추가
    int money_of_parent = earned_money * 0.1;
    node->total_earned_money += earned_money - money_of_parent;
        
    //10%금액으로 parent node에 재귀 함수 호출
    sellToothBrush(node->parent, money_of_parent);
}

//enroll : 조직 구성원
//referral : "-"는 root node(center),
//그 외의 이름은 판매한 금액의 10%를 받는 사람(parent Node의 이름)
//seller : 판매한 사람
//amount : 판매한 개수 (* 100원이 판매한 금액)
//리턴값 : enroll순서대로 총 번 금액
vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    //1.enroll을 읽고 Node 객체로 만들기
    //이름으로 Node객체를 찾을 수 있도록 unordered_map<string, Node*>로 저장
    unordered_map<string, Node*> name_to_node_map{{"-", new Node()}};
    for_each(enroll.begin(), enroll.end(),
             [&name_to_node_map](const string& name) {
                 name_to_node_map.emplace(name, new Node());
             });
    
    //2. referral값으로 각 조직원의 parent node를 설정
    for ( int i = 0 ; i < referral.size() ; i++ ) {
        name_to_node_map[enroll[i]]->parent = name_to_node_map[referral[i]];
    }
    
    //3. 칫솔 판매 시작
    for ( int i = 0 ; i < seller.size() ; i++ ) {
        Node* node = name_to_node_map[seller[i]];
        sellToothBrush(node, amount[i] * 100);
    }
    
    //4. 각 조직원의 총 번돈을 answer에 순서대로 저장
    vector<int> answer;
    for ( const string& name : enroll ) {
        answer.emplace_back(name_to_node_map[name]->total_earned_money);
    }
    return answer;
}
