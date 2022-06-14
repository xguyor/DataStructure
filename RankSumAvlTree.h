//
// Created by Shahar Or on 24/04/22.
//
#ifndef MIVNE_WET_2_RANKSUMAVLTREE_H
#define MIVNE_WET_2_RANKSUMAVLTREE_H
#include <iostream>
#include "memory"
#include "Employee.h"



class RankSumAvlTree{
public:
    class treeNode {
    public:
        treeNode() : element(nullptr), key(), size_of_subtree(0), sum_of_grades(0), left_son(nullptr), right_son(nullptr) {};
        ~treeNode() = default;
        treeNode(const treeNode& node) = default;
        treeNode& operator=(treeNode* node){
            element = node->getElement();
            key = node->getKey();
            left_son->setLeft(node->getLeft());
            right_son->setRight(node->getRight());
            height = node->getHeight();
            size_of_subtree = node->getSizeOfSubtree();
            sum_of_grades = node->getSumOfGrades();
            return *this;
        }
        SortBySalary&  getKey() { return key; }
        void setKey(SortBySalary& other) {key = other ;}
        Employee* getElement() const { return element;}
        void setElement(Employee* other) { element = other;}
        void      setLeft(treeNode* left) { left_son = left; }
        treeNode*  getLeft() const { return left_son; }
        void      setRight(treeNode* right) { right_son = right; }
        treeNode*  getRight() const { return right_son; }
        int getHeight() const {return height;}
        void setHeight(int x){height = x;}
        int getSizeOfSubtree(){return size_of_subtree;}
        int getSumOfGrades(){return sum_of_grades;}
        void increaseSizeOfSubtree(){size_of_subtree++;}
        void decreaseSizeOfSubtree(){size_of_subtree--;}
        void decreaseSumOfGrades(int grade){sum_of_grades-=grade;}
        void setSizeOfSubtree(int size){size_of_subtree= size;}
        void setSumOfGrades(int size){sum_of_grades = size;}
        void increaseSumOfGrades(int grade){sum_of_grades+=grade;}

    private:
        Employee* element;
        SortBySalary key;
        int height;
        int size_of_subtree;
        int sum_of_grades;
        treeNode* left_son;
        treeNode* right_son;
    };
    RankSumAvlTree(): tree_root(nullptr), size(0){}

    void setRoot(treeNode* node){
        tree_root = node;
    }

    int getSize(){return size;}

    void setSize(int to_set){ size = to_set;}

    bool insert(Employee* element, SortBySalary& key){
        treeNode* temp = insertUtility(tree_root,element,key);
        if(temp){
            size++;
            tree_root = temp;
            return true;
        }
        else
            return false;
    }

    bool remove(SortBySalary& key){
        if(!(find(tree_root, key)))
            return false;
        treeNode* temp = removeUtility(tree_root,key);

        if(temp) {
            size--;
            tree_root = temp;
            return true;
        }
        else{
            tree_root = nullptr;
            return true;
        }
    }


    treeNode* creatNode(Employee* element, SortBySalary& key) {
        treeNode* node = new treeNode();
        node->setElement(element);
        node->setKey(key);
        node->setRight(nullptr);
        node->setLeft(nullptr);
        node->setHeight(0);
        node->setSumOfGrades(element->getGrade());
        node->setSizeOfSubtree(1);
        return node;
    }




    treeNode* getRoot() const { return tree_root;}

    void destroyWithElement(treeNode* node){
        if(!node)
            return;
        destroyWithElement(node->getLeft());
        destroyWithElement(node->getRight());
        if(node->getElement())
            delete node->getElement();
        delete node;
    }

    void destroyWithoutElement(treeNode* root){
        if(!root)
            return;
        if(root->getLeft())
            destroyWithoutElement(root->getLeft());
        if(root->getRight())
            destroyWithoutElement(root->getRight());
        delete root;
    }

    int max(int x, int y){
        if(x > y)
            return x;
        else
            return y;
    }

    int height(treeNode* node){
        if(!node)
            return -1;
        else return node->getHeight();
    }


    treeNode* llRotate(treeNode* node){
        treeNode* temp = node->getLeft(); //node = b
        node->setLeft(temp->getRight()); // temp = a
        temp->setRight(node);
        node->setHeight(max(height(node->getLeft()),height(node->getRight())) + 1);
        temp->setHeight(max(height(temp->getLeft()), height(node) + 1));
        ///guy ll
        node->setSizeOfSubtree(sizeOfSubTree(node->getRight()) + sizeOfSubTree(node->getLeft()) + 1);
        node->setSumOfGrades(sumOfGrades(node->getRight()) + sumOfGrades(node->getLeft()) + node->getElement()->getGrade());
        temp->setSizeOfSubtree(sizeOfSubTree(temp->getLeft()) + sizeOfSubTree(temp->getRight()) + 1);
        temp->setSumOfGrades(sumOfGrades(temp->getLeft()) + sumOfGrades(temp->getRight()) + temp->getElement()->getGrade());
        return temp;
    }

