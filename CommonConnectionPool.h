#include "Connection.h"
#include <atomic>
#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

using namespace std;

// 实现连接池功能模块
class ConnectionPool
{
public:
    // 获取连接池对象实例（懒汉式单例模式，在获取实例时才实例化对象）
    static ConnectionPool *getConnectionPool();
    // 给外部提供接口，从连接池中获取一个可用的空闲连接
    //注意，这里不要直接返回指针，否则我们还需要定义一个（归还连接）的方法，还要自己去释放该指针。
    //这里直接返回一个智能指针，智能指针出作用域自动析构，（我们只需重定义析构即可--不释放而是归还）
    shared_ptr<Connection> getConnection();

private:
    // 单例模式——构造函数私有化
    ConnectionPool();
    // 从配置文件中加载配置项
    bool loadConfigFile();

    // 运行在独立的线程中，专门负责生产新连接
    // 非静态成员方法，其调用依赖对象，要把其设计为一个线程函数，需要绑定this指针。
    // 把该线程函数写为类的成员方法，最大的好处是 非常方便访问当前对象的成员变量。（数据）
    void produceConnectionTask();
    // 扫描超过maxIdleTime时间的空闲连接，进行对于连接的回收
    void scannerConnectionTask();

    string _ip;           // MySQL的ip地址
    unsigned short _port; // MySQL的端口号，默认为3306
    string _username;     // MySQL登陆用户名
    string _password;     // MySQL登陆密码
    string _dbname;       // 连接的数据库名称

    int _initSize;          // 连接池的最大初始连接量
    int _maxSize;           // 连接池的最大连接量
    int _maxIdleTime;       // 连接池的最大空闲时间
    int _connectionTimeout; // 连接池获取连接的超时时间

    // 存储MySQL连接的队列
    queue<Connection *> _connectionQue;

    // 维护连接队列的线程安全互斥锁
    mutex _queueMutex;
    // 记录connection连接的总数量
    atomic_int _connectionCnt;
    // 设置条件变量，用于连接生产线程和连接消费线程的通信
    condition_variable cv;
};