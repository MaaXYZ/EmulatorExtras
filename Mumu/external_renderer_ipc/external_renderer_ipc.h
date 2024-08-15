#pragma once

#ifdef NEMUEXTERNALRENDERERIPC_EXPORTS
#define EXTERNALRENDERERAPI __declspec(dllexport)
#else
#define EXTERNALRENDERERAPI
#endif

#ifdef __cplusplus
extern "C" {
#endif

	/*
	* @path: emulator install path, utf16 format.
	* @index: multi-instance index num
	* @return: >0 when connect success, 0 when fail.
	*/
	EXTERNALRENDERERAPI int nemu_connect(const wchar_t* path, int index);

	/*
	* disconnect handle;
	*/
	EXTERNALRENDERERAPI void nemu_disconnect(int handle);

	/*
	* get pkg display id when 'keep-alive' is on. when 'keep-alive' is off, always return 0 no matter what @pkg is.
	* when pkg close and start again, you should call this function again to get a newer display id.
	* Call this function after the @pkg start up.
	* @handle: value returned from nemu_connect();
	* @pkg   : pkg name, utf-8 format.
	* @appIndex: if @pkg is a cloned pkg, @appIndex means cloned index, the main clone is 0, the first clone is 1, and so on.
	* @return: <0 means fail, check if the pkg is started or pkg name is correct;
	*          >= 0 means valid display id.
	*/
	EXTERNALRENDERERAPI int nemu_get_display_id(int handle, const char* pkg, int appIndex);

	/*
	* call this function twice to get valid pixels data.
	* first you set @buffer_size to 0, function will return valid width and heigth to @width and @height.
	* then you set 4*@width*@height to @buffer_size, and call this function again, @pixels will contain valid data when function success.
	* 
	* @handle: value returned from nemu_connect();
	* @displayid: display id, return value from nemu_get_display_id().
	* @buffer_size: ref above.
	* @width,@height: valid width and height.
	* @pixels: valid pixels data.
	* @return: 0 when capture success, > 0 when fail.
	*/
	EXTERNALRENDERERAPI int nemu_capture_display(int handle, unsigned int displayid, int buffer_size, int *width, int *height, unsigned char* pixels);

	/*
	* @handle: return value from connect_server function.
	* @buf: text buffer, utf8 format.
	* @isze: buffer size
	* return: 0 means success, > 0 means fail
	*/
	EXTERNALRENDERERAPI int nemu_input_text(int handle, int size, const char* buf);

	/*
	* @displayid: display id, current only 0 is valid.
	* @return: 0 means success, > 0 means fail.
	*/
	EXTERNALRENDERERAPI int nemu_input_event_touch_down(int handle, int displayid, int x_point, int y_point);

	/*
	* @return: 0 means success, > 0 means fail.
	*/
	EXTERNALRENDERERAPI int nemu_input_event_touch_up(int handle, int displayid);

	/*
	* @key_code: ref in https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h
	* @return: 0 means success, > 0 means fail.
	*/
	EXTERNALRENDERERAPI int nemu_input_event_key_down(int handle, int displayid, int key_code);

	/*
	* used to release keyboard event.
	* @return: 0 means success, > 0 means fail.
	*/
	EXTERNALRENDERERAPI int nemu_input_event_key_up(int handle, int displayid, int key_code);

	/*
	* when you want multi touch, you can call nemu_input_event_finger_touch_down 
	* and nemu_input_event_finger_touch_up api multi times to simulate.
	*/

	/*
	* press your finger.
	* @finger_id: which finger you press down, range is [1, 10].
	* @x_point, @y_point: x, y value.
	* @return: 0 when success, >0 when fail.
	*/
	EXTERNALRENDERERAPI int nemu_input_event_finger_touch_down(int handle, int displayid, int finger_id, int x_point, int y_point);

	/*
	* raise your finger.
	* @finger_id: which finger you press up, range is [1, 10].
	* @return: 0 when success, >0 when fail.
	*/
	EXTERNALRENDERERAPI int nemu_input_event_finger_touch_up(int handle, int displayid, int slot_id);


#ifdef __cplusplus
}
#endif