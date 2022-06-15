#include <iostream>
#include "EmployeeManager.h"

int main() {
    EmployeeManager ds(10);
    ds.addEmployee(nullptr,1,1,1);
    ds.addEmployee(nullptr,2,1,2);
    ds.addEmployee(nullptr,3,1,3);
    ds.addEmployee(nullptr,4,1,4);
    ds.addEmployee(nullptr,5,5,5);
    ds.employeeSalaryIncrease(nullptr,1,1);
    ds.employeeSalaryIncrease(nullptr,2,2);
    ds.employeeSalaryIncrease(nullptr,3,3);
    ds.employeeSalaryIncrease(nullptr,4,4);
    ds.employeeSalaryIncrease(nullptr,5,5);
    ds.averageBumpGradeBetweenSalaryByGroup(nullptr,0,1,5);
    ds.bumpGradeToEmployees(nullptr,1,5,3);
    ds.averageBumpGradeBetweenSalaryByGroup(nullptr,0,1,5);


    return 0;
}
