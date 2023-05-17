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

/*      简单工厂模式和策略模式的对比

简单工厂模式：
    将对象的选择创建交给了简单工厂类，客户端只需要输入相应的条件就可以，
    不用负责对象的创建，但是需要客户端自己调用算法类的方法。但是一旦需要增加新的运算类，
    比如开根运算，就要去修改简单工厂类。

策略模式：
    对象的选择创建仍需要自己来做，但是将调用方法的职责交给了Context类。
    一旦需要增加新的策略需要修改客户端。

因此，简单工厂模式的缺点就是当有新的需求增加时，需要频繁的修改工厂类。
只用策略模式，当有新的需求增加时需要修改的是客户端，客户端仍然承担着创建对象的职责，并没有减轻客户端的压力。
而将这两种模式结合起来使用，则需要修改 Context 类，总之不是完美的。
*/