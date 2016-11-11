/*! Author: qwchen
 *! Date  : 2016-11-11
 * 任意进制之间的转换
 * 思想：利用十进制作为中介，先将原进制转化为十进制，再将十进制转化为目标进制
 */

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class BinaryConversion{
public:
    BinaryConversion();
    string convert(string srcNum, int srcBinary, int dstBinary); // 不同进制(2~16)之间的转化

private:
    unordered_map<char, int> charToNum;  // 字符转化为数字
    unordered_map<int, char> numToChar;  // 数字转化为字符
    int anyBinaryToDecimal(string num, int binary);     // 将其他进制(2~16)，转化为10进制
    string decimalToAnyBinary(int decimal, int binary); // 将10进制转化为其他进制(2~16)

};

BinaryConversion::BinaryConversion(){
    charToNum['0'] = 0;
    charToNum['1'] = 1;
    charToNum['2'] = 2;
    charToNum['3'] = 3;
    charToNum['4'] = 4;
    charToNum['5'] = 5;
    charToNum['6'] = 6;
    charToNum['7'] = 7;
    charToNum['8'] = 8;
    charToNum['9'] = 9;
    charToNum['A'] = 10;
    charToNum['B'] = 11;
    charToNum['C'] = 12;
    charToNum['D'] = 13;
    charToNum['E'] = 14;
    charToNum['F'] = 15;

    numToChar[0] = '0';
    numToChar[1] = '1';
    numToChar[2] = '2';
    numToChar[3] = '3';
    numToChar[4] = '4';
    numToChar[5] = '5';
    numToChar[6] = '6';
    numToChar[7] = '7';
    numToChar[8] = '8';
    numToChar[9] = '9';
    numToChar[10] = 'A';
    numToChar[11] = 'B';
    numToChar[12] = 'C';
    numToChar[13] = 'D';
    numToChar[14] = 'E';
    numToChar[15] = 'F';
}

/*
 * 将其他进制(2~16)，转化为10进制
 * Parament:
 *     num: string, 其他进制数
 *     binary: int, 进制
 * Return:
 *     int, 十进制数
 */
int BinaryConversion::anyBinaryToDecimal(string num, int binary){
    int decimal = 0;
    for (int i = 0; i < num.size(); i++){
        decimal = decimal * binary + charToNum[num[i]];
    }
    return decimal;
}

/*
 * 将10进制转化为其他进制(2~16)
 * Parament:
 *     decimal: int, 十进制数
 *     binary: int, 进制
 * Return:
 *     string, 其他进制数
 */
string BinaryConversion::decimalToAnyBinary(int decimal, int binary){    
    string str;
    while(decimal > 0){
        str = numToChar[decimal % binary] + str;
        decimal /= binary;
    }
    return str;
}

/*
 * 不同进制(2~16)之间的转化
 * Parament:
 *     srcNum: string, 原始的数
 *     srcBinary: int, 原始进制
 *     dstBinary: int, 目的进制
 * Return:
 *     string, 转化后的数
 */
string BinaryConversion::convert(string srcNum, int srcBinary, int dstBinary){
    int decimal = anyBinaryToDecimal(srcNum, srcBinary);     // 先将原始进制转化为十进制
    string dstNum = decimalToAnyBinary(decimal, dstBinary);  // 再将十进制转化为目的进制
    return dstNum;
}



int test(){
    BinaryConversion binaryConversion;
    cout << binaryConversion.convert("8", 10, 2) << endl;
    cout << binaryConversion.convert("FF", 16, 2) << endl;
}

int main(){
    test();
    return 0;
}

