//
// Created by gefre on 10.02.2020.
//

#ifndef PIV_FLIST_H
#define PIV_FLIST_H

#include <fstream>
#include <iostream>

using namespace std;

class Flist : fstream {

    char* name;

    const int number_of_records = 8;

    template <typename T>
    void add(const T &dat);

public:
    Flist(char name[] = (char*)"data.bin");
    ~Flist();

    template <typename T>
    void fwrite(const T val);

    template <typename T>
    T fread() {
        T val;
        this->read((char *) &val, sizeof(val));
        return val;
    }

    int len();

    void Set(int index);

    template <typename T>
    T extr(int ind)
    {
        Set(ind);
        T tmp;
        *this >> tmp;
        return tmp;
    }

    template <typename T>
    T del(const int &num) {
        static_assert(is_integral<T>::value || is_floating_point<T>::value,
                      "Argument should be of integral or floating point type");
        T ans = extr<T>(num);

        int prevPos = 0;
        seekg(prevPos);
        int curPos = fread<int>();
        for (int i = 1; i < num; ++i) {
            prevPos = curPos;
            seekg(curPos);
            curPos = fread<int>();
        }
        seekg(curPos);
        int nextPos = fread<int>();
        seekp(prevPos);
        fwrite(nextPos);
        // Обновить позицию последнего, если надо
        if (nextPos == 0) {
            seekp(sizeof(int));
            fwrite(prevPos);
        }
        // Обновление длины списка
        seekg(sizeof(int) * 2);
        int tmp = fread<int>();
        seekp(sizeof(int) * 2);
        fwrite(tmp - 1);
        return ans;
    }

    template <typename T>
    bool insByNum(const int &num, T &dat) {
        if (len() + 1 < num || num < 1) {
            return false;
        }

        if (num == (len() + 1)) {
            *this << dat;
            return true;
        }

        seekg(sizeof(int));
        int last_pos = fread<int>();
        seekg(0, ios::end);
        int cur_pos = tellg();

        if (num == 1) {
            seekg(0);
            int next_pos = fread<int>();

            *this << dat;
            seekp(0);
            fwrite(cur_pos);
            fwrite(last_pos);

            seekp(last_pos);
            fwrite((int) 0);

            seekp(cur_pos);
            fwrite(next_pos);
            return true;
        }
        Set(num - 1);
        seekg(-sizeof(int), ios::cur);
        int prev_pos = tellg();
        seekg(prev_pos);
        int next_pos = fread<int>();

        *this << dat;

        seekp(sizeof(int));
        fwrite(last_pos);

        seekp(prev_pos);
        fwrite(cur_pos);

        seekp(last_pos);
        fwrite((int) 0);

        seekp(cur_pos);
        fwrite(next_pos);
        return true;
    }

    template<typename T>
    bool edit(const int &num, T &dat) {
        int len = this->len();
        if (len == 0 || len < num) {
            return false;
        }

        T tmp = this->del<T>(num);

        if (sizeof(dat) > sizeof(tmp))
        {
            *this << dat;
        }
        else
        {
            insByNum(num, dat);
        }
        return true;
    }

    void swap(const int &lPrev) ;

    template <typename T>
    void sort() {
        int len = this->len();
        if (len < 2) {
            return;
        }

        for (int j = 1; j < len; ++j) {
            bool flag = false;
            int lPrevPos, lPos, rPos;
            T lVal, rVal;
            seekg(0);
            lPrevPos = 0;
            lPos = fread<int>();
            seekg(lPos);
            rPos = fread<int>();
            *this >> lVal;
            seekg(rPos + sizeof(int));
            *this >> rVal;

            for (int i = 1; i <= len - j; ++i) {
                if (lVal > rVal) {
                    this->swap(lPrevPos);
                    flag = true;
                }
                // Сдвиг пузыря
                seekg(lPrevPos);
                lPrevPos = fread<int>();
                seekg(lPrevPos);
                lPos = fread<int>();
                seekg(lPos);
                rPos = fread<int>();
                *this >> lVal;
                if (rPos != 0) {
                    seekg(rPos + sizeof(int));
                    *this >> rVal;
                } else {
                    break;
                }
            }
            if (!flag) {
                break;
            }
        }
    }

    template <typename T>
    void pageView(const int& num)
    {
        if (len() > (num - 1) * number_of_records)
        {
            cout << "Page " << num << endl;
            for (int i = (num - 1) * number_of_records; i < len() && i < number_of_records * num; ++i)
            {
                cout << this->extr<T>(i + 1) << " ";
            }
            cout << endl;
        }
    }

    template <typename T>
    void compression()
    {
        {
            Flist tmp((char *) "tmp.bin");
            seekg(2 * sizeof(int));
            int length = len();

            for (int i = 1; i <= length; ++i)
            {
                tmp.add(extr<T>(i));
            }
        }

        close();

        if (remove(name))
        {
            cerr << "Can't remove " << name;
            exit(2);
        }

        if (rename("tmp.bin", name))
        {
            cerr << "Can't rename file tmp.bin";
            exit(3);
        }

        open(name, ios::binary | ios::out | ios::in | ios::ate);
        if (!*this)
        {
            cerr << "Can't open " << name;
            exit(1);
        }
    }

    template <typename T>
    void insWithOrder(T& data)
    {
        *this << data;
        this->sort<T>();
    }

    Flist  &operator<<(char &);
    Flist  &operator<<(short &);
    Flist  &operator<<(int &);
    Flist  &operator<<(double &);

    char   &operator>>(char &);
    short  &operator>>(short &);
    int    &operator>>(int &);
    double &operator>>(double &);
};


#endif //PIV_FLIST_H
