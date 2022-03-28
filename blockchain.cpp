#include <cstring>
#include <string>
#include <iostream>
#include <istream>
#include <fstream>
#include <ostream>

#include "SHA1.hpp"
#include "SHA1.cpp"

using namespace std;

int block_no;
const string path = "./blockchain/";

int hash_verify(int block_NO) {
    if (block_NO == 0) {
        cout << "No Prev-Block" << endl;
    } else {
        string prev_hash;
        ifstream prev_blockFile(path + "block_" + to_string(block_NO - 1) + ".txt");
        prev_blockFile.ignore(50, '\n');
        getline(prev_blockFile, prev_hash);
        prev_hash = "prev " + prev_hash;
        cout << prev_hash << endl;

        string this_Block_prev_hash;
        ifstream blockFile(path + "block_" + to_string(block_NO) + ".txt");
        blockFile.ignore(50, '\n');
        blockFile.ignore(50, '\n');
        blockFile.ignore(50, '\n');
        getline(blockFile, this_Block_prev_hash);
        cout << this_Block_prev_hash << endl;
        
        if (prev_hash == this_Block_prev_hash) {
            cout << "The Blockchain Verified, no changed." << endl << endl;
        } else {
            cout << "The Blockchain was been changed!!! Please Check it!!!" << endl;
            cout << "Block " << block_NO - 1 << " has been changed" << endl << endl;
        }

        cout << "check prev one" << endl;
        hash_verify(block_NO - 1);
    }
    
}

void block_info(string block_number) {
    string block_information;
    ifstream blockFile(path + "block_" + block_number + ".txt");
    while (getline(blockFile, block_information)) {
        cout << block_information << endl;
    }
}

int block_index(int index) {
    ofstream index_file;
    index_file.open("index.txt");
    index_file << index + 1 << endl;
    index_file.close();

}


void add_block() {
    string data;
    cout << "Enter data into Blockchain: " << endl;
    getline(cin, data);

    SHA1 checksum;
	checksum.update(data);
	char hash[41];
	strcpy(hash, checksum.final().c_str());

    cout << "The SHA-1 of \"" << data << "\" is: " << hash << endl;

    string index;
    ifstream index_file("index.txt");
    if (index_file) {
        getline(index_file, index);
        block_no = stoi(index);
    } else {
        block_no = 0;
    }


    ofstream block_file;
    block_file.open(path + "block_" + to_string(block_no) + ".txt");
    block_file << "Block Number: " << block_no << endl;
    block_file << "hash: " << hash << endl;
    block_file << "data: " << data << endl;
    if (block_no == 0) {
        block_file << "prev hash: NULL" << endl;
    } else {
        string prev_hash;
        ifstream prev_blockFile(path + "block_" + to_string(block_no - 1) + ".txt");
        prev_blockFile.ignore(50, '\n');
        getline(prev_blockFile, prev_hash);
        block_file << "prev " << prev_hash << endl;
    }
    
    block_file.close();
    
    block_index(block_no);

}


int main() {
    int choose;
    string block_number;
    cout << "--- Welcome to Blockchain ---" << endl << endl;
    cout << "1. Check Blockchain Information" << endl << "2. Add A New Block into Blockchain" << endl << "3. Auto Blockchain Verify" << endl << "4. Exit" << endl;
    cout << "Choose One: ";
    cin >> choose;
    cout << endl;


    if (choose == 1) {
        cout << "Which Block want to look? - ";
        cin >> block_number;
        block_info(block_number);

    } else if (choose == 2) {
        getchar();
        add_block();
    
    } else if (choose == 3) {
        string index;
        ifstream index_file("index.txt");
        getline(index_file, index);
        block_no = stoi(index);
        
        int block_num = block_no - 1;
        hash_verify(block_num);

    } else if (choose == 4) {
        cout << "Bye Bye" << endl;

    } else {
        cout << "Error" << endl;
    }
    


    return 0;
}