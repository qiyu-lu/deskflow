# Deskflow Mouse Broadcast

这是一个基于 [Deskflow](https://github.com/deskflow/deskflow) 的个人功能分支。
当前修改位于
[`feature/mouse-broadcast`](https://github.com/qiyu-lu/deskflow/tree/feature/mouse-broadcast)，
并非 Deskflow 官方发布版本。

## 主要改动

- 服务端可以把鼠标移动、按键和滚轮动作广播到选中的已连接客户端。
- 支持通过 GUI 选择目标并开启或关闭广播，也可以配置一个 Toggle 快捷键切换状态。
- 鼠标广播与普通光标跨屏切换互斥：广播期间光标临时保留在服务端，屏幕边缘切换和“切换屏幕”快捷键不会生效。
- 关闭广播后立即恢复普通跨屏移动，并且不会修改用户原有的“锁定光标”配置。

更完整的使用条件和操作步骤请查看
[鼠标广播操作手册](../docs/MouseBroadcastGuide.zh_CN.md)。

## 下载

当前预览版：
[Mouse Broadcast Preview 0.1.0](https://github.com/qiyu-lu/deskflow/releases/tag/mouse-broadcast-v0.1.0)

| 系统 | 下载 |
| --- | --- |
| Windows x64 | [`deskflow-mouse-broadcast-windows-x64.zip`](https://github.com/qiyu-lu/deskflow/releases/download/mouse-broadcast-v0.1.0/deskflow-mouse-broadcast-windows-x64.zip) |
| Ubuntu x64（DEB） | [`deskflow-mouse-broadcast-ubuntu-x64.zip`](https://github.com/qiyu-lu/deskflow/releases/download/mouse-broadcast-v0.1.0/deskflow-mouse-broadcast-ubuntu-x64.zip) |
| Ubuntu x64（Flatpak） | [`deskflow-mouse-broadcast-flatpak-x64.zip`](https://github.com/qiyu-lu/deskflow/releases/download/mouse-broadcast-v0.1.0/deskflow-mouse-broadcast-flatpak-x64.zip) |

下载对应平台的 ZIP 并解压后再安装。请不要选择 Release 页面底部由 GitHub
自动生成的 `Source code (zip)` 或 `Source code (tar.gz)`，它们只包含源代码，不是安装包。

## 上游项目与许可证

- 官方项目：[deskflow/deskflow](https://github.com/deskflow/deskflow)
- 本分支保留 Deskflow 的 [GPL-2.0 许可证及 OpenSSL 例外](../LICENSE)。
