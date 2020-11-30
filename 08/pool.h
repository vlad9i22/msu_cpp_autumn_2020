#ifndef pool_H
#define pool_H
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <mutex>
#include <queue>
#include <future>
#include <thread>
#include <functional>
using namespace std;


class ThreadPool
{
public:
    explicit ThreadPool(size_t poolSize) : stop(false) {
        for(size_t i = 0; i < poolSize; ++i) {
            workers.emplace_back([this] {
                while(true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(this->qmut);
                        this->condition.wait(lock);
                        if(stop && tasks.empty()) {
                            return;
                        }
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
        using returning = typename std::result_of<Func(Args...)>::type;
        auto task = std::make_shared< std::packaged_task<returning()> >(
            std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
        );
        auto res = task->get_future();
        {
            std::lock_guard<std::mutex> lock(this->qmut);
            if(stop) {
                throw std::runtime_error("The pool is closed");
            }
            tasks.push([task](){
                (*task)();
            });
        }
        condition.notify_one();
        return res;
    }
    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(qmut);
            stop = true;
        }
        condition.notify_all();
        for(auto &thr : workers) {
            thr.join();
        }
    }
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex qmut;
    std::condition_variable condition;
    bool stop;
};
#endif