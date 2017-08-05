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


        try:
            soup = BeautifulSoup(resp, 'lxml')
            _list = soup.select("#h-content > div.uk-container > div.h-threads-list > div")
            for child in _list:
                _img = child.select("div.h-threads-item-main > div.h-threads-img-box > a")
                img = _img[0]["href"] if len(_img) > 0 else None

                _title = child.select("div.h-threads-item-main > div.h-threads-info > span.h-threads-info-title")
                title = _title[0].get_text().strip() if len(_title) > 0 else None

                _time = child.select("div.h-threads-item-main > div.h-threads-info > span.h-threads-info-createdat")
                time = _time[0].get_text() if len(_time) > 0 else None

                _uid = child.select("div.h-threads-item-main > div.h-threads-info > span.h-threads-info-uid")
                uid = _uid[0].get_text() if len(_uid) > 0 else None

                _id = child.select("div.h-threads-item-main > div.h-threads-info > a.h-threads-info-id")
                id = _id[0].get_text() if len(_id) > 0 else None

                href = _id[0]["href"] if id else None

                _content = child.select("div.h-threads-item-main > div.h-threads-content")
                content = _content[0].get_text().strip() if len(_content) > 0 else None

                _replys = child.select("div.h-threads-item-replys")
                replys = _replys[0] if len(_replys) > 0 else None

                replys_list = list()
                if replys and replys.children:
                    for _child in replys.children:
                        if not isinstance(_child, bs4.element.Tag):
                            continue

                        _reply_img = _child.select("div.h-threads-item-reply-main > div.h-threads-img-box > a")
                        reply_img = _reply_img[0]["href"] if len(_reply_img) > 0 else None

                        _reply_title = _child.select(
                            "div.h-threads-item-reply-main > div.h-threads-info > span.h-threads-info-title")
                        reply_title = _reply_title[0].get_text().strip() if len(_reply_title) > 0 else None

                        _reply_time = _child.select(
                            "div.h-threads-item-reply-main > div.h-threads-info > span.h-threads-info-createdat")
                        reply_time = _reply_time[0].get_text() if len(_reply_time) > 0 else None

                        _reply_uid = _child.select(
                            "div.h-threads-item-reply-main > div.h-threads-info > span.h-threads-info-uid")
                        reply_uid = _reply_uid[0].get_text() if len(_reply_uid) > 0 else None

                        _reply_id = _child.select("div.h-threads-item-reply-main > div.h-threads-info > a.h-threads-info-id")
                        reply_id = _reply_id[0].get_text() if len(_reply_id) > 0 else None

                        reply_href = _reply_id[0]["href"] if reply_id else None

                        _reply_content = _child.select("div.h-threads-item-reply-main > div.h-threads-content")
                        reply_content = _reply_content[0].get_text().strip() if len(_reply_content) > 0 else None

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





