#include "EmployeeManager.h"


StatusType EmployeeManager::addEmployee(void *DS, int EmployeeID, int CompanyID, int Grade) {
    if(EmployeeID <= 0 || CompanyID <= 0 || CompanyID > companies.getNumOfCompanies() || Grade < 0)
        return INVALID_INPUT;
    Employee* employee = employees_hash.find(EmployeeID);
    if(employee)
       return FAILURE;
    try{
    Company* company = companies.find(CompanyID);
    Employee* new_employee = new Employee(EmployeeID,Grade, company);
    employees_hash.insert(new_employee);
    company->insertToEmployeeTable(new_employee);
    sum_of_grades_no_salary += Grade;
    num_of_employees_no_salary++;
    company->increaseNumOfEmployeesNoSalary(1);
    company->increaseSumOfGradesNoSalary(Grade);
    return SUCCESS;
    }
    catch(const std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
}
StatusType EmployeeManager::removeEmployee(void *DS, int EmployeeID) {
    if(EmployeeID <= 0)
        return INVALID_INPUT;
    Employee* employee = employees_hash.find(EmployeeID);
    if(!employee)
        return FAILURE;
    try{
        if(employee->getSalary() == 0){
            sum_of_grades_no_salary -= employee->getGrade();
            num_of_employees_no_salary--;
            employee->getCompany()->increaseSumOfGradesNoSalary(-employee->getGrade());
            employee->getCompany()->increaseNumOfEmployeesNoSalary(-1);
            employees_hash.remove(EmployeeID);
            employee->getCompany()->removeFromEmployeeTable(EmployeeID);
            delete employee;
        }
        else{
            SortBySalary key(employee->getSalary(), EmployeeID, employee->getGrade());
            employees_tree.remove(key);
            employee->getCompany()->removeEmployeeFromTree(key);
            num_of_employees_with_salary--;
            employee->getCompany()->increaseNumOfEmployeesWithSalary(-1);
            employee->getCompany()->removeFromEmployeeTable(EmployeeID);
            employees_hash.remove(EmployeeID);
            employee->setCompany(nullptr);
            delete employee;
        }
        return SUCCESS;
    }
    catch(const std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
}
StatusType EmployeeManager::acquireCompany(void *DS, int AcquireID, int TargetID, double Factor) {
    if(AcquireID <= 0 || AcquireID > companies.getNumOfCompanies() || TargetID <= 0 || TargetID > companies.getNumOfCompanies() ||
                                                                                             TargetID == AcquireID || Factor <= 0)
        return INVALID_INPUT;
    try{
        Company* acquirer_company = companies.find(AcquireID);
        Company* target_company = companies.find(TargetID);
        ///case with same owners
        if(acquirer_company->getId() == target_company->getId())
            return INVALID_INPUT;
        RankSumAvlTree* acquirer_tree = acquirer_company->getEmployeesTree();
        RankSumAvlTree* target_tree = target_company->getEmployeesTree();

        ///merge trees
        if(target_company->getEmployeesWithSalary() > 0 && acquirer_company->getEmployeesWithSalary() >0) {
            acquirer_company->setRoot(acquirer_tree->arrayToTreeShell(
                    acquirer_tree->mergedEmployeesArray(acquirer_tree->getRoot(), target_tree->getRoot(),
                                                        acquirer_company->getEmployeesWithSalary(),
                                                        target_company->getEmployeesWithSalary()), 0,
                    acquirer_company->getEmployeesWithSalary() + target_company->getEmployeesWithSalary() - 1));
            acquirer_tree = acquirer_company->getEmployeesTree();
            acquirer_tree->setSize(acquirer_company->getEmployeesWithSalary() + target_company->getEmployeesWithSalary());
            acquirer_tree->updateRanksSums(acquirer_tree->getRoot());

            target_company->setRoot(nullptr);
        }
        if(target_company->getEmployeesWithSalary() > 0 && acquirer_company->getEmployeesWithSalary() == 0) {
            acquirer_company->setRoot(target_tree->getRoot());
            target_company->setRoot(nullptr);
        }
        acquirer_company->getEmployeesTable()->copyTable(*acquirer_company->getEmployeesTable(),*target_company->getEmployeesTable(),target_company->getEmployeesTable()->getTableSize(),acquirer_company);
        target_company->getEmployeesTable()->destoryTable(target_company->getEmployeesTable()->getTable());
        target_company->resetTable();
        ///update values
        companies.unite(AcquireID,TargetID,Factor);
        acquirer_company->increaseSumOfGradesNoSalary(target_company->getSumOfGradesNoSalary());
        acquirer_company->increaseNumOfEmployeesNoSalary(target_company->getEmployeesNoSalary());
        acquirer_company->increaseNumOfEmployeesWithSalary(target_company->getEmployeesWithSalary());
        acquirer_tree->setSize(target_company->getEmployeesWithSalary() + acquirer_company->getEmployeesWithSalary());
    }
    catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType EmployeeManager::employeeSalaryIncrease(void *DS, int EmployeeID, int SalaryIncrease) {
    if(EmployeeID <= 0 || SalaryIncrease <= 0)
        return INVALID_INPUT;
    Employee* employee = employees_hash.find(EmployeeID);
    if(!employee)
        return FAILURE;
    try {
        if (employee->getSalary() == 0) {    //no salary
            SortBySalary key(SalaryIncrease, EmployeeID, employee->getGrade());
            employee->increaseSalary(SalaryIncrease);
            employees_tree.insert(employee, key);
            employee->getCompany()->insertEmployeeToTree(employee, key);

            //updates of nums sheesh
            num_of_employees_no_salary--;
            num_of_employees_with_salary++;
            sum_of_grades_no_salary -= employee->getGrade();
            employee->getCompany()->increaseNumOfEmployeesNoSalary(-1);
            employee->getCompany()->increaseNumOfEmployeesWithSalary(1);
            employee->getCompany()->increaseSumOfGradesNoSalary(-employee->getGrade());
        }
            //with salary
        else {
            SortBySalary old_key(employee->getSalary(), EmployeeID, employee->getGrade());
            employees_tree.remove(old_key);
            employee->getCompany()->removeEmployeeFromTree(old_key);
            employee->increaseSalary(SalaryIncrease);
            SortBySalary new_key(employee->getSalary(), EmployeeID, employee->getGrade());
            employees_tree.insert(employee, new_key);
            employee->getCompany()->insertEmployeeToTree(employee, new_key);
        }
        return SUCCESS;
    }
    catch(const std::bad_alloc &e){
        return ALLOCATION_ERROR;
    }
}

StatusType EmployeeManager::promoteEmployee(void *DS, int EmployeeID, int BumpGrade) {
    if(EmployeeID<= 0)
        return INVALID_INPUT;
    Employee *e = employees_hash.find(EmployeeID);
    if (!e)
        return FAILURE;
    if(BumpGrade > 0) {
        try {
            if (e->getSalary() == 0) {
                e->bumpGrade(BumpGrade);
                sum_of_grades_no_salary += BumpGrade;
                e->getCompany()->increaseSumOfGradesNoSalary(BumpGrade);
                return SUCCESS;
            }
            else {
                SortBySalary old_key(e->getSalary(), EmployeeID, e->getGrade());
                employees_tree.remove(old_key);
                e->getCompany()->removeEmployeeFromTree(old_key);
                e->bumpGrade(BumpGrade);
                SortBySalary new_key(e->getSalary(), EmployeeID, e->getGrade());
                employees_tree.insert(e, new_key);
                e->getCompany()->insertEmployeeToTree(e, new_key);
                return SUCCESS;
            }
        }
        catch (std::bad_alloc &e) {
            return ALLOCATION_ERROR;
        }
    }
    return SUCCESS;
}

StatusType EmployeeManager::sumOfBumpGradeBetweenTopWorkersByGroup(void *DS, int CompanyID, int m) {
    if (CompanyID < 0 || CompanyID > companies.getNumOfCompanies() || m <= 0)
        return INVALID_INPUT;
    if(CompanyID == 63 && m ==2)
        int sss = 0;
    if (CompanyID > 0) {
        Company *company = companies.find(CompanyID);
        if(company->getEmployeesWithSalary() < m)
            return FAILURE;
//        int sum_smaller = company->getSumByIndexCompany( total_employees - m + 1);
        int high_sal =  company->getEmployeesTree()->findEmployeeByIndexAux(company->getEmployeesTree()->getRoot(),company->getEmployeesWithSalary())->getSalary();
        int low_sal = company->getEmployeesTree()->findEmployeeByIndexAux(company->getEmployeesTree()->getRoot(),company->getEmployeesWithSalary()-m+1)->getSalary();
        int sum = company->getEmployeesTree()->sumInRangeForSum(company->getEmployeesTree()->getRoot(), low_sal,high_sal,m,company->getEmployeesWithSalary());

        printf("SumOfBumpGradeBetweenTopWorkersByGroup: %d\n", sum);
       return SUCCESS;
    }
    else{
        if(num_of_employees_with_salary < m)
            return FAILURE;
        int total_employees = num_of_employees_with_salary;

//        int sum_smaller = employees_tree.getSumByIndexAux(employees_tree.getRoot(), total_employees - m);
//        int sum_total = employees_tree.getRoot()->getSumOfGrades();

        int high_sal =  employees_tree.findEmployeeByIndexAux(employees_tree.getRoot(),num_of_employees_with_salary)->getSalary();
        int low_sal = employees_tree.findEmployeeByIndexAux(employees_tree.getRoot(),num_of_employees_with_salary-m+1)->getSalary();
        int sum = employees_tree.sumInRangeForSum(employees_tree.getRoot(), low_sal,high_sal,m,num_of_employees_with_salary);
        printf("SumOfBumpGradeBetweenTopWorkersByGroup: %d\n", sum);

        return SUCCESS;
    }
}

StatusType EmployeeManager::averageBumpGradeBetweenSalaryByGroup(void *DS, int CompanyID, int lowerSalary,int higherSalary) {
    if(higherSalary < 0 || lowerSalary < 0 || lowerSalary > higherSalary ||
                                      CompanyID > companies.getNumOfCompanies() || CompanyID < 0)
        return INVALID_INPUT;
    int h_sal = 0, l_sal = 0, num_in_range = 0, sum_in_range = 0;
    double avg =0;


    if(CompanyID > 0){
        Company* company = companies.find(CompanyID);
        if(company->getEmployeesWithSalary() > 0 && higherSalary > 0) {
            h_sal = company->getEmployeesTree()->getMaxElement(company->getEmployeesTree()->getRoot())->getSalary();
            l_sal = company->getEmployeesTree()->getMinElement(company->getEmployeesTree()->getRoot())->getSalary();
            if((higherSalary >= l_sal && higherSalary <= h_sal) || (lowerSalary >= l_sal && lowerSalary <= h_sal)) {
                int high_index = company->findIndexBelowCompany(higherSalary);
                int low_index = company->findIndexAboveCompany(lowerSalary);
                num_in_range = high_index - low_index + 1;
                sum_in_range = company->getEmployeesTree()->sumInRange(company->getEmployeesTree()->getRoot(), lowerSalary,higherSalary);
            }

            //{
//                int high_index = company->findIndexBelowCompany(higherSalary);
//                int low_index = company->findIndexAboveCompany(lowerSalary);
//                if(low_index <= high_index) {
//                    num_in_range = high_index - low_index + 1;
//                    int grade_of_highest_in_range = company->gradeByIndexCompany(high_index);
//                    int sum1 = company->sumByIndexCompany(low_index);
//                    int sum2 = company->sumByIndexCompany(high_index) + grade_of_highest_in_range;
//                    sum_in_range = sum2 - sum1;
//                }
            //}
        }
        if(lowerSalary == 0 && num_in_range == 0 && company->getEmployeesNoSalary() == 0)
            return FAILURE;

        if(lowerSalary == 0){
            num_in_range += company->getEmployeesNoSalary();
            sum_in_range += company->getSumOfGradesNoSalary();
        }
            avg = ((double)sum_in_range)/((double )num_in_range);
        avg = ((double)((int)(avg*10.0 + 0.5)))/10.0;
        printf("AverageBumpGradeBetweenSalaryByGroup: %.1f\n", avg);
        return SUCCESS;
    }
    else{//company == 0
        int h_sal = 0, l_sal = 0, num_in_range = 0, sum_in_range = 0;
        if(num_of_employees_with_salary + num_of_employees_no_salary == 0)
            return FAILURE;
        if(num_of_employees_with_salary > 0 && higherSalary > 0) {
            h_sal = employees_tree.getMaxElement(employees_tree.getRoot())->getSalary();
            l_sal = employees_tree.getMinElement(employees_tree.getRoot())->getSalary();
            if (!((higherSalary >= l_sal && lowerSalary <= h_sal) ||
                  (lowerSalary == 0 && num_of_employees_no_salary > 0)))
                return FAILURE;
            if((higherSalary >= l_sal && higherSalary <= h_sal) || (lowerSalary >= l_sal && lowerSalary <= h_sal)) {
                int high_index = employees_tree.findIndexBelowAux(employees_tree.getRoot(), higherSalary);
                int low_index = employees_tree.findIndexAboveAux(employees_tree.getRoot(), lowerSalary);
                num_in_range = high_index - low_index + 1;
                sum_in_range = employees_tree.sumInRange(employees_tree.getRoot(), lowerSalary, higherSalary);
            }
            //{
//                int high_index = employees_tree.findIndexBelowAux(employees_tree.getRoot(), higherSalary);
//                int low_index = employees_tree.findIndexAboveAux(employees_tree.getRoot(), lowerSalary);
//                num_in_range = high_index - low_index + 1;
//                int grade_of_highest_in_range = employees_tree.gradeByIndexAux(employees_tree.getRoot(), high_index);
//                int sum1 = employees_tree.getSumByIndexAux(employees_tree.getRoot(), low_index);
//                int sum2 = employees_tree.getSumByIndexAux(employees_tree.getRoot(), high_index) + grade_of_highest_in_range;
//                sum_in_range = sum2 - sum1;

            //}
        }
        if(lowerSalary == 0){
            num_in_range += num_of_employees_no_salary;
            sum_in_range += sum_of_grades_no_salary;
        }

            avg = ((double)sum_in_range)/((double )num_in_range);
        avg = ((double)((int)(avg*10.0 + 0.5)))/10.0;
        printf("AverageBumpGradeBetweenSalaryByGroup: %.1f\n", avg);
        return SUCCESS;
    }
}
StatusType EmployeeManager::companyValue(void *DS, int CompanyID) {
    if(CompanyID <= 0 || CompanyID > companies.getNumOfCompanies())
        return INVALID_INPUT;
    printf("CompanyValue: %.1f\n", companies.davaiValue(CompanyID));
    return SUCCESS;
}
void EmployeeManager:: bumpTree(RankSumAvlTree* tree, int smallest, int highest,int bumpGrade){
    RankSumAvlTree::treeNode* first_in_range = tree->findFirstInRange(tree->getRoot(),smallest,highest);
    if(first_in_range){
        int smallest_in_range = tree->findEmployeeByIndexAux(tree->getRoot(),tree->findIndexAboveAux(tree->getRoot(),smallest))->getSalary();
        int highest_in_range = tree->findEmployeeByIndexAux(tree->getRoot(),tree->findIndexBelowAux(tree->getRoot(),highest))->getSalary();
        first_in_range->increaseBonus(bumpGrade);
        tree->updatePathToSmallest(first_in_range,smallest_in_range,bumpGrade);
        tree->updatePathToHighest(first_in_range,highest_in_range,bumpGrade);
    }
}


StatusType EmployeeManager:: bumpGradeToEmployees(void* DS, int lowerSalary,int higherSalary, int bumpGrade){
    bumpTree(&employees_tree,lowerSalary,higherSalary,bumpGrade);

}

void EmployeeManager::quit(){
    companies.destroy();
    employees_tree.destroyWithoutElement(employees_tree.getRoot());
    for(int i=0;i < employees_hash.getTableSize();i++) {
        if(employees_hash.getTable()[i]) {
            delete employees_hash.getTable()[i];
        }
    }
    delete []employees_hash.getTable();
}
