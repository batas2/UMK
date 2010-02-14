import SimpleXMLRPCServer
import time
import datetime

class rpcxml_time:
    def gettime(self, t):
	d = datetime.datetime.fromtimestamp(t)
	return d.strftime("%Y-%m-%d %H:%M:%S");
    
server = SimpleXMLRPCServer.SimpleXMLRPCServer(("localhost", 2608))
server.register_instance(rpcxml_time())
server.serve_forever()
