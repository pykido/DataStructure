#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// 문제 유형 : 자료구조, 정렬, 그리디

// 새롭게 배우는 내용들
// 1. unordered_map
// - 해시맵으로 키(Key)값을 기준으로 데이터를 매우 빠르게 찾는다.
// - 해시함수를 통해 데이터를 저장하고 조회하기에 O(1)의 시간 복잡도로 데이터를 찾을 수 있다.
// - 해시맵의 각 원소는 키와 그에 대응하는 값의 쌍으로 이루어져 있는데 이 쌍을 entry라고 한다.
// - 해시맵의 entry들을 순회하는 방법
//   for (auto& entry : myMap) {
//      // entry.first는 key, entry.second는 value
//      cout << entry.first << ": " << entry.second << endl;
//   }
//
// 2. const
// - 자바에서 final과 같음
// - 변경되지 않는 데이터를 의미
// 3. 참조와 복사
// - vector<int> number; 에 대하여....
// - vector<int>& number1 = number; -> 참조한다. 메모리 오버헤드가 발생하지 않으며 성능 면에서 효율적이다.
// - vecotr<int> number2 = number; -> 복사한다. 복사 비용이 발생한다.

int main() {
    // n은 플레이어 수, k는 각 플레이어가 가진 숫자 수
    int n, k;
    cin >> n >> k;

    // 각 플레이어의 숫자판을 저장할 2차원 벡터
    vector<vector<int> > number_board(n);

    // 숫자를 기준으로 그 숫자를 가진 플레이어 목록을 저장한다.
    unordered_map<int, vector<int> > number_to_players;

    // 각 플레이어가 마지막에 끝날 수 있는지 여부를 저장할 벡터, 기본값은 true
    vector<bool> can_be_last(n, true);

    // 1. 숫자판 숫자 입력 받기 && 해당 숫자를 가진 플레이어 기록하기
    for (int i = 0; i < n; ++i) {
        number_board[i].resize(k); // 각 플레이어가 가진 숫자는 k개이다.
        for (int j = 0; j < k; ++j) {
            int num;
            cin >> num;
            number_board[i][j] = num;  // 각 플레이어의 숫자판에 숫자 저장
            number_to_players[num].push_back(i);  // ⭐️⭐️ 해당 숫자를 가진 플레이어 기록 (해당 숫자를 key에 플레이어를 vector에 기록)
        }
    }

    // 2. 동일한 숫자를 가진 플레이어들에 대해 우선순위가 낮은 플레이어들은 해당 숫자를 지울 수 없도록 처리
    for (auto& entry : number_to_players) {
        vector<int>& players = entry.second; // 해당 숫자를 가진 플레이어들의 주소값
        if (players.size() >= 2) {  // 동일한 숫자를 여러 플레이어가 가지고 있다면
            vector<int> sorted_players = players; // 복사
            sort(sorted_players.begin(), sorted_players.end()); // 플레이어의 우선순위에 따라 정렬 (우선순위 : 작은 번호가 빠른 플레이어)
            // ⭐️⭐️ 정렬된 플레이어들 중에서 가장 빠른 반응 속도를 가진 첫 번째 플레이어는 마지막으로 끝날 가능성이 없다.
            for (size_t i = 0; i < sorted_players.size() - 1; ++i) {
                can_be_last[sorted_players[i]] = false ;
            }
        }
    }

    // 3. 마지막으로 끝날 수 있는 플레이어 수 카운트
    int total_can_be_last = 0;
    for (bool flag : can_be_last) {
        if (flag) {
            ++total_can_be_last;
        }
    }

    // 4. 출력하기
    // 각 플레이어의 마지막에 끝날 확률 출력
    for (int i = 0; i < n; ++i) {
        if (can_be_last[i]) {
            double probability = 1.0 / total_can_be_last;  // ⭐️⭐️ 마지막으로 끝날 수 있는 플레이어들 중에서의 확률 계산
            printf("%.10f\n", probability);  // 소수점 10자리까지 확률 출력
        } else {
            printf("%.10f\n", 0.0);  // 마지막으로 끝날 수 없는 플레이어는 0.0 출력
        }
    }

    return 0;
}