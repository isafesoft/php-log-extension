<?php
/**
 * 日志扩展测试demo
 * MarkXu
 * 2016-06-01
 */
namespace Home;

use Moshlog\Logger;
include_once('Moshlog/LogPublic.php');

spl_autoload_register(function ($class) {
    if ($class) {
        $file = str_replace('\\', '/', $class);
        $file .= '.class.php';
        echo $file;
        if (file_exists($file)) {
            include $file;
        }
    }
});


$log = Logger::getInstance();

//
//1,测试精确计时，毫秒
//
//计时开始，微秒精度
echo mlBeginSpan();//('My first php extension', 'xx');
//do something .... 
sleep(1.2);
//获取时间间隔
echo "<br><b>Time span:</b>" . mlGetSpan() . "（毫秒）<br>" ;

//
//2，获取日志配置文件存放目录
//
echo mlGetConfPath();

//
//3，获取日志存放目录
//
echo mlGetSavePath();


//
//4，获取日志配置项
//
echo mlGetConf();

//=========日志生成、写入测试===============
//
//5,测试日志包头生成
//你可以根据日志的类型，获取到不同的数组，
//具体开关请参考LogPublic.php内的开关定义
//默认获取所有，
$arrLog = Logger::mlGetLogArr();

//可以在这里随意修改，
//譬如将msg内容重新填充,如下
$arrLog['msg'] = json_encode(array('paymentMethod' => 'zhifubao', 'money' => '3.5$'));

//
//5，测试日志写入
//写入日志文件，返回0表示成功，非0表示错误码
//支持
echo mlogError($arrLog);

//
//，支持以下几种log，
//
//mlogError
//mlogInfo
//mlogDebug
//mlogCritical
//mlogAlert
//mlogEmergency

//打印扩展加载
//print_r(get_extension_funcs('mytest'));
//传参测试，返回 double 3.3
//echo php_mytest('参数1', 'Param2') . '<br>';




?>