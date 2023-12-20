#include "Header.h"

#define MAX_CHILD 184000


int main() {
    setlocale(LC_ALL, "Russian");
    ifstream file_gift("ded_moroz_wish.csv");
    ifstream file_kids("kids_wish.csv");
    vector<Child> children(MAX_CHILD);
    vector<Gift> gifts(1000);

    clock_t start_time = clock();

    thread t1(readChildren, ref(children), ref(file_kids), 0, children.size() / 2);
    thread t2(readChildren, ref(children), ref(file_kids), children.size() / 2, children.size());

    t1.join();
    t2.join();

    readGifts(gifts, file_gift, 0, gifts.size());

    sort(children.begin(), children.end(), comp_C);

    

    algoritm_twins(children, gifts, 0 , 5520);
    algoritm(children, gifts, 5520, children.size());

   
    clock_t end_time = clock();
    double seconds = (double)(end_time - start_time) / 1000;
    cout << "Время выполнения: " << seconds << " секунд" << endl;

    writing_file(children);

    file_gift.close();
    file_kids.close();
    return 0;
}













