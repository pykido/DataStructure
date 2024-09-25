#include <iostream>

using namespace std;

const int MAX_RANGE = 1000;

int main() {
    int N; // 입력할 함수의 개수
    cin >> N;

    int resultArray[MAX_RANGE + 1] = {}; // 결과 함수의 계수 배열
    int globalMaxE = 0; // 가장 큰 차수
    bool globalHasNum[MAX_RANGE + 1] = {}; // 차수별로 항의 여부
    int totalTerms = 0; // 총 항의 개수


    for (int i = 0; i < N; ++i) {
        int tNum; // 해당 함수의 항 개수
        cin >> tNum;

        int tmpArray[MAX_RANGE + 1] = {}; // 현재 함수의 계수 배열
        bool tmpHasNum[MAX_RANGE + 1] = {}; // 현재 항수에 항의 여부
        int maxE = 0; // 현재 함수에서 가장 큰 차수

        // 1. 입력되는 항의 계수와 지수를 입력 받으며
        for (int j = 0; j < tNum; ++j) {
            int coef, exp;
            cin >> coef >> exp;
            tmpArray[exp] += coef;
            tmpHasNum[exp] = true;
            maxE = max(maxE, exp);
        }

        for (int j = 0; j <= maxE; ++j) {
            if (tmpHasNum[j]) {
                resultArray[j] += tmpArray[j];

                // 기존 항이 0이 되었으면 삭제 처리
                if (globalHasNum[j] && resultArray[j] == 0) {
                    globalHasNum[j] = false;
                    totalTerms--;
                }
                // 새로운 항이 추가된 경우
                else if (!globalHasNum[j] && resultArray[j] != 0) {
                    globalHasNum[j] = true;
                    totalTerms++;
                }
            }
        }

        globalMaxE = max(globalMaxE, maxE);
    }

    cout << totalTerms << '\n';
    for (int i = globalMaxE; i >= 0; --i) {
        if (globalHasNum[i]) {
            cout << resultArray[i] << " " << i << '\n';
        }
    }

    return 0;
}