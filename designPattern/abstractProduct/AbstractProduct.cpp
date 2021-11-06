// 抽象工厂模式
#include <string>
#include <iostream>

// 工厂家族中每一个独立的工厂都要有一个基接口。不同的工厂必须实线这个接口。
class AbstractProductA
{
public:
	virtual ~AbstractProductA(){};
	virtual std::string UsefulFunctionA() const = 0;
};

// 具体的产品是由相关具体的工厂创造的
class ConcreteProductA1 : public AbstractProductA
{
public:
	std::string UsefulFunctionA() const override
	{
		return "The result of the product A1.";
	}
};

class ConcreteProductA2 : public AbstractProductA
{
public:
	std::string UsefulFunctionA() const override
	{
		return "The result of the product A2.";
	}
};

// 这里是另一个产品的基础接口，所有产品都可以彼此互动，但是一些特定的互动，只有来自同一具体的变种之间才能完成。
class AbstractProductB
{
	// 产品B可以做一些自己的事情
public:
	virtual ~AbstractProductB(){};
	virtual std::string UsefulFunctionB() const = 0;

	// 产品B也可以与产品A有一些协作
	// 这个抽象工厂确定它创造的所有产品都是同一个变种，也就是，是兼容的。
	virtual std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const = 0;
};

// 一个由特定的工厂制造的产品
class ConcreteProductB1 : public AbstractProductB
{
public:
	std::string UsefulFunctionB() const override
	{
		return "The result of the product B1.";
	}
	// 这里的变体，产品B1，只能与产品A进行正确的工作。然而，它接收任何产品A的实例作为参数。
	std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const override
	{
		const std::string result = collaborator.UsefulFunctionA();
		return "The result of the B1 collaborating with ( " + result + " )";
	}
};

class ConcreteProductB2 : public AbstractProductB
{
public:
	std::string UsefulFunctionB() const override
	{
		return "The result of product B2.";
	}

	// 这里的变体，产品B2，只能与产品A进行正确的工作。然而，它接收任何产品A的实例作为参数。
	std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const override
	{
		const std::string result = collaborator.UsefulFunctionA();
		return "The result of the B2 collaborating with ( " + result + " )";
	}
};

// 抽象工厂接口
class AbstractFactory
{
public:
	virtual AbstractProductA *CreateProductA() const = 0;
	virtual AbstractProductB *CreateProductB() const = 0;
};

// 具体工厂1，只生产产品A1和B1
class ConcreteFactory1 : public AbstractFactory
{
public:
	AbstractProductA *CreateProductA() const override
	{
		return new ConcreteProductA1();
	}
	AbstractProductB *CreateProductB() const override
	{
		return new ConcreteProductB1();
	}
};

// 具体工厂2，只生产产品A2和B2
class ConcreteFactory2 : public AbstractFactory
{
public:
	AbstractProductA *CreateProductA() const override
	{
		return new ConcreteProductA2();
	}
	AbstractProductB *CreateProductB() const override
	{
		return new ConcreteProductB2();
	}
};

// 传入工厂，生产该工厂能生产的产品A和B，并进行对应产品可以进行的操作（function）
void ClientCode(const AbstractFactory &factory)
{
	const AbstractProductA *product_a = factory.CreateProductA();
	const AbstractProductB *product_b = factory.CreateProductB();
	std::cout << product_b->UsefulFunctionB() << "\n";
	std::cout << product_b->AnotherUsefulFunctionB(*product_a) << "\n";
	delete product_a;
	delete product_b;
}

int main()
{
	std::cout << "Client: Testing client code with the first factory type:\n";
	ConcreteFactory1 *f1 = new ConcreteFactory1();
	ClientCode(*f1);
	delete f1;
	std::cout << std::endl;
	std::cout << "Client: Testing the same client code with the second factory type:\n";
	ConcreteFactory2 *f2 = new ConcreteFactory2();
	ClientCode(*f2);
	delete f2;
	return 0;
}
