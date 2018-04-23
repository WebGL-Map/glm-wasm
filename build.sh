# Make folders
mkdir -p cmake-build-release
SRC_DIR=$PWD
cd cmake-build-release

# Get user input
if [ ! -f emchainfile.txt ]; then
    read EM_CHAIN_FILE
    echo "$EM_CHAIN_FILE" > emchainfile.txt
else
    EM_CHAIN_FILE=`cat emchainfile.txt`
fi

cmake -DCMAKE_BUILD_TYPE=Release "-DCMAKE_TOOLCHAIN_FILE=$EM_CHAIN_FILE" -G "CodeBlocks - MinGW Makefiles" $SRC_DIR
cd ..
cmake --build cmake-build-release --target index -- -j 4