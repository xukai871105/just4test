
just4test
=========

仅仅用于测试，熟悉Git

1. 建立仓库
2. 本地克隆
3. 本地提交
4. 更新代码库

    git add
    git commit
    git push

# 操作流程 #
## 建立仓库 方法1 ##
1. 初始化git仓库 : git init;
2. 提交改变到缓存 : git commit -m 'description';
3. 增加远程代码仓库地址 : git remote add origin https://github.com/xukai871105/just4test.git;
4. 提交代码： git push -u origin master;

## 建立仓库 方法2 ##
1. 克隆项目到本地 :git clone https://github.com/xukai871105/just4test.git , 注意克隆时直接在仓库根目录即可, 不必再创建项目根目录;
2. 添加文件 :git add ./* , 将目录中所有文件添加;
3. 提交缓存 :git commit -m 'description';
4. 提交到远程GitHub仓库 : git push -u origin master;

## 同步代码 ##
1. 与远程仓库同步 :git pull;
2. 查看文件变更 : git status;
3. 提交代码到本地缓存 : git commit -m 'description';
4. 提交代码到远程仓库 :git push;

## 分支操作 ##
1. 列出分支 : git branch;
2. 切换分支 : git checkout master;
3. 提交分支 : git push origin branch_name;
4. 删除分支 : git branch -d branch_name , 强制删除分支 git branch -D branchName;
4. 合并分支 : git merge branch_name;

