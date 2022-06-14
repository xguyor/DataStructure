//
// Created by Sean Metlitski on 12/06/2022.
//

#include "library2.h"
#include "EmployeeManager.h"

void *Init(int k){
    if(k<=0)
        return nullptr;
    return new EmployeeManager(k);
}

StatusType AddEmployee(void *DS, int employeeID, int companyID, int grade){
    if(!DS)
        return INVALID_INPUT;
    return ((EmployeeManager*)DS)->addEmployee(DS,employeeID,companyID,grade);
}

StatusType RemoveEmployee(void *DS, int employeeID){
    if(!DS)
        return INVALID_INPUT;
    return ((EmployeeManager*)DS)->removeEmployee(DS,employeeID);
}

StatusType AcquireCompany(void *DS, int companyID1, int companyID2, double factor){
    if(!DS)
        return INVALID_INPUT;
    return ((EmployeeManager*)DS)->acquireCompany(DS,companyID1,companyID2,factor);
}

StatusType EmployeeSalaryIncrease(void *DS, int employeeID, int salaryIncrease){
    if(!DS)
        return INVALID_INPUT;
    return ((EmployeeManager*)DS)->employeeSalaryIncrease(DS,employeeID,salaryIncrease);
}

StatusType PromoteEmployee(void *DS, int employeeID, int bumpGrade){
    if(!DS)
        return INVALID_INPUT;
    return ((EmployeeManager*)DS)->promoteEmployee(DS,employeeID,bumpGrade);
}

StatusType SumOfBumpGradeBetweenTopWorkersByGroup(void *DS, int companyID, int m){
    if(!DS)
        return INVALID_INPUT;
    return ((EmployeeManager*)DS)->sumOfBumpGradeBetweenTopWorkersByGroup(DS,companyID,m);
}

StatusType AverageBumpGradeBetweenSalaryByGroup(void *DS, int companyID, int lowerSalary, int higherSalary){
    if(!DS)
        return INVALID_INPUT;
    return ((EmployeeManager*)DS)->averageBumpGradeBetweenSalaryByGroup(DS,companyID,lowerSalary,higherSalary);
}

StatusType CompanyValue(void *DS, int companyID){
    if(!DS)
        return INVALID_INPUT;
    return ((EmployeeManager*)DS)->companyValue(DS,companyID);
}

void Quit(void** DS){
    ((EmployeeManager*)(*DS))->quit();
    delete ((EmployeeManager*)(*DS));
    *DS = nullptr;
}