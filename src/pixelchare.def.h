/* DEFS: array PixelChare: ArrayElement{
PixelChare(CkMigrateMessage* impl_msg);
PixelChare(int width, int height);
void runStep(const vector<Shape > &shapes, const vector<lightSrc > &lights);
void run(void);
void liveVizFunc(liveVizRequestMsg* impl_msg);
};
 */
#ifndef CK_TEMPLATES_ONLY
 int CkIndex_PixelChare::__idx=0;
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
/* DEFS: PixelChare(CkMigrateMessage* impl_msg);
 */
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: PixelChare(int width, int height);
 */

void CProxyElement_PixelChare::insert(int width, int height, int onPE, const CkEntryOptions *impl_e_opts)
{ 
  //Marshall: int width, int height
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    implP|width;
    implP|height;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    implP|width;
    implP|height;
  }
   ckInsert((CkArrayMessage *)impl_msg,CkIndex_PixelChare::idx_PixelChare_marshall1(),onPE);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void runStep(const vector<Shape > &shapes, const vector<lightSrc > &lights);
 */

void CProxyElement_PixelChare::runStep(const vector<Shape > &shapes, const vector<lightSrc > &lights, const CkEntryOptions *impl_e_opts) 
{
  ckCheck();
  //Marshall: const vector<Shape > &shapes, const vector<lightSrc > &lights
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    //Have to cast away const-ness to get pup routine
    implP|(vector<Shape > &)shapes;
    //Have to cast away const-ness to get pup routine
    implP|(vector<lightSrc > &)lights;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    //Have to cast away const-ness to get pup routine
    implP|(vector<Shape > &)shapes;
    //Have to cast away const-ness to get pup routine
    implP|(vector<lightSrc > &)lights;
  }
  CkArrayMessage *impl_amsg=(CkArrayMessage *)impl_msg;
  impl_amsg->array_setIfNotThere(CkArray_IfNotThere_buffer);
  ckSend(impl_amsg, CkIndex_PixelChare::idx_runStep_marshall2(),0);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void run(void);
 */

