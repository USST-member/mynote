#ifndef EXCEPTIOM_H
#define EXCEPTIOM_H

namespace dong {

//抛出异常宏函数
#define THROW_EXCEPTION(e,m) (throw e(m,__FILE,__LINE__))//抛出异常

//父类 抽象层
class Exception
{
protected:
    char *m_message;
    char *m_location;

    void init(const char *message,const char *file,int line);//相当于二级构造

public:
    Exception(const char * message);
    Exception(const char * file,int line);
    Exception(const char * message,const char * file,int line);

    Exception(const Exception& e);
    Exception& operator =(const Exception& e);

    virtual const char *message() const;
    virtual const char *location() const;
    virtual ~Exception()=0;
};

//子类 计算异常
class ArithmeticException : public Exception
{
public:
    ArithmeticException():Exception(nullptr){}
    ArithmeticException(const char * message):Exception(message){}
    ArithmeticException(const char * file,int line):Exception(file ,line){}
    ArithmeticException(const char * message,const char * file,int line):Exception(message,file ,line){}


    ArithmeticException(const ArithmeticException& e):Exception(e){}
    ArithmeticException& operator=(const ArithmeticException& e)
    {
        Exception::operator=(e);
        return *this;
    }
};

//子类 空指针异常
class NullPointerException : public Exception
{
public:
    NullPointerException():Exception(nullptr){}
    NullPointerException(const char * message):Exception(message){}
    NullPointerException(const char * file,int line):Exception(file ,line){}
    NullPointerException(const char * message,const char * file,int line):Exception(message,file ,line){}


    NullPointerException(const NullPointerException& e):Exception(e){}
    NullPointerException& operator=(const NullPointerException& e)
    {
        Exception::operator=(e);
        return *this;
    }
};

//子类 越界异常
class IndexOutofBoubdsException : public Exception
{
public:
    IndexOutofBoubdsException():Exception(nullptr){}
    IndexOutofBoubdsException(const char * message):Exception(message){}
    IndexOutofBoubdsException(const char * file,int line):Exception(file ,line){}
    IndexOutofBoubdsException(const char * message,const char * file,int line):Exception(message,file ,line){}


    IndexOutofBoubdsException(const IndexOutofBoubdsException& e):Exception(e){}
    IndexOutofBoubdsException& operator=(const IndexOutofBoubdsException& e)
    {
        Exception::operator=(e);
        return *this;
    }
};

//子类 内存不足异常
class NoenoughmemoryException : public Exception
{
public:
    NoenoughmemoryException():Exception(nullptr){}
    NoenoughmemoryException(const char * message):Exception(message){}
    NoenoughmemoryException(const char * file,int line):Exception(file ,line){}
    NoenoughmemoryException(const char * message,const char * file,int line):Exception(message,file ,line){}


    NoenoughmemoryException(const NoenoughmemoryException& e):Exception(e){}
    NoenoughmemoryException& operator=(const NoenoughmemoryException& e)
    {
        Exception::operator=(e);
        return *this;
    }
};

//子类 参数错误异常
class InvalidparameterException : public Exception
{
public:
    InvalidparameterException():Exception(nullptr){}
    InvalidparameterException(const char * message):Exception(message){}
    InvalidparameterException(const char * file,int line):Exception(file ,line){}
    InvalidparameterException(const char * message,const char * file,int line):Exception(message,file ,line){}


    InvalidparameterException(const InvalidparameterException& e):Exception(e){}
    InvalidparameterException& operator=(const InvalidparameterException& e)
    {
        Exception::operator=(e);
        return *this;
    }
};

}


#endif // EXCEPTIOM_H
