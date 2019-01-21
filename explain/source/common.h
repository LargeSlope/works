#pragma once
/*///////////////////////////////////////////////////////////////////////////////////////////////////
*�ycommon ASSY�W���@�\�z																			*
*	�쐬���F2018/5/1																				*
*	�X�V���F2018/5/1																				*
*	�o�[�W�����F1.0.0																				*
*																									*
*	�R���e���c																						*
*	�y�J���[�p�b�P�[�W�z																			*
*	�y���ʃ��W���[�����C���@�\�z																	*
*	�y���ʃ��W���[�����Z�@�\�z																		*
*																									*
///////////////////////////////////////////////////////////////////////////////////////////////////*/
#include "DxLib.h"
#include <vector>
#include <math.h>
#include <iostream>
#include <fstream>
#include <windows.h>

/*///////////////////////////////////////////////////////////////////////////////////////////////////
*�y�J���[�p�b�P�[�W�z																				*
*	�쐬���F2016/8/29																				*
*	�X�V���F2018/5/1																				*
*	�o�[�W�����F3.0.0																				*
///////////////////////////////////////////////////////////////////////////////////////////////////*/

#define white	0xffffffff
#define black	0xff000000
#define blue	0xff0000ff
#define green	0xff00ff00
#define lime	0xff30ff30
#define red		0xffff0000
#define sky		0xffb1fcff
#define sky0	0xff00b2b2
#define sun		0xffffad4f
#define grass	0xff75d128
#define purple	0xffbb66ff
#define pink	0xffffbdfa
#define maple	0xffffe200
#define cream	0xfffff4a0
#define brown	0xffb45e25
#define shock	0xffb42563
#define dark	0xff3e6092

#define gray0	0xff181818 //24gray
#define gray1	0xff1f1f1f //31gray
#define gray2	0xff282828 //40gray
#define gray3	0xff2f2f2f //47gray
#define gray4	0xff383838 //56gray
#define gray5	0xff3f3f3f //63gray
#define gray6	0xff484848 //72gray
#define gray7	0xff4f4f4f //79gray
#define gray8	0xff585858 //88gray
#define gray9	0xff5f5f5f //95gray
#define gray10	0xff646464 //100gray
#define gray11	0xff686868 //104gray
#define gray12	0xff6f6f6f //111gray
#define gray13	0xff969696 //150gray
#define gray14	0xffb4b4b4 //180gray
#define gray15	0xffc8c8c8 //200gray
#define gray16	0xffdcdcdc //220gray
#define gray17	0xfff0f0f0 //240gray

//�R���\�[���A�v���P�[�V�����p
#define COL_BLACK			0x00
#define COL_DARK_BLUE       0x01
#define COL_DARK_GREEN		0x02
#define COL_DARK_CYAN		0x03
#define COL_DARK_RED		0x04
#define COL_DARK_VIOLET		0x05
#define COL_DARK_YELLOW		0x06
#define COL_GRAY			0x07
#define COL_LIGHT_GRAY		0x08
#define COL_BLUE			0x09
#define COL_GREEN			0x0a
#define COL_CYAN			0x0b
#define COL_RED				0x0c
#define COL_VIOLET			0x0d
#define COL_YELLOW			0x0e
#define COL_WHITE			0x0f
#define	COL_INTENSITY		0x08     // ���P�x�}�X�N
#define	COL_RED_MASK		0x04     // �ԐF�r�b�g
#define	COL_GREEN_MASK		0x02     // �ΐF�r�b�g
#define	COL_BLUE_MASK		0x01     //  �F�r�b�g

/*///////////////////////////////////////////////////////////////////////////////////////////////////
*�y���ʃ��W���[�����C���@�\�z																		*
*	�쐬���F2018/5/1																				*
*	�X�V���F2018/5/1																				*
*	�o�[�W�����F1.0.0																				*
///////////////////////////////////////////////////////////////////////////////////////////////////*/
#define WINDOW_SIZE_X	(816)
#define WINDOW_SIZE_Y	(624)

#define ALL		(0x08)	// All
#define FLIP	(0x0E)	// Flip
#define MESSAGE (0x0D)	// Message
#define CLEAR	(0x0B)	// Clear

#define WINDOW_COLOR (gray17)

//������
#define Init Winit();

//main�֐�
#define main() WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)

//���[�v�}�l�[�W
#define Loop(flag) Wupdate(flag)

int Winit();

int Wupdate(unsigned char update_flag);