    treeNode* rrRotate(treeNode* node){
        treeNode* temp = node->getRight(); //temp-b node-a
        node->setRight(temp->getLeft());
        temp->setLeft(node);
        node->setHeight(max(height(node->getLeft()),height(node->getRight())) + 1);
        temp->setHeight(max(height(node->getRight()),height(node)) + 1);
        ///guy  rr
        node->setSizeOfSubtree(sizeOfSubTree(node->getRight()) + sizeOfSubTree(node->getLeft()) + 1);
        node->setSumOfGrades(sumOfGrades(node->getRight()) + sumOfGrades(node->getLeft()) + node->getElement()->getGrade());
        temp->setSizeOfSubtree(sizeOfSubTree(temp->getLeft()) + sizeOfSubTree(temp->getRight()) + 1);
        temp->setSumOfGrades(sumOfGrades(temp->getLeft()) + sumOfGrades(temp->getRight()) + temp->getElement()->getGrade());
        return temp;
    }
    int sizeOfSubTree(treeNode* node){
        int size = 0;
        if(!node)
            return 0;
        if(node)
            size ++;
        if(node->getLeft())
            size += node->getLeft()->getSizeOfSubtree();
        if(node->getRight())
            size += node->getRight()->getSizeOfSubtree();
       return size;
    }
    int sumOfGrades(treeNode* node){
        int sumGrades = 0;
        if(!node)
            return 0;
        if(node)
            sumGrades += node->getElement()->getGrade();
        if(node->getLeft())
            sumGrades += node->getLeft()->getSumOfGrades();
        if(node->getRight())
            sumGrades += node->getRight()->getSumOfGrades();
        return sumGrades;
    }
    int getBalanceFactor(treeNode* node){
        if(!node)
            return 0;
        return height(node->getLeft()) - height(node->getRight());
    }

    treeNode* insertUtility(treeNode* node, Employee* element, SortBySalary& key){
        if(!node)
            return creatNode(element,key);
        if(key < node->getKey()){
            node->setLeft(insertUtility(node->getLeft(), element, key));
        }
        else if(key > node->getKey()) {
            node->setRight(insertUtility(node->getRight(), element, key));
        }
        else
            return nullptr;//Failure

        return balancer(node,key);
    }

    // function for rotations when inserting new node
    treeNode* balancer(treeNode* node, SortBySalary& key){
        node->setHeight(1 + max(height(node->getLeft()),height(node->getRight())));
        node->setSizeOfSubtree(sizeOfSubTree(node->getLeft()) + sizeOfSubTree(node->getRight()) + 1);
        node->setSumOfGrades(sumOfGrades(node->getLeft()) + sumOfGrades(node->getRight()) + node->getElement()->getGrade());
        int balanceFactor = getBalanceFactor(node);
        if(balanceFactor > 1){
            if(key < node->getLeft()->getKey())
                return llRotate(node);
            else if(key > node->getLeft()->getKey()) {
                node->setLeft(rrRotate(node->getLeft()));
                return llRotate(node);
            }
        }
        if(balanceFactor < -1){
            if(key > node->getRight()->getKey())
                return rrRotate(node);
            else if(key < node->getRight()->getKey()){
                node->setRight(llRotate(node->getRight()));
                return rrRotate(node);
            }
        }
        return node;
    }

    treeNode* find(treeNode* root, SortBySalary& key){
        if(!root)
            return nullptr;
        SortBySalary k = root->getKey();
        if(k == key)
            return root;
        if(key < k)
            return find(root->getLeft(), key);
        else
            return find(root->getRight(), key);
    }

    treeNode* findMin(treeNode* root){
        if(!root)
            return nullptr;
        else if(!(root->getLeft()))
            return root;
        else return findMin(root->getLeft());
    }


    treeNode* removeUtility(treeNode* node , SortBySalary& key){
        //searching node and deleting
        if(node == nullptr)
            return nullptr;
        if(key < node->getKey())
            node->setLeft(removeUtility(node->getLeft(), key));
        else if(key > node->getKey())
            node->setRight(removeUtility(node->getRight(),key));
            // found node, checking how many sons
        else{
            treeNode* temp;
            //single son case
            if((node->getLeft() == nullptr || node->getRight()== nullptr)) {
                //only left son
                if (node->getLeft())
                    temp = node->getLeft();
                    //only right son or no sons
                else
                    temp = node->getRight();
                // no sons
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                }
                else
                    *node = *temp;
                temp->setElement(nullptr);
                delete temp;
            }

                // 2 sons
            else{
                temp = findMin(node->getRight());
                node->setKey(temp->getKey());
                node->setElement(temp->getElement());
                node->setRight(removeUtility(node->getRight(),temp->getKey()));
            }
        }
        if (node == nullptr)
            return nullptr;

