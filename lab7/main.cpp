#include<iostream>

using namespace std;

template<typename T>
class BoolVec
{
    public:
        void print()
        {
            std::cout << "all types" << endl;
        }
};

struct BitRef
        {
            char* m_value;
            size_t m_index;
            BitRef(char* value, size_t index)
            {
                m_value = value;
                m_index = index;
            }

            void operator=(bool v)
            {
            size_t num = m_index / 8;
            size_t offset = m_index % 8;

            if (v)
                m_value[num] |= (1 << offset);
            else 
            m_value[num] &= ~(1 << offset);
            }
            
        };


template<>
class BoolVec<bool>
{
    private:
        char * m_value;
        size_t m_size;
        size_t m_cap;
    public:
        BoolVec()
        {
            m_value = new char[10];
            m_cap = 10;
            m_size = 0;

        }
        ~BoolVec() 
        {
            delete[] m_value;
        }

        void set(size_t index, bool value)
        {
            size_t num = index / 8;
            size_t offset = index % 8;

            if (value)
                m_value[num] |= (1 << offset);
            else 
            m_value[num] &= ~(1 << offset);
        }

        bool get(size_t index)
        {
            size_t num = index / 8;
            size_t offset = index % 8;

            return m_value[num] & (1 << offset);
        }

        BitRef operator[](size_t index)
        {
            return BitRef(m_value, index);
        }

        void insert(){

        } // доделать

};

ostream& operator<<(ostream& out, BitRef b)
{
    size_t num = b.m_index / 8;
    size_t offset = b.m_index % 8;
    out << ((b.m_value[num] & (1 << offset))?1:0);
    return out;
}


int main()
{

}


// template<>
// class BoolVec<bool>
// {

// }