void End();

/*///////////////////////////////////////////////////////////////////////////////////////////////////
*�y���ʃ��W���[�����Z�@�\�z																			*
*	�쐬���F2018/5/1																				*
*	�X�V���F2018/5/1																				*
*	�o�[�W�����F1.0.0																				*
///////////////////////////////////////////////////////////////////////////////////////////////////*/

#define BOTTOM	(0x03)
#define LEFT	(0x05)
#define RIGHT	(0x10)
#define TOP		(0x12)

#define ABS(num) (num < 0 ? -num : num)

#define PI (3.14159265359)

//�_���W�^
template<class T>
class point1 {

public:
	T x = 0, y = 0;

	point1() {
		x = 0;
		y = 0;
	}
	point1(T a) {
		x = a;
		y = a;
	}
	point1(T a, T b) {
		x = a;
		y = b;
	}
	point1(const point1<T>& point) {
		x = point.x;
		y = point.y;
	}

	point1<T> operator+(point1<T> a) { return point1<T>(x + a.x, y + a.y); }
	point1<T> operator-(point1 a) { return point1<T>(x - a.x, y - a.y); }
	point1<T> operator+(T a) { return point1<T>(x + a, y + a); }
	point1<T> operator-(T a) { return point1<T>(x - a, y - a); }
	point1<T> operator*(T a) { return point1<T>(x * a, y * a); }
	point1<T> operator/(T a) { return point1<T>(x / a, y / a); }
	T operator*(point1<T> a) { return x * a.y + y * a.x; }
	T operator=(T a) { x = a, y = a; return a; }
	bool operator==(point1<T> a) { return (x == a.x && y == a.y); }

	point1<T> operator+=(point1<T> a) { return *this = *this + a; }
	point1<T> operator-=(point1<T> a) { return *this = *this - a; }
	point1<T> operator+=(T a) { return *this = *this + a; }
	point1<T> operator-=(T a) { return *this = *this - a; }
	point1<T> operator*=(T a) { return *this = *this * a; }
	point1<T> operator/=(T a) { return *this = *this / a; }
	void operator()(T a, T b) { x = a, y = b; }

	operator point1<double>() const {
		return point1<double>((double)x, (double)y);
	}
	operator point1<float>() const {
		return point1<float>((float)x, (float)y);
	}
	operator point1<int>() const {
		return point1<int>((int)x, (int)y);
	}
	operator point1<short>() const {
		return point1<short>((short)x, (short)y);
	}

	point1<T> reverse() { return point1<T>(y, x) }
};

//�ʍ��W�^
template<class T>
class point2 {

	T point2<T>::arc() {

		return ((T)(atan((e.y - s.y)*1.0 / (e.x - s.x))));
	}

	template<class U>
	bool isin_x(point1<T> point, point2<U> line) {
		if ((((double)p2.s.x <= (double)p1.x && (double)p2.e.x >= (double)p1.x) ||
			((double)p2.e.x <= (double)p1.x && (double)p2.s.x >= (double)p1.x)) &&
			(((double)p2.s.y <= (double)p1.y && (double)p2.e.y >= (double)p1.y) ||
			((double)p2.e.y <= (double)p1.y && (double)p2.s.y >= (double)p1.y)))return true;
		else return false;
	}
public:
	point1<T> s, e;

	point2() {
		s = 0, e = 0;
	}
	point2(point1<T> point) {
		s = point, e = point;
	}
	point2(T sx, T sy, T ex, T ey) {
		s.x = sx, s.y = sy, e.x = ex, e.y = ey;
	}
	point2(point1<T> s, point1<T> e) {
		this->s = s, this->e = e;
	}
	point2(const point2<T> &point) {
		s = point.s, e = point.e;
	}

	point1<T> operator=(point1<T> a) {
		s = a, e = a;
		return a;
	}
	point1<T> operator[](int index) {
		switch (index) {
		case 0: return s;
		case 1: return point1<T>(e.x, s.y);
		case 2: return e;
		case 3: return point1<T>(s.x, e.y);
		default:return point1<T>(-1, -1);
		}
		return p;
	}
	T operator=(T a) {
		s = a, e = a;
		return a;
	}
	point2<T> operator+(point1<T> a) {
		return point2<T>(s + a, e + a);
	}
	point2<T> operator-(point1<T> a) {
		return point2<T>(s - a, e - a);
	}
	point2<T> operator+(point2<T> a) {
		return point2<T>(s + a.s, e + a.e);
	}
	point2<T> operator-(point2<T> a) {
		return point2<T>(s - a.s, e - a.e);
	}
	point2<T> operator*(T a) {
		return point2<T>(s * a, e * a);
	}
	point2<T> operator+(T a) {
		return point2<T>(s + a, e + a);
	}
	point2<T> operator-(T a) {
		return point2<T>(s - a, e - a);
	}

