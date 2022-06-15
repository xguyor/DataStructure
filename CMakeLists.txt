cmake_minimum_required(VERSION 3.20)
project(mivne_wet_2)

set(CMAKE_CXX_STANDARD 11)

add_executable(DSwet2 main2.cpp library2.cpp library2.h Employee.h RankSumAvlTree.h Company.h UnionFindDS.h DynamicHashTable.h EmployeeManager.cpp EmployeeManager.h )
