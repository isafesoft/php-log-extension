
<?php
 echo "<pre>";
//print_r(get_loaded_extensions());
//打印扩展加载
print_r(get_extension_funcs('mytest'));
//传参测试，返回 double 3.3
echo php_mytest('参数1', 'Param2') . '<br>';

//计时开始，微秒精度
echo mlBeginSpan();//('My first php extension', 'xx');
//do something .... 
sleep(1.2);

//获取时间间隔
echo "<br><b>Time span:</b>" . mlGetSpan() . "<br>" ;

//获取标准的uuid串，36 bytes len
echo "<br><b>uuid:</b>" . mlGetUUID() . "<br>" ;

//write array
$arrtest = array(1=>"a3341a 4", 'b'=> "hi jiantaob", 3=> 1);
$res =  mlogError($arrtest);
echo '<br><br> write info log error code: ' . $res;

echo "</pre>";
?>
<html><body><h1>It works!</h1></body></html>
