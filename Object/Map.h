#pragma once
class Map
{
public:
	Map();
	virtual ~Map();

	virtual void Init();
	virtual void End();

	virtual void Update();
	virtual void Draw(int x);
private:

	int m_hMap;
};

