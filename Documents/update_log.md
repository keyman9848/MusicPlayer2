**简体中文 | [English](https://github.com/zhongyang219/MusicPlayer2/blob/master/Documents/update_log_en-us.md)**<br>
# MusicPlayer2 更新日志
## V2.67 (2019/11/28)
* 新增桌面歌词功能。
* 新增播放列表工具栏。
* 新增cue音轨可以添加到播放列表。
* 新增调整播放速度的功能。
* 修正了一些bug。
* 其他细节方面的改进。
## V2.66 (2019/08/03)
* 新增播放列表功能，可自由创建和编辑播放列表。
* 新增歌曲红心的功能。
* 修正部分flac音频标签获取不正确的问题。
* 新增文件关联功能。
* 修正窗口大小改变时会导致GDI句柄泄漏的问题。
* 新增声音淡入淡出效果。
* 修正了一些bug。
* 其他细节方面的改进。
## V2.65 (2019/05/25)
* 新增在搜索框显示频谱分析的功能
* 新增累计听歌时间统计的功能
* 新增浮动播放列表的功能
* 新增总是置顶的功能
* 新增崩溃时显示错误信息并生成dump文件的功能
* 字体设置增加粗体、斜体和下划线的样式设置
* 新增创建播放控制快捷方式的功能
* 新增x64的支版本
* 其他细节方面的改进
## V2.64 (2019/02/16)
* 界面调整，界面中的播放控制按钮和进度条美化。
* 新增隐藏/显示播放列表的功能。
* 新增隐藏/显示菜单栏的功能。
* 新增响应多媒体按键的功能。
* 小娜搜索框歌词显示效果优化。
* 新增全屏显示的功能。
* 其他界面细节方面的调整。
* 其他细节方面的改进。
## V2.63 (2019/01/06)
* 主界面重新设计，外观更加简洁美观。仍然可以快速切换回以前的界面
* 迷你模式界面重新设计，使用和主界面相同的风格
* 优化获取系统主题颜色的功能，获取实际的系统主题颜色而不是窗口标题栏的颜色
* 修正一个由于GDI句柄泄漏导致程序运行一段时间崩溃的问题
* 新增全局快捷键的设置
* 增加通知区图标，关闭主窗口时可以最小化到通知区而不是退出程序
* 新增多语言支持，增加英语
* 其他细节方面的改进
## V2.62 (2018/09/08)
* 新增深色UI主题
* 频谱分析显示效果优化，增加顶端柱形
* 新增歌词翻译的原文双行显示
* 对于有翻译的歌词，执行歌词繁简转换时，只转换译文
* 修正设置了背景高斯模糊后，有时会导致背景为黑色的问题
* 新增选择播放设备的功能
* 修正下载的歌词时有时翻译在前面的问题
* 修正某些情况下获取的mp3标签不正确的问题
* 新增格式转换支持cue分轨
* 修正歌词结果中显示的歌曲信息如果含有“,”，则会导致显示不正确的问题
* 其他细节方面的改进
## V2.61 (2018/07/28)
* 新增bass播放插件，可支持几乎所有格式的音频格式
* 新增 MIDI 音乐播放功能，可加载音色库
* 优化频谱分析显示效果，增加频谱柱形的条数
* 新增格式转换功能，可将任意音频格式转换成 WAV、MP3、WMA和OGG
* 新增背景图片高斯模糊效果，选项设置中增加相关设置
* 新增没有专辑封面时显示默认的背景图片
* 新增播放列表可选中多个项目
* 其他细节方面的改进
## V2.60 (2018/07/08)
* 修正当小娜被禁用时，小娜搜索框上的歌词显示位置不正确的问题
* 新增：设置小娜搜索框歌词背景颜色的功能
* 匹配本地歌词文件时使用全词匹配，解决了有时会匹配到错误的歌词的问题
* 新增：“选择路径”列表中的右键菜单，增加“清除无效路径”功能
* 新增：随机播放时可向前回溯的功能
* 修正当程序首次运行时，迷你模式中播放列表默认展开的问题
* 新增：小娜搜索框图标跟随音乐节奏跳动的功能
* 优化音频标签的获取，解决了标签信息乱码或获取到的信息不正确的问题
* 优化了内嵌专辑封面的获取，解决了部分文件无法获取内嵌专辑封面的问题
* 新增：播放列表快速搜索的功能
* 新增：优先获取ID3V2标签的选项
* 新增：专辑封面在线下载功能
* 新增：自动下载专辑封面和歌词的功能
* 新增：自动检查更新的功能
## V2.59 (2018/03/11)
* 修正播放flac等扩展名不是3个字符的文件时无法加载歌词的问题
* 增加flac格式标签和专辑封面的支持
* 修正文件夹中有多个cue文件时可能会无法解析的问题
* 增加从外部图片获取专辑封面的功能
* 歌词编辑界面增加工具栏
* 增加APE格式的支持
* 修正播放cue文件时无法记住上次播放位置的问题
一些细节方面的改进
## V2.58 (2018/02/07)
* 增加专辑封面显示
* 选项设置中增加专辑封面相关设置
* 新增在Cortana搜索框中显示专辑封面
* 新增迷你模式中显示专辑封面
* 新增专辑封面另存为功能
* 一些细节方面的改进
## V2.57 (2018/02/04)
* 歌词右键菜单中增加“打开歌词文件位置”菜单项
* 新增歌曲标签可写入（目前仅支持MP3格式）
* 增加歌词繁简转换功能
* 增加小娜搜索框歌词双行显示功能
## V2.56 (2017/12/17)
* 小娜搜索框歌词适配白色搜索框
* 增加选择路径对话框可调整大小
* 播放列表加载过程中，禁用播放列表控件，并将鼠标状态改为“忙”
* 右击窗口时在歌曲信息区域和歌词区域弹出不同的右键菜单
* 当歌词文件夹不存在时，禁用“保存到歌词文件夹”单选按钮
* 选择路径对话框中，列表适应主题颜色
* 调整播放列表控件的样式
* 其他细节优化
