<div align="center">

## 2024 1st Semester DataStructure

</div>

### 🥅 GOAL
C를 이용해 데이터 구조 개념에 대해 알아보고 이를 이용해 간단한 게임을 만들기를 목표로 함 <br>

### 🖩 과제1
> infix, postfix를 이용한 수식 계산기 만들기
>
a. stack 개념 사용 ➡️ pop, push, peek, isfull, isempty <br>

b. linked list 개념 사용 ➡️ isp, icp


### 🏝️ 과제2
> 수건 돌리기 게임 무인도에서 탈출할 행운의 4인 정하기
>
a. SINGLY circle linked list <br>

b. DOUBLE circle linked list

```shell
head 노드가 삭제될 경우 vs head가 아닌 노드가 삭제될 경우
```

다음 노드로 이동
```shell
current = current->link;
```

```shell
이름 설정 & 게임 시작 번호 ➡️ random을 위해
#include <time.h>
srand(time(NULL)) 사용
```

### ♻️ 과제3
> selection sort
>
순서 없이 주어진 숫자를 크기 순으로 정렬하기

head=!NULL일 때까지 데이터를 읽고 개수 반환 후
```shell
head = head->link;
```

binary search로 수를 정렬하는 함수 생성
```shell
int left = 0;
int right = getLength(head) - 1;
```

### 🐭 과제4
> 미로를 제작하고 쥐를 탈출시켜라!
> 한 번 갔던 길은 다시 돌아갈 수 없다
m: 쥐의 위치
x: 탈출구
1: 벽, 막힌 길
0: 갈 수 있는 길

stack ➡️ push, pull 개념을 이용해 갔던 길에 되돌아감을 방지
