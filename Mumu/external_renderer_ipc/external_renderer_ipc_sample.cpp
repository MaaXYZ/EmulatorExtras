#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

#include "external_renderer_ipc/external_renderer_ipc.h"

int main(int argc, char* argv[])
{
	// MuMu12安装路径
	auto installPath = L"D:\\MuMuPlayer-12.0";

	// 连接的实例号，可以在MuMu多开器钟查看
	auto targetInstance = 0;

	// 开始连接
    auto connection = nemu_connect(L"D:\\MuMuPlayer-12.0", 0);

	if (connection == 0) {
		std::cout << u8"连接失败，请确认安装目录正确，且对应实例已经打开。" << std::endl;
		return 0;
	}

	// 以下为样例用法
    std::vector<unsigned char> pixels;
	
	bool done = false;
	while (!done)
	{
		// 等待间隔
		std::this_thread::sleep_for(std::chrono::seconds(1));

		// 安卓屏幕号，如果没有开启模拟器保活功能，永远为0
		int displayId = 0;

		// 开始截图
		auto begin = std::chrono::high_resolution_clock::now();
		int width = 0, height = 0;
		// 获取截图大小 (buffer_size == 0)
		if (nemu_capture_display(connection, displayId, 0, &width, &height, nullptr) != 0) {
			std::cout << "获取截图大小失败" << std::endl;
			// 错误处理
			break;
		}
		// 准备像素数据内存
		pixels.resize(width * height * 4);
		// 截图
		if (nemu_capture_display(connection, 0, (int)pixels.size(), &width, &height, pixels.data()) != 0) {
			// 错误处理
			break;
		}
		auto duration = std::chrono::high_resolution_clock::now() - begin;
		std::cout << "截图耗时： " << 
			std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms" << std::endl;

		// 图像分析等业务逻辑
		std::cout << "开始分析";
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		std::cout << "-- 完毕" << std::endl;

		// 发出点击
		if (nemu_input_event_touch_down(connection, displayId, 500, 500) != 0) {
			// 错误处理
			break;
		}
		if (nemu_input_event_touch_up(connection, displayId)) {
			// 错误处理
			break;
		}
	}

    nemu_disconnect(connection);
}

