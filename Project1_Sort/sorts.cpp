#include "iteratorSorts.h"
#include <functional>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#define MAX_SIZE 10
#define MIN_SIZE 1

using namespace std;

// 일단 사용자 입력받고 기본 배열로 입력받아서 오름차순 내림차순 정렬하는것 부터
// 사용자에게 입력받는 부분은

enum CompareMode { ASCEND = 1, DESCEND };

int getArraySum(int* arr, int size) {
    int result{ 0 };
    for (int i = 0; i < size; i++) {
        result += arr[i];
    }
    return result;
}

float getArrayAvg(int* arr, int size) {
    int sum = getArraySum(arr, size);
    return float(sum) / size;
}

bool ascendingCompare(int a, int b) {
    return a < b;
}

bool descendingCompare(int a, int b) {
    return a > b;
}

void setNumber(int& n, int i) {
    while (true) {
        cout << i + 1 << "번째 " << "정수 요소 입력: ";
        string input;
        cin >> input;

        stringstream ss(input);
        if (ss >> n) {
            if (ss.eof()) {
                break;
            }
        }

        cout << "잘못된 입력. 숫자를 입력해주세요." << endl << endl;
    }
}

int main(int argc, char const* argv[]) {
    int size;
    CompareMode compareMode{ ASCEND };

    // 배열 크기 입력
    while (true) {
        cout << "길이 입력(" << MIN_SIZE << "이상 " << MAX_SIZE << "이하; "
            << MAX_SIZE << "개 넘어가면 입력하기 힘듬): ";
        string input;
        cin >> input;

        stringstream ss(input);
        if (ss >> size) {
            if (ss.eof()) {
                if (size >= MIN_SIZE && size <= MAX_SIZE) {
                    break;
                }
                else {
                    cout << "입력값은 " << MIN_SIZE << "에서 " << MAX_SIZE
                        << " 사이의 정수." << endl;
                }
            }
        }

        cout << "잘못된 입력. 숫자를 입력해주세요." << endl << endl;
    }

    // 배열 요소 입력
    int* arr = new int[size] {};

    for (int i = 0; i < size; i++) {
        setNumber(arr[i], i);
    }

    // 정렬 방식 설정
    while (true) {
        cout << endl << "---정렬 방향 설정---" << endl;
        cout << "1: 오름차순, 2: 내림차순" << endl;

        cout << "입력: ";
        int tmp;
        string input;
        cin >> input;

        stringstream ss(input);
        if (ss >> tmp) {
            if (ss.eof()) {
                if (tmp == 1 || tmp == 2) {
                    compareMode = CompareMode(tmp);
                    break;
                }
                else {
                    cout << "입력값은 1또는 2" << endl;
                }
            }
        }

        cout << "잘못된 입력. 숫자를 입력해주세요." << endl << endl;
    }

    // 정렬
    switch (compareMode) {
    case ASCEND:
        quickSortIt(arr, arr + size, ascendingCompare);
        break;
    case DESCEND:
        quickSortIt(arr, arr + size, descendingCompare);
        break;
    }


	cout << endl << "-----결과출력-----" << endl;

    // 정렬 결과 출력
	cout << "정렬 결과: ";
    for (auto it = arr; it < arr + size; it++) {
        cout << *it << " ";
    }
    cout << endl;

	// 배열 요소의 합과 평균 출력
	cout << "배열 요소의 합: " << getArraySum(arr, size) << endl;
	cout << "배열 요소의 평균: " << getArrayAvg(arr, size) << endl;

    return 0;
}
