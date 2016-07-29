<?php

namespace Moshlog;
include_once('LogPublic.php');
/**
 * 日志辅助类
 * MarkXu
 * 2016-05-31
 * @author >
 */
class Logger
{


    private static $logPath = '/tmp';
    private static $logLevel = LOG_ERR;
    private static $maps = array(
        LOG_DEBUG   => 'debug',
        LOG_INFO    => 'info',
        LOG_NOTICE  => 'notice',
        LOG_WARNING => 'warning',
        LOG_ERR     => 'err',
        LOG_CRIT    => 'crit',
        LOG_ALERT   => 'alert',
        LOG_EMERG   => 'emerg',
    );

    private function __construct()
    {
        //
    }

    private function __clone()
    {
        //
    }

    /**
     * 获取单例
     * @return Logger
     */
    public static function getInstance()
    {
        static $instance = NULL;
        if (is_null($instance)) {
            $instance = new Logger();
        }
        return $instance;
    }

    /*
    * 设置链路追踪MUID，
    * 
     */
    public static function setMUID()
    {
        setcookie(UUID_STR_TAG, mlGetUuid());
    }

    /**
     * 获取日志外包字段
     * MarkXu
     * return: string
     */
    public static function mlGetLogArr($type = ML_ALL)
    {
       $arrStr = array();
        if ($type & ML_UUID)
        {
            $arrStr[UUID_STR_TAG] = empty($_COOKIE[UUID_STR_TAG]) ? ML_STR_ARROW : $_COOKIE[UUID_STR_TAG];
        }

        if($type & ML_RIP)
        {
            $arrStr['rip'] = empty($_SERVER['SERVER_ADDR']) ? ML_STR_ARROW : $_SERVER['SERVER_ADDR'];
        }

        if($type & ML_UA)
        {
            $arrStr['ua'] = empty($_SERVER['HTTP_USER_AGENT']) ? ML_STR_ARROW : $_SERVER['HTTP_USER_AGENT'];
        }

        if($type & ML_REFER)
        {
            $arrStr['refer'] = empty($_SERVER['HTTP_REFERER']) ? ML_STR_ARROW : $_SERVER['HTTP_REFERER'];
        }

        if($type & ML_UID)
        {
            $arrStr['uid'] = 'userID';//ML_STR_ARROW;
        }

        if($type & ML_HID)
        {
            $arrStr['hid'] = 'hid';//ML_STR_ARROW;
        }

        if($type & ML_QSTRING)
        {
            $arrStr['qstr'] = empty($_SERVER['QUERY_STRING']) ? ML_STR_ARROW : $_SERVER['QUERY_STRING'];
            if($_POST)
            {
                $arrStr['qstr'] .= '|'; //分割get 和 post串
                $arrStr['qstr'] .= http_build_query($_POST);
            }
        }

        if($type & ML_MODULE)
        {
            $arrStr['mod'] = self::mlGetStackTrace();
        }

        if($type & ML_MSG)
        {
            $arrStr['msg'] = ML_STR_ARROW;
        }

        return $arrStr;
    }

    /**
     * 打印当前堆栈的file/function name/args
     * MarkXu
     * @return string
     */
    public static function mlGetStackTrace()
    {

        $dbg = debug_backtrace(1, 4); //追踪4层
        $dbg = array_reverse($dbg);
        //$dbg = array_pop($dbg);

        $trace = $dbg;
        $length = count($trace);
        $result = array();

        for ($i = 0; $i < $length; $i++)
        {
            $result[] = ($i + 1)  . ')' . $trace[$i]['file'] . '(' .
                $trace[$i]['line'] . ')' . SP_STACK_API .
                $trace[$i]['function']  . SP_STACK_API .
                json_encode($trace[$i]['args']); // replace '#someNum' with '$i)', set the right ordering
        }

        return implode("\n", $result);
    }



    /**
     * 获取HTTP_HOST
     * @return mixed
     */
    private static function getHost()
    {
        static $host;
        if (!$host) {
            if ($_SERVER['HTTP_HOST']) {
                $host = $_SERVER['HTTP_HOST'];
            } else {
                $host = 'script';
            }
        }
        return $host;
    }

    /**
     * 获取客户端Ip
     * @return string|int
     */
    public static function getClientIp()
    {
        static $ip;
        if ($ip) {
            return $ip;
        }
        if (isset($_SERVER["HTTP_X_FORWARDED_FOR"])) {
            $ip = $_SERVER["HTTP_X_FORWARDED_FOR"];
        } elseif (isset($_SERVER["HTTP_CLIENT_IP"])) {
            $ip = $_SERVER["HTTP_CLIENT_IP"];
        } elseif (isset($_SERVER["HTTP_CLIENTIP"])) {
            $ip = $_SERVER["HTTP_CLIENTIP"];
        } elseif (isset($_SERVER["HTTP_X_REAL_IP"])) {
            $ip = $_SERVER["HTTP_X_REAL_IP"];
        } elseif (isset($_SERVER["REMOTE_ADDR"])) {
            $ip = $_SERVER["REMOTE_ADDR"];
        } else {
            $ip = '127.0.0.1';
        }
        $pos = strpos($ip, '|');
        if ($pos) {
            $ip = substr($ip, 0, $pos);
        }
        $ip = trim($ip);
        return $ip;
    }


    /**
     * 获取服务器IP
     * @return string
     */
    public static function getServerIp()
    {
        static $ip;
        if ($ip) {
            return $ip;
        }
        if (isset($_SERVER['SERVER_ADDR'])) {
            $ip = $_SERVER['SERVER_ADDR'];
        } else {
            $cmd = "/sbin/ifconfig|grep 'inet addr'|awk '{print $2}'|awk -F':' '{print $2}'|awk '$1 !~ /127.0.0.1/{print}'|tail -n 1";
            $handle = popen($cmd, 'r');
            $ip = trim(fread($handle, 1024));
            pclose($handle);
        }
        return $ip;
    }

    /**
     * 获取Header信息
     * @return mixed
     */
    private static function getHeaders()
    {
        static $headers = array();
        if ($headers) {
            return $headers;
        }
        foreach ($_SERVER as $key => $value) {
            if (substr($key, 0, 5) != 'HTTP_') {
                continue;
            }
            $header = str_replace(' ', '-', ucwords(str_replace('_', ' ', strtolower(substr($key, 5)))));
            $headers[$header] = $value;
        }
        return $headers;
    }

}
