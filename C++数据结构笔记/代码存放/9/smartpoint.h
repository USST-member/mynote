#ifndef SMARTPOINT_H
#define SMARTPOINT_H
namespace dong
{

template<typename T>
class Smartpoint
{
protected:
    T* m_p;
public:
    Smartpoint(T* p=nullptr)
    {
        m_p=p;
    }
    Smartpoint(const Smartpoint<T>& obj)
    {
        m_p=obj.m_p;
        const_cast<Smartpoint<T>&>(obj).m_p==nullptr;
    }
    Smartpoint<T>& operator =(const Smartpoint<T>& obj)
    {
        if(this!=&obj)
        {
            delete m_p;
            m_p=obj.m_p;
            const_cast<Smartpoint<T>&>(obj).m_p=nullptr;
        }
        return *this;
    }
    T* operator->()
    {
        return m_p;
    }
    T& operator*()
    {
        return *m_p;
    }
    bool isNULL()
    {
        return (m_p == nullptr);
    }
    T* get()
    {
        return m_p;
    }
    ~Smartpoint()
    {
        delete m_p;
    }
};

}

#endif // SMARTPOINT_H
