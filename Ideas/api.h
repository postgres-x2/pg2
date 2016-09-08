/*
 * API to GTM from various components
 */

/*
 * Common API
 */
GTM_errno GTM_getErrno(GTM_Handle *handle);
char * GTM_errstr(GTM_errno gtm_errno);
void GTM_HandleFree(GTM_Handle *handle);

/*
 * API from Postmaster
 */

GTM_Handle * PM_connectGtm(GTM_errno *gtm_errno);
GTM_Handle * PM_disconnectGtm(GTM_Handle *handle);
GTM_Handle * PM_removeBackend(GTM_Handle *handle, pid backend_pid);

/*
 * API from GTM (to remote GTM)
 */

GTM_Handle * GTM_connectGtm(host, port);
GTM_Handle * GTM_disconnectGtm(GTM_Handle *handle);
int GTM_registerMe(GTM_Handle *handle, char *nodename);
GTM_NodeList * GTM_reportClusterConfig(GTM_Handle *handle);
int GTM_reserverNodeNum(GTM_Handle *handle, char *nodename, int nodenum);
int GTM_addGtm(GTM_Handle *handle, char *nodename, int nodenum);
int GTM_cancelNodeNum(GTM_Handle *handle, char *nodename, int nodenum);
int GTM_reportNodeTmin(timestamp tmin);	/* To all the connected GTMs */
int GTM_reportNodeTmax(timestamp tmax);	/* To all the connected GTMs */
int GTM_requestTmax(GTM_Handle *handle,
					timestamp requestTm, timestamp *reportedTm);


/*
 * API from Backend
 */

GTM_Handle * BE_connectGtm();
GTM_Handle * BE_disconnectGtm(GTM_Handle *handle);
int BE_beginTxn(GTM_Handle *handle, XID localXid, int rootNode,
				XID rootXid, timestamp rootStartTm);
int BE_commitTxn(GTM_Handle *handle, XID localXid, timestamp rootTmax);
int BE_abortTxn(GTM_Handle *handle, XID localXid, timestamp rootTmax);
int BE_isGloballyCommitted(GTM_Handle *handle, XID localXid);
int BE_reportTmin(GTM_Handle *handle, timestamp rootTmin);	/* Only root */


