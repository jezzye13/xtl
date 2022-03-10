#include <xtl/function.h>
#include <xtl/memory/allocator.h>
#include <xtl/math/angle.h>
#include <xtl/strong_type.h>
#include <xtl/meta/operators.h>
#include <xtl/string.h>
#include <xtl/tagged_union.h>
#include <xtl/sparse_set.h>
#include <iostream>



enum class Type
{
	GameObject,
	Enemy
};

class GameObject;
using UpdateFn = void(*)(GameObject&, float);
class GameObject
{
protected:
	Type m_type;
	char m_name[25];

public:
	UpdateFn update;


};


class Enemy :
	public GameObject
{
	static void UpdateEnemy(GameObject& obj, float dt)
	{
		Enemy& enemy = static_cast<Enemy&>(obj);
		printf("Enemy did %d damage.\n", enemy.m_damage);
	}


	int m_damage;
public:

	Enemy(int damage) :
		m_damage(damage)
	{
		m_damage = damage;
		update = &UpdateEnemy;
	}
};



struct Example
{
	using Allocator = xtl::linear_allocator<xtl::auto_allocator<100, alignof(char)>>;
	Allocator allocator;
	xtl::string<Allocator> str1;
	xtl::string<Allocator> str2;

	Example() :
		str1(&allocator),
		str2(&allocator)
	{
		allocator.reserve(100, alignof(char));
		//same buffer, one after the other
		str1.reserve(50);
		str2.reserve(50);
		str1.assign("Bruh1");
		str2.assign("Bruh2");
		printf("%s\n", str2.c_str());
	}
};



int main()
{
	using UGameObject = xtl::tagged_union<Type, GameObject, Enemy>;
	using Allocator = xtl::auto_allocator<10 * sizeof(UGameObject), alignof(UGameObject)>;
	Allocator alloc;
	constexpr size_t count = 25;
	UGameObject objects[count];
	//xtl::packed_array<UGameObject, Allocator> reg(&alloc);


	for (int i = 0; i < count; i++)
	{
		objects[i].emplace<Enemy>(Type::Enemy, 20);
	}

	for (int i = 0; i < count; i++)
	{
		auto& obj = objects[i].as<GameObject>();
		obj.update(obj, 1.f);
	}

	Example ex;

	return 0;
}