/* DEFS: readonly CProxy_Main mainProxy;
 */
extern CProxy_Main mainProxy;
#ifndef CK_TEMPLATES_ONLY
extern "C" void __xlater_roPup_mainProxy(void *_impl_pup_er) {
  PUP::er &_impl_p=*(PUP::er *)_impl_pup_er;
  _impl_p|mainProxy;
}
#endif /* CK_TEMPLATES_ONLY */

/* DEFS: readonly int Total_iterations;
 */
extern int Total_iterations;
#ifndef CK_TEMPLATES_ONLY
extern "C" void __xlater_roPup_Total_iterations(void *_impl_pup_er) {
  PUP::er &_impl_p=*(PUP::er *)_impl_pup_er;
  _impl_p|Total_iterations;
}
#endif /* CK_TEMPLATES_ONLY */

/* DEFS: readonly int chareDimension;
 */
extern int chareDimension;
#ifndef CK_TEMPLATES_ONLY
extern "C" void __xlater_roPup_chareDimension(void *_impl_pup_er) {
  PUP::er &_impl_p=*(PUP::er *)_impl_pup_er;
  _impl_p|chareDimension;
}
#endif /* CK_TEMPLATES_ONLY */

/* DEFS: readonly int size;
 */
extern int size;
#ifndef CK_TEMPLATES_ONLY
extern "C" void __xlater_roPup_size(void *_impl_pup_er) {
  PUP::er &_impl_p=*(PUP::er *)_impl_pup_er;
  _impl_p|size;
}
#endif /* CK_TEMPLATES_ONLY */


/* DEFS: mainchare Main: Chare{
Main(CkArgMsg* impl_msg);
void done(void);
void run(void);
};
 */
#ifndef CK_TEMPLATES_ONLY
 int CkIndex_Main::__idx=0;
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
/* DEFS: Main(CkArgMsg* impl_msg);
 */

CkChareID CProxy_Main::ckNew(CkArgMsg* impl_msg, int impl_onPE)
{
  CkChareID impl_ret;
  CkCreateChare(CkIndex_Main::__idx, CkIndex_Main::idx_Main_CkArgMsg(), impl_msg, &impl_ret, impl_onPE);
  return impl_ret;
}

void CProxy_Main::ckNew(CkArgMsg* impl_msg, CkChareID* pcid, int impl_onPE)
{
  CkCreateChare(CkIndex_Main::__idx, CkIndex_Main::idx_Main_CkArgMsg(), impl_msg, pcid, impl_onPE);
}

  CProxy_Main::CProxy_Main(CkArgMsg* impl_msg, int impl_onPE)
{
  CkChareID impl_ret;
  CkCreateChare(CkIndex_Main::__idx, CkIndex_Main::idx_Main_CkArgMsg(), impl_msg, &impl_ret, impl_onPE);
  ckSetChareID(impl_ret);
}

// Entry point registration function

int CkIndex_Main::reg_Main_CkArgMsg() {
  int epidx = CkRegisterEp("Main(CkArgMsg* impl_msg)",
      _call_Main_CkArgMsg, CMessage_CkArgMsg::__idx, __idx, 0);
  return epidx;
}


