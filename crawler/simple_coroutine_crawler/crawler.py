import logging
import asyncio
import aiohttp
import urllib.parse
from asyncio import Queue

logging.basicConfig(
    level=logging.DEBUG,
    format="[%(asctime)s] %(name)s:%(levelname)s: %(message)s"
)


class CrawlerBase:
    def __init__(self,
                 max_retries=3, loop=None,
                 max_tasks=3, max_redirect=1):
        self.max_retries = max_retries
        self.max_tasks = max_tasks
        self.max_redirect = max_redirect
        self.seen_urls = set()
        self.loop = loop or asyncio.get_event_loop()
        self.q = Queue(loop=self.loop)
        self.session = aiohttp.ClientSession(loop=self.loop)

    async def fetch(self, url, **kwargs):
        retries = 0
        logging.info("Preparing for fetching html {}".format(url))
        while retries < self.max_retries:
            try:
                resp = await self.session.get(url, **kwargs)
                # self.parse_resp(await self.session.get(url, **kwargs))
                if retries > 1:
                    logging.info('try {} for {} success'.format(retries, url))
                return await resp.text()  # break
            except aiohttp.client_exceptions as e:
                print(e)

            retries += 1

    def parse_resp(self, resp):
        raise NotImplementedError

    def close(self):
        self.session.close()

    async def work(self):
        try:
            while True:
                url, max_redirect = await self.q.get()
                assert url in self.seen_urls
                resp = await self.fetch(url)
                self.parse_resp(resp)
                await self.sleep()
                self.q.task_done()
        except asyncio.CancelledError:
            pass

    @staticmethod
    def url_check(url):
        parts = urllib.parse.urlparse(url)
        if parts.scheme not in ('http', 'https'):
            logging.debug('skipping non-http scheme in {}'.format(url))
            return False
        return True

    def add_url(self, url, max_redirect=None):
        if max_redirect is None:
            max_redirect = self.max_redirect
        logging.info('adding {} {}'.format(url, max_redirect))
        if self.url_check(url):
            self.seen_urls.add(url)
            self.q.put_nowait((url, max_redirect))
        else:
            logging.info('adding {} {} failed'.format(url, max_redirect))

    def add_url_from_file(self, file_path, max_redirect=None):
        if max_redirect is None:
            max_redirect = self.max_redirect
        with open(file_path, "r") as _f:
            lines = _f.readlines()
            for url in lines:
                logging.info('adding {} {}'.format(url, max_redirect))
                if self.url_check(url):
                    self.seen_urls.add(url)
                    self.q.put_nowait((url, max_redirect))
                else:
                    logging.info('adding {} {} failed'.format(url, max_redirect))

    async def run_work(self):
        workers = [asyncio.Task(self.work(), loop=self.loop)
                   for _ in range(self.max_tasks)]
        await self.q.join()
        for w in workers:
            w.cancel()

    @staticmethod
    async def sleep():
        await asyncio.sleep(1)









