#include "Header.h"
int UNISD = 0;
int UNISDM = 0;


//������� ��� ����� ������ 
void readGifts(vector<Gift>& gifts, ifstream& file_gift, const int &start, const int &end) {
    for (int i = start; i < end; i++) {
        gifts[i] = reading_gift(file_gift);
    }
}

//������� ��� ����� ������ 
void readChildren(vector<Child>& children, ifstream& file_kids, const int& start, const int& end) {
    for (int i = start; i < end; i++) {
        children[i] = reading_child(file_kids);
    }
}

//�����������
bool comp_C(const Child  &a, const Child &b) {
    return a.id < b.id;
}

bool comp_G(const Gift  &a,const Gift &b) {
    return a.id < b.id;
}

//���� ���������� ������������������ ������� � ���������
vector<int> search_Similar(vector<int> a, vector<int> b, const int &start) {
    vector<int> simil;

    _Vector_iterator<_Vector_val<_Simple_types<int>>> it;

 
    for (int i = start; i < a.size(); i++) {
        it = find(a.begin(), a.end(), b[i]);
        if (it != a.end()) {
            simil.push_back(b[i]);
            simil.push_back(i);
            break;
        }
    }
    return simil;
}

//�������� �������
vector <Child> algoritm_twins(vector<Child>& child, vector<Gift>& gift, const int& start, const int& end) {

    _Vector_iterator<_Vector_val<_Simple_types<int>>> it_G1, it_G2, it_C1, it_C2;

    vector<int> similarities;

    int number_child, number_gifts;
    int index = 0;

    for (int i = start; i < end; i += 2) {
        //����� ���������� ��������
        similarities = search_Similar(child[i].gift_id, child[i + 1].gift_id, index);
        index = 0;
        //������ ���������� ������� 
        if (gift[similarities[0]].quantity > 1) {

            it_C1 = find(child[i].gift_id.begin(), child[i].gift_id.end(), similarities[0]);
            it_C2 = find(child[i + 1].gift_id.begin(), child[i + 1].gift_id.end(), similarities[0]);

            it_G1 = find(gift[similarities[0]].child_id.begin(), gift[similarities[0]].child_id.end(), child[i].id);
            it_G2 = find(gift[similarities[0]].child_id.begin(), gift[similarities[0]].child_id.end(), child[i + 1].id);

            child[i].best_gift = similarities[0];
            child[i + 1].best_gift = similarities[0];

            number_child = it_C1 - child[i].gift_id.begin();
            UNISD += (2 * (100 - number_child));
            number_child = it_C2 - child[i + 1].gift_id.begin();
            UNISD += (2 * (100 - number_child));
            

            if (it_G1 != gift[similarities[0]].child_id.end()) {
                number_gifts = it_G1 - gift[similarities[0]].child_id.begin();
                UNISDM += 2 * (184 - number_gifts);

            }


            if (it_G2 != gift[similarities[0]].child_id.end()) {
                number_gifts = it_G2 - gift[similarities[0]].child_id.begin();
                UNISDM += 2 * (184 - number_gifts);
            }

            gift[similarities[0]].quantity -= 2;
        }
        else {
            //���� �������,������� ����� ��������, �����������,�� �������� ������ ������ ������ �� 1 ������ � ���� �������� ���������������� �������
            i -= 2;
            index = similarities[1] + 1;
            continue;
        }

        similarities.clear();
    }
    return child;
}



vector <Child> algoritm(vector<Child>& child, vector<Gift>& gift, const int& start, const int& end) {

    _Vector_iterator<_Vector_val<_Simple_types<int>>> it_g, it_c;
    int number_child, number_gifts, UNIS;

    int id = 0;

     for (int j = start; j < end; j++) {
        for (int i = 0; i < 100; i++) {
            if (child[j].best_gift > -1) {
                break;
            }
            id = child[j].gift_id[i];

            it_g = find(gift[id].child_id.begin(), gift[id].child_id.end(), child[j].id);
            //������� ������� || ������� �������
            if (it_g != gift[id].child_id.end() && gift[id].quantity > 0) {
                it_c = find(child[j].gift_id.begin(), child[j].gift_id.end(), gift[id].id);

                number_gifts = it_g - gift[id].child_id.begin();
                number_child = it_c - child[j].gift_id.begin();

                gift[id].quantity -= 1;
                child[j].best_gift = gift[id].id;

                UNISD += 2 * (100 - number_child);
                UNISDM += 2 * (184 - number_gifts);


                break;
            }
            //��� �������������� �������,���������� �� ���� �������� ���� ������ � ���� �������
            if (i == 0) { 
                for (auto& gifts : gift) {
                    it_g = find(gifts.child_id.begin(), gifts.child_id.end(), child[j].id);
                    if (it_g != gifts.child_id.end() && gifts.quantity > 0) {

                        number_gifts = it_g - gifts.child_id.begin();
                        //���� ����� id ������� � ������� ���� ������ ������� �������,�� ������ ����� ������ ������� �������
                        if (number_gifts > 40) { //203 - 60 / 204 - 40
                            for (int x = 0; x < child[j].gift_id.size(); x++) {
                                id = child[j].gift_id[x];
                                if (gift[id].quantity > 0) {
                                    child[j].best_gift = id;
                                    gift[id].quantity -= 1;
                                    UNISD += 2 * (100 - x);
                                    UNISDM -= 1;
                                    break;
                                }
                            }
                        }
                        //���� ����� �������,�� ������� 
                        if (child[j].best_gift > -1) {
                            break;
                        }
                        gifts.quantity -= 1;
                        child[j].best_gift = gifts.id;

                        UNISD -= 1;
                        UNISDM += 2 * (184 - number_gifts);

                        break;
                    }
                }
            }
        }  // ���� �� ����� id ������� � �������� ���� ������,�� ������ ���� ��������������� ��� �������,��� ������� ��� ������� �� ����������
        if (child[j].best_gift < -1) {
            for (int x = 0; x < child[j].gift_id.size(); x++) {
                id = child[j].gift_id[x];
                if (gift[id].quantity > 0) {
                    child[j].best_gift = id;
                    gift[id].quantity -= 1;
                    UNISD += 2 * (100 - x);
                    UNISDM -= 1;
                    break;
                }
            }
        }
    }
    //������� ������� �������
    UNIS = (UNISD / child.size()) + (UNISDM / 250000);
    cout << "UNIS = " << UNIS << endl;
    return child;
}



