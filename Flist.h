// Flist.h -- File List

#ifndef PIV_FLIST_H
#define PIV_FLIST_H

#include <fstream>
#include <iomanip>

using namespace std;

class Flist : fstream {
    char *name;

    template<typename T>
    void add(const T &);

    void Set(const int &);

public:
    const int numOfRecords = 8;

    explicit Flist(char name[] = (char *) "data.bin");
    ~Flist() override;

    template<typename T>
    void fwrite(const T &);

    template<typename T>
    T fread();

    int len();

    Flist  &operator<<(const char &);
    Flist  &operator<<(const short &);
    Flist  &operator<<(const int &);
    Flist  &operator<<(const double &);

    char   &operator>>(char &);
    short  &operator>>(short &);
    int    &operator>>(int &);
    double &operator>>(double &);

    void swap(const int &);

    template<typename T>
    T extr(const int &ind) {
        if (ind < 1 || ind > len()) {
            throw "Index out of range";
        }
        Set(ind);
        T tmp;
        *this >> tmp;
        return tmp;
    }

    template<typename T>
    T del(const int &ind) {
        if (ind < 1 || ind > len()) {
            throw "Index out of range";
        }

        T ans = extr<T>(ind);

        int prevPos = 0;
        seekg(prevPos);
        int curPos = fread<int>();
        for (int i = 1; i < ind; ++i) {
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

    template<typename T>
    void insByNum(const int &ind, T &elem) {
        if (len() + 1 < ind || ind < 1) {
            throw "Index out of range";
        }

        if (ind == (len() + 1)) {
            *this << elem;
            return;
        }

        int prevPos, curPos, nextPos, lastPos;
        seekg(sizeof(int));
        lastPos = fread<int>();
        seekg(0, ios::end);
        curPos = tellg();

        if (ind == 1) {
            seekg(0);
            nextPos = fread<int>();

            *this << elem;
            seekp(0);
            fwrite(curPos);
            fwrite(lastPos);

            seekp(lastPos);
            fwrite((int) 0);

            seekp(curPos);
            fwrite(nextPos);
            return;
        }
        Set(ind - 1);
        seekg(-sizeof(int), ios::cur);
        prevPos = tellg();
        seekg(prevPos);
        nextPos = fread<int>();

        *this << elem;

        seekp(sizeof(int));
        fwrite(lastPos);

        seekp(prevPos);
        fwrite(curPos);

        seekp(lastPos);
        fwrite((int) 0);

        seekp(curPos);
        fwrite(nextPos);
    }

    template<typename T>
    void edit(const int &ind, T &elem) {
        int len = this->len();
        if (len == 0 || len < ind) {
            throw "Index out of range";
        }

        T tmp = del<T>(ind);
        if (sizeof(elem) > sizeof(tmp)) {
            *this << elem;
        } else {
            insByNum(ind, elem);
        }
    }

    template<typename T>
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
                    swap(lPrevPos);
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

    template<typename T>
    void insWithOrder(const T &elem) {
        *this << elem;
        sort<T>();
    }

    template<typename T>
    void pageView(const int &ind) {
        if (len() <= (ind - 1) * numOfRecords) {
            throw "Page out of range";
        }
        cout << "Page " << ind << ':' << endl;
        for (int i = (ind - 1) * numOfRecords; i < len() && i < numOfRecords * ind; ++i) {
            cout << setw(49) << setfill('-') << '-' << endl;
            cout << extr<T>(i + 1);
        }
        cout << setw(49) << setfill('-') << '-' << endl;
    }

    template<typename T>
    void compress() {
        {
            Flist tmp((char *) "tmp.bin");
            seekg(2 * sizeof(int));
            int len = this->len();
            for (int i = 1; i <= len; ++i) {
                tmp << extr<T>(i);
            }
        }
        close();

        if (remove(name)) {
            cerr << "Can't remove " << name;
            exit(2);
        }
        if (rename("tmp.bin", name)) {
            cerr << "Can't rename file tmp.bin";
            exit(3);
        }
        open(name, ios::binary | ios::out | ios::in | ios::ate);
        if (!*this) {
            cerr << "Can't open " << name;
            exit(1);
        }
    }
};


#endif //PIV_FLIST_H
