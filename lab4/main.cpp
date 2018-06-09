#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
using std::getline;

vector<string> split(const string &s, const string &seperator) {
    vector<string> result;
    typedef string::size_type string_size;
    string_size i = 0;

    while (i != s.size()) {
        //找到字符串中首个不等于分隔符的字母；
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

        //找到又一个分隔符，将两个分隔符之间的字符串取出；
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

long processOneRequest(vector<string> request) {
    vector<long> tmpLong;
    string tmpOp;
    long long1, long2;
    for (auto item:request) {
        if (item == "+" || item == "-" || item == "*" || item == "/") tmpOp = item;
        else if (item.length() <= 40)
            tmpLong.push_back(stol(item));
        else printf("%s", "出错啦");
        if (tmpLong.size() >= 2) {
            if (item == "+") return tmpLong[0] + tmpLong[1];
            else if (item == "-")return tmpLong[0] - tmpLong[1];
            else if (item == "*")return tmpLong[0] * tmpLong[1];
            else if (item == "/")return tmpLong[0] / tmpLong[1];
            else {
                cout << "出错啦" << endl;
                exit(-1);
            }
        }
    }
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
long operator+(const ca &v1, const ca &v2) {
    return v1.value + v2.value;
}

long operator-(const ca &v1, const ca &v2) {
    return v1.value - v2.value;
}

long operator*(const ca &v1, const ca &v2) {
    return v1.value * v2.value;
}

long operator/(const ca &v1, const ca &v2) {
    return v1.value / v2.value;
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "您输入的参数应该为两个" << endl;
    } else {
        ifstream samplein;
        samplein.open(argv[1]);
        if (!samplein) cout << "sample.in read error" << endl;
        else {
            string str;
            getline(samplein, str);
//            cout << samplein << endl;
            while (getline(samplein, str))   //按行读取,遇到换行符结束
            {
                vector<string> tmp = split(str, " ");
                long result = processOneRequest(tmp);
//                cout << result << endl;
                printf("%ld", result);
            }
        }
//        ifstream sampleout;
//        sampleout.open(argv[1]);
//        if (!sampleout) cout << "sample.out read error" << endl;
    }

    ca a, b;

    a.value = 10;
    b.value = 20;

    printf("a+b:%ld\n", a + b);    // 优先用成员函数
    printf("a-b:%ld\n", a - b);    // 优先用成员函数
    printf("a*b:%ld\n", a * b);    // 优先用成员函数
    printf("a/b:%ld\n", a / b);    // 优先用成员函数

    return 0;
}