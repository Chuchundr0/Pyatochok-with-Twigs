CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=c++17

LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

TARGET = build/PyatochokWithTwigs
SRCS = src/main.cpp \
	   src/include/assets_manager/assets_manager.cpp \
	   src/include/tilemap/tilemap.cpp \
	   src/include/animation/animation.cpp \
	   src/include/player/player.cpp \

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@ $(LIBS)

clean:
	rm -f $(TARGET)