void CProxyElement_PixelChare::run(void) 
{
  ckCheck();
  void *impl_msg = CkAllocSysMsg();
  CkArrayMessage *impl_amsg=(CkArrayMessage *)impl_msg;
  impl_amsg->array_setIfNotThere(CkArray_IfNotThere_buffer);
  ckSend(impl_amsg, CkIndex_PixelChare::idx_run_void(),0);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void liveVizFunc(liveVizRequestMsg* impl_msg);
 */

void CProxyElement_PixelChare::liveVizFunc(liveVizRequestMsg* impl_msg) 
{
  ckCheck();
  CkArrayMessage *impl_amsg=(CkArrayMessage *)impl_msg;
  impl_amsg->array_setIfNotThere(CkArray_IfNotThere_buffer);
  ckSend(impl_amsg, CkIndex_PixelChare::idx_liveVizFunc_liveVizRequestMsg(),0);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: PixelChare(CkMigrateMessage* impl_msg);
 */

// Entry point registration function

int CkIndex_PixelChare::reg_PixelChare_CkMigrateMessage() {
  int epidx = CkRegisterEp("PixelChare(CkMigrateMessage* impl_msg)",
      _call_PixelChare_CkMigrateMessage, 0, __idx, 0);
  return epidx;
}


void CkIndex_PixelChare::_call_PixelChare_CkMigrateMessage(void* impl_msg, void* impl_obj_void)
{
  PixelChare* impl_obj = static_cast<PixelChare *>(impl_obj_void);
  new (impl_obj) PixelChare((CkMigrateMessage*)impl_msg);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: PixelChare(int width, int height);
 */

CkArrayID CProxy_PixelChare::ckNew(int width, int height, const CkArrayOptions &opts, const CkEntryOptions *impl_e_opts)
{ 
  //Marshall: int width, int height
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    implP|width;
    implP|height;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    implP|width;
    implP|height;
  }
   return ckCreateArray((CkArrayMessage *)impl_msg,CkIndex_PixelChare::idx_PixelChare_marshall1(),opts);
}

CkArrayID CProxy_PixelChare::ckNew(int width, int height, const int s1, const int s2, const CkEntryOptions *impl_e_opts)
{ 
  //Marshall: int width, int height
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    implP|width;
    implP|height;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    implP|width;
    implP|height;
  }
   return ckCreateArray((CkArrayMessage *)impl_msg,CkIndex_PixelChare::idx_PixelChare_marshall1(),CkArrayOptions(s1, s2));
}

// Entry point registration function

int CkIndex_PixelChare::reg_PixelChare_marshall1() {
  int epidx = CkRegisterEp("PixelChare(int width, int height)",
      _call_PixelChare_marshall1, CkMarshallMsg::__idx, __idx, 0+CK_EP_NOKEEP);
  CkRegisterMarshallUnpackFn(epidx, _callmarshall_PixelChare_marshall1);
  CkRegisterMessagePupFn(epidx, _marshallmessagepup_PixelChare_marshall1);

  return epidx;
}


void CkIndex_PixelChare::_call_PixelChare_marshall1(void* impl_msg, void* impl_obj_void)
{
  PixelChare* impl_obj = static_cast<PixelChare *>(impl_obj_void);
  CkMarshallMsg *impl_msg_typed=(CkMarshallMsg *)impl_msg;
  char *impl_buf=impl_msg_typed->msgBuf;
  /*Unmarshall pup'd fields: int width, int height*/
  PUP::fromMem implP(impl_buf);
  int width; implP|width;
  int height; implP|height;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  new (impl_obj) PixelChare(width, height);
}

int CkIndex_PixelChare::_callmarshall_PixelChare_marshall1(char* impl_buf, void* impl_obj_void) {
  PixelChare* impl_obj = static_cast< PixelChare *>(impl_obj_void);
  /*Unmarshall pup'd fields: int width, int height*/
  PUP::fromMem implP(impl_buf);
  int width; implP|width;
  int height; implP|height;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  new (impl_obj) PixelChare(width, height);
  return implP.size();
}

void CkIndex_PixelChare::_marshallmessagepup_PixelChare_marshall1(PUP::er &implDestP,void *impl_msg) {
  CkMarshallMsg *impl_msg_typed=(CkMarshallMsg *)impl_msg;
  char *impl_buf=impl_msg_typed->msgBuf;
  /*Unmarshall pup'd fields: int width, int height*/
  PUP::fromMem implP(impl_buf);
  int width; implP|width;
  int height; implP|height;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  if (implDestP.hasComments()) implDestP.comment("width");
  implDestP|width;
  if (implDestP.hasComments()) implDestP.comment("height");
  implDestP|height;
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void runStep(const vector<Shape > &shapes, const vector<lightSrc > &lights);
 */

void CProxy_PixelChare::runStep(const vector<Shape > &shapes, const vector<lightSrc > &lights, const CkEntryOptions *impl_e_opts) 
{
  ckCheck();
  //Marshall: const vector<Shape > &shapes, const vector<lightSrc > &lights
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    //Have to cast away const-ness to get pup routine
    implP|(vector<Shape > &)shapes;
    //Have to cast away const-ness to get pup routine
    implP|(vector<lightSrc > &)lights;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    //Have to cast away const-ness to get pup routine
    implP|(vector<Shape > &)shapes;
    //Have to cast away const-ness to get pup routine
    implP|(vector<lightSrc > &)lights;
  }
  CkArrayMessage *impl_amsg=(CkArrayMessage *)impl_msg;
  impl_amsg->array_setIfNotThere(CkArray_IfNotThere_buffer);
  ckBroadcast(impl_amsg, CkIndex_PixelChare::idx_runStep_marshall2(),0);
}

// Entry point registration function

int CkIndex_PixelChare::reg_runStep_marshall2() {
  int epidx = CkRegisterEp("runStep(const vector<Shape > &shapes, const vector<lightSrc > &lights)",
      _call_runStep_marshall2, CkMarshallMsg::__idx, __idx, 0+CK_EP_NOKEEP);
  CkRegisterMarshallUnpackFn(epidx, _callmarshall_runStep_marshall2);
  CkRegisterMessagePupFn(epidx, _marshallmessagepup_runStep_marshall2);

  return epidx;
}


void CkIndex_PixelChare::_call_runStep_marshall2(void* impl_msg, void* impl_obj_void)
{
  PixelChare* impl_obj = static_cast<PixelChare *>(impl_obj_void);
  CkMarshallMsg *impl_msg_typed=(CkMarshallMsg *)impl_msg;
  char *impl_buf=impl_msg_typed->msgBuf;
  /*Unmarshall pup'd fields: const vector<Shape > &shapes, const vector<lightSrc > &lights*/
  PUP::fromMem implP(impl_buf);
  vector<Shape > shapes; implP|shapes;
  vector<lightSrc > lights; implP|lights;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  impl_obj->runStep(shapes, lights);
}

int CkIndex_PixelChare::_callmarshall_runStep_marshall2(char* impl_buf, void* impl_obj_void) {
  PixelChare* impl_obj = static_cast< PixelChare *>(impl_obj_void);
  /*Unmarshall pup'd fields: const vector<Shape > &shapes, const vector<lightSrc > &lights*/
  PUP::fromMem implP(impl_buf);
  vector<Shape > shapes; implP|shapes;
  vector<lightSrc > lights; implP|lights;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  impl_obj->runStep(shapes, lights);
  return implP.size();
}

void CkIndex_PixelChare::_marshallmessagepup_runStep_marshall2(PUP::er &implDestP,void *impl_msg) {
  CkMarshallMsg *impl_msg_typed=(CkMarshallMsg *)impl_msg;
  char *impl_buf=impl_msg_typed->msgBuf;
  /*Unmarshall pup'd fields: const vector<Shape > &shapes, const vector<lightSrc > &lights*/
  PUP::fromMem implP(impl_buf);
  vector<Shape > shapes; implP|shapes;
  vector<lightSrc > lights; implP|lights;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  if (implDestP.hasComments()) implDestP.comment("shapes");
  implDestP|shapes;
  if (implDestP.hasComments()) implDestP.comment("lights");
  implDestP|lights;
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void run(void);
 */

void CProxy_PixelChare::run(void) 
{
  ckCheck();
  void *impl_msg = CkAllocSysMsg();
  CkArrayMessage *impl_amsg=(CkArrayMessage *)impl_msg;
  impl_amsg->array_setIfNotThere(CkArray_IfNotThere_buffer);
  ckBroadcast(impl_amsg, CkIndex_PixelChare::idx_run_void(),0);
}

// Entry point registration function

int CkIndex_PixelChare::reg_run_void() {
  int epidx = CkRegisterEp("run(void)",
      _call_run_void, 0, __idx, 0);
  return epidx;
}


void CkIndex_PixelChare::_call_run_void(void* impl_msg, void* impl_obj_void)
{
  PixelChare* impl_obj = static_cast<PixelChare *>(impl_obj_void);
  CkFreeSysMsg(impl_msg);
  impl_obj->run();
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void liveVizFunc(liveVizRequestMsg* impl_msg);
 */

void CProxy_PixelChare::liveVizFunc(liveVizRequestMsg* impl_msg) 
{
  ckCheck();
  CkArrayMessage *impl_amsg=(CkArrayMessage *)impl_msg;
  impl_amsg->array_setIfNotThere(CkArray_IfNotThere_buffer);
  ckBroadcast(impl_amsg, CkIndex_PixelChare::idx_liveVizFunc_liveVizRequestMsg(),0);
}

// Entry point registration function

int CkIndex_PixelChare::reg_liveVizFunc_liveVizRequestMsg() {
  int epidx = CkRegisterEp("liveVizFunc(liveVizRequestMsg* impl_msg)",
      _call_liveVizFunc_liveVizRequestMsg, CMessage_liveVizRequestMsg::__idx, __idx, 0);
  return epidx;
}


void CkIndex_PixelChare::_call_liveVizFunc_liveVizRequestMsg(void* impl_msg, void* impl_obj_void)
{
  PixelChare* impl_obj = static_cast<PixelChare *>(impl_obj_void);
  impl_obj->liveVizFunc((liveVizRequestMsg*)impl_msg);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: PixelChare(CkMigrateMessage* impl_msg);
 */
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: PixelChare(int width, int height);
 */
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void runStep(const vector<Shape > &shapes, const vector<lightSrc > &lights);
 */

void CProxySection_PixelChare::runStep(const vector<Shape > &shapes, const vector<lightSrc > &lights, const CkEntryOptions *impl_e_opts) 
{
  ckCheck();
  //Marshall: const vector<Shape > &shapes, const vector<lightSrc > &lights
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    //Have to cast away const-ness to get pup routine
    implP|(vector<Shape > &)shapes;
    //Have to cast away const-ness to get pup routine
    implP|(vector<lightSrc > &)lights;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    //Have to cast away const-ness to get pup routine
    implP|(vector<Shape > &)shapes;
    //Have to cast away const-ness to get pup routine
    implP|(vector<lightSrc > &)lights;
  }
  CkArrayMessage *impl_amsg=(CkArrayMessage *)impl_msg;
  impl_amsg->array_setIfNotThere(CkArray_IfNotThere_buffer);
  ckSend(impl_amsg, CkIndex_PixelChare::idx_runStep_marshall2(),0);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void run(void);
 */

void CProxySection_PixelChare::run(void) 
{
  ckCheck();
  void *impl_msg = CkAllocSysMsg();
  CkArrayMessage *impl_amsg=(CkArrayMessage *)impl_msg;
  impl_amsg->array_setIfNotThere(CkArray_IfNotThere_buffer);
  ckSend(impl_amsg, CkIndex_PixelChare::idx_run_void(),0);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void liveVizFunc(liveVizRequestMsg* impl_msg);
 */

void CProxySection_PixelChare::liveVizFunc(liveVizRequestMsg* impl_msg) 
{
  ckCheck();
  CkArrayMessage *impl_amsg=(CkArrayMessage *)impl_msg;
  impl_amsg->array_setIfNotThere(CkArray_IfNotThere_buffer);
  ckSend(impl_amsg, CkIndex_PixelChare::idx_liveVizFunc_liveVizRequestMsg(),0);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
void CkIndex_PixelChare::__register(const char *s, size_t size) {
  __idx = CkRegisterChare(s, size, TypeArray);
  CkRegisterBase(__idx, CkIndex_ArrayElement::__idx);
  // REG: PixelChare(CkMigrateMessage* impl_msg);
  idx_PixelChare_CkMigrateMessage();
  CkRegisterMigCtor(__idx, idx_PixelChare_CkMigrateMessage());

  // REG: PixelChare(int width, int height);
  idx_PixelChare_marshall1();

  // REG: void runStep(const vector<Shape > &shapes, const vector<lightSrc > &lights);
  idx_runStep_marshall2();

  // REG: void run(void);
  idx_run_void();

  // REG: void liveVizFunc(liveVizRequestMsg* impl_msg);
  idx_liveVizFunc_liveVizRequestMsg();

  PixelChare::__sdag_register(); 
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
void PixelChare::run() {
    _TRACE_END_EXECUTE(); 
    _slist_0();
    _TRACE_BEGIN_EXECUTE_DETAILED(-1, -1, _dummyEP, CkMyPe(), 0, NULL); 
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void PixelChare::run_end() {
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void PixelChare::_slist_0() {
    _atomic_0();
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void PixelChare::_slist_0_end() {
    run_end();
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void PixelChare::_atomic_0() {
    _TRACE_BEGIN_EXECUTE_DETAILED(-1, -1, (_sdag_idx_PixelChare_Interation_block()), CkMyPe(), 0, NULL); 
    
                                                         
                                                  
                   
                    doWork();
                    iteration++;
                                                                             
                    mainProxy.done();
                   /* run();
                }
                else
                {
                        mainProxy.done();
                }*/
            
    _TRACE_END_EXECUTE(); 
    _slist_0_end();
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void PixelChare::__sdag_init() {
    __cDep = new CDep(0,0);
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void PixelChare::__sdag_register() {
    (void)_sdag_idx_PixelChare_Interation_block();
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
int PixelChare::_sdag_idx_PixelChare_Interation_block() {
  static int epidx = _sdag_reg_PixelChare_Interation_block();
  return epidx;
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
int PixelChare::_sdag_reg_PixelChare_Interation_block() {
  return CkRegisterEp("PixelChare_Interation_block", NULL, 0, CkIndex_PixelChare::__idx, 0);
}
#endif /* CK_TEMPLATES_ONLY */



#ifndef CK_TEMPLATES_ONLY
void _registerpixelchare(void)
{
  static int _done = 0; if(_done) return; _done = 1;
/* REG: array PixelChare: ArrayElement{
PixelChare(CkMigrateMessage* impl_msg);
PixelChare(int width, int height);
void runStep(const vector<Shape > &shapes, const vector<lightSrc > &lights);
void run(void);
void liveVizFunc(liveVizRequestMsg* impl_msg);
};
*/
  CkIndex_PixelChare::__register("PixelChare", sizeof(PixelChare));

}
#endif /* CK_TEMPLATES_ONLY */
