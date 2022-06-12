cmake_minimum_required(VERSION 3.22)
project(DSwet2)

set(CMAKE_CXX_STANDARD 11)

add_executable(DSwet2 main2.cpp Employee.h RankSumAvlTree.h Company.h UnionFindDS.h
        DynamicHashTable.h EmployeeManager.cpp EmployeeManager.h library2.cpp library2.h)
