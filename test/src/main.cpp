#include <xtl/function.h>
#include <xtl/memory/allocator.h>
#include <xtl/math/angle.h>
#include <xtl/strong_type.h>
#include <xtl/meta/operators.h>
#include <xtl/tagged_union.h>

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




int main()
{
	using UGameObject = xtl::tagged_union<Type, GameObject, Enemy>;

	constexpr size_t count = 25;
	UGameObject objects[count];
	

	for (int i = 0; i < count; i++)
	{
		objects[i].emplace<Enemy>(Type::Enemy, 20);
	}

	for (int i = 0; i < count; i++)
	{
		auto& obj = objects[i].as<GameObject>();
		obj.update(obj, 1.f);
	}

	return 0;
}