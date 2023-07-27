#include<iostream>
#include <vector>
#include <corecrt_math_defines.h>
#include <map>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include "fstream"
#include <sstream>
#include <functional>
#include <numeric>
/*
1���ַ����Ƚ�
2������ɽ  ������˹  �������ֵת����Ƕ�ֵ����
3���������  һ�����ݵ��Ƿ���һƬ�����ڵĲ���

*/
//M_PI

struct ptz_angel
{
	float x_p;     // Ŀ���x
	float y_p;    // Ŀ���y
	float x_angle;  // Ŀ�����������ĵ�ĽǶȲ�
	float y_angle;  // Ŀ�����������ĵ�ĽǶȲ�
	float z_zoom;

};

void CBS_PTZ_pixToAngle(ptz_angel ptz, float x_p, float y_p, float& P_, float& T_);
void Get_EEDS_PTZ_Data();
void Get_CBS_PTZ_Data();

void Test_PtInPolygon();
std::vector<cv::Point> Pano_cut(std::string pano_cut_path_);

bool PtInPolygon(cv::Point p, std::vector<cv::Point> pt, int nCount);

void unchar_() 
{
	// unchar �ַ����Ƚ�
	/*
	unchar �ַ����Ƚ� ֮ǰ���� != ���ıȽ�
	*/
	std::string Is_goal = "";
	std::string Is_goal_245 = "CSZ9927";

	unsigned char airport_names[8];
	unsigned char airport_names_245[8];

	std::string Is_goal222 = (char*)airport_names;
	if (!Is_goal222.empty())
	{
		std::cout << "Is_goal: " << Is_goal222 << std::endl;
	}
	// �ֱ�ֵ ���Ƚ� �鿴�Ƿ��ܱȽϳɹ�

	memset(airport_names, 0, sizeof(airport_names));											// ���airport_names �ٸ���airport_namesֵ
	memcpy(airport_names, Is_goal.c_str(), Is_goal.length());									// ���ɻ�����Ű󶨸�airport_names 


	memset(airport_names_245, 0, sizeof(airport_names_245));
	memcpy(airport_names_245, Is_goal_245.c_str(), Is_goal_245.length());

	if (Is_goal != Is_goal_245)
	{
		printf("Is_goal != Is_goal_245!\n");
	}

	if ((char*)airport_names != (char*)airport_names_245) 
	{
		// ����ж��ǲ��ɹ��� ������
		printf("ariprot_names != airport_name_245!\n");
	}

	// Ŀ�ģ� ����unchar��ͬʱ �ж�����ȳɹ� �����뵽�ж�������

	std::string AirportName = (char*)airport_names;
	std::string AirportNames245 = (char*)airport_names_245;

	if (AirportName != AirportNames245)
	{
		printf("AirportNames != AirportNames245!\n");
	}


	if (strncmp((char*)airport_names, (char*)airport_names_245, 8))
	{
		// ��airport_name��airport_name_245����� �򡣡��������ж�
		printf("(char*)ariprot_names != (char*)airport_name_245!\n");
	}
	std::cout << "airport_name: " << airport_names << " ,airport_names_245: " << airport_names_245 << std::endl;


}


void Scale_Pano() 
{
	double x_scale = 0.48387;
	double y_scale = 0.35197;

	int pano_x = 7936;
	int pano_y = 1824;

	int x_test = 3840;
	int y_test = 642;


	int pano_Xscale = x_test / x_scale;
	int pano_Yscale = y_test / y_scale;

	std::cout << "Pano_x: " << pano_Xscale<< " , x_test / x_scale: "<< x_test / x_scale << " , pano_y: " << pano_Yscale << std::endl;

}