void CkIndex_Main::_call_Main_CkArgMsg(void* impl_msg, void* impl_obj_void)
{
  Main* impl_obj = static_cast<Main *>(impl_obj_void);
  new (impl_obj) Main((CkArgMsg*)impl_msg);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void done(void);
 */

void CProxy_Main::done(void)
{
  ckCheck();
  void *impl_msg = CkAllocSysMsg();
  if (ckIsDelegated()) {
    int destPE=CkChareMsgPrep(CkIndex_Main::idx_done_void(), impl_msg, &ckGetChareID());
    if (destPE!=-1) ckDelegatedTo()->ChareSend(ckDelegatedPtr(),CkIndex_Main::idx_done_void(), impl_msg, &ckGetChareID(),destPE);
  }
  else CkSendMsg(CkIndex_Main::idx_done_void(), impl_msg, &ckGetChareID(),0);
}

// Entry point registration function

int CkIndex_Main::reg_done_void() {
  int epidx = CkRegisterEp("done(void)",
      _call_done_void, 0, __idx, 0);
  return epidx;
}


void CkIndex_Main::_call_done_void(void* impl_msg, void* impl_obj_void)
{
  Main* impl_obj = static_cast<Main *>(impl_obj_void);
  CkFreeSysMsg(impl_msg);
  impl_obj->done();
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void run(void);
 */

void CProxy_Main::run(void)
{
  ckCheck();
  void *impl_msg = CkAllocSysMsg();
  if (ckIsDelegated()) {
    int destPE=CkChareMsgPrep(CkIndex_Main::idx_run_void(), impl_msg, &ckGetChareID());
    if (destPE!=-1) ckDelegatedTo()->ChareSend(ckDelegatedPtr(),CkIndex_Main::idx_run_void(), impl_msg, &ckGetChareID(),destPE);
  }
  else CkSendMsg(CkIndex_Main::idx_run_void(), impl_msg, &ckGetChareID(),0);
}

// Entry point registration function

int CkIndex_Main::reg_run_void() {
  int epidx = CkRegisterEp("run(void)",
      _call_run_void, 0, __idx, 0);
  return epidx;
}


void CkIndex_Main::_call_run_void(void* impl_msg, void* impl_obj_void)
{
  Main* impl_obj = static_cast<Main *>(impl_obj_void);
  CkFreeSysMsg(impl_msg);
  impl_obj->run();
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
void CkIndex_Main::__register(const char *s, size_t size) {
  __idx = CkRegisterChare(s, size, TypeMainChare);
  CkRegisterBase(__idx, CkIndex_Chare::__idx);
  // REG: Main(CkArgMsg* impl_msg);
  idx_Main_CkArgMsg();
  CkRegisterMainChare(__idx, idx_Main_CkArgMsg());

  // REG: void done(void);
  idx_done_void();

  // REG: void run(void);
  idx_run_void();

  Main::__sdag_register(); 
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
void Main::run() {
    _TRACE_END_EXECUTE(); 
    _slist_0();
    _TRACE_BEGIN_EXECUTE_DETAILED(-1, -1, _dummyEP, CkMyPe(), 0, NULL); 
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void Main::run_end() {
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void Main::_slist_0() {
    _for_0();
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void Main::_slist_0_end() {
    run_end();
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void Main::_for_0() {
    count = 0;
    if ( count < chareDimension*chareDimension) {
      _slist_1();
    } else {
      _atomic_1();
    }
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void Main::_for_0_end() {
    count++;
    if ( count < chareDimension*chareDimension) {
      _slist_1();
    } else {
      _atomic_1();
    }
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void Main::_slist_1() {
    _when_0();
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void Main::_slist_1_end() {
    _for_0_end();
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
int Main::_when_0() {
    CMsgBuffer *done_buf;

    done_buf = __cDep->getMessage(0); // SEGFAULT? __cDep = 0x0? Did you call __sdag_init() in your constructor?

    if ((done_buf != 0)) {
       CkFreeSysMsg((void *) done_buf->msg);
       __cDep->removeMessage(done_buf);
      delete done_buf;
       _atomic_0();
       return 1;
    } else {
       CWhenTrigger *tr;
       tr = new CWhenTrigger(0, 1, 0, 1);
       tr->args[0] = (size_t)0xFF;
       tr->anyEntries[0] = 0;
       __cDep->Register(tr);
       return 0;
    }
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void Main::_when_0_end() {
    _slist_1_end();
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void Main::_atomic_0() {
    _TRACE_BEGIN_EXECUTE_DETAILED(-1, -1, (_sdag_idx_Main_atomic_0()), CkMyPe(), 0, NULL); 
    
                                                                                    
                
    _TRACE_END_EXECUTE(); 
    _when_0_end();
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void Main::_atomic_1() {
    _TRACE_BEGIN_EXECUTE_DETAILED(-1, -1, (_sdag_idx_Main_atomic_1()), CkMyPe(), 0, NULL); 
    
                iterations++;
                CkPrintf("\nStart iteration %d", iterations);
                if(iterations < ITERATIONS)
                    pixel.run();
                else CkExit();
                mainProxy.run();
            
    _TRACE_END_EXECUTE(); 
    _slist_0_end();
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void Main::done(void){
    CWhenTrigger *tr;
    void* _bgParentLog = NULL;
    CMsgBuffer* cmsgbuf;
    __cDep->bufferMessage(0, (void *) CkAllocSysMsg(), (void*) _bgParentLog, 0);
    tr = __cDep->getTrigger(0, 0);
    if (tr == 0)
      return;
    _TRACE_END_EXECUTE(); 
    {
        tr->args[0] = 0;
        _when_0();
        delete tr;
        _TRACE_BEGIN_EXECUTE_DETAILED(-1, -1, _dummyEP, CkMyPe(), 0, NULL); 
        return;
    }
}

#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
void Main::__sdag_init() {
    __cDep = new CDep(1,1);
    __cDep->addDepends(0,0);
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void Main::__sdag_register() {
    (void)_sdag_idx_Main_atomic_0();
    (void)_sdag_idx_Main_atomic_1();
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
int Main::_sdag_idx_Main_atomic_0() {
  static int epidx = _sdag_reg_Main_atomic_0();
  return epidx;
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
int Main::_sdag_reg_Main_atomic_0() {
  return CkRegisterEp("Main_atomic_0", NULL, 0, CkIndex_Main::__idx, 0);
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
int Main::_sdag_idx_Main_atomic_1() {
  static int epidx = _sdag_reg_Main_atomic_1();
  return epidx;
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
int Main::_sdag_reg_Main_atomic_1() {
  return CkRegisterEp("Main_atomic_1", NULL, 0, CkIndex_Main::__idx, 0);
}
#endif /* CK_TEMPLATES_ONLY */



#ifndef CK_TEMPLATES_ONLY
void _registermain(void)
{
  static int _done = 0; if(_done) return; _done = 1;
  CkRegisterReadonly("mainProxy","CProxy_Main",sizeof(mainProxy),(void *) &mainProxy,__xlater_roPup_mainProxy);

  CkRegisterReadonly("Total_iterations","int",sizeof(Total_iterations),(void *) &Total_iterations,__xlater_roPup_Total_iterations);

  CkRegisterReadonly("chareDimension","int",sizeof(chareDimension),(void *) &chareDimension,__xlater_roPup_chareDimension);

  CkRegisterReadonly("size","int",sizeof(size),(void *) &size,__xlater_roPup_size);

  _registerpixelchare();

/* REG: mainchare Main: Chare{
Main(CkArgMsg* impl_msg);
void done(void);
void run(void);
};
*/
  CkIndex_Main::__register("Main", sizeof(Main));

}
extern "C" void CkRegisterMainModule(void) {
  _registermain();
}
#endif /* CK_TEMPLATES_ONLY */
