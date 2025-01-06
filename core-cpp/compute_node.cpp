#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>
#include <future>
#include <queue>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue {
private:
    mutable std::mutex mut;
    std::queue<std::shared_ptr<T>> data_queue;
    std::condition_variable data_cond;
public:
    ThreadSafeQueue() {}
    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this]{return !data_queue.empty();});
        value = std::move(*data_queue.front());
        data_queue.pop();
    }
    bool try_pop(std::shared_ptr<T>& value) {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty()) return false;
        value = data_queue.front();
        data_queue.pop();
        return true;
    }
    void push(T new_value) {
        std::shared_ptr<T> data(std::make_shared<T>(std::move(new_value)));
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
    }
};

// Hash 1412
// Hash 6525
// Hash 4433
// Hash 4459
// Hash 1800
// Hash 7097
// Hash 4709
// Hash 9825
// Hash 2003
// Hash 6796
// Hash 6519
// Hash 7313
// Hash 6700
// Hash 3139
// Hash 6057
// Hash 8448
// Hash 2523
// Hash 6116
// Hash 3189
// Hash 5462
// Hash 8472
// Hash 3275
// Hash 4024
// Hash 3237
// Hash 3149
// Hash 8621
// Hash 3613
// Hash 5732
// Hash 1937
// Hash 6403
// Hash 6973
// Hash 4431
// Hash 9002
// Hash 5467
// Hash 3192
// Hash 1709
// Hash 5768
// Hash 4659
// Hash 1266
// Hash 1063
// Hash 2302
// Hash 8307
// Hash 5104
// Hash 3681
// Hash 1924
// Hash 7917
// Hash 1258
// Hash 9595
// Hash 6751
// Hash 2968
// Hash 1397
// Hash 5395
// Hash 4195
// Hash 2260
// Hash 1750