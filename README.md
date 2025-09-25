# Prim's Algorithm Implementation in C

프림 알고리즘(Prim's Algorithm)을 C언어로 구현한 최소 신장 트리(Minimum Spanning Tree) 탐색 프로그램입니다.

## 🌟 주요 특징

- **완전한 모듈화 설계**: 각 기능별로 독립적인 모듈 구현
- **두 가지 구현 방식**: 힙 기반과 단순 배열 기반 알고리즘 비교 가능
- **강력한 에러 처리**: 안전한 메모리 관리와 입력 검증
- **포괄적인 테스트**: 다양한 테스트 케이스와 검증 시스템
- **사용자 친화적**: 대화형 메뉴와 시각적 결과 출력

## 📁 프로젝트 구조

```
Prim-Algorithm/
├── src/
│   ├── main.c              # 메인 프로그램 및 사용자 인터페이스
│   ├── graph.c             # 그래프 자료구조 구현
│   ├── prim.c              # 프림 알고리즘 구현
│   ├── priority_queue.c    # 우선순위 큐 (최소 힙) 구현
│   └── utils.c             # 유틸리티 함수들
├── include/
│   ├── graph.h             # 그래프 헤더
│   ├── prim.h              # 프림 알고리즘 헤더
│   ├── priority_queue.h    # 우선순위 큐 헤더
│   └── utils.h             # 유틸리티 헤더
├── tests/
│   └── test_cases.c        # 테스트 케이스들
├── docs/
│   └── architecture.md     # 아키텍처 설계 문서
├── Makefile               # 빌드 설정
└── README.md              # 이 파일
```

## 🚀 빠른 시작

### 필수 요구사항

- GCC 컴파일러
- GNU Make
- C99 표준 지원

### 빌드 및 실행

```bash
# 프로젝트 빌드
make

# 프로그램 실행
make run

# 또는 직접 실행
./prim_algorithm
```

### 테스트 실행

```bash
# 테스트 빌드 및 실행
make run-test

# 또는 개별 실행
make test
./test_prim
```

## 🎮 사용법

프로그램을 실행하면 다음과 같은 메뉴가 표시됩니다:

```
====== Prim's Algorithm Demo ======
1. Run Example 1 (Simple 4-vertex graph)
2. Run Example 2 (Complete 5-vertex graph)
3. Run Example 3 (Linear graph)
4. Run Custom Graph
5. Compare Algorithms (Heap vs Simple)
0. Exit
===================================
```

### 예제 그래프들

#### 예제 1: 간단한 4정점 그래프
```
0 -- 1 (10)
|    |
|    |
2 -- 3 (4)
(6) (5) (15)
```

#### 예제 2: 완전 5정점 그래프
밀집된 그래프로 힙 기반 알고리즘의 성능 확인

#### 예제 3: 선형 그래프
희소 그래프로 단순 알고리즘의 성능 확인

### 커스텀 그래프

4번 옵션을 선택하면 직접 그래프를 입력할 수 있습니다:

```
Enter number of vertices: 4
Enter number of edges: 5
Enter edges (src dest weight):
Edge 1: 0 1 10
Edge 2: 0 2 6
Edge 3: 0 3 5
Edge 4: 1 3 15
Edge 5: 2 3 4
```

## 🔧 빌드 옵션

```bash
# 모든 빌드 옵션 확인
make help

# 디버그 버전 빌드
make debug

# 디버그 버전 실행
make run-debug

# 메모리 누수 검사 (valgrind 필요)
make memcheck

# 정적 분석 (cppcheck 필요)
make static-analysis

# 코드 포맷팅 (clang-format 필요)
make format

# 빌드 파일 정리
make clean
```

## 🧪 테스트 케이스

테스트 프로그램은 다음을 검증합니다:

1. **유틸리티 함수**: 메모리 관리와 안전한 할당/해제
2. **그래프 생성**: 정점 생성과 초기화
3. **간선 연산**: 간선 추가와 연결성 검사
4. **우선순위 큐**: 힙 구조와 키 값 업데이트
5. **MST 알고리즘**: 정확성과 결과 검증
6. **알고리즘 비교**: 힙 기반 vs 단순 구현 비교
7. **경계 조건**: 단일/이중 정점 그래프
8. **성능 테스트**: 큰 그래프에서의 동작

## 📊 알고리즘 복잡도

### 힙 기반 구현
- **시간 복잡도**: O(E log V)
- **공간 복잡도**: O(V²)
- **적합한 경우**: 밀집 그래프

### 단순 배열 구현
- **시간 복잡도**: O(V²)
- **공간 복잡도**: O(V²)
- **적합한 경우**: 희소 그래프

## 🔍 핵심 알고리즘

프림 알고리즘은 다음 단계로 동작합니다:

1. **초기화**: 모든 정점의 키 값을 무한대로, 시작 정점은 0으로 설정
2. **반복**:
   - 아직 MST에 포함되지 않은 정점 중 최소 키 값을 가진 정점 선택
   - 해당 정점을 MST에 추가
   - 인접한 모든 정점의 키 값을 갱신
3. **완료**: 모든 정점이 MST에 포함될 때까지 반복

## 🛡️ 안전성 특징

- **메모리 안전성**: 모든 동적 할당에 대한 NULL 검사
- **입력 검증**: 잘못된 정점 인덱스와 음수 가중치 검사
- **연결성 확인**: 그래프가 연결되지 않은 경우 경고
- **결과 검증**: MST 결과의 정확성 자동 검증

## 🐛 디버그 모드

디버그 모드에서는 알고리즘의 각 단계를 상세히 출력합니다:

```bash
make debug
./prim_debug
```

디버그 출력 예제:
```
DEBUG: Created graph with 4 vertices
DEBUG: Added edge: 0 -- 1 (weight: 10)
DEBUG: Starting Prim's algorithm from vertex 0
DEBUG: Added vertex 0 to MST (key: 0)
DEBUG: Updated vertex 1: parent=0, key=10
DEBUG: Extracted min vertex 3 with key 5
```

## 📈 성능 최적화

- **인접 행렬**: O(1) 시간에 간선 가중치 접근
- **인덱스 기반 힙**: 키 값 업데이트를 O(log V)로 최적화
- **메모리 풀링**: 빈번한 할당/해제 최소화

## 🤝 기여 방법

1. 이슈 생성 또는 기능 제안
2. 포크 후 브랜치 생성
3. 코드 작성 및 테스트 추가
4. 풀 리퀘스트 생성

## 📝 라이선스

MIT License - 자세한 내용은 LICENSE 파일 참조

## 🔗 참고 자료

- [Prim's Algorithm - Wikipedia](https://en.wikipedia.org/wiki/Prim%27s_algorithm)
- [Minimum Spanning Tree](https://en.wikipedia.org/wiki/Minimum_spanning_tree)
- [Graph Theory](https://en.wikipedia.org/wiki/Graph_theory)

---

**개발자**: [Your Name]
**버전**: 1.0.0
**최종 업데이트**: 2025년