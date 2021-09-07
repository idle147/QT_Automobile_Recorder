--=============================================================================================================
--            Function      :    创建用户信息表和文件路径表
--            Auhtor        :    余阳鑫
--            Create Date   :    2020-10-31
--            Description   :    数据库名: recordDB
--                               相关的表: 用户信息表、文件路径表
--=============================================================================================================
--            2020-10-31    :    创建用户信息表usr: 
--                                               主键用户账号:uId(VARCHAR), 用户名:uName(VARCHAR), 密码:pwd(VARCHAR), 状态:state(INT)
--
--                               创建文件路径表source: (已更名为fileTable)
--                                               主键:id(INT), 外键:uId(VARCHAR), 日期字符串:date(TEXT), 
--                                               文件类型:type(VARCHAR)(照片:photo, 视频:video, 视频封面:screencover, 视频截图:screenshot)
--                                               文件路径:path(TEXT) 
--
--                               设置的资料setTable:
--                                               主键:sType(INTEGER), 0表示没有设置过, 1表示设置过
--                                               视频存储位置:videoPath(VARCHAR)
--                                               图片存储位置:picPath(VARCHAR)
--                                               采集时间间隔:time(char(9))
--                                               摄像头配置:  camSet(VARCHAR)
--
--             2020-11-10   :   把表source更名为fileTable
--                              添加文件路径表fileTable项:frameNum 表示视频总帧数, 规则:整数, 不为空, 默认值为0                         
--=============================================================================================================
.open recordDB                                      --打开数据库
PRAGMA foreign_keys = ON;                           --启动外键约束

--创建用户信息表usr:
DROP TABLE IF EXISTS usr;
CREATE TABLE IF NOT EXISTS usr
(
    uId  VARCHAR  PRIMARY KEY  NOT NULL,              --主键uId,     规则:递增
    uName   VARCHAR(20)        NOT NULL,              --定义用户名,   规则:中英文, 长度限制最长20位 
    pwd     VARCHAR(20)        NOT NULL,              --定义密码,     规则:密码, 长度限制8-16位
    state   INTEGER DEFAULT 1  NOT NULL               --定义状态,     规则:正常状态为1(默认), 异常状态为0
);

--创建文件路径表fileTable
DROP TABLE IF EXISTS fileTable; 
CREATE TABLE IF NOT EXISTS fileTable
(
    id   INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, --定义ID为文件路径表主键,  规则:递增
    uId  INTEGER REFERENCES usr(uId) NOT NULL,       --外键uId:uId,            规则:与用户信息表的uID相关联
    type VARCHAR(20) NOT NULL,                       --文件类型:type(VARCHAR), 规则:照片:photo, 视频:video, 视频截图:screenshot
    data TEXT        NOT NULL,                       --日期data
    path TEXT        NOT NULL,                       --文件路径:path(TEXT),    规则:文件路径生成
    frameNum  INTEGER  DEFAULT 0 NOT NULL            --设置视频的总帧数, 规则:整数, 不为空, 默认值为0
);

--创建文件路径表setTable
DROP TABLE IF EXISTS setTable; 
CREATE TABLE IF NOT EXISTS setTable
(
    sType   INTEGER PRIMARY KEY  DEFAULT 0 NOT NULL,  --定义标签, 0表示没有设置过, 1表示设置过, 默认为0
    videoPath VARCHAR(100)   NOT NULL,                --文件路径:videoPath(TEXT),    规则:文件路径生成
    picPath   VARCHAR(100)   NOT NULL,                --文件类型:picPath(VARCHAR), 规则:照片:photo, 视频:video, 视频截图:screenshot
    time      char(9)       NOT NULL,                 --日期time
    camSet    VARCHAR(100)   NOT NULL                 --摄像头配置: 设置摄像头的信息
);

--插入默认的值
INSERT into usr VALUES('admin1234', '李大壮',  '123456', 1); --用户名为admin1234，密码为123456
INSERT into usr VALUES('root12345', '孙小胖',  '123456', 1); --用户名为root12345，密码为123456
INSERT into setTable VALUES(0, '../fileOut/video',  '../fileOut/picture', '0', 'NULL');


--转存数据库
.dump recordDB
