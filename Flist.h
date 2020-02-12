#ifndef PIV_FLIST_H
#define PIV_FLIST_H

#include <fstream>

using namespace std;

class Flist : fstream {
    char* name;
    const int numOfRecords = 8;

    template <typename T>
    void add(const T &);

    void Set(const int &);

public:
    explicit Flist(char name[] = (char*)"data.bin");

    ~Flist() override;

    template <typename T>
    void fwrite(const T &);

    template <typename T>
    T fread();

    int len();


    template <typename T>
    T extr(const int &ind)
    {
        if (ind < 1 || ind > len())
        {
            throw "Index out of range";
        }
        Set(ind);
        T tmp;
        *this >> tmp;
        return tmp;
    }

    template <typename T>
    T del(const int &ind) {
        if (ind < 1 || ind > len())
        {
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

    template <typename T>
    void insByNum(const int &ind, T &elem) {
        if (len() + 1 < ind || ind < 1) {
            throw "Index out of range";
        }

        if (ind == (len() + 1)) {
            *this << elem;
            return;
        }

        seekg(sizeof(int));
        int last_pos = fread<int>();
        seekg(0, ios::end);
        int cur_pos = tellg();

        if (ind == 1) {
            seekg(0);
            int next_pos = fread<int>();

            *this << elem;
            seekp(0);
            fwrite(cur_pos);
            fwrite(last_pos);

            seekp(last_pos);
            fwrite((int) 0);

            seekp(cur_pos);
            fwrite(next_pos);
            return;
        }
        Set(ind - 1);
        seekg(-sizeof(int), ios::cur);
        int prev_pos = tellg();
        seekg(prev_pos);
        int next_pos = fread<int>();

        *this << elem;

        seekp(sizeof(int));
        fwrite(last_pos);

        seekp(prev_pos);
        fwrite(cur_pos);

        seekp(last_pos);
        fwrite((int) 0);

        seekp(cur_pos);
        fwrite(next_pos);
    }

    template<typename T>
    void edit(const int &num, T &dat) {
        int len = this->len();
        if (len == 0 || len < num) {
            throw "Index out of range";
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
        if (len() > (num - 1) * numOfRecords)
        {
            cout << "----------Page " << num << "----------" << endl;
            for (int i = (num - 1) * numOfRecords; i < len() && i < numOfRecords * num; ++i)
            {
                cout << this->extr<T>(i + 1) << " ";
            }
            cout << endl;
        }
        else
        {
            cout << "Wrong page" << endl;
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
//                tmp.add(extr<T>(i));
                 tmp << extr<T>(i);
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

    Flist  &operator<<(const char &);
    Flist  &operator<<(const short &);
    Flist  &operator<<(const int &);
    Flist  &operator<<(const double &);

    char   &operator>>(char &);
    short  &operator>>(short &);
    int    &operator>>(int &);
    double &operator>>(double &);
};


#endif //PIV_FLIST_H
