import os

env_vars = os.environ

def	responseFileServer():
	file = env_vars["SCRIPT_NAME"]
	if (file.find(".php") == -1):
		# read and handle python code
	# read e write in outfile
	with open()

def handle_GETrequesition(endPoint):
	if (endPoint == "/"):
		return (responseFileServer)

def handle_requestMethod(method):
	if (method == "GET"):
		return handle_GETrequesition(env_vars["ENDPOINT"]);

if __name__ == "__main__":
	try:
		method = env_vars["REQUEST_METHOD"];
		handle_requestMethod(method)
	except Exception as e:
		print(f'Error: {e}')
