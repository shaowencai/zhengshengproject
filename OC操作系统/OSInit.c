
/*操作系统初始化函数*/

OSInit(void)
{
	OSInitHookBegin();//用户可编写该函数实现端口说明
	OS_InitMisc();// 初始化各种全局变量
	OS_InitRdyList();//对就绪表，就绪组就行初始化
	OS_InitTCBList();//建立好空闲链表，就绪链表
	OS_InitEventList();//对事件数据结构进行初始化
	
	#if (OS_FLAG_EN>0u)&&(OS_MAX_FLAGS>0u)
		OS_FlagInit();
	#endif

	#if (OS_MEM_EN>0u)&&(OS_MAX_MEM_PART>0u)
		OS_MemInit();
	#endif
	
	#if (OS_Q_EN>0u)&&(OS_MAX_QS>0u)
		OS_QInit();
	#endif
	OS_InitTaskIdle();//创建空闲任务
	#if OS_TASK_STAT_EN>0u
		OS_InitTaskStat();//创建统计任务
	#endif
	
	#if OS_TMR_EN>0u
		OSTmr_Init();//如果定时器使能，初始化定时器管理模块
	#endif
	
	OSInitHookEnd();// 用户可继续编写该函数实现端口说明
}

static void OS_InitMisc(void)
{
	#if OS_TIME_GET_EN>0u
		OSTime=0ul;
	#endif
	OSIntNesting=0u;   //清除嵌套计数  用来记录中断嵌套的层数  
	OSLockNesting=0u;  //清调度锁计数
	OSTaskCtr=0u;	   //当前任务数是0
	OSRunning=OS_FALSE;//未启动多任务
	OSCtxSwCtr=0u;     //任务切换次数是0
	OSIdleCtr=0ul;     //空闲计数器
	#if OS_TASK_STAT_EN>0u
		OSIdleCtrRun=0;//1秒内的空闲计数值是0
		OSIdleCtrMax=0ul;//最大空闲计数值
		OSStatRdy=OS_FALSE;//统计任务还没有准备好
	#endif
}

static void OS_InitRdyList(void)
{
	INT8U i;
	OSRdyGrp=0u;
	for(i=0u;i<OS_RDY_TBL_SIZE;i++)
	{
		OSRdyTbl[i]=0u;  //将就绪表清0
	}
	OSPrioCur=0u;       //当前任务的优先级初始化为0
	OSPrioHighRdy=0u;   //最高优先级初始化0
	OSTCBHighRdy=(OS_TCB *)0;//最高优先级的任务的控制块的指针初始化
	OSTCBCur=(OS_TCB *)0;  //控制块的指针初始化
}

static void OS_InitTCBList(void)
{
	INT8U ix;
	INT8U ix_next;
	OS_TCB *ptcb1;
	OS_TCB *Ptcb2;
	OS_Memclr((INT8U *)&OSTCBTbl[0],sizeof(OSTCBTbl));//将任务控制块初始化为0
	OS_Memclr((INT8U *)&OSTCBPrioTbl[0],sizeof(OSTCBPrioTbl));//将任务优先级指针初始化为0
	for(ix=0u;ix<(OS_MAX_TASKS+OS_N_SYS_TASKS-1u);ix++)//将控制块连接起来形成空闲表
	{
		ix_next=ix+1u;
		pctb1=&OSTCBTbl[ix];
		pctb2=&OSTCBTbl[ix_next];
		pctb1->OSTCBNext=pctb2;
	}
	pctb1=&OSTCBTbl[ix];
	pctb1->OSTCBNext=(OS_TCB *)0;//最后一个控制块指向空地址
	OSTCBFreeList=&OSTCBTbl[0];//OSTCBFreeList指向空闲链表的表头
	
	OSTCBList=(OS_TCB *)0;     //OSTCBList指向就绪表表头
}

static void OS_InitTaskIdle(void)
{
	#if OS_TASK_NAME_EN>0u
		INT8U err;
	#endif
	
	#if OS_TASK_CREATE_EXT_EN >0u
		#if OS_STK_GROWTH==1u
			(void) OSTaskCreateExt(OS_TaskIdle,(void *)0,&OSTaskIdleStk[OS_TASK_IDLE_STK_SIZE-1u],
			OS_TASK_IDLE_PRIO,OS_TASK_IDLE_ID,&OSTaskIdleStk[0],OS_TASK_IDLE_STK_SIZE,(void *)0,
			OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
		#else
			(void) OSTaskCreateExt(OS_TaskIdle,(void *)0,&OSTaskIdleStk[0],
			OS_TASK_IDLE_PRIO,OS_TASK_IDLE_ID,&OSTaskIdleStk[OS_TASK_IDLE_STK_SIZE-1u],OS_TASK_IDLE_STK_SIZE,(void *)0,
			OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
		#endif
	#else
		#if OS_STK_GROWTH==1u
			(void) OSTaskCreate(OS_TaskIdle,(void *)0,&OSTaskIdleStk[OS_TASK_IDLE_STK_SIZE-1u],OS_TASK_IDLE_PRIO);
		#else
			(void) OSTaskCreateExt(OS_TaskIdle,(void *)0,&OSTaskIdleStk[0],OS_TASK_IDLE_PRIO);
		#endif
	#endif
	
	#if OS_TASK_NAME_EN>0u
		OSTaskNameSet(OS_TASK_IDEL_PRIO,(INT8u *)(void *)"uc/os-II Idle",&err);
	#endif
}
static void OS_InitEventList(void)
{
	INT16U ix;
	INT16U ix_next;
	OS_EVENT *p1;
	OS_EVENT *p2;
	OS_Memclr((INT8U *)&OSEventTbl[0],sizeof(OSEventTbl));
	for(ix=0u;ix<(OS_MAX_EVENTS-1u);ix++)
	{
		ix_next=ix+1u;
		p1=&OSEventTbl[ix];
		p2=&OSEventTbl[ix_next];
		p1->OSEventType=OS_EVENT_TYPE_UNUSED;
		p1->OSEventPtr=p2;
		p1->OSEventName=(INT8U *)(void *)"?";
	}
	p1=&OSEventTbl[ix];
	p1->OSEventType=OS_EVENT_TYPE_UNUSED;
	p1->OSEventPtr=(OS_EVENT *)0;
	p1->OSEventName=(INT8U *)(void *)"?";
	OSEventFreeList=&OSEventTbl[0];
}



//调用钩子函数，在里面加入用户代码  
#if OS_CPU_HOOKS_EN > 0 && OS_VERSION > 203  
void  OSInitHookBegin (void)  
{  
     printf("OSInitHookBegin/n");  
}  
#endif  
  
  
//调用钩子函数，在里面加入用户代码  
#if OS_CPU_HOOKS_EN > 0 && OS_VERSION > 203  
void  OSInitHookEnd (void)  
{  
    printf("OSInitHookEnd/n");  
}  
#endif 