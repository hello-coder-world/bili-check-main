# 项目简介

本项目为一个卡片管理系统，支持卡片的添加、删除、查询、修改、价格管理等功能。主要文件包括：

- main.cpp：主程序入口
- addcard.cpp：添加卡片功能
- delcard.cpp：删除卡片功能
- chaxun.cpp：查询卡片功能
- change.cpp：修改卡片信息
- checkcard.cpp：卡片检查功能
- play.cpp：卡片玩法相关
- menu.cpp：菜单界面
- rw.cpp：读写相关功能
- bili.h：主头文件
- opencsv.h：CSV文件操作，开源文件
- card.csv、manager.csv、price.csv：数据存储文件

## 使用说明

1. 编译所有源文件（建议使用 g++ 或 Visual Studio）。
2. 运行 main.cpp，按照菜单提示操作。
3. 数据将自动保存到 CSV 文件中。

## 文件说明

- opencsv.h 为开源文件，负责 CSV 文件的读写操作。
- 其余文件为项目自定义功能模块。

## 贡献与许可

opencsv.h 文件为开源，遵循其原作者的开源协议。其余代码仅供学习和交流使用。

## 联系方式

如有问题或建议，请在项目页面留言或联系作者。
