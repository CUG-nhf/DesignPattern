#include <iostream>

using namespace std;

// 简单工厂模型

// 实例，实现一个计算器

// 运算基类
template <typename Type>
class Operation
{
public:
    Type m_NumberA;
    Type m_NumberB;

    Operation() = default;
    Operation(Type a, Type b):m_NumberA(a), m_NumberB(b) {}

    virtual Type DoGetResult()
    {
        Type result;
        return result;
    }
};

// 加法类
template <typename Type>
class OperationAdd:public Operation<Type>
{
public:
    Type DoGetResult()
    {
        return this->m_NumberA + this->m_NumberB;
    }
};

// 减法类
template <typename Type>
class OperationSub:public Operation<Type>
{
public:
    Type DoGetResult()
    {
        return this->m_NumberA - this->m_NumberB;
    }
};

// 乘法类
template <typename Type>
class OperationMul:public Operation<Type>
{
public:
    Type DoGetResult()
    {
        return this->m_NumberA * this->m_NumberB;
    }
};

// 除法类
template <typename Type>
class OperationDiv:public Operation<Type>
{
public:
    Type DoGetResult()
    {
        if (this->m_NumberB != 0)
            return this->m_NumberA / this->m_NumberB;
        else
        {
            cout << "异常：被除数为零！" << endl;
            return 0;
        }
            
    }
};


// 简单工厂类
// 用一个单独的类来做创建实例的过程，这就是工厂
// 如果增加需求，只需要写OperationXXX，并增加工厂里的switch分支即可
template <typename Type>
class OperationFactory
{
public:
    Operation<Type>* CreatOperation(char operation)
    {
        Operation<Type>* oper = nullptr;
        switch(operation)
        {
            case '+' :
                oper = new OperationAdd<Type>();
                break;
            case '-' :
                oper = new OperationSub<Type>();
                break;
            case '*' :
                oper = new OperationMul<Type>();
                break;
            case '/':
                oper = new OperationDiv<Type>();
                break;
        }
        return oper;
    }
};

int main()
{
    Operation<int>* oper = OperationFactory<int>().CreatOperation('+');
    oper->m_NumberA = 6;
    oper->m_NumberB = 2;

    cout << oper->DoGetResult() << endl;

    return 0;
}
