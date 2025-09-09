set -e

CXX=g++
CXXFLAGS="-std=c++17 -Wall -Wextra -O2"

SOURCES="test.cpp Binaryheap.cpp HashMap.cpp TreeNode.cpp"
OUTPUT="test"

echo "Compiling project..."
$CXX $CXXFLAGS $SOURCES -o $OUTPUT

echo "Build complete. Run with ./test"