	point2<T> operator+=(point1<T> a) {
		s += a, e += a;
		return *this;
	}
	point2<T> operator-=(point1<T> a) {
		s -= a, e -= a;
		return *this;
	}
	point2<T> operator+=(point2<T> a) {
		s += a.s, e += a.e;
		return *this;
	}
	point2<T> operator-=(point2<T> a) {
		s -= a.s, e -= a.e;
		return *this;
	}
	point2<T> operator*=(T a) {
		s *= a.s, e *= a.e;
		return *this;
	}
	point2<T> operator+=(T a) {
		s += a.s, e += a.e;
		return *this;
	}
	point2<T> operator-=(T a) {
		s -= a.s, e -= a.e;
		return *this;
	}
	void operator()(T a, T b, T c, T d) {
		s = point1<T>(a, b);
		e = point1<T>(c, d);
	}

	operator point2<double>() const
	{
		return point2<double>((double)s.x, (double)s.y, (double)e.x, (double)e.y);
	}
	operator point2<float>() const
	{
		return point2<float>((float)s.x, (float)s.y, (float)e.x, (float)e.y);
	}
	operator point2<int>() const
	{
		return point2<int>((int)s.x, (int)s.y, (int)e.x, (int)e.y);
	}
	operator point2<short>() const
	{
		return point2<short>((short)s.x, (short)s.y, (short)e.x, (short)e.y);
	}

	//�������擾
	double length() {
		return sqrt(pow((e.x - s.x), 2) + pow((e.y - s.y), 2));
	}

	//�p�x���擾
	double angle() {
		if (s.x <= e.x && s.y <= e.y) {

			return (arc());
		}
		if (s.x > e.x) {

			return (arc() + PI);
		}
		if (s.x <= e.x && s.y > e.y) {

			return (arc() + PI * 2);
		}

		return 0;
	}

	//�x�N�g���̎擾
	point1<T> vec() {

		return point1<T>(e.x - s.x, e.y - s.y);
	}

	//�@���x�N�g�����擾
	point1<T> norm() {
		return point1<T>(s.y - e.y, e.x - s.x);
	}

	//�����_�̍��W
	point1<T> crossPoint(point2<T> line) {
		double
			l1 = ((e.y - s.y) * 1.0) / (e.x - s.x),
			l2 = ((line.e.y - line.s.y) * 1.0) / (line.e.x - line.s.x),
			c1 = ((-l1 * s.x) + s.y) * 1.0,
			c2 = ((-l2 * line.s.x) + line.s.y) * 1.0;

		if (l1 != l2) {

			return point1<T>((T)((c2 - c1) / (l1 - l2)), (T)(((c1 * l2) - (c2 * l1)) / (l2 - l1)));
		}
		return s;
	}

	//��������
	bool isec(point2<T> line) {
		point1<T> point = crossPoint(line);

		if (isin_x(point, *this) && isin_x(point, line)) {

			return true;
		}
		return false;
	}

	//��`�̈悲�ƈړ�
	void adjust(point1<T> point, int point_num) {
		point1<T> size(e.x - s.x, e.y - s.y);

		switch (point_num) {

		case BOTTOM:
			s = point1<T>(point.x - size.x / 2, point.y - size.y);
			e = point1<T>(point.x + size.x / 2, point.y);
			break;
		case LEFT:
			s = point1<T>(point.x, point.y - size.y / 2);
			e = point1<T>(point.x + size.x, point.y + size.y / 2);
			break;
		case RIGHT:
			s = point1<T>(point.x - size.x, point.y - size.y / 2);
			e = point1<T>(point.x, point.y + size.y / 2);
			break;
		case TOP:
			s = point1<T>(point.x - size.x / 2, point.y);
			e = point1<T>(point.x + size.x / 2, point.y + size.y);
			break;
		case LEFT & TOP:
			s = point1<T>(point.x, point.y);
			e = point1<T>(point.x + size.x, point.y + size.y);
			break;
		case RIGHT & TOP:
			s = point1<T>(point.x - size.x, point.y);
			e = point1<T>(point.x, point.y + size.y);
			break;
		case RIGHT & BOTTOM:
			s = point1<T>(point.x - size.x, point.y - size.y);
			e = point1<T>(point.x, point.y);
			break;
		case LEFT & BOTTOM:
			s = point1<T>(point.x, point.y - size.y);
			e = point1<T>(point.x + size.x, point.y);
			break;
		}
	}

