import os
import tornado
import tornado.web
import tornado.ioloop
import tornado.httpserver


class TestHandler(tornado.web.RequestHandler):
    def get(self):
        self.render("main.html", title="NyaTest")

settings = dict(
    template_path=os.path.join(os.path.dirname(__file__), "template"),
    static_path=os.path.join(os.path.dirname(__file__), "static"),
    debug=True
)
application = tornado.web.Application([
    (r"/", TestHandler),
], **settings)
http_server = tornado.httpserver.HTTPServer(application)
http_server.listen(8888)
tornado.ioloop.IOLoop.instance().start()
