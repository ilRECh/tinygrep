#pragma once

#include <list>
#include <thread>
#include <mutex>
#include <memory>
#include <condition_variable>

/**
 * @brief thread-safe queue
 * 
 * @tparam T type of the data to hold
 */
template<typename T>
class BaseQueue
{
    public:

        typedef std::shared_ptr<T> BaseQueueElem;

    private:

        /**
         * @brief queue with the data
         * 
         * @details implemented with the linked list, because
         *          we care about taking from the front and adding to the end
         *          rather than about the random access
         */
        std::list<BaseQueueElem> m_queue;

        /**
         * @brief the variable, which defines if the queue is growing
         *        and will have more elements in the future
         */
        bool m_is_growing;

        /**
         * @brief Mutex to synchronize access to m_queue
         */
        std::mutex m_queue_mutex;
    
        /**
         * @brief Condition variable to signal changes in the m_queue
         */
        std::condition_variable m_cv;

    public:

        /**
         * @brief Construct a new Base Queue object
         */
        BaseQueue();

        /**
         * @brief Enqueue the next element
         * 
         * @details Cannot be used with dequeue in the same thread
         * 
         * @param elem 
         */
        void enqueue(BaseQueueElem elem);

        /**
         * @brief Dequeue an available group of elements
         * 
         * @details Cannot be used with enqueue in the same thread
         * 
         * @param[out] list of elements available
         * @param[out] is_growing
         */
        void dequeue(std::list<BaseQueueElem>& list, bool& is_growing);

        /**
         * @brief Dequeue an available element
         * 
         * @details Cannot be used with enqueue in the same thread
         * 
         * @param[out] elem if available
         * @param[out] is_growing
         */
        void dequeue(BaseQueueElem& elem, bool& is_growing);

        /**
         * @brief Mark the queue as finished as in there won't be any elements anymore
         */
        void set_finished(void) noexcept;
};
