vex机器人程序写了这么多年，一直没有研究出很好的用于四马达或六马达的底盘控制程序
包括PID控制的直行和陀螺仪控制的转向
所以这里我准备从头开始将其规范化，并写出一个模板供以后的同学们研究和使用
以上。
王时予。

程序结构：
1. UI部分：
--所有含有activity关键字的代码均为UI部分的代码，其中面向主程序接口为onClickListener()，其调用activityControl()实现不同界面间的显示、跳转、与互动。
--activity_loading.cpp用于加载初始化并显示开机画面，其中对外提供activity_loading(string teamNum, bool action)接口，teamNum为队伍名称需大于等于四位，action为是否加载动画。
--activity_main.cpp用于显示主界面并实现交互功能，通过点击不同的位置可以跳转至不同的功能界面。
--activity_autoSelect.cpp用于可见的自动选择，可显示场地俯视图并在选择不同自动时显示机器人起始位置，其初始位置信息需要在autoPreset.h文件中设置，包括起始点位和自动名称。
--activity_motorInfo.cpp用于查看各个电机的信息，包括：转速，旋转角度等。此项功能有待完善。
--activity_sensorValue.cpp用于查看各个传感器输入的信息，包括数字传感器和模拟传感器，模拟传感器也可选择输入的单位。此项功能有待完善。
--activity_robotTest.cpp用于做机器人显示等的各项测试。先将其预设为显示队号动画并注明版本信息等。

2.控制部分：
--控制部分主要由motorControl.cpp代码实现，由motorControl.h提供接口，其中包括开环控制如Move(), Lift()等，也有闭环控制如goForward()等。
--开环控制中主要参数为功率或伏特数，由不同电机功能决定具体单位，但给定数值时都需要在-100~100区间，程序会自动折算；还有另一参数为有预设值的刹车模式选择，当功率值为零时，会读取刹车模式参数的值作为刹车方式进行停止，其预设值为vex::brakeType::brake，当没有进行设定时即为该模式。
--闭环控制中主要参数为power(功率)，target(目标值)和timeLimit(时间限制)。power为电机行进的最大功率限制，target为需要行进的目标值，timeLimit为执行该条语句所限制的最长时间(单位为ms)，当由于到达timeLimit时间而返回时，函数会返回布尔类型false，否则会返回true。
--其中除又关键字gyro的函数为使用陀螺仪进行控制外，其余函数均由电机编码器控制。使用PID控制马达功率。
