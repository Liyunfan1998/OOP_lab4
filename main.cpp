#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <vector>
#include "biginteger.cpp"

using namespace std;
using std::getline;

vector<string> split(const string &s, const string &seperator) {
    vector<string> result;
    typedef string::size_type string_size;
    string_size i = 0;

    while (i != s.size()) {
        int flag = 0;
        while (i != s.size() && flag == 0) {
            flag = 1;
            for (string_size x = 0; x < seperator.size(); ++x)
                if (s[i] == seperator[x]) {
                    ++i;
                    flag = 0;
                    break;
                }
        }
        flag = 0;
        string_size j = i;
        while (j != s.size() && flag == 0) {
            for (string_size x = 0; x < seperator.size(); ++x)
                if (s[j] == seperator[x]) {
                    flag = 1;
                    break;
                }
            if (flag == 0)
                ++j;
        }
        if (i != j) {
            result.push_back(s.substr(i, j - i));
            i = j;
        }
    }
    return result;
}

BigNum processOneRequest(vector<string> request) {
    BigNum result;
    vector<BigNum> tmpBigNum;
    string tmpOp;
    for (const auto &item:request) {
        if (item == "+" || item == "-" || item == "*" || item == "/") tmpOp = item;
        else if (item.length() <= 40)
            tmpBigNum.emplace_back(item.c_str());
        else printf("%s", "出错啦1");

        if (tmpBigNum.size() == 2) {
            if (tmpOp == "+") {
                result = tmpBigNum[0] + tmpBigNum[1];
            } else if (tmpOp == "-") {
                result = tmpBigNum[0] - tmpBigNum[1];
            } else if (tmpOp == "*") {
                result = tmpBigNum[0] * tmpBigNum[1];
            } else if (tmpOp == "/") {
                result = tmpBigNum[0] / tmpBigNum[1];
            } else {
                cout << "出错啦2" << endl;
                exit(-1);
            }
            tmpBigNum.clear();
            tmpBigNum.emplace_back(result);
//            cout << item << endl;
        }
    }
    return result;
}

class ca {
public:
    long value;

    //重载为成员函数格式
    long operator+(const ca &v) {
        return this->value + v.value; // 等同于return value+v.value;
    }
};

//重载为非成员函数格式
//long operator+(const ca &v1, const ca &v2) {
//    return v1.value + v2.value;
//}
//
//long operator-(const ca &v1, const ca &v2) {
//    return v1.value - v2.value;
//}
//
//long operator*(const ca &v1, const ca &v2) {
//    return v1.value * v2.value;
//}
//
//long operator/(const ca &v1, const ca &v2) {
//    return v1.value / v2.value;
//}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "您输入的参数应该为两个" << endl;
    } else {

        vector<BigNum> results;
        ifstream samplein;
        samplein.open(argv[1]);
//    samplein.open("/Users/luke1998/Desktop/OOP/OOP_pj4/sample.in");
        if (!samplein) cout << "sample.in read error" << endl;
        else {
            string str;
            getline(samplein, str);
//            cout << samplein << endl;
            while (getline(samplein, str))   //按行读取,遇到换行符结束
            {
                vector<string> tmp = split(str, " ");
                BigNum result = processOneRequest(tmp);
                results.push_back(result);
                result.print();
            }
        }
        samplein.close();

        ofstream sampleout;
        sampleout.open(argv[2]);
//    sampleout.open("/Users/luke1998/Desktop/OOP/OOP_pj4/sample2.out");
        if (!sampleout) cout << "sample.out read error" << endl;
        else {
            for (auto bigNum:results) {
                bigNum.print2ofstream(sampleout);
            }
        }
    }

//    ca a, b;
//
//    a.value = 10;
//    b.value = 20;
//
//    printf("a+b:%ld\n", a + b);    // 优先用成员函数
//    printf("a-b:%ld\n", a - b);    // 优先用成员函数
//    printf("a*b:%ld\n", a * b);    // 优先用成员函数
//    printf("a/b:%ld\n", a / b);    // 优先用成员函数

    return 0;
}