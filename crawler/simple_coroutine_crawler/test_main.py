import json
import asyncio
import logging
import bs4.element
from bs4 import BeautifulSoup
from crawler import CrawlerBase


class Crawler(CrawlerBase):
    def __init__(self, **kwargs):
        super(Crawler, self).__init__(**kwargs)
        self.result = list()

    def parse_resp(self, resp):
        def get_content(obj, selector_str, return_func=lambda x: x.get_text()):
            _t = obj.select(selector_str)
            return return_func(_t[0]) if len(_t) > 0 else None

        try:
            soup = BeautifulSoup(resp, 'lxml')
            _list = soup.select("#h-content > div.uk-container > div.h-threads-list > div")
            for child in _list:
                img = get_content(child, "div.h-threads-item-main > div.h-threads-img-box > a", lambda x: x['href'])
                title = get_content(child, "div.h-threads-item-main > div.h-threads-info > span.h-threads-info-title",
                                    lambda x: x.get_text().strip())
                time = get_content(child, "div.h-threads-item-main > div.h-threads-info > span.h-threads-info-createdat")
                uid = get_content(child, "div.h-threads-item-main > div.h-threads-info > span.h-threads-info-uid")
                id = get_content(child, "div.h-threads-item-main > div.h-threads-info > a.h-threads-info-id")
                href = get_content(child, "div.h-threads-item-main > div.h-threads-info > a.h-threads-info-id",
                                   lambda x: x['href'])
                content = get_content(child, "div.h-threads-item-main > div.h-threads-content",
                                      lambda x: x.get_text().strip())
                replys = get_content(child, "div.h-threads-item-replys", lambda x: x)

                replys_list = list()
                if replys and replys.children:
                    for _child in replys.children:
                        if not isinstance(_child, bs4.element.Tag):
                            continue
                        reply_img = get_content(_child, "div.h-threads-item-reply-main > div.h-threads-img-box > a",
                                                lambda x: x['href'])
                        reply_title = get_content(_child, "div.h-threads-item-reply-main > div.h-threads-info >"
                                                          " span.h-threads-info-title", lambda x: x.get_text().strip())
                        reply_time = get_content(_child, "div.h-threads-item-reply-main > div.h-threads-info > "
                                                         "span.h-threads-info-createdat")
                        reply_uid = get_content(_child, "div.h-threads-item-reply-main > div.h-threads-info >"
                                                        " span.h-threads-info-uid")
                        reply_id = get_content(_child, "div.h-threads-item-reply-main > div.h-threads-info >"
                                                       " a.h-threads-info-id")
                        reply_href = get_content(_child, "div.h-threads-item-reply-main > div.h-threads-info >"
                                                         " a.h-threads-info-id", lambda x: x['href'])
                        reply_content = get_content(_child, "div.h-threads-item-reply-main > div.h-threads-content", 
                                                    lambda x: x.get_text().strip())

                        replys_list.append({
                            "reply_img": reply_img,
                            "reply_title": reply_title,
                            "reply_time": reply_time,
                            "reply_uid": reply_uid,
                            "reply_id": reply_id,
                            "reply_href": reply_href,
                            "reply_content": reply_content,
                        })
                else:
                    replys_list = []
                info = {
                    "img": img,
                    "title": title,
                    "time": time,
                    "uid": uid,
                    "id": id,
                    "href": href,
                    "content": content,
                    "replys": replys_list
                }
                self.result.append(info)
        except Exception as e:
            print(e)

    def add_target(self):
        for page in range(20, 0, -1):
            self.add_url("http://www.kukuku.cc/%E7%BB%BC%E5%90%88%E7%89%881/{}".format(page))

    async def work(self):
        try:
            while True:
                url, max_redirect = await self.q.get()
                assert url in self.seen_urls
                resp = await self.fetch(url, headers={
                    'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:51.0) Gecko/20100101 Firefox/51.0'
                })
                self.parse_resp(resp)
                await self.sleep()
                logging.info("{} done.".format(url))
                self.q.task_done()
        except asyncio.CancelledError:
            pass

    @staticmethod
    async def sleep():
        await asyncio.sleep(5)

    def run(self):
        _loop = asyncio.get_event_loop()
        self.add_target()
        try:
            _loop.run_until_complete(self.run_work())

            with open("result.json", "w", encoding="utf-8") as _f:
                _f.write(json.dumps(self.result, sort_keys=True, indent=4, ensure_ascii=False))
        except KeyboardInterrupt:
            logging.debug('\nInterrupted\n')
        finally:
            self.close()

            _loop.stop()
            _loop.run_forever()

            _loop.close()

A = Crawler()
A.run()





