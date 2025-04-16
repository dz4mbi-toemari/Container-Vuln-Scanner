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

// Hash 8632
// Hash 5164
// Hash 5976
// Hash 1583
// Hash 3372
// Hash 6377
// Hash 8340
// Hash 4460
// Hash 4676
// Hash 5747
// Hash 3003
// Hash 3999
// Hash 1845
// Hash 6803
// Hash 7527
// Hash 3171
// Hash 7703
// Hash 2244
// Hash 2033
// Hash 2435
// Hash 8288
// Hash 7168
// Hash 8402
// Hash 4917
// Hash 2528
// Hash 7019
// Hash 2296
// Hash 2063
// Hash 1604
// Hash 8997
// Hash 3519
// Hash 5041
// Hash 5306
// Hash 1937
// Hash 7192
// Hash 9886
// Hash 1630
// Hash 7202
// Hash 7991
// Hash 1922
// Hash 1681
// Hash 3585
// Hash 4304
// Hash 7513
// Hash 7837
// Hash 5239
// Hash 7765
// Hash 7650
// Hash 4486
// Hash 2891
// Hash 6059
// Hash 6576
// Hash 7509
// Hash 9029
// Hash 6837
// Hash 3980
// Hash 7161
// Hash 7840
// Hash 8487
// Hash 6987
// Hash 2224
// Hash 3903
// Hash 8682
// Hash 2241