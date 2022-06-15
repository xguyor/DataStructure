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
        treeNode() : element(nullptr), key(), size_of_subtree(0), sum_of_grades(0), left_son(nullptr), right_son(nullptr), bonus(0) {};
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
        void increaseBonus(int to_add){ bonus += to_add;}
        int getBonus() { return bonus;}

    private:
        Employee* element;
        SortBySalary key;
        int height;
        int size_of_subtree;
        int sum_of_grades;
        int bonus;
        treeNode* left_son;
        treeNode* right_son;
    };
    RankSumAvlTree(): tree_root(nullptr), size(0){}

    void setRoot(treeNode* node){
        tree_root = node;
    }

    int getSize(){return size;}

    void setSize(int to_set){ size = to_set;}
    int getBonus(treeNode* node){
        if(node)
            return node->getBonus();
        return 0;
    }
    bool insert(Employee* element, SortBySalary& key){
//        int sum_bump = 0;
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
//        node->increaseBonus(*sum_bump);
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
        int temp_a = temp->getBonus();
        int temp_b = temp->getBonus();
        node->setLeft(temp->getRight()); // temp = a
        temp->setRight(node);
        node->setHeight(max(height(node->getLeft()),height(node->getRight())) + 1);
        temp->setHeight(max(height(temp->getLeft()), height(node) + 1));
        ///guy ll
        node->setSizeOfSubtree(sizeOfSubTree(node->getRight()) + sizeOfSubTree(node->getLeft()) + 1);
        node->setSumOfGrades(sumOfGrades(node->getRight()) + sumOfGrades(node->getLeft()) + node->getElement()->getGrade());
        temp->setSizeOfSubtree(sizeOfSubTree(temp->getLeft()) + sizeOfSubTree(temp->getRight()) + 1);
        temp->setSumOfGrades(sumOfGrades(temp->getLeft()) + sumOfGrades(temp->getRight()) + temp->getElement()->getGrade());

        ///bonus updates
        ///A' = A + B, A_l' = A_l,B' = -A, A_r' = A_r + A, B_r' = B_r
//        temp->increaseBonus(temp_b);
//        node->increaseBonus(- temp_b - temp_a);
//        temp->getRight()->increaseBonus(temp_a);
        increaseBonus(temp,temp_b);
        increaseBonus(node,- temp_b - temp_a);
        increaseBonus(temp->getRight(), temp_a);

        return temp;
    }

    treeNode* rrRotate(treeNode* node){
        treeNode* temp = node->getRight(); //temp-b node-a
        int temp_b = temp->getBonus();
        int temp_a = node->getBonus();

        node->setRight(temp->getLeft());
        temp->setLeft(node);
        node->setHeight(max(height(node->getLeft()),height(node->getRight())) + 1);
        temp->setHeight(max(height(node->getRight()),height(node)) + 1);
        ///guy  rr
        node->setSizeOfSubtree(sizeOfSubTree(node->getRight()) + sizeOfSubTree(node->getLeft()) + 1);
        node->setSumOfGrades(sumOfGrades(node->getRight()) + sumOfGrades(node->getLeft()) + node->getElement()->getGrade());
        temp->setSizeOfSubtree(sizeOfSubTree(temp->getLeft()) + sizeOfSubTree(temp->getRight()) + 1);
        temp->setSumOfGrades(sumOfGrades(temp->getLeft()) + sumOfGrades(temp->getRight()) + temp->getElement()->getGrade());
        ///bonus updates
        ///B' -> B + A, A' -> -B, A_l' - > A_l, B_l' -> B_l + B
//        temp->increaseBonus(temp_a);
//        node->increaseBonus(-temp_a-temp_b);
//        node->getRight()->increaseBonus(temp_b);
        increaseBonus(temp,temp_a);
        increaseBonus(node, -temp_a - temp_b);
        increaseBonus(node->getRight(), temp_b);
        return temp;
    }
    void increaseBonus(treeNode* node, int bump){
        if(node)
            node->increaseBonus(bump);
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
//            *sum_bump += node->getBonus();///bonus
            node->setLeft(insertUtility(node->getLeft(), element, key));
        }
        else if(key > node->getKey()) {
//            *sum_bump += node->getBonus();///bounus
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
                if (node->getLeft()) {
                    temp = node->getLeft();
                    if(temp)
                        temp->increaseBonus(node->getBonus()); ///bonus
                }
                    //only right son or no sons
                else {
                    temp = node->getRight();
                    if(temp)
                        temp->increaseBonus(node->getBonus());///bonus
                }
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
                node->getLeft()->increaseBonus(node->getBonus());///bonus
                node->getRight()->increaseBonus(node->getBonus());///bonus



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

    treeNode* arrayToTreeShell(RankSumAvlTree::treeNode** array, int start, int end) {
        treeNode *root = arrayToTree(array, start, end);
        delete[]array;
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

    Employee* getSumByIndex(treeNode* node, int index, int* sum,int* sum_bump){///sum of smaller then me
        if(!node)
            return nullptr;
        if(sizeOfSubTree(node->getLeft()) + 1 == index) {
            *sum += sumOfGrades(node->getLeft()) + (*sum_bump + getBonus(node->getLeft())) * (sizeOfSubTree(node->getLeft()));///bounus
            return node->getElement();
        }
        if(sizeOfSubTree(node->getLeft()) + 1 < index) {
            *sum_bump += node->getBonus();///    adding bonus field
            *sum += sumOfGrades(node->getLeft()) + (*sum_bump + getBonus(node->getLeft())) * (sizeOfSubTree(node->getLeft())) +
                                                                                                    node->getElement()->getGrade() + *sum_bump;///bonus

            return getSumByIndex(node->getRight(), index - (sizeOfSubTree(node->getLeft()) + 1), sum,sum_bump);
        }
        else {
            *sum_bump += node->getBonus();///   adding bonus field
            return getSumByIndex(node->getLeft(), index, sum,sum_bump);
        }
    }

    int getSumByIndexAux(treeNode* node, int index,int* sumed_bump){
        int sum = 0;
        int sum_bump = *sumed_bump;
        getSumByIndex(node, index, &sum,&sum_bump);
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

    int gradeByIndex(treeNode* node, int index, int* grade,int* sum_bump){
        if(!node)
            return -1;
        if(sizeOfSubTree(node->getLeft()) + 1 == index) {
            *sum_bump += node->getBonus();
            return node->getElement()->getGrade();
        }
        if(sizeOfSubTree(node->getLeft()) + 1 < index) {
            *sum_bump += node->getBonus();
            *grade = sizeOfSubTree(node->getLeft()) + node->getElement()->getGrade();
            return gradeByIndex(node->getRight(), index - (sizeOfSubTree(node->getLeft()) + 1), grade,sum_bump);
        }
        else {
            *sum_bump += node->getBonus();
            *grade = node->getElement()->getGrade();
            return gradeByIndex(node->getLeft(), index,grade,sum_bump);
        }
    }
    int gradeByIndexAux(treeNode* node, int index){
        int grade = 0;
        int sum_bump = 0;
        grade = gradeByIndex(node,index,&grade,&sum_bump);
        return grade + sum_bump;
    }

    treeNode* findFirstInRange(treeNode* root, int low,int high){
        if(!root)
            return nullptr;
        else
        if(root->getElement()->getSalary() >= low && root->getElement()->getSalary() <= high)
            return root;
        else
        if(root->getElement()->getSalary() < low)
            return findFirstInRange(root->getRight(), low,high);
        else
        if(root->getElement()->getSalary() > high)
            return  findFirstInRange(root->getLeft(),low,high);
        else
            return nullptr;

    }

    void updatePathToSmallest(treeNode* root, int smallest_sal, int bump){
        if(root->getElement()->getSalary() == smallest_sal) {
            if (root->getLeft())
                root->getLeft()->increaseBonus(-bump);
            return;
        }
        if(root->getElement()->getSalary() > smallest_sal)
            updatePathToSmallest(root->getLeft(),smallest_sal,bump);
        if(root->getElement()->getSalary() < smallest_sal) {
            root->increaseBonus(-bump);
            root->getRight()->increaseBonus(bump);
            updatePathToSmallest(root->getRight(),smallest_sal,bump);
        }
    }

    void updatePathToHighest(treeNode* root, int highest_sal, int bump){
        if(root->getElement()->getSalary() == highest_sal) {
            if (root->getRight())
                root->getRight()->increaseBonus(-bump);
            return;
        }
        if(root->getElement()->getSalary() < highest_sal)
            updatePathToHighest(root->getRight(),highest_sal,bump);
        if(root->getElement()->getSalary() > highest_sal) {
            root->increaseBonus(-bump);
            root->getLeft()->increaseBonus(bump);
            updatePathToHighest(root->getLeft(),highest_sal,bump);
        }
    }
//    double avgInRange(treeNode* root, int low_sal, int high_sal){
//        treeNode* smallest_old_daddy = findFirstInRange(root,low_sal,high_sal);
//        int l_index = findIndexAboveAux(smallest_old_daddy, low_sal);
//        int h_index = findIndexBelowAux(smallest_old_daddy,high_sal);
//        int sum1 = getSumByIndexAux(smallest_old_daddy,l_index);
//        int grade = gradeByIndexAux(smallest_old_daddy,h_index);
//        int sum2 = getSumByIndexAux(smallest_old_daddy, h_index) + grade;
//        double avg  = (double)(sum2 - sum1)/(double)(h_index-l_index +1);
//        avg = ((double)((int)(avg*10.0 + 0.5)))/10.0;
//        return avg;
//    }
    void sumBumpToSmallestDaddy(treeNode* root, treeNode* daddy,int* bump){
        if(root == daddy)
            return;
        if(root->getKey() < daddy->getKey()){
            *bump += root->getBonus();
            sumBumpToSmallestDaddy(root->getRight(),daddy,bump);
        }
        else{
            *bump += root->getBonus();
            sumBumpToSmallestDaddy(root->getLeft(),daddy,bump);
        }
    }
    int sumInRange(treeNode* root, int low_sal, int high_sal){
        int sum_bump = 0;
        treeNode* smallest_old_daddy = findFirstInRange(root,low_sal,high_sal);
        sumBumpToSmallestDaddy(root,smallest_old_daddy,&sum_bump);
        int l_index = findIndexAboveAux(smallest_old_daddy, low_sal);
        int h_index = findIndexBelowAux(smallest_old_daddy,high_sal);
        int sum1 = getSumByIndexAux(smallest_old_daddy,l_index,&sum_bump);
        int grade = gradeByIndexAux(smallest_old_daddy,h_index);
        int sum2 = getSumByIndexAux(smallest_old_daddy, h_index,&sum_bump) + grade;
        return sum2 - sum1;
    }
    int sumInRangeForSum(treeNode* root, int low_sal, int high_sal,int m, int num_of_employees){
        int sum_bump = 0;
        treeNode* smallest_old_daddy = findFirstInRange(root,low_sal,high_sal);
        sumBumpToSmallestDaddy(root,smallest_old_daddy,&sum_bump);
//        int l_index = findIndexAboveAux(smallest_old_daddy, low_sal);
//        int l_sal = findEmployeeByIndexAux(root,num_of_employees - m + 1)->getSalary();
//        int h_index = findIndexBelowAux(smallest_old_daddy,high_sal);
        int sum1 = getSumByIndexAux(smallest_old_daddy,smallest_old_daddy->getSizeOfSubtree() - m + 1,&sum_bump);
        int grade = gradeByIndexAux(smallest_old_daddy,smallest_old_daddy->getSizeOfSubtree());
        int sum2 = getSumByIndexAux(smallest_old_daddy, smallest_old_daddy->getSizeOfSubtree(),&sum_bump) + grade;
        return sum2 - sum1;
    }
private:
    treeNode* tree_root;
    int size;
};


#endif //MIVNE_WET_2_RANKSUMAVLTREE_H