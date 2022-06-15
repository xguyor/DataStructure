//
// Created by Shahar Or on 05/06/22.
//

#ifndef DATASTRUCTURES2_EMPLOYEEMANAGER_H
#define DATASTRUCTURES2_EMPLOYEEMANAGER_H
#include "RankSumAvlTree.h"
#include "DynamicHashTable.h"
#include "UnionFindDS.h"
#include "library2.h"

class EmployeeManager {
    UnionFindDS companies;
    RankSumAvlTree employees_tree;
    DynamicHashTable employees_hash;
    int num_of_employees_with_salary;
    int num_of_employees_no_salary;
    int sum_of_grades_no_salary;
public:
    EmployeeManager(int k) : companies(k) , employees_tree(),
    employees_hash(), num_of_employees_with_salary(0), num_of_employees_no_salary(0), sum_of_grades_no_salary(0){}
    ~EmployeeManager() = default;
    StatusType addEmployee(void* DS, int EmployeeID, int CompanyID, int Grade);
    StatusType removeEmployee(void* DS, int EmployeeID);
    StatusType acquireCompany(void* DS, int AcquireID, int TargetID, double Factor);
    StatusType employeeSalaryIncrease(void* DS, int EmployeeID, int SalaryIncrease);
    StatusType promoteEmployee(void* DS, int EmployeeID, int BumpGrade);
    StatusType sumOfBumpGradeBetweenTopWorkersByGroup(void* DS, int CompanyID, int m);
    StatusType averageBumpGradeBetweenSalaryByGroup(void* DS,int CompanyID,int lowerSalary, int higherSalary);
    StatusType companyValue(void* DS, int CompanyID);
    StatusType bumpGradeToEmployees(void* DS, int lowerSalary,int higherSalary, int bumpGrade);
    void bumpTree(RankSumAvlTree* tree, int smallest, int highest,int bumpGrade);
    void quit();


    };


#endif //DATASTRUCTURES2_EMPLOYEEMANAGER_H
