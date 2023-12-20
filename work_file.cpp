#include "Header.h"


//Запись из файла с подарками
Gift reading_gift(ifstream& file) {
    Gift gift;
    string line;

    getline(file, line);
    replace(line.begin(), line.end(), ',', ' ');

    istringstream iss(line);

    int temp;
    iss >> gift.id;

    gift.child_id.reserve(184);

    while (iss >> temp) {
        gift.child_id.push_back(temp);
    }
    gift.quantity = 250;
    return gift;
}

//Запись из файла с детьми
Child reading_child(ifstream& file) {
    Child kids;
    string line;
    getline(file, line);
    replace(line.begin(), line.end(), ',', ' ');

    istringstream iss(line);

    int temp;
    iss >> kids.id;

    kids.gift_id.reserve(100);

    while (iss >> temp) {
        kids.gift_id.push_back(temp);
    }
    return kids;
}

//Запись в файл готового результата
void writing_file(vector<Child> children) {
    ofstream output_file("gift_allocation.csv");
    output_file << "ChildId,GiftId" << endl;
    for (const auto& child : children) {
        output_file << child.id << "," << child.best_gift << endl;
    }

    output_file.close();
}

