# API for decentralized distributed transaction management

----
## Problems with centralized GTM in PGXC and PGXL

* Any transaction need to interact with centralized GTM for any transaction events, including start, commit, abort, beginning 2PC.   Network performance determines whole clusster performance.
* GTM has a very good chance to become SPOF.   Configuring and operating GTM master and slave is sometimes painful and makes cluster operation compilcated.
* Does not allow any local operation without GTM imvolved.    Evn vacuum need GTM.
* Having dedicated node in the cluster is not good from resource consumption point of view.

----
## How to make global transaction management completely distributed and decentralized

### Calculate global transaction visibility based on the timestamp at root transaction.

* Transaction T begins at Tmin and ends at Tmax.
* Before Tmax, T is not bisible.
* When T is active, Tmax is set to NULL (typically 0).
* They are kept somewhere in each database node.
* For active transactions, where Tmax is not know,, referring transaction must know NULL time is valid at referring timestamp, say Tr.  This has to be maintained by root transaciton node.
* If any reference timestamp Tr is larger than Tz, then global transaction information whose Tmax is less than Tz can be removed.
* Such transaction timestamp should be related to root transaction node and root transaction local XID, as long as its local XID.

### Calculation of local transaction visibility
* If local XID does not appear in global transaction data above, visibility can be calculated in examtly same way as local PG.
* If it appears in the global transaction information, it should be calculated based on the above criteria and CLOG.

----
## Involved components

Each database node should have the following components involved:

1. Postmaster

* This tells GTM below to clean up crashed backend.

2. Backends

* Accepts root transaction information from parent transaction.
* Reports GTM change of global transaction status.
* Inquires GTM given transaction visibility and global status.

3. GTM

* Maintain global transaction information locally.
* Report change of minimum Tr to other GTMs in the cluster.
* Report effictive maximul timestamp value of the node to other GTMs.
* Takes care of requests from other components above.

## 
based on timestamp.

