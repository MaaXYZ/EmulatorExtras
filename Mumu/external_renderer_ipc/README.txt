
针对模拟器开启后台保活后，高速截图接口失效的问题，我们添加了一个新API来解决该问题：

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

该接口可以拿到已启动 app 的 display id。

接口中的 @appIndex 说明：由于模拟器支持单模拟器内的应用多开，开启保活后，同一应用的不同多开实例对应不同的 dispaly id。@appIndex 用来应对这种情况：0 表示主分身，1 表示第一个副本分身，以此类推。

该接口使用时需要注意的：
1，app 必须是已启动的状态；
2，app 重启，该接口需要重新调用，来获取最新的 display id；
