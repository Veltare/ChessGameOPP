#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <Windows.h>
#include <clocale>
#include <vector>
#include <algorithm>

using namespace sf;
using namespace std;

const int quantityFigure(16);
class cellField;
class Player;
class Figure
{
protected:
	
	Image image;
	Texture texture;
	Sprite sprite;
	float distance = 0;
	vector<vector<bool>> MovementField;
	

public:
	float x, y;
	int Logic_i, Logic_j;
	cellField* CellPointer;
	bool IsSelect = false;
	bool IsMove = false;
	bool IsDelete = false;
	bool color;
	bool IsKing = false;
	Figure()
	{
		MovementField.resize(8);
		for (int i = 0; i < (int)MovementField.size(); i++)
		{
			MovementField[i].resize(8);
		}
	}
	Figure(string& path)
	{
		MovementField.resize(8);
		for (int i = 0; i < (int)MovementField.size(); i++)
		{
			MovementField[i].resize(8);
		}
		SetImage(path);
	
		SetTexture(image);
		SetSprite(texture);
	};
	Figure (float x1,float y1,int Logic_1,int Logic_2, cellField*p,bool Select,bool Move,bool color):x(x1), y(y1),Logic_i(Logic_1), Logic_j(Logic_2),CellPointer(p),IsSelect(Select),IsMove(Move),color(color)
	{

	};
	Image& GetImage()
	{
		return image;

	};

	void Transformation(Figure &arg)
	{
		this->x = arg.x;
		this->y = arg.y;
		this->Logic_i = arg.Logic_i;
		this->Logic_j = arg.Logic_j;
		this->CellPointer = arg.CellPointer;
		this->IsSelect = arg.IsSelect;
		this->IsMove = arg.IsMove;
		this->IsDelete = arg.IsDelete;
		this->color = arg.color;

	}
	void SetImage(string& path)
	{
		if (!image.loadFromFile(path))
		{
			cout << "Файл не найден" << endl;
		}
	}
	Texture& GetTexture()
	{
		return texture;
	};
	void SetTexture(Image& path)
	{
		texture.loadFromImage(path);
	}
	Sprite& GetSprite()
	{
		return sprite;
	};
	void SpriteSetPosition(float x,float y)
	{
		sprite.setPosition(x,y);
	};
	void SetSprite(Texture& texture)
	{
		sprite.setTexture(texture);
		sprite.setOrigin(image.getSize().x/2, image.getSize().y / 2);
	}
	void TextureSize()
	{
		cout << "Ширина = " << texture.getSize().x << endl;
		cout << "Высота = " << texture.getSize().y << endl;
	}
	void SpriteInit(RenderWindow &window, string& path)
	{
		
		SetImage(path);
		SetTexture(GetImage());
		SetSprite(GetTexture());
		window.draw(GetSprite());

	};
	void SpriteInit(string& path)
	{
		SetImage(path);
		SetTexture(GetImage());
		SetSprite(GetTexture());
	};
	void SetDelete(bool logic)
	{
		IsDelete = logic;
	
	}
	void DeleteFigure()
	{
			//sprite.setColor(Color::Transparent);
		
			IsSelect = NULL;
			IsMove = NULL;
			IsDelete = true;
			x = -100;
			y = -100;
			
	}
	vector<vector<bool>>& GetMovementField()
	{
		return MovementField;
	}
	virtual bool Movement(cellField*Cell, float dX, float dY, float time, int i, int j, vector<vector<cellField>> Field)
	{
		return false;
	}
	virtual void GenerateMovementField(vector<vector<cellField>> Field)
	{

	}
	virtual bool Attack(cellField*Cell, int i, int j, vector<vector<cellField>> Field, vector<Figure*> &Array)
	{
		return NULL;
	}
	virtual inline void PawnTransmogrification(int i, vector<vector<cellField>> Field, vector<Figure*> &Array)
	{
		
	}
	
};
class cellField:public Figure
{
protected:
	bool place = true;
	
public:
	Figure* Pointer_to_Figure = NULL;
	cellField() :Figure()
	{}
	cellField(string& path) :Figure(path)
	{
		
	}
	void ChangePlace(bool l)
	{
		place = l;
	}
	bool GetPlace()
	{
		return place;
	}
	
};

