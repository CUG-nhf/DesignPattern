#include <iostream>

using namespace std;

/* 策略模式定义了算法家族，分别封装起来，让他们之间可以互相替换。
   此模式让算法的变化，不会影响到使用算法的客户
*/

// 实例 商场收银系统

// Stategy类，定义了所有支持的算法的公共接口
// 现金收费抽象类
class CashSuper
{
public:
    virtual double AcceptCash(double money) = 0;
};

//ConcreteStrategy类，封装了具体的算法或行为，继承于Strategy
// 正常收费子类
class CashNormal:public CashSuper
{
public:
    double AcceptCash(double money)
    {
        return money;
    }
};

// 打折收费子类
class CashRebate:public CashSuper
{
public:
    CashRebate(double R):moneyRebate(R) {}

    double AcceptCash(double money)
    {
        return money * moneyRebate;
    }
private:
    double moneyRebate = 1.0;   // 折扣
};

//满减收费子类
class CashReturn:public CashSuper
{
public:
    CashReturn(double a, double b):moneyCondition(a), moneyReturn(b){}

    double AcceptCash(double money)
    {
        return money - (int)(money / moneyCondition) * moneyReturn;
    }
private : 
    double moneyCondition = 0.0;
    double moneyReturn = 0.0;
};

//Context类，用一个ConreteStrategy来配置，维护一个对Strategy对象的引用
class CashContext
{
public:
    CashContext(CashSuper& csuper):cs(csuper){}

    double GetResult(double money)
    {
        return cs.AcceptCash(money);
    }

private:
    CashSuper& cs;
};

int main()
{
    CashNormal cN;  // 正常收费
    CashRebate cR(0.9); // 九折收费
    CashReturn cr(100, 20);

    double x = 300;
    cout << CashContext(cN).GetResult(x) << endl;
    cout << CashContext(cR).GetResult(x) << endl;
    cout << CashContext(cr).GetResult(x) << endl;

    return 0;
}