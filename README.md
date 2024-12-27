# Project1_Sort
## 개요

---

- 표준 라이브러리 `sort` 함수처럼 반복자와 비교함수를 받아서 동작하게 만들었습니다.
- buble, insertion, quick, merge로 구현했습니다.

## 알고리즘 설명

---

### quick sort

---

- 요소가 N개인 컨테이너를 오름차순 정렬할 때
- 요소중 하나를 집어서 pivot으로 삼고 pivot보다 작은 요소를 왼쪽, pivot보다 큰 요소를 오른쪽으로 배치
    - 연산량 N에 비례
    - 제 코드에서는 메이저한 방법을 따라 항상 첫 번째 요소를 pivot으로 잡고 다음과 같은 로직으로 구현했습니다.
  ![KakaoTalk_20241227_135035828](https://github.com/user-attachments/assets/5b129d6a-48ec-40c3-8546-3ff1156679a9)



- pivot을 제외한 왼쪽 부분과 오른쪽 부분에 대해서 반복
    - 횟수 약 log_2(N)
    ![KakaoTalk_20241227_134937698](https://github.com/user-attachments/assets/07a2c670-efff-4ad6-ab13-e8dce6823028)
- 하는 방식으로 동작하는 정렬 알고리즘입니다.
    - 시간복잡도 O(N logN)
