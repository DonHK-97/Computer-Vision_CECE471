#include "wl.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Cluster ���� ���� �̹��� ���ϸ�, ���� * ���� �ػ󵵸� �ֻ�ܿ��� ���� �� ����
#define CLUSTER_K 8
#define WIDTH 800
#define HEIGHT 540
#define RAW "Golf.raw"

// wl.cpp ���� ������ min �Լ��Դϴ�.
inline int min(int a, int b) { return (a < b ? a : b); }

void main()
{
	// while ���� ���Ḧ �˸� ��ȣ�� �� cluster �� �Ѱ�, cluster �� �󵵼��� �����ϴ� 2���� �迭�Դϴ�.
	int center_sum[CLUSTER_K][2] = { 0 };
	int flag = 0;

	CharImage Input(RAW, WIDTH, HEIGHT);

	// ù ȸ���� Centroid �� ������ K �� �ȼ� ������ �����Ǹ�, �� Cluster �� ��� ������ ��ü �˴ϴ�.
	BYTE centroids[CLUSTER_K];
	BYTE temp_buffer, temp_diff;

	srand(time(NULL));

	// ���� Centroid �� �����մϴ�.
	for (int i = 0; i < CLUSTER_K; i++)
	{
		int number = rand();
		centroids[i] = { Input.pixel(number % WIDTH, number % HEIGHT) };
	}
	
	// ȸ�� �� ������ Centroid �� ���� �� Centroid �� ����, �޶����� �ʾҴٸ� �������� �Ǵ��մϴ�.
	while (1) 
	{
		int temp_checker = centroids[0];
		
		for (int dx = 0; dx < WIDTH; dx++)
			for (int dy = 0; dy < HEIGHT; dy++)
			{
				temp_buffer = Input.pixel(dx, dy);
				BYTE temp_min = 255;
				int temp_loc = 0;

				for (int i = 0; i < CLUSTER_K; i++)
				{
					// Centroid ( mean �� ) ���� �ȼ� ���� ���̸� ���ϰ�, �ּҸ� �������� ������ �ش� ��ŵ�ϴ�.
					temp_diff = abs(centroids[i] - temp_buffer);
					temp_min = min(temp_diff, temp_min);
					if (temp_diff == temp_min) temp_loc = i;
				}
				// ���� �� �ȼ� �� ����� �� ���� ������ ����� ����Ҷ� ����մϴ�.
				center_sum[temp_loc][0] += temp_buffer;
				center_sum[temp_loc][1] += 1;

				// ���� ��ȣ�� �޾�������, ��� �ȼ��� �ش� �ϴ� ������ ������� ��ü �մϴ�.
				if (flag) Input.pixel(dx, dy) = centroids[temp_loc];
			}
		// ���� ��ȣ�� �������� ������ ȸ���� ���� �� ���� Ȯ�� �ܰ��, ������ ��ġ�� ����˴ϴ�.
		if (flag) break;
		for (int i = 0; i < CLUSTER_K; i++) centroids[i] = center_sum[i][0] / center_sum[i][1];

		// ���� ��ȣ�Դϴ�.
		if (temp_checker == centroids[0]) flag = 1;
	}
	Input.Save("Out_Golf8.raw");
}