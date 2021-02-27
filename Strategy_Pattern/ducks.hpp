#pragma once

#include <stdexcept>
#include <utility>
#include <memory>

/* FLY BEHAVIOUR INTERFACE */

class FlyBehaviour
{
public:
	FlyBehaviour() {}

	virtual void fly(char **field,
						int size,
						std::pair<int, int> &cur_pos) const = 0;
};

class SimpleFly : public FlyBehaviour
{
public:
	SimpleFly() {}

	void fly(char **field,
						int size,
						std::pair<int, int> &cur_pos) const
	{
		int shift = 5;
		if (cur_pos.first + shift >= size)
			shift = size - 1 - cur_pos.first;

		if (shift == 0)
			return;

		if (field[cur_pos.first + shift][cur_pos.second] != ' ')
			throw std::runtime_error("Place in the air is busy!");

		std::swap(field[cur_pos.first + shift][cur_pos.second],
				field[cur_pos.first][cur_pos.second]);
		cur_pos.first += shift;
	}
};

class NoFly : public FlyBehaviour
{
public:
	NoFly() {}

	void fly(char **field,
						int size,
						std::pair<int, int> &cur_pos) const
	{
		(void)field; (void)size; (void)cur_pos;
		throw std::runtime_error("This duck can't fly!");
	}
};


/* DUCKS */
#include <iostream>
class Duck
{
protected:
	int field_size;
	char **field;
	std::pair<int, int> position;
	std::unique_ptr<FlyBehaviour> fly_behaviour;

public:
	Duck (char **field_, int size, const std::pair<int, int> &pos, char c)
	{
		if (!field_ || !field_[pos.first])
			throw std::runtime_error("Wrong field (nullptr)!");
		if (pos.first < 0 || pos.first >= size)
			throw std::runtime_error("Position.x is out of map!");
		if (pos.second < 0 || pos.second >= size)
			throw std::runtime_error("Position.x is out of map!");
		if (field_[pos.first][pos.second] != ' ')
			throw std::runtime_error("Position is busy!");

		field = field_;
		field_size = size;
		position = pos;
		field[pos.first][pos.second] = c;
	}

	Duck (char **field_, int field_size, const std::pair<int, int> &pos)
		: Duck(field_, field_size, pos, 'D')
	{
		fly_behaviour = std::unique_ptr<FlyBehaviour>(new SimpleFly());
	}

	void fly()
	{
		fly_behaviour->fly(field, field_size, position);
	}

	void swim (int x)
	{
		if (x < 0 || x >= field_size)
			throw std::runtime_error("Index out of range");
		if (field[position.first][x] != ' ')
			throw std::runtime_error("Position is busy!");
		std::swap(field[position.first][position.second],
						field[position.first][x]);
		position.second = x;
	}

	void set_fly_behaviour(bool mode)
	{
		if (mode == true)
			fly_behaviour = std::unique_ptr<FlyBehaviour>(new SimpleFly());
		else
			fly_behaviour = std::unique_ptr<FlyBehaviour>(new NoFly());
	}
};

/* other ducks */

class RedDuck : public Duck
{
public:
	RedDuck(char **field, int field_size, const std::pair<int, int> &pos)
		: Duck(field, field_size, pos, 'R')
	{
		fly_behaviour = std::unique_ptr<FlyBehaviour>(new SimpleFly());
	}
};

class GreenDuck : public Duck
{
public:
	GreenDuck(char **field, int field_size, const std::pair<int, int> &pos)
		: Duck(field, field_size, pos, 'G')
	{
		fly_behaviour = std::unique_ptr<FlyBehaviour>(new SimpleFly());
	}
};

class RubberDuck : public Duck
{
public:
	RubberDuck(char **field, int field_size, const std::pair<int, int> &pos)
		: Duck(field, field_size, pos, 'r')
	{
		fly_behaviour = std::unique_ptr<FlyBehaviour>(new NoFly());
	}
};
