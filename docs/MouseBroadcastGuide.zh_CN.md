# Deskflow 鼠标广播操作手册

本文适用于 Ubuntu 作为主机（Server）、Windows 作为客户端（Client）的测试环境。

## 1. 下载新安装包

从个人仓库最新一次成功的 `Package test builds` 工作流下载并解压：

- Windows：`deskflow-mouse-broadcast-windows-x64`，使用其中的 `.msi`。
- Ubuntu DEB：`deskflow-mouse-broadcast-ubuntu-x64`，使用其中的 `.deb`。
- Ubuntu Flatpak：`deskflow-mouse-broadcast-flatpak-x64`，使用其中的 `.flatpak`。

建议两台电脑安装同一次构建生成的软件包。

## 2. 卸载旧版

卸载前先退出托盘中的 Deskflow，避免新旧进程或后台服务同时运行。正常卸载会保留用户配置。

### Windows

打开“设置 → 应用 → 已安装的应用”，找到 Deskflow 并选择“卸载”。如果卸载后旧的 Deskflow 服务仍在运行，重启 Windows 后再安装新版。

### Ubuntu DEB 版

打开终端执行：

```bash
sudo apt remove deskflow
```

### Ubuntu Flatpak 版

可以先用以下命令确认是否安装了 Flatpak 版：

```bash
flatpak info org.deskflow.deskflow
```

如果 Deskflow 正在运行，先从托盘退出，然后卸载：

```bash
flatpak uninstall org.deskflow.deskflow
```

不要添加 `--delete-data`，这样可以保留原有 Flatpak 用户数据。

## 3. 安装新版

### Windows

双击下载的 `.msi`，按照安装向导完成安装。建议使用 MSI 安装版，不使用便携版，以保证后台服务、UAC 和登录界面支持正常工作。

### Ubuntu

DEB 和 Flatpak 二选一，不要同时运行两个版本。

#### 安装 DEB

进入 `.deb` 所在目录并安装。以下命令要求当前目录中只有一个匹配的新安装包：

```bash
cd ~/Downloads/deskflow-mouse-broadcast-ubuntu-x64
sudo apt install ./deskflow-mouse-broadcast-*.deb
deskflow-core --version
```

如果解压目录名称不同，请相应修改 `cd` 路径。

#### 安装 Flatpak

进入 `.flatpak` 所在目录并安装：

```bash
cd ~/Downloads/deskflow-mouse-broadcast-flatpak-x64
flatpak install --user ./deskflow-*-linux-x86_64.flatpak
flatpak run org.deskflow.deskflow
```

如果解压目录或文件名不同，请相应修改路径。

## 4. 配置和使用鼠标广播

1. Ubuntu 选择 Server 模式，Windows 选择 Client 模式，并先确认普通鼠标、键盘连接正常。
2. Ubuntu 打开 `Configure Server → Hotkeys`。
3. 如果启用了 `Advanced → Use a server config file`，先关闭它，否则 GUI 中的热键设置不会生效。
4. 新建快捷键，例如 `Ctrl+Shift+F8`。
5. 选中该快捷键，在 Actions 中新建 `Control mouse broadcasting` 动作。
6. 选择 `Toggle mouse broadcasting`，并勾选需要同步的 Windows 客户端；可以选择多个客户端。
7. 保存配置。必要时停止并重新启动 Deskflow Core。
8. 将光标留在 Ubuntu 主屏，按一次快捷键开启广播，再按一次关闭广播。

开启后应同步绝对位置、左/右/中键点击和滚轮。不同分辨率之间会按屏幕比例映射坐标。

## 5. 多显示器保护

- 鼠标广播要求 Ubuntu 主机只有一个处于系统“启用”状态的显示器。
- 主机已经是多显示器时，开启请求会被拒绝。
- 广播过程中启用第二个显示器时，广播会立即关闭，并释放客户端上可能保持按下的鼠标键。
- 恢复单显示器后不会自动重新广播，需要再次按快捷键开启。
- 仅关闭显示器电源可能仍会被系统视为已启用；应在系统显示设置中禁用该显示器或断开连接。

## 6. 注意事项

- 不要同时运行旧版和新版 Deskflow，否则可能发生端口、服务或 IPC socket 冲突。
- Flatpak 与 DEB 的配置目录相互隔离，切换安装方式后通常需要重新配置 Server/Client、屏幕布局和广播快捷键。
- 广播仅在光标位于 Ubuntu 主机时工作；测试时避免从屏幕边缘切换到客户端，必要时启用光标锁定。
- Windows 客户端名称必须与 GUI 中选择的目标名称一致。
- Ubuntu X11 可重点测试点击和滚轮修复；可用 `echo $XDG_SESSION_TYPE` 查看当前会话类型。
- 如果快捷键没有反应，先检查是否正在使用外部配置文件，并查看日志中的 `mouse broadcasting` 信息。