/*����ӳ��Ǳ궨 ��������ڵ����� ����������ڵ����ݽ��б궨*/
void Get_CBS_PTZ_Data()
{
	// CBS

		// ��ȡptz������
	/*
	�̶����ʲ��� ������������ҵ�һ���ΪP1,��¼P1�����ص�λ�� ���ʱ����ĽǶȡ�����ֵ PTZ1
	�̶����ʲ��� ת����� ��������ĵ�ת����P1λ���� ��¼��ʱ����ĽǶ� ����ֵ PTZ2
	ͨ����
	PTZ1_P + ^P = PTZ2_P,����� ^p
	PTZ1_T + ^T = PTZ2_T, ����� ^T
	����data1(�������ֵx  �������ֵy  ^p  ^T, Z)
	�ı�x_p, y_p����ֵ ֱ���ҵ�ʹ�� x_degre - ptz.x_angle Ϊ��Сֵ��x����ֵ ��Ϊ���յ�x_pֵ

	z = 10  306   182
	z = 20  365   211
	z = 30  402   220
	z = 40  422   234
	z = 50	425	  241
		z = 60	432	  249
			z = 70	444	  258  ===>����������
				z = 80	448	  248

					z = 90	455	  254

						z = 100	460	  258

							z = 150	464	  258/260/247

								z = 200	462	  251

									z = 300	512	  290	// ������

										z = 400	574	  295
	*/
	std::vector<ptz_angel> PTZ_DATA;


	// ����20
	//ptz_angel data1 = {610, 70, -7.0, 9.4, 20};
	//ptz_angel data2 = {1864, 928, 17.3, -7.2, 20};
	//ptz_angel data3 = {1884, 406, 17.6, 3.0, 20};
	//ptz_angel data4 = {854, 1024, -2.2, -9.9, 20};
	//ptz_angel data5 = {228, 738, -15.4, -3.4, 20};

	// ����10
	//PTZ_DATA.push_back(ptz_angel{1884, 314, 29.7, 8.3, 10});
	//PTZ_DATA.push_back(ptz_angel{546, 890, -14.3, -12.1, 10});
	//PTZ_DATA.push_back(ptz_angel{1874, 126, 29.4, 15.8 ,10});
	//PTZ_DATA.push_back(ptz_angel{84, 880, -29.4,  -10.5,  10});
	//PTZ_DATA.push_back(ptz_angel{80, 708, -28.8, -5.4, 10});
	//PTZ_DATA.push_back(ptz_angel{448, 394, -17.2, 5.1, 10});

	//// ����30
	//PTZ_DATA.push_back(ptz_angel{ 1706, 906, 10.5, -5.0, 30 });
	//PTZ_DATA.push_back(ptz_angel{ 96, 942,-12.3,-5.4, 30 });
	//PTZ_DATA.push_back(ptz_angel{ 1576, 466, 8.8, 1.2, 30 });
	//PTZ_DATA.push_back(ptz_angel{ 1866, 176, 12.5, 5.2, 30 });
	//PTZ_DATA.push_back(ptz_angel{ 1840,  1042, 12.2, -6.7,30 });
	//PTZ_DATA.push_back(ptz_angel{ 114, 130, -11.9, 5.8, 30 });
	//PTZ_DATA.push_back(ptz_angel{ 172, 292, -11.0, 3.3, 30 });

	//// ����40
	//PTZ_DATA.push_back(ptz_angel{ 562,  952, -4.4, -4.7, 40 });
	//PTZ_DATA.push_back(ptz_angel{ 108, 188, -9.3,  3.7, 40 });
	//PTZ_DATA.push_back(ptz_angel{ 1720, 248,  8.3,  3.3,  40 });
	//PTZ_DATA.push_back(ptz_angel{ 1594, 1064,  7.2 ,-5.7,40 });
	//PTZ_DATA.push_back(ptz_angel{ 1794, 964,  9.1, -4.4,40 });
	//PTZ_DATA.push_back(ptz_angel{ 380, 126 ,-6.4,  4.4, 40 });

	//// ����50
	//PTZ_DATA.push_back(ptz_angel{ 128,  58, -7.6 , 4.3, 50 });
	//PTZ_DATA.push_back(ptz_angel{ 1720,  22 , 6.6 ,  4.7, 50 });
	//PTZ_DATA.push_back(ptz_angel{ 1644, 306,  6.3,  2.2, 50 });
	//PTZ_DATA.push_back(ptz_angel{ 294, 72, -6.0,  4.3, 50 });
	//PTZ_DATA.push_back(ptz_angel{ 22, 980 ,-8.1, -3.8,  50 });
	//PTZ_DATA.push_back(ptz_angel{ 1414 ,748,  4.1 ,-2.0 , 50 });

	// ����60
	//PTZ_DATA.push_back(ptz_angel{ 76 , 864 , -6.7 , -2.5 , 60 });
	//PTZ_DATA.push_back(ptz_angel{ 1866 , 802 , 7 , -1.9 , 60 });
	//PTZ_DATA.push_back(ptz_angel{ 226 , 58 , -5.6 , 3.7 , 60 });
	//PTZ_DATA.push_back(ptz_angel{ 870 , 30 , -0.8 , 3.9 , 60 });
	//PTZ_DATA.push_back(ptz_angel{ 96 , 466 , -6.7 , 0.6 , 60 });
	//PTZ_DATA.push_back(ptz_angel{ 226 , 1044 , -5.7 , -3.9 , 60 });

	//// ����70

	//PTZ_DATA.push_back(ptz_angel{ 1706 , 314 , 5 , 1.6 , 70 });
	//PTZ_DATA.push_back(ptz_angel{ 50 , 90 , -6 , 3 , 70 });
	//PTZ_DATA.push_back(ptz_angel{ 696 , 970 , -1.9 , -2.9 , 70 });
	//PTZ_DATA.push_back(ptz_angel{ 1552 , 1032 , 3.9 , -3.3 , 70 });
	//PTZ_DATA.push_back(ptz_angel{ 1274 , 1044 , 2.1 , -3.5 , 70 });
	//PTZ_DATA.push_back(ptz_angel{ 1238 , 360 , 1.8 , 1.2 , 70 });


	//// ����80
	//PTZ_DATA.push_back(ptz_angel{ 384 , 186 , -3.4 , 2 , 80 });
	//PTZ_DATA.push_back(ptz_angel{ 292 , 932 , -3.9 , -2.3 , 80 });
	//PTZ_DATA.push_back(ptz_angel{ 1810 , 998 , 5 , -2.6 , 80 });
	//PTZ_DATA.push_back(ptz_angel{ 1822 , 38 , 4.9 , 2.9 , 80 });
	//PTZ_DATA.push_back(ptz_angel{ 128 , 1028 , -5 , -2.8 , 80 });
	//PTZ_DATA.push_back(ptz_angel{ 386 , 322 , -3.5 , 1.2 , 80 });



	//// ����90
	//PTZ_DATA.push_back(ptz_angel{ 1220 , 68 , 1.3 , 2.5 , 90 });
	//PTZ_DATA.push_back(ptz_angel{ 254 , 78 , -3.8 , 2.4 , 90 });
	//PTZ_DATA.push_back(ptz_angel{ 1560 , 982 , 3.3 , -2.3 , 90 });
	//PTZ_DATA.push_back(ptz_angel{ 1790 , 492 , 4.3 , 0.2 , 90 });
	//PTZ_DATA.push_back(ptz_angel{ 956 , 954 , 0 , -2.2 , 90 });
	//PTZ_DATA.push_back(ptz_angel{ 84 , 112 , -4.5 , 2.2 , 90 });



	//// ����100

	//PTZ_DATA.push_back(ptz_angel{ 330 , 878 , -3.1 , -1.6 , 100 });
	//PTZ_DATA.push_back(ptz_angel{ 76 , 78 , -4.2 , 2.2 , 100 });
	//PTZ_DATA.push_back(ptz_angel{ 1828 , 182 , 4.1 , 1.7 , 100 });
	//PTZ_DATA.push_back(ptz_angel{ 286 , 232 , -3.2 , 1.5 , 100 });
	//PTZ_DATA.push_back(ptz_angel{ 1256 , 998 , 1.4 , -2.2 , 100 });
	//PTZ_DATA.push_back(ptz_angel{ 706 , 962 , -1.2 , -2 , 100 });


	//// ����150

	PTZ_DATA.push_back(ptz_angel{ 1708 , 60 , 2.4 , 1.5 , 150 });
	PTZ_DATA.push_back(ptz_angel{ 1686 , 36 , 2.3 , 1.6 , 150 });
	PTZ_DATA.push_back(ptz_angel{ 594 , 1000 , -1.2 , -1.5 , 150 });
	PTZ_DATA.push_back(ptz_angel{ 1852 , 754 , 2.9 , -0.6 , 150 });
	PTZ_DATA.push_back(ptz_angel{ 1046 , 146 , 0.3 , 1.2 , 150 });
	PTZ_DATA.push_back(ptz_angel{ 1270 , 886 , 1 , -1.1 , 150 });
	PTZ_DATA.push_back(ptz_angel{ 434 , 442 , -1.7 , 0.2 , 150 });
	//
	//// ����200

	//PTZ_DATA.push_back(ptz_angel{ 890 , 1008 , -0.2 , -1.1 , 200 });
	//PTZ_DATA.push_back(ptz_angel{ 366 , 134 , -1.5 , 1 , 200 });
	//PTZ_DATA.push_back(ptz_angel{ 1632 , 1030 , 1.6 , -1.1 , 200 });
	//PTZ_DATA.push_back(ptz_angel{ 1650 , 110 , 1.6 , 1 , 200 });
	//PTZ_DATA.push_back(ptz_angel{ 706 , 690 , -0.6 , -0.5 , 200 });
	//PTZ_DATA.push_back(ptz_angel{ 1572 , 600 , 1.5 , -0.1 , 200 });


	//// ����300

	//PTZ_DATA.push_back(ptz_angel{ 1678 , 28 , 1.3 , 0.9 , 300 });
	//PTZ_DATA.push_back(ptz_angel{ 1670 , 912 , 1.3 , -0.6 , 300 });
	//PTZ_DATA.push_back(ptz_angel{ 402 , 342 , -1 , 0.3 , 300 });
	//PTZ_DATA.push_back(ptz_angel{ 18 , 908 , -1.6 , -0.6 , 300 });
	//PTZ_DATA.push_back(ptz_angel{ 560 , 952 , -0.8 , -0.8 , 300 });
	//PTZ_DATA.push_back(ptz_angel{ 286 , 508 , -1.2 , 0 , 300 });


	//// ����400

	//PTZ_DATA.push_back(ptz_angel{ 58 , 46 , -1.4 , 0.7 , 400 });
	//PTZ_DATA.push_back(ptz_angel{ 1648 , 14 , 1.1 , 0.7 , 400 });
	//PTZ_DATA.push_back(ptz_angel{ 1436 , 338 , 0.7 , 0.3 , 400 });
	//PTZ_DATA.push_back(ptz_angel{ 1450 , 984 , 0.7 , -0.6 , 400 });
	//PTZ_DATA.push_back(ptz_angel{ 1544 , 44 , 0.8 , 0.7 , 400 });
	////PTZ_DATA.push_back(ptz_angel{ });


	float x_in = -1000;
	float y_in = -500;

	int k_count = 0, j_count = 0;
	float x_end = -100000, y_end = -10000;

	while (true)
	{
		int k_i = 0, j_i = 0;

		std::map<int, float> x_map;
		std::map<int, float> y_map;

		for (int i = 0; i < PTZ_DATA.size(); i++)
		{
			float p_ = 0.0, t_ = 0.0;
			CBS_PTZ_pixToAngle(PTZ_DATA[i], x_in, y_in, p_, t_);
			if (abs(p_) < 0.09)
			{
				//std::cout << "x_in: " << x_in << std::endl;
				x_map.insert(std::make_pair(k_i, x_in));
				k_i += 1;
			}
			if (abs(t_) < 0.1)
			{
				//std::cout << "y_in: " << y_in << std::endl;
				y_map.insert(std::make_pair(j_i, y_in));
				j_i += 1;

			}

		}

		if (k_i >= PTZ_DATA.size() && k_i >= k_count)
		{
			k_count = k_i;
			x_end = x_in;
			std::cout << "------ The best args_X: " << x_end << std::endl;
		}

		if (j_i >= PTZ_DATA.size() && j_i >= j_count)
		{
			j_count = j_i;
			y_end = y_in;
			std::cout << "The best args_Y: " << y_end << std::endl;

		}

		x_in += 0.5;
		y_in += 0.5;

		if (x_in >= 1000)
		{
			break;
		}
	}


}
void Get_EEDS_PTZ_Data()
{
	// ��ȡptz������
/*
�̶����ʲ��� ������������ҵ�һ���ΪP1,��¼P1�����ص�λ�� ���ʱ����ĽǶȡ�����ֵ PTZ1
�̶����ʲ��� ת����� ��������ĵ�ת����P1λ���� ��¼��ʱ����ĽǶ� ����ֵ PTZ2
ͨ����
PTZ1_P + ^P = PTZ2_P,����� ^p
PTZ1_T + ^T = PTZ2_T, ����� ^T
����data1(�������ֵx  �������ֵy  ^p  ^T, Z)
�ı�x_p, y_p����ֵ ֱ���ҵ�ʹ�� x_degre - ptz.x_angle Ϊ��Сֵ��x����ֵ ��Ϊ���յ�x_pֵ

Z= 4  -110  -51

Z = 8  -144 -80.5

Z= 12  -161  -93

Z = 16   -167  -93

Z= 20   -173   -98

Z = 40	 -181	-99

Z= 60    -189  -106

Z = 80   -183  -105
*/
	std::vector<ptz_angel> PTZ_DATA;


	// ���� 4
	PTZ_DATA.push_back(ptz_angel{ 14 , 954 , 29.2 ,9.9 , 4 });
	PTZ_DATA.push_back(ptz_angel{ 1856 , 164 , -25.9 , -12.6 , 4 });
	PTZ_DATA.push_back(ptz_angel{ 670 , 1012 ,  8.7, 13.5  , 4 });
	PTZ_DATA.push_back(ptz_angel{ 1624 , 866 ,  -23.2,  7.6, 4 });

	//// ���� 8
	//PTZ_DATA.push_back(ptz_angel{ 1790 , 10 , -15.3 , -10.3 , 8 });
	//PTZ_DATA.push_back(ptz_angel{ 360 , 42 , 11.5 , -9.1 , 8 });
	//PTZ_DATA.push_back(ptz_angel{ 248 , 906 , 13.3 , 6.9 , 8 });
	//PTZ_DATA.push_back(ptz_angel{ 1694 , 974 , -14.4 , 7.7 , 8 });

	//// ���� 12
	//PTZ_DATA.push_back(ptz_angel{ 122 , 6 , 11.5 , -7.7 , 12 });
	//PTZ_DATA.push_back(ptz_angel{ 306 , 932 , 9.5 , 5.5 , 12 });
	//PTZ_DATA.push_back(ptz_angel{ 1830 , 142 , -12 , -5.7 , 12 });
	//PTZ_DATA.push_back(ptz_angel{ 906 , 1020 , 0.9 , 6.8 , 12 });

	//// ���� 16
	//PTZ_DATA.push_back(ptz_angel{ 224 , 146 , 7.9 , -4.1 , 16 });
	//PTZ_DATA.push_back(ptz_angel{ 1688 , 14 , -7.7 , -5.7 , 16 });
	//PTZ_DATA.push_back(ptz_angel{ 1564 , 984 , -6.7 , 4.7 , 16 });
	//PTZ_DATA.push_back(ptz_angel{ 78 , 918 , 9.9 , 4.1 , 16 });

	//// ���� 20
	//PTZ_DATA.push_back(ptz_angel{ 106 , 42 , 7.8 , -4.4 , 20 });
	//PTZ_DATA.push_back(ptz_angel{ 1836 , 144 , -7.9 , -3.7 , 20 });
	//PTZ_DATA.push_back(ptz_angel{ 58 , 1002 , 8 , 4.3 , 20 });
	//PTZ_DATA.push_back(ptz_angel{ 1724 , 966 , -7 , 3.8 , 20 });

	//// ���� 40
	//PTZ_DATA.push_back(ptz_angel{ 1798 , 26 , -3.9 , -2.5 , 40 });
	//PTZ_DATA.push_back(ptz_angel{ 102 , 96 , 4 , -1.9 , 40 });
	//PTZ_DATA.push_back(ptz_angel{ 100 , 1018 , 4.1 , 2.3 , 40 });
	//PTZ_DATA.push_back(ptz_angel{ 1260 , 1000 , -1.5 , 2.2 , 40 });

	//// ���� 60
	//PTZ_DATA.push_back(ptz_angel{ 180 , 30 , 2.5 , -1.6 , 60 });
	//PTZ_DATA.push_back(ptz_angel{ 1592 , 998 , -2.1 , 1.4 , 60 });
	//PTZ_DATA.push_back(ptz_angel{ 1864 , 140 , -3 , -1.4 , 60 });
	//PTZ_DATA.push_back(ptz_angel{ 134 , 842 , 2.7 , 1 , 60 });

	//// ���� 80
	//PTZ_DATA.push_back(ptz_angel{ 1726 , 110 , -1.9 , -1.1 , 80 });
	//PTZ_DATA.push_back(ptz_angel{ 260 , 974 , 1.6 , 1 , 80 });
	//PTZ_DATA.push_back(ptz_angel{ 1660 , 966 , -1.7 , 1 , 80 });
	//PTZ_DATA.push_back(ptz_angel{ 132 , 920 , 1.9 , 0.9 , 80 });



	float x_in = -1000;
	float y_in = -1000;

	int k_count = 0, j_count = 0;
	float x_end = -100000, y_end = -10000;

	while (true)
	{
		int k_i = 0, j_i = 0;

		std::map<int, float> x_map;
		std::map<int, float> y_map;

		for (int i = 0; i < PTZ_DATA.size(); i++)
		{
			float p_ = 0.0, t_ = 0.0;
			CBS_PTZ_pixToAngle(PTZ_DATA[i], x_in, y_in, p_, t_);

			if (abs(p_) < 0.5)
			{
				//std::cout << "x_in: " << x_in << std::endl;
				x_map.insert(std::make_pair(k_i, x_in));
				k_i += 1;
			}
			if (abs(t_) < 0.5)
			{
				//std::cout << "y_in: " << y_in << std::endl;
				y_map.insert(std::make_pair(j_i, y_in));
				j_i += 1;

			}

		}

		if (k_i >=2 && k_i >= k_count)
		{
			k_count = k_i;
			x_end = x_in;
			std::cout << "------ The best args_X: " << x_end << std::endl;
		}

		if (j_i >= 2 && j_i >= j_count)
		{
			j_count = j_i;
			y_end = y_in;
			std::cout << "The best args_Y: " << y_end << std::endl;

		}

		x_in += 0.5;
		y_in += 0.5;

		if (x_in >= 1000)
		{
			break;
		}
	}

}

