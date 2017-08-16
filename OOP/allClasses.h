//#pragma once
#include <windows.h> 
#include <windowsx.h>
#include <stdio.h>

class Rhomb
{
protected:
	POINT ppt[4]; //���������� �����

public:
	virtual void draw() = 0; //����������� ������� ���������
	virtual void saveData(char *filename) = 0;//����������� ������� ������ � ����
	virtual void readData(char *filename) = 0; //����������� ������� ����������
	bool inWin(); //������� �������� ��������� ����� � ����
	bool checkRhomb(); //������� �������� �������� �� ������ ������

	void set_coordinats(POINT *ppt_in); //������� �������� ����������
	POINT *get_coordinats(); //� ������������ ��

};

class Shaded
{
protected:
	int color[3]; //���� �������

public:
	void set_color(int *clr); //������� �������� ����
	int *get_color(); //� ������������ ���
};

class RhombContour : public Rhomb
{
protected:
	int cntColor[3]; //���� �������
	int thickness;

public:
	void draw(); //��������������� ����������� ������� ���������
	void readData(char *filename); //��������������� ����������� ������� ����������
	void saveData(char *filename);
	void set_cntColor(int *clr); //������� �������� ���� �������
	int *get_cntColor(); //������������ ���

	void set_thickness(int thick); //������� �������� ������� �������
	int get_thickness(); //������������ ���
};

class RhombShaded : public Shaded, public RhombContour
{
protected:
public:
	void draw(); //��������������� ����������� ������� ���������
	void readData(char *filename); //��������������� ����������� ������� ����������
	void saveData(char *filename);
};

class CombRhomb : public RhombShaded
{
protected:
	RhombContour smallRhomb;

public:
	void draw(); //��������������� ������� ���������
	void readData(char *filename); //��������������� ������� ���������� �����
	void saveData(char *filename);

	bool insideRhomb(); //������� �������� �� �����������

	RhombContour get_smallRhomb(); //������� ������������ ������ � ����� �����
};

void clearScreen(); //������� ������� ������

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
