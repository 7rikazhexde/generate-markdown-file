# コンパイラ
CXX = g++

# コンパイルオプション
CXXFLAGS = -Wall -Wextra -std=c++17 -I./src -I./toml11

# ソースファイル
SOURCES = src/main.cpp src/markdown_generator.cpp src/config.cpp src/file_processor.cpp

# オブジェクトファイル
OBJECTS = $(SOURCES:.cpp=.o)

# 実行ファイル名
TARGET = generate_markdown_file

# 実行ファイルの生成ルール
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# オブジェクトファイルの生成ルール
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# クリーンルール
clean:
	rm -f $(OBJECTS) $(TARGET)

# ファイルの依存関係
src/main.o: src/main.cpp src/markdown_generator.hpp src/config.hpp
src/markdown_generator.o: src/markdown_generator.cpp src/markdown_generator.hpp src/config.hpp src/file_processor.hpp
src/config.o: src/config.cpp src/config.hpp
src/file_processor.o: src/file_processor.cpp src/file_processor.hpp