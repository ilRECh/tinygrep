#include "base_queue.hpp"

#include <iostream>

#include "book.hpp"

template<typename T>
BaseQueue<T>::BaseQueue(bool is_to_always_dequeue_max) :
    m_queue(),
    m_is_growing(true),
    m_is_dequeueing_max(is_to_always_dequeue_max),
    m_updated(false)
{}

template<typename T>
void BaseQueue<T>::enqueue(T elem)
{
    std::lock_guard lock(m_queue_mutex);

    m_updated = true;
    m_queue.push_back(elem);

    m_cv.notify_one();
}

template<typename T>
void BaseQueue<T>::dequeue(std::list<T>& list, bool& is_growing)
{
    std::unique_lock<std::mutex> lock(m_queue_mutex);

    m_cv.wait(lock, [this]{ return m_updated; } );

    m_updated = false;
    is_growing = m_is_growing;

    if(m_is_dequeueing_max)
    {
        list.splice(list.begin(), m_queue, m_queue.begin(), m_queue.end());
    }
    else
    {
        list.splice(list.begin(), m_queue, m_queue.begin());
    }
}

template<typename T>
void BaseQueue<T>::set_finished(void) noexcept
{
    std::lock_guard lock(m_queue_mutex);

    m_is_growing = false;
    m_updated = true;

    m_cv.notify_one();
}
