#include "allClasses.h"
#include <cmath>

bool Rhomb::inWin()
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	RECT rt;
	GetClientRect(hwnd, &rt);
	for (int i = 0; i < 4; i++)
	{
		if (ppt[i].x > rt.right || ppt[i].x < 0 || ppt[i].y > rt.bottom || ppt[i].y < 0)
			return false;
	}
	ReleaseDC(hwnd, hdc);
	return true;
}

bool Rhomb::checkRhomb()
{
	for (int i = 0; i < 3; i++)
	{
		if (pow((ppt[i].x - ppt[(i + 1) % 4].x), 2.0) + pow((ppt[i].y - ppt[(i + 1) % 4].y), 2.0) ==
			pow((ppt[i + 1].x - ppt[(i + 2) % 4].x), 2.0) + pow((ppt[i + 1].y - ppt[(i + 2) % 4].y), 2.0))
			continue;
		else
			return false;
	}
	return true;
}

void Rhomb::set_coordinats(POINT *ppt_in)
{
	for (int i = 0; i < 4; i++)
	{
		ppt[i].x = ppt_in[i].x;
		ppt[i].y = ppt_in[i].y;
	}
}

POINT *Rhomb::get_coordinats()
{
	return ppt;
}

void clearScreen()
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	HPEN darkPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HBRUSH darkBrush = CreateSolidBrush(RGB(0, 0, 0));
	SelectPen(hdc, darkPen);
	SelectBrush(hdc, darkBrush);
	Rectangle(hdc, 0, 0, 9000, 9000);
	DeletePen(darkPen);
	DeleteBrush(darkBrush);
	ReleaseDC(hwnd, hdc);
}

void Shaded::set_color(int *clr)
{
	for (int i = 0; i < 3; i++)
		color[i] = clr[i];
}
int *Shaded::get_color()
{
	return color;
}

void RhombContour::draw()
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	SetBkColor(hdc, RGB(0, 0, 0));
	HPEN Pen = CreatePen(PS_SOLID, thickness, RGB(cntColor[0], cntColor[1], cntColor [2]));
	HBRUSH Brush = CreateSolidBrush(RGB(0, 0, 0));
	SelectPen(hdc, Pen);
	SelectBrush(hdc, Brush);
	bool bxt = Polygon(hdc, ppt, 4);
	ReleaseDC(hwnd, hdc);
}

void RhombContour::readData(char *filename)
{
	FILE *f;
	f = fopen(filename, "r");
	for (int i = 0; i < 4; i++)
		fscanf(f, "%d %d", &ppt[i].x, &ppt[i].y);
	fscanf(f, "%d %d %d", &cntColor[0], &cntColor[1], &cntColor[2]);
	fscanf(f, "%d", &thickness);
	fclose(f);
}
void RhombContour::saveData(char *filename)
{
	FILE *f;
	f = fopen(filename, "w");
	for (int i = 0; i < 4; i++)
		fprintf(f, "%d %d\n", ppt[i].x, ppt[i].y);
	fprintf(f, "%d %d %d\n", cntColor[0], cntColor[1], cntColor[2]);
	fprintf(f, "%d\n", thickness);
	fclose(f);
}

void RhombContour::set_cntColor(int *clr)
{
	for (int i = 0; i < 4; i++)
		cntColor[i] = clr[i];
}

int *RhombContour::get_cntColor()
{
	return cntColor;
}

void RhombContour::set_thickness(int thick)
{
	thickness = thick;
}

int RhombContour::get_thickness()
{
	return thickness;
}

void RhombShaded::draw()
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	SetBkColor(hdc, RGB(0, 0, 0));
	HPEN Pen = CreatePen(PS_SOLID, thickness, RGB(cntColor[0], cntColor[1], cntColor [2]));
	HBRUSH Brush = CreateSolidBrush(RGB(color[0], color[1], color[2]));
	SelectPen(hdc, Pen);
	SelectBrush(hdc, Brush);
	bool bxt = Polygon(hdc, ppt, 4);
	ReleaseDC(hwnd, hdc);
}

void RhombShaded::readData(char *filename)
{
	FILE *f;
	f = fopen(filename, "r");
	for (int i = 0; i < 4; i++)
		fscanf(f, "%d %d", &ppt[i].x, &ppt[i].y);
	fscanf(f, "%d %d %d", &cntColor[0], &cntColor[1], &cntColor[2]);
	fscanf(f, "%d %d %d", &color[0], &color[1], &color[2]);
	fscanf(f, "%d", &thickness);
	fclose(f);
}

void RhombShaded::saveData(char *filename)
{
	FILE *f;
	f = fopen(filename, "w");
	for (int i = 0; i < 4; i++)
		fprintf(f, "%d %d\n", ppt[i].x, ppt[i].y);
	fprintf(f, "%d %d %d\n", cntColor[0], cntColor[1], cntColor[2]);
	fprintf(f, "%d %d %d\n", color[0], color[1], color[2]);
	fprintf(f, "%d", thickness);
	fclose(f);
}

