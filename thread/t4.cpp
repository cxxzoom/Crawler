//
// Created by Administrator on 2023/6/9.
//
/**
 * 创建一个线程池
 *
 * 使用队列，初始化线程池的大小
 * 对线程池进行加锁，并
 */
#include "main.h"


class ThreadPool {
public :
    ThreadPool(size_t poolSize) : done(false) {
        for (int i = 0; i < poolSize; i++) {
            threads.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(mtx);
                        condition.wait(lock, [this] {
                            return done || !tasks.empty();
                        });

                        if (done || tasks.empty()) {
                            return;
                        }

                        task = std::move(tasks.front());
                        tasks.pop();
                    }

                    task();
                }
            });
        }
    };

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(mtx);
            done = true;
        }

        condition.notify_all();

        for (auto &thread: threads) {
            thread.join();
        }
    };

    template<class T, class... Args>
    void commit(T &&t, Args &&... args) {
        // 先获取锁
        std::function<void()> task = std::bind(std::forward<T>(t),std::forward<Args>(args)...);
        {
            std::unique_lock<std::mutex> lock(mtx);
            tasks.emplace(std::move(task));
        }
        condition.notify_one();
    }

private :
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex mtx;
    std::condition_variable condition;
    bool done;
};

void PrintNumber(size_t number) {
    cout << number << endl;
}


int main() {
    ThreadPool pool(4);

    for (int i = 0; i < 10; ++i) {
        pool.commit(PrintNumber, i);
    }

    return 0;
}