# コンパイラ
CC = gcc
# コンパイルオプション
CFLAGS = -Wall -Wextra -I. -Isrc -Itomlc99
# ソースファイル
SOURCES = src/main.c src/process_file.c src/process_directory.c src/utils.c tomlc99/toml.c
# オブジェクトファイル
OBJECTS = $(SOURCES:.c=.o)
# 実行ファイル名
TARGET = generate_markdown_file

# 実行ファイルの生成ルール
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# オブジェクトファイルの生成ルール
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# クリーンルール
clean:
	rm -f $(OBJECTS) $(TARGET)

# ファイルの依存関係
src/main.o: src/main.c src/process_directory.h src/process_file.h
src/process_file.o: src/process_file.c src/process_file.h
src/process_directory.o: src/process_directory.c src/process_directory.h src/utils.h src/process_file.h
src/utils.o: src/utils.c src/utils.h tomlc99/toml.h
tomlc99/toml.o: tomlc99/toml.c tomlc99/toml.h
tomlc99/toml.h: ;