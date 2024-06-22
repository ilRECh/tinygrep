#include "base_queue.hpp"

#include <iostream>

#include "book.hpp"
#include "sleuth.hpp"

template<typename T>
BaseQueue<T>::BaseQueue() :
    m_queue(),
    m_is_growing(true)
{}

template<typename T>
void BaseQueue<T>::enqueue(BaseQueue<T>::BaseQueueElem elem)
{
    std::lock_guard lock(m_queue_mutex);

    m_queue.push_back(elem);

    m_cv.notify_one();
}

template<typename T>
void BaseQueue<T>::dequeue(
    std::list<BaseQueue<T>::BaseQueueElem>& list, 
    bool& is_growing
) {
    std::unique_lock<std::mutex> lock(m_queue_mutex);

    m_cv.wait(lock, [this]{ return !m_queue.empty() || !m_is_growing; } );

    is_growing = m_is_growing;

    if(!m_queue.empty())
    {
        list.splice(list.begin(), m_queue, m_queue.begin(), m_queue.end());
    }
}

template<typename T>
void BaseQueue<T>::dequeue(
    BaseQueue<T>::BaseQueueElem& elem, 
    bool& is_growing
) {
    std::unique_lock<std::mutex> lock(m_queue_mutex);

    m_cv.wait(lock, [this]{ return !m_queue.empty() || !m_is_growing; } );

    is_growing = !m_queue.empty() || m_is_growing;

    if(!m_queue.empty())
    {
        elem = *m_queue.begin();
        m_queue.pop_front();
    }
}

template<typename T>
void BaseQueue<T>::set_finished(void) noexcept
{
    std::lock_guard lock(m_queue_mutex);

    m_is_growing = false;

    m_cv.notify_all();
}
