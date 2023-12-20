#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <thread>

using namespace std;
//200000000
//Структура детей
struct Child {
    int id;
    int best_gift = -200000000;
    vector<int> gift_id;
};

//Структура подарков
struct Gift {
    int id;
    int quantity;
    vector<int> child_id;

};

bool comp_G(const Gift& a, const Gift& b);
bool comp_C(const Child& a, const Child& b);
Gift reading_gift(ifstream& file);
Child reading_child(ifstream& file);
void writing_file(vector<Child> children);
void readGifts(vector<Gift>& gifts, ifstream& file_gift, const int& start, const int& end);
void readChildren(vector<Child>& children, ifstream& file_kids, const int& start, const int& end);
vector <Child> algoritm(vector<Child>& child, vector<Gift>& gift, const int& start, const int& end);
vector <Child> algoritm_twins(vector<Child>& child, vector<Gift>& gift, const int& start, const int& end);
