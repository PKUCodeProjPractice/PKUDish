# QT大作业

队名：Coding project practice

## 项目创建参数

创建时使用QtCreator创建，创建时参数如下

- 模板：Qt Widgets Application
- 构建工具：qmake
- 构建套件：Desktop Qt 6.7.0 MinGW 64-bit
- 翻译：添加简体中文（zh_CN）

## git commit要求

- 请检查`.gitignore`文件，可从其他文件获得的文件（如二进制文件、编译过程中的缓存）不要提交。
- 当添加新特性或者修复bug时
  + 在本地新开一个名为`feat/name`或`fixbug/name`的分支，name需要能表示需要添加的功能或修复的bug（可以使用issue编号表示）
  + 在本地编写新特性或修复bug
  + 简单测试特性无误后，提交到本地
  + 同步到GitHub上的远程仓库
  + 提交pull request，然后合并到develop分支，不要合并到master分支
- 当发布时
  + 将develop分支拖到本地，测试有无问题
  + 若无问题，提交pull request，然后合并到master分支
- 请不要在master分支上进行直接的提交或者修改