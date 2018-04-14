#define OS_TASK_CREATE_EXT_EN   1 //任务创建扩展功能使能

#define OS_Q_EN                 1 //消息队列使能

#define OS_MAX_QS               2 //最大消息队列数

#define OS_MBOX_EN          	1 //消息邮箱使能

#define OS_EVENT_EN             1 //事件使能




#define OS_MAX_EVENTS             8    // 最大的事件控制块的数量。包括消息邮箱，消息队列，信号量的个数总和 必须大于0*/
#define OS_MAX_FLAGS              8    // 应用中最多事件标志组的数目，必须大于0                                     */
#define OS_MAX_MEM_PART           8    // 最大内存控制块如果要使用内存块最小应设为2　OS_MEM_EN也要同时置1　　　　*/
#define OS_MAX_QS                 1    //最大的消息队列数。要使用消息队列，常量OS_Q_EN也要同时置1。如果要使用消息队列，OS_MAX_ QS最小应该设置为2*/
#define OS_MAX_TASKS              5    //最大的任务数 OS_MAX_MEM_TASKS设定的太大则会浪费内存     */
#define OS_LOWEST_PRIO            8    //任务最低优先级设定OS_LOWEST_PRIO可以节省用于任务控制块的内存*/
#define OS_TASK_IDLE_STK_SIZE     128    // 空闲任务（Idle task）堆栈的容量。注意堆栈容量的单位不是字节，而是OS_STK（μC/OS-II中堆栈统一用OS_STK声明 */
          //虽然空闲任务几乎不做什么工作，但还是要预留足够的堆栈空间保存CPU寄存器的内容，以及可能出现的中断嵌套情况
#define OS_TASK_STAT_EN           0    // 统计任务使能（statistic task）*/
#define OS_TASK_STAT_STK_SIZE     128    // 统计任务堆栈*/
          //如果想在统计任务中进行堆栈检查，判断实际的堆栈使用，用户需要设OS_TASK_CREATE_EXT_EN为1，并使用OSTaskCreateExt（）函数建立任务
#define OS_ARG_CHK_EN             1    // 允许或禁止变量检查         */
#define OS_CPU_HOOKS_EN           1    //为0时，UC/OS II提供的接口函数可以重新定义,为1时，使用系统提供的函数。 OSTaskCreateHook（）等任务创建切换及OSTIMETICK*/
// ------------------事件标志组管理函数相关使能 ------------------------ */
#define OS_FLAG_EN                0    // 允许（1）或者禁止（0）产生事件标志代码   */
#define OS_FLAG_WAIT_CLR_EN       1    // 允许生成 Wait on Clear 事件标志代码 */
#define OS_FLAG_ACCEPT_EN         1    // 允许生成 OSFlagAccept()函数代码*/
#define OS_FLAG_DEL_EN            1    // 允许生成 OSFlagDel() 函数代码 */
#define OS_FLAG_QUERY_EN          1    // 允许生成函数代码  OSFlagQuery()                           */
// ------------------消息邮箱管理相关使能- --------------------- */
#define OS_MBOX_EN                1    // 使能（1）或者禁止（0）产生邮箱代码*/
#define OS_MBOX_ACCEPT_EN         1    //  允许生成函数代码OSMboxAccept()                          */
#define OS_MBOX_DEL_EN            1    //  允许生成函数代码OSMboxDel()                             */
#define OS_MBOX_POST_EN           1    //  允许生成函数代码OSMboxPost()                            */
#define OS_MBOX_POST_OPT_EN       1    //  允许生成函数代码OSMboxPostOpt()                         */
#define OS_MBOX_QUERY_EN          1    //  允许生成函数代码OSMboxQuery()                           */
// ------------------内存管理相关使能控制 -------------------- */
#define OS_MEM_EN                 1    // 允许（1）或者禁止（0）产生内存关系代码*/
#define OS_MEM_QUERY_EN           1    // 允许生成函数代码OSMemQuery()                            */

// ---------------- 互斥型信号量管理--------------- */
#define OS_MUTEX_EN               1    // 允许（1）或者禁止（0） MUTEX          */
#define OS_MUTEX_ACCEPT_EN        1    // 允许生成函数代码OSMutexAccept()                         */
#define OS_MUTEX_DEL_EN           1    // 允许生成函数代码OSMutexDel()                            */
#define OS_MUTEX_QUERY_EN         1    // 允许生成函数代码OSMutexQuery()                          */

// -----------------消息队列管理相关使能常量 ---------------------- */
#define OS_Q_EN                   1    // Enable (1) or Disable (0) code generation for QUEUES         */
#define OS_Q_ACCEPT_EN            1    // 允许生成函数代码OSQAccept()                             */
#define OS_Q_DEL_EN               1    //  允许生成函数代码OSQDel()                                */
#define OS_Q_FLUSH_EN             1    //  允许生成函数代码OSQFlush()                              */
#define OS_Q_POST_EN              1    //  允许生成函数代码OSQPost()                               */
#define OS_Q_POST_FRONT_EN        1    //  允许生成函数代码OSQPostFront()                          */
#define OS_Q_POST_OPT_EN          1    //  允许生成函数代码OSQPostOpt()                            */
#define OS_Q_QUERY_EN             1    //  允许生成函数代码OSQQuery()                              */

// -----------------信号量------- SEMAPHORES ------------------------ */
#define OS_SEM_EN                 1    // Enable (1) or Disable (0) code generation for SEMAPHORES     */
#define OS_SEM_ACCEPT_EN          1    // 允许生成函数代码OSSemAccept()                            */
#define OS_SEM_DEL_EN             1    // 允许生成函数代码OSSemDel()                               */
#define OS_SEM_QUERY_EN           1    // 允许生成函数代码OSSemQuery()                             */

// ------------------任务管理--- TASK MANAGEMENT ---------------------- */
#define OS_TASK_CHANGE_PRIO_EN    1    // 允许生成函数代码OSTaskChangePrio()                      */
#define OS_TASK_CREATE_EN         1    // 允许生成函数代码OSTaskCreate()                          */
#define OS_TASK_CREATE_EXT_EN     1    // 允许生成函数代码OSTaskCreateExt()                       */
#define OS_TASK_DEL_EN            1    // 允许生成函数代码OSTaskDel()                             */
#define OS_TASK_SUSPEND_EN        1    // 允许生成函数代码OSTaskSuspend() and OSTaskResume()      */
#define OS_TASK_QUERY_EN          1    // 允许生成函数代码OSTaskQuery()                           */

// ------------------时间管理--- TIME MANAGEMENT ---------------------- */
#define OS_TIME_DLY_HMSM_EN       1    //允许生成函数代码OSTimeDlyHMSM()                         */
#define OS_TIME_DLY_RESUME_EN     1    //允许生成函数代码OSTimeDlyResume()                       */
#define OS_TIME_GET_SET_EN        1    //允许生成函数代码OSTimeGet() and OSTimeSet()             */

// ------------------其它---- MISCELLANEOUS ----------------------- */
#define OS_SCHED_LOCK_EN          1    //允许生成函数代码OSSchedLock() and OSSchedUnlock()       */

#define OS_TICKS_PER_SEC        1000    // 时钟节拍常数，要与实际所设置一样*/

typedef INT16U             OS_FLAGS;   // Date type for event flag bits (8, 16 or 32 bits)             */