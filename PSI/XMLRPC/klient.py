import xmlrpclib
import time
import datetime

server = xmlrpclib.Server('http://localhost:2608')
t = datetime.datetime.now()
s = time.mktime(t.timetuple())
print server.gettime(s)
