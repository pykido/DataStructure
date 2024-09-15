#include <iostream>
#include <vector>

using namespace std;

int land[101][1001] = {0}; // 행은 최대 100, 열은 최대 가능한 값으로 조정

int main() {
    // 1. 수평 방향으로 깔린 왼쪽에서 연속된 벽돌 입력 받기
    vector<int> hl, hr;
    int row_length, col_length, n, i = 0, maxVal = 0;
    while (cin >> n && n != -9) {
        hl.push_back(n);
        maxVal = max(n, maxVal);
    }
    row_length = hl.size();

    // 2. 수평 방향으로 오른쪽에서부터 깔린 연속된 벽돌 입력 받기
    bool flag = true;
    while (cin >> n && n != -9) {
        hr.push_back(n);
        if ((n != 0) && (n != -9)) flag = false; // 전부 0이 입력되지 않는 경우
    }
    if (flag) col_length = maxVal + 1;
    else col_length = maxVal;

    // 3. 왼쪽부터 수직방향으로 장애물이 차지하는 벽돌 수의 리스트를 구하기!!
    for (int r = 0; r < row_length; ++r) {
        int cnt_r = hl[r];
        int cnt_c = hr[r];
        for (int c = 0; c < col_length; ++c) {
            if ((c > (cnt_r-1) && ((col_length - cnt_c) > c))) { // 장애물이 있음
                land[r][c] = 1;
            }
        }
    }

    // 4. 장애물이 차지하는 벽돌 수의 수직방향 합계리스트 출력하기
    for (int c = 0; c < col_length; ++c) {
        int result = 0;
        for (int r = 0; r < row_length; ++r) {
            if (land[r][c] == 1) {
                result++;
            }
        }
        cout << result << " ";
    }
    cout << -9;

    return 0;
}