void CBS_PTZ_pixToAngle(ptz_angel ptz, float x_p, float y_p, float& P_, float& T_)
{
	float dkx = 960.0 / tan(x_p / ptz.z_zoom / 180.0 * M_PI);
	float dky = 540.0 / tan(y_p / ptz.z_zoom / 180.0 * M_PI);


	float x_degre;
	float y_degre;

	float d_x = ptz.x_p - 960.0;
	float d_y = ptz.y_p - 540.0;


	if (d_y > 0) {
		y_degre = -atan(-(540.0 - ptz.y_p) / dky) * 180.0 / M_PI;
	}
	if (d_y <= 0) {
		y_degre = atan(-(ptz.y_p - 540.0) / dky) * 180.0 / M_PI;

	}
	if (d_x > 0) {
		x_degre = atan((ptz.x_p - 960.0) / dkx) * 180.0 / M_PI;
	}
	if (d_x <= 0) {
		x_degre = atan((ptz.x_p - 960.0) / dkx) * 180.0 / M_PI;
	}

	P_ = x_degre - ptz.x_angle;
	T_ = y_degre - ptz.y_angle;


	//std::cout<<"^x: "<<x_degre - ptz.x_angle<<" ,^y: "<<y_degre - ptz.y_angle << " ,pixe_x:  " << ptz.x_p << " ,pixe_y: "<<ptz.y_p << " ,x_degre: " << x_degre<<" ,real_xDegre: "<<ptz.x_angle << " ,y_degre:" << y_degre << " ,real_yDegre: " << ptz.y_angle << std::endl;
}



