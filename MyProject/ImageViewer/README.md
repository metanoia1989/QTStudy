# 图片查看器
UI仿照[ImageClass](https://github.com/d2phap/ImageGlass)这个软件，后期实现自己的功能。  

## Github 上Qt写的图片查看组件
* qt5-image-viewer https://github.com/blastak/qt5-image-viewer
* A minimalistic Qt image viewer widget, with zoom and pixel color picking. https://github.com/palacaze/image-viewer
* photo qt https://github.com/luspi/photoqt`

# 功能开发
## 第一阶段 图片展示操作
* [ ] 工具栏在程序宽度变小时，那个menu按钮被先隐藏了，我要做到始终不隐藏这个按钮。
* [ ] 底部thumbnail，鼠标悬浮样式，选中之后的样式，背景颜色，padding。 
* [ ] 点击底部thumbnail，切换图片。
* [ ] 图片预览区域，背景颜色，一个是透明，一个是白色。
* [ ] 图片预览区域，鼠标拖动图片，可以左右移动
* [ ] 上一页、下一页切换按钮，当鼠标移动到右侧自动显示下一页按钮，左侧显示上一页。要大、颜色浅、醒目。
* [ ] 顶部标题栏透明效果 - 这个可能有点难，可选，还有看看能不能修改整个应用的模糊透明。

## 第二阶段 图片简单操作
* [ ] 文件夹拖拽，或者打开图片，可以预览整个文件夹的图片。
* [ ] 标题随打开的文件动态变化，展示图片路径和图片简略信息
* [ ] 图片操作，放大缩小、高度对齐、宽度对齐、旋转、镜像
* [ ] 刷新重新读取文件夹并且重新读取图片
* [ ] 图片复制、粘贴、删除操作

## 第三阶段 图片进阶操作
* [ ] 图片裁剪操作
* [ ] 图片批注绘制操作
* [ ] 图片拼接、压缩、转换操作
* [ ] 图片滤镜处理、模糊处理、对比度、亮度等操作

# 软件说明
底部 thumbnail 是一个预览图的滚动区域，高125px，每张图片宽113px。   
底部 thumbnail 可能需要一个QList属性作为容器，无论是读取还是删除咋样的。
初始打开图片的高宽 1267x760(无缩略图) 1267x634(有底部缩略图)，打开图片直接拉伸高度即可。    

# BUG记录修复
* [x] 4.11 menu按钮点击显示菜单时，第一次而后面几次的位置不一致，原因是QMenu的宽度变化了。
 * 解决了这个问题，原因是的确是popup之后QMenu的大小会变化，需要从sizeHint()获取正确高度宽度。
* [x] 4.11 工具栏和菜单栏都显示了QAction的图标，但是我只想在工具栏显示。
 * QAction::setIconVisibleInMenu() 可以隐藏菜单栏的图标显示。