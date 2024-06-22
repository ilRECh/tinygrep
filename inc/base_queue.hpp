#pragma once

#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>

/**
 * @brief thread-safe queue
 * 
 * @tparam T type of the data to hold
 */
template<typename T>
class BaseQueue
{
    private:
        BaseQueue();

        /**
         * @brief queue with the data
         * 
         * @details implemented with the linked list, because
         *          we care about taking from the front and adding to the end
         *          rather than about the random access
         */
        std::list<T> m_queue;

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

        bool m_updated;

    protected:

        /**
         * @brief Whether to take whole queue on dequeue
         * 
         * @see dequeue
         */
        bool m_is_dequeueing_max;

    public:

        /**
         * @brief Construct a new Base Queue object
         * 
         * @param is_to_always_dequeue_max tells the queue whehter to always extract maximum
         *                                 available elements, or one at a time
         */
        BaseQueue(bool is_to_always_dequeue_max);

        /**
         * @brief Enqueue the next element
         * 
         * @details Cannot be used with dequeue in the same thread
         * 
         * @param elem 
         */
        void enqueue(T elem);

        /**
         * @brief Dequeue the next element or a group of elements
         * 
         * @details Cannot be used with enqueue in the same thread
         * 
         * @param[out] list
         * @param[out] is_growing
         */
        void dequeue(std::list<T>& list, bool& is_growing);

        /**
         * @brief Mark the queue as finished as in there won't be any elements anymore
         */
        void set_finished(void) noexcept;
};
