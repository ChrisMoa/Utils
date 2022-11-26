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
    CThread(CThread &a);
    CThread &operator=(const CThread &a);
    virtual ~CThread();

    /**
     * @brief start a new execution process
     * @param[in] void
     * @return void
     * @note can be used in combination with CheckUpdate in the child classes (is not be used in this class)
     * @date 23.02.2020
     */
    void Resume(void);

    /**
     * @brief let the thread take a break to the next time
     * @param[in] void
     * @return void
     * @note can be used in combination with CheckUpdate in the child classes (is not be used in this class)
     * @date 23.02.2020
     */
    void Break(void);

    /**
     * @brief begins a new thread execution
     * @param  void
     * @return void
     */
    void Begin(void);

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
     * @note can be used in combination with CheckUpdate in the child classes (is not be used in this class)
     * @date 15.05.2021
     */
    void CheckFlags(void);

    /**
     * @brief returns the thread name
     * @return the thread name
     */
    std::string getThreadName();

    /**
     * @brief get the state of the execution thread
     * @return if running {true}, not started {false}
     */
    bool IsRunning();

  protected:
    /**
     * @brief executes a cycle
     * @return void
     * @date 23.02.2020
     */
    virtual void Execute(void) = 0;

    // Slots
    /**
     * @brief executes on termination process process
     * @param[in] void:
     * @return
     * @date 23.02.2020
     */
    virtual void onFinish(void);

    /**
     * @brief do this while waiting till thread can resume
     * @param[in] void:
     * @return
     * @date 23.02.2020
     */
    virtual void onStartWaiting(void);

    /**
     * @brief do this while waiting till thread finishes working
     * @param[in] void:
     * @return
     * @date 23.02.2020
     */
    virtual void onResume(void);

    /**
     * @brief do this when before Executing() starts
     * @param void
     * @return void
     */
    virtual void onBeginning(void);

    /**
     * @brief do this when an Exception occurs
     * @param msg the exception msg
     * @return void
     */
    virtual void onException(std::string msg);

    /**
     * @brief checks the flags of the child class
     * @param void
     * @note can be override from child class to check his own flags whenever flags will be checked
     * @return void
     */
    virtual void onFlagCheck();

    /**
     * @brief will be executed when the created thread stops executing and destroying
     * @param void
     * @return void
     */
    virtual void onEnd();

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
    std::condition_variable begin;   //! the execution begin condition

    std::atomic_bool flagBreak;   //! thread shoud take a break
    std::atomic_bool flagAlive;   //! thread is alive
    std::atomic_bool flagFinish;  //! thread has finished execution
    std::atomic_bool flagBegin;   //! thread starts to executes or continious
    const std::string threadName; //! is the name of the thread which is applied to recognize the thread
  };

}
#endif // CTHREAD_H
