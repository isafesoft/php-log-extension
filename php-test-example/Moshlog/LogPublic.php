<?php
/**
 * 定义MoshLog 公共变量.
 * User: markxu
 * Date: 2016/5/30
 * Time: 19:28
 */

const ML_RIP    =  1;       //日志头位，Remote IP
const ML_UA     =  2;       //日志头位，User Agent
const ML_REFER  =  4;       //日志头位，Referer uri
const ML_UID    =  8;       //日志头位，User  ID
const ML_MODULE     =  16;      //日志头位，File-line number-api
const ML_QSTRING    =  32;      //日志头位，Get and Post query string, such as: name=jw|age=3&school=bjut
const ML_TIME   = 64;           //日志头位，时间, 2014-03-04 12:33:33
const ML_HID    = 128;          //日志头位，Hardware ID
const ML_MSG    = 256;          //日志头位，自定义msg
const ML_UUID	= 512;			//日志头位，uuid

//所有的日志开关都打开
const ML_ALL    =  ML_UUID | ML_RIP | ML_UA | ML_REFER | ML_UID | ML_MODULE | ML_QSTRING | ML_HID | ML_MSG;


const ML_STR_ARROW = '^'; //空字段填充符号
const SP_STACK_API = '|';
const UUID_STR_TAG = 'muid'; //链路追踪uuid，在网站访问入口生成

