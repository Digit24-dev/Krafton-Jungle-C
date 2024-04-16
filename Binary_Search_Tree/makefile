# 컴파일러 설정
CC=gcc
# 컴파일 옵션 설정
CFLAGS=-Wall -Wextra -pedantic -std=c11

# 실행 파일 이름 설정
TARGET=*

# 기본 타겟 설정 (첫 번째 타겟을 기본 타겟으로 함)
all: $(TARGET)

# 실행 파일 생성 규칙 설정
$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) $^ -o $@

# 사용자가 명령어 뒤에 파일 이름을 지정하여 해당 파일만 컴파일할 수 있도록 함
compile:
	$(CC) $(CFLAGS) $(TARGET).c -o $(TARGET)

# 정리 타겟 설정 (생성된 파일 정리)
clean:
	rm -f $(TARGET)
