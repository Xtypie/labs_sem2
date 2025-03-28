#include<iostream>
#include<string>
#define N_max 1000 // Число цифр в BigInt
using namespace std;

class BigInt {
    char m_value[N_max];
    short m_size = 0;

    public:
        BigInt(const string& value){
            size_t len = value.length();
            for (int i = 0; i < len; i++)
                m_value[i] = value[len - i - 1] - '0';
            for (int i = len; i < N_max; i++)
                m_value[i] = 0;
            m_size = len;
        }

        void Print()
        {
            for (int i = 0; i < m_size; i++)
                cout << static_cast<short>(m_value[m_size - i - 1]); // Вывести коды символов в массиве
            cout << endl;
        }

        BigInt& operator+=(const BigInt& other) // оператор +=
        {
            bool carry = 0;
            for (int i = 0; i < m_size; i++)
            {
                m_value[i] += other.m_value[i] + carry;
                carry = 0;
                if (m_value[i] > 9)
                {
                    carry = 1;
                    m_value[i] -= 10;
                    m_value[i + 1]++;
                    if (i + 1 == m_size)
                        m_size ++;
                }
            }
            return *this;
        }

        BigInt operator+(const BigInt& other)
        {
            BigInt result(*this);
            result += other;
            return result;
        }

        friend ostream& operator << (ostream& out, const BigInt& other);

        bool operator < (const BigInt& other)
        {
            if (m_size < other.m_size)
                return true;
            if (m_size > other.m_size)
                return false;
            else
            {
                for (int i = m_size - 1; i >= 0; i--)
                {
                    if (m_value[i] < other.m_value[i])
                        return true;
                    else if (m_value[i] > other.m_value[i])
                        return false;
                }
                return false;
            }
        }

        bool operator >= (const BigInt& other)
        {
            return !(*this < other);
        }

        bool operator == (const BigInt & other)
        {
            if (m_size != other.m_size)
                return false;
            else
            {
                for (int i = m_size - 1; i >= 0; i--)
                {
                    if (m_value[i] != other.m_value[i])
                        return false;

                }
                return true;
            }
                
        }

        BigInt& operator *= (const BigInt& other)
        {
            char result[N_max] = {0};
            int ResultSize = m_size + other.m_size;

            for (int i = 0; i < m_size; i++)
            {
                for (int j = 0; j < other.m_size; j++)
                result[i + j] = m_value[i] * other.m_value[j];
            }
            for (int i = 0; i < ResultSize - 1; i++)
            {
                result[i + 1] += result[i] / 10;
                result[i] %= 10;
            }

            while (ResultSize > 1 && result[ResultSize - 1] == 0)
                ResultSize -- ;
            
            return *this;
        }

        BigInt operator * (const BigInt& other)
        {
            BigInt result(*this);
            result *= other;
            return result;
        }

    };

istream& operator >> (istream& in, BigInt other) // оператор "ввода"
{
    string s;
    in >> s;
    other  = BigInt(s);
    return in;
}

ostream& operator << (ostream& out, const BigInt& other) // оператор "вывода"
{
    for (int i = 0; i < other.m_size; i++)
        out << static_cast<short>(other.m_value[other.m_size - i - 1]); // Вывести коды символов в массиве
    cout << endl;
    return out;
}


int main()
{
    BigInt  x("123");
    x.Print();
    BigInt y = x;
    y.Print();


}