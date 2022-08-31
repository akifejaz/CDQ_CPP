# Call Quality Dashboard : C++

## Introduction

This project is for the simple visualization of how data is accessed from a database. Starting from request to TCP Connection then API to database everything is implemented.
This is Not Perfect Implementation but it is a good start.

## Usage : CMake

There are two files, in the directory as `server.cpp` and `client.cpp` . You have to compile both, for that use below commands for CMake 

```makefile
#for server.cpp
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="-std=c++17
make
./CQD_DB 

#for client.cpp
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="-std=c++17
make
./CQD_DB -u <username> -p <password> -ip <ip> -po <port> -f <function> 

```

OR  `Istall the VScode Extension for CMake : Just Press Build`

Sample Input :

```makefile
./CQD_DB "user" "user" "localhost" "8080"
```

## Usage : Manual

For `server.cpp` 

```makefile
g++ server.cpp -o server
./server
```

For `client.cpp`

```makefile
g++ client.cpp -o client
./client -u <username> -p <password> -ip <ip> -po <port> -f <function>
```