bool CombRhomb::insideRhomb()
{
	POINT *ppt1 = ppt;
	POINT *ppt2 = smallRhomb.get_coordinats();
	int i = 0;
	while (!(ppt1[i].x <= ppt1[(i + 1) % 4].x && ppt1[i].y > ppt1[(i + 1) % 4].y))
		i++;
	for (int j = 0; j < 4; j++)
	{
		if (((ppt2[j].y - ppt1[i].y) * (ppt1[(i + 1) % 4].x - ppt1[i].x) - (ppt2[j].x - ppt1[i].x) * (ppt1[(i + 1) % 4].y - ppt1[i].y)) > 0);
		else return false;
		if (((ppt2[j].y - ppt1[(i + 1) % 4].y) * (ppt1[(i + 2) % 4].x - ppt1[(i + 1) % 4].x) - (ppt2[j].x - ppt1[(i + 1) % 4].x) * (ppt1[(i + 2) % 4].y - ppt1[(i + 1) % 4].y)) > 0);
		else return false;
		if (((ppt2[j].y - ppt1[(i + 2) % 4].y) * (ppt1[(i + 3) % 4].x - ppt1[(i + 2) % 4].x) - (ppt2[j].x - ppt1[(i + 2) % 4].x) * (ppt1[(i + 3) % 4].y - ppt1[(i + 2) % 4].y)) > 0);
		else return false;
		if (((ppt2[j].y - ppt1[(i + 3) % 4].y) * (ppt1[(i + 4) % 4].x - ppt1[(i + 3) % 4].x) - (ppt2[j].x - ppt1[(i + 3) % 4].x) * (ppt1[(i + 4) % 4].y - ppt1[(i + 3) % 4].y)) > 0);
		else return false;
	}
	return true;
}

void CombRhomb::draw()
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	SetBkColor(hdc, RGB(0, 0, 0));
	HPEN Pen = CreatePen(PS_SOLID, thickness, RGB(cntColor[0], cntColor[1], cntColor [2]));
	HBRUSH Brush = CreateSolidBrush(RGB(color[0], color[1], color[2]));
	SelectPen(hdc, Pen);
	SelectBrush(hdc, Brush);
	bool bxt = Polygon(hdc, ppt, 4);
	int *smallRhombColor = smallRhomb.get_cntColor();
	Pen = CreatePen(PS_SOLID, smallRhomb.get_thickness(), RGB(smallRhombColor[0], smallRhombColor[1], smallRhombColor[2]));
	Brush = CreateSolidBrush(RGB(0, 0, 0));
	SelectPen(hdc, Pen);
	SelectBrush(hdc, Brush);
	bxt = Polygon(hdc, smallRhomb.get_coordinats(), 4);
	ReleaseDC(hwnd, hdc);
}

void CombRhomb::readData(char *filename)
{
	FILE *f;
	f = fopen(filename, "r");
	for (int i = 0; i < 4; i++)
		fscanf(f, "%d %d", &ppt[i].x, &ppt[i].y);
	POINT ppt1[4];
	int cntColor1[3];
	int color1[3];
	int thickness1;
	fscanf(f, "%d %d %d", &cntColor[0], &cntColor[1], &cntColor[2]);
	fscanf(f, "%d %d %d", &color[0], &color[1], &color[2]);
	fscanf(f, "%d", &thickness);
	for (int i = 0; i < 4; i++)
		fscanf(f, "%d %d", &ppt1[i].x, &ppt1[i].y);
	fscanf(f, "%d %d %d", &cntColor1[0], &cntColor1[1], &cntColor1[2]);
	fscanf(f, "%d", &thickness1);
	smallRhomb.set_coordinats(ppt1);
	smallRhomb.set_cntColor(cntColor1);
	smallRhomb.set_thickness(thickness1);
	fclose(f);
}

void CombRhomb::saveData(char *filename)
{
	FILE *f;
	f = fopen(filename, "w");
	for (int i = 0; i < 4; i++)
		fscanf(f, "%d %d\n", ppt[i].x, ppt[i].y);
	POINT *ppt1 = smallRhomb.get_coordinats();
	int *cntColor1 = smallRhomb.get_cntColor();
	int thickness1 = smallRhomb.get_thickness();
	fprintf(f, "%d %d %d\n", cntColor[0], cntColor[1], cntColor[2]);
	fprintf(f, "%d %d %d\n", color[0], color[1], color[2]);
	fprintf(f, "%d\n", thickness);
	for (int i = 0; i < 4; i++)
		fprintf(f, "%d %d\n", ppt1[i].x, ppt1[i].y);
	fprintf(f, "%d %d %d\n", cntColor1[0], cntColor1[1], cntColor1[2]);
	fprintf(f, "%d", thickness1);
	fclose(f);
}

RhombContour CombRhomb::get_smallRhomb()
{
	return smallRhomb;
}
