# Test
test claude

## Ring Buffer 예제 + 단위 테스트

- `src/ring_buffer.[ch]` : 정적 메모리 기반 바이트 링 버퍼 (malloc 없음)
- `test/unit_test.h` : 외부 의존성 없는 최소 테스트 매크로
- `test/test_ring_buffer.c` : 단위 테스트

```sh
make test
```
