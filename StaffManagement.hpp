#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>

using namespace std;

class Staff{

    protected:  
        int driverId;  
        char name[40];
        int age;

    public:

    Staff(){
        driverId = 0;
        strcpy(name,"nil");
        age = 0;
    }


    void getStaffDate()
    {

        cout << "Enter Driver Id: ";
        cin >> driverId;
        cout << "enter driver name: ";
        cin >> name;
        cout << "Enter age: ";
        cin >>  age;


    } 
    void showStaffData()
    {
        cout << "  " << driverId << "  "<< name << "  " << age << endl;
    }

    bool is_empty(std::ifstream& pFile)
    {
    return pFile.peek() == std::ifstream::traits_type::eof();
    }
    bool is_empty(std::fstream& file){
    return file.peek() == std::ifstream::traits_type::eof();
    }

    int writeRecord();
    void displayAll();
    void searchRecord(char*);
    void deleteRecord(char*);
    void updateRecord(int);
};

void Staff::displayAll()
{
    ifstream fin;
    fin.open("Staff.DAT",ios::in);
    if(!fin){
        cout << "FATAL ERROR ! File not found" << endl;
    }
    else if(is_empty(fin)){
        cout << "No records to display file is empty" << endl;
    }
    else{
        cout << "-------------------------------" << endl;
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof()){
            showStaffData();
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        cout << "-------------------------------" << endl;
    }
}
int Staff::writeRecord()
{
    if(this->driverId==0 && this->age==0)
    {
        cout << "Staff data not initialized";
        return 0;
    }
    else{
        ofstream fout;
        fout.open("Staff.DAT",ios::app);
        fout.write((char*)this,sizeof(*this));
        fout.close();
        cout << "Successfully saved record" << endl;
        return 1;
    }
}

void Staff::searchRecord(char *t)
{
    ifstream fin;
    fin.open("staff.DAT",ios::in);
    if(!fin){
        cout << "\nFATAL ERROR! File not found" << endl;
    }
    else if(is_empty(fin)){
    cout << "Can't search file is empty" << endl;
    }
    else{
        bool flag = false;
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof()){
            if(!strcmp(name,t)){
                showStaffData();
                flag = true;
            }
            fin.read((char*)this,sizeof(*this));
        }
        if (!flag){
            cout << "No record found" << endl;
        }
        fin.close();
    }
}

void Staff::deleteRecord(char* t)
{
    ifstream fin;
    ofstream fout;
    fin.open("Staff.DAT",ios::in);
    if(!fin){
        cout << "FATAL ERROR ! File not found" << endl;
    }
    else if(is_empty(fin)){
    cout << "Can't delete record file is empty" << endl;
    }
    else{
        fout.open("tempfile.DAT",ios::out);
        fin.read((char*)this,sizeof(*this));
        bool flag=false;
        while(!fin.eof()){
           if(strcmp(name,t)) fout.write((char*)this,sizeof(*this));
           fin.read((char*)this,sizeof(*this));
           flag=true;
           
        }
        if(flag){
            cout << "Successfully Deleted Record" << endl;
        }
        else{
            cout << "No record found"<<endl;
        }
        fin.close();
        fout.close();
        remove("Staff.DAT");
        rename("tempfile.DAT","Staff.DAT");

    }
}

void Staff::updateRecord(int id)
{
    int pos,flag = 0;
    fstream file;
    file.open("Staff.DAT",ios::in|ios::out);
    if (!file){
        cout << "FATAL ERROR ! File not found" << endl;
    }
    else if(is_empty(file)){
        cout << "Can't update file is empty" << endl;
    }
    while(!file.eof()){ 
        pos = file.tellg();
        file.read((char*)this,sizeof(*this));
            if(id == driverId){
                flag = 1;
                getStaffDate();
                file.seekp(pos);
                file.write((char*)this,sizeof(*this));
                break;
            
        }
    }
    file.close();
    if (flag == 1)
        cout << "\nRecord successfully modified \n";
    else
        cout << "\nRecord not found \n";
}


int displayOptions()
{
    int choice;
    cout << "\nStaff Management";
    cout << "\n1. Insert Bus Staff Record";
    cout << "\n2. View All Bus Staff Records";
    cout << "\n3. Search Bus Staff record";
    cout << "\n4. Delete Bus Staff Record";
    cout << "\n5. Update Bus Staff Record";
    cout << "\n6. Return to main menu";
    cout << "\nEnter your choice: ";
    cin >> choice;
    cout << endl;
    return choice;
}


void menu(){
    Staff driver;
    string title;
    char*  record;
    while(1){
        switch(displayOptions())
        {
            case 1:
                driver.getStaffDate();
                driver.writeRecord();
                break;
            case 2:
                driver.displayAll();
                break;
            case 3:
                cout << "Enter name of Driver to search: ";
                cin >> title;
                record = &*title.begin();
                driver.searchRecord(record);
                break;
            case 4:
                cout << "Enter name of Driver to Delete: ";
                cin >> title;
                record = &*title.begin();
                driver.deleteRecord(record);
                break;
            case 5:
                cout << "Enter id of driver: ";
                int id;
                cin >> id;
                driver.updateRecord(id);
                break;
            case 6:
                exit(0);
            default:
                cout << "Invalid choice";
        }
    }
}
