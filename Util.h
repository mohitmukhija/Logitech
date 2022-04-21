#pragma once

constexpr int BitsInChar = ((sizeof(char)) * 8);

template<class T>
T switchEndian(T obj)
{
    // Check if data is already in little endian in system 
    std::bitset<4> foo(1);
    if (foo[0] == 0)
        return obj;
    std::string objString = obj.to_string();
    std::reverse(objString.begin(), objString.end());
    return T(objString);
}
