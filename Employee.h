//
// Created by Sean Metlitski on 02/06/2022.
//

#ifndef MIVNE_WET_2_EMPLOYEE_H
#define MIVNE_WET_2_EMPLOYEE_H

class Company;

class Employee {
    int id;
    int salary;
    int grade;
    Company* employing_company;
public:
    Employee(int id,int grade,Company* company): id(id),salary(0),grade(grade),employing_company(company) {}
    ~Employee() = default;
     int getId() const { return id;}
    int getSalary() const {return salary;}
    int getGrade() const {return grade;}
    Company* getCompany() const {return employing_company;}
    void increaseSalary(int to_add){ salary += to_add;}
    void bumpGrade(int to_add) {grade += to_add;}
    void setCompany(Company* company){ employing_company = company;}
};


class SortBySalary{
private:
    int salary;
    int id;
    int grade;
public:
    SortBySalary(int salary, int id,int grade): salary(salary), id(id), grade(grade) {};
    SortBySalary() = default;
    ~SortBySalary() = default;
    int getGrade(){return grade;}
    bool operator <(SortBySalary b) const {
        if(salary < b.salary )
            return true;
        else
        if(salary == b.salary) {
            if (id < b.id) //todo: if id equal return FAILURE
                return true;
        }
        return false;
    }
    bool operator >(SortBySalary b) const {
        if(salary > b.salary )
            return true;
        if(salary == b.salary){
            if(id > b.id) //todo: if id equal return FAILURE
                return true;
        }
        return false;
    }

    bool operator ==(SortBySalary b) const {
        if(id == b.id)
            return true;
        else return false;}
};




#endif //MIVNE_WET_2_EMPLOYEE_H
