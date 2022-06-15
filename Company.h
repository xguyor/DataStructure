//
// Created by Sean Metlitski on 02/06/2022.
//

#ifndef MIVNE_WET_2_COMPANY_H
#define MIVNE_WET_2_COMPANY_H

#include "RankSumAvlTree.h"
#include "DynamicHashTable.h"

class Company {
    int id;
    int num_of_employees_with_salary;
    int num_of_employees_no_salary;
    int sum_of_grades_no_salary;
    RankSumAvlTree employees;
    DynamicHashTable employees_table;
public:
    Company(int id) : id(id), num_of_employees_with_salary(0) ,num_of_employees_no_salary(0),sum_of_grades_no_salary(0),
                                                        employees() , employees_table(){}
    ~Company() = default;
    void setRoot(RankSumAvlTree::treeNode* root){employees.setRoot(root);}
    void resetTable() {employees_table.setTableToNull();}
    int getId() const {return id;}
    int getEmployeesNoSalary() const {return num_of_employees_no_salary; }
    int getEmployeesWithSalary() const { return num_of_employees_with_salary;}
    void increaseNumOfEmployeesNoSalary(int num){ num_of_employees_no_salary+=num;}
    void increaseNumOfEmployeesWithSalary(int num){ num_of_employees_with_salary+=num;}
    void increaseSumOfGradesNoSalary(int num){ sum_of_grades_no_salary += num;}
    int getSumOfGradesNoSalary() const { return sum_of_grades_no_salary;}
    void removeEmployeeFromTree(SortBySalary& key){ employees.remove(key);}
    void insertEmployeeToTree(Employee* employee, SortBySalary& key) { employees.insert(employee,key);}
    RankSumAvlTree* getEmployeesTree() {return &employees;}
    DynamicHashTable* getEmployeesTable() {return &employees_table;}
    void insertToEmployeeTable(Employee* employee) { employees_table.insert(employee);}
    void removeFromEmployeeTable(int id) {employees_table.remove(id);}
    int getSumByIndexCompany(int index, int* sum_bump)  {return employees.getSumByIndexAux(employees.getRoot(), index,sum_bump);}
    int findIndexBelowCompany(int salary)  {return employees.findIndexBelowAux(employees.getRoot(), salary);}
    int findIndexAboveCompany(int salary) {return employees.findIndexAboveAux(employees.getRoot(), salary);}
    int gradeByIndexCompany(int index)  {return employees.gradeByIndexAux(employees.getRoot(),index);}
//    int sumByIndexCompany(int index) {return employees.getSumByIndexAux(employees.getRoot(),index);}
    void deleteTable() {employees_table.destoryTable(employees_table.getTable());}


};


#endif //MIVNE_WET_2_COMPANY_H
