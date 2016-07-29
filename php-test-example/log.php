<?php
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
//include_once("Logger.class.php");

/*
echo '
<form action="" method="post">
  First name: <input type="text" name="fname"><br>
  Last name: <input type="text" name="lname"><br>
  <input type="submit" value="Submit">
</form>
';
*/

//生成log实例
$log = Logger::getInstance();

//设置追踪UUID
$log->setMUID();

//一个跳转页面，用来测试跳转后的UUID是否可用
echo '<a href="log2.php">Test Track</a>';








?>
