#ifndef _DECL_pixelchare_H_
#define _DECL_pixelchare_H_
#include "charm++.h"
/* DECLS: array PixelChare: ArrayElement{
PixelChare(CkMigrateMessage* impl_msg);
PixelChare(int width, int height);
void runStep(const vector<Shape > &shapes, const vector<lightSrc > &lights);
void run(void);
void liveVizFunc(liveVizRequestMsg* impl_msg);
};
 */
 class PixelChare;
 class CkIndex_PixelChare;
 class CProxy_PixelChare;
 class CProxyElement_PixelChare;
 class CProxySection_PixelChare;
/* --------------- index object ------------------ */
class CkIndex_PixelChare:public CProxyElement_ArrayElement{
  public:
    typedef PixelChare local_t;
    typedef CkIndex_PixelChare index_t;
    typedef CProxy_PixelChare proxy_t;
    typedef CProxyElement_PixelChare element_t;
    typedef CProxySection_PixelChare section_t;

    static int __idx;
    static void __register(const char *s, size_t size);
    /* DECLS: PixelChare(CkMigrateMessage* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_PixelChare_CkMigrateMessage();
    // Entry point index lookup
    
    inline static int idx_PixelChare_CkMigrateMessage() {
      static int epidx = reg_PixelChare_CkMigrateMessage();
      return epidx;
    }

    
    static int ckNew(CkMigrateMessage* impl_msg) { return idx_PixelChare_CkMigrateMessage(); }
    
    static void _call_PixelChare_CkMigrateMessage(void* impl_msg, void* impl_obj);
    /* DECLS: PixelChare(int width, int height);
     */
    // Entry point registration at startup
    
    static int reg_PixelChare_marshall1();
    // Entry point index lookup
    
    inline static int idx_PixelChare_marshall1() {
      static int epidx = reg_PixelChare_marshall1();
      return epidx;
    }

    
    static int ckNew(int width, int height) { return idx_PixelChare_marshall1(); }
    
