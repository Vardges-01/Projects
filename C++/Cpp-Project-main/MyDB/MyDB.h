#ifndef _MYDB_
#define _MYDB_
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;

class MyDB
{
private:
    unordered_map<string, unordered_map<string, string>> entity_mp;
    bool legal_entity(string);
    bool legal_types(string, string, string);
    bool legal_date(string, string);
    string typ_info(string);
    string del_simb_line(string);

    void info_table();                // Info comand
    void create_entity(string);       // Create new Entity
    void insert_date(string);         // Insert new Date
    void update_date(string);         // Update Date
    void select_date_to_read(string); // Sellect to Read
    void remove_date(string);         // Remove Date
public:
    MyDB();
    void DB_Strat();
    ~MyDB();
};

MyDB::MyDB()
{
    string str;
    string enti_key, data_name, data_typ;
    fstream fs("Entity_info.txt", fstream::in);
    istringstream ss;
    while (getline(fs, str))
    {
        str = del_simb_line(str);
        ss.str(str);
        ss >> enti_key;
        cout << enti_key << endl;
        while (ss >> data_name)
        {
            ss >> data_typ;
            entity_mp[enti_key][data_name] = data_typ;
        }
        ss.clear();
    }
}
MyDB::~MyDB() {}

string MyDB::del_simb_line(string tmp)
{
    for (int i = 0; i < tmp.size(); i++)
    {
        if (tmp[i] == '>' || tmp[i] == '=')
        {
            tmp[i] = ' ';
        }
    }
    return tmp;
}

string MyDB::typ_info(string value)
{
    string typ;
    for (int i = 0; i < value.size(); i++)
    {
        if (value[i] >= '0' && value[i] <= '9')
            typ = "int";
        else
        {
            typ = "string";
            break;
        }
    }
    return typ;
}

bool MyDB::legal_types(string enti_key, string typ_key, string value_key)
{
    string typ_inf = typ_info(value_key);
    auto it = (entity_mp.find(enti_key));
    if (it != entity_mp.end())
    {
        for (auto a : it->second)
        {
            // cout<<a.second<<endl;
            if (typ_key == a.first && a.second == typ_inf)
            {
                if (legal_date(enti_key, value_key) == true)
                {
                    return true;
                }
                cout << "The Name /" << value_key << "/ is not Available..\n"
                     << "Try Again." << endl;
                break;
            }
            else if(typ_key == a.first && a.second != typ_inf)
            {
                cout << "Error convert * " << typ_inf << " * to * " << a.second << " *" << endl;
                break;
            }
        }
    }
    return false;
}

bool MyDB::legal_entity(string key)
{
    fstream ss(key + ".txt", fstream::in);
    if (!ss.is_open())
    {
        return true;
    }
    else
        return false;
}

bool MyDB::legal_date(string enti_name, string value)
{
    string date_line;
    string tmp;
    fstream fs(enti_name + ".txt", fstream::in);
    istringstream is;
    while (getline(fs, date_line))
    {
        is.str(date_line);
        is >> tmp;
        cout << tmp << endl;
        if (tmp == value)
            return false;

        is.clear();
    }
    return true;
}

void MyDB::DB_Strat()
{
    while (true)
    {
        string key;
        cout << "Please Enter Command!" << endl;
        cin >> key;
        if (key == "create")
        {
            cin.get();
            getline(cin, key);
            create_entity(key);
        }
        else if (key == "insert")
        {
            cin.get();
            getline(cin, key);
            insert_date(key);
        }
        else if (key == "update")
        {
            cin.get();
            getline(cin, key);
        }
        else if (key == "select")
        {
            cin.get();
            getline(cin, key);
        }
        else if (key == "remove")
        {
            cin.get();
            getline(cin, key);
        }
        else
        {
            cout << "Command not Found" << endl;
            exit(0);
        }
    }
}
void MyDB::info_table()
{
    cout << "\t\t Command info! \n\n "
         << "1)";
}

void MyDB::create_entity(string command) // Create new Entity
{
    string key;
    fstream obj;
    fstream com("Entity_info.txt", fstream::app);
    stringstream str(command);
    while (str >> key)
    {
        if (key == "entity")
        {
            str >> key;
            if (legal_entity(key) == true)
            {
                obj.open(key + ".txt", fstream::out);
                com << key << " ";
            }
            else
            {
                cout << "Enter comand again" << endl;
                return;
            }
        }
        else
            com << key << " ";
    }
    com << "\n";
}

void MyDB::insert_date(string command) // Insert new Date
{
    string key, tmp_key, tmp_value;
    string types;
    fstream fs;
    unordered_map<string, string> mp;
    istringstream str(command);
    str >> key;

    if (key == "into")
    {
        str >> key;
        command.erase(0, key.size() + 5);
        types = del_simb_line(command);
        cout << types << endl;
        str.clear();
        if (!legal_entity(key))
        {
            str.str(types);
            auto it = (entity_mp.find(key));
            for (auto a : it->second)
            {
                mp[a.first] = "";
            }
            fs.open(key + ".txt", fstream::app);
            while (str >> tmp_key)
            {
                str >> tmp_value;
                if (legal_types(key, tmp_key, tmp_value) == true)
                {
                    mp[tmp_key] = tmp_value;
                }
                else
                {
                    return;
                }
            }
            for (auto a : mp)
            {
                fs << a.second << "  ";
            }
            fs << '\n';
        }
        else
        {
            cout << "Enter comand again" << endl;
            return;
        }
    }
}

void MyDB::update_date(string command) // Update Date
{
}
void MyDB::select_date_to_read(string command) // Sellect to Read
{
}
void MyDB::remove_date(string) // Remove Date
{
}

#endif //MYDB