        // updating height and perfofrming rotations on tree
        node->setHeight(1+ max(height(node->getLeft()), height(node->getRight())));
        node->setSizeOfSubtree(sizeOfSubTree(node->getLeft()) + sizeOfSubTree(node->getRight()) + 1);
        node->setSumOfGrades(sumOfGrades(node->getLeft()) + sumOfGrades(node->getRight()) + node->getElement()->getGrade());
        int b_factor = getBalanceFactor(node);
        if(b_factor > 1){
            if(getBalanceFactor(node->getLeft()) >= 0){
                return llRotate(node);
            }
            else{
                node->setLeft(rrRotate(node->getLeft()));
                return llRotate(node);
            }
        }
        if(b_factor < -1){
            if(getBalanceFactor(node->getRight()) <= 0){
                return rrRotate(node);
            }
            else{
                node->setRight(llRotate(node->getRight()));
                return rrRotate(node);
            }
        }
        return node;
    }

    Employee* getMaxElement(treeNode* node){
        if(!node)
            return nullptr;
        if(node->getRight())
            return getMaxElement(node->getRight());
        return node->getElement();
    }

    Employee* getMinElement(treeNode* node){
        if(!node)
            return nullptr;
        if(node->getLeft())
            return getMinElement(node->getLeft());
        return node->getElement();
    }


    void inorderToArray(treeNode* root, RankSumAvlTree::treeNode** array_begin, int size, int* counter){
        if(root == nullptr)
            return;
        inorderToArray(root->getLeft(), array_begin,size, counter);
        if(*counter < size)
            array_begin[*counter] = root;
        if(*counter >= size - 1)
        {
            (*counter)++;
            return;
        }
        (*counter)++;
        inorderToArray(root->getRight(),array_begin, size ,counter);

    }
    void updateRanksSums(treeNode* node){
        if(!node)
            return;
        updateRanksSums(node->getLeft());
        updateRanksSums(node->getRight());
        node->setSumOfGrades(node->getElement()->getGrade() + sumOfGrades(node->getLeft()) + sumOfGrades(node->getRight()));
        node->setSizeOfSubtree(1 + sizeOfSubTree(node->getRight()) + sizeOfSubTree(node->getLeft()));
    }

    treeNode* arrayToTreeShell(RankSumAvlTree::treeNode** array, int start, int end){
        treeNode* root = arrayToTree(array,start,end);
        delete []array;
        return root;
    }
    treeNode* arrayToTree(RankSumAvlTree::treeNode** array, int start, int end){
        if(start > end)
            return nullptr;
        int mid = (start + end)/2;
        treeNode* root = array[mid];
        root->setLeft(arrayToTree(array, start, mid - 1));
        root->setRight(arrayToTree(array, mid + 1, end));
        root->setHeight(max(height(root->getLeft()), height(root->getRight())) + 1);
        return root;
    }

    void  createEmployeeArray(treeNode** array, int size){
        int counter = 0;
        inorderToArray(array[0],array,size,&counter);
    }


    void mergeIdArrays(treeNode **a,treeNode **b,treeNode **c, int size_a, int size_b) {
        int i = 0, j = 0, k = 0;
        while (i < size_a && j < size_b) {
            if (a[i]->getKey() < b[j]->getKey())
                c[k++] = a[i++];
            else
                c[k++] = b[j++];
        }
        while (i < size_a) {
            c[k++] = a[i++];
        }
        while (j < size_b) {
            c[k++] = b[j++];
        }
    }

    treeNode** mergedEmployeesArray(treeNode *root_a,treeNode *root_b , int size_a , int size_b) {
        try {
            treeNode **a = new treeNode *[size_a];
            a[0] = root_a;
            treeNode **b = new treeNode *[size_b];
            b[0] = root_b;
            treeNode **c = new treeNode *[size_a + size_b];

            createEmployeeArray(a, size_a);
            createEmployeeArray(b, size_b);
            mergeIdArrays(a, b, c, size_a, size_b);
            for (int i = 0; i < (size_a + size_b); ++i) {
                c[i]->setLeft(nullptr);
                c[i]->setRight(nullptr);
                c[i]->setHeight(0);
            }
            delete []a;
            delete []b;
            return c;
        }
        catch (std::bad_alloc& e) {
            throw e;
        }
    }


    void increaseRankSums(treeNode* node, Employee* element, SortBySalary& key){
        if(!node)
            return;
        if(key < node->getKey()){
            increaseRankSums(node->getLeft(),element,key);
        }
        else if(key > node->getKey()) {
            increaseRankSums(node->getRight(),element,key);
        }
        else
            return;
        node->setSizeOfSubtree(sizeOfSubTree(node->getLeft()) + sizeOfSubTree(node->getRight()) + 1);
        node->setSumOfGrades(sumOfGrades(node->getLeft()) + sumOfGrades(node->getRight()) + node->getElement()->getGrade());
    }

    void decreaseRankSums2(treeNode* node,SortBySalary& key){
        if(!node)
            return;
        if(key < node->getKey()){
            decreaseRankSums2(node->getLeft(),key);
        }
        else if(key > node->getKey()) {
            decreaseRankSums2(node->getRight(),key);
        }
        node->setSizeOfSubtree(sizeOfSubTree(node->getLeft()) + sizeOfSubTree(node->getRight()) + 1);
        node->setSumOfGrades(sumOfGrades(node->getLeft()) + sumOfGrades(node->getRight()) + node->getElement()->getGrade());
    }

    Employee* getSumByIndex(treeNode* node, int index, int* sum){
        if(!node)
            return nullptr;
        if(sizeOfSubTree(node->getLeft()) + 1 == index) {
            *sum += sumOfGrades(node->getLeft());
            return node->getElement();
        }
        if(sizeOfSubTree(node->getLeft()) + 1 < index) {
            *sum += sumOfGrades(node->getLeft()) + node->getElement()->getGrade();
            return getSumByIndex(node->getRight(), index - (sizeOfSubTree(node->getLeft()) + 1), sum);
        }
        else
            return getSumByIndex(node->getLeft(), index, sum);
    }

    int getSumByIndexAux(treeNode* node, int index){
        int sum = 0;
        getSumByIndex(node, index, &sum);
        return sum;
    }
    Employee* findEmployeeByIndexAux(treeNode* node, int index){
        Employee* employee = nullptr;
        employee = findEmployeeByIndex(node,index,employee);
        return employee;
    }
    Employee* findEmployeeByIndex(treeNode* node, int index, Employee* employee){
        if(!node)
            return employee;
        if(sizeOfSubTree(node->getLeft()) + 1 == index)
            return node->getElement();
        if(sizeOfSubTree(node->getLeft()) + 1 < index) {
            employee = node->getElement();
            return findEmployeeByIndex(node->getRight(), index - (sizeOfSubTree(node->getLeft()) + 1),employee);
        }
        else {
            employee = node->getElement();
            return findEmployeeByIndex(node->getLeft(), index, employee);
        }
    }

    int findIndexAboveAux(treeNode* node, int salary){
        int sum =0, last_sum = 0;
        findIndexAbove(node,salary,&sum, &last_sum);
        if(findEmployeeByIndexAux(node,sum)->getSalary() < salary)
            return last_sum;
        return sum;
    }

    void findIndexAbove(treeNode* node, int salary, int* sum, int* last_sum){
        if(!node)
            return;
        if(node->getElement()->getSalary() >= salary) {
            if(!node->getLeft()){//smallest sal is in range
                (*sum)++;
                return;
            }
            *last_sum = *sum + sizeOfSubTree(node->getLeft()) + 1;
            findIndexAbove(node->getLeft(), salary, sum, last_sum);
        }
        if(node->getElement()->getSalary() < salary){
                *sum += sizeOfSubTree(node->getLeft()) + 1;
            findIndexAbove(node->getRight(),salary, sum, last_sum);
        }
    }

    ///bigest in range
    int findIndexBelowAux(treeNode* node, int salary){
        int sum = 0;
        findIndexBelow(node,salary,&sum);
        return sum;
    }

    void findIndexBelow(treeNode* node, int salary, int* sum){
        if(!node)
            return;
        if(node->getElement()->getSalary() > salary)
            findIndexBelow(node->getLeft(),salary,sum);
        if(node->getElement()->getSalary() <= salary){
            *sum += sizeOfSubTree(node->getLeft()) + 1;
            findIndexBelow(node->getRight(),salary, sum);
        }
    }

    int gradeByIndex(treeNode* node, int index, int* grade){
        if(!node)
            return -1;
        if(sizeOfSubTree(node->getLeft()) + 1 == index)
            return node->getElement()->getGrade();
        if(sizeOfSubTree(node->getLeft()) + 1 < index) {
            *grade = node->getElement()->getGrade();
            return gradeByIndex(node->getRight(), index - (sizeOfSubTree(node->getLeft()) + 1), grade);
        }
        else {
            *grade = node->getElement()->getGrade();
            return gradeByIndex(node->getLeft(), index,grade);
        }
    }
    int gradeByIndexAux(treeNode* node, int index){
        int grade = 0;
        grade = gradeByIndex(node,index,&grade);
        return grade;
    }



private:
    treeNode* tree_root;
    int size;
};


#endif //MIVNE_WET_2_RANKSUMAVLTREE_H