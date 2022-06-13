#include <iostream>
#include "EmployeeManager.h"

int main() {
    EmployeeManager ds(10);
    ds.addEmployee(nullptr,1,1,1);
    ds.addEmployee(nullptr,2,2,2);
    ds.addEmployee(nullptr,3,3,3);
    ds.addEmployee(nullptr,4,4,4);
    ds.addEmployee(nullptr,5,5,5);
    ds.employeeSalaryIncrease(nullptr,1,1);
    ds.employeeSalaryIncrease(nullptr,2,2);
    ds.employeeSalaryIncrease(nullptr,3,3);
    ds.employeeSalaryIncrease(nullptr,4,4);
    ds.employeeSalaryIncrease(nullptr,5,5);
    ds.removeEmployee(nullptr,1);


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