    static void _call_PixelChare_marshall1(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_PixelChare_marshall1(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_PixelChare_marshall1(PUP::er &p,void *msg);
    /* DECLS: void runStep(const vector<Shape > &shapes, const vector<lightSrc > &lights);
     */
    // Entry point registration at startup
    
    static int reg_runStep_marshall2();
    // Entry point index lookup
    
    inline static int idx_runStep_marshall2() {
      static int epidx = reg_runStep_marshall2();
      return epidx;
    }

    
    inline static int idx_runStep(void (PixelChare::*)(const vector<Shape > &shapes, const vector<lightSrc > &lights) ) {
      return idx_runStep_marshall2();
    }


    
    static int runStep(const vector<Shape > &shapes, const vector<lightSrc > &lights) { return idx_runStep_marshall2(); }
    
    static void _call_runStep_marshall2(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_runStep_marshall2(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_runStep_marshall2(PUP::er &p,void *msg);
    /* DECLS: void run(void);
     */
    // Entry point registration at startup
    
    static int reg_run_void();
    // Entry point index lookup
    
    inline static int idx_run_void() {
      static int epidx = reg_run_void();
      return epidx;
    }

    
    inline static int idx_run(void (PixelChare::*)(void) ) {
      return idx_run_void();
    }


    
    static int run(void) { return idx_run_void(); }
    
    static void _call_run_void(void* impl_msg, void* impl_obj);
    /* DECLS: void liveVizFunc(liveVizRequestMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_liveVizFunc_liveVizRequestMsg();
    // Entry point index lookup
    
    inline static int idx_liveVizFunc_liveVizRequestMsg() {
      static int epidx = reg_liveVizFunc_liveVizRequestMsg();
      return epidx;
    }

    
    inline static int idx_liveVizFunc(void (PixelChare::*)(liveVizRequestMsg* impl_msg) ) {
      return idx_liveVizFunc_liveVizRequestMsg();
    }


    
    static int liveVizFunc(liveVizRequestMsg* impl_msg) { return idx_liveVizFunc_liveVizRequestMsg(); }
    
    static void _call_liveVizFunc_liveVizRequestMsg(void* impl_msg, void* impl_obj);
};
/* --------------- element proxy ------------------ */
 class CProxyElement_PixelChare : public CProxyElement_ArrayElement{
  public:
    typedef PixelChare local_t;
    typedef CkIndex_PixelChare index_t;
    typedef CProxy_PixelChare proxy_t;
    typedef CProxyElement_PixelChare element_t;
    typedef CProxySection_PixelChare section_t;

    CProxyElement_PixelChare(void) {}
    CProxyElement_PixelChare(const ArrayElement *e) : CProxyElement_ArrayElement(e){  }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxyElement_ArrayElement::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxyElement_ArrayElement::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxyElement_ArrayElement::pup(p); }

    int ckIsDelegated(void) const
    { return CProxyElement_ArrayElement::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxyElement_ArrayElement::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxyElement_ArrayElement::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxyElement_ArrayElement::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxyElement_ArrayElement::ckCheck(); }
    inline operator CkArrayID () const
    { return ckGetArrayID(); }
    inline CkArrayID ckGetArrayID(void) const
    { return CProxyElement_ArrayElement::ckGetArrayID(); }
    inline CkArray *ckLocalBranch(void) const
    { return CProxyElement_ArrayElement::ckLocalBranch(); }
    inline CkLocMgr *ckLocMgr(void) const
    { return CProxyElement_ArrayElement::ckLocMgr(); }

    inline static CkArrayID ckCreateEmptyArray(void)
    { return CProxyElement_ArrayElement::ckCreateEmptyArray(); }
    inline static CkArrayID ckCreateArray(CkArrayMessage *m,int ctor,const CkArrayOptions &opts)
    { return CProxyElement_ArrayElement::ckCreateArray(m,ctor,opts); }
    inline void ckInsertIdx(CkArrayMessage *m,int ctor,int onPe,const CkArrayIndex &idx)
    { CProxyElement_ArrayElement::ckInsertIdx(m,ctor,onPe,idx); }
    inline void doneInserting(void)
    { CProxyElement_ArrayElement::doneInserting(); }

    inline void ckBroadcast(CkArrayMessage *m, int ep, int opts=0) const
    { CProxyElement_ArrayElement::ckBroadcast(m,ep,opts); }
    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxyElement_ArrayElement::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxyElement_ArrayElement::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxyElement_ArrayElement::ckSetReductionClient(cb); }

    inline void ckInsert(CkArrayMessage *m,int ctor,int onPe)
    { CProxyElement_ArrayElement::ckInsert(m,ctor,onPe); }
    inline void ckSend(CkArrayMessage *m, int ep, int opts = 0) const
    { CProxyElement_ArrayElement::ckSend(m,ep,opts); }
    inline void *ckSendSync(CkArrayMessage *m, int ep) const
    { return CProxyElement_ArrayElement::ckSendSync(m,ep); }
    inline const CkArrayIndex &ckGetIndex() const
    { return CProxyElement_ArrayElement::ckGetIndex(); }

    PixelChare *ckLocal(void) const
    { return (PixelChare *)CProxyElement_ArrayElement::ckLocal(); }

    CProxyElement_PixelChare(const CkArrayID &aid,const CkArrayIndex2D &idx,CK_DELCTOR_PARAM)
        :CProxyElement_ArrayElement(aid,idx,CK_DELCTOR_ARGS)
    {}
    CProxyElement_PixelChare(const CkArrayID &aid,const CkArrayIndex2D &idx)
        :CProxyElement_ArrayElement(aid,idx)
    {}

    CProxyElement_PixelChare(const CkArrayID &aid,const CkArrayIndex &idx,CK_DELCTOR_PARAM)
        :CProxyElement_ArrayElement(aid,idx,CK_DELCTOR_ARGS)
    {}
    CProxyElement_PixelChare(const CkArrayID &aid,const CkArrayIndex &idx)
        :CProxyElement_ArrayElement(aid,idx)
    {}
/* DECLS: PixelChare(CkMigrateMessage* impl_msg);
 */

/* DECLS: PixelChare(int width, int height);
 */
    
    void insert(int width, int height, int onPE=-1, const CkEntryOptions *impl_e_opts=NULL);
/* DECLS: void runStep(const vector<Shape > &shapes, const vector<lightSrc > &lights);
 */
    
    void runStep(const vector<Shape > &shapes, const vector<lightSrc > &lights, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void run(void);
 */
    
    void run(void) ;

/* DECLS: void liveVizFunc(liveVizRequestMsg* impl_msg);
 */
    
    void liveVizFunc(liveVizRequestMsg* impl_msg) ;

};
PUPmarshall(CProxyElement_PixelChare)
/* ---------------- collective proxy -------------- */
 class CProxy_PixelChare : public CProxy_ArrayElement{
  public:
    typedef PixelChare local_t;
    typedef CkIndex_PixelChare index_t;
    typedef CProxy_PixelChare proxy_t;
    typedef CProxyElement_PixelChare element_t;
    typedef CProxySection_PixelChare section_t;

    CProxy_PixelChare(void) {}
    CProxy_PixelChare(const ArrayElement *e) : CProxy_ArrayElement(e){  }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxy_ArrayElement::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxy_ArrayElement::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxy_ArrayElement::pup(p); }

    int ckIsDelegated(void) const
    { return CProxy_ArrayElement::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxy_ArrayElement::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxy_ArrayElement::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxy_ArrayElement::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxy_ArrayElement::ckCheck(); }
    inline operator CkArrayID () const
    { return ckGetArrayID(); }
    inline CkArrayID ckGetArrayID(void) const
    { return CProxy_ArrayElement::ckGetArrayID(); }
    inline CkArray *ckLocalBranch(void) const
    { return CProxy_ArrayElement::ckLocalBranch(); }
    inline CkLocMgr *ckLocMgr(void) const
    { return CProxy_ArrayElement::ckLocMgr(); }

    inline static CkArrayID ckCreateEmptyArray(void)
    { return CProxy_ArrayElement::ckCreateEmptyArray(); }
    inline static CkArrayID ckCreateArray(CkArrayMessage *m,int ctor,const CkArrayOptions &opts)
    { return CProxy_ArrayElement::ckCreateArray(m,ctor,opts); }
    inline void ckInsertIdx(CkArrayMessage *m,int ctor,int onPe,const CkArrayIndex &idx)
    { CProxy_ArrayElement::ckInsertIdx(m,ctor,onPe,idx); }
    inline void doneInserting(void)
    { CProxy_ArrayElement::doneInserting(); }

    inline void ckBroadcast(CkArrayMessage *m, int ep, int opts=0) const
    { CProxy_ArrayElement::ckBroadcast(m,ep,opts); }
    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxy_ArrayElement::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxy_ArrayElement::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxy_ArrayElement::ckSetReductionClient(cb); }

    static CkArrayID ckNew(void) { return ckCreateEmptyArray(); }
    // Generalized array indexing:
    CProxyElement_PixelChare operator [] (const CkArrayIndex2D &idx) const
    { return CProxyElement_PixelChare(ckGetArrayID(), idx, CK_DELCTOR_CALL); }
    CProxyElement_PixelChare operator() (const CkArrayIndex2D &idx) const
    { return CProxyElement_PixelChare(ckGetArrayID(), idx, CK_DELCTOR_CALL); }
    CProxyElement_PixelChare operator () (int i0,int i1) const 
        {return CProxyElement_PixelChare(ckGetArrayID(), CkArrayIndex2D(i0,i1), CK_DELCTOR_CALL);}
    CProxyElement_PixelChare operator () (CkIndex2D idx) const 
        {return CProxyElement_PixelChare(ckGetArrayID(), CkArrayIndex2D(idx), CK_DELCTOR_CALL);}
    CProxy_PixelChare(const CkArrayID &aid,CK_DELCTOR_PARAM) 
        :CProxy_ArrayElement(aid,CK_DELCTOR_ARGS) {}
    CProxy_PixelChare(const CkArrayID &aid) 
        :CProxy_ArrayElement(aid) {}
/* DECLS: PixelChare(CkMigrateMessage* impl_msg);
 */

/* DECLS: PixelChare(int width, int height);
 */
    
    static CkArrayID ckNew(int width, int height, const CkArrayOptions &opts, const CkEntryOptions *impl_e_opts=NULL);
    static CkArrayID ckNew(int width, int height, const int s1, const int s2, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void runStep(const vector<Shape > &shapes, const vector<lightSrc > &lights);
 */
    
    void runStep(const vector<Shape > &shapes, const vector<lightSrc > &lights, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void run(void);
 */
    
    void run(void) ;

/* DECLS: void liveVizFunc(liveVizRequestMsg* impl_msg);
 */
    
    void liveVizFunc(liveVizRequestMsg* impl_msg) ;

};
PUPmarshall(CProxy_PixelChare)
/* ---------------- section proxy -------------- */
 class CProxySection_PixelChare : public CProxySection_ArrayElement{
  public:
    typedef PixelChare local_t;
    typedef CkIndex_PixelChare index_t;
    typedef CProxy_PixelChare proxy_t;
    typedef CProxyElement_PixelChare element_t;
    typedef CProxySection_PixelChare section_t;

    CProxySection_PixelChare(void) {}

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxySection_ArrayElement::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxySection_ArrayElement::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxySection_ArrayElement::pup(p); }

    int ckIsDelegated(void) const
    { return CProxySection_ArrayElement::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxySection_ArrayElement::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxySection_ArrayElement::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxySection_ArrayElement::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxySection_ArrayElement::ckCheck(); }
    inline operator CkArrayID () const
    { return ckGetArrayID(); }
    inline CkArrayID ckGetArrayID(void) const
    { return CProxySection_ArrayElement::ckGetArrayID(); }
    inline CkArray *ckLocalBranch(void) const
    { return CProxySection_ArrayElement::ckLocalBranch(); }
    inline CkLocMgr *ckLocMgr(void) const
    { return CProxySection_ArrayElement::ckLocMgr(); }

    inline static CkArrayID ckCreateEmptyArray(void)
    { return CProxySection_ArrayElement::ckCreateEmptyArray(); }
    inline static CkArrayID ckCreateArray(CkArrayMessage *m,int ctor,const CkArrayOptions &opts)
    { return CProxySection_ArrayElement::ckCreateArray(m,ctor,opts); }
    inline void ckInsertIdx(CkArrayMessage *m,int ctor,int onPe,const CkArrayIndex &idx)
    { CProxySection_ArrayElement::ckInsertIdx(m,ctor,onPe,idx); }
    inline void doneInserting(void)
    { CProxySection_ArrayElement::doneInserting(); }

    inline void ckBroadcast(CkArrayMessage *m, int ep, int opts=0) const
    { CProxySection_ArrayElement::ckBroadcast(m,ep,opts); }
    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxySection_ArrayElement::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxySection_ArrayElement::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxySection_ArrayElement::ckSetReductionClient(cb); }

    inline void ckSend(CkArrayMessage *m, int ep, int opts = 0)
    { CProxySection_ArrayElement::ckSend(m,ep,opts); }
    inline CkSectionInfo &ckGetSectionInfo()
    { return CProxySection_ArrayElement::ckGetSectionInfo(); }
    inline CkSectionID *ckGetSectionIDs()
    { return CProxySection_ArrayElement::ckGetSectionIDs(); }
    inline CkSectionID &ckGetSectionID()
    { return CProxySection_ArrayElement::ckGetSectionID(); }
    inline CkSectionID &ckGetSectionID(int i)
    { return CProxySection_ArrayElement::ckGetSectionID(i); }
    inline CkArrayID ckGetArrayIDn(int i) const
    { return CProxySection_ArrayElement::ckGetArrayIDn(i); } 
    inline CkArrayIndex *ckGetArrayElements() const
    { return CProxySection_ArrayElement::ckGetArrayElements(); }
    inline CkArrayIndex *ckGetArrayElements(int i) const
    { return CProxySection_ArrayElement::ckGetArrayElements(i); }
    inline int ckGetNumElements() const
    { return CProxySection_ArrayElement::ckGetNumElements(); } 
    inline int ckGetNumElements(int i) const
    { return CProxySection_ArrayElement::ckGetNumElements(i); }    // Generalized array indexing:
    CProxyElement_PixelChare operator [] (const CkArrayIndex2D &idx) const
        {return CProxyElement_PixelChare(ckGetArrayID(), idx, CK_DELCTOR_CALL);}
    CProxyElement_PixelChare operator() (const CkArrayIndex2D &idx) const
        {return CProxyElement_PixelChare(ckGetArrayID(), idx, CK_DELCTOR_CALL);}
    CProxyElement_PixelChare operator () (int idx) const 
        {return CProxyElement_PixelChare(ckGetArrayID(), *(CkArrayIndex2D*)&ckGetArrayElements()[idx], CK_DELCTOR_CALL);}
    static CkSectionID ckNew(const CkArrayID &aid, CkArrayIndex2D *elems, int nElems) {
      return CkSectionID(aid, elems, nElems);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, int l1, int u1, int s1, int l2, int u2, int s2) {
      CkVec<CkArrayIndex2D> al;
      for (int i=l1; i<=u1; i+=s1) 
        for (int j=l2; j<=u2; j+=s2) 
          al.push_back(CkArrayIndex2D(i, j));
      return CkSectionID(aid, al.getVec(), al.size());
    } 
    CProxySection_PixelChare(const CkArrayID &aid, CkArrayIndex *elems, int nElems, CK_DELCTOR_PARAM) 
        :CProxySection_ArrayElement(aid,elems,nElems,CK_DELCTOR_ARGS) {}
    CProxySection_PixelChare(const CkArrayID &aid, CkArrayIndex *elems, int nElems) 
        :CProxySection_ArrayElement(aid,elems,nElems) {}
    CProxySection_PixelChare(const CkSectionID &sid)       :CProxySection_ArrayElement(sid) {}
    CProxySection_PixelChare(int n, const CkArrayID *aid, CkArrayIndex const * const *elems, const int *nElems, CK_DELCTOR_PARAM) 
        :CProxySection_ArrayElement(n,aid,elems,nElems,CK_DELCTOR_ARGS) {}
    CProxySection_PixelChare(int n, const CkArrayID *aid, CkArrayIndex const * const *elems, const int *nElems) 
        :CProxySection_ArrayElement(n,aid,elems,nElems) {}
    static CkSectionID ckNew(const CkArrayID &aid, CkArrayIndex *elems, int nElems) {
      return CkSectionID(aid, elems, nElems);
    } 
/* DECLS: PixelChare(CkMigrateMessage* impl_msg);
 */

/* DECLS: PixelChare(int width, int height);
 */
    

/* DECLS: void runStep(const vector<Shape > &shapes, const vector<lightSrc > &lights);
 */
    
    void runStep(const vector<Shape > &shapes, const vector<lightSrc > &lights, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void run(void);
 */
    
    void run(void) ;

/* DECLS: void liveVizFunc(liveVizRequestMsg* impl_msg);
 */
    
    void liveVizFunc(liveVizRequestMsg* impl_msg) ;

};
PUPmarshall(CProxySection_PixelChare)
#define PixelChare_SDAG_CODE                                                   \
public:                                                                        \
  void run();                                                                  \
private:                                                                       \
  void run_end();                                                              \
  void _slist_0();                                                             \
  void _slist_0_end();                                                         \
  void _atomic_0();                                                            \
public:                                                                        \
private:                                                                       \
  CDep *__cDep;                                                                \
  void __sdag_init();                                                          \
public:                                                                        \
  void __sdag_pup(PUP::er& p) {                                                \
    if (__cDep) { __cDep->pup(p); }                                            \
  }                                                                            \
  static void __sdag_register();                                               \
  static int _sdag_idx_PixelChare_Interation_block();                          \
  static int _sdag_reg_PixelChare_Interation_block();                          \

typedef CBaseT1<ArrayElementT<CkIndex2D>, CProxy_PixelChare> CBase_PixelChare;

extern void _registerpixelchare(void);
#endif
