#include "CommonConnectionPool.h"
#include "Connection.h"
#include <ctime>
#include <iostream>
#include <string>

int n = 10000; //数据量

int main()
{

    //不使用连接池，单线程：
    clock_t begin = clock();
    for (int i = 0; i < n; i++)
    {
        Connection conn;
        char sql[1024] = {0};
        sprintf(sql, "insert into t1(id,name) values(%d,'%s')",
                1, "a");
        conn.connect("127.0.0.1", 3306, "root", "zh601572", "chat");
        conn.update(sql);
    }

    clock_t end = clock();
    cout << end - begin << "ms" << endl;
    return 0;

    //不使用连接池，4线程：
    /*
    Connection conn;
    conn.connect("localhost", 3306, "root", "zh601572", "chat");
    clock_t begin = clock();
    thread t1([]()
    	{
    		for (int i = 0; i < n/4; ++i)
    		{
    			Connection conn;
    			char sql[1024] = { 0 };
    			sprintf(sql, "insert into t1(id,name) values(%d,'%s')",
    				5, "a");
    			conn.connect("localhost", 3306, "root", "zh601572", "chat");
    			conn.update(sql);
    		}
    	});
    thread t2([]()
    	{
    		for (int i = 0; i < n / 4; ++i)
    		{
    			Connection conn;
    			char sql[1024] = { 0 };
    			sprintf(sql, "insert into t1(id,name) values(%d,'%s')",
    				6, "a");
    			conn.connect("localhost", 3306, "root", "zh601572", "chat");
    			conn.update(sql);
    		}
    	});
    thread t3([]()
    	{
    		for (int i = 0; i < n / 4; ++i)
    		{
    			Connection conn;
    			char sql[1024] = { 0 };
    			sprintf(sql, "insert into t1(id,name) values(%d,'%s')",
    				7, "a");
    			conn.connect("localhost", 3306, "root", "zh601572", "chat");
    			conn.update(sql);
    		}
    	});
    thread t4([]()
    	{
    		for (int i = 0; i < n / 4; ++i)
    		{
    			Connection conn;
    			char sql[1024] = { 0 };
    			sprintf(sql, "insert into t1(id,name) values(%d,'%s')",
    				8, "a");
    			conn.connect("localhost", 3306, "root", "zh601572", "chat");
    			conn.update(sql);
    		}
    	});
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    clock_t end = clock();
    cout << end - begin << "ms" << endl;
    return 0;
    */

    //使用连接池，单线程：
    /*
    clock_t begin = clock();
    ConnectionPool* cp = ConnectionPool::getConnectionPool();
    for (int i = 0; i < n; i++)
    {
    	shared_ptr<Connection> sp = cp->getConnection();
    	char sql[1024] = { 0 };
    	sprintf(sql, "insert into t1(id,name) values(%d,'%s')",
    	4, "zhouhui");
    	sp ->update(sql);
    }
    clock_t end = clock();
    cout << end - begin << "ms" << endl;
    return 0;

    使用连接池，四线程：
    clock_t begin = clock();
    
    thread t1([]()
    	{
    		ConnectionPool* cp = ConnectionPool::getConnectionPool();
    		for (int i = 0; i < n / 4; i++)
    		{
    			shared_ptr<Connection> sp = cp->getConnection();
    			char sql[1024] = { 0 };
    			sprintf(sql, "insert into t1(id,name) values(%d,'%s')",4, "zhouhui");
    			sp ->update(sql);
    		}
    	}
    );

    thread t2([]()
    	{
    		ConnectionPool* cp = ConnectionPool::getConnectionPool();
    		for (int i = 0; i < n /4; i++)
    		{
    			shared_ptr<Connection> sp = cp->getConnection();
    			char sql[1024] = { 0 };
    			sprintf(sql, "insert into t1(id,name) values(%d,'%s')", 4, "zhouhui");
    			sp->update(sql);
    		}
    	}
    );

    thread t3([]()
    	{
    		ConnectionPool* cp = ConnectionPool::getConnectionPool();
    		for (int i = 0; i < n / 4; i++)
    		{
    			shared_ptr<Connection> sp = cp->getConnection();
    			char sql[1024] = { 0 };
    			sprintf(sql, "insert into t1(id,name) values(%d,'%s')", 4, "zhouhui");
    			sp->update(sql);
    		}
    	}
    );
    thread t4([]()
    	{
    		ConnectionPool* cp = ConnectionPool::getConnectionPool();
    		for (int i = 0; i < n / 4; i++)
    		{
    			shared_ptr<Connection> sp = cp->getConnection();
    			char sql[1024] = { 0 };
    			sprintf(sql, "insert into t1(id,name) values(%d,'%s')", 4, "zhouhui");
    			sp->update(sql);
    		}
    	}
    );

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    clock_t end = clock();
    cout << (end - begin) << "ms" << endl;

    return 0;
    */
}