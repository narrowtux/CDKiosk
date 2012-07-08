#ifndef UTILS_H
#define UTILS_H

#define SQL_QUERY(Object, Query)	if(!Object.exec(Query)){ qDebug()<<Object.lastQuery() << "returned error:" << Object.lastError().databaseText(); } else 
#define SQL_PREPARED_QUERY(Object)	if(!Object.exec()) {  qDebug()<<Object.lastQuery() << "returned error:" << Object.lastError().databaseText(); } else 

#endif // UTILS_H
