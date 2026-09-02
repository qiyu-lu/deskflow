# Deskflow Input Broadcast

这是一个基于 [Deskflow](https://github.com/deskflow/deskflow) 的个人功能分支。
当前修改位于
[`feature/mouse-broadcast`](https://github.com/qiyu-lu/deskflow/tree/feature/mouse-broadcast)，
并非 Deskflow 官方发布版本。

## 主要改动

- 服务端可以把鼠标移动、点击、滚轮和原始键盘按键广播到选中的客户端。
- 鼠标与键盘广播可以独立开关，并支持 GUI、状态提示和 Toggle 快捷键。
- 鼠标广播期间光标保留在服务端；键盘广播在光标离开服务端时自动关闭。
- 键盘广播面向相同键盘布局，不保证不同输入法之间的文本完全一致。

更完整的使用条件和操作步骤请查看
[键鼠广播使用指南](../docs/InputBroadcastGuide.zh_CN.md)。

## 下载

当前预览版：
[Deskflow Input Broadcast Preview 0.2.0](https://github.com/qiyu-lu/deskflow/releases/tag/input-broadcast-v0.2.0)

| 系统 | 下载 |
| --- | --- |
| Windows x64 | [`deskflow-input-broadcast-v0.2.0-windows-x64.zip`](https://github.com/qiyu-lu/deskflow/releases/download/input-broadcast-v0.2.0/deskflow-input-broadcast-v0.2.0-windows-x64.zip) |
| Ubuntu x64（DEB） | [`deskflow-input-broadcast-v0.2.0-ubuntu-x64.zip`](https://github.com/qiyu-lu/deskflow/releases/download/input-broadcast-v0.2.0/deskflow-input-broadcast-v0.2.0-ubuntu-x64.zip) |
| Ubuntu x64（Flatpak） | [`deskflow-input-broadcast-v0.2.0-flatpak-x64.zip`](https://github.com/qiyu-lu/deskflow/releases/download/input-broadcast-v0.2.0/deskflow-input-broadcast-v0.2.0-flatpak-x64.zip) |

下载对应平台的 ZIP 并解压后再安装。请不要选择 Release 页面底部由 GitHub
自动生成的 `Source code (zip)` 或 `Source code (tar.gz)`，它们只包含源代码，不是安装包。

## 上游项目与许可证

- 官方项目：[deskflow/deskflow](https://github.com/deskflow/deskflow)
- 本分支保留 Deskflow 的 [GPL-2.0 许可证及 OpenSSL 例外](../LICENSE)。
