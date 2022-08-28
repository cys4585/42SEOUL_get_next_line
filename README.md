# 1. get_next_line

**Reading a line from a fd is way to tedius.**

## Summary

이 프로젝트는 file descriptor로부터 읽은 한 줄을 반환하는 함수를 프로그래밍하는 과제이다.

## Goals

이 프로젝트는 당신의 컬렉션에 매우 편리한 기능을 추가할 수 있을 뿐만 아니라, C 프로그래밍에서 매우 흥미로운 새로운 개념인 정적 변수(static variables)를 배우게 할 것이다.

---

## Mandatory part

| Function name | get_next_line |
| --- | --- |
| Prototype | char *get_next_line(int fd); |
| Turn in files | get_next_line.c, get_next_line_utils.c, get_next_line.h |
| Parameters | fd: file descriptor to read from |
| Return value | Read line: correct Behavior
NULL: there is nothing else to read, or an error occurred |
| External functs. | read, malloc, free |
| Description | Write a function that returns a line read from a file descriptor |
- `get_next_line()` 함수에 대한 반복 호출(예를 들어 루프 사용)을 통해 file descriptor가 가리키는 텍스트 파일을 한 번에 한 줄씩 읽을 수 있다.
- 함수는 읽은 줄을 반환해야 한다. 다른 읽을 내용이 없거나 오류가 발생한 경우 `NULL`을 반환해야 한다.
- 파일을 읽을 때와 표준 입력(standard input)에서 읽을 때 모두 기능이 예상대로 작동하는지 확인해라.
- 반환되는 줄에는 끝의 파일 끝에 도달하여 `\n` 문자로 끝나지 않는 경우를 제외하고 끝에 `\n` 문자가 포함되어야 한다.
- 헤더 파일 `get_next_line.h`에는 적어도 `get_next_line()` 함수의 프로토타입이 포함되어 있어야 한다.
- `get_next_line_utils.c` 파일에 필요한 유틸리티 함수를 추가한다.

**(Information) 정적 변수가 무엇인지 아는 것이 좋은 시작일 것이다.**

- `get_next_line()`에서 파일을 읽어야 하므로, 컴파일러 호출에 이 옵션을 추가해라: (`-D BUFFER_SIZE=n`). 
이것은 `read()`의  버퍼 크기를 정의한다. 버퍼 크기 값은 코드를 테스트하기 위해 동료 평가자 및 Moulinete에 의해 수정될 것이다.
- 다음과 같이 코드를 컴파일한다(예시로 버퍼 크기가 42로 사용된다): `cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c`
- file descriptor가 가리키는 파일이 마지막 호출 이후 변경된 반면 `read()`가 파일 끝에 도달하지 않은 경우 `get_next_line()`은 정의되지 않은 동작을 한다고 간주한다.
- 우리는 또한 이진 파일을 읽을 때 `get_next_line()`이 정의되지 않은 동작을 한다고 생각한다. 그러나 원하는 경우 이 동작을 처리하는 논리적 방법을 구현할 수 있다.

**(Hint) BUFFER_SIZE 값이 9999인 경우에도 기능이 계속 작동하는가? 1이면? 1000000이면? 왠지 아는가?**

**(Information) get_next_line()이 호출될 때마다 가능한 한 적게 읽도록 해라. 새 줄이 나타나면 현재 줄을 반환해야 한다. 파일 전체를 읽지 말고 각 행을 처리해라.**

**Forbidden**

- `libft`는 사용할 수 없다.
- `lseek()`는 사용할 수 없다.
- 전역 변수(global variables)는 사용할 수 없다.

---

## Bonus part

이 프로젝트는 간단해서 복잡한 보너스를 허용하지 않는다. 하지만, 우리는 당신의 창의성을 신뢰한다. 필수 파트를 완료한 경우 이 보너스 파트를 시도해 봐라.

**보너스 파트 요구사항**

- 정적 변수 하나만 사용하여 `get_next_line()`을 개발해라.
- `get_next_line()`은 동시에 여러 file descriptor를 관리할 수 있다. 예를 들어, file descriptor 3, 4, 5에서 읽을 수 있는 경우 각 file descriptor의 읽기 스레드를 손실하거나 다른 fd에서 한 줄을 반환하지 않고 호출당 다른 fd에서 읽을 수 있어야 한다. 즉, `get_next_line()`을 호출하여 fd3, 4, 5를 차례로 읽은 다음 다시 3, 다시 4를 읽을 수 있어야 한다.

Bonus part 파일에 `_bonus.[c\h]`를 추가한다. Mandatory part 파일 외에 다음 3개파일을 제출한다는 의미이다.

- get_next_line_bonus.c
- get_next_line_bonus.h
- get_next_line_utils_bonus.c

**(Warning) Bonus part는 Mandatory part가 PERFECT한 경우에만 평가된다. 완벽하다는 것은 Mandatory part가 일체적으로 처리되었고 오작동 없이 작동한다는 것을 의미한다. 필수 요구사항을 모두 통과하지 않은 경우 Bonus part는 전혀 평가되지 않는다.**

---

## Submission and peer-evaluation

평소처럼 Git 저장소에 과제를 제출해라. 방어 중에는 리포지토리 내부의 작업만 평가된다. 파일이 정확한지 확인하기 위해 파일 이름을 다시 확인해라.

**(Information) 테스트를 작성할 때 다음 사항을 기억해라.
1) 버퍼 크기와 라인 크기는 모두 매우 다른 값을 가질 수 있다.
2) 파일 설명자는 일반 파일만 가리키는 것이 아니다.
똑똑하게 행동하고 동료들과 교차 점검하라. 방어를 위한 다양한 테스트 세트를 준비해라.**

통과하면, 주저하지 말고 `get_next_line()`을 `libft`에 추가해라.