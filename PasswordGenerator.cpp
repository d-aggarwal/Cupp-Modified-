#include <bits/stdc++.h>
#include <fstream>
using namespace std;

#define int long long
#define vll vector<long long>
char special;

ofstream outfile("output.txt");

void p(const string& ans) {
    if (!outfile.is_open()) {
        cerr << "Error: Could not open output.txt for writing." << endl;
        return;
    }
    outfile << ans << endl;
}

void generateCombinations(const string& str, int index, string current) {
    if (index == str.size()) {
        p('.'+current+'.');
        return;
    }
    char ch = str[index];
    if (isalpha(ch)) {
        generateCombinations(str, index + 1, current + (char)tolower(ch));
        generateCombinations(str, index + 1, current + (char)toupper(ch));
    } else {
        generateCombinations(str, index + 1, current + ch);
    }
}

// void concatenateEachPair(const vector<string>& strVec) {
//     int n = strVec.size();
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             if (i != j) {
//                 generateCombinations(strVec[i] + strVec[j], 0, "");
//             }
//         }
//     }
// }

void generateInterleavings(const string& str1, const string& str2, string current, const vector<string>& strNumber) {
    if (str1.empty() && str2.empty()) {
        generateCombinations(current, 0, "");
        for (auto it : strNumber) {
            generateCombinations(current + it, 0, "");
            generateCombinations(current + it, 0, "");
        }
        return;
    }

    // Always prioritize processing characters from str1
    if (!str1.empty()) {
        generateInterleavings(str1.substr(1), str2, current + str1[0], strNumber);
    }
    if (!str2.empty()) {
        generateInterleavings(str1, str2.substr(1), current + str2[0], strNumber);
    }
}


void generatePrefixes(const vector<string>& strings,const vector<string>& strNumber) {
    for (const auto& str : strings) {
        for (int i = 0; i < str.length(); i++) {
            generateCombinations(str.substr(0, i + 1), 0, "");
            for(auto it:strNumber){
                generateCombinations(str.substr(0, i + 1)+it, 0, "");
                generateCombinations(it+str.substr(0, i + 1), 0, "");
            }
        }
    }
}

// void generateWithNumbers(const vector<string>& strString, const vector<string>& strNumber) {
//     for (const auto& str : strString) {
//         for (const auto& num : strNumber) {
//             generateCombinations(str + num, 0, "");
//             generateCombinations(num + str, 0, "");
//         }
//     }
// }

void generateNestedCombinations(const vector<string>& strString, const vector<string>& strNumber) {
    for (const auto& str1 : strString) {
        string prefix = "";
        for (const auto& ch : str1) {
            prefix += ch;
            for (const auto& str2 : strString) {
                if (str1 != str2) {
                    string suffix = "";
                    for (int k=0;k<str2.size();k++) {
                        suffix += str2[k];
                        generateCombinations(prefix + suffix, 0, "");
                        for (const auto& num : strNumber) {
                            generateCombinations(prefix + num + suffix, 0, "");
                            generateCombinations(num + prefix + suffix, 0, "");
                            generateCombinations(prefix + suffix + num, 0, "");
                        }
                    }
                }
            }
        }
    }
    for (const auto& str1 : strString) {
        string prefix = "";
        for (const auto& ch : str1) {
            prefix += ch;
            for (const auto& str2 : strString) {
                if (str1 != str2) {
                    string suffix = "";
                    for (int k=str2.size()-1;k>0;k--){
                        suffix =str2[k]+suffix;
                        generateCombinations(prefix + suffix, 0, "");
                        for (const auto& num : strNumber) {
                            generateCombinations(prefix + num + suffix, 0, "");
                            generateCombinations(num + prefix + suffix, 0, "");
                            generateCombinations(prefix + suffix + num, 0, "");
                        }
                    }
                }
            }
        }
    }
}

void stage1(const vector<string>& strString, const vector<string>& strNumber) {
    generatePrefixes(strString,strNumber);
    for (const auto& num : strNumber) {
        p(num);
    }
}

void stage2(const vector<string>& strString, const vector<string>& strNumber) {
    stage1(strString, strNumber);
    //concatenateEachPair(strString);
}

void stage3(const vector<string>& strString, const vector<string>& strNumber) {
    stage2(strString, strNumber);
    generateNestedCombinations(strString, strNumber);
}

void stage4(const vector<string>& strString, const vector<string>& strNumber) {
    stage3(strString, strNumber);
    //generateWithNumbers(strString, strNumber);
    for (int i = 0; i < strString.size(); ++i) {
        for (int j = i + 1; j < strString.size(); ++j) {
            generateInterleavings(strString[i], strString[j], "",strNumber);
        }
    }
}
//with special character
void generateCombinations$(const string& str, int index, string current) {
    if (index == str.size()) {
        p('.'+current+'.');
        return;
    }
    char ch = str[index];
    if (isalpha(ch)) {
        generateCombinations$(str, index + 1, current + (char)tolower(ch));
        generateCombinations$(str, index + 1, current + (char)toupper(ch));
    } else {
        generateCombinations$(str, index + 1, current + ch);
    }
}

void generateInterleavings$(const string& str1, const string& str2, string current, const vector<string>& strNumber) {
    if (str1.empty() && str2.empty()) {
        generateCombinations(current + special, 0, "");
        generateCombinations(special + current, 0, "");
        for (auto it : strNumber) {
            generateCombinations(current + special + it, 0, "");
            generateCombinations(current + it + special, 0, "");
            generateCombinations(it + current + special, 0, "");
            generateCombinations(it + special + current, 0, "");
        }
        return;
    }

    // Prioritize processing characters from str1
    if (!str1.empty()) {
        generateInterleavings$(str1.substr(1), str2, current + str1[0], strNumber);
    }
    if (!str2.empty()) {
        generateInterleavings$(str1, str2.substr(1), current + str2[0], strNumber);
    }
}


void generatePrefixes$(const vector<string>& strings,const vector<string>& strNumber) {
    for (const auto& str : strings) {
        for (int i = 0; i < str.length(); i++) {
            generateCombinations(special+str.substr(0, i + 1), 0, "");
            generateCombinations(str.substr(0, i + 1)+special, 0, "");
            for(auto it:strNumber){
                generateCombinations(str.substr(0, i + 1)+it+special, 0, "");
                generateCombinations(special+str.substr(0, i + 1)+it, 0, "");
                generateCombinations(str.substr(0, i + 1)+special+it, 0, "");
                generateCombinations(it+str.substr(0, i + 1)+special, 0, "");
                generateCombinations(it+special+str.substr(0, i + 1), 0, "");
                generateCombinations(special+it+str.substr(0, i + 1), 0, "");
                
            }
        }
    }
}

// void generateWithNumbers$(const vector<string>& strString, const vector<string>& strNumber) {
//     for (const auto& str : strString) {
//         for (const auto& num : strNumber) {
//             generateCombinations$(special+str + num, 0, "");
//             generateCombinations$(str+ special + num, 0, "");
//             generateCombinations$(str+ num +special, 0, "");
//             generateCombinations$(special+ num + str, 0, "");
//             generateCombinations$(num +special+ str, 0, "");
//             generateCombinations$(num + str +special, 0, "");
//         }
//     }
// }

void generateNestedCombinations$(const vector<string>& strString, const vector<string>& strNumber) {
    for (const auto& str1 : strString) {
        string prefix = "";
        for (const auto& ch : str1) {
            prefix += ch;
            for (const auto& str2 : strString) {
                if (str1 != str2) {
                    string suffix = "";
                    for (const auto& ch2 : str2) {
                        suffix += ch2;
                        generateCombinations$(prefix +special+ suffix, 0, "");
                        generateCombinations$(special+prefix + suffix, 0, "");
                        generateCombinations$(prefix + suffix+special, 0, "");
                        for (const auto& num : strNumber) {
                            generateCombinations$(prefix + special+num + suffix, 0, "");
                            generateCombinations$(prefix + num +special+ suffix, 0, "");
                            generateCombinations$(special+prefix + num + suffix, 0, "");
                            generateCombinations$(prefix+special + num + suffix, 0, "");
                            generateCombinations$(prefix + num + special+ suffix, 0, "");
                            generateCombinations$(prefix + num + suffix + special, 0, "");
                            generateCombinations$(num+special + prefix + suffix, 0, "");
                            generateCombinations$(special+num + prefix + suffix, 0, "");
                            generateCombinations$(num + prefix+special+ suffix, 0, "");
                            generateCombinations$(num +special+ prefix + suffix, 0, "");
                            generateCombinations$(num + prefix +special+ suffix, 0, "");
                            generateCombinations$(num + prefix + suffix + special, 0, "");
                            generateCombinations$(prefix+special + suffix + num, 0, "");
                            generateCombinations$(special + prefix + suffix + num, 0, "");
                            generateCombinations$(prefix + suffix+special+ num, 0, "");
                            generateCombinations$(prefix + special+ suffix + num, 0, "");
                            generateCombinations$(prefix + suffix +special+ num, 0, "");
                            generateCombinations$(prefix + suffix + num+special, 0, "");
                        }
                    }
                }
            }
        }
    }
    for (const auto& str1 : strString) {
        string prefix = "";
        for (const auto& ch : str1) {
            prefix += ch;
            for (const auto& str2 : strString) {
                if (str1 != str2) {
                    string suffix = "";
                    for (int k=str2.size()-1;k>0;k--) {
                        suffix =str2[k]+suffix;
                        generateCombinations$(prefix +special+ suffix, 0, "");
                        generateCombinations$(special+prefix + suffix, 0, "");
                        generateCombinations$(prefix + suffix+special, 0, "");
                        for (const auto& num : strNumber) {
                            generateCombinations$(prefix + special+num + suffix, 0, "");
                            generateCombinations$(prefix + num +special+ suffix, 0, "");
                            generateCombinations$(special+prefix + num + suffix, 0, "");
                            generateCombinations$(prefix+special + num + suffix, 0, "");
                            generateCombinations$(prefix + num + special+ suffix, 0, "");
                            generateCombinations$(prefix + num + suffix + special, 0, "");
                            generateCombinations$(num+special + prefix + suffix, 0, "");
                            generateCombinations$(special+num + prefix + suffix, 0, "");
                            generateCombinations$(num + prefix+special+ suffix, 0, "");
                            generateCombinations$(num +special+ prefix + suffix, 0, "");
                            generateCombinations$(num + prefix +special+ suffix, 0, "");
                            generateCombinations$(num + prefix + suffix + special, 0, "");
                            generateCombinations$(prefix+special + suffix + num, 0, "");
                            generateCombinations$(special + prefix + suffix + num, 0, "");
                            generateCombinations$(prefix + suffix+special+ num, 0, "");
                            generateCombinations$(prefix + special+ suffix + num, 0, "");
                            generateCombinations$(prefix + suffix +special+ num, 0, "");
                            generateCombinations$(prefix + suffix + num+special, 0, "");
                        }
                    }
                }
            }
        }
    }
}

void stage1$(const vector<string>& strString, const vector<string>& strNumber) {
    generatePrefixes$(strString,strNumber);
    for (const auto& num : strNumber) {
        p(num);
    }
}

void stage2$(const vector<string>& strString, const vector<string>& strNumber) {
    stage1$(strString, strNumber);
    //concatenateEachPair$(strString);
}

void stage3$(const vector<string>& strString, const vector<string>& strNumber) {
    stage2$(strString, strNumber);
    generateNestedCombinations$(strString, strNumber);
}

void stage4$(const vector<string>& strString, const vector<string>& strNumber) {
    stage3$(strString, strNumber);
    //generateWithNumbers$(strString, strNumber);
    for (const auto& str1 : strString) {
        for (const auto& str2 : strString) {
            if (str1 != str2) {
                generateInterleavings$(str1, str2, "",strNumber);
            }
        }
    }
}

void solve() {
    vector<string> strString, strNumber;
    string st;

    cout << "Enter first name: ";
    cin >> st;
    strString.push_back(st);

    cout << "Enter second name: ";
    cin >> st;
    strString.push_back(st);

    cout << "Enter partner's name: ";
    cin >> st;
    strString.push_back(st);

    cout << "Enter partners second name: ";
    cin >> st;
    strString.push_back(st);

    cout << "Enter children name: ";
    cin >> st;
    strString.push_back(st);

    cout << "Enter mobile number: ";
    cin >> st;
    strNumber.push_back(st);

    cout << "Enter your DOB (e.g., DD-MM-YYYY): ";
    cin >> st;
    strNumber.push_back(st);

    // Parse mobile number for combinations
    string num = strNumber[0];
    if (num.length() == 10) {
        strNumber.push_back(num.substr(0, 2));
        strNumber.push_back(num.substr(0, 3));
        strNumber.push_back(num.substr(0, 4));
        strNumber.push_back(num.substr(4, 6));
        strNumber.push_back(num.substr(6, 4));
        strNumber.push_back(num.substr(8, 2));
    }

    // Parse DOB for additional combinations
    string dob = strNumber[1];
    strNumber.push_back(dob.substr(0, 2));
    strNumber.push_back(dob.substr(0, 4));
    strNumber.push_back(dob.substr(4, 4));
    char check;
    cout<<"Do u want to add special char[y/n]: ";
    cin>>check;
    if(check=='y'){
        cout<<"Enter the special character: ";
        cin>>special;
        stage4(strString, strNumber);
        stage4$(strString, strNumber);
        for(auto it:strNumber){
        p('.'+it+'.');
        p('.'+(special+"")+it+'.');
        p('.'+it+(special+"")+'.');
        for(int i=0;i<it.size();i++){ 
            string strr=it.substr(0,i+1)+(special)+it.substr(i+1);
            p('.'+strr+'.');
        }
        }
    }
    else{

        stage4(strString, strNumber);
        for(auto it:strNumber){
           p('.'+it+'.');
        }
    }
    
}

int32_t main() {
    solve();

    if (outfile.is_open()) {
        outfile.close();
    }

    return 0;
}