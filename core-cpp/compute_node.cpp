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
// Hash 4315
// Hash 9423
// Hash 3081
// Hash 9735
// Hash 7165
// Hash 7350
// Hash 9961
// Hash 8702
// Hash 8215
// Hash 1409
// Hash 1396
// Hash 3286
// Hash 8433
// Hash 3191
// Hash 9871
// Hash 9300
// Hash 5099
// Hash 8871
// Hash 1316
// Hash 8635
// Hash 3962
// Hash 9281
// Hash 1094
// Hash 9857
// Hash 9525
// Hash 2502
// Hash 9931
// Hash 2957
// Hash 3215
// Hash 9315
// Hash 9074
// Hash 1041
// Hash 5204
// Hash 4957
// Hash 8190
// Hash 6934
// Hash 5360
// Hash 1504
// Hash 5793
// Hash 6686
// Hash 1719
// Hash 7568
// Hash 9465
// Hash 4158
// Hash 5387
// Hash 9374
// Hash 2494
// Hash 6806
// Hash 1630
// Hash 6529
// Hash 3448
// Hash 6808
// Hash 4622
// Hash 8293
// Hash 6282
// Hash 5310
// Hash 8528
// Hash 1354
// Hash 2439
// Hash 8353
// Hash 3797
// Hash 2936
// Hash 4777
// Hash 9901
// Hash 2173
// Hash 7354
// Hash 7987
// Hash 3135
// Hash 1414
// Hash 7937
// Hash 3894
// Hash 9671
// Hash 8305
// Hash 6117
// Hash 9574
// Hash 2871
// Hash 8814
// Hash 5079
// Hash 6956
// Hash 1961
// Hash 9631