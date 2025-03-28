#include <iostream>
using namespace std;

class MyVec
{
    int* m_arr;
    size_t m_size;
    size_t m_cap;

    public:
        // создание вектора:
        MyVec()
        {
            m_size = 0;
            m_cap = 0;
            m_arr = nullptr;
        }
        MyVec(size_t size, int value)
        {
            m_arr = new int[size];
            m_cap = size;
            m_size = size;
        }
        ~MyVec()
        {
            if(m_arr != nullptr)
            {
                delete[] m_arr;
            }
        }

        void push_back(int value) //добавление элемента в конец вектора
        {
            if(m_size + 1 <= m_cap)
            {
                m_arr[m_size] = value;
                m_size++;
                return;
            }

            m_cap = m_cap*2 + 1;
            int* tmp = new int[m_cap];

            for(int i=0;i<m_size;i++)
            {
                tmp[i] = m_arr[i];
            }

            tmp[m_size] = value;
            delete[] m_arr;
            m_arr = tmp;
            m_size++;
        }

        size_t size()
        {
            return m_size;
        }

        size_t capacity()
        {
            return m_cap;
        }

        void reserve(size_t cap)
        {
            if(m_size >= cap)
            {
                return;
            }
            m_cap = cap;
            int* temp = new int[m_cap];
            for(int i=0;i<m_size;i++)
            {
                temp[i] = m_arr[i];
            }
            delete[] m_arr;
            m_arr = temp;
        }

        void stf() //операция shrink to fit
        {
            m_cap = m_size;
            int* tmp = new int[m_cap];
            for(int i=0;i<m_size;i++)
            {
                tmp[i] = m_arr[i];
            }
            delete[] m_arr;
            m_arr = tmp;
        }
        int& operator[](size_t index)
        {
            return m_arr[index];
        }
        int& back()
        {
            return m_arr[m_size - 1];
        }
        int& front()
        {
            return m_arr[0];
        }
        bool empty()
        {
            if(m_arr!=nullptr)
            {
                return false;
            }
            return true;
        }
        MyVec(const MyVec&) = delete;

        void resize(size_t n_size)
        {

            if(m_size == n_size)
            {
                return;
            }
            else if(m_size > n_size)
            {
                int* tmp = new int[n_size];
                
                for(int i=0;i<n_size;i++)
                {
                    tmp[i] = m_arr[i];
                }

                delete[] m_arr;
                m_arr = tmp;
            }

            m_size = n_size;
            reserve(m_size);
        }

        void insert(int index,int value)
        {
            int size = m_size+1;
            int* tmp = new int[size];
                for(int i=0;i<index;i++)
                {
                    tmp[i] = m_arr[i];
                }

                tmp[index] = value;

                for(int i=index+1;i<m_size+1;i++)
                {
                    tmp[i] = m_arr[i-1];
                }

                delete[] m_arr;
                m_arr = tmp;
                m_size+=1;
        }

        void erase(int index)
        {       
            int size = m_size-1;
            int* tmp = new int[size];

            for(int i=0;i<index;i++)
            {
                tmp[i] = m_arr[i];
            }

            for(int i=index;i<size;i++)
            {
                tmp[i] = m_arr[i+1];
            }

            delete[] m_arr;
            m_arr = tmp;
            m_size-=1;
        }
};

int main()
{
    MyVec mas(5,0);

    for(int i = 0; i<mas.size();i++)
    {
        mas[i]=i+1;
    }

    cout << mas.size()<<endl;
    mas.erase(1);
    cout << mas.size()<<endl;

    for(int i = 0; i<mas.size();i++)
    {
        cout << mas[i] << endl;
    }

}
