from http.server import SimpleHTTPRequestHandler, HTTPServer
import logging
import random
import socket
import os


s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.connect(("8.8.8.8", 80))
IPAddr = s.getsockname()[0]
s.close()


PORT = 4000


class S(SimpleHTTPRequestHandler):
	def _set_response(self):
		self.send_response(200)
		self.send_header('Access-Control-Allow-Origin', '*')
		self.send_header('Access-Control-Allow-Methods', '*')
		self.send_header("Access-Control-Allow-Headers", "*")
		self.send_header("Access-Control-Allow-Headers", "*")
		self.send_header("Access-Control-Expose-Headers", "*")
		self.end_headers()

	def do_OPTIONS(self):
		self.send_response(200)
		self.send_header('Access-Control-Allow-Origin', '*')
		self.send_header('Access-Control-Allow-Methods', '*')
		self.send_header("Access-Control-Allow-Headers", "*")
		self.send_header("Access-Control-Allow-Headers", "*")
		self.send_header("Access-Control-Expose-Headers", "*")
		self.end_headers()

	def do_GET(self):
		if self.path == '/upload':
			self._set_response()
			self.wfile.write(uploadHtml.encode('utf-8'))
		else :
			"""Serve a GET request."""
			f = self.send_head()
			if f:
				try:
					self.copyfile(f, self.wfile)
				finally:
					f.close()

	def do_POST(self):
		self._set_response()
		content_length = int(self.headers['Content-Length']) # <--- Gets the size of data
		post_data = self.rfile.read(content_length) # <--- Gets the data itself

		filename = self.headers['filename']
		print(filename)
		if os.path.isfile(filename):
			filename = str(random.randrange(100, 999, 2))+'_'+filename

		file = open(filename,"wb")
		file.write(post_data)
		file.close()


def run(server_class=HTTPServer, handler_class=S, port=PORT):
	logging.basicConfig(level=logging.INFO)
	server_address = ('', port)
	httpd = server_class(server_address, handler_class)
	logging.info("serving at port " + str(PORT) + "    " + IPAddr + ":" + str(PORT) + "    http://localhost" + ":" + str(PORT)+"  |  /upload \n")
	httpd.serve_forever()

uploadHtml = '''
<!DOCTYPE html>
<html>
<head>
    <title>upload</title>
</head>
<body>
    <input type="file" id="files" multiple>
    <input type="button" id="button" value="send">
    <script>
        const input = document.querySelector('#files');
        const button = document.querySelector('#button');

        button.addEventListener('click', ()=> {
            fileUpload(input.files);
        })

        const fileUpload = (files) => {
            Array.from(files).forEach(file => {
                const xhr = new XMLHttpRequest();
                xhr.open('POST', '');
                xhr.setRequestHeader('filename', file['name'])
                xhr.send(file);
            });
        };
    </script>
</body>
</html>
'''

if __name__ == '__main__':
	from sys import argv

	if len(argv) == 2:
		run(port=int(argv[1]))
	else:
		run()