void Test_PtInPolygon() 
{
	// 
	std::vector<cv::Point> Pano_cut_ = Pano_cut("./13_1_VLC_XY_cutrange3840.txt");
	cv::Point in_range(554, 290);
	bool ret = PtInPolygon(in_range, Pano_cut_, Pano_cut_.size());

	// ���ݴ���txt�������� ����1   ���ݲ�����txt�������� ����0
	std::cout << "ret: " << ret << std::endl;
}


std::vector<cv::Point> Pano_cut(std::string pano_cut_path_)
{
	std::ifstream infile;
	std::vector<cv::Point> Pano_cut_;

	infile.open(pano_cut_path_, std::ios::in);
	if (!infile.is_open())
		std::cout << "open file failure" << std::endl;

	int int_num, x, y;
	cv::Point ps;

	while (infile.peek() != EOF) {

		infile >> int_num >> x >> y;
		ps.x = x;
		ps.y = y;
		Pano_cut_.push_back(ps);
		infile.get();
	}
	infile.close();

	std::cout << "read pano cut: " << Pano_cut_.size() << " " << Pano_cut_[0] << std::endl;

	return Pano_cut_;

}
// �ж�һ�����Ƿ��ڶ���η�Χ��
bool PtInPolygon(cv::Point p, std::vector<cv::Point> pt, int nCount)
{
	int nCross = 0;
	for (int i = 0; i < nCount; i++)
	{
		cv::Point p1 = pt[i];
		cv::Point p2 = pt[(i + 1) % nCount];
		if (p1.y == p2.y)
		{
			if (p.y == p1.y && p.x >= std::min(p1.x, p2.x) && p.x <= std::max(p1.x, p2.x))
				return true;
			continue;
		}
		if (p.y < std::min(p1.y, p2.y) || p.y > std::max(p1.y, p2.y))
			continue;
		double x = (double)(p.y - p1.y) * (double)(p2.x - p1.x) / (double)(p2.y - p1.y) + p1.x;

		if (x > p.x)
			nCross++;
		else if (x == p.x)
			return true;
	}
	if (nCross % 2 == 1)
		return true;
	return false;
}

