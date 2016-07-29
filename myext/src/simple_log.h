#ifndef SIMPLE_LOG_H
#define SIMPLE_LOG_H



//级别						代码			解释	动作
const int DEBUG_LEVEL	= 100;			//调试日志（上线关闭）
const int INFO_LEVEL	= 200;			//重要的动作，譬如用户登录等
const int ERROR_LEVEL	= 400;			//运行时错误	不需要立刻采取措施，但是显著表示，让管理员容易注意到
const int CRITICAL_LEVEL	= 500;			//严重错误，譬如组件不可用，出现逻辑异常	立刻通知管理员
const int ALERT_LEVEL	= 550;			//必须立刻采取措施，譬如网站故障，数据库连接失败	触发短信报警
const int EMERGENCY_LEVEL	= 600;			//整个系统瘫痪

const int ERR_OK = 0x00; //okay
const int ERR_NOCONFIG = 0x10; //error no config file
const int ERR_OPENFILE = 0x11; //error open file
const int ERR_MKDIR = 0x12; //error make dir
const int ERR_LEVEL = 0x13; //error log level
const int ERR_PARAM_NULL = 0x14; //error parameter should not be null
const int ERR_INITFILE = 0x15; //error when open init file


// log config
extern int log_level;

std::string _get_show_time();

//get 2016-3-4 14:24:24.33 string
std::string getNowTimeString();


//get log save path
int getLogSavePath(POUT std::string &savePath);

//get log config file path
int getLogConfPath(POUT std::string &confPath);

//get log config items
int getLogConf(POUT std::string &confPath);


int log_init(std::string dir, std::string file);


int log_debug(const char *format, ...);
int log_info(const char *format, ...);
int log_error(const char *format, ...);
int log_critical(const char *format, ...);
int log_alert(const char *format, ...);
int log_emergency(const char *format, ...);

void set_log_level(const char *level);
std::string formatLogString(vstring &vs);
int logjw(const char *format, ...);

//set the span begin
long long mlBeginSpan();
long mlGetSpan(long long beginTimer);
std::string mlGetUString();

class FileAppender {
    public:
        FileAppender();
        ~FileAppender();
        int init(std::string dir, std::string file);
        bool is_inited();
        int write_log(char *log, const char *format, va_list ap);
        int shift_file_if_need(struct timeval tv, struct timezone tz);
        int delete_old_log(timeval tv);
        void set_retain_day(int rd);
    private:
        std::fstream _fs;
        std::string _log_file;
        std::string _log_dir;
        std::string _log_file_path;
        long _last_sec;
        bool _is_inited;
        int _retain_day;
        pthread_mutex_t writelock;
};

#endif
