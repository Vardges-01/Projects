#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
struct variable
{
    std::string m_type;
    std::string m_name;
    std::string m_value;
};

std::vector<std::string> token;
std::vector<variable> variables;

bool etef(std::string lhs, std::string znak, std::string rhs)
{
    double m_lhs;
    double m_rhs;
    std::string new_lhs = lhs;
    std::string new_rhs = rhs;
    for (int ix = 0; ix < variables.size(); ++ix)
    {
        if (variables[ix].m_name == lhs) { new_lhs = variables[ix].m_value; }
        if (variables[ix].m_name == rhs) { new_rhs = variables[ix].m_value; }
    }
    if (lhs[0] >= '0' && lhs[0] <= '9') { new_lhs = lhs; }
    if (rhs[0] >= '0' && rhs[0] <= '9') { new_rhs = rhs; }
    if (new_lhs == "" && new_rhs == "") 
    { 
        std::cout << "Error... Not found Element"; 
        exit(0); 
    }

    std::stringstream ssj;
    ssj << new_lhs;
    ssj >> m_lhs;
    std::stringstream ssi;
    ssi << new_rhs;
    ssi >> m_rhs;
    if (znak == "<"){ return (m_lhs < m_rhs);}
    else if (znak == ">"){ return (m_lhs > m_rhs);}
    else if (znak == "=="){ return (m_lhs == m_rhs);}
    else if (znak == "&&"){ return (m_lhs && m_rhs);} 
    else if (znak == "!="){ return (m_lhs != m_rhs);}
    else if (znak == "||"){ return (m_lhs || m_rhs);}
    else if (znak == "<"){ return (m_lhs < m_rhs);}
    else if (znak == "<="){ return (m_lhs <= m_rhs);}
    else if (znak == ">="){ return (m_lhs >= m_rhs);}
    return false;
}

