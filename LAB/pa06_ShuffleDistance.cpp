#include <iostream>
#include <algorithm>

using namespace std;

// 리스트 입력 받기
int inputList(int* list) {
    int index = 0, number = 0;
    cin >> number;
    while (number != -9) {
        list[index++] = number;
        cin >> number;
    }
    return index;
}

// 리스트를 섞기
int* shuffle(int* list, int size) {
    int half_size = (size + 1) / 2;
    int first_half[half_size], second_half[half_size];
    int index_first = 0, index_second = 0;

    // 리스트를 두 부분으로 나누기
    for (int i = 0; i < half_size; i++) {
        first_half[i] = list[i];
    }
    for (int i = 0; i < size / 2; i++) {
        second_half[i] = list[half_size + i];
    }

    // 섞은 결과를 원래 리스트에 저장
    for (int i = 0; i < size; i++) {
        if (i % 2 == 0)
            list[i] = first_half[index_first++];
        else
            list[i] = second_half[index_second++];
    }
    return list;
}

// 두 리스트가 다른지 확인하는 함수
int validateDifference(int* list1, int* list2, int size) {
    for (int i = 0; i < size; i++) {
        if (list1[i] != list2[i]) {
            return 1; // 다름
        }
    }
    return 0; // 같음
}

// 리스트를 복사하는 함수
void copyArray(int* source, int* destination, int size) {
    for (int i = 0; i < size; i++) {
        destination[i] = source[i];
    }
}

// 섞기 횟수를 계산하는 함수
int countShuffle(int* start_list, int* target_list, int* temp_list, int size) {
    int shuffle_count = 0;
    copyArray(start_list, temp_list, size);
    while (1) {
        if (!validateDifference(target_list, temp_list, size)) break;
        temp_list = shuffle(temp_list, size);
        shuffle_count++;
        if (shuffle_count > 5000) {
            cout << "NOT";
            return -1;
        }
    }
    return shuffle_count;
}

int main() {
    int size = 0, count_start_to_list1 = 0, count_start_to_list2 = 0;
    int count1 = 0, count2 = 0, min_count = 0;

    int *sorted_list, *list1, *list2, *temp_list;
    sorted_list = new int[5001];
    list1 = new int[5001];
    list2 = new int[5001];
    temp_list = new int[5001];

    // 1. 리스트 입력
    size = inputList(list1);
    size = inputList(list2);

    // 2. 원본 리스트를 정렬하여 sorted_list에 저장
    copyArray(list1, sorted_list, size);
    sort(sorted_list, sorted_list + size);

    // 3. 시작 리스트에서 각 리스트로의 섞기 횟수 계산하기
    count_start_to_list1 = countShuffle(sorted_list, list1, temp_list, size);
    if (count_start_to_list1 == -1) return 0;
    count_start_to_list2 = countShuffle(sorted_list, list2, temp_list, size);
    if (count_start_to_list2 == -1) return 0;

    // 4. list1에서 list2로의 섞기 횟수 계산
    count1 = countShuffle(list1, list2, temp_list, size);
    if (count1 == -1) return 0;
    count2 = countShuffle(list2, list1, temp_list, size);
    if (count2 == -1) return 0;

    // 5. 출력하기
    min_count = (count1 < count2) ? count1 : count2;
    cout << min_count;

    return 0;
}