#include <iostream>
#include <vector>

using namespace std;

int main() {
    int K, N;
    cin >> K >> N;

    int num_slots = K;
    int num_cars = 0;

    vector<int> parking_lot(num_slots, -1);

    for (int i = 0; i < N; ++i) {
        int carNum;
        cin >> carNum;

        if (carNum > 0) {
            bool parked = false;
            for (int index = 0; index < num_slots; ++index) {
                if (parking_lot[index] == -1) {
                    parking_lot[index] = carNum;
                    num_cars++;
                    parked = true;
                    break;
                }
            }
            if (!parked) {
                num_slots *= 2;
                parking_lot.resize(num_slots, -1);
                for (int index = 0; index < num_slots; ++index) {
                    if (parking_lot[index] == -1) {
                        parking_lot[index] = carNum;
                        num_cars++;
                        break;
                    }
                }
            }
        } else {
            int car_to_remove = -carNum;
            bool found = false;
            for (int index = 0; index < num_slots; ++index) {
                if (parking_lot[index] == car_to_remove) {
                    parking_lot[index] = -1;
                    num_cars--;
                    found = true;
                    break;
                }
            }
            if (!found) {
                continue;
            }
            while (num_cars <= num_slots / 3 && num_slots / 2 >= K) {
                num_slots /= 2;
                vector<int> temp_parking_lot(num_slots, -1);
                int idx = 0;
                for (int j = 0; j < parking_lot.size(); ++j) {
                    if (parking_lot[j] != -1) {
                        temp_parking_lot[idx++] = parking_lot[j];
                        if (idx == num_slots) {
                            break;
                        }
                    }
                }
                parking_lot = temp_parking_lot;
            }
        }
    }

    for (int i = 0; i < num_slots; ++i) {
        if (parking_lot[i] != -1) {
            cout << i + 1 << " " << parking_lot[i] << endl;
        }
    }

    return 0;
}