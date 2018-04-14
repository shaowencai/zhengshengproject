Typedef struct os_tcb{
	OS_STK *OSTCBStkPtr  //任务堆栈指针
	struct os_tcb *OSTCBNext;
	struct os_tcb *OSTCBPrev;
	INT32U OSTCBDly;
	INT8U  OSTCBStat;
	INT8U  OSTCBStatPend;
	INT8U  OSTCBPrio;
	INT8U  OSTCBX;
	INT8U  OSTCBY;
	INT8U  OSTCBBitX;
	INT8U  OSTCBBitY;
}

