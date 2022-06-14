//
// Created by Sean Metlitski on 02/06/2022.
//

#ifndef MIVNE_WET_2_DYNAMICHASHTABLE_H
#define MIVNE_WET_2_DYNAMICHASHTABLE_H

#include "Employee.h"

class DynamicHashTable {
    int table_size;
    int num_of_elements;
    Employee** table;
public:
    DynamicHashTable() : table_size(1), num_of_elements(0){
        table = new Employee*[1];
        table[0] = nullptr;
    }

    ~DynamicHashTable() = default;

    void destoryTable(Employee** table){
        delete []table;
    }

    void setTableToNull(){
        table = nullptr;
    }

    int getTableSize() const {return table_size;}

    Employee** getTable() {return table;}

    void extendTable(){
        int old_table_size = table_size;
        if(table_size == 1)
            table_size = 3;
        else
            table_size = (table_size-1) * 2 + 1;
        //allocate new array and reset
        Employee** new_table = new Employee*[table_size];
        for(int i=0;i<table_size;i++){//
            new_table[i] = nullptr;
        }
        //copy old array to new and reset old array
        for(int i=0; i < old_table_size; i++){
            new_table[i] = table[i];
            table[i] = nullptr;
        }
        delete []table;
        table = new_table;
    }

    void shortenTable(){
        int old_table_size = table_size;
        if(table_size == 3)
            table_size = 1;
        else
            table_size = (table_size -1)/2 + 1;
        Employee** new_table = new Employee*[table_size];
        Employee** temp_table = new Employee*[old_table_size];
        for(int i=0;i<table_size;i++) {//
            new_table[i] = nullptr;
        }
        for(int i=0; i<old_table_size;i++) {//
            temp_table[i] = table[i];
            table[i] = nullptr;
        }
        delete []table;
        table = new_table;
        for(int i = 0; i< old_table_size; i++){//
            if(temp_table[i]) {
                num_of_elements--;
                insert(temp_table[i]);
                temp_table[i] = nullptr;
            }
        }
        destoryTable(temp_table);
    }

    int findSpotInHash(int id){
        int k = 0;
        while((((id + k)%table_size == 0) || table[(id + k)%table_size]) && k < table_size)
            k++;
        return (id + k)%table_size;
    }

    void insert(Employee* employee){
        if(((num_of_elements + 1) * 4)/3  >= table_size - 1)
            extendTable();
        int index = findSpotInHash(employee->getId());
        table[index] = employee;
        num_of_elements++;
    }

    void remove(int id){
        int index = findIndex(id);
        if(index != 0)
            table[index] = nullptr;
        if(num_of_elements<= (table_size -1)/4) {
            shortenTable();
        }
        num_of_elements--;
    }

    int findIndex(int id){
        int k = 0;
        while((!table[(id + k)%table_size] || ((table[(id + k)%table_size]) && table[(id + k)%table_size]->getId() != id)) && k < table_size) {
            k++;
            if((id + k)%table_size == 0)
                k++;
        }
        if(k < table_size)
            return (id + k)%table_size;
        return 0;
    }

    Employee* find(int id){
        int k = 0;
        while((!table[(id + k)%table_size] || ((table[(id + k)%table_size]) && table[(id + k)%table_size]->getId() != id)) && k < table_size) {
            k++;
            if((id + k)%table_size == 0)
                k++;
        }
        if(k < table_size)
            return table[(id +k)%table_size];
        return nullptr;
    }

    void copyTable(DynamicHashTable& table1, DynamicHashTable& table2, int num,Company* company){
        for(int i=0; i<num;i++){
            if(table2.table[i]){
                table2.table[i]->setCompany(company);
                table1.insert(table2.table[i]);
            }
        }
    }
};




#endif //MIVNE_WET_2_DYNAMICHASHTABLE_H

