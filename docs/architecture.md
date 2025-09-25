# 프림 알고리즘 C 구현 아키텍처 설계서

## 1. 개요

### 1.1 목적
가중치가 있는 무방향 그래프에서 최소 신장 트리(Minimum Spanning Tree)를 찾는 프림 알고리즘을 C언어로 구현합니다.

### 1.2 프림 알고리즘 특징
- 그리디 알고리즘 기반
- 임의의 정점에서 시작하여 가장 가까운 정점을 순차적으로 추가
- 시간 복잡도: O(V²) (단순 구현) 또는 O(E log V) (힙 사용)
- 공간 복잡도: O(V²) (인접 행렬 사용시)

## 2. 시스템 아키텍처

### 2.1 레이어 구조

```
┌─────────────────────────────────────┐
│        Application Layer            │
│            (main.c)                 │
├─────────────────────────────────────┤
│        Algorithm Layer              │
│            (prim.c)                 │
├─────────────────────────────────────┤
│      Data Structure Layer           │
│    (graph.c, priority_queue.c)     │
├─────────────────────────────────────┤
│        Utility Layer                │
│           (utils.c)                 │
└─────────────────────────────────────┘
```

### 2.2 모듈 구성

#### 2.2.1 그래프 모듈 (graph.h/graph.c)
- **책임**: 그래프 데이터 구조 관리
- **주요 기능**:
  - 그래프 생성 및 초기화
  - 간선 추가/삭제
  - 그래프 정보 출력
  - 메모리 해제

#### 2.2.2 프림 알고리즘 모듈 (prim.h/prim.c)
- **책임**: 최소 신장 트리 계산
- **주요 기능**:
  - 프림 알고리즘 핵심 로직
  - MST 결과 생성 및 관리
  - 알고리즘 진행 상황 추적

#### 2.2.3 우선순위 큐 모듈 (priority_queue.h/priority_queue.c)
- **책임**: 최소 힙 구현
- **주요 기능**:
  - 최소값 추출
  - 키 값 업데이트
  - 힙 속성 유지

#### 2.2.4 유틸리티 모듈 (utils.h/utils.c)
- **책임**: 공통 기능 제공
- **주요 기능**:
  - 메모리 관리 (safe malloc/free)
  - 에러 처리 및 로깅
  - 입출력 헬퍼 함수

#### 2.2.5 메인 프로그램 (main.c)
- **책임**: 사용자 인터페이스
- **주요 기능**:
  - 프로그램 진입점
  - 테스트 케이스 실행
  - 결과 출력 및 검증

## 3. 데이터 구조 설계

### 3.1 그래프 표현

```c
typedef struct Graph {
    int vertices;           // 정점 개수
    int **adj_matrix;      // 인접 행렬 (가중치 저장)
} Graph;
```

**선택 근거**: 인접 행렬
- 프림 알고리즘에서 모든 간선 가중치에 빈번한 접근 필요
- O(1) 시간에 두 정점 간 가중치 확인 가능
- 구현 복잡도 낮음

### 3.2 최소 신장 트리 결과

```c
typedef struct MST_Result {
    int *parent;          // 각 정점의 부모 정점
    int *key;            // 각 정점의 최소 가중치
    int total_weight;    // MST 전체 가중치
    int vertex_count;    // 정점 개수
} MST_Result;
```

### 3.3 우선순위 큐 (최소 힙)

```c
typedef struct PriorityQueue {
    int *heap;           // 힙 배열 (정점 번호)
    int *pos;            // 각 정점의 힙 내 위치
    int *key;            // 각 정점의 키 값
    int size;            // 현재 힙 크기
} PriorityQueue;
```

## 4. API 인터페이스 설계

### 4.1 그래프 API

```c
// 그래프 생성 및 초기화
Graph* create_graph(int vertices);

// 간선 추가 (무방향 그래프)
void add_edge(Graph* graph, int src, int dest, int weight);

// 그래프 정보 출력
void print_graph(Graph* graph);

// 그래프 메모리 해제
void destroy_graph(Graph* graph);
```

### 4.2 프림 알고리즘 API

