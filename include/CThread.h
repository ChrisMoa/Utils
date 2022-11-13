//
// Created by chris-tab on 15.05.21.
//

#ifndef CTHREAD_H
#define CTHREAD_H

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <atomic>
#include <shared_mutex>

namespace Thread
{

  class CThread
  {
  public:
    CThread(std::string name);

    virtual ~CThread();

    /**
     * @brief start a new execution process
     * @param[in] void
     * @return void
     * @date 23.02.2020
     */
    void Resume(void);

    /**
     * @brief let the thread take a break to the next time
     * @param[in] void
     * @return void
     * @date 23.02.2020
     */
    void Break(void);

    /**
     * @brief terminates the thread safely
     * @return void
     * @date 23.02.2020
     */
    virtual void Terminate(void);

    /**
     * @brief wait For the Thread till finish
     * @param[in] void:
     * @return
     * @date 23.02.2020
     */
    void WaitForThread(void);

    /**
     * @brief checks the current flags for this thread
     * @note should be called on every long execution time
     * @return void
     * @date 15.05.2021
     */
    void CheckFlags(void);

    /**
     * @brief adds $amount$ number of automatic execution
     * @param[in] amount the number of repetitions
     * @note if $amount$ < 0, then the amount will decrease
     * @return void
     * @date 15.05.2021
     */
    void addExecution(int32_t amount);

  protected:
    /**
     * @brief executes a cycle
     * @return void
     * @date 23.02.2020
     */
    virtual void Execute(void);

    // Slots
    /**
     * @brief executes on termination process process
     * @param[in] void:
     * @return
     * @date 23.02.2020
     */
    virtual void onFinish(void);

    /**
     * @brief do this while waiting till thread finishes working
     * @param[in] void:
     * @return
     * @date 23.02.2020
     */
    virtual void onWaiting(void);

    /**
     * @brief do this while waiting till thread finishes working
     * @param[in] void:
     * @return
     * @date 23.02.2020
     */
    virtual void onResume(void);

    // Signals

  private:
    /**
     * @brief defines the run state of the thread
     * @return void
     * @date 23.02.2020
     */
    void run(void);

    std::thread *_threadHandle;      //! thread handle
    std::shared_mutex lock;          //! default lock mutex for parameters
    std::mutex mtxWaiting;           //! the mutex for waiting
    std::condition_variable waiting; //! condition variable for waiting

    std::atomic_bool flagBreak;  //! thread shoud take a break
    std::atomic_bool flagAlive;  //! thread is alive
    std::atomic_bool flagFinish; //! thread has finished execution

    std::atomic_int32_t executionCounter; //! repeat execution while this count > 0

    const std::string threadName; //! is the name of the thread which is applied to recognize the thread
  };

}
#endif // CTHREAD_H