	//s->e�����ɑ΂��_�����E�ǂ���ɂ���̂�(false:�� true:�E)
	bool lorr(point1<T> point) {
		double ang = point2<T>((T)s.x, (T)s.y, (T)point.x, (T)point.y).angle() - (double)angle();

		if (ang >= 0. && ang < PI) {

			return true;
		}
		return false;
	}
};

//�ɍ��W
class polar {
public:
	double angle;
	double distanse;

	polar() {
		angle = 0.;
		distanse = 0.;
	}

	polar(double ang, double dis) {
		angle = ang;
		distanse = dis;
	}

	point1<double> fix() {

		return point1<double>(distanse * cos(angle), distanse * sin(angle));
	}
};

template<class T, class U>
bool isin(point1<T> point, point2<U> line) {
	if (
		(((double)line.s.x <= (double)point.x && (double)line.e.x >= (double)point.x) ||
		((double)line.e.x <= (double)point.x && (double)line.s.x >= (double)point.x)) &&
		(((double)line.s.y <= (double)point.y && (double)line.e.y >= (double)point.y) ||
		((double)line.e.y <= (double)point.y && (double)line.s.y >= (double)point.y))
		)return true;

	else return false;
}

//target��rad��]������
template<class T>
point1<T> rot(point1<T> origin, point1<T> target, double rad) {

	point1<T> point = target - origin;

	return(
		point1<T>(
		(T)(cos(rad) * point.x - sin(rad) * point.y + origin.x),
			(T)(sin(rad) * point.x + cos(rad) * point.y + origin.y)
			));
}

//�_�Ɛ����̋���
template<class T, class U>
double dis(point1<T> point, point2<U> line) {

	//�_�Ɠ_�̋���
	double length_s = point2<double>(point, line.s).length(),
		length_e = point2<double>(point, line.e).length();

	//��{�p�x�̈�ɕϊ�
	point2<double> Hline = line - line.s;
	point1<double> Point = point - line.s;

	Hline = point2<U>(point1<U>(), rot(Hline.s, Hline.e, -line.angle()));
	Point = rot(point1<double>(), Point, -line.angle());


	//��������
	if (Hline.s.x <= Point.x && Point.x <= Hline.e.x) {

		return (double)(ABS(Point.y));
	}
	else if (length_s < length_e) {

		return length_s;
	}
	else {

		return length_e;
	}
	return -1;
}

//�_�Ɛ����̋���
template<class T, class U>
double dis(point2<T> line, point1<U> point) {

	//�_�Ɠ_�̋���
	double
		length_s = point2<double>(point, line.s).length(),
		length_e = point2<double>(point, line.e).length();

	//��{�p�x�̈�ɕϊ�
	point2<double> Hline = line - line.s;
	point1<double> Point = point - line.s;

	//�p�x��0�x�Ƀ��Z�b�g
	Hline = point2<U>(point1(), rot(Hline.s, Hline.e, -line.angle()));
	Point = rot(point1<double>(), Point, -line.angle());


	//��������
	if (Hline.s.x <= Point.x && Point.x <= Hline.e.x) {

		return (double)(ABS(Point.y));
	}
	else if (length_s < length_e) {

		return length_s;
	}
	else {

		return length_e;
	}
	return -1;
}

//�͏�̐�������
template<class T>
point1<T> field(T force, double angle) {

	return point1<T>((T)(force * cos(angle)), (T)(force * sin(angle)));
}

//e������ratio�̊�������������(s:0 �� e:1)
template<class T>
point1<T> fix(point1<T> s, point1<T> e, double ratio) {

	point1<T> size((T)((e.x - s.x) * ratio), (T)((e.y - s.y) * ratio));

	return (s + size);
}

