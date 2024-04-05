#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

#include "external_renderer_ipc/external_renderer_ipc.h"

int main(int argc, char* argv[])
{
	// MuMu12��װ·��
	auto installPath = L"D:\\MuMuPlayer-12.0";

	// ���ӵ�ʵ���ţ�������MuMu�࿪���Ӳ鿴
	auto targetInstance = 0;

	// ��ʼ����
    auto connection = nemu_connect(L"D:\\MuMuPlayer-12.0", 0);

	if (connection == 0) {
		std::cout << u8"����ʧ�ܣ���ȷ�ϰ�װĿ¼��ȷ���Ҷ�Ӧʵ���Ѿ��򿪡�" << std::endl;
		return 0;
	}

	// ����Ϊ�����÷�
    std::vector<unsigned char> pixels;
	
	bool done = false;
	while (!done)
	{
		// �ȴ����
		std::this_thread::sleep_for(std::chrono::seconds(1));

		// ��׿��Ļ�ţ����û�п���ģ��������ܣ���ԶΪ0
		int displayId = 0;

		// ��ʼ��ͼ
		auto begin = std::chrono::high_resolution_clock::now();
		int width = 0, height = 0;
		// ��ȡ��ͼ��С (buffer_size == 0)
		if (nemu_capture_display(connection, displayId, 0, &width, &height, nullptr) != 0) {
			std::cout << "��ȡ��ͼ��Сʧ��" << std::endl;
			// ������
			break;
		}
		// ׼�����������ڴ�
		pixels.resize(width * height * 4);
		// ��ͼ
		if (nemu_capture_display(connection, 0, (int)pixels.size(), &width, &height, pixels.data()) != 0) {
			// ������
			break;
		}
		auto duration = std::chrono::high_resolution_clock::now() - begin;
		std::cout << "��ͼ��ʱ�� " << 
			std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms" << std::endl;

		// ͼ�������ҵ���߼�
		std::cout << "��ʼ����";
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		std::cout << "-- ���" << std::endl;

		// �������
		if (nemu_input_event_touch_down(connection, displayId, 500, 500) != 0) {
			// ������
			break;
		}
		if (nemu_input_event_touch_up(connection, displayId)) {
			// ������
			break;
		}
	}

    nemu_disconnect(connection);
}