struct poolArea {
	cv::Rect area;
	std::vector<int> status;
};

bool inRect(int x, int y, cv::Rect r)
{
	bool ret = false;
	if (x <= 0 || x >= 3840 || y <= 0 || y >= 896)
		ret = false;
	if (x > r.x && x < r.x + r.width && y > r.y && y < r.y + r.height)
		ret = true;
	return ret;
}

void Test_std_accumulate() 
{
	poolArea area1, area2;

	area1.area = cv::Rect(1700 / 2, 750 / 2, 200, 200);
	area2.area = cv::Rect(2600 / 2, 900 / 2, 300, 200);

	std::vector<poolArea> areas{ area1, area2 };

	int x = 2000;
	int y = 360;

	while (true) 
	{
		x -= 5;
		y += 1.5;

		for (auto& aa : areas)
		{
			// areasΪ��ǰ�滮�ľ��� ����ʱ�״������ڹ滮��ȫ�������� �򷵻�true ���¹滮������ǰ״̬ ����ʾ�״�����˸�����
			if (inRect(x, y, aa.area))
			{
				//if (aa.status.size() > 50)
				//	aa.status.erase(aa.status.begin());
				aa.status.push_back(1);															// һ�������Ӧ��һ��״̬��
				std::cout << " x��" << x << " ,y�� " << y << " , area: " << aa.area.x << std::endl;
			}
		}


		if (x <100 || y > 1975) 
		{
			std::cout << "End x: " << x << " ,y: " << y << std::endl;
			break;

		}
	}


	auto maxPositionback = std::accumulate(areas.back().status.begin(), areas.back().status.end(), 0);			// ��һ���滮��ȫ������Ŀ�ʼ�ͽ���״̬
	auto maxPositionfront = std::accumulate(areas.front().status.begin(), areas.front().status.end(), 0);		// �ڶ����滮��ȫ������Ŀ�ʼ�ͽ���״̬
	// �����������

	std::cout << "maxBack: " << maxPositionback << " ,maxfront: " << maxPositionfront << std::endl;


	if (maxPositionback > 0 && maxPositionfront > 0)
	{
		
		std::cout << "22_maxBack: " << maxPositionback << " ,maxfront: " << maxPositionfront << std::endl;
	}
}
int main()
{
	//unchar_();

	// unchar ת�� string Ȼ��Ƚ϶����Ƿ���ͬ
	//Scale_Pano();

	//Get_EEDS_PTZ_Data();
	//
	//Get_CBS_PTZ_Data();
	//Test_PtInPolygon();

	//Test_std_accumulate();

	std::cout << "add git: " << std::endl;
	std::string ds = "Down";

	if (ds.compare("None") != 0)
	{
		std::cout<<" iiii: "<<std::endl;
	}
	return 0;
}