//e������s����̋����ɌŒ肷��
template<class T>
point1<T> fix(point1<T> s, point1<T> e, T distance) {

	point1<T> dist(point2<double>(s, e).length() * cos((double)distance), point2<double>(s, e).length() * sin((double)distance));

	return (s + (point1<T>)dist);
}
/*
//���͌n�N���X(��DxLib�K�{)
class Input {

	//�L�[�̓��͏��
	char key_input[256];

	//�}�E�X���͏��
	int mouse_input;

	//�}�E�X���͗���
	int mouse_input_old;

public:

	int mouse_input_time;		//�}�E�X�̓��͎���
	int mouse_detach;
	point1<int> mouse_point;	//�}�E�X�̍��W
	int key[256];				//�L�[�{�[�h�̓��͎���

	//�}�E�X���͏�Ԏ擾
	void getMouseState();

	//�L�[�{�[�h���͏�Ԏ擾
	void getKeyState();
};
*/


#define update_mouse() _update_mouse(GetMousePoint, GetMouseInput, GetMouseWheelRotVol)
#define update_key() _update_key(GetHitKeyStateAll)

//�}�E�X�|�C���^
class Mouse {
public:
	point1<int> s_point;		//�h���b�O�J�n�ʒu
	point1<int> e_point;		//�h���b�O�I���ʒu
	point1<int> point;			//�}�E�X�|�C���^���W
	int push[2];				//0:LEFT  1:RIGHT  push����
	bool detach[2] = { false };	//�f�^�b�`�t���O
	int wheel = 0;				//�}�E�X�z�C�[��
};

//�L�[�{�[�h
class Key {
public:
	int value[256];			//�L�[���͎���
};

//���͊Ǘ��n
class Input {

public:
	static Mouse mouse;
	static Key key;

	//�}�E�X�����X�V
	static void _update_mouse(
		int (*GetMousePoint)(int *, int *),
		int (*GetMouseInput)(),
		int (*GetMouseWheelRotVol)(int));

	//�L�[�{�[�h���͏����X�V
	static void _update_key(int (*GetHitKeyStateAll)(char *));
};


typedef std::vector<point1<int>> FixedNode;
typedef std::vector<polar> PolarNode;

template<class T>
class FixedPolygonObj {

	//�m�[�h����(x-y���)
	FixedNode point;

public:

	//�����f�[�^
	point2<T> operator[](int num) {
		return point2<T>(point[num], point[num + 1]);
	}

	//�m�[�h�̊i�[
	void push(point1<T> point) {
		this->point.push_back(point);
	}

	//�m�[�h�̍폜
	void pop(point1<T> point) {
		for (std::vector<point1<T>>::iterator it = this->point.begin(); it != this->point.end(); it++) {

			if (*it == point) {

				this->point.erase(it);

				return;
			}
		}
	}

	//�m�[�h�����ׂč폜
	void clear() {
		point.clear();
	}

	//�m�[�h���̕ۑ�
	void save(char *filePath) {

		ofstream fout;

		fout.open(filePath, ios::out | ios::binary | ios::trunc);

		if (!fout) {//�G���[����
			cout << "�t�@�C�� file.txt ���J���܂���";
			return;
		}

		for (int i = 0; i < (int)point.size(); i++) {

			fout.write((char *)& point[i], sizeof(point1<T>));
		}

		fout.close();  //�t�@�C�������
	}

	//�m�[�h���̓ǂݎ��
	void load(char *filePath) {
		FILE *fp;
		errno_t error = fopen_s(&fp, filePath, "rb");
		point1 pointbuf;

		if (error) {

			_RPT0(_CRT_WARN, "ERROR : Failed to open the file");
		}
		else {

			clear();
			while (fread(&pointbuf, sizeof(point1<T>), 1, fp)) {

				point.push_back(pointbuf);
			}
			_RPT0(_CRT_WARN, "Successed to open the file");
		}

		fclose(fp);
	}

	//point2���z�z��̐����擾
	unsigned int size_point2() {
		return point.size() - 1;
	}
};

template<class T>
class PolarPolygonObj {

	//�m�[�h����(a-d���)
	PolarNode point;

public:

	//�����f�[�^
	point2<T> operator[](int num) {
		return point2<T>(point[num].fix(), point[num + 1].fix());
	}

	//�m�[�h�̊i�[
	void push(polar point) {
		this->point.push_back(point);
	}

	//�m�[�h�̍폜
	void pop(polar point) {
		for (std::vector<polar>::iterator it = this->point.begin(); it != this->point.end(); it++) {

			if (*it == point) {

				this->point.erase(it);

				return;
			}
		}
	}

	//�m�[�h�����ׂč폜
	void clear() {
		point.clear();
	}
};