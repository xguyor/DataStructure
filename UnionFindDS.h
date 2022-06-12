//
// Created by Sean Metlitski on 02/06/2022.
//

#ifndef MIVNE_WET_2_UNIONFINDDS_H
#define MIVNE_WET_2_UNIONFINDDS_H
#include "Company.h"
#include "ostream"

struct HeadOfGroup;

struct Node {
    Company *company;
    Node *daddy;
    HeadOfGroup *head;
    double diff;
};

struct HeadOfGroup{
    Node *root;
    Company* head_company;
    double group_value;
    int group_size;
};

class UnionFindDS {
    HeadOfGroup** groups;
    Node** companies;
    int num_of_companies;
public:
    UnionFindDS() : groups(nullptr), companies(nullptr), num_of_companies(0) {}
    UnionFindDS(int size) : num_of_companies(size) {
        groups = new HeadOfGroup*[size + 1];
        companies = new Node *[size + 1];
        for (int i = 1; i <= size; i++) {
            Node *new_node = new Node;
            Company *new_company = new Company(i);
            HeadOfGroup *new_head = new HeadOfGroup;
            new_head->root = new_node;
            new_head->group_size = 1;
            new_head->head_company = new_company;
            new_head->group_value = new_company->getId();
            new_node->company = new_company;
            new_node->daddy = nullptr;
            new_node->head = new_head;
            new_node-> diff = 0;
            groups[i] = new_head;
            companies[i] = new_node;
        }
    }
    int getNumOfCompanies() { return num_of_companies;}


    void unite(int id1, int id2 , double factor){
        Node* node1 = getRoot(find(id1)->getId());
        Node* node2 = getRoot(find(id2)->getId());
        if(node1->head->group_size >= node2->head->group_size){
            node2->daddy = node1;
            node1->head->group_size += node2->head->group_size;
            node2->head->group_size = 0;
            node1->head->group_value += node2->head->group_value * factor;
            node2->diff += node1->head->group_value - node2->head->group_value;
            node2->head = nullptr;
        }
        else{
            node1->head->group_size += node2->head->group_size;
            node2->head->group_size = 0;
            node1->head->group_value += node2->head->group_value * factor;
            node2->diff += node1->head->group_value - node2->head->group_value;
            node1->diff -= node1->head->group_value - node2->head->group_value;
            node1->daddy = node2;
            node2->head = node1->head;
            node1->head = nullptr;
        }
    }

    Company* find(int id){
        Node* temp_node = companies[id];
        Node* root = getRoot(id);
        double temp_diff = temp_node->diff;
        while(temp_node->daddy && temp_node->daddy != root){
            temp_diff += temp_node->diff;
            Node* temp_daddy = temp_node->daddy;
            temp_node->daddy = root;
            temp_node = temp_daddy;
        }
        companies[id]->diff = temp_diff;
        return root->head->head_company;
    }

    Node* getRoot(int id){
        Node* root = companies[id];
        while(root->daddy)
            root = root->daddy;
        return root;
    }
    void print(){
        for(int i=1; i<=num_of_companies;i++){
            if(companies[i]->daddy != nullptr)
                std::cout<<"i am " << i << "and my daddy is " <<  companies[i]->daddy->company->getId() << std::endl;
            else
                std::cout << "i am" << i << "and i have no daddy" << std::endl;
        }
    }

    double davaiValue(int company_id){
        Node* node = companies[company_id];
        double sum = 0;
        while(!node->head) {
            sum += node->diff;
            node = node->daddy;
        }
        sum += node->diff;
        return node->head->group_value - sum;
    }

    void destroy(){
        for(int i=1;i<=num_of_companies;i++){
            if(companies[i]->company->getEmployeesTree())
                companies[i]->company->getEmployeesTree()->destroyWithoutElement(companies[i]->company->getEmployeesTree()->getRoot());
            delete companies[i]->company;
            companies[i]->daddy = nullptr;
            companies[i]->head = nullptr;
            delete companies[i];
            groups[i]->head_company= nullptr;
            groups[i]->root= nullptr;
            delete groups[i];
        }
    }
};


#endif //MIVNE_WET_2_UNIONFINDDS_H