```c
// 프림 알고리즘 실행
MST_Result* prim_mst(Graph* graph, int start_vertex);

// MST 결과 출력
void print_mst(MST_Result* result);

// MST 결과 검증
bool validate_mst(Graph* graph, MST_Result* result);

// MST 결과 메모리 해제
void destroy_mst_result(MST_Result* result);
```

### 4.3 우선순위 큐 API

```c
// 우선순위 큐 생성
PriorityQueue* create_pq(int max_size);

// 원소 삽입
void insert_pq(PriorityQueue* pq, int vertex, int key);

// 최소값 추출
int extract_min(PriorityQueue* pq);

// 키 값 감소
void decrease_key(PriorityQueue* pq, int vertex, int new_key);

// 우선순위 큐 상태 확인
bool is_empty_pq(PriorityQueue* pq);

// 우선순위 큐 메모리 해제
void destroy_pq(PriorityQueue* pq);
```

### 4.4 유틸리티 API

```c
// 안전한 메모리 할당
void* safe_malloc(size_t size);

// 안전한 메모리 해제
void safe_free(void **ptr);

// 에러 메시지 출력
void error_exit(const char* message);

// 디버그 메시지 출력
void debug_print(const char* format, ...);
```

## 5. 알고리즘 흐름

### 5.1 프림 알고리즘 단계

```
1. 초기화
   - 모든 정점의 key 값을 무한대로 설정
   - 시작 정점의 key 값을 0으로 설정
   - 우선순위 큐에 모든 정점 삽입

2. 반복 (정점 개수만큼)
   - 우선순위 큐에서 최소 key 값을 가진 정점 u 추출
   - u의 모든 인접 정점 v에 대해:
     * v가 아직 MST에 포함되지 않고
     * weight(u,v) < key[v] 이면
     * key[v] = weight(u,v)
     * parent[v] = u
     * 우선순위 큐에서 v의 key 값 갱신

3. 결과 반환
   - parent 배열을 통해 MST 구성
   - 전체 가중치 계산
```

## 6. 성능 분석

### 6.1 시간 복잡도
- **인접 행렬 + 배열 기반**: O(V²)
  - 최소 정점 찾기: O(V)
  - V번 반복: O(V²)

- **인접 행렬 + 힙 기반**: O(V² + E log V)
  - 힙 구성: O(V)
  - 정점 추출: O(V log V)
  - 키 값 갱신: O(E log V)

### 6.2 공간 복잡도
- **인접 행렬**: O(V²)
- **보조 배열들**: O(V)
- **우선순위 큐**: O(V)
- **전체**: O(V²)

## 7. 에러 처리 전략

### 7.1 입력 검증
- 그래프 정점 개수 유효성 검사
- 간선 가중치 음수 여부 확인
- 시작 정점 범위 검사

### 7.2 메모리 관리
- 모든 동적 할당에 대한 실패 검사
- 명시적 메모리 해제
- 메모리 누수 방지

### 7.3 예외 상황 처리
- 연결되지 않은 그래프 처리
- 빈 그래프 처리
- 자기 자신으로의 간선 처리

## 8. 테스트 전략

### 8.1 단위 테스트
- 각 모듈별 개별 기능 테스트
- 경계 조건 테스트
- 에러 케이스 테스트

### 8.2 통합 테스트
- 전체 알고리즘 정확성 검증
- 다양한 그래프 구조 테스트
- 성능 벤치마킹

### 8.3 테스트 케이스
- 완전 그래프
- 선형 그래프
- 스타 그래프
- 연결되지 않은 그래프

## 9. 빌드 및 배포

### 9.1 파일 구조
```
Prim-Algorithm/
├── src/
│   ├── main.c
│   ├── graph.c
│   ├── prim.c
│   ├── priority_queue.c
│   └── utils.c
├── include/
│   ├── graph.h
│   ├── prim.h
│   ├── priority_queue.h
│   └── utils.h
├── tests/
│   └── test_cases.c
├── docs/
│   └── architecture.md
└── Makefile
```

### 9.2 컴파일 옵션
```makefile
CFLAGS = -Wall -Wextra -std=c99 -O2 -g
```

이 아키텍처 설계를 바탕으로 각 모듈을 단계적으로 구현할 수 있습니다.