int main()
{
    std::string str;
    bool m_value_key = false;
    bool if_key = false;
    bool cikl_key = false;
    char symbol;
    std::fstream fs;
    fs.open("file.txt");

    //Kardum enq File
    while (!fs.eof())
    {
        fs.get(symbol);
     std::cout<<symbol;
        if (symbol != ' ' && symbol != '\n')
        {
            str.push_back(symbol);
        }
        else if(str != "")
        {
            token.push_back(str);
            str = "";
        }
    }
    variable v;
    //Kardum enq Tokenner
    for (int i = 0; i < token.size(); ++i)
    {
        // Gtnum enq Tvi m_type
        if (token[i] == "tiv")
        {
            v.m_name = token[i + 1];
            v.m_type = "float";
            v.m_value = "";
            variables.push_back(v);
            continue;
        }

        //Talis enq Arjeq
        if (token[i] == "=" )
        {   
            if(token[i + 2] != "+" && token[i + 2 ] != "-" && token[i+2] != "*" && token[i+2] != "/" )
            {
                for (int j = 0; j < variables.size(); ++j)
                {
                    if (token[i - 1] == variables[j].m_name)
                    {
                        std::string value = token[i + 1];

                        for(int ix = 0; ix < value.length(); ++ix)
                        {
                            if(value[ix]>= '0' && value[ix] <= '9' )
                            {
                                variables[j].m_type = "int";
                                variables[j].m_value = value;   
                            }
                            else if(value[ix] == '.') 
                            { 
                                variables[j].m_type = "float";
                                variables[j].m_value = value;    
                                break; 
                            }

                            if(value[0] == '/')
                            {
                                variables[j].m_value = "";
                                for (ix = 1; value[ix] != '\0'; ++ix)
                                {
                                    variables[j].m_value += value[ix];
                                }
                                break;
                            }
                        }
                        break;
                    }

                }
            }
            continue;
        }

        // Gtnum enq String
        if (token[i] == "txt")
        {
            v.m_name = "";
            v.m_value = "";
            v.m_type = "";

            v.m_name = token[i + 1];
            v.m_type = "string";
            variables.push_back(v);
        }

        // Gtnum enq Bool
        if (token[i] == "hache")
        {
            v.m_name = token[i + 1];
            for (int j = i; j < token.size(); j++)
            {
                if ((token[j] == "=" && token[j - 1] == v.m_name) && token[j + 1] == "chisht" || token[j + 1] == "sxal")
                {
                    v.m_value = token[j + 1];
                    v.m_type = "bool";
                }
                else if (token[j] == "=" && token[j - 1] == v.m_name)
                {
                    std::cout << "Es Hakanum em menak ''Chisht'' kam ''Sxal'' - ''" << token[j + 1] << "'' es incha ?" << std::endl;
                    exit(0);
                }
            }
            variables.push_back(v);
        }

        //Tpelu gorcoxutyun
        if (token[i] == "zarge")
        {
            for (int j = i + 1; token[j] != ";"; ++j)
            {
                if (token[j] == "->")
                {
                    if (token[j + 1] == "|")
                    {
                        for (int ix = j + 2; token[ix] != "|"; ++ix) { std::cout << token[ix]<<" "; }
                    }

                    for (int ix = 0; ix < variables.size(); ++ix)
                    {
                        if (token[j + 1] == variables[ix].m_name) { std::cout << variables[ix].m_value; }
                    }
                }
                if (token[j] == "->" && token[j + 1] == "bacat") { std::cout << "\n"; break; }
                // else
                // {
                //     std::cout << "Sintax ERROR ''" << token[j] << "''" << std::endl;
                //     exit(0);
                // }
            }
        }

        // Mat. gorcoxutyunner
        // Operators ( +, -, *, / )
        if(token[i] == "+" || token[i] == "-" || token[i] == "*" || token[i] == "/")
        {
            if (token[i-2] == "=")
            {
                for (int j = 0; j < variables.size(); ++j)
                {
                    if (token[i - 3] == variables[j].m_name)
                    {
                        std::stringstream bbb, ccc, in_val;
                        std::string num1 = token[i - 1];
                        std::string num2 = token[i + 1];

                        // int -i depq
                        if (variables[j].m_type == "int")
                        {
                            int val, b,c;
                            if(num1[0]>= '0' && num1[0]<= '9') { bbb << num1; bbb >> b; }
                            if(num2[0]>= '0' && num2[0]<= '9') { ccc << num2; ccc >> c; }

                            for (int ix = 0; ix < variables.size(); ++ix)
                            {
                                if (variables[ix].m_name == num1)
                                {
                                    bbb<<variables[ix].m_value;
                                    bbb>>b;
                                }
                                if (variables[ix].m_name == num2)
                                {
                                    ccc << variables[ix].m_value;
                                    ccc >> c;
                                }
                            }
                            if(token[i]=="+") { val = b + c; }
                            if(token[i]=="-") { val = b - c; }
                            if(token[i]=="*") { val = b * c; }
                            if(token[i]=="/") { val = b / c; }

                            in_val << val;
                            in_val >> variables[j].m_value;
                            break;
                        }
                        // float -i dempq
                        if (variables[j].m_type == "float")
                        {
                            float val, b,c;
                            if(num1[0]>= '0' && num1[0]<= '9') { bbb << num1; bbb >> b; }
                            if(num2[0]>= '0' && num2[0]<= '9') { ccc << num2; ccc >> c; }

                            for (int ix = 0; ix < variables.size(); ++ix)
                            {
                                if (variables[ix].m_name == num1)
                                {
                                    bbb<<variables[ix].m_value;
                                    bbb>>b;
                                }
                                if (variables[ix].m_name == num2)
                                {
                                    ccc << variables[ix].m_value;
                                    ccc >> c;
                                }
                            }
                            if(token[i]=="+") { val = b + c; }
                            if(token[i]=="-") { val = b - c; }
                            if(token[i]=="*") { val = b * c; }
                            if(token[i]=="/") { val = b / c; }
                            
                            in_val << val;
                            in_val >> variables[j].m_value;
                            break;
                        }
                        //string -i demp
                        if (variables[j].m_type == "string")
                        {
                            if(token[i]=="+")
                            {
                                bool num = false;
                                bool num1 = false;
                                bool num2;
                                std::string lhs;
                                std::string rhs;
                                for (int y = 0; y < variables.size(); ++y)
                                {
                                    if (token[i - 1] == variables[y].m_name)
                                    {
                                        lhs = variables[y].m_value;
                                        num = true;
                                    }
                                    if (token[i + 1] == variables[y].m_name)
                                    {
                                        rhs = variables[y].m_value;
                                        num1 = true;
                                    }
                                }
                                if (num && num1)
                                {
                                    lhs += rhs;
                                    variables[j].m_value = lhs;
                                }
                                else
                                {
                                    std::cout << "Error";
                                    exit(0);
                                }
                            }
                            else { std::cout << "Operation not Found...."; exit(0); }
                        }
                    }
                }
            }
           
        }

        // //Operator ( ++ , -- )
        if(token[i]=="++" || token[i]=="--")
        {
            float a;
            std::stringstream in_val, out_val;
            std::string name = token[i + 1];
            std::string name1 = token [i - 1];
            for (int j = 0; j < variables.size(); ++j)
            {
                if(name == variables[j].m_name || name1 == variables[j].m_name)
                {
                    if (token[i] == "++")
                    {
                        in_val << variables[j].m_value;
                        in_val >> a;
                        ++a;
                        out_val << a;
                        out_val >> variables[j].m_value;
                        break;
                    }
                    if (token[i] == "--")
                    {
                        in_val << variables[j].m_value;
                        in_val >> a;
                        --a;
                        out_val << a;
                        out_val >> variables[j].m_value;
                        break;
                    }
                }
            }
            continue;
        }

        // If ( Ete )
        if (token[i] == "ete")
        {
            if (token[i + 1] == "[")
            {
                for (int j = i; token[j] != "]"; ++j)
                {
                    if (token[j] == "<" || token[j] == ">" || token[j] == "==" || token[j] == "&&" || token[j] == "!=" || token[j] == "||" || token[j] == "<=" || token[j] == ">=")
                    {
                        if (etef(token[j - 1], token[j], token[j + 1])) { break; }
                        else { while (token[i] != "}"){ ++i; } if_key = true; }
                    }
                }
            }    
        }

        // Else ( Eteche )
        if (token[i] == "eteche")
        {
            if (token[i + 1] == "{" && if_key == true) { continue; }
            if (if_key == false) { while (token[i] != "}") { ++i; } }
        }

        //While
        if (token[i] == "qani")
        {
            if (token[i + 1] == "[")
            {
                for (int j = i + 1; token[j] != "]"; ++j)
                {
                    if (token[j] == "<" || token[j] == ">" || token[j] == "==" || token[j] == "&&" || token[j] == "!=" || token[j] == "||" || token[j] == "<=" || token[j] == "=>")
                    {
                        if (etef(token[j - 1], token[j], token[j + 1]))
                        {
                            if (token[j + 3] == "{")
                            {
                                cikl_key = true;
                                break;
                            }
                            else
                            {
                                std::cout << "Error Cikl..." << std::endl;
                            }
                        }
                        else
                        {
                            while (token[i] != "}") { ++i; }
                            cikl_key = false;
                        }
                    }
                }
            }
        }
        if (token[i] == "}" && cikl_key == true)
        {
            while (cikl_key == true && token[i+1] != "qani")
            {
                --i;
            }
            continue;
        }

    }

    // std::cout << variables[0].m_name << std::endl;
    // std::cout << variables[0].m_type << std::endl;
    // std::cout << variables[0].m_value << std::endl;
    // std::cout << std::endl;
    // std::cout << variables[1].m_name << std::endl;
    // std::cout << variables[1].m_type << std::endl;
    // std::cout << variables[1].m_value << std::endl;
    // std::cout << std::endl;
    // std::cout << variables[2].m_name << std::endl;
    // std::cout << variables[2].m_type << std::endl;
    // std::cout << variables[2].m_value << std::endl;
    // std::cout << std::endl;
    // std::cout << variables[3].m_name << std::endl;
    // std::cout << variables[3].m_type << std::endl;
    // std::cout << variables[3].m_value << std::endl;
}