class GameEvent
{
protected:
	Figure background;
public:
	GameEvent(RenderWindow &window)
	{
		string buffer = "./Resource/background.png";
		background.SpriteInit(window,buffer);
	}
	Sprite GetBackground()
	{
		return background.GetSprite();
	}

};
class Pawn:public Figure
{	
protected:	
public:
	bool IsFirst = true;
	Pawn(){
		MovementField.resize(8);
		for (int i = 0; i < (int)MovementField.size(); i++)
		{
			MovementField[i].resize(8);
		}
	}
	Pawn(string& path):Figure(path)
	{

	}
	inline void GenerateMovementField(vector<vector<cellField>> Field)
	{
		for (int i = 0; i < (int)MovementField.size(); i++)
		{
			for (int j = 0; j < (int)MovementField.size(); j++)
			{
				this->MovementField[i][j] = false;
			}
		}
		if (this->color == 0)
		{
			int buff_i = this->Logic_i + 1;
			if (IsFirst)
			{
				int buff_i2 = this->Logic_i + 2;
				if (buff_i2 < (int)MovementField.size() && buff_i2 >= 0)
					if (Field[buff_i2][this->Logic_j].GetPlace() == true)
					{
						MovementField[buff_i2][this->Logic_j] = true;
						MovementField[this->Logic_i][this->Logic_j] = false;	
					}
			}

			if (buff_i < (int)MovementField.size() && buff_i >= 0)
				if (Field[buff_i][this->Logic_j].GetPlace() == true)
				{
					MovementField[buff_i][this->Logic_j] = true;
					MovementField[this->Logic_i][this->Logic_j] = false;
				}
		}
		if (this->color == 1)
		{
			int buff_i = this->Logic_i - 1;
			if (IsFirst)
			{
				int buff_i2 = this->Logic_i - 2;
				if (buff_i2 < (int)MovementField.size() && buff_i2 >= 0)
					if (Field[buff_i2][this->Logic_j].GetPlace() == true)
					{
						MovementField[buff_i2][this->Logic_j] = true;
						MovementField[this->Logic_i][this->Logic_j] = false;	
					}
			}

			if (buff_i < (int)MovementField.size() && buff_i >= 0)
				if (Field[buff_i][this->Logic_j].GetPlace() == true)
				{
					MovementField[buff_i][this->Logic_j] = true;
					MovementField[this->Logic_i][this->Logic_j] = false;
				}
		}
		for (int i = 0; i < (int)Field.size(); i++)
		{
			for (int j = 0; j < (int)Field.size(); j++)
			{
				if(Field[i][j].GetPlace() == false)
					MovementField[i][j] = false;
			}
		}	
	}
	Pawn& GetObj()
	{
		return *this;
	}
	inline bool Movement(cellField*Cell, float dX, float dY, float time, int i, int j, vector<vector<cellField>> Field)
	{
		if (this->IsFirst == true)
		{
			if (this->color == 0)
			{
				if (Field[Logic_i + 1][Logic_j].GetPlace() == false)
				{	
					return false;
				}
			}
			if (this->color == 1)
			{
				if (Field[Logic_i - 1][Logic_j].GetPlace() == false)
				{
					return false;
				}
			}
		}
		if (MovementField[i][j] == true)
		{
			
			distance = sqrt((dX - this->x)*(dX - this->x) + (dY - this->y)*(dY - this->y));
			if (distance > 2)
			{
				this->x += 0.15*time*(dX - this->x) / distance;
				this->y += 0.15*time*(dY - this->y) / distance;
			}
			else
			{
				this->CellPointer->ChangePlace(true);
				this->CellPointer->Pointer_to_Figure = NULL;
				this->IsMove = false;
				this->CellPointer = Cell;
				Cell->Pointer_to_Figure = this;
				this->CellPointer->ChangePlace(false);
				this->Logic_i = i;
				this->Logic_j = j;
				this->IsFirst = false;
				GenerateMovementField(Field);
				return false;
			}
		}
		else
		{
			GenerateMovementField(Field);
			
			return false;
		}
		return true;
	}
	inline bool Attack(cellField*Cell, int i1, int j, vector<vector<cellField>> Field, vector<Figure*> &Array)
	{
		//Черные фигуры
		if (this->color == 0)
		{
			//Общий случай
			if ((Logic_i + 1 > 0 && Logic_i + 1 < (int)Field.size()) && ((Logic_j - 1 >= 0 && Logic_j - 1 < (int)Field.size()) && (Logic_j + 1 > 0 && Logic_j + 1 < (int)Field.size())))
			{
				if ((Field[Logic_i + 1][Logic_j - 1].GetPlace() == false) || (Field[Logic_i + 1][Logic_j + 1].GetPlace() == false))
				{
					if ((i1 == Logic_i + 1 && j == Logic_j - 1) || (i1 == Logic_i + 1 && j == Logic_j + 1))
					{
						for (int i = 0; i < (int)Array.size(); i++)
						{
							if (Array[i] == Cell->Pointer_to_Figure)
							{
								if (((Array[i]->Logic_i == Logic_i + 1) && (Array[i]->Logic_j == Logic_j - 1)) || ((Array[i]->Logic_i == Logic_i + 1) && (Array[i]->Logic_j == Logic_j + 1)))
								{
									Array[i]->DeleteFigure();
									this->GetMovementField()[i1][j] = true;
									return true;
								}
							}
						}
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				//Когда нет фигур справа
				if ((Logic_i + 1 > 0 && Logic_i + 1 < (int)Field.size()) && ((Logic_j - 1 >= 0 && Logic_j - 1 < (int)Field.size())))
				{
					if (Field[Logic_i + 1][Logic_j - 1].GetPlace() == false)
					{
						if ((i1 == Logic_i + 1 && j == Logic_j - 1))
						{

							for (int i = 0; i < (int)Array.size(); i++)
							{
								if (Array[i] == Cell->Pointer_to_Figure)
								{

									if ((Array[i]->Logic_i == Logic_i + 1) && (Array[i]->Logic_j == Logic_j - 1))
									{
										Array[i]->DeleteFigure();
								    	this->GetMovementField()[i1][j] = true;
										return true;
									}
								}
							}
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				else
				{
					//Когда нет фигур слева
					if ((Logic_i + 1 > 0 && Logic_i + 1 < (int)Field.size()) && (Logic_j + 1 > 0 && Logic_j + 1 < (int)Field.size()))
					{
						if (Field[Logic_i + 1][Logic_j + 1].GetPlace() == false)
						{
							if ((i1 == Logic_i + 1 && j == Logic_j + 1))
							{

								for (int i = 0; i < (int)Array.size(); i++)
								{
									if (Array[i] == Cell->Pointer_to_Figure)
									{

										if ((Array[i]->Logic_i == Logic_i + 1) && (Array[i]->Logic_j == Logic_j + 1))
										{
											Array[i]->DeleteFigure();
											this->GetMovementField()[i1][j] = true;
											return true;
										}
									}
								}

							}
							else
							{
								return false;
							}
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				return false;
			}
		}
		//Белые фигуры
		if (this->color == 1)
		{
			//Общий случай
			if ((Logic_i - 1 >= 0 && Logic_i - 1 < (int)Field.size()) && ((Logic_j - 1 >= 0 && Logic_j - 1 < (int)Field.size()) && (Logic_j + 1 > 0 && Logic_j + 1 < (int)Field.size())))
			{
				if ((Field[Logic_i - 1][Logic_j - 1].GetPlace() == false) || (Field[Logic_i - 1][Logic_j + 1].GetPlace() == false))
				{
					if ((i1 == Logic_i - 1 && j == Logic_j - 1) || (i1 == Logic_i - 1 && j == Logic_j + 1))
					{
						for (int i = 0; i < (int)Array.size(); i++)
						{
							if (Array[i] == Cell->Pointer_to_Figure)
							{
								if (((Array[i]->Logic_i == Logic_i - 1) && (Array[i]->Logic_j == Logic_j - 1)) || ((Array[i]->Logic_i == Logic_i - 1) && (Array[i]->Logic_j == Logic_j + 1)))
								{
									Array[i]->DeleteFigure();
									this->GetMovementField()[i1][j] = true;
									return true;
								}
							}
						}
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				//Когда нет фигур справа
				if ((Logic_i - 1 >= 0 && Logic_i - 1 < (int)Field.size()) && ((Logic_j - 1 >= 0 && Logic_j - 1 < (int)Field.size())))
				{
					if (Field[Logic_i - 1][Logic_j - 1].GetPlace() == false)
					{
						if ((i1 == Logic_i - 1 && j == Logic_j - 1))
						{

							for (int i = 0; i < (int)Array.size(); i++)
							{
									
								if (Array[i] == Cell->Pointer_to_Figure)
								{

									if ((Array[i]->Logic_i == Logic_i - 1) && (Array[i]->Logic_j == Logic_j - 1))
									{
										Array[i]->DeleteFigure();
										this->GetMovementField()[i1][j] = true;
										return true;
									}
								}
							}
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				else
				{
					//Когда нет фигур слева
					if ((Logic_i - 1 >= 0 && Logic_i - 1 < (int)Field.size()) && (Logic_j + 1 > 0 && Logic_j + 1 < (int)Field.size()))
					{
						if (Field[Logic_i - 1][Logic_j + 1].GetPlace() == false)
						{
							if ((i1 == Logic_i - 1 && j == Logic_j + 1))
							{
								for (int i = 0; i < (int)Array.size(); i++)
								{
									if (Array[i] == Cell->Pointer_to_Figure)
									{
										if ((Array[i]->Logic_i == Logic_i - 1) && (Array[i]->Logic_j == Logic_j + 1))
										{
											Array[i]->DeleteFigure();
											this->GetMovementField()[i1][j] = true;
											return true;
										}
									}
								}
							}
							else
							{

								return false;
							}
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				return false;
			}
		}
		return false;
	}
	inline void PawnTransmogrification(int i, vector<vector<cellField>> Field, vector<Figure*> &Array)
	{
		
		if(i==0 || i == (int)Field.size()-1)
		{
			
			for (int i = 0; i < 4; i++)
			{
				
				if (i == 2)
				{
					if (Array[0]->IsDelete == true)
					{
						Array[0]->Transformation(*this);
						break;
					}
					if (Array[7]->IsDelete == true)
					{
						Array[7]->Transformation(*this);
						break;
					}
				}
				else if (i == 3)
				{
					if (Array[1]->IsDelete == true)
					{
						Array[1]->Transformation(*this);
						break;
					}
					if (Array[6]->IsDelete == true)
					{
						Array[6]->Transformation(*this);
						break;
					}
				}
				else if (i == 1)//Ладья
				{
					
					if (Array[2]->IsDelete == true)
					{
						Array[2]->Transformation(*this);
						break;
					}
					if (Array[5]->IsDelete == true)
					{
						Array[5]->Transformation(*this);
						break;
					}
					
				}
				else if (i == 0)//Ферзь
				{
					//3
					if(this->color == 0)
						if (Array[4]->IsDelete == true)
						{
						Array[4]->Transformation(*this);
						break;
						}
					if(this->color == 1)
						if (Array[3]->IsDelete == true)
						{
							Array[3]->Transformation(*this);
							break;
						}
				}

			}
			this->DeleteFigure();
		}
	}

};
class Elephant :public Figure
{
	enum Color { Black, White };
protected:
	Color Side;
public:
	Elephant(string& path) :Figure(path)
	{
		
	}
	Elephant() :Figure()
	{
		
	}
	Elephant(float x1, float y1, int Logic_1, int Logic_2, cellField*p, bool Select, bool Move, bool color) :Figure(x1,y1,Logic_1,Logic_2,p,Select,Move,color)
	{

	}
	inline bool Movement(cellField*Cell, float dX, float dY, float time, int i, int j, vector<vector<cellField>> Field)
	{
		if (MovementField[i][j] == true)
		{
			distance = sqrt((dX - this->x)*(dX - this->x) + (dY - this->y)*(dY - this->y));
			if (distance > 2)
			{

				this->x += 0.15*time*(dX - this->x) / distance;
				this->y += 0.15*time*(dY - this->y) / distance;
			}
			else
			{
				this->CellPointer->ChangePlace(true);
				this->CellPointer->Pointer_to_Figure = NULL;
				this->IsMove = false;
				this->CellPointer = Cell;
				Cell->Pointer_to_Figure = this;
				this->CellPointer->ChangePlace(false);
				this->Logic_i = i;
				this->Logic_j = j;
				GenerateMovementField(Field);
				return false;
			}
		}
		else
		{
			GenerateMovementField(Field);
			return false;
		}
		return true;
	}
	inline void GenerateMovementField(vector<vector<cellField>> Field)

	{
		
		for (int i = 0; i < (int)MovementField.size(); i++)
		{
			for (int j = 0; j < (int)MovementField.size(); j++)
			{
				this->MovementField[i][j] = false;

			}
		}
		int m = 0;
		int k = 0;
		int buffi = this->Logic_i;
		int buffj = this->Logic_j;
		for (int i = 0; i < 4; i++)
		{
			switch (i)
			{
			case 0:
			{
				m = 1;
				k = 1;
				break;
			}
			case 1:
			{
				m = -1;
				k = 1;
				break;
			}
			case 2:
			{
				m = 1;
				k = -1;
				break;
			}
			case 3:
			{
				m = -1;
				k = -1;
				break;
			}
			default:
				break;
			}
			for(int h=0;h<(int)MovementField.size();h++)
			{ 
				if (buffi + m < (int)MovementField.size() && buffi + m >= 0 && buffj + k < (int)MovementField.size() && buffj + k >= 0)
				{	
					if (Field[buffi + m][buffj + k].GetPlace() == true)
					{
						MovementField[buffi + m][buffj + k] = true;
					}
					else
					{
						continue;
					}
				}
			buffi += m;
			buffj += k;
			}
			buffi = this->Logic_i;
			buffj = this->Logic_j;
		}

		for (int i = 0; i < (int)Field.size(); i++)
		{
			for (int j = 0; j < (int)Field.size(); j++)
			{
				if (Field[i][j].GetPlace() == false)
					MovementField[i][j] = false;

			}
		}
		
		

	}
	inline bool Attack(cellField*Cell, int i1, int j1, vector<vector<cellField>> Field, vector<Figure*> &Array)
	{
		int m(0), k(0);
		int buffi = this->Logic_i;
		int buffj = this->Logic_j;
		if (Field[i1][j1].GetPlace() == false)
		{

			for (int i = 0; i < (int)Array.size(); i++)
			{
				if (Array[i] == Cell->Pointer_to_Figure)
				{
					if (this->color == Cell->Pointer_to_Figure->color)
					{
						return false;
					}
					else
						for (int p = 0; p < 4; p++)
						{
							switch (p)
							{
							case 0:
							{
								m = 1;
								k = 1;
								break;
							}
							case 1:
							{
								m = -1;
								k = 1;
								break;
							}
							case 2:
							{
								m = 1;
								k = -1;
								break;
							}
							case 3:
							{
								m = -1;
								k = -1;
								break;
							}
							default:
								break;
							}
							for (int h = 0; h<(int)MovementField.size(); h++)
							{

								if (buffi + m < (int)MovementField.size() && buffi + m >= 0 && buffj + k < (int)MovementField.size() && buffj + k >= 0)
								{
									if (Field[buffi + m][buffj + k].GetPlace() == false)
									{
										if (i1 == buffi + m && j1 == buffj + k)
										{
											Array[i]->DeleteFigure();
											return true;
										}
										else break;
									}			
								}
								buffi += m;
								buffj += k;
							}
							buffi = this->Logic_i;
							buffj = this->Logic_j;
						}


						}
				}

			}
		else return false;
		return false;
		}	
};
class Knight :public Figure
{
	enum Color { Black, White };
protected:

	static int id;
	Color Side;
public:
	Knight(string& path) :Figure(path)
	{
		
	}
	Knight(float x1, float y1, int Logic_1, int Logic_2, cellField*p, bool Select, bool Move, bool color) :Figure(x1, y1, Logic_1, Logic_2, p, Select, Move, color)
	{

	}
	inline void GenerateMovementField(vector<vector<cellField>> Field)
	{
		
		for (int i = 0; i < (int)MovementField.size(); i++)
		{
			for (int j = 0; j < (int)MovementField.size(); j++)
			{
				this->MovementField[i][j] = false;

			}
		}
		int m = 0;
		int k = 0;
		for (int i = 0; i < (int)MovementField.size(); i++)
		{
			switch (i)
			{
			case 0:
			{
				m = -2;
				k = 1;
				break;
			}
			case 1:
			{
				m = 2;
				k = 1;
				break;
			}
			case 2:
			{
				m = 2;
				k = -1;
				break;
			}
			case 3:
			{
				m = -2;
				k = -1;
				break;
			}
			case 4:
			{
				m = -1;
				k = 2;
				break;
			}
			case 5:
			{
				m = 1;
				k = 2;
				break;
			}
			case 6:
			{
				m = 1;
				k = -2;
				break;
			}
			case 7:
			{
				m = -1;
				k = -2;
				break;
			}
			default:
				break;
			}
			if (this->Logic_i + m < (int)MovementField.size() && this->Logic_i + m >= 0 && this->Logic_j + k < (int)MovementField.size() && this->Logic_j + k >= 0)
				if (Field[this->Logic_i + m][this->Logic_j + k].GetPlace() == true)
				{
					MovementField[this->Logic_i + m][this->Logic_j + k] = true;
					MovementField[this->Logic_i][this->Logic_j] = false;
					
				}
		}

		for (int i = 0; i < (int)Field.size(); i++)
		{
			for (int j = 0; j < (int)Field.size(); j++)
			{
				if (Field[i][j].GetPlace() == false)
					MovementField[i][j] = false;

			}
		}
		
		
	}
	inline bool Attack(cellField*Cell, int i1, int j1, vector<vector<cellField>> Field, vector<Figure*> &Array)
	{
		int m(0), k(0);
		if (Field[i1][j1].GetPlace() == false) 
		{
			
				for (int i = 0; i < (int)Array.size(); i++)
				{
					if (Array[i] == Cell->Pointer_to_Figure)
					{
						if (this->color == Cell->Pointer_to_Figure->color)
						{
							return false;
						}
						else
							for (int j = 0; j < (int)MovementField.size(); j++)
							{
								switch (j)
								{
								case 0:
								{
									m = -2;
									k = 1;
									break;
								}
								case 1:
								{
									m = 2;
									k = 1;
									break;
								}
								case 2:
								{
									m = 2;
									k = -1;
									break;
								}
								case 3:
								{
									m = -2;
									k = -1;
									break;
								}
								case 4:
								{
									m = -1;
									k = 2;
									break;
								}
								case 5:
								{
									m = 1;
									k = 2;
									break;
								}
								case 6:
								{
									m = 1;
									k = -2;
									break;
								}
								case 7:
								{
									m = -1;
									k = -2;
									break;
								}
								default:
									break;
								}
								if (i1 == this->Logic_i + m && j1 == this->Logic_j + k)
								{
									Array[i]->DeleteFigure();
									return true;
								}
							}
						
							
						
					}
				
			}
			
		}
		else return false;

		return false;
	}
	inline bool Movement(cellField*Cell, float dX, float dY, float time, int i, int j, vector<vector<cellField>> Field)
	{
		if (MovementField[i][j] == true)
		{
			distance = sqrt((dX - this->x)*(dX - this->x) + (dY - this->y)*(dY - this->y));
			if (distance > 2)
			{
				this->x += 0.15*time*(dX - this->x) / distance;
				this->y += 0.15*time*(dY - this->y) / distance;
			}
			else
			{
				this->CellPointer->ChangePlace(true);
				this->CellPointer->Pointer_to_Figure = NULL;
				this->IsMove = false;
				this->CellPointer = Cell;
				Cell->Pointer_to_Figure = this;
				this->CellPointer->ChangePlace(false);
				this->Logic_i = i;
				this->Logic_j = j;
				GenerateMovementField(Field);
				return false;
			}
		}
		else
		{
			GenerateMovementField(Field);
			return false;
		}
		return true;
	}
};
	
class Rooks :public Figure
{
	enum Color { Black, White };
protected:
	static int id;
	Color Side;
public:
	Rooks(string& path) :Figure(path)
	{
		
	}
	Rooks(float x1, float y1, int Logic_1, int Logic_2, cellField*p, bool Select, bool Move, bool color) :Figure(x1, y1, Logic_1, Logic_2, p, Select, Move, color)
	{

	}
	inline void GenerateMovementField(vector<vector<cellField>> Field)
	{
		
		for (int i = 0; i < (int)MovementField.size(); i++)
		{
			for (int j = 0; j < (int)MovementField.size(); j++)
			{
				this->MovementField[i][j] = false;
			}
		}
		int m = 0;
		int k = 0;
		int buffi = this->Logic_i;
		int buffj = this->Logic_j;
		for (int i = 0; i < 4; i++)
		{
			switch (i)
			{
			case 0:
			{
				m = 1;
				k = 0;
				break;
			}
			case 1:
			{
				m = -1;
				k = 0;
				break;
			}
			case 2:
			{
				m = 0;
				k = -1;
				break;
			}
			case 3:
			{
				m = 0;
				k = 1;
				break;
			}
			default:
				break;
			}
			for (int h = 0; h<(int)MovementField.size(); h++)
			{
				if (buffi + m < (int)MovementField.size() && buffi + m >= 0 && buffj + k < (int)MovementField.size() && buffj + k >= 0)
				{

					if (Field[buffi + m][buffj + k].GetPlace() == true)
					{
						MovementField[buffi + m][buffj + k] = true;
					}
					else
					{
						break;
					}
				}
				buffi += m;
				buffj += k;
			}
			buffi = this->Logic_i;
			buffj = this->Logic_j;
		}

		for (int i = 0; i < (int)Field.size(); i++)
		{
			for (int j = 0; j < (int)Field.size(); j++)
			{
				if (Field[i][j].GetPlace() == false)
					MovementField[i][j] = false;

			}
		}
		

	}
	inline bool Movement(cellField*Cell, float dX, float dY, float time, int i, int j, vector<vector<cellField>> Field)
	{

		if (MovementField[i][j] == true)
		{



			distance = sqrt((dX - this->x)*(dX - this->x) + (dY - this->y)*(dY - this->y));
			if (distance > 2)
			{

				this->x += 0.15*time*(dX - this->x) / distance;
				this->y += 0.15*time*(dY - this->y) / distance;

			}
			else
			{


				this->CellPointer->ChangePlace(true);
				this->CellPointer->Pointer_to_Figure = NULL;
				this->IsMove = false;
				this->CellPointer = Cell;
				Cell->Pointer_to_Figure = this;
				this->CellPointer->ChangePlace(false);
				this->Logic_i = i;
				this->Logic_j = j;

				GenerateMovementField(Field);

				return false;
			}
		}
		else
		{
			GenerateMovementField(Field);
			return false;
		}
		return true;
	}
	inline bool Attack(cellField*Cell, int i1, int j1, vector<vector<cellField>> Field, vector<Figure*> &Array)
	{
		int m(0), k(0);
		int buffi = this->Logic_i;
		int buffj = this->Logic_j;
		if (Field[i1][j1].GetPlace() == false)
		{

			for (int i = 0; i < (int)Array.size(); i++)
			{
				if (Array[i] == Cell->Pointer_to_Figure)
				{
					if (this->color == Cell->Pointer_to_Figure->color)
					{
						return false;
					}
					else
						for (int p = 0; p < 4; p++)
						{
							switch (p)
							{
							case 0:
							{
								m = 0;
								k = 1;
								break;
							}
							case 1:
							{
								m = 0;
								k = -1;
								break;
							}
							case 2:
							{
								m = 1;
								k = 0;
								break;
							}
							case 3:
							{
								m = -1;
								k = 0;
								break;
							}
							default:
								break;
							}
							for (int h = 0; h<(int)MovementField.size(); h++)
							{
								if (buffi + m < (int)MovementField.size() && buffi + m >= 0 && buffj + k < (int)MovementField.size() && buffj + k >= 0)
								{
									if (Field[buffi + m][buffj + k].GetPlace() == false)
									{
										if (i1 == buffi + m && j1 == buffj + k)
										{
											Array[i]->DeleteFigure();
											return true;
										}
										else break;

									}
								}
								buffi += m;
								buffj += k;
							}
							buffi = this->Logic_i;
							buffj = this->Logic_j;
						}
					}
				}

			}
			else return false;
			return false;
	}

};
class Queen :public Figure
{
	enum Color { Black, White };
protected:
	static int id;
	Color Side;
public:
	Queen(string& path) :Figure(path)
	{
		
	}
	Queen(float x1, float y1, int Logic_1, int Logic_2, cellField*p, bool Select, bool Move, bool color) :Figure(x1, y1, Logic_1, Logic_2, p, Select, Move, color)
	{

	}
	inline void GenerateMovementField(vector<vector<cellField>> Field)
	{
		for (int i = 0; i < (int)MovementField.size(); i++)
		{
			for (int j = 0; j < (int)MovementField.size(); j++)
			{
				this->MovementField[i][j] = false;
			}
		}
		int m = 0;
		int k = 0;
		int buffi = this->Logic_i;
		int buffj = this->Logic_j;
		for (int i = 0; i < 8; i++)
		{
			switch (i)
			{
			case 0:
			{
				m = 1;
				k = 0;
				break;
			}
			case 1:
			{
				m = -1;
				k = 0;
				break;
			}
			case 2:
			{
				m = 0;
				k = -1;
				break;
			}
			case 3:
			{
				m = 0;
				k = 1;
				break;
			}
			case 4:
			{
				m = 1;
				k = 1;
				break;
			}
			case 5:
			{
				m = -1;
				k = 1;
				break;
			}
			case 6:
			{
				m = 1;
				k = -1;
				break;
			}
			case 7:
			{
				m = -1;
				k = -1;
				break;
			}
			default:
				break;
			}
			for (int h = 0; h<(int)MovementField.size(); h++)
			{

				if (buffi + m < (int)MovementField.size() && buffi + m >= 0 && buffj + k < (int)MovementField.size() && buffj + k >= 0)
				{

					if (Field[buffi + m][buffj + k].GetPlace() == true)
					{
						MovementField[buffi + m][buffj + k] = true;
					}
					else
					{
						
					}
				}
				buffi += m;
				buffj += k;
			}
			buffi = this->Logic_i;
			buffj = this->Logic_j;
		}

		for (int i = 0; i < (int)Field.size(); i++)
		{
			for (int j = 0; j < (int)Field.size(); j++)
			{
				if (Field[i][j].GetPlace() == false)
					MovementField[i][j] = false;

			}
		}

	}
	inline bool Movement(cellField*Cell, float dX, float dY, float time, int i, int j, vector<vector<cellField>> Field)
	{
		if (MovementField[i][j] == true)
		{
			distance = sqrt((dX - this->x)*(dX - this->x) + (dY - this->y)*(dY - this->y));
			if (distance > 2)
			{

				this->x += 0.15*time*(dX - this->x) / distance;
				this->y += 0.15*time*(dY - this->y) / distance;

			}
			else
			{
				this->CellPointer->ChangePlace(true);
				this->CellPointer->Pointer_to_Figure = NULL;
				this->IsMove = false;
				this->CellPointer = Cell;
				Cell->Pointer_to_Figure = this;
				this->CellPointer->ChangePlace(false);
				this->Logic_i = i;
				this->Logic_j = j;
				GenerateMovementField(Field);
				return false;
			}
		}
		else
		{
			GenerateMovementField(Field);
			return false;
		}
		return true;
	}
	inline bool Attack(cellField*Cell, int i1, int j1, vector<vector<cellField>> Field, vector<Figure*> &Array)
	{
		int m(0), k(0);
		int buffi = this->Logic_i;
		int buffj = this->Logic_j;
		if (Field[i1][j1].GetPlace() == false)
		{
			for (int i = 0; i < (int)Array.size(); i++)
			{
				if (Array[i] == Cell->Pointer_to_Figure)
				{
					if (this->color == Cell->Pointer_to_Figure->color)
					{
						return false;
					}
					else
						for (int z = 0; z < 8; z++)
						{
							switch (z)
							{
							case 0:
							{
								m = 1;
								k = 0;
								break;
							}
							case 1:
							{
								m = -1;
								k = 0;
								break;
							}
							case 2:
							{
								m = 0;
								k = -1;
								break;
							}
							case 3:
							{
								m = 0;
								k = 1;
								break;
							}
							case 4:
							{
								m = 1;
								k = 1;
								break;
							}
							case 5:
							{
								m = -1;
								k = 1;
								break;
							}
							case 6:
							{
								m = 1;
								k = -1;
								break;
							}
							case 7:
							{
								m = -1;
								k = -1;
								break;
							}
							default:
								break;
							}
							for (int h = 0; h<(int)MovementField.size(); h++)
							{

								if (buffi + m < (int)MovementField.size() && buffi + m >= 0 && buffj + k < (int)MovementField.size() && buffj + k >= 0)
								{

									if (Field[buffi + m][buffj + k].GetPlace() == false)
									{
										if (i1 == buffi + m && j1 == buffj + k)
										{
											Array[i]->DeleteFigure();
											return true;
										}
										else break;

									}
								}
								buffi += m;
								buffj += k;
							}
							buffi = this->Logic_i;
							buffj = this->Logic_j;
						}
				}
			}
		}
		else return false;
		return false;
	}
};
class King :public Figure
{
	enum Color { Black, White };
protected:
	static int id;
	Color Side;
public:
	King(string& path) :Figure(path)
	{
		IsKing = true;
	}
	King(float x1, float y1, int Logic_1, int Logic_2, cellField*p, bool Select, bool Move, bool color) :Figure(x1, y1, Logic_1, Logic_2, p, Select, Move, color)
	{

	}
	inline void GenerateMovementField(vector<vector<cellField>> Field)

	{
		for (int i = 0; i < (int)MovementField.size(); i++)
		{
			for (int j = 0; j < (int)MovementField.size(); j++)
			{
				this->MovementField[i][j] = false;

			}
		}

		int m = 0;
		int k = 0;
		int buffi = this->Logic_i;
		int buffj = this->Logic_j;
		for (int i = 0; i < 8; i++)
		{
			switch (i)
			{
			case 0:
			{
				m = 1;
				k = 0;
				break;
			}
			case 1:
			{
				m = -1;
				k = 0;
				break;
			}
			case 2:
			{
				m = 0;
				k = -1;
				break;
			}
			case 3:
			{
				m = 0;
				k = 1;
				break;
			}
			case 4:
			{
				m = 1;
				k = 1;
				break;
			}
			case 5:
			{
				m = -1;
				k = 1;
				break;
			}
			case 6:
			{
				m = 1;
				k = -1;
				break;
			}
			case 7:
			{
				m = -1;
				k = -1;
				break;
			}
			default:
				break;
			}
		

				if (buffi + m < (int)MovementField.size() && buffi + m >= 0 && buffj + k < (int)MovementField.size() && buffj + k >= 0)
				{
					if (Field[buffi + m][buffj + k].GetPlace() == true)
					{
						MovementField[buffi + m][buffj + k] = true;
					}
				}
			
			buffi = this->Logic_i;
			buffj = this->Logic_j;
		}

		for (int i = 0; i < (int)Field.size(); i++)
		{
			for (int j = 0; j < (int)Field.size(); j++)
			{
				if (Field[i][j].GetPlace() == false)
					MovementField[i][j] = false;

			}
		}
	}
	inline bool Movement(cellField*Cell, float dX, float dY, float time, int i, int j, vector<vector<cellField>> Field)
	{

		if (MovementField[i][j] == true)
		{



			distance = sqrt((dX - this->x)*(dX - this->x) + (dY - this->y)*(dY - this->y));
			if (distance > 2)
			{

				this->x += 0.15*time*(dX - this->x) / distance;
				this->y += 0.15*time*(dY - this->y) / distance;

			}
			else
			{


				this->CellPointer->ChangePlace(true);
				this->CellPointer->Pointer_to_Figure = NULL;
				this->IsMove = false;
				this->CellPointer = Cell;
				Cell->Pointer_to_Figure = this;
				this->CellPointer->ChangePlace(false);
				this->Logic_i = i;
				this->Logic_j = j;

				GenerateMovementField(Field);

				return false;
			}
		}
		else
		{
			GenerateMovementField(Field);
			return false;
		}
		return true;
	}
	inline bool Attack(cellField*Cell, int i1, int j1, vector<vector<cellField>> Field, vector<Figure*> &Array)
	{
		int m(0), k(0);
		int buffi = this->Logic_i;
		int buffj = this->Logic_j;
		if (Field[i1][j1].GetPlace() == false)
		{

			for (int i = 0; i < (int)Array.size(); i++)
			{
				if (Array[i] == Cell->Pointer_to_Figure)
				{
					if (this->color == Cell->Pointer_to_Figure->color)
					{
						return false;
					}
					else
						for (int z = 0; z < 8; z++)
						{
							switch (z)
							{
							case 0:
							{
								m = 1;
								k = 0;
								break;
							}
							case 1:
							{
								m = -1;
								k = 0;
								break;
							}
							case 2:
							{
								m = 0;
								k = -1;
								break;
							}
							case 3:
							{
								m = 0;
								k = 1;
								break;
							}
							case 4:
							{
								m = 1;
								k = 1;
								break;
							}
							case 5:
							{
								m = -1;
								k = 1;
								break;
							}
							case 6:
							{
								m = 1;
								k = -1;
								break;
							}
							case 7:
							{
								m = -1;
								k = -1;
								break;
							}
							default:
								break;
							}
							

								if (buffi + m < (int)MovementField.size() && buffi + m >= 0 && buffj + k < (int)MovementField.size() && buffj + k >= 0)
								{

									if (Field[buffi + m][buffj + k].GetPlace() == false)
									{
										if (i1 == buffi + m && j1 == buffj + k)
										{
											Array[i]->DeleteFigure();
											return true;
										}
									}
								}
								
							buffi = this->Logic_i;
							buffj = this->Logic_j;
						}
				}
				else
				{
					cout << "Адрес не найден" << endl;
				}
			}

		}
		else return false;
		return false;
	}
};
class Gamefield
{
protected:

	vector<Figure*> GameFigureBlack;
	vector<Figure*> GameFigureWhite;
	
	Figure GameBackground;
public:

	vector<vector<cellField>> Field;

	Gamefield(RenderWindow &window)
	{
		Field.resize(8);
		for (int i = 0; i < (int)Field.size(); i++)
		{
			Field[i].resize(8);
		}
		string buffer = "./Resource/Gamefield.png";
		GameBackground.SpriteInit(window, buffer);
		GameBackground.GetSprite().setScale(0.48, 0.48);
		GameBackground.GetSprite().setPosition(240, 240);
		int lever(0);
		for (int i = 0; i<(int)Field.size(); i++)
		{
			for (int j = 0; j < (int)Field.size(); j++)
			{
				switch (lever)
				{
				case 0:
				{
					string bufferCell = "./Resource/FieldWhite.png";
					Field[i][j].SpriteInit(bufferCell);
					

					lever = 1;
					break;
				}
				case 1:
				{
					string bufferCell = "./Resource/FieldBlack.png";
					Field[i][j].SpriteInit(bufferCell);
					
					lever = 0;
					break;
				}
				default:
					break;
				}


			}
			if (i % 2 == 0)
			{
				lever = 1;
			}
			else
			{
				lever = 0;
			}
		}

	}
	void DrawField(RenderWindow &window)
	{
		int x(50), y(50);
		for (int i = 0; i < (int)Field.size(); i++)
		{
			for (int j = 0; j < (int)Field.size(); j++)
			{
				
				window.draw(Field[i][j].GetSprite());
				

			}
		}
		
		DrawFigure(window);
	}
	inline void CreateFigure()
	{
		GameFigureBlack.resize(quantityFigure);
		GameFigureWhite.resize(quantityFigure);
		string buffer;
		for (int i = 0; i < quantityFigure; i++)
		{
			if (i > 7)
			{
				buffer = "./Resource/PawnWhite.png";
				GameFigureWhite[i] = new Pawn(buffer);
				buffer = "./Resource/PawnBlack.png";
				GameFigureBlack[i] = new Pawn(buffer);
				GameFigureWhite[i]->GetSprite().setScale(0.70, 0.70);
				GameFigureBlack[i]->GetSprite().setScale(0.70, 0.70);
			}
			else if (i == 0 || i == 7)
			{
				buffer = "./Resource/RookWhite.png";
				GameFigureWhite[i] = new Rooks(buffer);
				buffer = "./Resource/RookBlack.png";
				GameFigureBlack[i] = new Rooks(buffer);
				GameFigureWhite[i]->GetSprite().setScale(0.70, 0.70);
				GameFigureBlack[i]->GetSprite().setScale(0.70, 0.70);
			}
			else if (i == 1 || i == 6)
			{
				buffer = "./Resource/KnightWhite.png";
				GameFigureWhite[i] = new Knight(buffer);
				buffer = "./Resource/KnightBlack.png";
				GameFigureBlack[i] = new Knight(buffer);
				GameFigureWhite[i]->GetSprite().setScale(0.70, 0.70);
				GameFigureBlack[i]->GetSprite().setScale(0.70, 0.70);
			}
			else if (i == 2 || i == 5)
			{
				buffer = "./Resource/ElephantWhite.png";
				GameFigureWhite[i] = new Elephant(buffer);
				buffer = "./Resource/ElephantBlack.png";
				GameFigureBlack[i] = new Elephant(buffer);
				GameFigureWhite[i]->GetSprite().setScale(0.70, 0.70);
				GameFigureBlack[i]->GetSprite().setScale(0.70, 0.70);
			}
			else if (i == 4)
			{
				buffer = "./Resource/KingWhite.png";
				GameFigureWhite[i] = new King(buffer);
				buffer = "./Resource/QueenBlack.png";
				GameFigureBlack[i] = new Queen(buffer);
				GameFigureWhite[i]->GetSprite().setScale(0.70, 0.70);
				GameFigureBlack[i]->GetSprite().setScale(0.70, 0.70);
			}
			else if (i == 3)
			{
				buffer = "./Resource/QueenWhite.png";
				GameFigureWhite[i] = new Queen(buffer);
				buffer = "./Resource/KingBlack.png";
				GameFigureBlack[i] = new King(buffer);
				GameFigureWhite[i]->GetSprite().setScale(0.70, 0.70);
				GameFigureBlack[i]->GetSprite().setScale(0.70, 0.70);
				
			}

		}
	}
	void SetCoordFigure()
	{
		int count(0);
		int x(50), y(50), m(0), k(0);
		for (m = 0; m < (int)Field.size(); m++)
		{
			for (k = 0; k < (int)Field.size(); k++)
			{
				Field[m][k].GetSprite().setScale(0.60, 0.60);
				Field[m][k].GetSprite().setPosition(x, y);
				x = x + (Field[m][k].GetImage().getSize().x*0.60);

			}
			x = 50;
			y = y + (Field[m][k - 1].GetImage().getSize().y*0.60);

		}
		while (count != GameFigureBlack.size())
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < (int)Field.size(); j++)
				{
					GameFigureBlack[count]->x = (Field[i][j].GetSprite().getPosition().x);
					GameFigureBlack[count]->y = (Field[i][j].GetSprite().getPosition().y);
					Field[i][j].ChangePlace(false); // Ячейка становиться занятой

					GameFigureBlack[count]->CellPointer = &Field[i][j];
					Field[i][j].Pointer_to_Figure = GameFigureBlack[count];
					GameFigureBlack[count]->Logic_i = i;
					GameFigureBlack[count]->Logic_j = j;
					GameFigureBlack[count]->color = 0;
					count++;
				
				}
			}
		count = GameFigureWhite.size() - 1;
		while (count > 0)
		{
			for (int i = Field.size() - 2; i < (int)Field.size(); i++)
			{
				for (int j = 0; j < (int)Field.size(); j++)
				{
					GameFigureWhite[count]->x = (Field[i][j].GetSprite().getPosition().x);
					GameFigureWhite[count]->y = (Field[i][j].GetSprite().getPosition().y);
					Field[i][j].ChangePlace(false); // Ячейка становиться занятой
					GameFigureWhite[count]->CellPointer = &Field[i][j];
					Field[i][j].Pointer_to_Figure = GameFigureWhite[count];
					GameFigureWhite[count]->Logic_i = i;
					GameFigureWhite[count]->Logic_j = j;
					GameFigureWhite[count]->color = 1;
					count--;
				}
			}
		}
	}
	inline void DrawFigure(RenderWindow &window)
	{
		int count(0);
		while(count != GameFigureBlack.size())
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < (int)Field.size(); j++)
			{	
				GameFigureBlack[count]->GetSprite().setPosition(GameFigureBlack[count]->x, GameFigureBlack[count]->y);
				window.draw(GameFigureBlack[count++]->GetSprite());
			}
		}
		count = GameFigureWhite.size()-1;
		while (count > 0)
		for (int i = Field.size()-2; i < (int)Field.size(); i++)
		{
			for (int j = 0; j < (int)Field.size(); j++)
			{
				GameFigureWhite[count]->GetSprite().setPosition(GameFigureWhite[count]->x, GameFigureWhite[count]->y);
				if (GameFigureWhite[count] == NULL)
				{
					count--;
				}
				else
				{
					window.draw(GameFigureWhite[count--]->GetSprite());
				}
				
			}
		}
	}


	Sprite GetBackground()
	{
		return GameBackground.GetSprite();
	}
	vector<Figure*> GetGameFigureBlack()
	{
		return GameFigureBlack;
	}
	vector<Figure*> GetGameFigureWhite()
	{
		return GameFigureWhite;
	}
};
class Player
{
protected:
	
public:
	vector<Figure*> GameFigure;

	Player()
	{

	}
	void SetPlayer(vector<Figure*> P)
	{
		GameFigure = P;
	}
	vector<Figure*> GetFigure()
	{
		return GameFigure;
	}
};
static void InitGraphics();
int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	InitGraphics();
	system("pause");
	return 0;
}

static void InitGraphics()
{
	//Сглаживание...
	ContextSettings settings;
	settings.antialiasingLevel = 16;

	//-----------------------------------------//
	RenderWindow window(VideoMode(500, 500), "Chess");


	GameEvent GameProcess(window);
	Gamefield GameTile(window);
	Font fontStyle;
	GameTile.CreateFigure();
	window.setFramerateLimit(60);
	Clock clock;
	Player PlayerOne, PlayerTwo;
	bool step = true;
	if (!fontStyle.loadFromFile("ArialBlack.ttf"))
	{
		cout << "Oshibka zagruzki shrifta" << endl;
		window.close();

	}
	PlayerOne.SetPlayer(GameTile.GetGameFigureWhite());
	PlayerTwo.SetPlayer(GameTile.GetGameFigureBlack());

	GameTile.SetCoordFigure();
	for (int i = 0; i < quantityFigure; i++)
	{
		PlayerTwo.GameFigure[i]->GenerateMovementField(GameTile.Field);

	}
	for (int i = 0; i < quantityFigure; i++)
	{

		PlayerOne.GameFigure[i]->GenerateMovementField(GameTile.Field);

	}
	Figure* SelectObject1 = NULL;
	Figure* SelectObject2 = NULL;
	cellField* SelectCell = NULL;
	cellField* SelectCell2 = NULL;
	float dX = 0;
	float dY = 0;
	int buffer_i(0), buffer_j(0);
	float distance = 0;
	bool Action = false;
	while (window.isOpen())
	{
		Event event;

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		vector<vector<cellField>>SelectField(0);

		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);

		while (window.pollEvent(event))
		{

			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed)
			{
				if (event.key.code == Mouse::Left)
				{

					if (!Action)
						for (int i = 0; i < quantityFigure; i++)
						{
							if(step)
							if (PlayerOne.GameFigure[i]->GetSprite().getGlobalBounds().contains(pos.x, pos.y))
							{
								if (SelectObject2 != NULL)
								{
									SelectObject2->IsSelect = false;
									SelectObject2->IsMove = false;
									SelectObject2 = NULL;
								}

								//PlayerOne.GameFigure[i]->GetSprite().setColor(Color::Green);
								SelectObject1 = PlayerOne.GameFigure[i];
								PlayerOne.GameFigure[i]->IsSelect = true;



							}
							if(!step)
							if (PlayerTwo.GameFigure[i]->GetSprite().getGlobalBounds().contains(pos.x, pos.y))
							{
								if (SelectObject1 != NULL)
								{
									SelectObject1->IsSelect = false;
									SelectObject1->IsMove = false;
									SelectObject1 = NULL;
								}

								//PlayerTwo.GameFigure[i]->GetSprite().setColor(Color::Green);
								SelectObject2 = PlayerTwo.GameFigure[i];
								PlayerTwo.GameFigure[i]->IsSelect = true;

							}

						}
				}

			}
			if(step)
			if (SelectObject1 != NULL)
				if (SelectObject1->IsSelect)
				{
					if (SelectObject2 != NULL)
					{
						SelectObject2->IsSelect = false;
						SelectObject2->IsMove = false;
						SelectObject2 = NULL;
					}
					if (event.type == Event::MouseButtonPressed)
						if (event.key.code == Mouse::Right)
							for (int m = 0; m < 8; m++)
								for (int j = 0; j < 8; j++)
								{
									if (GameTile.Field[m][j].GetSprite().getGlobalBounds().contains(pos.x, pos.y))
									{
										
										dX = (GameTile.Field[m][j].GetSprite().getPosition().x);
										dY = (GameTile.Field[m][j].GetSprite().getPosition().y);
										SelectCell = &GameTile.Field[m][j];
										buffer_i = m;
										buffer_j = j;
										SelectObject1->IsMove = true;
										SelectObject1->IsSelect = false;
										if (SelectObject1->Attack(SelectCell, buffer_i, buffer_j, GameTile.Field, GameTile.GetGameFigureBlack())==true)
										{
											if (SelectCell->Pointer_to_Figure->IsKing==true)
											{
												
													cout << "Победа" << endl;
													return;
												
											}
											GameTile.Field[m][j].ChangePlace(true);
											Action = SelectObject1->Movement(SelectCell, dX, dY, time, buffer_i, buffer_j, GameTile.Field);
											if (!Action)
											{
												step = true;
											}
											break;
										}				
									}
								}
							}
			if(!step)
			if (SelectObject2 != NULL)
				if (SelectObject2->IsSelect)
				{
					if (SelectObject1 != NULL)
					{
						SelectObject1->IsSelect = false;
						SelectObject1->IsMove = false;
						SelectObject1 = NULL;
					}
					if (event.type == Event::MouseButtonPressed)
						if (event.key.code == Mouse::Right)
							for (int m = 0; m < (int)GameTile.Field.size(); m++)
								for (int j = 0; j < (int)GameTile.Field.size(); j++)
								{
									if (GameTile.Field[m][j].GetSprite().getGlobalBounds().contains(pos.x, pos.y))
									{

										dX = (GameTile.Field[m][j].GetSprite().getPosition().x);
										dY = (GameTile.Field[m][j].GetSprite().getPosition().y);

										SelectCell2 = &GameTile.Field[m][j];

										buffer_i = m;
										buffer_j = j;
										
										SelectObject2->IsMove = true;
										SelectObject2->IsSelect = false;
										
										if (SelectObject2->Attack(SelectCell2, buffer_i, buffer_j, GameTile.Field, GameTile.GetGameFigureWhite())==true)
										{
											if (SelectCell->Pointer_to_Figure->IsKing == true)
											{
												
												cout << "Победа" << endl;
												return;

											}
											GameTile.Field[m][j].ChangePlace(true);
											Action = SelectObject2->Movement(SelectCell2, dX, dY, time, buffer_i, buffer_j, GameTile.Field);
											if (!Action)
											{
												step = true;
											}
											break;
										}
										
									}

								}
				}
		}
		if(step)
		if (SelectCell != NULL)
			if (SelectObject1 != NULL && SelectCell->GetPlace() == true)
				if (SelectObject1->IsMove)
				{
					Action = true;
					if (SelectObject2 != NULL)
					{
						SelectObject2->IsSelect = false;
						SelectObject2->IsMove = false;
						SelectObject2 = NULL;
					}
				
					
					Action = SelectObject1->Movement(SelectCell, dX, dY, time,buffer_i,buffer_j, GameTile.Field);
					if (!Action)
					{
						SelectObject1->PawnTransmogrification(SelectObject1->Logic_i, GameTile.Field, PlayerOne.GameFigure);
						SelectObject1->GenerateMovementField(GameTile.Field);
						SelectObject1->SetSprite(SelectObject1->GetTexture());
						step = false;
					}
				}

		if(!step)
		if (SelectCell2 != NULL)
			if (SelectObject2 != NULL && SelectCell2->GetPlace() == true)
				if (SelectObject2->IsMove)
				{
					Action = true;
					if (SelectObject1 != NULL)
					{
						SelectObject1->IsSelect = false;
						SelectObject1->IsMove = false;
						SelectObject1 = NULL;
					}
					
	 
					
					Action = SelectObject2->Movement(SelectCell2, dX, dY, time, buffer_i, buffer_j, GameTile.Field);
					if (!Action)
					{
						
						SelectObject2->PawnTransmogrification(SelectObject2->Logic_i, GameTile.Field, PlayerTwo.GameFigure);
						SelectObject2->GenerateMovementField(GameTile.Field);
						SelectObject2->SetSprite(SelectObject2->GetTexture());
						step = true;
					}
				}
	
		window.clear(Color::White);
		window.draw(GameProcess.GetBackground());
		window.draw(GameTile.GetBackground());
		GameTile.DrawField(window);

		window.display();
	}
}

