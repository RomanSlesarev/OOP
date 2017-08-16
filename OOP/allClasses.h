//#pragma once
#include <windows.h> 
#include <windowsx.h>
#include <stdio.h>

class Rhomb
{
protected:
	POINT ppt[4]; //координаты ромба

public:
	virtual void draw() = 0; //виртуальная функция рисования
	virtual void saveData(char *filename) = 0;//виртуальная функция записи в файл
	virtual void readData(char *filename) = 0; //виртуальная функция считывания
	bool inWin(); //функция проверки вхождения точек в поле
	bool checkRhomb(); //функция проверки является ли фигура ромбом

	void set_coordinats(POINT *ppt_in); //функция задающая координаты
	POINT *get_coordinats(); //и возвращающая их

};

class Shaded
{
protected:
	int color[3]; //цвет заливки

public:
	void set_color(int *clr); //функция задающая цвет
	int *get_color(); //и возвращающая его
};

class RhombContour : public Rhomb
{
protected:
	int cntColor[3]; //цвет контура
	int thickness;

public:
	void draw(); //переопределение виртуальной функции рисования
	void readData(char *filename); //переопределение виртуальной функции считывания
	void saveData(char *filename);
	void set_cntColor(int *clr); //функция задающая цвет контура
	int *get_cntColor(); //возвращающая его

	void set_thickness(int thick); //функция задающая толщину контура
	int get_thickness(); //возвращающая его
};

class RhombShaded : public Shaded, public RhombContour
{
protected:
public:
	void draw(); //переопределение виртуальной функции рисования
	void readData(char *filename); //переопределение виртуальной функции считывания
	void saveData(char *filename);
};

class CombRhomb : public RhombShaded
{
protected:
	RhombContour smallRhomb;

public:
	void draw(); //переопределение функции рисования
	void readData(char *filename); //переопределение функции считывания файла
	void saveData(char *filename);

	bool insideRhomb(); //функция проверки на вложенность

	RhombContour get_smallRhomb(); //функция возвращающая данные о малом ромбе
};

void clearScreen(); //функция очистки экрана

template <typename Type> class List
{
	struct ch
	{
		int key;
		typename Type rh;
		ch *next;
		ch *prev;
	};
private:
	ch *flist;
	ch *top;
	int quantity;
public:
	List()
	{
		flist = new ch;
		flist->key = 0;
		flist->next = flist;
		flist->prev = flist;
		top = flist;
		quantity = 0;
	}
	~List()
	{
		ch *bufp = top;
		ch *bufn = top;
		for (int i = 0; i < quantity; i++)
		{
			bufn = bufp->next;
			delete(bufp);
			bufp = bufn;
		}
	}
	void addEl(Type rh);
	void findEl(Type *inp, int key);
	bool isEmpty();
	int get_quantity();
};

template <typename Type> void List <Type> ::addEl(Type rh)
{
	ch *newEl = new ch;
	flist->rh = rh;
	flist->next = newEl;
	flist->key = quantity;
	newEl->prev = flist;
	flist = newEl;
	quantity++;
};

template <typename Type> void List <Type> ::findEl(Type *inp, int key)
{
	ch *buf = top;
	for (int i = 0; i < quantity; i++)
	{
		if (buf->key == key)
		{
			*inp = buf->rh;
			break;
		}
		else
		{
			buf = buf->next;
		}
	}

};


template <typename Type> bool List <Type> ::isEmpty()
{
	if (quantity == 0)
		return true;
	else return false;
};

template <typename Type> int List <Type> ::get_quantity()
{
	return quantity;
};
